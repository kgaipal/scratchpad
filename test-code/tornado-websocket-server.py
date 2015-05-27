#!/usr/bin/env python
# -*- coding: utf-8 -*-

import time
import datetime
import tornado.httpserver
import tornado.websocket
import tornado.ioloop


class PingState:
    PONG_DEADLINE_EXPIRED = -1
    WAITING_FOR_PONG = 0
    SEND_PING = 1

    def __init__(self):
        self.last_ping_timestamp = None
        self.last_pong_timestamp = None
        self.pinged = 0     # number of times PINGed (testing purpose only)

    def state(self):
        if self.last_ping_timestamp is None:
            self.last_pong_timestamp = None
            return PingState.SEND_PING  # never PING-ed yet

        pongDeadlineTimestamp = self.last_ping_timestamp + WSHandler.PING_PONG_WINDOW
        currentTimestamp = time.time()

        # PONG never received
        if self.last_pong_timestamp is None:
            if currentTimestamp <= pongDeadlineTimestamp:
                return PingState.WAITING_FOR_PONG
            else:
                return PingState.PONG_DEADLINE_EXPIRED

        # PONG received atleast once
        if self.last_ping_timestamp < self.last_pong_timestamp \
           and self.last_pong_timestamp <= pongDeadlineTimestamp:
            return PingState.SEND_PING

        return PingState.PONG_DEADLINE_EXPIRED

    def ping_sent(self, ping_timestamp):
        self.last_ping_timestamp = ping_timestamp
        self.pinged += 1

    def got_pong(self, pong_timestamp):
        self.last_pong_timestamp = pong_timestamp

    def __repr__(self):
        return (
            "ping#: %d ping: %s pong: %s" % (
                self.pinged,
                str(self.last_ping_timestamp),
                str(self.last_pong_timestamp))
        )


class WSHandler(tornado.websocket.WebSocketHandler):

    # A PING should replied with a PONG within this duration (in seconds)
    PING_PONG_WINDOW = 5

    def open(self):
        print '** open %s **' % str(self)
        self.write_message("Hello, I am echo server.")

        self.ping_state = PingState()
        self.remind_to_ping()

    def on_message(self, message):
        if not self.ws_connection:
            return

        if message == 'quit' or message == 'bye':
            self.close()
        else:
            self.write_message(message)  # echo back

    # def on_close(self):
    #     print '** on_close %s **' % str(self)

    def on_pong(self, data):
        print '** on_pong %s **' % str(self)
        self.got_pong(data)

    def remind_to_ping(self, seconds=PING_PONG_WINDOW):
        tornado.ioloop.IOLoop.current().add_timeout(
            datetime.timedelta(seconds=seconds), self.send_ping)

    def send_ping(self):
        """Sends the PING to the given client (if needed).

        Send a PING if we are starting fresh or a new PING only if we have received a PONG
        earlier well within our waiting window. Otherwise disconnect the client because
        PONG is overdue (late or never received).

        """
        if not self.ws_connection:
            return

        ping_state = self.ping_state.state()
        print "%s [%s] ping action: %s" % (
            str(self), str(self.ping_state), ping_state
        )

        if ping_state == PingState.PONG_DEADLINE_EXPIRED:
            print "--> pong overdue, deleting", str(self)
            self.close()
            return

        if ping_state == PingState.SEND_PING:
            timestamp = time.time()
            self.ping(str(timestamp))
            self.ping_state.ping_sent(timestamp)
            print "--> sent ping at", self.ping_state.last_ping_timestamp

        self.remind_to_ping()

    def got_pong(self, data_received):
        if str(self.ping_state.last_ping_timestamp) == str(data_received):
            self.ping_state.got_pong(time.time())

            print "--> got  pong (%s) at %s" % (
                data_received, self.ping_state.last_pong_timestamp
            )


application = tornado.web.Application([
    (r'/', WSHandler),
])

if __name__ == "__main__":
    http_server = tornado.httpserver.HTTPServer(application)
    http_server.listen(8888)

    # start server
    tornado.ioloop.IOLoop.instance().start()

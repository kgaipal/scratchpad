#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import pdb
import socket
import ssl
import sys
import time
import websocket
from websocket import ABNF
from datetime import datetime, timedelta

# pdb.set_trace()

# Requirements: python packages: websocket-client
# Installation: pip install websocket-client

class State:
    DISCONNECTED = -1
    CONNECTED = 0

class MyWebSocket:
    def __init__(self):
        self.state = State.DISCONNECTED
        self.enable_trace = False

    def connect(self):
        if self.state != State.DISCONNECTED:
            self.disconnect()

        print "Connecting..."

        # start new connection
        websocket.enableTrace(self.enable_trace)
        ws = websocket.WebSocketApp(
            "ws://localhost:8888/",
            on_message=self.on_message,
            on_error=self.on_error,
            on_close=self.on_close,
            on_open=self.on_open,
            on_ping=self.on_ping,
            on_pong=self.on_pong)

        socket_options = [
            (socket.SOL_SOCKET, socket.SO_KEEPALIVE, 1),
            (socket.IPPROTO_TCP, socket.TCP_KEEPIDLE, 10),
            (socket.IPPROTO_TCP, socket.TCP_KEEPINTVL, 5),
            (socket.IPPROTO_TCP, socket.TCP_KEEPCNT, 1)
        ]

        ssl_options = {
            'cert_reqs': ssl.CERT_NONE
        }

        ws.run_forever(sockopt=socket_options, sslopt=ssl_options)

    def disconnect(self):
        if self.state == State.DISCONNECTED:
            raise Exception("already disconnected")

        self.state = State.DISCONNECTED
        print "disconnected"

    def on_open(self, ws):
        pass

    def on_close(self, ws):
        self.disconnect()
        print "** closed **"

    def on_error(self, ws, error):
        raise Exception(str(error))

    def on_ping(self, ws, data):
        print "** PING **", data
        # time.sleep(10)
        # print "got up"
        # ws.send("", opcode=ABNF.OPCODE_PONG)

    def on_pong(self, ws, data):
        print "** PONG **"

    def on_message(self, ws, message):
        print "Server:", message
        ws.send(raw_input("You:"))

def main():
    c = MyWebSocket()
    c.connect()

if __name__ == "__main__":
    main()

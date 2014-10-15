#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Requirements: python packages: websocket-client
# Installation: pip install websocket-client
# https://pypi.python.org/pypi/websocket-client/

class StateTableRecord:
    def __init__(self, recordId):
        self.recordId = recordId
        self.fields = {}        # map of fieldName:fieldValue

    def __str__(self):
        str_field = ""
        for f, v in self.fields.iteritems():
            str_field += str(f) + ":" + str(v) + "\n"
    
        return str_field


class StateTable:
    def __init__(self, tableId, name, fieldsInfo):
        self.tableId = tableId
        self.name = name
        self.fieldsInfo = fieldsInfo
        self.records = {} # map of "recordId":StateTableRecord

    def updateRecordField(self, recordId, field, value):
        if not recordId in self.records:
            self.records[recordId] = StateTableRecord(recordId)

        self.records[recordId].fields[field] = value

    def deleteRecord(self, recordId):
        if recordId in self.records:
            del self.records[recordId]
    
    def truncate(self):
        self.records = {}

    def __str__(self):
        header = "Table '%s'; fields: %d; records: %d\n" % (
            self.name, len(self.fieldsInfo), len(self.records))

        str_records = ""
        for record in self.records.values():
             str_records += str(record) + "\n"

        return header+str_records

STATE_TABLES = {
    "queue" : StateTable(
        "queue", "Queue", [
            ("id", "ID"),
            ("name", "Name"),
            ("code_name", "Code Name"),
            ("type", "Type"),
            ("support_team_id", "Support Team ID"),
            ("created_timestamp", "Created Timestamp")
        ]),
    "support_session" : StateTable(
        "support_session", "Support Session", [
            ("id", "ID"),
            ("lsid", "LSID"),
            ("queue_id", "Queue ID"),
            ("queue_entry_timestamp", "Queue Entry Timestamp"),
            ("customer_name", "Customer Name"),
            ("customer_company", "Customer Company"),
            ("customer_company_code", "Customer Company Code"),
            ("customer_description", "Customer Description"),
            ("start_method", "Start Method"),
            ("priority", "Priority"),
            ("estimated_pickup_timestamp", "Estimated Pickup Timestamp"),
            ("created_timestamp", "Created Timestamp")
        ]),
    "support_session_attribute" : StateTable(
        "support_session_attribute", "Support Session Attribute", [
            ("id", "ID"),
            ("support_session_id", "Support Session ID"),
            ("code_name", "Code Name"),
            ("value", "Value"),
            ("created_timestamp", "Created Timestamp")
        ]),
    "support_session_skill" : StateTable(
        "support_session_skill", "Support Session Skill", [
            ("id", "ID"),
            ("support_session_id", "Support Session ID"),
            ("code_name", "Code Name"),
            ("value", "Value"),
            ("created_timestamp", "Created Timestamp")
        ]),
    "customer_client" : StateTable(
        "customer_client", "Customer Client", [
            ("id", "ID"),
            ("support_session_id", "Support Session ID"),
            ("support_session_id", "Operating System"),
            ("hostname", "Hostname"),
            ("client_type", "Client Type"),
            ("elevated", "Elevated"),
            ("created_timestamp", "Created Timestamp")
        ]),
    "representative" : StateTable(
        "representative", "Representative", [
            ("id", "ID"),
            ("user_id", "User ID"),
            ("username", "Username"),
            ("private_display_name", "Private Display Name"),
            ("public_display_name", "Public Display Name"),
            ("routing_available", "Routing Available"),
            ("routing_idle", "Routing Idle"),
            ("routing_busy", "Routing Busy"),
            ("routing_enabled", "Routing Enabled"),
            ("skill_code_names", "Skill Code Names"),
            ("queue_id", "Queue ID"),
            ("created_timestamp", "Created Timestamp")
        ]),
    "representative_queue" : StateTable(
        "representative_queue", "Representative Queue", [
            ("id", "ID"),
            ("user_id", "User ID"),
            ("username", "Username"),
            ("private_display_name", "Private Display Name"),
            ("public_display_name", "Public Display Name"),
            ("routing_available", "Routing Available"),
            ("routing_idle", "Routing Idle"),
            ("routing_busy", "Routing Busy"),
            ("routing_enabled", "Routing Enabled"),
            ("skill_code_names", "Skill Code Names"),
            ("queue_id", "Queue ID"),
            ("created_timestamp", "Created Timestamp")
        ]),
    "representative_support_session" : StateTable(
        "representative_support_session", "Representative Support Session", [
            ("id", "ID"),
            ("support_session_id", "Support Session ID"),
            ("representative_id", "Representative ID"),
            ("created_timestamp", "Created Timestamp")
        ])
}

import json
import websocket

class State:
    DISCONNECTED = -1
    APP_CHOSER = 0
    AUTHENTICATE = 1
    SUBSCRIBE = 2
    UPDATES = 3

class Client:

    def __init__(self, site, company, enable_trace=True):
        self.state = State.DISCONNECTED
        self.site = site
        self.company = company
        self.enable_trace = enable_trace

    def on_open(self, ws):
        self.state = State.APP_CHOSER
        ws.send("NS01" + self.company + "\ningredi state api\n")

    def on_close(self, ws):
        self.disconnect()
        raise Exception("connection closed")

    def on_error(self, ws, error):
        raise Exception(str(error))

    def on_message(self, ws, message):
        message = message.decode('utf-8', 'ignore')

        if self.state == State.APP_CHOSER:
            if message != "0 Application chosen\n":
                raise Exception("Application choser failed")

            auth = {
                'type': "authenticate",
                'credentials': {
                    'username': "kgaipal",
                    'password': "password"
                }
            }
            ws.send(json.dumps(auth) + "\n")
            self.state = State.AUTHENTICATE

        elif self.state == State.AUTHENTICATE:
            resp = json.loads(message)
            if resp["success"] != True:
                raise Exception("Authentication failed")

            subscription = {
                'type': "subscribe",
                'tables': "all"
            }
            ws.send(json.dumps(subscription) + "\n")
            self.state = State.SUBSCRIBE

        elif self.state == State.SUBSCRIBE:
            resp = json.loads(message)
            if resp["success"] != True:
                raise Exception("Subscription failed")

            self.state = State.UPDATES

        elif self.state == State.UPDATES:
            model_update = json.loads(message)

            updated = False
            if model_update["type"] == "update_model":
                if model_update.has_key("insert"):
                    self.parse_inserts(model_update["insert"])
                    updated = True

                if model_update.has_key("update"):
                    self.parse_updates(model_update["update"])
                    updated = True

                if model_update.has_key("delete"):
                    self.parse_deletes(model_update["delete"])
                    updated = True
    
            elif model_update["type"] == "truncate_model":
                for table in STATE_TABLES.values():
                    table.truncate()
                updated = True

            if updated:
                print "\n"
                self.printAllTables()

        else:
            raise Exception("Unkown state: " + str(self.state))

    def printAllTables(self):
        for table in STATE_TABLES.values():
            if table is not None:
                print str(table) + "\n**"
            else:
                print "<empty>\n**"

    def parse_inserts(self, msg):
        self.parse_updates(msg)         # same structure

    def parse_updates(self, msg):
        for table in msg:
            for recId, record in msg[table].items():
                for field, value in record.items():
                    STATE_TABLES[table].updateRecordField(recId, field, value)

    def parse_deletes(self, msg):
        for table in msg:
            for recId in msg[table]:
                print "KGAIPAL: " + str(recId)
                STATE_TABLES[table].deleteRecord(recId)

    def connect(self):
        if self.state != State.DISCONNECTED:
            self.disconnect()

        # start new connection
        websocket.enableTrace(self.enable_trace)
        ws = websocket.WebSocketApp(
            "wss://" + self.site + "/nw",
            on_message = self.on_message,
            on_error = self.on_error,
            on_close = self.on_close,
            on_open = self.on_open)

        ws.run_forever()

    def disconnect(self):
        if self.state == State.DISCONNECTED:
            raise Exception("already disconnected")

        self.state = State.DISCONNECTED
        print "disconnected"


if __name__ == "__main__":

    try:
        c = Client("kgaipalrtd.dev.bomgar.com", "kgaipalrtd", False)
        c.connect()

    except Exception, e:
        print str(e)
        c.disconnect()

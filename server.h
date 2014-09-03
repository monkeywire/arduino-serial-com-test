#ifndef SERVER_ACTIONS_H
#define SERVER_ACTIONS_H

#include "arduino-serial/arduino-serial-lib.h"
#include "mongoose/mongoose.h"

#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include <tclap/CmdLine.h>
#include <jsoncpp/json/json.h>

extern int fd;

int event_handler(struct mg_connection *conn, enum mg_event ev);

/*URI Handlers*/
void query (struct mg_connection *conn, enum mg_event ev);
void set   (struct mg_connection *conn, enum mg_event ev);

#endif
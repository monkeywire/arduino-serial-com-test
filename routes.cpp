#include "server.h"

int event_handler(struct mg_connection *conn, enum mg_event ev) {
    if(ev == MG_AUTH) {

        return MG_TRUE;

    } else if(ev == MG_REQUEST && !strcmp(conn->uri, "/set")) {
        set(conn, ev);
        return MG_TRUE;

    } else if(ev == MG_REQUEST && !strcmp(conn->uri, "/query")) {
        query(conn, ev);
        return MG_TRUE;

    } else {
        return MG_FALSE;
    }
}
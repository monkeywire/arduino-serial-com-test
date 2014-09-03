#include "server.h"

void query(struct mg_connection *conn, enum mg_event ev) {

    char buffer[32] = {0};
    serialport_write(fd, "01q");
    usleep(10); // Time for the response to hit the buffer
    serialport_read_until(fd, buffer, '\0', 32, 10);

    Json::Value result;
    result["success"] = true;
    result["value"]   = buffer;
    mg_printf_data(conn, "%s", result.toStyledString().c_str());
}

void set(struct mg_connection *conn, enum mg_event ev) {
    char command;
    char buffer[32] = {0};
    char param [16] = {0};
    char value [16] = {0};
    Json::Value result;

    if(mg_get_var(conn, "param", param, 16) == -1) {
        result["success"] = false;
        result["error"]   = "param was not set";
        mg_printf_data(conn, "%s", result.toStyledString().c_str());
        return;
    }

    if(mg_get_var(conn, "value", value, 16) == -1) {
        result["success"] = false;
        result["error"]   = "value was not set";
        mg_printf_data(conn, "%s", result.toStyledString().c_str());
        return;
    }

    if      (strcmp(param, "blink") == 0) command = 'b';
    else if (strcmp(param, "pwm"  ) == 0) command = 'p';
    else {
        result["success"] = false;
        result["error"]   = "param was not found";
        mg_printf_data(conn, "%s", result.toStyledString().c_str());
        return;
    }

    sprintf(buffer, "%02i%c%s", strlen(value) + 1, command, value);
    serialport_write(fd, buffer);

    result["success"] = true;
    mg_printf_data(conn, "%s", result.toStyledString().c_str());
}

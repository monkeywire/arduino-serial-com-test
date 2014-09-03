#include "server.h"

using namespace std;
using namespace TCLAP;

int fd = -1;

int main(int argc, char** argv) {
    try {

        CmdLine cmd("Mongoose for Arudino", ' ', "alpha");
        ValueArg<string> portArg ("p", "port", "Port that the server will use", false, "8080", "string");
        ValueArg<string> rootArg ("r", "root", "Document root for html pages",  false,    ".", "string");

        cmd.add(portArg);
        cmd.add(rootArg);
        cmd.parse(argc, argv);

        printf("Server starting and being served at http:://localhost:%s\n", portArg.getValue().c_str());
        printf("Ctrl-c to stop server...\n");

        struct mg_server *server = mg_create_server(NULL, event_handler);
        mg_set_option(server, "document_root",   rootArg.getValue().c_str());
        mg_set_option(server, "listening_port",  portArg.getValue().c_str());

        fd = serialport_init("/dev/ttyACM0", 9600);
        if(fd == -1) printf("Error opening serial port");
        serialport_flush(fd);

        while(1) { mg_poll_server(server, 1000); }
        mg_destroy_server(&server);
        serialport_close(fd);

    } catch (const TCLAP::ArgException& e) {
        printf(e.what());
    }

    return 0;
}

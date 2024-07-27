#ifndef _STARTSERVER_H
#define _STARTSERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <microhttpd.h>
#include "serve.h"
#include "handle.h"
#include "config.h"

// Starts a html server on a port
static int startserver(unsigned int PORT, struct server_config config) {

    if (PORT == 0 || PORT > 65535) {
        return -1;
    }

    // Start http server with daemon
    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_INTERNAL_POLLING_THREAD, PORT, NULL, NULL, 
                              &request_handler, &config, MHD_OPTION_END);

    // If daemon/ http server fails 
    if (daemon == NULL) {
        printf("Server failed to run\n");
        return -1;
    }

    printf("Server is running on http://localhost:%d\n", PORT);

    // getchar() will keep the server running until enter or ctrl-c is entered into stdin
    getchar();

    // Stop the http server after getchar() and return
    MHD_stop_daemon(daemon);
    return 0;
}
#endif

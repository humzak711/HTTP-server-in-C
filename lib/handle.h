#ifndef _HANDLE_H
#define _HANDLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include "config.h"
#include "serve.h"

static enum MHD_Result request_handler(void *cls, struct MHD_Connection *connection,
                    const char *url, const char *method, const char *version,
                    const char *upload_data, size_t *upload_data_size, void **con_cls) {

    struct server_config *config = (struct server_config *)cls;

    // Only accept get requests
    if (strcmp(method, "GET") != 0) {
        return MHD_NO;
    }

    // Get the html file from the config struct and render it to the connection
    return serve_html(config->html_file_path, connection);
}

#endif

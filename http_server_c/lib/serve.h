#ifndef SERVE_H
#define SERVE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>


static enum MHD_Result serve_html(const char *file_path, struct MHD_Connection *connection) {

    // Prepare the html template
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        return MHD_NO;
    }

    // Check the html templates file size to see how much memory we need to allocate to a buffer
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Create a buffer the size of the file size
    char *buffer = (char *)malloc(file_size + 1);
    if (!buffer) {
        fclose(file);
        return MHD_NO;
    }

    // Read the html template into the buffer
    fread(buffer, 1, file_size, file);
    fclose(file);

    // Set up a response with our buffer
    struct MHD_Response *response = MHD_create_response_from_buffer(file_size, (void *)buffer, MHD_RESPMEM_MUST_FREE);
    if (!response) {
        free(buffer);
        return MHD_NO;
    }

    // Store our content type
    const char *mime_type = "text/html";
    if (strstr(file_path, ".css")) {
        mime_type = "text/css";
    } else if (strstr(file_path, ".js")) {
        mime_type = "application/javascript";
    }

    // Prepare and send the response
    MHD_add_response_header(response, "Content-Type", mime_type);
    enum MHD_Result ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response); // MHD_destroy_response should prevent memory leaks

    return ret;
}

#endif
#include <stdio.h>
#include <stdlib.h>
#include <microhttpd.h>
#include "lib/serve.h"
#include "lib/handle.h"
#include "lib/config.h"
#include "lib/startserver.h"

#define PORT 8888

int main() {
    struct MHD_Daemon *daemon; // Create a daemon 

    // Create a configuration struct with the path to our html template
    struct server_config config;
    config.html_file_path = "templates/index.html"; 

    // Start our HTTP web server with our static html template
    startserver(PORT, config);
    
    return 0; // return a 0 :o
}

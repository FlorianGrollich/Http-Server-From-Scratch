
#include <string.h>
#include "handleRoutes.h"



char* handle_routes(char* URI) {
    if (strcmp(URI, "/") == 0) {
        return "html/index.html";
    }
    else if (strcmp(URI, "/sendMessage") == 0) {
        return "html/index.html";
    }

    return "html/404.html";
}

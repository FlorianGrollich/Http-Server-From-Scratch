//
// Created by F-Gro on 31.03.2023.
//
#include "HTTPRequest.h"
#include <string.h>

struct HTTPRequest http_request_constructor(char *request_string) {
    for (int i = 0; i< strlen(request_string)-2; i++) {

    }
    char *request_line = strtok(request_string, "\n");

}
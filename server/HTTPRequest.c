//
// Created by F-Gro on 31.03.2023.
//
#include "HTTPRequest.h"
#include <string.h>

struct HTTPRequest http_request_constructor(char *request_string) {
    for (int i = 0; i< strlen(request_string)-2; i++) {
        if(request_string[i] == '\n' && request_string[i+1] == '\n') {
            request_string[i+1] = '|';
        }
    }
    char *request_line = strtok(request_string, "\n");
    char *header_fields = strtok(NULL, "|");
    char *message_body = strtok(NULL, "|");

    struct HTTPRequest request;

    char *method = strtok(request_line, " ");
    if(strcmp(method, "GET") == 0) {
        request.method = GET;
    } else if(strcmp(method, "POST") == 0) {
        request.method = POST;
    } else if(strcmp(method, "PUT") == 0) {
        request.method = PUT;
    } else if(strcmp(method, "DELETE") == 0) {
        request.method = DELETE;
    } else if(strcmp(method, "HEAD") == 0) {
        request.method = HEAD;
    } else if(strcmp(method, "OPTIONS") == 0) {
        request.method = OPTIONS;
    }
    else if(strcmp(method, "CONNECT") == 0) {
        request.method = CONNECT;
    }
    else if(strcmp(method, "PATCH") == 0) {
        request.method = PATCH;
    }
}
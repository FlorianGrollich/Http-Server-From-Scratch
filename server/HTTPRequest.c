//
// Created by F-Gro on 31.03.2023.
//
#include "HTTPRequest.h"
#include <string.h>


int method_select(char *method) {
    if(strcmp(method, "GET") == 0) {
        return GET;
    } else if(strcmp(method, "POST") == 0) {
        return POST;
    } else if(strcmp(method, "PUT") == 0) {
        return PUT;
    } else if(strcmp(method, "DELETE") == 0) {
        return DELETE;
    } else if(strcmp(method, "HEAD") == 0) {
        return HEAD;
    } else if(strcmp(method, "OPTIONS") == 0) {
        return OPTIONS;
    }
    else if(strcmp(method, "CONNECT") == 0) {
        return CONNECT;
    }
    else if(strcmp(method, "PATCH") == 0) {
        return PATCH;
    }
}

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
    request.Method = method_select(method);
    char *URI = strtok(NULL, " ");
    request.URI = URI;
    char *HTTPVersion = strtok(NULL, " ");
    HTTPVersion = strtok(HTTPVersion,"/");
    HTTPVersion = strtok(NULL,"/");



    return request;
}
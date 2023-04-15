#include "HTTPRequest.h"
#include <string.h>
#include <stdlib.h>

#include "../DataStructures/Lists/Queue.h"

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

struct Dictionary query_parameters_constructor(char *URI) {
    struct Dictionary query_parameters = dictionary_constructor(compare_string_keys);
    char *query_string = strchr(URI, '?');
    if(query_string) {
        query_string++;
        char *token = strtok(query_string, "&");
        while(token) {
            char *key = strtok(token, "=");
            char *value = strtok(NULL, "&");
            query_parameters.insert(&query_parameters, key,sizeof(*key), value, sizeof(*value));
            token = strtok(NULL, "&");
        }
    }
    return query_parameters;
}

struct HTTPRequest http_request_constructor(char *request_string) {


    char request_string_copy[strlen(request_string)];
    strcpy(request_string_copy, request_string);
    for (int i = 0; i< strlen(request_string_copy)-2; i++) {
        if(request_string_copy[i] == '\n' && request_string_copy[i+1] == '\n') {
            request_string_copy[i+1] = '|';
        }
    }
    char *request_line = strtok(request_string_copy, "\n");
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
    request.HTTPVersion = (float)atof(HTTPVersion);

    request.header_fields = dictionary_constructor(compare_string_keys);

    struct Queue headers = queue_constructor();

    char *token = strtok(header_fields, "\n");
    while(token) {
        headers.push(&headers, token, sizeof(*token));
        token = strtok(NULL, "\n");
    }

    char *header = (char *)headers.peek(&headers);

    while(header) {
        char *key = strtok(header, ":");
        char *value = strtok(NULL, "|");
        request.header_fields.insert(&request.header_fields, key, sizeof(*key), value, sizeof(*value));
        headers.pop(&headers);
        header = (char *)headers.peek(&headers);
    }

    int hasQueryParameters = strchr(URI, '?') != NULL;
    if(hasQueryParameters) {
        request.query_parameters = query_parameters_constructor(URI);
    }


    return request;
}
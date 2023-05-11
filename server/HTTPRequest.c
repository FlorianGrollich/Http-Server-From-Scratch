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
    return -1;
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
    char *request_line = strtok(request_string_copy, "\n");
    char *header_fields = strtok(NULL, "|");

    struct HTTPRequest request;

    char *method = strtok(request_line, " ");
    request.Method = method_select(method);
    char *URI = strtok(NULL, " ");
    request.URI = URI;
    char *HTTPVersion = strtok(NULL, " ");
    HTTPVersion = strtok(HTTPVersion,"/");
    HTTPVersion = strtok(NULL,"/");
    request.HTTPVersion = (float)atof(HTTPVersion);

    char *content_type_header = "Content-Type: application/x-www-form-urlencoded";
    char *content_length_header = "Content-Length: ";
    char *payload_start = strstr(header_fields, "\r\n\r\n") + 4;
    char *content_type_field = strstr(header_fields, content_type_header);
    char *content_length_field = strstr(header_fields, content_length_header);

    if (content_type_field != NULL && content_length_field != NULL) {
        char *content_length_str = content_length_field + strlen(content_length_header);
        int content_length = atoi(content_length_str);

        request.Payload = malloc(content_length + 1);
        strncpy(request.Payload, payload_start, content_length);
        request.Payload[content_length] = '\0';
    } else {
        request.Payload = NULL;
    }


    return request;
}
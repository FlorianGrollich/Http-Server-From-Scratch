


#ifndef HTTPRequest_h
#define HTTPRequest_h

#include "../DataStructures/Dictionary/Dictionary.h"

enum HTTPMethod {
    GET,
    POST,
    PUT,
    DELETE,
    HEAD,
    OPTIONS,
    CONNECT,
    PATCH
};

struct HTTPRequest {
    enum HTTPMethod Method;
    char *URI;
    float HTTPVersion;
    struct Dictionary query_parameters;
    struct Dictionary header_fields;
    char *Payload;
};

int method_select(char *method);

struct Dictionary query_parameters_constructor(char *URI);

struct HTTPRequest http_request_constructor(char *request_string);

#endif /* HTTPRequest_h */
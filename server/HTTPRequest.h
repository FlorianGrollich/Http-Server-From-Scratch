


#ifndef HTTPRequest_h
#define HTTPRequest_h

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
    enum HTTPMethod method;
    char *URI;
    float HTTPVersion;

};


struct HTTPRequest http_request_constructor(char *request_string);

#endif /* HTTPRequest_h */
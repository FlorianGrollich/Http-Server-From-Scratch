#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HTTPResponse.h"


char* get_HTML_response(char* filename, char** string_list, int num_strings) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("file open failed");
        exit(1);
    }
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *html = malloc(fsize + 1);
    if (html == NULL) {
        perror("memory allocation failed");
        exit(1);
    }

    size_t read_size = fread(html, 1, fsize, fp);
    if (read_size != fsize) {
        perror("file read failed");
        exit(1);
    }

    fclose(fp);

    html[fsize] = '\0';

    // create a string for the list of strings
    char list_str[4096] = "";
    for (int i = 0; i < num_strings; i++) {
        strcat(list_str, "<li>");
        strcat(list_str, string_list[i]);
        strcat(list_str, "</li>");
    }

    // create the final response string
    char* response = malloc(4096 + fsize + strlen(list_str) + 1);
    if (response == NULL) {
        perror("memory allocation failed");
        exit(1);
    }
    snprintf(response, 4096 + fsize + strlen(list_str) + 1,
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html\r\n"
             "Cache-Control: no-cache, no-store, must-revalidate\r\n"
             "Expires: 0 \r\n"
             "Content-Length: %ld\r\n"
             "\r\n"
             "%s"
             "<ul>%s</ul>",
             fsize + strlen(list_str) + 10, html, list_str
    );

    free(html);

    return response;
}
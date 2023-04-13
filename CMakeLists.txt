cmake_minimum_required(VERSION 3.24)
project(server_from_scratch C)

set(CMAKE_C_STANDARD 11)

add_executable(client client.c)
add_executable(server main.c server/Server.c)

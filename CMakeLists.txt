cmake_minimum_required(VERSION 3.24)
project(server_from_scratch C)

set(CMAKE_C_STANDARD 11)

add_executable(client client.c main.c)
add_executable(server main.c server/Server.c)
add_executable(main main.c server/Server.c)

# Copy HTML file to build directory
configure_file(index.html index.html COPYONLY)
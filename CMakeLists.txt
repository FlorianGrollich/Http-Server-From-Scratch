cmake_minimum_required(VERSION 3.24)
project(server_from_scratch C)
link_libraries(ws2_32 wsock32)

set(CMAKE_C_STANDARD 11)

add_executable(client client.c)
add_executable(server main.c server/Server.c)
target_link_libraries(server ws2_32)
target_link_libraries(server wsock32)

cmake_minimum_required(VERSION 3.24)
project(server_from_scratch C)

set(CMAKE_C_STANDARD 11)
add_library(dictionary DataStructures/Dictionary/Dictionary.c DataStructures/Dictionary/Dictionary.h)
add_library(queue DataStructures/Lists/Queue.c DataStructures/Lists/Queue.h)
add_library(linked_list DataStructures/Lists/LinkedList.c DataStructures/Lists/LinkedList.h)
add_library(binary_tree DataStructures/Trees/BinarySearchTree.c DataStructures/Trees/BinarySearchTree.h)
add_library(node DataStructures/Common/Node.c DataStructures/Common/Node.h)
add_library(entry DataStructures/Dictionary/Entry.c DataStructures/Dictionary/Entry.h)


add_executable(client client.c main.c)
add_executable(server main.c server/Server.c)

add_executable(main main.c server/Server.c server/HTTPRequest.c handleRoutes.c server/HTTPResponse.c)

target_link_libraries(main dictionary queue linked_list node binary_tree entry)

# Copy HTML file to build directory
configure_file(html/index.html html/index.html COPYONLY)
configure_file(html/404.html html/404.html COPYONLY)
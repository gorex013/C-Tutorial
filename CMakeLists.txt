cmake_minimum_required(VERSION 3.13)
project(Chat C)

set(CMAKE_C_STANDARD 99)

#add_executable(Chat_client Exp/client.c Exp/client.h)
#add_executable(Chat_server Exp/server.c Exp/server.h)
add_executable(Main_File_Descriptors "Chat/File Descriptors/main.c")
add_executable(Main_Threads "Chat/Threads/main.c" Chat/Threads/main.c)
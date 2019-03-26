cmake_minimum_required(VERSION 3.13)
project(Chat C)

set(CMAKE_C_STANDARD 99)

#add_executable(Chat_client Exp/client.c Exp/client.h)
#add_executable(Chat_server Exp/server.c Exp/server.h)
add_executable(Main Chat/main.c)
#add_executable(Server server.c)
#add_executable(Client client.c)
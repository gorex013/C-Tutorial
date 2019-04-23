//
// Created by vasile on 4/23/19.
//

#ifndef CHAT_SERVER_H
#define CHAT_SERVER_H
/*
    C socket server example, handles multiple clients using threads
    Compile
    gcc server.c -lpthread -o server
*/

#include<stdio.h>
#include<string.h>    //strlen
#include<stdlib.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<pthread.h> //for threading , link with lpthread

#define TRUE 1
#define FALSE 0
#define PORT 9973
#define MAX_CLIENTS 30
int server_port;

//the thread function
void *connection_handler(void *);


#endif //CHAT_SERVER_H

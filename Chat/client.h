//
// Created by Vasile Rotaru on 08-Mar-19.
//

#ifndef CHAT_CLIENT_H
#define CHAT_CLIENT_H

#include <stdlib.h>
#include <stdio.h> //printf
#include <string.h>    //strlen
#include <sys/socket.h>    //socket
#include <arpa/inet.h> //inet_addr
#include <unistd.h>

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT 9973

//message buffer related delcartions/macros
int buffer_message(char *message);

int find_network_newline(char *message, int inbuf);

#define COMPLETE 0
#define BUF_SIZE 256

static int inbuf; // how many bytes are currently in the buffer?
static int room; // how much room left in buffer?
static char *after; // pointer to position after the received characters

#endif //CHAT_CLIENT_H

#include "client.h"

//main starts below
char *server_address;
int server_port;

int client(int argc, char **argv) {
    server_address = (char *) malloc(15);
    if (argc != 3) {
        printf("To connect remotely, insert as arguments address and port of the remote server.\n");
        strcpy(server_address, SERVER_ADDRESS);
        server_port = SERVER_PORT;
    } else {
        strcpy(server_address, argv[1]);
        server_port = strtol(argv[2], NULL, 10);
    }
    int sock;
    struct sockaddr_in server;
    char message[max_message_length], server_reply[max_message_length];

    //Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("Could not create socket");
    }

    server.sin_addr.s_addr = inet_addr(server_address);
    server.sin_family = AF_INET;
    server.sin_port = htons(server_port);

    //Connect to remote server
    if (connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("connect failed. Error");
        return 1;
    }

//set up variables for select()
    fd_set all_set, r_set;
    int maxfd = sock + 1;
    FD_ZERO(&all_set);
    FD_SET(STDIN_FILENO, &all_set);
    FD_SET(sock, &all_set);
    r_set = all_set;
    struct timeval tv;
    tv.tv_sec = 2;
    tv.tv_usec = 0;

//set the initial position of after
    after = message;
//keep communicating with server
    for (;;) {

        r_set = all_set;
        //check to see if we can read from STDIN or sock
        select(maxfd, &r_set, NULL, NULL, &tv);
        memset(message, 0, strlen(message));
        if (FD_ISSET(STDIN_FILENO, &r_set)) {
            if (buffer_message(message) == COMPLETE) {
                //Send some data
                message[strlen(message)] = '\0';
                if (send(sock, message, strlen(message) + 1, 0) <
                    0)//NOTE: we have to do strlen(message) + 1 because we MUST include '\0'
                {
                    puts("Send failed");
                    return 1;
                }

            }
        }

        if (FD_ISSET(sock, &r_set)) {
            //Receive a reply from the server

            if (recv(sock, server_reply, max_message_length, 0) < 0) {
                puts("recv failed");
                break;
            }
            server_reply[strlen(server_reply)] = '\0';
            printf("%s\n", server_reply);
            memset(server_reply, 0, strlen(server_reply));


        }
    }

    close(sock);
    return 0;
}

int buffer_message(char *message) {

    int bytes_read = read(STDIN_FILENO, after, (unsigned int) (max_message_length - inbuf));
    short flag = -1; // indicates if returned_data has been set
    inbuf += bytes_read;
    int where; // location of network newline

    // Step 1: call findeol, store result in where
    where = find_network_newline(message, inbuf);
    if (where >= 0) { // OK. we have a full line

        // Step 2: place a null terminator at the end of the string
        char *null_c = "\0";
        memcpy(message + where, &null_c, 1);

        // Step 3: update inbuf and remove the full line from the clients's buffer
        memmove(message, message + where + 1, (size_t) (inbuf - (where + 1)));
        inbuf -= (where + 1);
        flag = 0;
    }

    // Step 4: update room and after, in preparation for the next read
    room = sizeof(message) - inbuf;
    after = message + inbuf;

    return flag;
}

int find_network_newline(char *message, int bytes_inbuf) {
    int i;
    for (i = 0; i < inbuf; i++) {
        if (*(message + i) == '\n')
            return i;
    }
    return -1;
}
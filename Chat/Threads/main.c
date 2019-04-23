//
// Created by vasile on 4/23/19.
//

#include "server.c"
#include "../File Descriptors/client.c"

int main(int argc, char **argv){
    if (argc < 2) {
        printf("To start in server mode use `-s` or `--server`.\nTo start in client mode use `-c` or `--client`.\n");
        return 0;
    }
    if (strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "--server") == 0) {
        printf("Starting in server mode!\n");
        server(argc - 1, argv + 1);
        return 0;
    } else if (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--client") == 0) {
        printf("Starting in client mode!\n");
        client(argc - 1, argv + 1);
        return 0;
    }
    printf("Unknown option `%s`.\n", argv[1]);
    return 0;
}
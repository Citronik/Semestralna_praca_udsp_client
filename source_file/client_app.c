//
// Created by Filip on 6. 1. 2023.
//
#include "../header_file/client_app.h"

void * client_start_app() {
    TOKEN * token = malloc(sizeof(TOKEN));
    token_init(token);
    SOCKET soket;
    client_socket_started(&soket, "127.0.0.1", 11111);
    DATA * data = malloc(sizeof(DATA));
    data_init(data,soket.newsockfd);
    read_message(data, token);
    printf("%s\n",token->response_);
    bool koniec = false;
    int result = 0;
    while (!koniec) {
        if (system_is_user_authenticated(token)) {
            system_authentification(data, token);
        } else {
            printf("MENU:\n"
                   " [1] VYPISAT FILMY Z KNIZNICE\n"
                   " [2] ZORADIT FILMY\n"
                   " [3] HLADAT FILM PODLA HERCA\n"
                   " [4] HLADAT FILM PODLA ZANRU\n"
                   " [5] POZICAT SI FILM PODLA ID\n"
                   " [6] VYPISAT MOJU KNIZNICU\n"
                   " [7] VRATIT FILM PODLA ID\n");
            scanf("%d",&result);
        }
    }
}
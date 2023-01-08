//
// Created by Filip on 6. 1. 2023.
//
#include "../header_file/client_app.h"

void * client_start_app() {
    TOKEN * token = malloc(sizeof(TOKEN));
    token_init(token);
    SOCKET soket;
    USER * user;
    client_socket_started(&soket, "127.0.0.1", 11112);
    DATA * data = malloc(sizeof(DATA));
    data_init(data,soket.newsockfd);
    read_message(data, token);
    printf("%s\n",token->response_);
    bool koniec = false;
    int result = 0;
    while (!koniec) {
        if (system_is_user_authenticated(token)) {
            user = system_authentification(data, token);
        } else {
            printf("MENU:\n"
                   " [1] DISPLAY COMPONENTS\n"
                   " [2] SORT COMPONENTS\n"
                   " [3] FIND COMPONENTS\n"
                   " [4] DISPLAY YOUR CARTS\n"
                   " [5] RETURN COMPONENT\n"
                   " [6] EXIT\n");
            scanf("%d",&result);
        }


    }
}
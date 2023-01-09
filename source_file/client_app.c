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
                   " [3] BUY COMPONENT\n"
                   " [4] RETURN COMPONENT\n"
                   " [5] DISPLAY YOUR COMPONENTS\n"
                   " [6] FIND COMPONENTS\n"
                   " [7] LOGOUT\n"
                   " [10] EXIT\n");
            scanf("%d",&result);
            switch (result) {
                case 1:
                    //DISPLAY COMPONENTS
                    system_print_all_components(data , token);
                    break;
                case 2:
                    //SORT COMPONENTS
                    system_sort_components(data , token);
                    system_print_all_components(data , token);
                    break;
                case 3:
                    //BUY COMPONENT
                    break;
                case 4:
                    //RETURN COMPONENT
                    break;
                case 5:
                    //DISPLAY YOUR COMPONENTS
                    system_print_user_components(user, data, token);
                    break;
                case 6:
                    //FIND COMPONENTS
                    system_find_component_by_identifier(data, token);
                    break;
                case 7:
                    //LOGOUT
                    system_user_unathorize(data, token, user);
                    break;
                case 10:
                    //EXIT
                    break;
                default:
                    break;
            }
        }
    }
}
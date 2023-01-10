//
// Created by Filip on 6. 1. 2023.
//
#include "../header_file/client_app.h"

void * client_start_app() {
    TOKEN * token = malloc(sizeof(TOKEN));
    token_init(token);
    SOCKET soket;
    USER * user = malloc(sizeof(USER));
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
            printf("  MENU[%s]:\n"
                   "|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|\n"
                   "|  [1]  DISPLAY COMPONENTS      |\n"
                   "|  [2]  SORT COMPONENTS         |\n"
                   "|  [3]  BUY COMPONENT           |\n"
                   "|  [4]  RETURN COMPONENT        |\n"
                   "|  [5]  DISPLAY YOUR COMPONENTS |\n"
                   "|  [6]  FIND COMPONENTS         |\n"
                   "|  [7]  LOGOUT                  |\n"
                   "|  [8]  TOP UP CREDIT           |\n"
                   "|  [9]  USER INFO               |\n"
                   "|  [10] EXIT                    |\n"
                   "|_______________________________|\n"
                   , user->username_);
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
                    system_buy_components(data, token, user);
                    break;
                case 4:
                    //RETURN COMPONENT
                    system_print_user_components(user, data, token);
                    system_return_component(data, token, user);
                    system_print_user_components(user, data, token);
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
                case 8:
                    //TOP UP CREDIT
                    system_user_top_up_credit(data, token, user);
                    //printf("%s\n", token->content_);
                    break;
                case 9:
                    //INFO ABOUT USER
                    user_to_string(user, token->content_);
                    printf("%s\n", token->content_);
                    break;
                case 10:
                    //EXIT
                    system_user_unathorize(data, token, user);
                    token->service_type_ = 0;
                    send_message(data, token);
                    koniec = true;
                    break;
                default:
                    //warning message
                    printf("[+]Wrong key\n");
                    break;
            }
        }
    }
    free(token);
    token = NULL;
    free(user);
    user = NULL;
    free(data);
    data = NULL;

}
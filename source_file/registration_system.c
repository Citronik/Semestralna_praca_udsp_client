//
// Created by Filip on 6. 1. 2023.
//
#include "../header_file/registration_system.h"

_Bool system_is_user_authenticated(TOKEN * token){
    return token->user_id_ == 0;
}

USER * system_authentification(DATA * data, TOKEN * token){
    int result = 0;
    do {
        printf("DO YOU HAVE ACCOUNT:\n"
               " [1] SIGN IN\n"
               " [2] SIGN UP\n");
        scanf("%d",&result);
    } while (!(result == 1 || result == 2));
    USER * user = malloc(sizeof(USER));
    user_init(user);
    if (result == 1){
        system_login_form(data, user, token);
    } else {
        system_registration_form(data, user, token);
    }
    //validate the data
    return user;
}

void system_registration_form(DATA *pData, USER *pUser, TOKEN *pToken) {
    pToken->service_type_ = 1;
    strcpy(pToken->content_, "User is filling data");
    send_message(pData, pToken);
    USER tmp_user;
    printf("Enter a first name: \n");
    scanf("%s",tmp_user.first_name_);

    printf("Enter a last name: \n");
    scanf("%s",tmp_user.last_name_);

    printf("Enter a username: \n");
    scanf("%s",tmp_user.username_);

    printf("Enter the password: \n");
    scanf("%s", tmp_user.password_);

    pData->state = write(pData->socket, &tmp_user, sizeof (USER));
    pData->state = read(pData->socket, pUser, sizeof (USER));
    read_message(pData, pToken);
}

void system_login_form(DATA *pData, USER * pUser, TOKEN *pToken) {
    pToken->service_type_ = 2;
    printf("Enter a username: \n");
    scanf("%s",pToken->content_);

    printf("Enter the password: \n");
    scanf("%s", pToken->content_+USER_NAME_LENGTH);
    send_message(pData, pToken);
    read_message(pData, pToken);
    pData->state = read(pData->socket, pUser, sizeof (USER));

    printf("Token ID : %d | Content %d - %s \n" , pToken->user_id_, pToken->service_type_, pToken->content_);
    printf("Response %d - %s \n", pToken->response_status_, pToken->response_);
    printf("user id: %d - %s \n", pUser->id_, pUser->first_name_);
}

void system_print_all_components(DATA * data, TOKEN * token){
    token->service_type_ = 3;
    send_message(data, token);

    token->response_status_ = RAND_MAX;
    strcpy(token->response_, "NOT END");
    printf("COMPONENTS FOR SALE\n");
    while (token->service_type_ <= token->response_status_ && strcmp(token->response_, "END") != 0){
        read_message(data, token);
        if (strcmp(token->response_, "END") != 0) {
            printf("COMPONENT num: [%d]\n", token->service_type_);
            printf("[%d]%s", token->service_type_, token->content_);
            if (token->service_type_%3 == 0) {
                printf("\n");
            }
        }
    }
    printf("COMPONENTS ARE PRINTED\n");
}

void system_user_unathorize(DATA * data, TOKEN * token, USER * user){
    token->service_type_ = 9;
    send_message(data, token);
    data->state = write(data->socket, user, sizeof (USER));
    read_message(data, token);
    data->state = read(data->socket, user, sizeof (USER));
    read_message(data, token);
    printf("USER LOGGED OUT %d, response: %c\n", token->user_id_, token->response_);
}

void system_sort_components(DATA * data, TOKEN * token){
    token->service_type_ = 4;
    int result = 0;
    do {
        printf("HOW DO YOU WANT TO SORT THE COMPONENTS:\n"
               " [1] BY PRICE\n"
               " [2] BY MODEL\n"
               " [3] BY YEAR\n");
        scanf("%d",&result);
    } while (!(result == 1 || result == 2 || result == 3));
    token->response_status_ = result;
    send_message(data, token);
}

void system_find_component_by_identifier(DATA * data, TOKEN * token){
    token->service_type_ = 8;
    char keyword[CONTENT_LENGTH] = {0};
    printf("WRITE A KEYWORD SO WE CAN HELP YOU FIND COMPONENT FOR YOU: \n");
    scanf("%s",keyword);
    strcpy(token->content_,keyword);
    send_message(data, token);

    token->response_status_ = RAND_MAX;
    strcpy(token->response_, "NOT END");
    printf("COMPONENTS FOR SALE\n");
    while (token->service_type_ <= token->response_status_ && strcmp(token->response_, "END") != 0){
        read_message(data, token);
        if (strcmp(token->response_, "END") != 0) {
            printf("COMPONENT num: [%d] from\n", token->service_type_);
            printf("%s", token->content_);
        }
    }
    printf("COMPONENTS ARE PRINTED\n");
}

void system_print_user_components(USER *user, DATA *data, TOKEN *token){
    token->service_type_ = 7;
    send_message(data, token);
    read_message(data, token);
    if (token->response_status_ == 200){
        data->state = read(data->socket, user, sizeof (USER));
        printf("%d\n", user->id_);
        for (int i = 0; i < user->number_of_owned_components_; ++i) {
            char cmp[BUFFER] = {0};
            component_to_string(&user->owned_components_[i], cmp);
            printf("[%d] %s", i, cmp);
            if (i%3 == 0) {
                printf("\n");
            }
        }
    }
    printf("%s\n", token->response_);
}

void system_buy_components(DATA * data, TOKEN * token, USER * user){
    token->service_type_ = 5;
    printf("WRITE NUMBER OF COMPONET  YOU WANT TO BUY\n");
    scanf("%d",&token->response_status_);
    send_message(data, token);
    read_message(data, token);
    if (token->response_status_ != 404){
        data->state = read(data->socket, user, sizeof (USER));
        printf("[+]COMPONENT: %s SUCCESFULLY ADDED TO USER: %d!\n"
                , user->owned_components_[user->number_of_owned_components_-1].model_
                , user->id_);
    }
    printf("%s\n", token->response_);
}

void system_return_component(DATA * data, TOKEN * token, USER *user){
    token->service_type_ = 6;
    printf("WRITE NUMBER OF COMPONET  YOU WANT TO RETURN\n");
    scanf("%d",&token->response_status_);
    send_message(data, token);
    read_message(data, token);
    printf("%s\n", token->response_);
    if (token->response_status_ != 200){
        return;
    }
    data->state = read(data->socket, user, sizeof (USER));
}

void system_user_top_up_credit(DATA * data, TOKEN * token, USER *user){
    token->service_type_ = 10;
    double credit = 0;
    do {
        memset(token->content_, 0 , sizeof(token->content_));
        printf("WRITE HOW MUCH CREDIT DO YOU WANT ADD\n");
        scanf("%lf",&credit);
        if (credit > 0) {
            sprintf(token->content_, "%lf", credit);
        }
    } while (strlen(token->content_) <= 0);
    send_message(data, token);
    read_message(data, token);
    if (token->response_status_ != 200){
        printf("%s\n", token->response_);
        return;
    }
    data->state = read(data->socket, user, sizeof(USER));
    printf("CREDIT WAS SUCCESSFULLY TOPPED UP\n");
    char buff[BUFFER] = {0};
    user_to_string(user, buff);
    printf("%s\n", buff);
}
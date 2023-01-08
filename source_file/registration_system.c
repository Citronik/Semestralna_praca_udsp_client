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

    printf("Enter a first name: \n");
    scanf("%s",pToken->content_);

    printf("Enter a last name: \n");
    scanf("%s",pToken->content_);

    printf("Enter a username: \n");
    scanf("%s",pToken->content_);

    printf("Enter the password: \n");
    scanf("%s", pToken->content_+USER_NAME_LENGTH);
    send_message(pData, pToken);
    read_message(pData, pToken);
    pData->state = read(pData->socket, pUser, sizeof (USER));

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

//
// Created by Filip on 6. 1. 2023.
//

#ifndef SEMESTRALNA_PRACA_UDSP_KLIENT_REGISTRATION_SYSTEM_H
#define SEMESTRALNA_PRACA_UDSP_KLIENT_REGISTRATION_SYSTEM_H

#include "user.h"
#include "token.h"
#include "socket_definitions.h"

_Bool system_is_user_authenticated(TOKEN * token);
USER * system_authentification(DATA * data, TOKEN * token);
void system_login_form(DATA *pData, USER *pUser, TOKEN *pToken);
void system_registration_form(DATA *pData, USER *pUser, TOKEN *pToken);
void system_print_all_components(DATA * data, TOKEN * token);
void system_user_unathorize(DATA * data, TOKEN * token, USER * user);
void system_sort_components(DATA * data, TOKEN * token);
void system_find_component_by_identifier(DATA * data, TOKEN * token);
void system_print_user_components(USER *user, DATA *data, TOKEN *token);
void system_buy_components(DATA * data, TOKEN * token, USER * user);
void system_return_component(DATA * data, TOKEN * token, USER *user);
_Bool system_user_top_up_credit(DATA * data, TOKEN * token, USER *user);

#endif //SEMESTRALNA_PRACA_UDSP_KLIENT_REGISTRATION_SYSTEM_H

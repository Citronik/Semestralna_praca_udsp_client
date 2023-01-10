//
// Created by slavi on 5. 1. 2023.
//
#include "../header_file/computer_component.h"

void component_init(COMPONENT * cp) {
    memset(cp->manufacturer_,0,strlen(cp->manufacturer_));
    memset(cp->type_,0,strlen(cp->type_));
    memset(cp->model_,0,strlen(cp->model_));
    cp->year_of_production_ = 0;
    cp->price_ = 0;
}

_Bool compare_components(const COMPONENT *cp1, const COMPONENT *cp2){
    if (strcmp(cp1->manufacturer_,cp2->manufacturer_) == 0){
        return true;
    }
    if (strcmp(cp1->type_,cp2->type_) == 0 && (cp1->year_of_production_ == cp2->year_of_production_)){
        return true;
    }
    return false;
}


char* component_to_string(const COMPONENT *cp, char *dest) {
    sprintf(dest, "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|\n"
                  " [Type]:  %s      \n"
                  " [Brand]: %s      \n"
                  " [Name]:  %s      \n"
                  " [Year]:  %d      \n"
                  " [Price]: %.2f€   \n"
                  "|___________________|\n"
            , cp->type_,cp->manufacturer_,cp->model_,cp->year_of_production_, cp->price_);
    return dest;
}
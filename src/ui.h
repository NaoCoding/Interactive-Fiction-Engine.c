#ifndef UI_H
#define UI_H
#include "std.h"


void html_setup(FILE * html){

    fwrite("<!DOCTYPE html>\n",16,1,html);
    fwrite("<html>\n",7,1,html);

}

#endif
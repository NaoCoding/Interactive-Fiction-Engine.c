#ifndef SMALLFN_H
#define SMALLFN_H
#include "std.h"
void fgetsDelendl(char * target){

    if(target[strlen(target)-1] <= 25)target[strlen(target)-1] = 0;
}

int string_compare(int start, int length , char * a , char * b){
    for(int i=start;i<start + length;i++){
        if(a[i] != b[i]) return 0;
    }
    return 1;
}




#endif
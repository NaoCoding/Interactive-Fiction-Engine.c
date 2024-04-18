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

char * strtok_withoutReplace(char * target , char token){
    int size = 0;
    while(*target && *target != token){
        size ++;
        target ++;
    }
    char * return_string = calloc(size,sizeof(char));
    int idx = 0;
    while(*(target-size) && size){
        return_string[idx] = *(target-size);
        size --;
        idx ++;
    }
    return return_string;
}

void writeInInt(int target, FILE * f){

    int val = 1;
    while(target>=val) val *= 10;
    val /= 10;

    if(val==0){
        char n = target + '0';
        fwrite(&n,1,1,f);
    }
    else{
        while(val){
            char n = target/val + '0';
            fwrite(&n,1,1,f);
            target %= val;
            val /= 10;
        }
    }

}




#endif
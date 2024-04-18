#ifndef UI_H
#define UI_H
#include "std.h"
#include "smallfn.h"

void html_setup(FILE * html);
void merge_js(FILE * fnjs,FILE * js);
int _CHAR_NameIDSearch(char * target);

typedef struct _CHAR_{
    char src[1025];
    char name[1025];
    int active;
}Character;

Character * npc;
int npc_size = 0;

void html_setup(FILE * html){

    fwrite("<!DOCTYPE html>\n",16,1,html);
    fwrite("<html>\n",7,1,html);

}

void merge_js(FILE * fnjs,FILE * js){
    char in[1025];
    while(fgets(in,1025,fnjs))fwrite(in,strlen(in),1,js);
    
}

int _CHAR_NameIDSearch(char * target){
    for(int i=0;i<1000;i++){
        if(!strcmp(npc[i].name,target)) return i;
    }
    return -1;
}

#endif
#ifndef GB_H_
#define GB_H_

#include "std.h"

//character
//html id : name + src_name
typedef struct GB_STRUCT_CHARACTER{
    char *src[50];
    char *src_name[50];
    char *moving_src[50];
    int src_count;
    char * name;

}GB_CHARACTER;
GB_CHARACTER * character;
int character_count = 0;

// objects
typedef struct GB_STRUCT_OBJECT{

    char id[1025];


}  GB_OBJECT;
GB_OBJECT * object;
int object_count = 0;

//paths
char file_folder[1025];


//input
char in[3000];

int scene = 0;
char charScene[100] = {0};

//files
FILE * html;
FILE * js;
FILE * fnjs;
FILE * script;

#endif
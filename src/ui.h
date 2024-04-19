#ifndef UI_H
#define UI_H
#include "std.h"
#include "smallfn.h"

void html_setup(FILE * html);
void merge_js(FILE * fnjs,FILE * js);
int _CHAR_NameIDSearch(char * target);
void animation_fadeIn_windowonload(char * target, FILE * html);
void ANICONFIG_initialize();

typedef struct _ANICONFIG
{
    int didfirst_fadein;
}ANICONFIG;


typedef struct _SPEAK__
{
    char src[1025];
    int x;
    int y;
    int xsize;
    int ysize;
    int srcactive;
}Div;


typedef struct _CHAR_{
    char src[1025];
    char name[1025];
    int active;
    char place[4][25];
}Character;

Character * npc;
ANICONFIG * ani_config;
Div * speakDiv;
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

void animation_fadeIn_windowonload(char * target, FILE * html){
    fwrite("<script type=\"text/javascript\">\n",32,1,html);
    fwrite("window.onload = fadeIn;\n",24,1,html);
    fwrite("function fadeIn() {\n",20,1,html);
    fwrite("var fade = document.getElementById(",35,1,html);
    fwrite(target,strlen(target),1,html);
    fwrite(");\n",3,1,html);
    fwrite("var opacity = 0;\n",17,1,html);
    fwrite("var intervalID = setInterval(function() {\n",42,1,html);
    fwrite("if (opacity < 1) {\n opacity = opacity + 0.05\n fade.style.opacity = opacity;\n",76,1,html);
    fwrite("} else {\n clearInterval(intervalID);\n }\n }, 105);\n }\n </script> \n",65,1,html);

    
}

void animation_fadeIn_click_change_scene(char * target, FILE * html){
    fwrite("var fade = document.getElementById(",35,1,html);
    fwrite(target,strlen(target),1,html);
    fwrite(");\n",3,1,html);
    fwrite("fade.style.display = \"block\";\n",30,1,html);
    fwrite("var opacity = 0;\n",17,1,html);
    fwrite("var intervalID = setInterval(function() {\n",42,1,html);
    fwrite("if (opacity < 1) {\n opacity = opacity + 0.05\n fade.style.opacity = opacity;\n",76,1,html);
    fwrite("} else {\n clearInterval(intervalID);\n }\n }, 105);\n \n",52,1,html);
}

void animation_fadeOut_click_change_scene(char * target, FILE * html){
    fwrite("var fade = document.getElementById(",35,1,html);
    //fwrite("fade.style.display = \"block\";\n",30,1,html);
    fwrite(target,strlen(target),1,html);
    fwrite(");\n",3,1,html);
    fwrite("var opacity = 1;\n",17,1,html);
    fwrite("var intervalID = setInterval(function() {\n",42,1,html);
    fwrite("if (opacity > 0) {\n opacity = opacity - 0.05\n fade.style.opacity = opacity;\n",76,1,html);
    fwrite("} else {\n clearInterval(intervalID);\n }\n }, 105);\n \n",52,1,html);
}

void ANICONFIG_initialize(){
    ani_config->didfirst_fadein = 0;
}

#endif
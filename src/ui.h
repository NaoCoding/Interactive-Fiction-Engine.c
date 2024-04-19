#ifndef UI_H
#define UI_H
#include "std.h"
#include "smallfn.h"

void html_setup(FILE * html);
void merge_js(FILE * fnjs,FILE * js);
int _CHAR_NameIDSearch(char * target);
void animation_fadeIn_windowonload(char * target, FILE * html);
void ANICONFIG_initialize();
void PLAYERCONFIG_initialize();
void ui_player_show(FILE *html);

typedef struct _SCRIPT_{
    char path[1025];
    char folder[1025];
    FILE *source;
}Script;

typedef struct _ANICONFIG
{
    int didfirst_fadein;
}ANICONFIG;

typedef struct _Player_{

    int movement_speed;
    int movement_multiply;
    int movement_xy[2];

    char movement_src[4][1025]; // left,right,up,sneak
    int movement_src_active[4];

    char normal_src[1025];
    int normal_src_active;

    char style_place[4][1025]; //left,top,width,height

    int active;


}_Player;


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

_Player *player;
Character * npc;
ANICONFIG * ani_config;
Div * speakDiv;
int npc_size = 0;

void ui_player_key_left(FILE * html){
    fwrite("PLAYERSTATUS = document.getElementById(\"UI_PLAYER_CONST\")\n",58,1,html);
    fwrite("if(parseInt(PLAYERSTATUS.style.left) >= ",39,1,html);
    writeInInt(player->movement_multiply * player->movement_speed,html);
    fwrite(")PLAYERSTATUS.style.left = (parseInt(PLAYERSTATUS.style.left) - ",64,1,html);
    //printf("%d %d",player->movement_speed,player->movement_multiply);
    writeInInt(player->movement_multiply * player->movement_speed,html);
    fwrite(").toString()+\"%\"",16,1,html);
    fwrite("\n",1,1,html);
    
}

void ui_player_key_right(FILE * html){
    fwrite("PLAYERSTATUS = document.getElementById(\"UI_PLAYER_CONST\")\n",58,1,html);
    fwrite("if(parseInt(PLAYERSTATUS.style.left) + ",39,1,html);
    writeInInt(player->movement_multiply * player->movement_speed,html);
    fwrite(" < 100",6,1,html);
    fwrite(")PLAYERSTATUS.style.left = (parseInt(PLAYERSTATUS.style.left) + ",64,1,html);
    //printf("%d %d",player->movement_speed,player->movement_multiply);
    writeInInt(player->movement_multiply * player->movement_speed,html);
    fwrite(").toString()+\"%\"",16,1,html);
    fwrite("\n",1,1,html);
}

void ui_player_img_normal(Script * target,FILE * html){

    fwrite("document.getElementById(\"UI_PLAYER_CONST\").src=\".",49,1,html);
    fwrite(target->folder,strlen(target->folder),1,html);
    fwrite(player->normal_src+1,strlen(player->normal_src)-1,1,html);
    fwrite("\n",1,1,html);
}

void ui_player_show(FILE *html){
    
    fwrite("document.getElementById(\"UI_PLAYER_CONST\").style.display=\"block\"\n",65,1,html);
    
}

void PLAYERCONFIG_initialize(){

    player->movement_multiply = 1;
    player->movement_speed = 1;
    for(int i=0;i<4;i++) player->movement_src_active[i] = 0;
    player->normal_src_active = 0;
    player->active = 0;
    player->movement_xy[0] = 0;
    player->movement_xy[1] = 0;

}

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
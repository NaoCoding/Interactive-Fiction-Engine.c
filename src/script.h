#ifndef SCRIPT_H
#define SCRIPT_H
#include "std.h"
#include "smallfn.h"
#include "ui.h"

typedef struct _SCRIPT_{
    char path[1025];
    char folder[1025];
    FILE *source;
}Script;

Script * Script_setup(char p[]);
void Script_freespace(Script * target);
int Script_start_general_check(Script * target);
void Script_read(Script * target, FILE * html , FILE * js);
void Script_read_general(Script * target, FILE * html,FILE * js);
void Script_read_scene(Script * target, FILE * html,FILE * js);
void checkPoundSign(char * in,Script * target, FILE * html,FILE * js);

static int didGeneral = 0;

void Script_read_scene(Script * target, FILE * html,FILE * js){  
    
    int didId = 0,didFirst = 0;
    char in[1025];
    char bg[1025] = {0};
    while(fgets(in,1025,target->source)){

        fgetsDelendl(in);
        if(in[0] == '#') break;
        if(string_compare(0,3,in,"id:")){
            fwrite("<div class=",11,1,html);
            didId = 1;
            int idx = 0;
            while(in[idx]!='\"')idx ++;
            while(in[idx]){
                fwrite(&in[idx],1,1,html);
                idx ++;
            }
            fwrite(" style=",7,1,html);
            
        }

        if(string_compare(0,10,in,"first:True") && didId){
            didFirst = 1;
            fwrite("\"display:block;\"",16,1,html);
        }

        if(string_compare(0,11,in,"background:") && didId){
            int idx = 11;
            while(in[idx]!='\"')idx ++;
            strcpy(bg,in+idx+1);
        }

    }
    
    if(!didFirst)fwrite("\"display:none;\"",15,1,html);
    fwrite(">",1,1,html);
    
    if(strlen(bg)){
        fwrite("<img src=\"",10,1,html);
        fwrite(target->folder,strlen(target->folder),1,html);
        fwrite(bg,strlen(bg),1,html); 
        fwrite(">",1,1,html);
    }
   

    fwrite("</div>\n",7,1,html);

    checkPoundSign(in,target,html,js);

}


void Script_read_general(Script * target, FILE * html,FILE * js){
    didGeneral = 1;
    fwrite("<head>\n",7,1,html);
    fwrite("<meta charset=\"utf-8\">\n",23,1,html);
    
    char in[1025];
    while(fgets(in,1025,target->source)){

        fgetsDelendl(in);
        if(in[0] == '#') break;
        if(string_compare(0,6,in,"title:")){
            fwrite("<title>",7,1,html);
            int idx = 0;
            while(in[idx]!='\"')idx ++;
            idx ++;
            while(in[idx]!='\"'){
                fwrite(&in[idx],1,1,html);
                idx ++;
            }
            fwrite("</title>\n",9,1,html);
        }


    }
    fwrite("</head>\n<body>\n",15,1,html);

    checkPoundSign(in,target,html,js);

}

void checkPoundSign(char * in,Script * target, FILE * html,FILE * js){
    if(!strcmp(in,"#general"))Script_read_general(target,html,js);
    if(!strcmp(in,"#scene"))Script_read_scene(target,html,js);
}


Script * Script_setup(char p[]){
    Script * target = calloc(1,sizeof(Script));
    strcpy(target->path,p);
    strcat(target->path,"script.yaml");
    target->source = fopen(target->path,"r");
    return target;
}

void Script_freespace(Script * target){
    fclose(target->source);
    free(target);
}

int Script_start_general_check(Script * target){
    char in[1025];
    fgets(in,1025,target->source);
    fgetsDelendl(in);

    return strcmp(in,"#script");
}

void Script_read(Script * target, FILE * html , FILE * js){

    char in[1025];
    html_setup(html);
    while(fgets(in,1025,target->source)){
        fgetsDelendl(in);
        checkPoundSign(in,target,html,js);
    
    }

}




#endif
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
void Script_read(Script * target, FILE * html , FILE * js,FILE * fnjs);
void Script_read_general(Script * target, FILE * html,FILE * js,FILE * fnjs);
void Script_read_scene(Script * target, FILE * html,FILE * js,FILE * fnjs);
void Script_read_character(Script * target, FILE * html,FILE * js,FILE * fnjs);
void checkPoundSign(char * in,Script * target, FILE * html,FILE * js,FILE * fnjs);

static int didGeneral = 0;

void Script_read_scene(Script * target, FILE * html,FILE * js,FILE * fnjs){  
    
    int didId = 0,didFirst = 0;
    char in[1025];
    char id[1025] = {0};
    char onclick[1025] = {0};
    char bg[1025] = {0};
    int characters[1000][3];
    int characters_atScene = 0;
    for(int i=0;i<1000;i++) characters[i][0] = -1;

    while(fgets(in,1025,target->source)){

        fgetsDelendl(in);
        if(in[0] == '#') break;
        if(string_compare(0,3,in,"id:")){
            fwrite("<div id=",8,1,html);
            didId = 1;
            int idx = 0;
            
            while(in[idx]!='\"')idx ++;
            strcpy(id,in+idx);
            while(in[idx]){
                fwrite(&in[idx],1,1,html);
                idx ++;
            }
            fwrite(" style=",7,1,html);
            
        }

        if(string_compare(0,10,in,"first:True") && didId){
            didFirst = 1;
            fwrite("\"display:block;",15,1,html);
        }

        if(string_compare(0,11,in,"background:") && didId){
            int idx = 11;
            while(in[idx]!='\"')idx ++;
            strcpy(bg,in+idx+1);
        }

        if(string_compare(0,19,in,"click.change_scene:") && didId){
            int idx = 19;
            while(in[idx]!='\"')idx ++;
            strcpy(onclick,in+idx+1);
        }

        if(string_compare(0,15,in,"character.show:") && didId){

            int idx = 15;
            //printf("DEBUG_MESSAGE");

            if(in[idx] == '\"'){

                char * name = strtok_withoutReplace(in+idx,',');
                characters[characters_atScene][0] = _CHAR_NameIDSearch(name);
                idx += strlen(name);

            }
            else{
                characters[characters_atScene][0] = 0;
                while(isdigit(in[idx])){
                    characters[characters_atScene][0] *= 10;
                    characters[characters_atScene][0] += in[idx] - '0';
                    idx ++;
                }
                
                
            }

            //printf("DEBUG_MESSAGE");
            idx ++;
            
            
            if(isdigit(in[idx])){

                characters[characters_atScene][1] = 0;
                characters[characters_atScene][2] = 0;
                while(isdigit(in[idx])){
                    characters[characters_atScene][1] *= 10;
                    characters[characters_atScene][1] += in[idx] - '0';
                    idx ++;
                }

                idx += 1;

                while(isdigit(in[idx])){
                    characters[characters_atScene][2] *= 10;
                    characters[characters_atScene][2] += in[idx] - '0';
                    idx ++;
                }
                
            }
            

            //debug
            //for(int i=0;i<3;i++)printf("%d ",characters[characters_atScene][i]);
        
            characters_atScene ++;
        }

    }

    if(!didFirst)fwrite("\"display:none;",14,1,html);
    
    fwrite("position:absolute;width:100%;height:100%;top:0px;left:0px;",58,1,html);

    fwrite("\"",1,1,html);

    if(strlen(onclick)){
        fwrite("onclick = ",10,1,html);
        fwrite(id+1,strlen(id)-2,1,html);
        fwrite(onclick,strlen(onclick)-1,1,html);
        fwrite("()",2,1,html);
        fwrite("function ",9,1,fnjs);
        fwrite(id+1,strlen(id)-2,1,fnjs);
        fwrite(onclick,strlen(onclick)-1,1,fnjs);
        fwrite("(){\n",4,1,fnjs);
        fwrite("document.getElementById(",24,1,fnjs);
        fwrite(id,strlen(id),1,fnjs);
        fwrite(").style.display = \"none\";\n",26,1,fnjs);
        fwrite("document.getElementById(\"",25,1,fnjs);
        fwrite(onclick,strlen(onclick),1,fnjs);
        fwrite(").style.display = \"block\"\n;",27,1,fnjs);

        fwrite("}\n",2,1,fnjs);
    }


    fwrite(">",1,1,html);
    fwrite("\n",1,1,html);
    if(strlen(bg)){
        fwrite("<img src=\".",11,1,html);
        fwrite(target->folder,strlen(target->folder),1,html);
        fwrite(bg,strlen(bg),1,html); 
        fwrite("style=\"position:absolute;height:100%;width:100%;top:0px;left:0px;\">",67,1,html);
    }
    fwrite("\n",1,1,html);

    for(int i=0;i<characters_atScene;i++){
        fwrite("<img src=\".",11,1,html);
        fwrite(target->folder,strlen(target->folder),1,html);
        printf("%s",npc[characters[i][0]].src);
        fwrite(npc[characters[i][0]].src+1,strlen(npc[characters[i][0]].src)-1,1,html);
        fwrite("style=\"position:absolute;left:",30,1,html);
        writeInInt(characters[i][1],html);
        fwrite("px;top:",7,1,html);
        writeInInt(characters[i][2],html);
        fwrite("px;\"",4,1,html);
        fwrite(">\n",2,1,html);
    }
   

    fwrite("</div>\n",7,1,html);

    checkPoundSign(in,target,html,js,fnjs);

}

void Script_read_character(Script * target, FILE * html,FILE * js,FILE * fnjs){

    char in[1025];
    int npcidx = -1;
    while(fgets(in,1025,target->source)){

        fgetsDelendl(in);
        if(in[0] == '#') break;
        if(string_compare(0,3,in,"id:")){
            int idx = 3;
            npcidx = 0;
            while(isdigit(in[idx])){
                npcidx = npcidx * 10 + in[idx] - '0';
                idx ++;
            }
            npc[npcidx].active = 1;
            
        }

        if(string_compare(0,5,in,"name:") && npcidx != -1){
            strcpy(npc[npcidx].name,in+5);
        }

        if(string_compare(0,4,in,"img:") && npcidx != -1){
            strcpy(npc[npcidx].src,in+4);
        }



    }

    checkPoundSign(in,target,html,js,fnjs);


}


void Script_read_general(Script * target, FILE * html,FILE * js,FILE * fnjs){
    didGeneral = 1;
    fwrite("<head>\n",7,1,html);
    fwrite("<script src=\"output.js\"></script>",33,1,html);
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

        if(string_compare(0,15,in,"characterCount:")){
            int idx = 15;
            while(isdigit(in[idx])){
                npc_size = npc_size * 10 + in[idx] - '0';
                idx ++;
            }
           
        }


    }
    fwrite("</head>\n<body>\n",15,1,html);

    checkPoundSign(in,target,html,js,fnjs);

}

void checkPoundSign(char * in,Script * target, FILE * html,FILE * js,FILE * fnjs){
    if(!strcmp(in,"#general"))Script_read_general(target,html,js,fnjs);
    else if(!strcmp(in,"#scene"))Script_read_scene(target,html,js,fnjs);
    else if(!strcmp(in,"#character"))Script_read_character(target,html,js,fnjs);

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

void Script_read(Script * target, FILE * html , FILE * js,FILE * fnjs){

    char in[1025];
    html_setup(html);
    while(fgets(in,1025,target->source)){
        fgetsDelendl(in);
        checkPoundSign(in,target,html,js,fnjs);
    
    }

}




#endif
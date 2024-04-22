#ifndef SCRIPT_H_
#define SCRIPT_H_

#include "std.h"
#include "GLOBALVARIABLE.h"
#include "PROCESS.h"
#include "SMALLFUNCTION.h"

void SCRIPT_read();
void SCRIPT_readDot(char * para);
void SCRIPT_window_title();
void SCRIPT_showCharacterImage(int character_index, int src_index);
void SCRIPT_hideCharacterImage(int character_index, int src_index);
void SCRIPT_modifyCharacterStyle(int character_index, int src_index, char * attr, char * content);

void SCRIPT_read(){

    
    
    while(fgets(in,3000,script)){

        FN_fgetsDelEndl();
        printf("%s\n",in);


        if(strlen(in))SCRIPT_readDot(in);

    }

}

void SCRIPT_readDot(char * n){

    char **para = FN_splitDot(n);
    
    if(!strcmp(para[0],"//")) return;

    else if(!strcmp(para[0],"window")){
        if(!strcmp(para[1],"title"))SCRIPT_window_title(para[2]);
    }

    else if(!strcmp(para[0],"character")){
        
        if(!strcmp(para[1],"count"))character = calloc(atoi(para[2]),sizeof(GB_CHARACTER));

        else if(!strcmp(para[1],"create")){
            character[character_count].name = calloc(strlen(para[2]),sizeof(char));
            strcpy(character[character_count++].name,para[2]);
        }
        

        else{ //para[1] = character.name
            for(int i=0;i<character_count;i++){
                if(!strcmp(para[1],character[i].name)){
                    if(!strcmp(para[2],"src")){
                        int src_count = character[i].src_count ++;
                        character[i].src_name[src_count] = calloc(strlen(para[3]) + 1,sizeof(char));
                        character[i].src[src_count] = calloc(strlen(para[4]) ,sizeof(char));
                        strcpy(character[i].src_name[src_count],para[3]);
                        strcpy(character[i].src[src_count],para[4]);
                        
                        PROCESS_characterSrcHTMLWriteIn(i , src_count);
                    }

                    if(!strcmp(para[2],"show")){
                        int idx = FN_nameToIdx(i,para[3]);
                        SCRIPT_showCharacterImage(i,idx);
                    }

                     if(!strcmp(para[2],"hide")){
                        int idx = FN_nameToIdx(i,para[3]);
                        SCRIPT_hideCharacterImage(i,idx);
                    }
                    if(!strcmp(para[2],"style")){
                        int idx = FN_nameToIdx(i,para[3]);
                        SCRIPT_modifyCharacterStyle(i,idx,para[4],para[5]);
                    }
                }
            }
        }
    }

    else if(!strcmp(para[0],"dialogBox")){

        if(!strcmp(para[1],"show"))PROCESS_showElement("DIALOG_BOX");
        else if(!strcmp(para[1],"hide"))PROCESS_hideElement("DIALOG_BOX");

        else if(!strcmp(para[1],"background"))PROCESS_modifySrcElement("DIALOG_BOX_BG",para[2]);

    }



    free(para);
   
}

void SCRIPT_window_title(char * target){
    fwrite("document.getElementById(\"HTML_TITLE\").innerHTML = ",50,1,fnjs);
    fwrite(target,strlen(target),1,fnjs);
    fwrite("\n",1,1,fnjs);
}

void SCRIPT_showCharacterImage(int character_index, int src_index){

    char * target = FN_mergeString(character[character_index].name,character[character_index].src_name[src_index]);

    fwrite("document.getElementById(\"",25,1,fnjs);
    fwrite(target,strlen(target),1,fnjs);
    fwrite("\").style.display=\"block\"\n",25,1,fnjs);


    free(target);

}

void SCRIPT_hideCharacterImage(int character_index, int src_index){

    char * target = FN_mergeString(character[character_index].name,character[character_index].src_name[src_index]);

    fwrite("document.getElementById(\"",25,1,fnjs);
    fwrite(target,strlen(target),1,fnjs);
    fwrite("\").style.display=\"none\"\n",24,1,fnjs);


    free(target);

}

void SCRIPT_modifyCharacterStyle(int character_index, int src_index, char * attr, char * content){

    char * target = FN_mergeString(character[character_index].name,character[character_index].src_name[src_index]);
    fwrite("document.getElementById(\"",25,1,fnjs);
    fwrite(target,strlen(target),1,fnjs);
    fwrite("\").style.",9,1,fnjs);
    fwrite(attr,strlen(attr),1,fnjs);
    fwrite("=",1,1,fnjs);
    fwrite(content,strlen(content),1,fnjs);
    fwrite("\n",1,1,fnjs);


    free(target);

}

#endif
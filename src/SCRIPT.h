#ifndef SCRIPT_H_
#define SCRIPT_H_

#include "std.h"
#include "GLOBALVARIABLE.h"
#include "PROCESS.h"
#include "SMALLFUNCTION.h"

void SCRIPT_read();
void SCRIPT_readDot(char * para);
void SCRIPT_window_title();

void SCRIPT_read(){

    
    
    while(fgets(in,3000,script)){

        FN_fgetsDelEndl();
        printf("%s\n",in);


        if(strlen(in))SCRIPT_readDot(in);

    }

}

void SCRIPT_readDot(char * n){

    char **para = FN_splitDot(n);
    
    if(!strcmp(para[0],"window")){
        if(!strcmp(para[1],"title"))SCRIPT_window_title(para[2]);
    }

    else if(!strcmp(para[0],"character")){
        
        if(!strcmp(para[1],"count"))character = calloc(atoi(para[2]),sizeof(GB_CHARACTER));
        else if(!strcmp(para[1],"create")){
            character[character_count].name = calloc(strlen(para[2]),sizeof(char));
            strcpy(character[character_count++].name,para[2]);
        }
        

        else{
            for(int i=0;i<character_count;i++){
                if(!strcmp(para[1],character[i].name)){
                    if(!strcmp(para[2],"src")){
                        int src_count = character[i].src_count ++;
                        character[i].src_name[src_count] = calloc(strlen(para[4]),sizeof(char));
                        character[i].src[src_count] = calloc(strlen(para[3]),sizeof(char));
                        strcpy(character[i].src_name[src_count],para[4]);
                        strcpy(character[i].src_name[src_count],para[3]);
                    }

                    if(!strcmp(para[2],"show")){
                        int idx = FN_nameToIdx(i,para[3]);
                        
                    }
                }
            }
        }
    }
    free(para);
   
}

void SCRIPT_window_title(char * target){
    fwrite("document.getElementById(\"HTML_TITLE\").innerHTML = ",50,1,fnjs);
    fwrite(target,strlen(target),1,fnjs);
    fwrite("\n",1,1,html);
}

#endif
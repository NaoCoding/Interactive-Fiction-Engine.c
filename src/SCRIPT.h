#ifndef SCRIPT_H_
#define SCRIPT_H_

#include "std.h"
#include "SMALLFUNCTION.h"
#include "GLOBALVARIABLE.h"
#include "PROCESS.h"

void SCRIPT_READ();
void SCRIPT_ANALYZE();
void SCRIPT_window_title();
void SCRIPT_showCharacterImage(int character_index, int src_index);
void SCRIPT_hideCharacterImage(int character_index, int src_index);
void SCRIPT_modifyCharacterStyle(int character_index, int src_index, char * attr, char * content);

void SCRIPT_ANALYZE(){

    char **para = FN_splitDot(in);

    if(!strcmp(para[0],"object")){
        if(!strcmp(para[1],"create")){
            PROCESS_createObject(FN_mergeString("OBJECT_",para[2]));
        }
        else if(!strcmp(para[1],"place")){
            PROCESS_modifyStyleElement(FN_mergeString("OBJECT_",para[2]),"width",para[3]);
            PROCESS_modifyStyleElement(FN_mergeString("OBJECT_",para[2]),"height",para[4]);
            PROCESS_modifyStyleElement(FN_mergeString("OBJECT_",para[2]),"left",para[5]);
            PROCESS_modifyStyleElement(FN_mergeString("OBJECT_",para[2]),"top",para[6]);
        }
        else if(!strcmp(para[1],"style")){
            PROCESS_modifyStyleElement(FN_mergeString("OBJECT_",para[2]),para[3],para[4]);
        }
        else if(!strcmp(para[1],"show")){
            PROCESS_showElement(FN_mergeString("OBJECT_",para[2]));
        }
        else if(!strcmp(para[1],"hide")){
            PROCESS_hideElement(FN_mergeString("OBJECT_",para[2]));
        }
        else if(!strcmp(para[1],"src")){
            PROCESS_modifySrcElement(FN_mergeString("OBJECT_",para[2]),para[3]);
        }
        else if(!strcmp(para[1],"click")){
            if(!strcmp(para[2],"subscene_open")){
                PROCESS_onClickElement(FN_mergeString("OBJECT_",para[3]),para[4]);
            }
        }
    }

    else if(!strcmp(para[0],"background"))PROCESS_modifySrcElement("BACKGROUND",para[1]);
    else if(!strcmp(para[0],"subscenebackground"))PROCESS_modifySrcElement("HTML_SUB",para[1]);


    else if(!strcmp(para[0],"window")){
        if(!strcmp(para[1],"title"))SCRIPT_window_title(para[2]);
    }

    else if(!strcmp(para[0],"character")){
        
        if(!strcmp(para[1],"count"))character = calloc(atoi(para[2]),sizeof(GB_CHARACTER));

        else if(!strcmp(para[1],"create")){
            character[character_count].name = calloc(strlen(para[2]),sizeof(char));
            strcpy(character[character_count++].name,para[2]);
            PROCESS_characterMovingHTMLWriteIn(character[character_count-1].name);
        }
        

        else{ //para[1] = character.name
            for(int i=0;i<character_count;i++){
                if(!strcmp(para[1],character[i].name)){
                    if(!strcmp(para[2],"src")){
                        int src_count = character[i].src_count ++;
                        character[i].src_name[src_count] = calloc(strlen(para[3]) + 1,sizeof(char));
                        character[i].src[src_count] = calloc(strlen(para[4]) + 1,sizeof(char));
                        strcpy(character[i].src_name[src_count],para[3]);
                        strcpy(character[i].src[src_count],para[4]);
                        
                        PROCESS_characterSrcHTMLWriteIn(i , src_count);
                    }

                    else if(!strcmp(para[2],"control")){
                        if(!strcmp(para[3],"start")){
                            PROCESS_showElement(FN_mergeString(character[i].name,"MOVINGIMG"));
                            fwrite("control = \"",11,1,fnjs);
                            fwrite(FN_mergeString(character[i].name,"MOVINGIMG"),strlen(FN_mergeString(character[i].name,"MOVINGIMG")),1,fnjs);
                            fwrite("\"\n",2,1,fnjs);
                        }
                        else if(!strcmp(para[3],"stop")){
                            PROCESS_hideElement(FN_mergeString(character[i].name,"MOVINGIMG"));
                            fwrite("control = \"\"\n",13,1,fnjs);
                        }

                        else if(!strcmp(para[3],"movingAnimation")){
                            fwrite("control_movingAnimation = ",26,1,fnjs);
                            PROCESS_writeInFN_str2ARR(i,atoi(para[4]),atoi(para[5]));
                        }

                        else if(!strcmp(para[3],"standingAnimation")){
                            fwrite("control_standingAnimation = ",28,1,fnjs);
                            PROCESS_writeInFN_str2ARR(i,atoi(para[4]),atoi(para[5]));
                        }
                        else if(!strcmp(para[3],"jumpingAnimation")){
                            //printf("%d",atoi(para[4]));
                            fwrite("control_jumpingAnimation = ",27,1,fnjs);
                            PROCESS_writeInFN_str2ARR(i,atoi(para[4]),atoi(para[4]));
                            fwrite("\n",1,1,fnjs);
                        }

                    }

                    else if(!strcmp(para[2],"show")){
                        int idx = FN_nameToIdx(i,para[3]);
                        SCRIPT_showCharacterImage(i,idx);
                    }

                    else if(!strcmp(para[2],"hide")){
                        int idx = FN_nameToIdx(i,para[3]);
                        SCRIPT_hideCharacterImage(i,idx);
                    }
                    else if(!strcmp(para[2],"style")){
                        int idx = FN_nameToIdx(i,para[3]);
                        SCRIPT_modifyCharacterStyle(i,idx,para[4],para[5]);
                    }
                    else if(!strcmp(para[2],"place")){
                        int idx = FN_nameToIdx(i,para[3]);
                        char * elementid = FN_mergeString(character[i].name,character[i].src_name[idx]);
                        PROCESS_modifyStyleElement(elementid,"width",para[4]);
                        PROCESS_modifyStyleElement(elementid,"height",para[5]);
                        PROCESS_modifyStyleElement(elementid,"left",para[6]);
                        PROCESS_modifyStyleElement(elementid,"top",para[7]);
                        free(elementid);
                    }

                    else if(!strcmp(para[2],"moving")){
                        character[i].moving_src[atoi(para[3])-1] = calloc(strlen(para[4])+1,sizeof(char));
                        strcpy(character[i].moving_src[atoi(para[3])-1],para[4]);
                    }

                    else if(!strcmp(para[2],"moving_place")){
                        char * fq = FN_mergeString(character[i].name,"MOVINGIMG");
                        PROCESS_modifyStyleElement(fq,"width",para[3]);
                        PROCESS_modifyStyleElement(fq,"height",para[4]);
                        PROCESS_modifyStyleElement(fq,"left",para[5]);
                        PROCESS_modifyStyleElement(fq,"top",para[6]);
                        free(fq);
                    }
                    
                    else if(!strcmp(para[2],"moving_src")){
                        PROCESS_modifySrcElement(FN_mergeString(character[i].name,"MOVINGIMG"),para[3]);
                    }

                    else if(!strcmp(para[2],"moveAnimation")){
                        int qq = atoi(para[3]);
                        int qqlast = atoi(para[4]);
                        //printf("%d %d",qq,qqlast);
                        PROCESS_showElement(FN_mergeString(character[i].name,"MOVINGIMG"));
                        PROCESS_characterMovingAnimation(FN_mergeString(character[i].name,"MOVINGIMG"),qq,qqlast,200,FN_arr2String(i,qq,qqlast),9);

                    }

                    else if(!strcmp(para[2],"moving_style"))PROCESS_modifyStyleElement(FN_mergeString(character[i].name,"MOVINGIMG"),para[3],para[4]);
                
                    else if(!strcmp(para[2],"moving_show"))PROCESS_showElement(FN_mergeString(character[i].name,"MOVINGIMG"));
                    else if(!strcmp(para[2],"moving_hide"))PROCESS_hideElement(FN_mergeString(character[i].name,"MOVINGIMG"));
                }
            }
        }
    }

    else if(!strcmp(para[0],"first_scene")){
        fwrite("scene_send(",11,1,fnjs);
        fwrite(para[1],strlen(para[1]),1,fnjs);
        fwrite(")\n",2,1,fnjs);
    }

    else if(!strcmp(para[0],"scene")){
        fclose(html);
        fclose(fnjs);
        html = fopen(FN_mergeString("./output/scene",FN_mergeString(para[1],".html")),"w+");
        fnjs = fopen(FN_mergeString("./output/scene",FN_mergeString(para[1],".js")),"w+");
    }

    else if(!strcmp(para[0],"subscene")){
        fclose(html);
        fclose(fnjs);
        html = fopen(FN_mergeString("./output/subscene",FN_mergeString(para[1],".html")),"w+");
        fnjs = fopen(FN_mergeString("./output/subscene",FN_mergeString(para[1],".js")),"w+");
    }


    else if(!strcmp(para[0],"change_scene")){

        if(!strcmp(para[1],"character")){
            if(!strcmp(para[2],"right")){
                fwrite("change_sceneTargetFn[1] = \"",27,1,fnjs);
                fwrite(para[3],strlen(para[3]),1,fnjs);
                fwrite("\"\nchange_scenePlace[1] = 1\n",27,1,fnjs);
            }
        }

    }

    else if(!strcmp(para[0],"dialogBox")){

        if(!strcmp(para[1],"show"))PROCESS_showElement("DIALOG_BOX");
        else if(!strcmp(para[1],"hide"))PROCESS_hideElement("DIALOG_BOX");

        else if(!strcmp(para[1],"background")){
            if(!strcmp(para[2],"src"))PROCESS_modifySrcElement("DIALOG_BOX_BG",para[3]);
            else if(!strcmp(para[2],"style"))PROCESS_modifyStyleElement("DIALOG_BOX_BG",para[3],para[4]);

            else if(!strcmp(para[2],"place")){
                PROCESS_modifyStyleElement("DIALOG_BOX_BG","width",para[3]);
                PROCESS_modifyStyleElement("DIALOG_BOX_BG","height",para[4]);
                PROCESS_modifyStyleElement("DIALOG_BOX_BG","left",para[5]);
                PROCESS_modifyStyleElement("DIALOG_BOX_BG","top",para[6]);
            }
        
        }
        
        else if(!strcmp(para[1],"style"))PROCESS_modifyStyleElement("DIALOG_BOX",para[2],para[3]);
        else if(!strcmp(para[1],"place")){
            PROCESS_modifyStyleElement("DIALOG_BOX","width",para[2]);
            PROCESS_modifyStyleElement("DIALOG_BOX","height",para[3]);
            PROCESS_modifyStyleElement("DIALOG_BOX","left",para[4]);
            PROCESS_modifyStyleElement("DIALOG_BOX","top",para[5]);
        }

        else if(!strcmp(para[1],"speaker")){
            if(!strcmp(para[2],"place")){
                PROCESS_modifyStyleElement("DIALOG_BOX_SPEAKER","width",para[3]);
                PROCESS_modifyStyleElement("DIALOG_BOX_SPEAKER","height",para[4]);
                PROCESS_modifyStyleElement("DIALOG_BOX_SPEAKER","left",para[5]);
                PROCESS_modifyStyleElement("DIALOG_BOX_SPEAKER","top",para[6]);
            }

            else if(!strcmp(para[2],"set"))PROCESS_modifyInnerHTMLElement("DIALOG_BOX_SPEAKER",para[3]);
            else if(!strcmp(para[2],"style"))PROCESS_modifyStyleElement("DIALOG_BOX_SPEAKER",para[3],para[4]);
        
        }

        else if(!strcmp(para[1],"content")){
            if(!strcmp(para[2],"place")){
                PROCESS_modifyStyleElement("DIALOG_BOX_CONTENT","width",para[3]);
                PROCESS_modifyStyleElement("DIALOG_BOX_CONTENT","height",para[4]);
                PROCESS_modifyStyleElement("DIALOG_BOX_CONTENT","left",para[5]);
                PROCESS_modifyStyleElement("DIALOG_BOX_CONTENT","top",para[6]);
            }

            else if(!strcmp(para[2],"set")){
                char **sln = FN_splitDotWithoutComma(in);
                PROCESS_contentAppearAnimation("DIALOG_BOX_CONTENT",sln[3],30);
            }
            else if(!strcmp(para[2],"style"))PROCESS_modifyStyleElement("DIALOG_BOX_CONTENT",para[3],para[4]);
        
        }
        else if(!strcmp(para[1],"click")){
            if(!strcmp(para[2],"subscene_open")){
                PROCESS_onClickElement("DIALOG_BOX",para[3]);
            }
            else if(!strcmp(para[2],"subscene_close")){
                PROCESS_onClickCloseElement("DIALOG_BOX");
            }
        }

    }



    free(para);
   


}


void SCRIPT_READ(){

    while(fgets(in,1025,script)){

        FN_fgetsDelEndl(in);
        //printf("%s\n",in);
        if(strlen(in)) SCRIPT_ANALYZE();

    }

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
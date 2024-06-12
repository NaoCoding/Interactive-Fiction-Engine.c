#ifndef SCRIPT_H_
#define SCRIPT_H_

#include "std.h"
//std.h is for all the neccessary include file to make this work
//in order to make the engine work and be compiled successfully, include std.h is neccessary.

#include "SMALLFUNCTION.h"
// some small functions, functions from FN
// Generally, those functions in FN are usually useful and being the core of the engine.
// such as some small functions to parse the script

#include "GLOBALVARIABLE.h"
// store global variable and structures
// characters, objects, storing all needs structure for script.

#include "PROCESS.h"
// process all command parsed from SCRIPT.h
// most of the fwrite command and the parsing command are written in PROCESS.h

void SCRIPT_READ();
// parse script.yaml and transfer to lots of html and js.
// "not" the core system of the engine
// all it do is pre-parse and transfer the parameters to SCRIPT_ANALYZE()
// the core function is SCRIPT_ANALYZE()


void SCRIPT_ANALYZE();
// parse script.yaml and transfer to lots of html and js.
// the real core function of the engine
// to check or modify the engine, most of the time just check this function
// to add functions or to change format, check this functions either.


void SCRIPT_window_title();
// setup the window title of your game/script
// just fwrite the window title into your html/js

void SCRIPT_showCharacterImage(int character_index, int src_index);
// show the character image(not animation)
// must defined the character and make sure the character have the src
// if not following the rule, segmentation fault may appear since it cannot find the target.


void SCRIPT_hideCharacterImage(int character_index, int src_index);
// hide the character image(not animation)
// must defined the character and make sure the character have the src
// if not following the rule, segmentation fault may appear since it cannot find the target.

void SCRIPT_modifyCharacterStyle(int character_index, int src_index, char * attr, char * content);
// to modify specific image CSS style.
// must defined the character and make sure the character have the src
// if not following the rule, segmentation fault may appear since it cannot find the target.

void SCRIPT_ANALYZE(){

    char **para = FN_splitDot(in);
    // parse the yaml format to Array
    // it support parsing : / . / "," / ,
    // the comma (,) writing inside "" may count as a character, will not be parse to different element
    // FN_splitDot() is an important function, which parse all the commands in script.yaml into arrays
    // without this function, the whole system will not work
    // the paramenter (in) is a string for each line fgets the script.yaml
    // char * in should be parsed by deleting the last element if it is \n

    
    if(!strcmp(para[0],"audio")){
        //audio is the element to control all the audio input in script.yaml
        //the usage is to initialize first(add) , and play and stop after you have initialize the music.
        //if there is no stop command in script, the audio played will be looped.
        //the typing sound of the dialogBox is setup at src/audio, not setup by the "audio" relative commands
        //therefore, to disable the typing sound of the dialogBox, check the animaition.js


        if(!strcmp(para[1],"add")){
            //to setup a new audio.
            //it will create a variable AUDIO_[name]
            //for controling the music
            //require two parameter, [name] and [src]

            PROCESS_initialAudio(FN_mergeString("AUDIO_",para[2]) , para[3]);

        }
        else if(!strcmp(para[1],"play")){
            //to start playing the audio file.
            //however, normally the audio file will not stop and you should setup the stop command
            //in some place of the script.yaml if you want to stop the audio.


            PROCESS_playAudio(FN_mergeString("AUDIO_",para[2]));
        }

        else if(!strcmp(para[1],"stop")){
            //to pause an audio file and set its currentTime to 0.
            //if you don't want the engine to set it back to 0,
            //check the PROCESS_stopAudio and modify the engine.

            PROCESS_stopAudio(FN_mergeString("AUDIO_",para[2]));
        }

    }


    else if(!strcmp(para[0],"status")){
        //status is the element to control the status label(E)
        //the default setting of status is enable and without any speicific elements.
        //status label includes inventory, character's status, and character's photos.

        if(!strcmp(para[1],"photo")){
            PROCESS_modifySrcElement("STATUS_CHARACTER_IMAGE",para[2]);
        }
        //setup the photo of the status panel.
        //fwrite one line command to fnjs, change the src.


        else if(!strcmp(para[1],"name")){
            PROCESS_modifyInnerHTMLElement("STATUS_CHARACTER_NAME",para[2]);
        }
        //setup the name of the status panel
        //fwrite one line command to fnjs, change the innerHTML
        
        else if(!strcmp(para[1],"value")){
            //the value of status means to create a progress bar and 
            //you can change its value in script.yaml
            //such as when you go to specific subscene or options.
            //you can also modify the status value easily.


            if(!strcmp(para[2],"new")){
                PROCESS_statusNewValue(para[3]);
            }
            //to define a new status value.
            //you must define first in order to set or add the value
            //the default value will be 0 
            //the range of status value should between 0~100


            else if(!strcmp(para[2],"set")){
                PROCESS_setStatusValue(para[3],para[4]);
            }
            else if(!strcmp(para[2],"add")){
                PROCESS_addStatusValue(para[3],para[4]);
            }
        }

        else if(!strcmp(para[1],"inventory")){

        }

    }

    else if(!strcmp(para[0],"object")){
        //objects is an important part of engine 
        //items / doors / buttons(not options) /diary
        //anything except characters you want to display at screen
        //anything except characters you want to be able to click at screen

        if(!strcmp(para[1],"create")){
            PROCESS_createObject(FN_mergeString("OBJECT_",para[2]));
        }
        // create a new object named [name]
        // must be called before other commands relative to object
        // as you can see, the objects created will create html ID with OBJECT_ prefix
        // this is to make sure it will not be conflicted to other html ID set from user


        else if(!strcmp(para[1],"place")){
            PROCESS_modifyStyleElement(FN_mergeString("OBJECT_",para[2]),"width",para[3]);
            PROCESS_modifyStyleElement(FN_mergeString("OBJECT_",para[2]),"height",para[4]);
            PROCESS_modifyStyleElement(FN_mergeString("OBJECT_",para[2]),"left",para[5]);
            PROCESS_modifyStyleElement(FN_mergeString("OBJECT_",para[2]),"top",para[6]);
        }
        // to modify the object's width/height/left/top CSS style
        // this commands is just for convinients in order to less using style
        // support different types of value, such as 190% , px , rem .
        

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
            else if(!strcmp(para[2],"scene_open")){
                PROCESS_onClickScene(FN_mergeString("OBJECT_",para[3]),para[4]);
            }
        }
    }


    else if(!strcmp(para[0],"background"))PROCESS_modifySrcElement("BACKGROUND",para[1]);
    //to setup the background of the game/script
    //to modify the src of BACKGROUND this element in html
    //not neccessary if you don't want to have a background

    else if(!strcmp(para[0],"subscenebackground"))PROCESS_modifySrcElement("HTML_SUB",para[1]);
    //already discard after engine version 0.0.3
    //still can use, but our example-game discard this kind of commands
    //this will modify the HTML_SUB elements
    //which was used for subscene's background.

    else if(!strcmp(para[0],"animation")){
        if(!strcmp(para[1],"fadeIn")){
            PROCESS_writeInFadeIn();
        }
    }
    //to make the scene have animation.
    //the animation source code is written in animation.js
    //there are some other animaion such as walking and moving animation for character,
    //if interested in, check the character command below.


    else if(!strcmp(para[0],"window")){
        if(!strcmp(para[1],"title"))SCRIPT_window_title(para[2]);
    }
    //to setup the title of the html window.

    else if(!strcmp(para[0],"character")){
        //character is the most important element of the engine
        //those CG, character moving animations, some other image for character while talking...
        //character has a structure defined at GLOBALVARAIBLE.h
        //careful to use, may segmentation fault with bad use method.

        
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

                    if(!strcmp(para[2],"subscene_open")){
                        PROCESS_onClickElement(FN_mergeString(character[i].name,"MOVINGIMG"),para[3]);
                    }
                    else if(!strcmp(para[2],"subscene_close")){
                        PROCESS_onClickCloseElement(FN_mergeString(character[i].name,"MOVINGIMG"),para[3]);
                    }

                    else if(!strcmp(para[2],"moving_place")){
                         // recommend % for character since the moving animation is depend on its percentage


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
    else if(!strcmp(para[0],"option")){
        if(!strcmp(para[1],"show")){
            PROCESS_showElement(FN_mergeString("OPTIONBOX",para[2]));
        }
        else if(!strcmp(para[1],"hide")){
            PROCESS_hideElement(FN_mergeString("OPTIONBOX",para[2]));
        }
        else if(!strcmp(para[1],"place")){
            PROCESS_modifyStyleElement(FN_mergeString("OPTIONBOX",para[2]),"width",para[3]);
            PROCESS_modifyStyleElement(FN_mergeString("OPTIONBOX",para[2]),"height",para[4]);
            PROCESS_modifyStyleElement(FN_mergeString("OPTIONBOX",para[2]),"left",para[5]);
            PROCESS_modifyStyleElement(FN_mergeString("OPTIONBOX",para[2]),"top",para[6]);
        }
        else if(!strcmp(para[1],"style")){
            PROCESS_modifyStyleElement(FN_mergeString("OPTIONBOX",para[2]),para[3],para[4]);
        }
        else if(!strcmp(para[1],"src")){
            PROCESS_modifySrcElement(FN_mergeString("OPTIONBOX",para[2]),para[3]);
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

    else if(!strcmp(para[0],"close_subscene")){
        fclose(html);
        fclose(fnjs);
        html = fopen(FN_mergeString("./output/closesubscene",FN_mergeString(para[1],".html")),"w+");
        fnjs = fopen(FN_mergeString("./output/closesubscene",FN_mergeString(para[1],".js")),"w+");
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

        if(!strcmp(para[1],"show")){
            PROCESS_showElement("DIALOG_BOX");
            PROCESS_showElement("DIALOG_BOX_BG");
            PROCESS_showElement("DIALOG_BOX_SPEAKER");
            PROCESS_showElement("DIALOG_BOX_CONTENT");
        }
        else if(!strcmp(para[1],"hide")){
            PROCESS_hideElement("DIALOG_BOX");
            PROCESS_hideElement("DIALOG_BOX_BG");
            PROCESS_hideElement("DIALOG_BOX_SPEAKER");
            PROCESS_hideElement("DIALOG_BOX_CONTENT");
        }

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
                PROCESS_onClickElement("DIALOG_BOX_CONTENT",para[3]);
            }
            else if(!strcmp(para[2],"subscene_close")){
                PROCESS_onClickCloseElement("DIALOG_BOX_CONTENT",para[3]);
            }

            else if(!strcmp(para[2],"scene_open")){
                PROCESS_onClickScene("DIALOG_BOX_CONTENT",para[3]);
            }
            /*else if(!strcmp(para[2],"dialog_next")){
                PROCESS_ModifyDialogContent("DIALOG_BOX_CONTENT",para[3]);
            }*/
            else if(!strcmp(para[2],"close_dialogBox")){
                PROCESS_onClickhideElement("DIALOG_BOX_CONTENT","DIALOG_BOX",0);
                PROCESS_onClickhideElement("DIALOG_BOX_CONTENT","DIALOG_BOX_BG",1);
                PROCESS_onClickhideElement("DIALOG_BOX_CONTENT","DIALOG_BOX_SPEAKER",1);
                PROCESS_onClickhideElement("DIALOG_BOX_CONTENT","DIALOG_BOX_CONTENT",1);
            }
        }

    }



    free(para);
   


}


void SCRIPT_READ(){

    while(fgets(in,1025,script)){

        FN_fgetsDelEndl(in);
        if(in[0] == '#') continue;
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
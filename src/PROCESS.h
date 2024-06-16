#ifndef PROCESS_H_
#define PROCESS_H_

#include "std.h"
//std.h is for all the neccessary include file to make this work
//in order to make the engine work and be compiled successfully, include std.h is neccessary.

#include "GLOBALVARIABLE.h"
// store global variable and structures
// characters, objects, storing all needs structure for script.


#include "SMALLFUNCTION.h"
// some small functions, functions from FN
// Generally, those functions in FN are usually useful and being the core of the engine.
// such as some small functions to parse the script


void PROCESS_checkScript_NULL();
// to check if your script.yaml exists or not
// this function is important since if you don't check the file exists or not,
// the whole engine may be segmentation fault.
// on the other hand, you can modify this function for more setting if you want to pre-parse other stuff.
// default : only check the existence of the file(script.yaml)

void PROCESS_createStatusPanel();
//to write in the status panel into the html
//without this function, the status panel will not work since there is not status element
//therefore, usually this function will be run before any other function written in html and js.
//status panel contains eight status value and nine inventory slots.
//however, you can modify and choose the amount in your script.

void PROCESS_createDialogBox();
//to write in the dialogBox into the html
//without this function, the dialog system will not work since there is no dialogBox
//therefore, usually this function will be run before any other function written in html and js.
//dialogBox contains four HTML objects, includes CONTENT, AUTHOR, BACKGROUND_IMG, DialogBox.

void PROCESS_getScript();
//the process to read the script.yaml from specific dir.
//file_folder is the variable of argv_[1]

void PROCESS_OPTIONWriteInHTML();
//write in the options button into the html
//without this function, the option system will not work since there is no options.
//therefore, usually this function will be run before any other function written in html and js.

void PROCESS_writeInHTMLHeader();
//write in some headers important to html
//however, this function had been discard after the engine version 0.0.3
//since we pre-written the html system and some neccessary html
//therefore, this function is just for supporting older version of the engine

void PROCESS_fnjsToJS();
//this function is also being discard after the engine version 0.0.3
//since we have changed our engine into a webserver, the function is useless and
//not convienence now.
//this function was mainly for writting js with different files.

void PROCESS_writeInScript(); // discard

void PROCESS_characterSrcHTMLWriteIn(int character_index, int src_index);
//this function is to write in the character's image src into the html.
//without this function, the character will not display its image.
//this function works in any scene, which means you can change the image of the character
//in every different scene.
//character_index is the index of character structure in GLOBALVARIABLE_H
//src_index is the src index of that character.
//each character support to save 500 src.

void PROCESS_showElement(char * id);
//to modify the css style display : block
//there are some prefix of html element,
//therefore, check the prefix before using the function
//otherwise, you may get error from browser's console

void PROCESS_hideElement(char * id);
//to modify the css style display : none
//there are some prefix of html element,
//therefore, check the prefix before using the function
//otherwise, you may get error from browser's console

void PROCESS_modifySrcElement(char * id, char * target);
//this function is to write in the object's image src into the html.
//without this function, the object will not display its image.
//this function works in any scene, which means you can change the image of the object
//in every different scene.

void PROCESS_modifyStyleElement(char * id,char * style,char * target);
//this function is to change the style (css) of a object or any html elements
//there are some prefix of html element,
//therefore, check the prefix before using the function
//otherwise, you may get error from browser's console

void PROCESS_modifyInnerHTMLElement(char * id, char * target);
//this function is to change the innerHTML of a object or any html elements
//there are some prefix of html element,
//therefore, check the prefix before using the function
//otherwise, you may get error from browser's console/

void PROCESS_contentAppearAnimation(char * target, char * content, int speed);
//this function is to make the char * display at dialogBox has animation.
//useful and easy to use function.
//the speed is the ms between next character appear.

void PROCESS_characterMovingAnimation(char * target, int val,int vallast,int speed, char *f,int moves);
//this function is to make the moving animation for the characters.
//as you can see in example-game, idle NPC uses moving animation.
//it is important that the character should be calloc first from the GLOBALVARIABLE.h
//target is the html_tag, val and vallast is the img_src id no.
//the speed is default and you should not change if you don't know how the frequents.
//char *f is the string parameter, check the SCRIPT.h to see the parameter.

void PROCESS_characterMovingHTMLWriteIn(char * target);
//this function is to writeIn the character Moving animation into the js file.
//target is the target character's id.
//make sure the char * target exists or the JS may returns error.
//update : engine version 0.0.3

void PROCESS_writeInInt(int target, FILE * dir);
//this function is to writeIn an int object into specific dir.
//this function is important since the engine may recieve or calculate lots of int object.
//and this function can easily writeIn the int object into fwrite()
//so you won't need to write lots of char buf[] and sprintf.
//(update : may contains bugs and sometimes should try to use sprintf() instead)

void PROCESS_writeInFN_str2ARR(int  i,int a , int b);
//this function is to writeIn an for(i,a,b) range array into a string.
//fwrite(), this function is mainly for making character_movingAnimation() work
//this object can easily writeIn range() array into specific file (generally javascript)

void PROCESS_writeInBackGround();
//this function is to writeIn the background of the html
//this function mainly support the script.yaml for the background parameter.
//without this function, there will be no background html and no background can be set.
//basically setup <img id="BACKGROUND">

void PROCESS_callocObject();
//this function is to calloc the objects in GLOBALVARIABLE_H
//basically => object = calloc(3000,sizeof(GB_OBJECT));

void PROCESS_freeAll();
//free all the stuff which defined at GLOBALVARIABLE_H
//this function is important or the engine may cause serious memory leak.
//check the GLOBALVARIABLE_H to see what have been defined and what to free inside the function
// GB_ 

void PROCESS_requireValueOption(char * value, char * require, char * opt);

void PROCESS_createObject(char * id);
void PROCESS_onClickElement(char * id, char * target);
void PROCESS_onClickScene(char * id, char *target);

void PROCESS_onClickCloseElement(char * id, char * target);
void PROCESS_onClickBodyElement(char * id, char * target);
void PROCESS_onClickBodyCloseElement(char * id, char * target);
void PROCESS_onClickhideElement(char * obj,char * id,int mode);
void PROCESS_ModifyDialogContent(char * id, char * target);
void PROCESS_writeInFadeIn();
void PROCESS_writeInFadeOutAndIn();
void PROCESS_statusNewValue(char * name);
void PROCESS_setStatusValue(char * name , char * value);
void PROCESS_addStatusValue(char * name ,char * src, char * value);
void PROCESS_audioCalloc();
void PROCESS_initialAudio(char * id,char * src);
void PROCESS_playAudio(char * id);
void PROCESS_stopAudio(char * id);
void PROCESS_inventoryNew(char * id);
void PROCESS_inventorySRC(char * id, char * src);
void PROCESS_inventoryGET(char * id);
void PROCESS_requireInventoryOption(char * value, char * opt);
void PROCESS_AudioLoop(char * id,char * src);

void PROCESS_inventoryGET(char * id){
    fwrite("PROCESS_inventoryHAVE(\"",23,1,fnjs);
    fwrite(id,strlen(id),1,fnjs);
    fwrite("\")\n",3,1,fnjs);
}


void PROCESS_inventorySRC(char * id, char * src){
    fwrite("PROCESS_inventorySRC(\"",22,1,fnjs);
    fwrite(id,strlen(id),1,fnjs);
    fwrite("\",\"",3,1,fnjs);
    fwrite(file_folder,strlen(file_folder),1,fnjs);
    fwrite(src+1,strlen(src+1),1,fnjs);
    fwrite(")\n",2,1,fnjs);
}

void PROCESS_inventoryNew(char * id){

    fwrite("PROCESS_inventoryNew(",21,1,fnjs);
    fwrite(id,strlen(id),1,fnjs);
    fwrite(")\n",2,1,fnjs);

}

void PROCESS_requireInventoryOption(char * value, char * opt){
    fwrite("PROCESS_requireInventoryOption(\"",32,1,fnjs);
    fwrite(value,strlen(value),1,fnjs);
    fwrite("\",",2,1,fnjs);
    fwrite(opt,strlen(opt),1,fnjs);
    fwrite(")\n",2,1,fnjs);
}

void PROCESS_requireValueOption(char * value, char * require, char * opt){

    fwrite("PROCESS_requireValueOption(\"",28,1,fnjs);
    fwrite(value,strlen(value),1,fnjs);
    fwrite("\",",2,1,fnjs);
    fwrite(require,strlen(require),1,fnjs);
    fwrite(",",1,1,fnjs);
    fwrite(opt,strlen(opt),1,fnjs);
    fwrite(")\n",2,1,fnjs);

}

void PROCESS_audioCalloc(){
    audio = calloc(3000,sizeof(GB_AUDIO));
}

void PROCESS_initialAudio(char * id,char * src){

    fwrite("AUDIOS_.push(\"",14,1,fnjs);
    fwrite(id,strlen(id),1,fnjs);
    fwrite("\")\n",3,1,fnjs);
    fwrite("AUDIOSSRC_.push(",16,1,fnjs);
    fwrite("new Audio(\"",11,1,fnjs);
    fwrite(file_folder,strlen(file_folder),1,fnjs);
    fwrite(src+1,strlen(src+1),1,fnjs);
    fwrite("))\n",3,1,fnjs);
    fwrite("AUDIOSSRC_[AUDIOSSRC_.length-1].volume = 0.5\n",45,1,fnjs);
    
}

void PROCESS_AudioLoop(char * id,char * src){
    fwrite("AUDIOS_.push(\"",14,1,fnjs);
    fwrite(id,strlen(id),1,fnjs);
    fwrite("\")\n",3,1,fnjs);
    fwrite("AUDIOSSRC_.push(",16,1,fnjs);
    fwrite("new Audio(\"",11,1,fnjs);
    fwrite(file_folder,strlen(file_folder),1,fnjs);
    fwrite(src+1,strlen(src+1),1,fnjs);
    fwrite("))\n",3,1,fnjs);
    fwrite("AUDIOSSRC_[AUDIOSSRC_.length-1].volume = 0.5\n",45,1,fnjs);
    fwrite("AUDIOSSRC_[AUDIOSSRC_.length-1].loop = true\n",44,1,fnjs);
}

void PROCESS_stopAudio(char * id){

    fwrite("AUDIOSSRC_[AUDIOS_.indexOf(\"",28,1,fnjs);
    fwrite(id,strlen(id),1,fnjs);
    fwrite("\")]",3,1,fnjs);
    fwrite(".pause();\n",10,1,fnjs);

    fwrite("AUDIOSSRC_[AUDIOS_.indexOf(\"",28,1,fnjs);
    fwrite(id,strlen(id),1,fnjs);
    fwrite("\")]",3,1,fnjs);
    fwrite(".currentTime = 0;\n",18,1,fnjs);


}

void PROCESS_playAudio(char * id){


    fwrite("AUDIOSSRC_[AUDIOS_.indexOf(\"",28,1,fnjs);
    fwrite(id,strlen(id),1,fnjs);
    fwrite("\")]",3,1,fnjs);
    fwrite(".play();\n",9,1,fnjs);

}


void PROCESS_createStatusPanel(){

    fwrite("document.getElementById(\"CHARACTER_STATUS\").innerHTML +=\"",57,1,fnjs);
    //CHARACTER_STATUS is the html element which store the whole status panel.
    //CHARACTER_STATUS can be active or hide by keystroke(e) while playing the game/script.
    //CHARACTER_STATUS is the engine standard, should not set other html element same id as CHARACTER_STATUS.


    fwrite("<img id=\\\'STATUS_CHARACTER_IMAGE\\\' ",35,1,fnjs);
    fwrite("style=\\\'height:65%; width: 20%;position: absolute;top:7%;",57,1,fnjs);
    fwrite("left: 4%; border-radius: 1%;background-color: white;\\\'>",55,1,fnjs);
    //


    fwrite("<h2 id=\\\'STATUS_CHARACTER_NAME\\\' style=\\\'height:7%; width: 20%;position: absolute;top:77%",89,1,fnjs);
    fwrite(";left: 4%; text-align: center; font-size: 36px;\\\'></h2>",55,1,fnjs);
    for(int i=1;i<=8;i++){
        fwrite("<div id=\\\'STATUS",16,1,fnjs);
        char buf[100] = {0};
        sprintf(buf,"%d",i);
        fwrite(buf,strlen(buf),1,fnjs);
        fwrite("LABEL\\\' class=\\\'statusName\\\'",28,1,fnjs);
        fwrite("  style=\\\'height:8%; left: 32%;top: ",36,1,fnjs);
        fwrite(buf,strlen(buf),1,fnjs);
        fwrite("5%;width: 5%;position:absolute;display: none;\\\'></div>",54,1,fnjs);
        fwrite("<div id=\\\'STATUS",16,1,fnjs);
        fwrite(buf,strlen(buf),1,fnjs);
        fwrite("\\\' style=\\\'height:8%; left: 39%;top: ",37,1,fnjs);
        fwrite(buf,strlen(buf),1,fnjs);
        fwrite("5%;width: 15%;position:absolute;display: none;\\\'> ",50,1,fnjs);
        fwrite("<div id=\\\'STATUS",16,1,fnjs);
        fwrite(buf,strlen(buf),1,fnjs);
        fwrite("LINKHIDE\\\' class=\\\'dashedLinkHide\\\'></div>",42,1,fnjs);
        fwrite("<div id=\\\'STATUS",16,1,fnjs);
        fwrite(buf,strlen(buf),1,fnjs);
        fwrite("LINK\\\' class=\\\'dashedLink\\\'></div>",34,1,fnjs);
        fwrite("</div><div id=\'STATUS",21,1,fnjs);
        fwrite(buf,strlen(buf),1,fnjs);
        fwrite("VALUE\\\'class=\\\'statusName\\\'style=\\\'height:8%; left: 57%;top: ",61,1,fnjs);
        fwrite(buf,strlen(buf),1,fnjs);
        fwrite("5%;width: 5%;position:absolute;display: none;\\\'>0%</div>",56,1,fnjs);
    }

    for(int i=0;i<9;i++){
        int j = i % 3;
        int k = i / 3;
        fwrite("<img id=\\\'STATUS_INVENTORY_",27,1,fnjs);
        char buf[100] = {0};
        sprintf(buf,"%d",i+1);
        fwrite(buf,strlen(buf),1,fnjs);
        fwrite("\\\' style=\\\'position: absolute;height: 20%;width: 8%;top: ",57,1,fnjs);
        char buf2[100] = {0};
        sprintf(buf2,"%d",(3*k+1)*10);
        fwrite(buf2,strlen(buf2),1,fnjs);
        fwrite("%;left:",7,1,fnjs);
        char buf3[100] = {0};
        sprintf(buf3,"%d",65 + j*12);
        fwrite(buf3,strlen(buf3),1,fnjs);
        fwrite("%;background-color: white;\\\'></div>",35,1,fnjs);
    }

    fwrite("\"\n",2,1,fnjs);
}




void PROCESS_addStatusValue(char * name ,char * src, char * value){

    fwrite("PROCESS_STATUSADDVALUE(\"",24,1,fnjs);
    fwrite(name,strlen(name),1,fnjs);
    fwrite("\",\"",3,1,fnjs);
    fwrite(src,strlen(src),1,fnjs);
    fwrite("\",",2,1,fnjs);
    fwrite(value,strlen(value),1,fnjs);
    fwrite(")\n",2,1,fnjs);

}

void PROCESS_setStatusValue(char * name , char * value){
    
}

void PROCESS_onClickScene(char * id, char * target){

    fwrite("document.getElementById(\"",25,1,fnjs);
     fwrite(id,strlen(id),1,fnjs);
    fwrite("\").onclick=",11,1,fnjs);
    fwrite("async function() ",17,1,fnjs);
    fwrite("{await sceneonclick(\"",21,1,fnjs);
    fwrite(target,strlen(target),1,fnjs);
    fwrite("\")}\n",4,1,fnjs);
    
}

void PROCESS_statusNewValue(char * name){

    fwrite("PROCESS_statusNewValueSetup(",28,1,fnjs);
    fwrite(name,strlen(name),1,fnjs);
    fwrite(");\n",3,1,fnjs);

}

void PROCESS_onClickhideElement(char * obj,char * id,int mode){

    if(!mode){
        fwrite(obj,strlen(obj),1,fnjs);
        fwrite("onclickHideEle = [\"",19,1,fnjs);
        fwrite(id,strlen(id),1,fnjs);
        fwrite("\"]\n",3,1,fnjs);

        fwrite("document.getElementById(\"",25,1,fnjs);
        fwrite(obj,strlen(obj),1,fnjs);
        fwrite("\").onclick=function(){\n",23,1,fnjs);
        fwrite("for(var i=0;i<",14,1,fnjs);
        fwrite(obj,strlen(obj),1,fnjs);
        fwrite("onclickHideEle.length",21,1,fnjs);
        fwrite(";i++){\n",7,1,fnjs);
        fwrite("document.getElementById(",24,1,fnjs);
        fwrite(obj,strlen(obj),1,fnjs);
        fwrite("onclickHideEle[i]).style.display = \"None\"",41,1,fnjs);


        fwrite("}}\n",3,1,fnjs);
        
    }
    else{
        fwrite(obj,strlen(obj),1,fnjs);
        fwrite("onclickHideEle.push(\"",21,1,fnjs);
        fwrite(id,strlen(id),1,fnjs);
        fwrite("\")\n",3,1,fnjs);
    }

}

void PROCESS_OPTIONWriteInHTML(){
    fwrite("<div id=\"OPTIONBOX1\" style=\"display:none;position:absolute;z-index:25;\"></div>\n",78,1,html);
    fwrite("<div id=\"OPTIONBOX2\" style=\"display:none;position:absolute;z-index:25;\"></div>\n",78,1,html);
    fwrite("<div id=\"OPTIONBOX3\" style=\"display:none;position:absolute;z-index:25;\"></div>\n",78,1,html);
    fwrite("<div id=\"OPTIONBOX4\" style=\"display:none;position:absolute;z-index:25;\"></div>\n",78,1,html);
}

void PROCESS_writeInFadeIn(){
    fwrite("screenfadeIn()\n",15,1,fnjs);

}

void PROCESS_writeInFadeOutAndIn(){
    fwrite("screenfadeOutandIn()\n",21,1,fnjs);

}

void PROCESS_ModifyDialogContent(char * id, char * target){
    fwrite("document.getElementById(\"",25,1,fnjs);
    fwrite(id,strlen(id),1,fnjs);
    fwrite("\").onclick=function(){",22,1,fnjs);
    PROCESS_contentAppearAnimation(id,target,30);
    fwrite(";}\n",3,1,fnjs);
    
}

void PROCESS_onClickCloseElement(char * id, char * target){
    fwrite("document.getElementById(\"",25,1,fnjs);
    fwrite(id,strlen(id),1,fnjs);
    fwrite("\").onclick=function(){",22,1,fnjs);
    fwrite("subsceneclose();}\n",18,1,fnjs);

}

void PROCESS_onClickElement(char * id, char * target){

    fwrite("document.getElementById(\"",25,1,fnjs);
     fwrite(id,strlen(id),1,fnjs);
    fwrite("\").onclick=",11,1,fnjs);
    fwrite("async function() ",17,1,fnjs);
    fwrite("{await subsceneonclick(\"",24,1,fnjs);
    fwrite(target,strlen(target),1,fnjs);
    fwrite("\")}\n",4,1,fnjs);
    
}



void PROCESS_onClickBodyElement(char * id, char * target){

    fwrite("document.getElementById(\"",25,1,fnjs);
     fwrite(id,strlen(id),1,fnjs);
    fwrite("\").onclick=",11,1,fnjs);
    fwrite("async function() ",17,1,fnjs);
    fwrite("{await scene_send(\"",19,1,fnjs);
    fwrite(target,strlen(target),1,fnjs);
    fwrite("\")}\n",4,1,fnjs);
    
}

void PROCESS_checkScript_NULL(){
    if(script == NULL){
        printf("script.yaml not found.");
        exit(0);
    }
}

void PROCESS_modifySrcElement(char * id, char * target){

    fwrite("document.getElementById(\"",25,1,fnjs);
    fwrite(id,strlen(id),1,fnjs);
    fwrite("\").src=",7,1,fnjs);

    char * n = FN_mergeString(file_folder,target+1);
    n = FN_mergeString("\".",n);

    fwrite(n,strlen(n),1,fnjs);
    fwrite("\n",1,1,fnjs);


    free(n);

}

void PROCESS_createDialogBox(){
    fwrite("<img id=\"BACKGROUND\" style=\"position:absolute;width:100%;height:100%;top:0px;left:0px;\"></img>",94,1,html);
    fwrite("<div id=\"DIALOG_BOX\" style=\"display:none;position:absolute;z-index:5;\">\n",72,1,html);
    fwrite("<img id=\"DIALOG_BOX_BG\" style=\"position:absolute;z-index:-1;\"></img>\n</div>\n",76,1,html);
    fwrite("<h1 id=\"DIALOG_BOX_SPEAKER\" style=\"position:absolute;z-index:6;\"></h1>\n",71,1,html);
    fwrite("<h3 id=\"DIALOG_BOX_CONTENT\" style=\"position:absolute;z-index:7;\"></h3>\n",71,1,html);
    
}





void PROCESS_createObject(char * id){

    fwrite(FN_mergeString("<img id=",id),strlen(FN_mergeString("<img id=",id)),1,html);
    fwrite(" style=\"position:absolute;\">\n",29,1,html);
    fwrite("</img>\n",7,1,html);
}

void PROCESS_freeAll(){
    free(character);
    free(object);
}

void PROCESS_callocObject(){

    object = calloc(3000,sizeof(GB_OBJECT));

}



void PROCESS_characterSrcHTMLWriteIn(int character_index, int src_index){
    
    char * target = FN_mergeString(character[character_index].name,character[character_index].src_name[src_index]);


    fwrite("<img id=\"",9,1,html);
    fwrite(target,strlen(target),1,html);
    fwrite("\" src=\".",8,1,html);

    free(target);
    target = FN_mergeString(file_folder,character[character_index].src[src_index]+1);
    //printf("%s",target);
    fwrite(target,strlen(target),1,html);

    fwrite("style=\"display:none;position:absolute;\">\n",41,1,html);

    
}

void PROCESS_fnjsToJS(){

    fnjs = fopen("./output/temp.js","r+");
    while(fgets(in,3000,fnjs)){
        fwrite(in,strlen(in),1,js);
    }
    fclose(fnjs);
    fclose(js);

}


void PROCESS_writeInHTMLHeader(){

    fwrite("<!DOCTYPE html>\n<html>\n",23,1,html);
    fwrite("<title id=\"HTML_TITLE\"></title>\n",32,1,html);
    fwrite("<meta charset=\"big-5\">\n",23,1,html);
    fwrite("<body style=\"height:97.8%;width:99%;position:absolute;top:0px;left:0px;\">",73,1,html);


}


void PROCESS_getScript(){
    script = fopen(FN_mergeString(file_folder,"script.yaml"),"r+");
}




void PROCESS_contentAppearAnimation(char * target, char * content, int speed){
    fwrite("PROCESS_contentAppearAnimation(\"",32,1,fnjs);
    fwrite(target,strlen(target),1,fnjs);
    fwrite("\",",2,1,fnjs);
    fwrite(content,strlen(content),1,fnjs);
    fwrite(",",1,1,fnjs);
    PROCESS_writeInInt(speed,fnjs);
    fwrite(")\n",2,1,fnjs);

}

void PROCESS_writeInInt(int target, FILE * dir){

    int val = 1;
    if(!target) fwrite("0",1,1,dir);
    else{
        while(target >= val) val *= 10;
        val /= 10;
        while(val){
            int q = target/val;
            q += '0';
            fwrite(&q,1,1,dir);
            target %= val;
            val /= 10;
        }
    }

}


void PROCESS_characterMovingAnimation(char * target, int val,int vallast,int speed, char *f,int moves){

    fwrite("PROCESS_characterMovingAnimation(\"",34,1,fnjs);
    fwrite(target,strlen(target),1,fnjs);
    fwrite("\",",2,1,fnjs);
    PROCESS_writeInInt(val,fnjs);
    fwrite(",",1,1,fnjs);
    PROCESS_writeInInt(vallast,fnjs);
    fwrite(",",1,1,fnjs);
    PROCESS_writeInInt(speed,fnjs);
    fwrite(",",1,1,fnjs);
    fwrite(f,strlen(f),1,fnjs);
    fwrite(",",1,1,fnjs);
    PROCESS_writeInInt(moves,fnjs);
    fwrite(")\n",2,1,fnjs);
}





void PROCESS_characterMovingHTMLWriteIn(char * target){

    char * fq = FN_mergeString(target,"MOVINGIMG");
    //printf("%s",fq);
    fwrite("<img id=\"",9,1,html);
    fwrite(fq,strlen(fq),1,html);
    fwrite("\" ",2,1,html);

    
    fwrite("style=\"display:none;position:absolute;\">\n",41,1,html);   
    free(fq);

}

void PROCESS_writeInBackGround(){
    fwrite("<img id=\"BACKGROUND\" style=\"position:absolute;width:100%;height:100%;top:0px;left:0px;\"></img>\n",95,1,html);
}


void PROCESS_writeInFN_str2ARR(int i,int a , int b){
    //printf("%s",FN_arr2String(i,a,b));
    char * target = FN_arr2String(i,a,b);
    fwrite(target,strlen(target),1,fnjs);
    fwrite("\n",1,1,fnjs);
    free(target);
}

void PROCESS_modifyInnerHTMLElement(char * id, char * target){

    fwrite("document.getElementById(\"",25,1,fnjs);
    fwrite(id,strlen(id),1,fnjs);
    fwrite("\").innerHTML=",13,1,fnjs);
    fwrite(target,strlen(target),1,fnjs);
    fwrite("\n",1,1,fnjs);

}

void PROCESS_modifyStyleElement(char * id,char * style,char * target){

    fwrite("document.getElementById(\"",25,1,fnjs);
    fwrite(id,strlen(id),1,fnjs);
    fwrite("\").style.",9,1,fnjs);
    fwrite(style,strlen(style),1,fnjs);
    fwrite("=",1,1,fnjs);
    fwrite(target,strlen(target),1,fnjs);
    fwrite("\n",1,1,fnjs);

}



void PROCESS_showElement(char * id){

    fwrite("document.getElementById(\"",25,1,fnjs);
    fwrite(id,strlen(id),1,fnjs);
    fwrite("\").style.display=\"block\"\n",25,1,fnjs);

}

void PROCESS_hideElement(char * id){

    fwrite("document.getElementById(\"",25,1,fnjs);
    fwrite(id,strlen(id),1,fnjs);
    fwrite("\").style.display=\"none\"\n",24,1,fnjs);


}

#endif
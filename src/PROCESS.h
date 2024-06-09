#ifndef PROCESS_H_
#define PROCESS_H_

#include "std.h"
#include "GLOBALVARIABLE.h"
#include "SMALLFUNCTION.h"

void PROCESS_checkScript_NULL();
void PROCESS_createDialogBox();
void PROCESS_getScript();

void PROCESS_writeInHTMLHeader();
void PROCESS_fnjsToJS();
void PROCESS_writeInScript(); // discard
void PROCESS_characterSrcHTMLWriteIn(int character_index, int src_index);
void PROCESS_showElement(char * id);
void PROCESS_hideElement(char * id);
void PROCESS_modifySrcElement(char * id, char * target);
void PROCESS_modifyStyleElement(char * id,char * style,char * target);
void PROCESS_modifyInnerHTMLElement(char * id, char * target);
void PROCESS_contentAppearAnimation(char * target, char * content, int speed);
void PROCESS_characterMovingAnimation(char * target, int val,int vallast,int speed, char *f,int moves);
void PROCESS_characterMovingHTMLWriteIn(char * target);
void PROCESS_writeInInt(int target, FILE * dir);
void PROCESS_writeInFN_str2ARR(int  i,int a , int b);
void PROCESS_writeInBackGround();
void PROCESS_callocObject();
void PROCESS_freeAll();
void PROCESS_createObject(char * id);
void PROCESS_onClickElement(char * id, char * target);
void PROCESS_onClickCloseElement(char * id, char * target);
void PROCESS_onClickBodyElement(char * id, char * target);
void PROCESS_onClickBodyCloseElement(char * id, char * target);
void PROCESS_onClickhideElement(char * obj,char * id,int mode);
void PROCESS_ModifyDialogContent(char * id, char * target);
void PROCESS_writeInFadeIn();


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

void PROCESS_writeInFadeIn(){
    fwrite("screenfadeIn()\n",15,1,fnjs);

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
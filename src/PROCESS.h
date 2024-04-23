#ifndef PROCESS_H_
#define PROCESS_H_

#include "std.h"
#include "GLOBALVARIABLE.h"
#include "SMALLFUNCTION.h"

void PROCESS_createOutputFile();
void PROCESS_delTempJS();
void PROCESS_getScript();
void PROCESS_closeOutputFile();
void PROCESS_checkScript_NULL();
void PROCESS_writeInHTMLHeader();
void PROCESS_fnjsToJS();
void PROCESS_writeInScript();
void PROCESS_characterSrcHTMLWriteIn(int character_index, int src_index);
void PROCESS_createDialogBox();
void PROCESS_showElement(char * id);
void PROCESS_hideElement(char * id);
void PROCESS_modifySrcElement(char * id, char * target);
void PROCESS_modifyStyleElement(char * id,char * style,char * target);
void PROCESS_modifyInnerHTMLElement(char * id, char * target);
void PROCESS_contentAppearAnimation(char * target, char * content, int speed);
void PROCESS_contentAppearAnimationFunctionWriteInFnJs();
void PROCESS_characterMovingAnimation(char * target, int val,int vallast,int speed, char *f);
void PROCESS_characterMovingAnimationFunctionWriteInFnJs();
void PROCESS_characterMovingHTMLWriteIn(char * target);
void PROCESS_writeInInt(int target, FILE * dir);



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

void PROCESS_characterSrcHTMLWriteIn(int character_index, int src_index){
    
    char * target = FN_mergeString(character[character_index].name,character[character_index].src_name[src_index]);


    fwrite("<img id=\"",9,1,html);
    fwrite(target,strlen(target),1,html);
    fwrite("\" src=\".",8,1,html);

    free(target);
    target = FN_mergeString(file_folder,character[character_index].src[src_index]+1);
    
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

void PROCESS_checkScript_NULL(){
    if(script == NULL){
        printf("script.yaml not found.");
        exit(0);
    }
}

void PROCESS_createOutputFile(){
    mkdir("output");
    html = fopen("./output/output.html","w+");
    js = fopen("./output/output.js","w+");
    fnjs = fopen("./output/temp.js","w+");

}

void PROCESS_closeOutputFile(){
    fclose(html);
    fclose(fnjs);
}

void PROCESS_delTempJS(){
    remove("./output/temp.js");
}

void PROCESS_writeInScript(){
    fwrite("<script src=\"output.js\"></script>\n",34,1,html);
}


void PROCESS_createDialogBox(){
    fwrite("<div id=\"DIALOG_BOX\" style=\"display:none;position:absolute;z-index:5;\">\n",72,1,html);
    fwrite("<img id=\"DIALOG_BOX_BG\" style=\"position:absolute;z-index:-1;\"></img>\n</div>\n",76,1,html);
    fwrite("<h1 id=\"DIALOG_BOX_SPEAKER\" style=\"position:absolute;z-index:6;\"></h1>\n",71,1,html);
    fwrite("<h3 id=\"DIALOG_BOX_CONTENT\" style=\"position:absolute;z-index:7;\"></h3>\n",71,1,html);
    
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

void PROCESS_contentAppearAnimationFunctionWriteInFnJs(){
    
    fwrite("function PROCESS_contentAppearAnimation(a,b,c){\n",48,1,fnjs);
    fwrite("var fade = document.getElementById(a);\n",39,1,fnjs);
    fwrite("var q = setInterval(() => {\n",28,1,fnjs);
    fwrite("fade.innerHTML += b[0];\n",24,1,fnjs);
    fwrite("if(fade.innerHTML.length%60 == 0){\n",35,1,fnjs);
    fwrite("fade.innerHTML += '/n'}\n",24,1,fnjs);
    fwrite("b = b.substring(1);\n",20,1,fnjs);
    fwrite("if(b.length == 0) clearInterval(q)\n",35,1,fnjs);
    fwrite("}, c);}\n",8,1,fnjs);
    


}

void PROCESS_characterMovingAnimation(char * target, int val,int vallast,int speed, char *f){

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
    fwrite(")\n",2,1,fnjs);
}



void PROCESS_characterMovingAnimationFunctionWriteInFnJs(){
    
    fwrite("function PROCESS_characterMovingAnimation(a,b,c,d,e){\n",54,1,fnjs);
    fwrite("var qs = document.getElementById(a);\n",37,1,fnjs);
    fwrite("var cc = 0;\n",12,1,fnjs);
    fwrite("var q = setInterval(() => {\n",28,1,fnjs);
    fwrite("qs.src=e[cc]\n",13,1,fnjs);
    fwrite("cc += 1\n",8,1,fnjs);
    fwrite("if(cc == e.length) cc = 0\n",26,1,fnjs);
    
    fwrite("}, d);}\n",8,1,fnjs);
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

#endif
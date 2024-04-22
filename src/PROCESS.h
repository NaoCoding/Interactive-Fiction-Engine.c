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
    fwrite("<div id=\"DIALOG_BOX\" style=\"display:none;\">\n",44,1,html);
    fwrite("<img id=\"DIALOG_BOX_BG\"></img>\n</div>\n",38,1,html);
    
}

#endif
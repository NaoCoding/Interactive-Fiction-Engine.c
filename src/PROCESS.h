#ifndef PROCESS_H_
#define PROCESS_H_

#include "std.h"
#include "GLOBALVARIABLE.h"
#include "SCRIPT.h"
#include "SMALLFUNCTION.h"

void PROCESS_createOutputFile();
void PROCESS_delTempJS();
void PROCESS_getScript();
void PROCESS_closeOutputFile();
void PROCESS_checkScript_NULL();
void PROCESS_writeInHTMLHeader();
void PROCESS_fnjsToJS();

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
    fwrite("<script src=\"output.js\"></script>\n",34,1,html);


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

#endif
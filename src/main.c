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

#include "SCRIPT.h" 
// parse script.yaml and parse script


#include "PROCESS.h" 
// process all command parsed from SCRIPT.h


int main(int argc,char *argv_input_path[]){

    strcpy(file_folder,argv_input_path[1]);
    // file_folder is a char * which store the file folder of your script

    mkdir("output",0777);
    // to create a dir in your pc to save the output files after parsing your script.yaml

    html = fopen("./output/general.html","w+");
    js = fopen("./output/functions.js","w+");
    fnjs = fopen("./output/general.js","w+");
    script = fopen(FN_mergeString(file_folder,"script.yaml"),"r");
    //four essential FILE * 

    //("DEBUG_MESSAGE\n");

    PROCESS_checkScript_NULL(script);
    // to check if your script.yaml exists or not

    //PROCESS_playerControlFunctionWriteInFnJs();    //already discarded
    //PROCESS_characterMovingAnimationFunctionWriteInFnJs(); //already discarded
    //PROCESS_contentAppearAnimationFunctionWriteInFnJs(); //already discarded

    //PROCESS_audioCalloc();
    //calloc the size to store audio files
    //this function is to calloc the structure which store the src of the audio
    //discard after engine version 0.0.4

    PROCESS_createDialogBox();
    //write in the dialogBox html 

    PROCESS_createStatusPanel();
    //write in the status panel html

    PROCESS_OPTIONWriteInHTML();
    //write in the options button html

    
    SCRIPT_READ(script,html,js,fnjs);
    // parse script.yaml and transfer to lots of html and js.
    // "not" the core system of the engine
    // all it do is pre-parse and transfer the parameters to SCRIPT_ANALYZE()
    // the core function is SCRIPT_ANALYZE()


    fclose(html);
    fclose(js);
    fclose(fnjs);
    fclose(script);
    // to close all the file opened currently 
    // fnjs, html may be other file ( not general.html , general.js)
    // depends on the script.yaml
    // each time change scene or subscene, the file changed


    //free(audio);
    //to free the audio pointer
    //audio pointer_size is 3000
    //which means the engine support 3000 audio src in the same script.
    //discard after engine version 0.0.4


    system("python3 ./src/server.py");
    // start the http.server from python
    // if there are errors when GET requests, sometimes check the python file may help
    

    //system("rm -r ./output");
}




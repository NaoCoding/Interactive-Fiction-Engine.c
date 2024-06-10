#include "std.h" // to include all c library
#include "SMALLFUNCTION.h" // some small functions, functions from FN
#include "GLOBALVARIABLE.h" // store global variable and structures
#include "SCRIPT.h" // parse script.yaml and parse script
#include "PROCESS.h" // process all command parsed from SCRIPT.h


int main(int argc,char *argv_input_path[]){

    strcpy(file_folder,argv_input_path[1]);
    mkdir("output",0777);
    //mkdir("./outout/save",0777);

    html = fopen("./output/general.html","w+");
    js = fopen("./output/functions.js","w+");
    fnjs = fopen("./output/general.js","w+");
    script = fopen(FN_mergeString(file_folder,"script.yaml"),"r");

    //("DEBUG_MESSAGE\n");
    PROCESS_checkScript_NULL(script);

    //PROCESS_playerControlFunctionWriteInFnJs();    
    //PROCESS_characterMovingAnimationFunctionWriteInFnJs();
    //PROCESS_contentAppearAnimationFunctionWriteInFnJs();

    PROCESS_createDialogBox();
    PROCESS_OPTIONWriteInHTML();

    // parse script.yaml and transfer to lots of html and js.
    SCRIPT_READ(script,html,js,fnjs);


    fclose(html);
    fclose(js);
    fclose(fnjs);
    fclose(script);



    system("python3 ./src/server.py");

    //system("rm -r ./output");
}




#include "std.h"
#include "SMALLFUNCTION.h"
#include "GLOBALVARIABLE.h"
#include "SCRIPT.h"
#include "PROCESS.h"


int main(int argc,char *argv_input_path[]){

    strcpy(file_folder,argv_input_path[1]);
    mkdir("output",0777);
    //mkdir("./outout/save",0777);

    html = fopen("./output/general.html","w+");
    js = fopen("./output/functions.js","w+");
    fnjs = fopen("./output/general.js","w+");
    script = fopen(FN_mergeString(file_folder,"script.yaml"),"r");

    //printf("DEBUG_MESSAGE\n");
    PROCESS_checkScript_NULL(script);

    //PROCESS_playerControlFunctionWriteInFnJs();    
    //PROCESS_characterMovingAnimationFunctionWriteInFnJs();
    //PROCESS_contentAppearAnimationFunctionWriteInFnJs();

    PROCESS_createDialogBox();

    SCRIPT_READ(script,html,js,fnjs);


    fclose(html);
    fclose(js);
    fclose(fnjs);
    fclose(script);



    system("python3 ./src/server.py");

    system("rm -r ./output");
}




#include "std.h"
#include "SMALLFUNCTION.h"
#include "GLOBALVARIABLE.h"
#include "SCRIPT.h"
#include "PROCESS.h"


int main(int argc,char *argv_input_path[]){

    strcpy(file_folder,argv_input_path[1]);
    mkdir("output",0777);
    sprintf(charScene,"%d",scene);
    html = fopen(FN_mergeString("./output/scene",FN_mergeString(charScene,".html")),"w+");
    js = fopen("./output/temp.js","w+");
    fnjs = fopen(FN_mergeString("./output/scene",FN_mergeString(charScene,".js")),"w+");
    script = fopen(FN_mergeString(file_folder,"script.yaml"),"r");


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




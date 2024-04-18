#include "std.h"
#include "script.h"
#include "smallfn.h"
#include "ui.h"



int main(int argc,char *argv_input_path[]){

    Script * input_file = Script_setup(argv_input_path[1]);
    strcpy(input_file->folder,argv_input_path[1]);

    if(Script_start_general_check(input_file)){
        printf("%s file format error!\n",input_file->path);
        exit(0);
    }

    mkdir("output");
    FILE * output_file = fopen("output/output.html","w+");
    FILE * output_js = fopen("output/output.js","w+");
    FILE * temp_js = fopen("output/temp.js","w+");
    
    npc = calloc(1000,sizeof(Character));


    Script_read(input_file,output_file,output_js,temp_js);
    fwrite("</body>\n</html>\n",16,1,output_file);
    fclose(temp_js);

    FILE * temp_js_rMode = fopen("output/temp.js","r");
    merge_js(temp_js_rMode,output_js);

    Script_freespace(input_file);
    fclose(output_file);
    fclose(output_js);

    /*
    if(didGeneral){
        char *cwd = calloc(1025,sizeof(char));
        getcwd(cwd,1025);
        strcat(cwd,"/output/output.html");
        system(cwd);
    }
    */
   //printf("%d",npc_size);
    



}


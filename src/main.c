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

    FILE * output_file = fopen("output.html","w+");
    FILE * output_js = fopen("output.js","w+");

    Script_read(input_file,output_file,output_js);
    fwrite("</body>\n</html>\n",16,1,output_file);

    Script_freespace(input_file);
    fclose(output_file);
    fclose(output_js);
    //if(didGeneral)system("output.html");
    



}


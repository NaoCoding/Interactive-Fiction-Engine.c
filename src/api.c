#include "std.h"
#include "SMALLFUNCTION.h"

int main(int argc,char *argv_input_path[]){

    if(!strcmp(argv_input_path[1],"html")){
        printf("%s",FN_mergeString("scene",FN_mergeString(argv_input_path[2]+1,".html")));
    }

    if(!strcmp(argv_input_path[1],"js")){
        printf("%s",FN_mergeString("scene",FN_mergeString(argv_input_path[2]+1,".js")));
    }

}
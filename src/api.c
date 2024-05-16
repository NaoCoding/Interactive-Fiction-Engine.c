#include "std.h"
#include "SMALLFUNCTION.h"

char * API_RANDOMFILENAME();


char * API_RANDOMFILENAME(){
    char * s = calloc(11,sizeof(char));
    for(int i=0;i<10;i++) s[i] = rand()%26+65;
    return s;
}

int main(int argc,char *argv_input_path[]){

    srand(time(0));
    if(argc == 1){
        printf("del_saves : delete all save files\n");
        printf("start_server [game_folder] : start a server with game folder\n");

        exit(0);
    }

    if(!strcmp(argv_input_path[1],"new_game")){
        if(!strcmp(argv_input_path[2],"createFile")){
            mkdir("./saves",0777);
            char * dir = API_RANDOMFILENAME();
            FILE * save = fopen(FN_mergeString("./saves/",dir),"w+");
            fwrite("scene=NULL",13,1,save);
            fclose(save);
            printf("%s",dir);
            free(dir);
        }
        else  printf("%s",FN_mergeString("general.",argv_input_path[2]));
    }

    else if(!strcmp(argv_input_path[1],"change_scene")){
        printf("%s",FN_mergeString("scene",FN_mergeString(argv_input_path[3],FN_mergeString(".",argv_input_path[2]))));
    }
    else if(!strcmp(argv_input_path[1],"change_subscene")){
        printf("%s",FN_mergeString("",FN_mergeString(argv_input_path[3],FN_mergeString(".",argv_input_path[2]))));
    }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                

    else if(!strcmp(argv_input_path[1],"del_saves")){
        system("rm -r ./saves");
    }
    else if(!strcmp(argv_input_path[1],"start_server")){
        //system("make");
        system(FN_mergeString("./engine ",argv_input_path[2]));
    }
    else if(!strcmp(argv_input_path[1],"closesubscene")){
        printf("%s",FN_mergeString("close",FN_mergeString(argv_input_path[3],FN_mergeString(".",argv_input_path[2]))));
    }
    
    //else if(!(strcmp(argv_input_path[1],"character_move")))

}
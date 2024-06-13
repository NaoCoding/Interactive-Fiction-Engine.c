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
    else if(!strcmp(argv_input_path[1],"save")){
        FILE * readIn = fopen("./saves/temp","w");
        FILE * writeIn = fopen(FN_mergeString("./saves/",argv_input_path[2]),"r");
        char in[1025];
        while(fgets(in,1025,writeIn)){
            fwrite(in,strlen(in),1,readIn);
        }
        fclose(readIn);
        fclose(writeIn);
        readIn = fopen("./saves/temp","r");
        writeIn = fopen(FN_mergeString("./saves/",argv_input_path[2]),"w");

        int index = 0;
        while(index < atoi(argv_input_path[3])){
            fgets(in,1025,readIn);
            fwrite(in,strlen(in),1,writeIn);
            index += 1;
        }
        fgets(in,1025,readIn);
        fwrite(argv_input_path[4],strlen(argv_input_path[4]),1,writeIn);
        fwrite("\n",1,1,writeIn);
        while(fgets(in,1025,readIn)){
            fwrite(in,strlen(in),1,writeIn);
        }
        fclose(readIn);
        fclose(writeIn);
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
#ifndef DEBUG_H
#define DEBUG_H

#include "std.h"
#include "smallfn.h"
#include "script.h"
#include "ui.h"

void DEBUG_checkNPCTag(){
    for(int i=0;i<npc_size;i++){
        if(npc[i].active){
            printf("%s %s",npc[i].name,npc[i].src);
        }
    }
}

#endif
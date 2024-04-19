#ifndef SCRIPT_H
#define SCRIPT_H
#include "std.h"
#include "smallfn.h"
#include "ui.h"




Script * Script_setup(char p[]);
void Script_freespace(Script * target);
int Script_start_general_check(Script * target);
void Script_read(Script * target, FILE * html , FILE * js,FILE * fnjs);
void Script_read_general(Script * target, FILE * html,FILE * js,FILE * fnjs);
void Script_read_scene(Script * target, FILE * html,FILE * js,FILE * fnjs);
void Script_read_character(Script * target, FILE * html,FILE * js,FILE * fnjs);
void Script_read_player(Script * target, FILE * html,FILE * js,FILE * fnjs);
void checkPoundSign(char * in,Script * target, FILE * html,FILE * js,FILE * fnjs);

static int didGeneral = 0;

void Script_read_scene(Script * target, FILE * html,FILE * js,FILE * fnjs){  
    
    int didId = 0,didFirst = 0;
    char in[1025];
    char id[1025] = {0};
    char onclick[1025] = {0};
    char bg[1025] = {0};
    int characters[1000];
    char characters_parameters[1000][4][25];
    int player_atScene[5] = {0}; // active,left,right,up,sneak
    char speak[2][1000];
    int speakToggle = 0;
    int characters_atScene = 0;

    for(int i=0;i<1000;i++){
        characters[i] = -1;
        for(int j=0;j<4;j++){
            characters_parameters[i][j][0] = 0;
        }
    }

    while(fgets(in,1025,target->source)){

        fgetsDelendl(in);
        if(in[0] == '#') break;

        if(string_compare(0,3,in,"id:")){
            fwrite("<div id=",8,1,html);
            didId = 1;
            int idx = 0;
            
            while(in[idx]!='\"')idx ++;
            strcpy(id,in+idx);
            while(in[idx]){
                fwrite(&in[idx],1,1,html);
                idx ++;
            }
            fwrite(" style=",7,1,html);
            
        }

        if(string_compare(0,10,in,"first:True") && didId){
            didFirst = 1;
            fwrite("\"display:block;",15,1,html);
            
        }

        if(string_compare(0,11,in,"background:") && didId){
            int idx = 11;
            while(in[idx]!='\"')idx ++;
            strcpy(bg,in+idx+1);
        }

        if(string_compare(0,19,in,"click.change_scene:") && didId){
            int idx = 19;
            while(in[idx]!='\"')idx ++;
            strcpy(onclick,in+idx+1);
        }

        if(string_compare(0,16,in,"character.speak:") && didId){
            int idx = 16;
            char * name = strtok_withoutReplace(in+idx,',');
            idx += strlen(name);
            speakToggle = 1;
            idx += 1;
            strcpy(speak[1],in+idx);
            strcpy(speak[0],name);
        }

        if(string_compare(0,15,in,"character.show:") && didId){

            int idx = 15;
            //printf("DEBUG_MESSAGE");

            if(in[idx] == '\"'){

                char * name = strtok_withoutReplace(in+idx,',');
                characters[characters_atScene] = _CHAR_NameIDSearch(name);
                idx += strlen(name);

            }
            else{
                characters[characters_atScene] = 0;
                while(isdigit(in[idx])){
                    characters[characters_atScene] *= 10;
                    characters[characters_atScene] += in[idx] - '0';
                    idx ++;
                }
                
                
            }

            //printf("DEBUG_MESSAGE");
            idx ++;
            
            if(in[idx-1]==','){
                for(int j=0;j<4;j++){
                    strcpy(characters_parameters[characters_atScene][j],strtok_withoutReplace(in+idx,','));
                    idx += strlen(characters_parameters[characters_atScene][j]);
                    idx += 1;
                }
            }

            else{
                for(int j=0;j<4;j++){
                    strcpy(characters_parameters[characters_atScene][j],npc[characters[characters_atScene]].place[j]);
                }
            }
            
            

            //debug
            //for(int i=0;i<3;i++)printf("%d ",characters[characters_atScene][i]);
        
            characters_atScene ++;
        }


        if(string_compare(0,13,in,"player.active:True"))player_atScene[0] = 1;
        if(string_compare(0,16,in,"player.left:True")) player_atScene[1] = 1;
        if(string_compare(0,17,in,"player.right:True")) player_atScene[2] = 1;
        

    }

    if(!didFirst)fwrite("\"display:none;",14,1,html);
    
    fwrite("position:absolute;width:100%;height:100%;top:0px;left:0px;",58,1,html);

    fwrite("\"",1,1,html);

    

    if(strlen(onclick)){
        fwrite("onclick = ",10,1,html);
        fwrite(id+1,strlen(id)-2,1,html);
        fwrite(onclick,strlen(onclick)-1,1,html);
        fwrite("()",2,1,html);
        fwrite("function ",9,1,fnjs);
        fwrite(id+1,strlen(id)-2,1,fnjs);
        fwrite(onclick,strlen(onclick)-1,1,fnjs);
        fwrite("(){\n",4,1,fnjs);
        animation_fadeOut_click_change_scene(id,fnjs);
        fwrite("\n",1,1,fnjs);
        //fwrite("fade.style.display = \"none\";\n",29,1,fnjs);
        fwrite(merge_string("fadeIn",onclick),strlen(merge_string("fadeIn",onclick))-1,1,fnjs);
        fwrite("()",2,1,fnjs);

        fwrite("}\n",2,1,fnjs);

       

        fwrite("function ",9,1,fnjs);
        fwrite(merge_string("fadeIn",onclick),strlen(merge_string("fadeIn",onclick))-1,1,fnjs);
        fwrite("(){\n",4,1,fnjs);
        fwrite("\n",1,1,fnjs);
        
         animation_fadeIn_click_change_scene(merge_string("\"",onclick),fnjs);

        fwrite("}\n",2,1,fnjs);
    }


    fwrite(">",1,1,html);
    fwrite("\n",1,1,html);
    if(didFirst && ani_config->didfirst_fadein)animation_fadeIn_windowonload(id,html);

    if(strlen(bg)){
        fwrite("<img src=\".",11,1,html);
        fwrite(target->folder,strlen(target->folder),1,html);
        fwrite(bg,strlen(bg),1,html); 
        fwrite("style=\"position:absolute;height:100%;width:100%;top:0px;left:0px;z-index:-2;\">",78,1,html);
    }
    fwrite("\n",1,1,html);

    for(int i=0;i<characters_atScene;i++){
        fwrite("<img src=\".",11,1,html);
        fwrite(target->folder,strlen(target->folder),1,html);
        //printf("%s",npc[characters[i][0]].src);
        fwrite(npc[characters[i]].src+1,strlen(npc[characters[i]].src)-1,1,html);
        fwrite("style=\"position:absolute;left:",30,1,html);
        fwrite(characters_parameters[i][0],strlen(characters_parameters[i][0]),1,html);
        fwrite(";top:",5,1,html);
        fwrite(characters_parameters[i][1],strlen(characters_parameters[i][1]),1,html);
        fwrite(";width:",7,1,html);
        fwrite(characters_parameters[i][2],strlen(characters_parameters[i][2]),1,html);
        fwrite(";height:",8,1,html);
        fwrite(characters_parameters[i][3],strlen(characters_parameters[i][3]),1,html);
        fwrite("\">\n",3,1,html);
    }

    if(speakToggle){
        fwrite("<div style=\"position:absolute;top:",34,1,html);
        writeInInt(speakDiv->y,html);
        fwrite("%;left:",7,1,html);
        writeInInt(speakDiv->x,html);
        fwrite("%;height:",9,1,html);
        writeInInt(speakDiv->ysize,html);
        fwrite("%;width:",8,1,html);
        writeInInt(speakDiv->xsize,html);
        fwrite("%;\">\n",5,1,html);
        if(speakDiv->srcactive){
            fwrite("<img style=\"position:absolute;top:0px;left:0px;width:100%;height:100%;z-index:-1;\" src=\".",89,1,html);
            fwrite(target->folder,strlen(target->folder),1,html);
            
            fwrite(speakDiv->src+1,strlen(speakDiv->src)-1,1,html);
            fwrite("></img>\n",8,1,html);
        }
        fwrite("<h1 style=\"left:5%;position:absolute;\">",39,1,html);
        fwrite(speak[0]+1,strlen(speak[0])-2,1,html);
        fwrite("</h1>\n<h3 style=\"left:7%;top:23%;position:absolute;\">",53,1,html);
        fwrite(speak[1]+1,strlen(speak[1])-2,1,html);
        fwrite("</h3>\n",6,1,html);

        fwrite("</div>\n",7,1,html);
    }

    if(player_atScene[0]){
        fwrite("<script type=\"text/javascript\">\n",32,1,html);
        
        ui_player_show(html);
        ui_player_img_normal(target,html);
        
        fwrite("function keyPressed(){\n",23,1,html);
        fwrite("var k = event.keyCode\n",22,1,html);
        //fwrite("console.log(k==37)\n",19,1,html);
        if(player_atScene[1]){
            fwrite("if(k==37){",10,1,html);
            ui_player_key_left(html);
            fwrite("}\n",1,1,html);
        }
        if(player_atScene[2]){
            fwrite("if(k==39){",10,1,html);
            ui_player_key_right(html);
            fwrite("}\n",1,1,html);
        }
        // 38 up 40 down
        fwrite("}document.onkeydown=keyPressed",30,1,html);
        fwrite("</script> \n",11,1,html);
        
    }
   

    fwrite("</div>\n",7,1,html);

    checkPoundSign(in,target,html,js,fnjs);

}

void Script_read_player(Script * target, FILE * html,FILE * js,FILE * fnjs){

    char in[1025];
    player->active = 1;
    fwrite("<img id=\"UI_PLAYER_CONST\" style=\"position:absolute;display:none;left:0%;top:0%;",79,1,html);
    //fwrite("\n",1,1,html);
    while(fgets(in,1025,target->source)){

        fgetsDelendl(in);
        if(in[0] == '#') break;

        if(string_compare(0,13,in,"player.speed:")){
            player->movement_speed = 0;
            int idx = 13;
            while(isdigit(in[idx])){
                player->movement_speed *= 10;
                player->movement_speed += in[idx] - '0';
                idx ++;
            }
        }

        if(string_compare(0,20,in,"player.normal.image:")){
            strcpy(player->normal_src,in+20);
            player->normal_src_active = 1; 
        }

        if(string_compare(0,11,in,"player.size:")){
            strcpy(player->style_place[2],strtok_withoutReplace(in+12,','));
            strcpy(player->style_place[3],in+11+strlen(player->style_place[2])+2);
            fwrite("width:",6,1,html);
            fwrite(player->style_place[2],strlen(player->style_place[2]),1,html);
            fwrite(";height:",8,1,html);
            fwrite(player->style_place[3],strlen(player->style_place[3]),1,html);
            fwrite(";",1,1,html);
        }

    }
    fwrite("\">",2,1,html);

    checkPoundSign(in,target,html,js,fnjs);

}

void Script_read_character(Script * target, FILE * html,FILE * js,FILE * fnjs){

    char in[1025];
    int npcidx = -1;
    while(fgets(in,1025,target->source)){

        fgetsDelendl(in);
        if(in[0] == '#') break;
        if(string_compare(0,3,in,"id:")){
            int idx = 3;
            npcidx = 0;
            while(isdigit(in[idx])){
                npcidx = npcidx * 10 + in[idx] - '0';
                idx ++;
            }
            npc[npcidx].active = 1;
            
        }

        if(string_compare(0,5,in,"name:") && npcidx != -1){
            strcpy(npc[npcidx].name,in+5);
        }

        if(string_compare(0,4,in,"img:") && npcidx != -1){
            strcpy(npc[npcidx].src,in+4);
        }


        if(string_compare(0,6,in,"place:") && npcidx != -1){
            int idx = 6;
            for(int j=0;j<4;j++){
                strcpy(npc[npcidx].place[j],strtok_withoutReplace(in+idx,','));
                idx += strlen(npc[npcidx].place[j]);
                idx += 1;
            }
        }



    }

    checkPoundSign(in,target,html,js,fnjs);


}


void Script_read_general(Script * target, FILE * html,FILE * js,FILE * fnjs){
    didGeneral = 1;
    fwrite("<head>\n",7,1,html);
    fwrite("<script src=\"output.js\"></script>",33,1,html);
    fwrite("<meta charset=\"big-5\">\n",23,1,html);
    
    char in[1025];
    while(fgets(in,1025,target->source)){

        fgetsDelendl(in);
        if(in[0] == '#') break;

        if(string_compare(0,6,in,"title:")){
            fwrite("<title>",7,1,html);
            int idx = 0;
            while(in[idx]!='\"')idx ++;
            idx ++;
            while(in[idx]!='\"'){
                fwrite(&in[idx],1,1,html);
                idx ++;
            }
            fwrite("</title>\n",9,1,html);
        }

        if(string_compare(0,15,in,"characterCount:")){
            int idx = 15;
            while(isdigit(in[idx])){
                npc_size = npc_size * 10 + in[idx] - '0';
                idx ++;
            }
           
        }
        if(string_compare(0,10,in,"dialogBox:")){
            speakDiv->srcactive = 1;
            strcpy(speakDiv->src,in + 10);
        }

        if(string_compare(0,22,in,"animation.first_scene:")){
            if(!strcmp("\"fadeIn\"",in+22)){
                ani_config->didfirst_fadein = 1;
            }
        }


    }
    
    fwrite("</head>\n<body>\n",15,1,html);

    checkPoundSign(in,target,html,js,fnjs);

}

void checkPoundSign(char * in,Script * target, FILE * html,FILE * js,FILE * fnjs){
    if(!strcmp(in,"#general"))Script_read_general(target,html,js,fnjs);
    else if(!strcmp(in,"#scene"))Script_read_scene(target,html,js,fnjs);
    else if(!strcmp(in,"#character"))Script_read_character(target,html,js,fnjs);
    else if(!strcmp(in,"#player"))Script_read_player(target,html,js,fnjs);

}


Script * Script_setup(char p[]){
    Script * target = calloc(1,sizeof(Script));
    strcpy(target->path,p);
    strcat(target->path,"script.yaml");
    target->source = fopen(target->path,"r");
    return target;
}

void Script_freespace(Script * target){
    fclose(target->source);
    free(target);
}

int Script_start_general_check(Script * target){
    char in[1025];
    fgets(in,1025,target->source);
    fgetsDelendl(in);

    return strcmp(in,"#script");
}

void Script_read(Script * target, FILE * html , FILE * js,FILE * fnjs){

    char in[1025];
    html_setup(html);
    while(fgets(in,1025,target->source)){
        fgetsDelendl(in);
        checkPoundSign(in,target,html,js,fnjs);
    
    }

}




#endif
function subsceneonclick(a){

    subscene_toOpen = a;
    scene_subscene[1] = a;
    subscene_send();

}

function sceneonclick(a){

    scene_send(a);
    scene_subscene[0] = a;
    change_scenePlace = [-1,-1]
    change_sceneTargetFn = ["",""]


}

function load_save(a){

    save_name = a
    /*
    $.ajax({
        url:"command/load_save_" + a,
        method:"GET",
        
        success:function(res){
            
        }

    })
    */

}

function new_save(){


    $.ajax({
        url:"command/new?game?html",
        method:"GET",

        success:function(res){
            document.getElementById("HTML_GENERAL").innerHTML = res;
        }

    })

    $.ajax({
        url:"command/new?game?js",
        method:"GET",

        success:function(res){
            eval(res)
        }

    })

}

function subscene_send(){

    

    $.ajax({
        url:"command/sub?game?html?" + subscene_toOpen,
        method:"GET",

        success:function(res){
            
            document.getElementById("HTML_SUB").innerHTML = res;
        },
    }
    )
    
    $.ajax({
        url:"command/sub?game?js?" + subscene_toOpen,
        method:"GET",

        success:function(res){
            eval(res)
        },
    }
    )
    //document.getElementById("HTML_BODY").style.opacity = 0.5;
    document.getElementById("HTML_SUB").style.zIndex = 5;
}

function subsceneclose(){
    scene_subscene[1] = ""
    $.ajax({
        url:"command/close?subgame?html?" + subscene_toOpen,
        method:"GET",

        success:function(res){
            
            document.getElementById("HTML_SUB").innerHTML = res;
        },
    }
    )
    
    $.ajax({
        url:"command/close?subgame?js?" + subscene_toOpen,
        method:"GET",

        success:function(res){
            eval(res)
        },
    }
    )
    document.getElementById("HTML_BODY").style.opacity = 1;
    document.getElementById("HTML_SUB").style.zIndex = -1;
}


function scene_send(scene){

    

    $.ajax({
        url:"command/start?game?html?" + scene.toString(),
        method:"GET",

        success:function(res){
            
            document.getElementById("HTML_BODY").innerHTML = res;
        },
    }
    )
    
    $.ajax({
        url:"command/start?game?js?" + scene.toString(),
        method:"GET",

        success:function(res){
            eval(res)
        },
    }
    )
    document.getElementById("HTML_BODY").style.zIndex = 1;
    document.getElementById("HTML_SUB").style.zIndex = -1;
}




function character_move_send(a){
    $.ajax({
        url:"command/character?move?" + parseFloat(a.style.left).toString() + "?" +  parseFloat(a.style.top).toString(),
        method:"GET",

        success:function(res){
            eval(res)
        },
    }
    )
}

function SAVE_SAVEGAME(){
    if(didSaveFile == 0){
        $.ajax({
            url:"command/new?game?createFile",
            method:"GET",
    
            success:function(res){
                save_name = res;
                document.getElementById("SAVE_PANEL_INPUT").value = save_name
                didSaveFile = 1
            }
    
        })
    }
    else{
        for(var i=0;i<2;i++){
            $.ajax({
                url:"command/save?"+save_name+"?"+ i +"?" + scene_subscene[i],
                method:"GET",
            })
        }
        for(var i=0;i<8;i++){
            if(status_value.length > i){
                $.ajax({
                    url:"command/save?"+save_name+"?"+ (i+2).toString() +"?" + status_value[i][1],
                    method:"GET",
                })
            }
            else{
                $.ajax({
                    url:"command/save?"+save_name+"?"+ (i+2).toString() +"?" + "",
                    method:"GET",
                })
            }
        }
        for(var i=0;i<9;i++){
            $.ajax({
                url:"command/save?"+save_name+"?"+ (i+10).toString() +"?" + status_inventory_have[i],
                method:"GET",
            })
        }
    }
}

function SAVE_LOADGAME(){
    navigator.clipboard.readText().then((text) => save_name = text)
    document.getElementById("SAVE_PANEL_INPUT").value = save_name
    var valid = 0
    if(save_name.length < 10) return
    $.ajax({
        url:"command/save?"+save_name+"?valid_check",
        method:"GET",

        success:function(res){
            if(res == 0 || res == '0') return
            change_scenePlace = [-1,-1]
            change_sceneTargetFn = ["",""]
            for(var i=0;i<1;i++){
                if(i==0){
                    scene_subscene[0] = res;
                    $.ajax({
                        url:"command/load_save?"+save_name+"?"+i,
                        method:"GET",
                
                        success:function(res){
                            $.ajax({
                                url:"command/start?game?html?" + res.toString(),
                                method:"GET",
    
                                success:function(res2){
                                    
                                    document.getElementById("HTML_BODY").innerHTML = res2;
                                },
                            }
                            )
                        
                            $.ajax({
                                url:"command/start?game?js?" + res.toString(),
                                method:"GET",
    
                                success:function(res2){
                                    eval(res2)
                                },
                            }
                            )
                            document.getElementById("HTML_BODY").style.zIndex = 1;
                            document.getElementById("HTML_SUB").style.zIndex = -1;
                        },
                    })
                }
                if(i==1){
                    subscene_toOpen = res;
                    scene_subscene[1] = res;
                    $.ajax({
                        url:"command/sub?game?html?" + subscene_toOpen,
                        method:"GET",
                
                        success:function(res2){
                            
                            document.getElementById("HTML_SUB").innerHTML = res2;
                        },
                    }
                    )
                    
                    $.ajax({
                        url:"command/sub?game?js?" + subscene_toOpen,
                        method:"GET",
                
                        success:function(res2){
                            eval(res2)
                        },
                    }
                    )
                    
                    document.getElementById("HTML_SUB").style.zIndex = 5;
                }
                
            }
            for(var i=0;i<8;i++){
                $.ajax({
                    url:"command/load_save?"+save_name+"?"+(i+2).toString(),
                    method:"GET",
                    async:false,
                    success:function(res){
                        if(res.length < 1)return
                        status_value[i][1] = res
                    }
                })
                update_statusBar()
            }
            for(var i=0;i<9;i++){
                $.ajax({
                    url:"command/load_save?"+save_name+"?"+(i+10).toString(),
                    method:"GET",
                    async:false,
            
                    success:function(res){
                        if(res.length < 1)return
                        status_inventory_src[i] = res
                    },
                })
            }
        },
    })
    //console.log(valid)
    
    
}

var save_name = ""
var scene_subscene = ["",""]
var subscene_toOpen = ""
var status_value = []
var status_inventory_have = [0,0,0,0,0,0,0,0,0]
var status_inventory = []
var status_inventory_src = [0,0,0,0,0,0,0,0,0]
var AUDIOS_ = []
var AUDIOSSRC_ = []
var didSaveFile = 0
window.onload = new_save()

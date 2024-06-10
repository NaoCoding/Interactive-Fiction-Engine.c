function subsceneonclick(a){

    subscene_toOpen = a;
    subscene_send();

}

function sceneonclick(a){

    scene_send(a);


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
        url:"command/new?game?createFile",
        method:"GET",

        success:function(res){
            save_name = res;
        }

    })

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
    document.getElementById("HTML_BODY").style.opacity = 0.5;
    document.getElementById("HTML_SUB").style.zIndex = 5;
}

function subsceneclose(){
    
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

var save_name = ""
var subscene_toOpen = ""
window.onload = new_save()

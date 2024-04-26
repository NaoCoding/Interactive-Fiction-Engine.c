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
        url:"command/new_game_createFile",
        method:"GET",

        success:function(res){
            save_name = res;
        }

    })

    $.ajax({
        url:"command/new_game_html",
        method:"GET",

        success:function(res){
            document.getElementById("HTML_GENERAL").innerHTML = res;
        }

    })

    $.ajax({
        url:"command/new_game_js",
        method:"GET",

        success:function(res){
            eval(res)
        }

    })

}


function scene_send(scene){

    

    $.ajax({
        url:"command/start_game_html_" + scene.toString(),
        method:"GET",

        success:function(res){
            
            document.getElementById("HTML_BODY").innerHTML = res;
        },
    }
    )
    
    $.ajax({
        url:"command/start_game_js_" + scene.toString(),
        method:"GET",

        success:function(res){
            eval(res)
        },
    }
    )
}


function character_move_send(a){
    $.ajax({
        url:"command/character_move_" + parseFloat(a.style.left).toString() + "_" +  parseFloat(a.style.top).toString(),
        method:"GET",

        success:function(res){
            eval(res)
        },
    }
    )
}

var save_name = ""
window.onload = new_save()

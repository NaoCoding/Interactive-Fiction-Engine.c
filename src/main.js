function send(scene){

    

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


window.onload = send(0)

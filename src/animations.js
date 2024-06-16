var control = ""
var control_move = 0
var change_scenePlace = [-1,-1]
var change_sceneTargetFn = ["",""]
var control_movingAnimation = []
var control_standingAnimation = []
var lastcontrol_move = 0
var dialog_word = []
var dialogNow = 0
var statusOn = 0
var saveOn = 0
var buttonSound = new Audio("src/audio/button.mp3")


function PROCESS_inventoryNew(a){
    if(status_inventory.length < 9)status_inventory.push(a)

}

function PROCESS_inventoryHAVE(a){
    var index = -1
    for(var i=0;i<8;i++){
        if(status_inventory[i] == a){
            index = i;
            break;
        }
    }
    if(index == -1) return;
    status_inventory_have[index] = 1;
    updateInventory()
}

function updateInventory(){
    for(var i=0;i<9;i++){
        if(status_inventory_have[i] == 1){
            document.getElementById("STATUS_INVENTORY_" + (i+1).toString()).src = status_inventory_src[i]
        }
    }
}

function PROCESS_inventorySRC(a,b){
    var index = -1
    for(var i=0;i<8;i++){
        if(status_inventory[i] == a){
            index = i;
            break;
        }
    }
    if(index == -1) return;
    status_inventory_src[index] = b
}

function PROCESS_requireValueOption(a,b,c){
    var index = -1
    for(var i=0;i<status_value.length;i++){
        if(status_value[i][0] == a){
            index = i;
            break;
        }
    }
    if(index == -1)return;
    if(status_value[index][1] < b) document.getElementById("OPTIONBOX"+c).style.display="none"
    else document.getElementById("OPTIONBOX"+c).style.display="block"
}

function PROCESS_requireInventoryOption(a,b){
    var index = -1
    for(var i=0;i<status_value.length;i++){
        if(status_inventory[i] == a){
            index = i;
            break;
        }
    }
    if(index == -1)return;
    if(status_inventory_have[index] != 1) document.getElementById("OPTIONBOX"+b).style.display="none"
    else document.getElementById("OPTIONBOX"+b).style.display="block"
}

function PROCESS_STATUSADDVALUE(a,b,c){
    var index = -1
    for(var i=0;i<status_value.length;i++){
        if(status_value[i][0] == a){
            index = i;
            break;
        }
    }
    if(index == -1)return;

    for(var i=0;i<status_value[index][2].length;i++){
        if(status_value[index][2][i] == b) return
    }
    status_value[index][1] += c
    status_value[index][2].push(b)
    update_statusBar()
}

function PROCESS_statusNewValueSetup(a){
    if(status_value.length >= 8) return;
    status_value.push([a,0,[]])
    update_statusBar()
}

function update_statusBar(){

    for(var i=0;i<status_value.length;i++){
        document.getElementById("STATUS" + (i+1).toString() + "LABEL").style.display = "block"
        document.getElementById("STATUS" + (i+1).toString()).style.display = "block"
        document.getElementById("STATUS" + (i+1).toString() + "VALUE").style.display = "block"
        document.getElementById("STATUS" + (i+1).toString() + "LABEL").innerHTML = status_value[i][0]
        document.getElementById("STATUS" + (i+1).toString() + "VALUE").innerHTML = status_value[i][1]
        document.getElementById("STATUS" + (i+1).toString() + "LINK").style.width = status_value[i][1] + "%"
    }

}

async function screenfadeIn(tt){

    var s = document.getElementById("HTML_BODY")
    var f = document.body
    f.style.opacity = 0
    s.style.opacity = 0
    var time = 0
    var q = setInterval(() => {
        if(time == 50)clearInterval(q);
        s.style.opacity = (parseFloat(s.style.opacity) + 0.02).toString()
        f.style.opacity = (parseFloat(f.style.opacity) + 0.02).toString()
        time += 1
    },80)

}

async function screenfadeOutandIn(tt){

    var s = document.getElementById("HTML_BODY")
    var f = document.body
    f.style.opacity = 1
    s.style.opacity = 1
    var time = 0
    var q = setInterval(() => {
        if(time == 50)clearInterval(q);
        s.style.opacity = (parseFloat(s.style.opacity) - 0.02).toString()
        f.style.opacity = (parseFloat(f.style.opacity) - 0.02).toString()
        time += 1
    },40)

    while(time!=50){
        await delay(20)
    }

    f.style.opacity = 0
    s.style.opacity = 0
    time = 0
    var ar = setInterval(() => {
        if(time == 50 || s.style.opacity > 1)clearInterval(ar);
        s.style.opacity = (parseFloat(s.style.opacity) + 0.02).toString()
        f.style.opacity = (parseFloat(f.style.opacity) + 0.02).toString()
        time += 1
    },40)


}

async function change_sceneCharacterFunction(){

    var q = setInterval(() =>{
        if(control.length > 1){
            var p = document.getElementById(control)
            if(parseFloat(p.style.left) >= (95 - parseFloat(p.style.width))  && change_scenePlace[1] != -1){
                change_scenePlace = [-1,-1]
                p.style.display = "none"
                scene_send(change_sceneTargetFn[1])
                change_sceneTargetFn = ["",""]
            }
            if(parseFloat(p.style.left) <= (5)  && change_scenePlace[0] != -1){
                change_scenePlace = [-1,-1]
                p.style.display = "none"
                scene_send(change_sceneTargetFn[0])
                change_scenePlace = [-1,-1]
                change_sceneTargetFn = ["",""]
            }
        }
        
    },40)


}

async function toggleStatus(){
    buttonSound.play();
    if(statusOn == 0){
        statusOn = 1
        document.getElementById("CHARACTER_STATUS").style.display = "block"
    }
    else{
        statusOn = 0
        document.getElementById("CHARACTER_STATUS").style.display = "none"
    }

}

async function toggleSave(){
    buttonSound.play();
    if(saveOn == 0){
        saveOn = 1
        document.getElementById("SAVE_PANEL").style.display = "block"
    }
    else{
        saveOn = 0
        document.getElementById("SAVE_PANEL").style.display = "none"
    }

}

async function PROCESS_playerControlFunction(){
    var key = event.keyCode
    var p = document.getElementById(control)
    if(key == 69) toggleStatus()
    if(key == 66) toggleSave()
    if((key==37 || key==65) && control.length > 0){
    if(parseInt(p.style.left) > 1){p.style.left = (parseInt(p.style.left) - 1).toString() + "%"
    p.style.transform = ""
    control_move = 1;}
    }
    else if((key==39 || key==68) && control.length > 0){
    if(parseInt(p.style.left) + parseInt(p.style.width) < 100){p.style.left = (parseInt(p.style.left) + 1).toString() + "%"
    p.style.transform = "scaleX(-1)"
    control_move = 1;}}
    else return
    if(lastcontrol_move!=control_move){
    if(control_move==1){
    PROCESS_characterMovingAnimation(control,0,0,200,control_movingAnimation,0)}else{
    PROCESS_characterMovingAnimation(control,0,0,200,control_standingAnimation,1)}
    lastcontrol_move = control_move}
    
}

async function PROCESS_playerControlFunction2(){
    var key = event.keyCode
    var p = document.getElementById(control)
    if((key==37 || key==65) && control.length > 0){
    
    p.style.transform = ""
    control_move = 0;
    }
    else if((key==39 || key==68) && control.length > 0){
    
    p.style.transform = "scaleX(-1)"
    control_move = 0;}
    else return
    if(control_move==1){
    PROCESS_characterMovingAnimation(control,0,0,200,control_movingAnimation,0)}else{
    PROCESS_characterMovingAnimation(control,0,0,200,control_standingAnimation,1)}
    lastcontrol_move = control_move}

function delay(n) {
    return new Promise(function (resolve) {
        setTimeout(resolve, n);
    });
}

async function PROCESS_contentAppearAnimation(a,b,c){

    while(dialogNow == 1) await new Promise(function (resolve) {
        setTimeout(resolve, 5);
    });

    await new Promise((resolve) =>{
        const typingSound = new Audio("src/audio/typingSound.mp3")
        typingSound.play()
        var fade = document.getElementById(a);
        dialogNow = 1
        fade.innerHTML = ""
        var tic = 0
        var q = setInterval(() => {
            fade.innerHTML += b[0];
            if(fade.innerHTML.length %80 == 0 && fade.innerHTML.length>=80) tic = 1
            if(tic == 1 && b[0] == " "){
                fade.innerHTML += '<br>'
                tic  = 0}
            b = b.substring(1);
            if(b.length == 0){
                typingSound.pause()
                typingSound.currentTime = 0
                clearInterval(q)
                
            }
        }, c);

        async function skip() {
            document.removeEventListener("click", skip);
            typingSound.pause()
            typingSound.currentTime = 0
            clearInterval(q);
            var toBr = 0
            for(var i=0;i<b.length;i++){
                fade.innerHTML += b[i]
                if(fade.innerHTML.length %80 == 0 && fade.innerHTML.length>=80){
                   toBr = 1
                }
                if(toBr == 1 && b[i] == " "){
                    fade.innerHTML += '<br>'
                    toBr = 0
                }
            }
            resolve();
        }

        document.addEventListener("click", skip);

    })
    dialogNow = 0

}

function PROCESS_characterMovingAnimation(a,b,c,d,e,f){
    var qs = document.getElementById(a);
    var cc = 0;
    var q = setInterval(() => {
        qs.src=e[cc]
        cc += 1
        if(cc == e.length) cc = 0
        if(control_move == f) clearInterval(q)
    }, d);}

document.onkeydown=PROCESS_playerControlFunction
document.onkeyup=PROCESS_playerControlFunction2
change_sceneCharacterFunction()
var control = ""
var control_move = 0
var change_scenePlace = [-1,-1]
var change_sceneTargetFn = ["",""]
var control_movingAnimation = []
var control_standingAnimation = []
var lastcontrol_move = 0

async function screenfadeIn(tt){

    var s = document.body
    s.style.opacity = 0
    var time = 0
    var q = setInterval(() => {
        if(time == 50)clearInterval(q);
        s.style.opacity = (parseFloat(s.style.opacity) + 0.02).toString()
        time += 1
    },40)

}

async function change_sceneCharacterFunction(){

    var q = setInterval(() =>{
        if(control.length > 1){
            var p = document.getElementById(control)
            if(parseFloat(p.style.left) >= (95 - parseFloat(p.style.width))  && change_scenePlace[1] != -1){
                change_scenePlace = [-1,-1]
                p.style.left = "0%"
                p.style.display = "none"
                control = ""
                scene_send(change_sceneTargetFn[1])
                change_sceneTargetFn = ["",""]
            }
        }
        
    },40)


}

async function PROCESS_playerControlFunction(){
    var key = event.keyCode
    var p = document.getElementById(control)
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

async function PROCESS_contentAppearAnimation(a,b,c){
    var fade = document.getElementById(a);
    //await new Promise(r => setTimeout(r,800))
    fade.innerHTML = ""

    var q = setInterval(() => {
        fade.innerHTML += b[0];
        if(fade.innerHTML.length%60 == 0){
            fade.innerHTML += '/n'}
        b = b.substring(1);
        if(b.length == 0) clearInterval(q)
    }, c);}

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
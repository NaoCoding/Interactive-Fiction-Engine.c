document.getElementById("DIALOG_BOX").style.display="block"
document.getElementById("DIALOG_BOX_BG").style.display="block"
document.getElementById("DIALOG_BOX_SPEAKER").style.display="block"
document.getElementById("DIALOG_BOX_CONTENT").style.display="block"
document.getElementById("HTML_SUB").src="../example-game/images/scene01/scene01.png"
PROCESS_contentAppearAnimation("DIALOG_BOX_CONTENT","Hello world",30)
document.getElementById("DIALOG_BOX_SPEAKER").innerHTML="Roku"
document.getElementById("Mancenormal_stand").style.display="block"
document.getElementById("Mancenormal_stand").style.zIndex=9
document.getElementById("ManceMOVINGIMG").style.display="none"
PROCESS_contentAppearAnimation("DIALOG_BOX_CONTENT","Goodbye world",30)
document.getElementById("DIALOG_BOX_CONTENT").onclick=function(){subsceneclose();}

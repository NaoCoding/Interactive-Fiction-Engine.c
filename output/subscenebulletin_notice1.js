document.getElementById("DIALOG_BOX").style.display="block"
document.getElementById("DIALOG_BOX_BG").style.display="block"
document.getElementById("DIALOG_BOX_SPEAKER").style.display="block"
document.getElementById("DIALOG_BOX_CONTENT").style.display="block"
PROCESS_contentAppearAnimation("DIALOG_BOX_CONTENT","Attention All Students and Staff :",30)
document.getElementById("DIALOG_BOX_SPEAKER").innerHTML="Bulletin"
document.getElementById("ManceMOVINGIMG").style.display="none"
document.getElementById("DIALOG_BOX_CONTENT").onclick=function() {subsceneonclick("subscenebulletin_notice2")}

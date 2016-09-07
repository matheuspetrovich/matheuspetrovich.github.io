
function popTela(x) {
	
	document.getElementById("tela").style.marginTop = (x-1)*200+"px";
	document.getElementById("tela").style.visibility = "visible";
  document.getElementById("tela").style.zIndex = "1000";
	document.getElementById("tela").style.backgroundImage = "url('livros7.png')";
  document.getElementById("fecha").style.display = "";
  document.getElementById("fecha").style.zIndex = "1001";
  
  
	document.getElementById("tEsq").innerHTML = document.getElementById("t"+x).innerHTML;
	document.getElementById("pEsq").innerHTML = document.getElementById("p"+x).innerHTML;
	document.getElementById("dir").innerHTML = "Texto "+x*2;
  
}

function fecha(){
	document.getElementById("tela").style.visibility = "hidden";
	document.getElementById("fecha").style.display = "none";
}

function mP(){
	if(document.getElementById("menuP").style.marginLeft == "275px"){
		document.getElementById("menuL").style.visibility = "hidden";
  	document.getElementById("menuP").style.marginLeft = "-10px";
	}else{	
		document.getElementById("menuL").style.visibility = "visible";
  	document.getElementById("menuP").style.marginLeft = "275px";
  }
	
}


function popTela(x) {
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

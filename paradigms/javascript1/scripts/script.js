/*
Nathan Vahrenberg
CSE30332 Programming Paradigms
21 March 2016
*/

var p = document.createElement("p");
p.setAttribute("id","name");
var text = document.createTextNode("who?");
p.appendChild(text);
document.getElementById("div").appendChild(p);

function changeName(){
	document.getElementById("name").innerHTML = "Nathan Vahrenberg";
}
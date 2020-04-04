/*
Nathan Vahrenberg
CSE30332 Programming Paradigms
JavaScript 3
30 March 2016
*/

var Item = {
    addToDocument:function(){
    	document.getElementById("div").appendChild(this.item);
    }
};

function Label(text, id){

	this.item = document.createElement("p");
	this.item.setAttribute("id",id);
	var t = document.createTextNode(text);
	this.item.appendChild(t);
	
	this.setText = function(text){
		this.item.t(text);
	}

}

function Button(text, id){
	this.item = document.createElement("button");
	this.item.setAttribute("id",id);
	var t = document.createTextNode(text);
	this.item.appendChild(t);

	this.addClickEventHandler = function(handler, args){
		document.getElementById(this.item.id).onmouseup = function(){handler(args);};
	}
}

function changeText(args){
	label = args[0];
	var request = new XMLHttpRequest();
    request.open("GET", "http://student03.cse.nd.edu:40001/movies/32", true);
    request.onload = function(){
    	text = request.responseText;
		document.getElementById(label.item.id).innerHTML = text;
    }
    request.send();
}
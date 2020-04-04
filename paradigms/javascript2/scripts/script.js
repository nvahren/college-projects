/*
Nathan Vahrenberg
CSE30332 Programming Paradigms
JavaScript 2
23 March 2016
*/


var Item = {
    addToDocument:function(){
    	document.getElementById("div").appendChild(this.item);
    }
};

var Label = {
	createLabel:function(text, id){
		this.item = document.createElement("p");
		this.item.setAttribute("id",id);
		var t = document.createTextNode(text);
		this.item.appendChild(t);
	},
	setText:function(text){
		this.item.t(text);
	}
}

var Button = {
	createButton:function(text, id){
		this.item = document.createElement("button");
		this.item.setAttribute("id",id);
		var t = document.createTextNode(text);
		this.item.appendChild(t);
	},
	addClickEventHandler:function(handler, args){
		document.getElementById(this.item.id).onmouseup = function(){handler(args);};
	}
}

function changeText(args){
	text = args[0];
	label = args[1];
	document.getElementById(label.item.id).innerHTML = text;
}

Label.__proto__ = Item;
Button.__proto__ = Item;

Label.createLabel("who?","label");
Label.addToDocument();

Button.createButton("click here","button");
args = ["Nathan Vahrenberg",Label];
Button.addToDocument();
Button.addClickEventHandler(changeText, args);
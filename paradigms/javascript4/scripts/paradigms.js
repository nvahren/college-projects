/*
Nathan Vahrenberg
CSE30332 Programming Paradigms
JavaScript 4
1 April 2016
*/

var movie_id = 0;

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

function Dropdown(dict, id, selected){
	this.item = document.createElement("select");
	this.item.setAttribute("id",id);
	this.item.options.add( new Option("Select a rating",0), true, true);
	for (var i = dict.length - 1; i >= 0; i--) {
		this.item.options.add( new Option(dict[i],parseInt(i) + 1) );
	}

	this.addOnChange = function(func, args){
		document.getElementById(this.item.id).onchange = function(){func(args);};
	}

	this.getSelected = function(){
		return this.selected;
	}
}

function changeText(args){
	label = args[0];
	var request = new XMLHttpRequest();
    request.open("GET", "http://student03.cse.nd.edu:40001/movies/32", true);
    request.onload = function(){
    	text = request.responseText;
		document.getElementById(label.item.id).innerHTML = text;
		var data = JSON.parse(text);
		movie_id = data.id;
		
    }
    request.send();
}

function onChange(args){
	dropdown = args[0];
	dropdown.selected = document.getElementById(dropdown.item.id).value
}

function submitVote(args){
	if(movie_id != 0){
		vote = parseInt(args[0].getSelected());
		if(isNaN(vote) || vote == 0){
			alert("Please select a rating");
		}else{
			var request = new XMLHttpRequest();
			request.open("PUT", "http://student02.cse.nd.edu:40001/recommendations/32");
			request.onload = function(){
				text = request.responseText;
				console.log(text);
			}
			var json = { "movie_id":String(movie_id), "rating":String(vote), "apikey":"3rEMq572cB" };
			console.log(JSON.stringify(json));
			request.send(JSON.stringify(json));
		}	
	}else{
		alert("No movie selected");
	}
}
/*
Nathan Vahrenberg
CSE30332 Programming Paradigms
AJAX
8 April 2016
*/

var SITE_URL = "http://student02.cse.nd.edu:40042";
var MOVIES_URL = SITE_URL + "/movies/";
var RATINGS_URL = SITE_URL + "/ratings/";
var RECOMMENDATIONS_URL = SITE_URL + "/recommendations/";
var IMAGES_URL = "http://www.cse.nd.edu/~cmc/teaching/cse30332_sp16/images";

var movie_id = 0;
var user_id = 12;

var Item = {
    addToDocument:function(div){
    	document.getElementById(div).appendChild(this.item);
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

function loadMovie(args){
	label = args[0];
	rating = args[1];
	poster = args[2];
	var img;

	var request = new XMLHttpRequest();
    request.open("GET", RECOMMENDATIONS_URL + user_id, true);
    request.onload = function(){
    	var data = JSON.parse(request.responseText);
    	movie_id = data.movie_id;
    
    	var info_request = new XMLHttpRequest();
    	info_request.open("GET", MOVIES_URL + movie_id, true);
    	info_request.onload = function(){
    		text = info_request.responseText;
			var data = JSON.parse(text);
			document.getElementById(label).innerHTML = data.title;
    		document.getElementById(poster).src = IMAGES_URL + data.img;
   
		}
		info_request.send();

		var rating_request = new XMLHttpRequest();
		rating_request.open("GET", RATINGS_URL + movie_id, true);
    	rating_request.onload = function(){
    		text = rating_request.responseText;
			var data = JSON.parse(text);
			document.getElementById(rating).innerHTML = data.rating;	
    	}
    	rating_request.send();
    }
    request.send();
}

function onChange(args){
	dropdown = args[0];
	dropdown.selected = document.getElementById(dropdown.item.id).value
}

function submitVote(args){
	if(movie_id != 0){
		vote = parseInt(args[0]);
		var request = new XMLHttpRequest();
		request.open("PUT", RECOMMENDATIONS_URL + user_id);
		request.onload = function(){
			text = request.responseText;
			loadMovie(["title","rating","poster"]);
		}
		var json = { "movie_id":String(movie_id), "rating":String(vote), "apikey":"3rEMq572cB" };
		request.send(JSON.stringify(json));
	}else{
		alert("No movie selected");
	}
}
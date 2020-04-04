/*
Nathan Vahrenberg
CSE30332 Programming Paradigms
AJAX
8 April 2016
*/

Label.prototype = Item;
Button.prototype = Item;
Dropdown.prototype = Item;

var title_label = new Label("title","title");
var rating_label = new Label("rating","rating");
var up_button = new Button("Up","up_button");
var down_button = new Button("Down","down_button");

left_div = document.createElement("div");
left_div.setAttribute("id", "left_div");
left_div.setAttribute("class", "button_div");
document.getElementById("main").appendChild(left_div);

middle_div = document.createElement("div");
middle_div.setAttribute("id", "middle_div");
middle_div.setAttribute("class", "movie_div");
document.getElementById("main").appendChild(middle_div);

right_div = document.createElement("div");
right_div.setAttribute("id", "right_div");
right_div.setAttribute("class", "button_div");
document.getElementById("main").appendChild(right_div);

args = ["5"];
up_button.addToDocument("left_div");
up_button.addClickEventHandler(submitVote, args);

args = ["1"];
down_button.addToDocument("right_div");
down_button.addClickEventHandler(submitVote, args);

title_label.addToDocument("middle_div");
poster = document.createElement("img");
poster.setAttribute("id","poster");
document.getElementById("middle_div").appendChild(poster);
rating_label.addToDocument("middle_div");

loadMovie([title_label.item.id,rating_label.item.id,poster.id]);
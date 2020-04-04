/*
Nathan Vahrenberg
CSE30332 Programming Paradigms
JavaScript 4
1 April 2016
*/

Label.prototype = Item;
Button.prototype = Item;
Dropdown.prototype = Item;

var movie_label = new Label("which movie?","label");
var get_movie_button = new Button("Get Movie","button");
var opinion_label = new Label("I thought this movie was...","opinionlabel");
var dropdown = new Dropdown(["1 star","2 star","3 star","4 star","5 star"],"dropdown",0);
var submit_button = new Button("Submit","submitbutton");

movie_label.addToDocument();

args = [movie_label];
get_movie_button.addToDocument();
get_movie_button.addClickEventHandler(changeText, args);

opinion_label.addToDocument();

onchange_args = [dropdown];
dropdown.addToDocument();
dropdown.addOnChange(onChange,onchange_args);

submit_args = [dropdown];
submit_button.addToDocument();
submit_button.addClickEventHandler(submitVote, submit_args);
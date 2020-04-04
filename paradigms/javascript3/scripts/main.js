/*
Nathan Vahrenberg
CSE30332 Programming Paradigms
JavaScript 3
30 March 2016
*/

Label.prototype = Item;
Button.prototype = Item;

var label = new Label("who?","label");
var button = new Button("click here","button");

label.addToDocument();

args = [label];
button.addToDocument();
button.addClickEventHandler(changeText, args);
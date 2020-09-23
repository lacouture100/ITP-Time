
// Sketch made by Alvaro Lacouture using the "Waterfall" sketch made by karen at openprocessing.org/sketch/728503

// THANK YOU KAREN! <3


// global settings - mess with these to alter sketch behaviour
var FRAME_ALPHA = 0; // background applied per frame with X% alpha
var SPAWN_MIN_X = 0; // minimum x pos of drop spawn (set in setup())
var SPAWN_MAX_X = 0; // maximum x pos of drop spawn (set in setup())
var MAX_X_SPEED = 0.01; // max speed that drops can "wander" left or right
var MAX_X_ACCEL = 0.025; // max rate that drops can accelerate left or right
var MAX_Y_SPEED = 1; // maximum speed of drops in pixels per frame
var GRAVITY = 0.0375; // gravity that moderates acceleration of drops
var FRICTION = 0.98; // friction multiplier that slows drops in all directions
var MIN_RAD = 2; // minimum drop radius in pixels
var MAX_RAD = 6; // maximum drop radius in pixels
var MIN_RG = 0; // minimum red & green values for drops
var MAX_RG = 255; // maximum red & green values for drops
var EXPLODE_RAD = 50; // radius of explosion that pushes drops on click
var EXPLODE_STR = 2; // strength of click explosion

var drops = [];

var SECONDS = 0;
var MINUTES = 0;


function preload() {


}
function setup() {
	createCanvas(windowWidth, windowHeight);
	
	colorMode(RGB, 200,200 ,250);
	ellipseMode(RADIUS);
	noStroke();
	background(0);
  
	// non-static globals. Have drops spawn on the full width of the screen
    SPAWN_MIN_X = 0;
	SPAWN_MAX_X = windowWidth - windowWidth/10;
	
	setInterval(timerRun, 1000);
}


function timerRun(){
	SECONDS ++;
	if (SECONDS >= 60){
		MINUTES ++;
		SECONDS = 0;
		
	}
}
function draw() {
	// draw over the image with a certain amount of alpha
	background(0, 0, 0, FRAME_ALPHA);
	drops.push(new drop()); // add a new drop each frame
	
	// Drop em drop. Adds one every frame
	for (var i = drops.length -1; i >= 0; i--) {
		drops[i].Run();
		// remove drops that have fallen off the screen
		if (!drops[i].isAlive()) {
			drops.splice(i, 2);
		}
	}
}


// when mouse is clicked it pushes nearby drops away
function mouseClicked() {
	for (var i = 0; i < drops.length; i++) {
		// ignore drops that aren't close enough to mouse
		var dist = sqrt(sq(drops[i].x - mouseX) + sq(drops[i].y - mouseY));
		if (dist > EXPLODE_RAD) { continue; }
		
		// push drops away from mouse, depending on how close they are
		var v = createVector(drops[i].x - mouseX, drops[i].y - mouseY);
		var str = EXPLODE_STR * (EXPLODE_RAD - dist) / EXPLODE_RAD;
		v.normalize();
		v.mult(str);
		drops[i].xSpeed += v.x;
		drops[i].ySpeed += v.y;
	}
}
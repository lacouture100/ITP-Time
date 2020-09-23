// drop object
function drop() {
	this.x = random(SPAWN_MIN_X, SPAWN_MAX_X); // x pos of drop
	this.y = 0; // y pos of drop
	this.rad = random(MIN_RAD, MAX_RAD); // drop radius
  
	this.xSpeed = 0; // drop wander speed
	this.ySpeed = 0; // drop fall speed
  
	this.r = random(MIN_RG, MAX_RG); // red & green colour of drop
	this.g = random(MIN_RG, MAX_RG); // red & green colour of drop
	this.b = 150; // blue is always max
  
	this.millisTime;
	this.minuteTimer = 0;
	
	this.Run = function() {
		this.Update();
		this.Display();
	}
		

	
	// animate the drop
	this.Update = function() {
		// apply gravity to drop
		this.ySpeed += GRAVITY;
		
		// make drop "wander" left & right
		var a = random(-MAX_X_ACCEL, MAX_X_ACCEL);
		this.xSpeed += a;
		
		// apply friction and movement
		this.xSpeed *= FRICTION;
		this.ySpeed *= FRICTION;
		this.y += this.ySpeed;
		this.x += this.xSpeed;
      
		this.millisTime = millis();
		
	}
	
	// draw the time drop
	this.Display = function() {
		fill(this.r, this.g, this.b, 180);
        this.TimeDisplay(this.x, this.y);
	}
	// Display time
    this.TimeDisplay = function(posx,posy){
        textSize(25)
		strokeWeight(4);
		stroke(51);

		// 
		if (SECONDS >= 60) {
			
			text(`0${MINUTES}:${SECONDS}:${this.millisTime.toString().slice(-2)}`, posx,posy);
		  }
		if (SECONDS >= 10) {
			text(`0${MINUTES}:${SECONDS}:${this.millisTime.toString().slice(-2)}`, posx,posy);
		  }
		  if (SECONDS < 10) {
			text(`0${MINUTES}:0${SECONDS}:${this.millisTime.toString().slice(-2)}`, posx,posy);
		  }
		  
	}

	

	// check if drop is still alive or not. This means if it is still on the screen
	this.isAlive = function() {
		return this.y < random(0,windowWidth*15) + this.rad;
	}
}

/**
 * This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
 * http://creativecommons.org/licenses/by-nc-sa/4.0/
 * 
 * The original source can be found here:
 * https://p5js.org/examples/simulate-particle-system.html
 * 
 * It was modified to run with DOjS by Andre Seidelt <superilu@yahoo.com>.
 */
Require('p5');

ps = null;

/*
** This function is called once when the script is started.
*/
function Setup() {
	SetFramerate(300);

	ps = new ParticleSystem(new PVector(SizeX() / 2, 50));
}

/*
** This function is repeatedly until ESC is pressed or Stop() is called.
*/
function Loop() {
	ClearScreen(EGA.BLACK);

	ps.addParticle();
	ps.run();
}

/*
** This function is called on any input.
*/
function Input(event) {
}

function random(min, max) {
	return (Math.random() * (max - min)) + min;
}

//////
// class ParticleSystem
function ParticleSystem(position) {
	this.origin = position.copy();
	this.particles = [];
}
ParticleSystem.prototype.addParticle = function () {
	if (this.particles.length < 128) {
		this.particles.push(new Particle(this.origin));
	}
}
ParticleSystem.prototype.run = function () {
	for (var i = this.particles.length - 1; i >= 0; i--) {
		var p = this.particles[i];
		p.update();
		if (p.isDead()) {
			this.particles.splice(i, 1);
		}
		p.display();
	}
}

//////
// class Particle
function Particle(l) {
	this.acceleration = new PVector(0, 0.05);
	this.velocity = new PVector(random(-1, 1), random(-2, 0));
	this.position = l.copy();
	this.lifespan = 128;
}
Particle.prototype.update = function () {
	// Method to update position
	this.velocity.add(this.acceleration);
	this.position.add(this.velocity);
	this.lifespan -= 1;
}
Particle.prototype.display = function () {
	// Method to display
	var c = new Color(this.lifespan, this.lifespan, this.lifespan * 2);
	FilledCircle(this.position.x, this.position.y, 4, c);
}
Particle.prototype.isDead = function () {
	// Is the particle still useful?
	if (this.lifespan <= 0) {
		return true;
	} else {
		return false;
	}
}

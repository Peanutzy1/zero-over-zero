// this script is used to draw stuff in the canvas
// "if this doesnt exist you'd be second guessing where the button is" - peanut

'use strict';
import { world, screen } from './vars.js';

export function draw() {
  drawWorld();
  drawUI();
}

function drawWorld() {
  world.ctx.setTransform(1, 0, 0, 1, 0, 0); // resets zoom / pan
  world.ctx.clearRect(0, 0, window.innerWidth, window.innerHeight);
  world.ctx.translate(window.innerWidth / 2, window.innerHeight / 2); // center the canvas
  world.ctx.scale(world.scale, world.scale);
  // i want world.x and world.y to be canvas pos not offsets
  world.ctx.translate(-world.x, -world.y);
  world.viewableButtons.forEach(button => button.draw()); // draw EVERYTHING!!!!
}

function drawUI() {
  screen.ctx.strokeStyle = '#808080';
  screen.ctx.lineWidth = 1;
  screen.ctx.lineCap = 'square';
  const centerX = Math.floor(screen.canvas.width / 2) + 0.5;
  const centerY = Math.floor(screen.canvas.height / 2) + 0.5;
  const size = 10;
  screen.ctx.beginPath();

  screen.ctx.beginPath();
  screen.ctx.moveTo(centerX - size, centerY);
  screen.ctx.lineTo(centerX + size, centerY);
  screen.ctx.moveTo(centerX, centerY - size);
  screen.ctx.lineTo(centerX, centerY + size);
  screen.ctx.stroke();
}

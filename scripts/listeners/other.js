// this script includes other listeners
// "BORING" - peanut

'use strict';
import { world, screen, keyStates } from '../vars.js';

function resizeCanvas() {
  const width = window.innerWidth;
  const height = window.innerHeight;
  
  // resizes canvas and also style so it doesnt scale canvas
  // "i swear i will change this" -peanut
  world.canvas.style.width = `${width}px`;
  world.canvas.style.height = `${height}px`;
  world.canvas.width = width;
  world.canvas.height = height;
  screen.canvas.style.width = `${width}px`;
  screen.canvas.style.height = `${height}px`;
  screen.canvas.width = width;
  screen.canvas.height = height; 
}

export function resizeInit() {
  resizeCanvas();
  addEventListener('resize', () => {
    resizeCanvas();
  });
}

export function focusInit() {
  window.addEventListener('blur', () => {
    for (const key in keyStates) { keyStates[key] = false; }
  });
}

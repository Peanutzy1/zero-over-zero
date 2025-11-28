// this script includes other listeners
// "BORING" - peanut

'use strict';
import { world, screen, keyStates } from '../vars.js';

function resizeCanvas() {
  const width = window.innerWidth;
  const height = window.innerHeight;

  const dpr = window.devicePixelRatio || 1;

  // WORLD
  world.canvas.style.width = `${width}px`;
  world.canvas.style.height = `${height}px`;
  world.canvas.width = width * dpr;
  world.canvas.height = height * dpr;
  world.ctx.setTransform(dpr, 0, 0, dpr, 0, 0); 
  // this resets scaling every resize so camera math works cleanly

  // SCREEN/UI
  screen.canvas.style.width = `${width}px`;
  screen.canvas.style.height = `${height}px`;
  screen.canvas.width = width * dpr;
  screen.canvas.height = height * dpr;
  screen.ctx.setTransform(dpr, 0, 0, dpr, 0, 0);
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

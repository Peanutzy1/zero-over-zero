// this script is used to initialize the game
// "this part is what the thing actually runs xdd" - peanut

'use strict';

import { mouseInit } from './listeners/mouse.js';
import { focusInit, resizeInit } from './listeners/other.js';
import { keyboardController, keyboardInit } from './listeners/keyboard.js';
import { draw } from './render.js';
import { pointTreeSetup } from './setup/pointTree.js';
import { screen } from './vars.js';
import { updateCurrencies } from './classes/currency.js';

// starts everything
// "i love it when it has lowest amount of lines but technically runs the most" - peanut 
function start() {
  pointTreeSetup();
  mouseInit();
  resizeInit();
  focusInit();
  keyboardInit();
  requestAnimationFrame(gameLoop);
}

// game loop, runs every frame
// "isnt it very loopi de doop?" - peanut
let lastTime = 0;
function gameLoop(currentTime) {
  keyboardController();
  updateCurrencies();
  screen.deltaTime = (currentTime - lastTime) / 1000;
  lastTime = currentTime;
  draw();
  requestAnimationFrame(gameLoop);
}

start();

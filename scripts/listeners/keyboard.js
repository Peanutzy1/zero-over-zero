// this file contains keyboard listeners and keybinds
// because a game with only mouse control sucks (trust me i tried doing mouse only controls)

'use strict';

import { keyStates, world, screen } from '../vars.js';
import { buttonScanner } from '../utils.js';

// this thing logs if a key is pressed or not, very useful but still have a bug
// like when you press on a key and then quickly unfocus the tab via switching to an another one
// or like unfocusing it would make it sustain even tho its released
export function keyboardInit() {
  window.addEventListener('keydown', key => {
    keyStates[key.key] = true;
  });
  window.addEventListener('keyup', key => {
    keyStates[key.key] = false;
  });
}

// read screen.keystates every frame and then apply action, is in ../main.js inside of gameloop()
export function keyboardController() {
  let movementSpeed = 3;
  // space for moving fast because players would complain if there's only 1 speed
  if(keyStates[' ']) { movementSpeed *= 2; }
  // accounting for the zoom and the deltaTime to remain constant no matter the situation
  const actualSpeed = movementSpeed / world.scale * screen.deltaTime * 60;
  // your movement keys
  if(keyStates['a']) { world.x += actualSpeed; }
  if(keyStates['d']) { world.x -= actualSpeed; }
  if(keyStates['w']) { world.y += actualSpeed; }
  if(keyStates['s']) { world.y -= actualSpeed; }
  // activates buttonScanner() for when viewport moves
  // oh and buttonScanner() scans for buttons inside viewport btw
  if(
    keyStates['w'] ||
    keyStates['a'] ||
    keyStates['s'] ||
    keyStates['d']
  ) { buttonScanner(); }
  // more binds later
}

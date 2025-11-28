// this file contains keyboard listeners and keybinds
// "because a game with only mouse control sucks" - peanut

'use strict';

import { keyStates, world, screen } from '../vars.js';
import { buttonScanner } from '../utils.js';

// logs if a key is pressed, very useful
// bug: when you press on a key and then quickly unfocus the tab via switching to an another one
// or unfocusing the window would make keypress sustain after released
export function keyboardInit() {
  window.addEventListener('keydown', key => {
    keyStates[key.key] = true;
  });
  window.addEventListener('keyup', key => {
    keyStates[key.key] = false;
  });
}

// reads screen.keystates every frame and then apply action, 
// is in ../main.js inside of gameloop()
export function keyboardController() {
  let movementSpeed = 8;
  if(keyStates[' ']) { movementSpeed *= 2; } // speedy mode via space

  // smooths out movement speed
  const actualSpeed = movementSpeed / world.scale * screen.deltaTime * 60;

  if(keyStates['a']) { world.x -= actualSpeed; }
  if(keyStates['d']) { world.x += actualSpeed; }
  if(keyStates['w']) { world.y -= actualSpeed; }
  if(keyStates['s']) { world.y += actualSpeed; }

  // activates buttonScanner() for when viewport moves
  // oh and buttonScanner() scans for buttons inside viewport btw - peanut
  if(
    keyStates['w'] ||
    keyStates['a'] ||
    keyStates['s'] ||
    keyStates['d']
  ) { buttonScanner(); }
  // more binds later
}

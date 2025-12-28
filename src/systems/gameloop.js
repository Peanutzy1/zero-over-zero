/**
 * This file is for the gameloop that runs.. a lot
 * "loopi deloop" -peanut
 */

import { nut } from '../data-storage.js';
import { update } from './update.js';

export function loopi(currentTime) {
  nut.dt = currentTime - nut.lastTime;
  nut.lastTime = currentTime;

  update();
 
  if (nut.dt >= 250000) nut.dt = 250000
  update(nut.dt);

  requestAnimationFrame(loopi);
}

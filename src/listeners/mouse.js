// this script starts mouse logics like moving and scrolling
'use strict';
import { world, screen, mouseStates } from '../vars.js';
import { screenToWorld, buttonScanner } from '../utils.js';
export function mouseInit() {
  buttonScanner();
  window.addEventListener('mousemove', e => {
    screen.mouse.x = e.clientX;
    screen.mouse.y = e.clientY;
    const mouseWorldCoords = screenToWorld(e.clientX, e.clientY); 

    world.mouse.x = mouseWorldCoords.x; 
    world.mouse.y = mouseWorldCoords.y;
    world.viewableButtons.forEach(button => { button.hovered = button.isUnderMouse(); });
  });

  window.addEventListener('mousedown', () => {
    mouseStates.leftDown = true;
    world.viewableButtons.forEach(button => { button.pressed = button.isUnderMouse(); });
  });

  window.addEventListener('mouseup', () => {
    mouseStates.leftDown = false;
    world.viewableButtons.forEach(button => {
      if(button.isInViewport() && button.pressed && button.isUnderMouse()) {
        button.onClick();
      } else {
        button.pressed = false;
      }
    });
  });

  window.addEventListener('contextmenu', e => {
    e.preventDefault();
  });

  window.addEventListener('wheel', e => {
    e.preventDefault();
    const zoomFactor = 1.1;
    if (e.deltaY < 0) { world.scale *= zoomFactor; } else { world.scale /= zoomFactor; }
    world.scale = Math.min(Math.max(world.scale, 0.1), 100);
    buttonScanner();            
  }, { passive: true });
}

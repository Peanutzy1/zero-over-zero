// this script starts mouse logics like moving and scrolling
'use strict';
import { world, screen } from '../vars.js';
import { screenToWorld, buttonScanner } from '../utils.js';
export function mouseInit() {
  let leftMouseDown = false;
  let _rightMouseDown = false;
  let mouseUp = false;
  // add "let _lastX = 0; let _lastY = 0" for mouse panning
  buttonScanner();
  buttonHoverController(screen.viewableButtons, leftMouseDown, mouseUp);
  window.addEventListener('mousemove', e => {
    screen.mouse.x = e.clientX;
    screen.mouse.y = e.clientY;
    const mouseWorldCoords = screenToWorld(e.clientX, e.clientY);
    /* if (_rightMouseDown) {
      world.x -= (e.clientX - _lastX) / world.scale;
      world.y -= (e.clientY - _lastY) / world.scale;
      _lastX = e.clientX;
      _lastY = e.clientY;
      buttonScanner();
    } */
    world.mouse.x = mouseWorldCoords.x; 
    world.mouse.y = mouseWorldCoords.y;
    screen.viewableButtons.forEach(button => { button.hovered = button.isUnderMouse(); });
  });

  window.addEventListener('mousedown', () => {
    /* if (e.button === 2) {
      _rightMouseDown = true;
      _lastX = e.clientX;
      _lastY = e.clientY;
    } else {
      leftMouseDown = true;
      screen.viewableButtons.forEach(button => { button.pressed = button.isUnderMouse(); });
    } */
    leftMouseDown = true;
    screen.viewableButtons.forEach(button => { button.pressed = button.isUnderMouse(); });
  });

  window.addEventListener('mouseup', () => {
    leftMouseDown = false;
    _rightMouseDown = false;
    mouseUp = true;
    requestAnimationFrame(() => {
      mouseUp = false;
    });
    screen.viewableButtons.forEach(button => {
      if(button.isInViewport() && button.pressed) {
        button.onClick();
      } else {
        button.pressed = false;
      }
    });
  });

  window.addEventListener('contextmenu', e => {
    e.preventDefault();
  });

  world.canvas.addEventListener('wheel', e => {
    e.preventDefault();
    const zoomFactor = 1.1;
    if (e.deltaY < 0) { world.scale *= zoomFactor; } else { world.scale /= zoomFactor; }
    world.scale = Math.min(Math.max(world.scale, 0.1), 100);
    buttonScanner();            
  });
}

function buttonHoverController(buttons, mouseDown, mouseUp) {
  const hoveringButtons = new Set();
  buttons.forEach(button => {
    if(button.isUnderMouse()) {
      button.hovered = true;
      button.pressed = mouseDown;
      button.clicked = mouseUp;
      hoveringButtons.add(button);
    } else {
      button.hovered = false; 
      button.pressed = false;
    }
  });
}

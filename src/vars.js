// this file contains.. variables, do you expect it to contain magic?
// without these your game would have dementia trying to remember
'use strict';
export const screen = { 
  mouse: { x: 0, y: 0 },
  leftMouseDown: false,
  fps: 30,
  viewableButtons: new Set(), // buttons inside viewport / canvas
  deltaTime: 0,
  canvas: document.getElementById('uiCanvas'),
};
screen.ctx = screen.canvas.getContext('2d');

export const world = {
  mouse: { x: 0, y: 0 },
  x: 0, y: 0, // viewport position
  scale: 0.8, // scale closer to 0 = bigger fov
  background: 0,
  canvas: document.getElementById('worldCanvas'),
  viewableButtons: new Set(),
};
world.ctx = world.canvas.getContext('2d');

export const trees = new Map();

export const keyStates = {}; // stores key is pressed or not

export const mouseStates = { leftDown: false };

export const currencies = new Map();

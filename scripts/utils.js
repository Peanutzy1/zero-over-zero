// this script is for utility functions
'use strict';
import { world, screen, trees } from './vars.js';

export const screenToWorld = (x, y) => {
  return { 
    x: (x - window.innerWidth / 2) / world.scale + world.x,
    y: (y - window.innerHeight / 2) / world.scale + world.y
  };
};

export const worldToScreen = (x, y) => {
  return {
    x: (x - world.x) * world.scale + window.innerWidth / 2,
    y: (y - world.y) * world.scale + window.innerHeight / 2
  };
};

export const makeRectBounds = ({ x, y, w, h, pad = 0 }) => {
  return {
    left: x - w / 2 - pad,
    right: x + w / 2 + pad,
    up: y - h / 2 - pad,
    down: y + h / 2 + pad
  };
};

export const isPointInRect = ({ px, py, x, y, w, h }) => {
  const { left, right, up, down } = makeRectBounds({ x, y, w, h });
  return px >= left && px <= right && py >= up && py <= down;
};

export const isRectInViewport = ({ x, y, w, h, pad = 0 }) => {
  const { left, right, up, down } = makeRectBounds({ x, y, w, h, pad });
  const { left: vLeft, right: vRight, up: vUp, down: vDown } = makeRectBounds({
    x: world.x,
    y: world.y,
    w: window.innerWidth / world.scale,
    h: window.innerHeight / world.scale
  });

  return !(right < vLeft || left > vRight || down < vUp || up > vDown);
};

export function hexToRgba(hex) {
  // remove hash if present
  hex = (hex || '').replace(/^#/, '');
  if (hex.length !== 6 && hex.length !== 8) {
    throw new Error('Hex must be 6 (RGB) or 8 (RGBA) characters');
  }

  const r = parseInt(hex.slice(0, 2), 16);
  const g = parseInt(hex.slice(2, 4), 16);
  const b = parseInt(hex.slice(4, 6), 16);
  const a = hex.length === 8 ? parseInt(hex.slice(6, 8), 16) / 255 : 1;

  return { r, g, b, a };
}

export const scaleRGB = (r, g, b, scale) => {
  return { r: r * scale, g: g * scale, b: b * scale };
};

export function buttonScanner() {
  const viewableButtons = new Set();
  trees.forEach(tree => {
    tree.buttons.forEach(button => {
      if(button.isInViewport() && button.unlocked) {
        viewableButtons.add(button);
      } else {
        button.hovered = false;
        button.pressed = false;
        button.clicked = false;
      }
    });
  });
  screen.viewableButtons = viewableButtons;
}

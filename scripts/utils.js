// this script is for utility functions
// "just dump every function in here and it would not be nonsense" - peanut
'use strict';

import { world, trees } from './vars.js';

// turns screen -> world coords (zoom aware)
// no use case yet
export function screenToWorld(x, y) {
  return { 
    x: (x - window.innerWidth / 2) / world.scale + world.x,
    y: (y - window.innerHeight / 2) / world.scale + world.y
  };
}

// world -> screen coords (zoom aware, as always)
// used in mouse.js, checks button hover / pressing / clicking
export function worldToScreen(x, y) {
  return {
    x: (x - world.x) * world.scale + window.innerWidth / 2,
    y: (y - world.y) * world.scale + window.innerHeight / 2
  };
}

// makes bounds of a rect with padding; x, y are centered
// used in isRectInViewport() and isPointInRect() (heh its this func's children)
export function makeRectBounds({ x, y, w, h, pad = 0 }) {
  return {
    left: x - w / 2 - pad,
    right: x + w / 2 + pad,
    up: y - h / 2 - pad,
    down: y + h / 2 + pad
  };
}

// point inside rect?; first 2 params are point's coords, rest is the rect's 
// use case is in ./gameplay/button.js -> TreeButton.isUnderMouse() method
export function isPointInRect({ px, py, x, y, w, h }) {
  const { left, right, up, down } = makeRectBounds({ x, y, w, h });
  return px >= left && px <= right && py >= up && py <= down;
}

// rect in viewport? same params as makeRectBounds()
// use case is in ./gameplay/button.js -> TreeButton.isInViewport() method
export function isRectInViewport({ x, y, w, h, pad = 0 }) {
  const { left, right, up, down } = makeRectBounds({ x, y, w, h, pad });
  const { left: vLeft, right: vRight, up: vUp, down: vDown } = makeRectBounds({
    x: world.x,
    y: world.y,
    w: window.innerWidth / world.scale,
    h: window.innerHeight / world.scale
  });

  return !(right < vLeft || left > vRight || down < vUp || up > vDown);
}

// hex -> {r, g, b a}
// use case is in button.js Button class's constructor
// "please do not use 'rgba()' when making a treebutton" - peanut
export function hexToRgba(hex) {
  // remove hash if present
  hex = (hex || '').replace(/^#/, ''); // "i hate RegExps" - Peanut
  if (hex.length !== 6 && hex.length !== 8) {
    throw new Error('Hex must be 6 (RGB) or 8 (RGBA) characters');
  }

  const r = parseInt(hex.slice(0, 2), 16);
  const g = parseInt(hex.slice(2, 4), 16);
  const b = parseInt(hex.slice(4, 6), 16);
  const a = hex.length === 8 ? parseInt(hex.slice(6, 8), 16) / 255 : 1;

  return { r, g, b, a };
}

// not useful you can hardcode the scale anyways
export function scaleRGB(r, g, b, scale) {
  return { r: r * scale, g: g * scale, b: b * scale };
}

export function scaleRgbaToString({ r, g, b, a }, scale) {
  return `rgba(${r * scale}, ${g * scale}, ${b * scale}, ${a})`;
}
// "my greatest invention" - Peanutzy
// scans all buttons, return all buttons inside viewport.
// use case is in keyboard.js, scans for buttons if movement key (wasd) is pressed
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
  world.viewableButtons = viewableButtons;
}

// sorry guys if the docs are a bit too extensive because i asked claude to generate this
// used in drawWrappedText() to create wrapped text
export function wrapText(text, maxWidth) {
  const words = text.split(' '); // makes an array, then seperates each word by spaces
  const lines = []; // the output, will be individual lines fitting the maxWidth
  let line = ''; // current line

  for (let i = 0; i < words.length; i++) {
    const testLine = `${line}${words[i]} `; // current line with the next word 
    // and a space at the end of that word
    const metrics = world.ctx.measureText(testLine); // measures the width of the test line
    // checks if testline is too long and if were not on the first word
    // cuz if we dont allow words like supercalifragilisticexpialidocious to exist
    // it would run into infinite loop
    if (metrics.width > maxWidth && i > 0) {
      lines.push(line.trim()); // pushes the line from before to the output
      line = `${words[i]} `; // starts the line at the new word
    } else {
      line = testLine; // set line to be the one in testing aka the one with the word added
    }
  }
  lines.push(line.trim()); // pushes the last fitting line
  return lines;
}

// draws the wrapped text, spacing is height (px), and stroke param means draw stroke?
// used in Button.drawDescription() to draw the description
export function drawWrappedText({ text, maxWidth, x, y, spacing, stroke, ctx }) {
  const metrics = ctx.measureText("'MgH@q*- yes its for accuracy' - peanut");
  const actualHeight = metrics.actualBoundingBoxAscent + metrics.actualBoundingBoxDescent;
  let textY = y;
  const lines = wrapText(text, maxWidth);
  lines.forEach(line => { 
    world.ctx.fillText(line, x, textY);
    stroke && ctx.strokeText(line, x, textY);
    textY += actualHeight + spacing;
  });
}

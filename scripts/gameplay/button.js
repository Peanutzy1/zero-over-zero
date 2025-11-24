// this file is for the button class
// who would've thought button behavior is complicated af

'use strict';
import { ctx, world, screen } from '../vars.js';
import { hexToRgba, isRectInViewport, isPointInRect } from '../utils.js';

export class Button {
  constructor({
    id = '', description = '', x = 0, y = 0, // x, y is for button's position (centered)
    action = () => { console.log(`${this.id} did action`); }, // action for when its clicked
    activateReq = () => { return true; }, // requirements to activate it, returns a boolean
    unlockReq = () => { return true; }, // the requirements for it to appear, return boolean
    //  for the suprise element xdd
    childrenIDs = [], // IDs of other button that will try to unlock after activation
    tree // the upgrade tree this button belongs, yes theres will be trees with 1 button
  }) {
    this.id = id;
    this.description = description;
    this.tree = tree;
    this.x = x;
    this.y = y;

    // the button inherits these traits from the tree
    this.w = this.tree?.buttonWidth ?? 160;
    this.h = this.tree?.buttonHeight ?? 100;
    this.fill = this.tree?.buttonFill ?? '#0080ff';
    this.stroke = this.tree?.buttonStroke ?? '#8000ff';

    // current states of the button
    this.pressed = false;
    this.hovered = false;
    this.unlocked = unlockReq();
    this.activationCount = 0; // activation count instead of activated because its more versatile

    this.activateReq = activateReq;
    this.unlockReq = unlockReq;
    this.action = action;

    this.childrenIDs = childrenIDs;

    // tree button colors has to be in hex format 
    // this is r, g, b, a values (stored as an object) for stoke color and fill color
    this.rgbaFill = hexToRgba(this.fill);
    this.rgbaStroke = hexToRgba(this.stroke);

    // button auto adds itself on the tree's buttons Map
    this.tree.buttons.set(this.id, this);
  }
  // ah yes, the visuals. Players would complain if the game's a blank canvas
  // with invisible buttons lol
  draw() {
    ctx.beginPath();
    // so this fill darkens based on the states
    // like darker when hovered and EVEN DARKER when its pressed on
    if(this.pressed) {
      ctx.fillStyle = `rgba(
      ${this.rgbaFill.r * 0.5}, 
      ${this.rgbaFill.g * 0.5}, 
      ${this.rgbaFill.b * 0.5},
      ${this.rgbaFill.a}
      )`;
    } else if(this.hovered) {
      ctx.fillStyle = `rgba(
      ${this.rgbaFill.r * 0.75}, 
      ${this.rgbaFill.g * 0.75}, 
      ${this.rgbaFill.b * 0.75},
      ${this.rgbaFill.a}
      )`;
    } else {
      ctx.fillStyle = this.fill;
    }

    // the stroke darkens when its not upgraded yet, and shines the true color when it does
    if(this.activationCount === 0) {
      ctx.strokeStyle = `rgba(
      ${this.rgbaStroke.r * 0.25}, 
      ${this.rgbaStroke.g * 0.25}, 
      ${this.rgbaStroke.b * 0.25},
      ${this.rgbaStroke.a}
      )`;
    } else {
      ctx.strokeStyle = this.stroke;
    }
    // fatty borders, maybe will get fatter
    ctx.lineWidth = 4;
    // drawing button, you can see the button's x and y are centered 
    // by subtracting it by half the width / height 
    ctx.strokeRect(this.x - this.w / 2, this.y - this.h / 2, this.w, this.h);
    ctx.fillRect(this.x - this.w / 2, this.y - this.h / 2, this.w, this.h);
    ctx.beginPath();
  }

  // returns true if the button is in viewport, the function used here is in ../utils.js 
  isInViewport() {
    return isRectInViewport({ x: this.x, y: this.y, w: this.w, h: this.h, pad: 50 });
  }

  // returns true if the mouse is hovering on top of the button
  // ah yes reactive buttons, function used is also in ../utils.js
  isUnderMouse() {
    return isPointInRect({ 
      px: world.mouse.x, py: world.mouse.y,
      x: this.x, y: this.y, w: this.w, h: this.h 
    });
  }

  // when you click it, no sad button cant clicky clicky here (except for trolls)
  onClick() {
    // checks if theres action to begin with, and checks if activateReqs returns true
    if(this.action && this.activateReq()) {
      this.activationCount++;
      this.action();
      this.unlockController();
    } // there will be a method / a function,
    //  that prevents this.pressed to go back to true after button fully activated 
    // yes unreactive button incoming
    this.pressed = false;
  }

  // this will attempt to unlock other button with matching ID inside this.childrenIDs
  // aka loops thru the ids, get their button objects, check if unlockReq() returns true
  // and add it to screen.viewableButtons (a set/ array of buttons inside viewport) 
  // if their button's isInViewport() returns true 
  unlockController() {
    for (const i in this.childrenIDs) {
      const button = this.tree.buttons.get(this.childrenIDs[i]);
      if(button) {
        button.unlocked = button.unlockReq();
        if(button.isInViewport()) {
          screen.viewableButtons.add(button);
        }
      }
    }
  }
} // the {} slide of doom, never nesters hates this

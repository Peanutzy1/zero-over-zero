// this file is for the button clas\
// "who would've thought button behavior is complicated af" - peanut

'use strict';
import { world, screen, trees } from '../vars.js';
import { 
  hexToRgba, scaleRgbaToString, isRectInViewport, isPointInRect, drawWrappedText 
} from '../utils.js';

export class TreeButton {
  constructor({
    id = '', description = '', x = 0, y = 0, // coords is centered
    action = () => {}, // action for onclick() method
    activateReq = () => { return true; }, // activation requirements, returns boolean
    unlockReq = () => { return true; }, // visibility requirements, returns boolean
    //  "for the suprise element xdd" - peanut
    childrenIDs = [], // IDs of buttons attempting unlocking after activation
    treeID, 
    how2style 
    // (wip) the style guide, will be a functionable class later
    //  the property "iLikeToRewritehow2draw" is self explanatory.
    // " r/unixp*** but its buttons" -peanut
  }) {
    // self explanatory
    this.id = id; 
    this.description = description;
    this.treeID = treeID;
    this.x = x; 
    this.y = y;

    this.style = how2style ;

    // the button inherits these traits from the style
    this.w = this.style.w ?? 160; this.h = this.style.h ?? 100;
    this.fill = this.style.fill ?? '#0080ff';
    this.stroke = this.style.stroke ?? '#8000ff';
    this.font = this.style.font ?? 'bold 14px "Comic Sans MS", cursive, monospace';
    this.fontFill = this.style.fontFill ?? '#ffffff'; 
    this.fontStroke = this.style.fontStroke ?? '#000000';

    // current states of the button
    this.pressed = false;
    this.hovered = false;
    this.unlocked = unlockReq();
    this.activationCount = 0; // activation count instead of activated because its more versatile
    this.activateReq = activateReq;
    this.unlockReq = unlockReq;
    this.action = action ?? (() => { console.log(`${this.id} did action`); });

    this.childrenIDs = childrenIDs;

    // this is r, g, b, a values (stored as an object) for stoke color and fill color
    this.rgbaFill = hexToRgba(this.fill);
    this.rgbaStroke = hexToRgba(this.stroke);
    // button auto adds itself on the tree's buttons Map
    this.tree = trees.get(this.treeID);
    this.tree.buttons.set(this.id, this);
  }

  // "Players would complain if the game's a blank canvas with invisible buttons lol" - peanut
  draw() {
    if(!this.style.iLikeToRewritehow2draw) {
      world.ctx.beginPath();
      // so this fill darkens based on the states
      // like darker when hovered and EVEN DARKER when its pressed on
      world.ctx.fillStyle = this.fill;
      if(this.hovered) {
        world.ctx.fillStyle = scaleRgbaToString(this.rgbaFill, 0.75);
      }
      if(this.pressed) {
        world.ctx.fillStyle = scaleRgbaToString(this.rgbaFill, 0.5);
      } 
      // the stroke darkens when its not upgraded yet, and shines the true color when it does
      if(this.activationCount === 0) {
        world.ctx.strokeStyle = scaleRgbaToString(this.rgbaStroke, 0.25);
      } else {
        world.ctx.strokeStyle = this.stroke;
      }
      world.ctx.lineWidth = 15;
      // you can see the button's coords are centered 
      world.ctx.strokeRect(this.x - this.w / 2, this.y - this.h / 2, this.w, this.h);
      world.ctx.fillRect(this.x - this.w / 2, this.y - this.h / 2, this.w, this.h);
      this.drawDescription();
    }
    this.style.draw?.();
  }

  // "couldve intergrated this to draw()" - peanut
  drawDescription() {
    world.ctx.font = this.font;
    world.ctx.fillStyle = this.fontFill;
    world.ctx.strokeStyle = this.fontStroke;
    world.ctx.textAlign = 'center';
    world.ctx.lineWidth = 1;
    drawWrappedText({
      text: this.description,
      x: this.x,
      y: this.y,
      maxWidth: this.w - 20,
      spacing: 0,
      stroke: false,
      ctx: world.ctx
    });
  }

  // "1 comment per everything" - p e a n u t
  isInViewport() {
    return isRectInViewport({ x: this.x, y: this.y, w: this.w, h: this.h, pad: 50 });
  }

  // "ah yes reactive buttons" - peanut
  isUnderMouse() {
    return isPointInRect({ 
      px: world.mouse.x, py: world.mouse.y,
      x: this.x, y: this.y, w: this.w, h: this.h 
    });
  }

  // "no sad button cant clicky clicky here (except for trolls)" - peanut
  onClick() {
    if(this.action && this.activateReq()) {
      this.activationCount++;
      this.action();
      this.unlockController();
    }
    this.pressed = false;
  }

  // unlock other button with matching ID inside this.childrenIDs
  // if their unlockReq() returns true
  // will be visible if theirisInViewport() also returns true 
  unlockController() {
    this.childrenIDs.forEach(id => {
      const btn = this.tree.buttons.get(id);
      if(!btn) { return; }
      btn.unlocked = btn.unlockReq();
      btn.isInViewport() && world.viewableButtons.add(btn);
    });
  }
} // "the {} slide of doom, never nesters hates this" - peanut

export class UIButton {
  constructor({ x, y, action, viewReq, style }) {
    this.x = x;
    this.y = y;
    this.action = action; // function
    this.style = style;
    this.hovered = false;
    this.pressed = false;
    this.activated = false;

    this.viewReq = viewReq;
    this.viewable = viewReq();
  }

  draw() {
    this.style.draw();
  }

  isUnderMouse() {
    return isPointInRect({
      px: screen.mouse.x, py: screen.mouse.y,
      x: this.x, y: this.y, w: this.style.w, h: this.style.h
    });
  }
}

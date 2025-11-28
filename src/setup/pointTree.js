// this script is used to setup context, buttons, trees
// "will have too much lines maybe" - peanut

'use strict';
import { trees } from '../vars.js';
import { Tree } from '../classes/tree.js';
import { TreeButton } from '../classes/button.js';
import { Currency } from '../classes/currency.js';

// #region Point tree
export function pointTreeSetup() {
  trees.set('pointTree', new Tree({
    id: 'point',
    buttonFill: '#808080',
    buttonStroke: '#ffffff',
    buttonWidth: 160,
    buttonHeight: 100
  }));

  // follow this format when you are making a button style
  // "ah yes jss (Javascript Style Sheets)"
  const pointTreeButtonStyle = {
    w: 400,
    h: 200,
    fill: '#c0c0c0',
    stroke: '#ffffff',
    font: 'bold 20px noto sans',
    fontFill: '#ffffff',
    fontStroke: '#000000',
    draw: (_btn) => {}
  };

  const point = new Currency('point');

  const p1 = new TreeButton({
    id: 'p1',
    treeID: 'point',
    description: 'starter of all things, 1/s passive point generation',
    x: 0,
    y: 0,
    childrenIDs: ['p2', 'p3'],
    action: () => { point.baseGen = 1; },
    unlockReq: () => { return true; },
    activateReq: () => { return true; },
    how2style: pointTreeButtonStyle
  });

  const p2 = new TreeButton({
    id: 'p2',
    treeID: 'point',
    x: -400,
    y: -400,
    description: 'template upgrade desc',
    childrenIDs: [],
    action: () => { console.log('p2 has been pressed'); },
    unlockReq: () => { return p1.activationCount > 0; },
    activateReq: () => { return p2.unlocked; },
    how2style: pointTreeButtonStyle
  });

  const p3 = new TreeButton({
    id: 'p3',
    treeID: 'point',
    x: 0,
    y: -800,
    description: 'template upgrade desc',
    childrenID: [],
    action: () => { console.log('p3 has been pressed'); },
    unlockReq: () => { return p1.activationCount > 0; },
    activateReq: () => { return p3.unlocked; },
    how2style: pointTreeButtonStyle
  });
}
// #endregion 

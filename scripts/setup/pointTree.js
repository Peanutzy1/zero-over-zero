// this script is used to setup context, buttons, trees
// "will have too much lines maybe" - peanut

'use strict';
import { trees } from '../vars.js';
import { Tree } from '../classes/tree.js';
import { Button } from '../classes/button.js';

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
    w: 350,
    h: 200,
    fill: '#c0c0c0',
    stroke: '#ffffff',
    font: '12px noto sans',
    fontFill: '#ffffff',
    fontStroke: '#000000',
  };

  const _pointTree = trees.get('pointTree');

  const p1 = new Button({
    id: 'p1',
    treeID: 'point',
    description: 'starter of all things, 1/s passive point generation',
    x: 0,
    y: 0,
    childrenIDs: ['p2', 'p3'],
    action: () => { console.log('p1 has been pressed'); },
    unlockReq: () => { return true; },
    activateReq: () => { return true; },
    how2style: pointTreeButtonStyle
  });

  const p2 = new Button({
    id: 'p2',
    treeID: 'point',
    x: -200,
    y: -200,
    description: 'template upgrade desc',
    childrenIDs: [],
    action: () => { console.log('p2 has been pressed'); },
    unlockReq: () => { return p1.activationCount > 0; },
    activateReq: () => { return p2.unlocked; },
    how2style: pointTreeButtonStyle
  });

  const p3 = new Button({
    id: 'p3',
    treeID: 'point',
    x: 0,
    y: -400,
    description: 'template upgrade desc',
    childrenID: [],
    action: () => { console.log('p3 has been pressed'); },
    unlockReq: () => { return p1.activationCount > 0; },
    activateReq: () => { return p3.unlocked; },
    how2style: pointTreeButtonStyle
  });
}
// #endregion 

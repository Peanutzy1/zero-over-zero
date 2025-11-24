// this script is used to setup context, buttons, trees
'use strict';
import { trees } from '../vars.js';
import { Tree } from '../gameplay/tree.js';
import { Button } from '../gameplay/button.js';

// #region Point tree
export function pointTreeSetup() {
  trees.set('pointTree', new Tree({
    id: 'Point Tree',
    buttonFill: '#808080',
    buttonStroke: '#ffffff',
    buttonWidth: 160,
    buttonHeight: 100
  }));

  const pointTree = trees.get('pointTree');

  const p1 = new Button({
    id: 'p1',
    tree: pointTree,
    description: 'starter of all things, 1/s passive point generation',
    x: 0,
    y: 0,
    childrenIDs: ['p2', 'p3'],
    action: () => { console.log('p1 has been pressed'); },
    unlockReq: () => { return true; },
    activateReq: () => { return true; }, 
  });

  const p2 = new Button({
    id: 'p2',
    tree: pointTree,
    x: -200,
    y: -200,
    description: 'template upgrade desc',
    childrenIDs: [],
    action: () => { console.log('p2 has been pressed'); },
    unlockReq: () => { return p1.activationCount > 0; },
    activateReq: () => { return p2.unlocked; }
  });

  const p3 = new Button({
    id: 'p3',
    tree: pointTree,
    x: 0,
    y: -400,
    description: 'template upgrade desc',
    childrenID: [],
    action: () => { console.log('p3 has been pressed'); },
    unlockReq: () => { return p1.activationCount > 0; },
    activateReq: () => { return p3.unlocked; }
  });
}
// #endregion 

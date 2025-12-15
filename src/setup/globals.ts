// this file is for some globals that is totally not the elements
import { MacademiaManager, HazelnutHook, ChestnutContainer } from '../core/core';
import { Position } from './types';

export type ContainerMap = {
  position: {x: number, y: number}
}

const manager = new MacademiaManager<ContainerMap>();
manager.addEntity('screenGlobals');

manager.addContainer('position', new ChestnutContainer<Position>);

manager.addComponents('screenGlobals', {
  position: { x: 0, y: 0 }
})
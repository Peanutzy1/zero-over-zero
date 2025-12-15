// this file is for the HazelnutHook system

import { MacademiaManager } from './MacademiaManager';
import { ContainerMap, CullFn } from './types';

export class HazelnutHook<C extends ContainerMap> {
  private culls: Array<CullFn> = [];
  private activeIDs: string[] = [];
  private manager: MacademiaManager<C>;

  constructor(manager: MacademiaManager<C>) {
    this.manager = manager;
  }

  addCull(fn: CullFn) {
    this.culls.push(fn);
  }

  cull(initalIDs: string[]) {
    let ids = initalIDs;
    for (const cull of this.culls) {
      ids = cull(ids, this.manager);
    }
    this.activeIDs = ids;
  }

  runFunc(fn: (id: string) => void) {
    for (const id of this.activeIDs) {
      fn(id);
    }
  }

  getActiveIDs() {
    return this.activeIDs;
  }
}

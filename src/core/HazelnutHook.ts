// this file is for the HazelnutHook system

import { MacademiaManager } from './MacademiaManager';
import { ContainerMap, CullFn } from './types';

export class HazelnutHook<C extends ContainerMap> {
  private culls: Array<CullFn> = [];
  private activeIDs: string[] = [];

  addCull(fn: CullFn) {
    this.culls.push(fn);
  }

  run(InitalIds: string[], manager: MacademiaManager<C>) {
    let ids = InitalIds;
    for (const cull of this.culls) {
      ids = cull(ids, manager);
    }
    this.activeIDs = ids;
  }

  runFunc(fn: (id: string) => void) {
    for (const id of this.activeIDs) {
      fn(id);
    }
  }

  getActiveIds() {
    return this.activeIDs;
  }
}

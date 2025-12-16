// this file is for the HazelnutHook system

import { MacademiaManager } from './MacademiaManager';
import {ContainerSchema, CullFn, EntityID } from './types';

export class HazelnutHook<S extends ContainerSchema> {
  private culls: Array<CullFn<S>> = [];
  private activeIDs: string[] = [];
  private manager: MacademiaManager<S>;

  constructor(manager: MacademiaManager<S>) {
    this.manager = manager;
  }

  addCull(fn: CullFn<S>) {
    this.culls.push(fn);
  }

  cull() {
    let ids = Array.from(this.manager.entities);
    for (const cull of this.culls) {
      ids = cull(ids, this.manager);
    }
    this.activeIDs = ids;
  }

  runFunc(fn: (id: EntityID) => void) {
    for (const id of this.activeIDs) {
      fn(id);
    }
  }

  getActiveIDs() {
    return this.activeIDs;
  }
}

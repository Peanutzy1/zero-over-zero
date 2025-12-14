// this file is for the manager system
import { ChestnutContainer } from './ChestnutContainer';
import { HazelnutHook } from './HazelnutHook';
import { ContainerMap, EntityID } from './types';

export class MacademiaManager<C extends ContainerMap> {
  containers: { [K in keyof C]?: ChestnutContainer<C[K]> } = {} as any;
  hooks: Record<string, unknown> = {};

  addContainer<K extends keyof C>(name: K, container: ChestnutContainer<C[K]>) {
    this.containers[name] = container;
  }

  addHook(name: string, hook: HazelnutHook<C>) {
    this.hooks[name] = hook as HazelnutHook<C>;
  }

  getEntity(id: EntityID) {
    const bundle: Partial<C> = {};
    for (const key in this.containers) {
      bundle[key as keyof C] = this.containers[key as keyof C]?.get(id);
    }
    return bundle;
  }
}

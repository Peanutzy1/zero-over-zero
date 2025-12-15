// this file is for the manager system
import { ChestnutContainer } from './ChestnutContainer';
import { HazelnutHook } from './HazelnutHook';
import { ContainerMap, EntityID } from './types';

export class MacademiaManager<C extends ContainerMap> {
  containers: { [K in keyof C]?: ChestnutContainer<C[K]> } = {};
  hooks: Record<string, unknown> = {};
  entities: Set<EntityID> = new Set();

  addContainer<K extends keyof C>(name: K, container: ChestnutContainer<C[K]>) {
    this.containers[name] = container;
  }

  addHook(name: string, hook: HazelnutHook<C>) {
    this.hooks[name] = hook as HazelnutHook<C>;
  }

  addEntity(id: EntityID) {
    if (this.entities.has(id)) {
      throw new Error(`Entity ${id} already exists.`);
    }

    this.entities.add(id);
  }

  addComponents(id: EntityID, components: Partial<C>) {

    if (components == null || typeof components !== 'object') {
      throw new Error(`Components must be a non-null object.`);
    }

    if (!this.entities.has(id)) {
      throw new Error(`Entity ${id} does not exist.`);
    }

    for (const key in components) {
      const container = this.containers[key as keyof C];
      if (!container) throw new Error(`Container ${key} does not exist.`);

      const component = components[key as keyof C];
      if (component) container.set(id, component);
    }
  }

  deleteEntityAndComponents(id: EntityID) {
    if (!this.entities.has(id)) return;

    for (const key in this.containers) {
      const container = this.containers[key as keyof C];
      container?.delete(id);
    }

    this.entities.delete(id);
  }

  getComponents(id: EntityID): Partial<C> {
    if (!this.entities.has(id)) {
      throw new Error(`the entity ${id} does not exist.`);
    }

    const bundle: Partial<C> = {};

    for (const key in this.containers) {
      const container = this.containers[key as keyof C];

      if (!container) continue;

      const component = container.get(id);

      if (component) {
        bundle[key] = component;
      }
    }

    return bundle;
  }
}

// this file is for the ChestnutContainer system

import { ContainerID } from "./types";

export class ChestnutContainer<T> {
  data: Map<ContainerID, T>;
  constructor() {
    this.data = new Map<string, T>();
  }

  add(id: ContainerID, component: T) {
    this.data.set(id, component);
  }

  get(id: ContainerID) {
    return this.data.get(id);
  }

  del(id: ContainerID) {
    this.data.delete(id);
  }
}


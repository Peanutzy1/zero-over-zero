// this file is for the ChestnutContainer system

import { ContainerID } from "./types";

export class ChestnutContainer<T> {
  private data: Map<ContainerID, T>;
  constructor() {
    this.data = new Map<string, T>();
  }

  set(id: ContainerID, component: T) {
    this.data.set(id, component);
  }

  get(id: ContainerID) {
    return this.data.get(id);
  }

  delete(id: ContainerID) {
    this.data.delete(id);
  }
}


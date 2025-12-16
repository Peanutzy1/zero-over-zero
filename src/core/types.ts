// this file contains types.. and thats it.

import { MacademiaManager } from './MacademiaManager';

export type CullFn<S extends ContainerSchema> = (ids: string[], manager: MacademiaManager<S>) => string[];

export type EntityID = string;
export type ContainerID = string;

export type ChestnutContainer<T> = Map<EntityID, T>

export type ContainerSchema = Record<ContainerID, () => ChestnutContainer<any>>

type InferContainer<F> =
  F extends () => ChestnutContainer<infer T>
    ? ChestnutContainer<T>
    : never;

export type ContainerMapFromSchema<S extends ContainerSchema> = {
  [K in keyof S]: InferContainer<S[K]>;
};
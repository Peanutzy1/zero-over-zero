// this file contains types.. and thats it.

import { MacademiaManager } from './MacademiaManager';

export type ContainerMap = Record<ContainerID, any>;

export type CullFn = (ids: string[], manager: MacademiaManager<ContainerMap>) => string[];

export type EntityID = string;
export type ContainerID = string;

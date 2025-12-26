/**
 * This file is the single source of truth
 * for the systems to run on
 * "I wonder where you get your data from" -peanut
 */

import { carve } from "./utils/data-storage.js"
export const pea = {
    buffer: new ArrayBuffer(100 * 1024 * 1024),
    maxEntities: 10000,
    IS
}

export const nut = {

}

export const zy = {
    idenityStates: carve(Uint32Array),
    specializedStates: carve(Uint32Array),
    x: carve(Float32Array),
    y: carve(Float32Array),
}
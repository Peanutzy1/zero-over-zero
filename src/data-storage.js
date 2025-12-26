/**
 * This file is the single source of truth
 * for the systems to run on
 * "I wonder where you get your data from" -peanut
 */

import { carve } from "./utils/zy.js"
export const pea = {
    buffer: new ArrayBuffer(100 * 1024 * 1024),
    maxEntities: 10000
}
const buf = pea.buffer // array buffer
const hiE = pea.maxEntities

export const zy = {
    idenityStates: carve(Uint32Array),
    specializedStates: carve(Uint32Array),
    x: carve(Float32Array)
}

let head = 0


/**
 * ONLY RUN THIS IN INITILIZATION
 * RUNNING THIS IN THE GAME LOOP
 * OR ANY REPEATABLE FUNCTIONS
 * IS A MASSIVE PERFORMANCE HIT
 * 
 */
let key = null
const arrayStorage = zy
function assign(id, configObj) {
    for (key in configObj) {
        arrayStorage[key][id] = configObj[key]
    }
}

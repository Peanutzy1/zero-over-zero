/**
 * this file contains the helpers for
 * the object that contains typed arrays (zy)
 */

import { pea, zy } from "../data-storage.js"

/** * 
 * @typedef {
 * Int8Array 
 * | Uint8Array 
 * | Uint8ClampedArray 
 * | Int16Array 
 * | Uint16Array 
 * | Int32Array 
 * | Uint32Array 
 * | Float32Array 
 * | Float64Array 
 * | BigInt64Array 
 * | BigUint64Array
 * } TypedArrayInstance
 */

/** * 
 * @typedef {
 * Int8ArrayConstructor 
 * | Uint8ArrayConstructor 
 * | Uint8ClampedArrayConstructor 
 * | Int16ArrayConstructor 
 * | Uint16ArrayConstructor 
 * | Int32ArrayConstructor 
 * | Uint32ArrayConstructor 
 * | Float32ArrayConstructor 
 * | Float64ArrayConstructor 
 * | BigInt64ArrayConstructor 
 * | BigUint64ArrayConstructor
 * } TypedArrayConstructor 
*/

/**
 * @param {TypedArrayConstructor} Type - the type of the constructor for typed arrays (like Uint32Array not new Uint32Array())
 * @returns {TypedArrayInstance} - the instance, like new Uint32Array()
 */

let head = 0 // cursor / pointer of this 

export function carve(Type) {
    const buffer = pea.buffer
    const entities = pea.maxEntities
    const bPE = Type.BYTES_PER_ENTITY

    const start = (head + bPE - 1) & ~(bPE - 1)

    head += bPE * entities // array length in bytes
    
    if (head > buffer.byteLength) {
        throw new Error("INCREASE YOUR pea.buffer size!!!")
    }

    return new Type(buffer, start, entities)
}

/**
 * @param {number} id - The entity index.
 * @param {Object} config - The data to "bake" into the arrays.
 * * @important UNDER NO CIRCUMSTANCES RUN THIS IN GAMELOOP OR PARTS OF IT
 * This function creates garbage and uses slow reflection (for...in).
 * Use only for initialization/spawn.
 */

export function sculpt(id, config) {
    const arrays = zy

    for (const key in config) {
        arrays[key][id] = config[key]
    }
}

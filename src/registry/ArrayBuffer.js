/**
 * this file contains all arrays and the bits
 * "i welcom u to da stack of dis machin" -peanut
 */
import { carve } from "../utils/data-storage";
export const MAX_ENTITIES = 10000

export const BUFFER_SIZE = 100 * 1024 * 1024 // 100 mb
export const buffer = new ArrayBuffer(BUFFER_SIZE)

export let head = 0;

/**
 * @param {
 * Uint8ArrayConstructor | Uint16ArrayConstructor | Uint32ArrayConstructor |
 * Int8ArrayConstructor | Int16ArrayConstructor | Int32ArrayConstructor |
 * Float32ArrayConstructor | Float64ArrayConstructor} Type - the type of the constructor for typed arrays (like Uint32Array not new Uint32Array())
 *
 * @returns {
 * Int8Array | Uint8Array | Uint8ClampedArray | Int16Array
 * | Uint16Array | Int32Array | Uint32Array | Float32Array
 * | Float64Array | BigInt64Array | BigUint64Array} - the instance, like new Uint32Array()
 *
 * "sorry for the big union types idk why it doesnt work if u do @typedef" -peanutzy (yes the developer not the persona)
 */

export function carve(Type) {
  const entities = pea.MAX_ENTITIES;
  const bPE = Type.BYTES_PER_ELEMENT;

  const start = (nut.head + bPE - 1) & ~(bPE - 1);

  nut.head = start + bPE * entities; // the start plus array length in bytes

  if (nut.head > buffer.byteLength) {
    throw new Error('INCREASE YOUR pea.buffer size!!!');
  }

  return new Type(buffer, start, entities);
}

/**
 * @param {number} id - The entity index.
 * @param {Object} config - The data to "bake" into the arrays.
 * * @important UNDER NO CIRCUMSTANCES RUN THIS IN GAMELOOP OR PARTS OF IT
 * This function creates garbage and uses slow reflection (for...in).
 * Use only for initialization/spawn.
 * "no use dis in loopi!!!" -peanut
 */

export function sculpt(id, config) {
  const arrays = zy;

  for (const key in config) {
    arrays[key][id] = config[key];
  }
}

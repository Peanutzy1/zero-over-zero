/**
 * this file contains the helpers for
 * the object that contains typed arrays (zy)
 */

import pea from "../data-storage.js"

let head = 0
let lastHead = 0
const buffer = pea.buffer
const entities = pea.maxEntities

export function carve(Type) {
    bytesPerEntity = Type.BYTES_PER_ENTITY
    lastHead = (head + bytesPerEntity - 1) & ~(bytesPerEntity - 1)
    head = lastHead + ( bytesPerEntity * entities )
    return new Type(buffer, lastHead, entities)
}
/**
 * This file is the single source of truth
 * for the systems to run on
 * "I wonder where you get your data from" -peanut
 */

export const ramhouse = {
    // 100 MB of good ol ram
    memory: new ArrayBuffer(100_000_000),
    maxEntities: 10000,
    generalFlags: carve(Uint32Array, maxEntities),
    
}

/**
 * Carves out an typed array in the 100MB buffer.
 * @param {Uint8ArrayConstructor|Float32ArrayConstructor|Uint32ArrayConstructor|Float64ArrayConstructor} Type 
 * @param {number} count - How many elements to allocate
 * @returns {InstanceType<typeof Type>} - Returns the specific TypedArray view
 */
let head = 0; // le pointer
function carve(Type, count) {
    const bytesPerElement = Type.BYTES_PER_ELEMENT;

    const alignment = bytesPerElement;
    head = (head + alignment - 1) & ~(alignment - 1);
    
    const start = head;
    head += count * bytesPerElement;
    
    return new Type(buffer, start, count);
}

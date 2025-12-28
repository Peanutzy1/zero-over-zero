/**
 * This file is the single source of truth
 * for the systems to run on
 * "I wonder where you get your data from" -peanut
 */

import { carve } from './utils/data-storage.js';
export const pea = {
  // ========== STORAGE ==========
  maxEntities: 10000,

  IS_ACTIVE: 1 << 0,
  IS_RENDERED: 1 << 1,
  IS_DIRTY: 1 << 2,

  // ========== RENDERING ==========
  fps: 60,
};

export const nut = {
  // ========== STORAGE ==========
  head: 0,

  // ========== RENDERING ==========
  dt: 0,
  lastTime: 0,
};

export const buffer = new ArrayBuffer(100 * 1024 * 1024);

export const zy = {
  general: carve(Uint32Array),
  special: carve(Uint32Array),
  x: carve(Float32Array),
  y: carve(Float32Array),
};



/**
 * This file contain a IIFE for initilization
 * "20 layers of abstractions" -peanut =w=
 */
import { loopi } from './gameloop.js';
import { nut } from '../data-storage.js';


nut.lastTime = performance.now();
requestAnimationFrame(loopi);
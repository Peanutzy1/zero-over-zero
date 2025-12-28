/**
 * this file is used to initiate the webgl thingie
 * "i hate webgl" -peanutzy
 */

import vertexShaderSource from './vert-shader.vert?raw';
import fragmentShaderSource from './frag-shader.frag?raw';
import {createShader, createProgram} from '../utils/render.js'

export let canvas = document.getElementById('webgl2Canvas');
export let gl = canvas.getContext('webgl2');
if (!gl) {
  throw new Error('you expected ME to RUN WEBGL 1???');
}

const vertexShader = createShader(gl, gl.VERTEX_SHADER, vertexShaderSource);

const fragmentShader = createShader(gl, gl.FRAGMENT_SHADER, fragmentShaderSource)

const program = createProgram(gl, vertexShader, fragmentShader)
gl.useProgram(program);

gl.drawArrays(gl.POINTS, 0, 1);

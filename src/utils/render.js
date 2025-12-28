/**
 * this file contains helper funcs for webgl shit
 * "at peanutTec we do not fucking store init code and helper fns together" -peanut
 */

/**
 * Compiles a GLSL shader from source string.
 * * @param {WebGLRenderingContext} gl - The WebGL context.
 * @param {number} type - The shader type: gl.VERTEX_SHADER or gl.FRAGMENT_SHADER.
 * @param {string} source - The raw GLSL source code (use ?raw import).
 * @returns {WebGLShader | undefined} The compiled shader or undefined if it failed.
 */

export function createShader(gl, type, source) {
  const shader = gl.createShader(type);
  gl.shaderSource(shader, source);
  gl.compileShader(shader);
  const success = gl.getShaderParameter(shader, gl.COMPILE_STATUS);
  if (success) {
    return shader;
  }

  console.log(gl.getShaderInfoLog(shader));
  gl.deleteShader(shader);
}

/**
 * Links a vertex and fragment shader into a single GPU Program.
 * * @param {WebGLRenderingContext} gl - The WebGL context.
 * @param {WebGLShader} vertexShader - The compiled vertex shader.
 * @param {WebGLShader} fragmentShader - The compiled fragment shader.
 * @returns {WebGLProgram | undefined} The linked program or undefined if it failed.
 */

export function createProgram(gl, vertexShader, fragmentShader) {
  const program = gl.createProgram();
  gl.attachShader(program, vertexShader);
  gl.attachShader(program, fragmentShader);
  gl.linkProgram(program);
  const success = gl.getProgramParameter(program, gl.LINK_STATUS);
  if (success) {
    return program;
  }

  console.log(gl.getProgramInfoLog(program));
  gl.deleteProgram(program);
}

/**
 * Orchestrates the synchronization between the Browser's CSS layout
 * and the GPU's internal drawing buffer.
 * * @param {HTMLCanvasElement} canvas - The target DOM element to observe.
 * @param {WebGL2RenderingContext} gl - The active WebGL2 context.
 * @param {Function} [onResize] - Optional callback for engine-level updates (e.g., updating camera matrices).
 */

/**
 * Monitors the canvas for size changes and syncs the WebGL viewport.
 * @param {HTMLCanvasElement} canvas
 * @param {WebGL2RenderingContext} gl
 */
export function resizeListener(canvas, gl) {

  const sync = () => {
    const dpr = window.devicePixelRatio || 1;

    const w = window.innerWidth;
    const h = window.innerHeight;

    const pw = Math.floor(w * dpr);
    const ph = Math.floor(h * dpr);

    if (canvas.width !== pw || canvas.height !== ph) {
      canvas.width = pw;
      canvas.height = ph;
      gl.viewport(0, 0, pw, ph);
    }

    console.log(`synced to ${pw}, ${ph}`)
  };

  window.addEventListener('resize', sync);

  sync();
}

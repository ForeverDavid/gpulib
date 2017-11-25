GpuLib
------

<img width="800px" src="https://i.imgur.com/dQEm83w.gif" />

GpuLib is a public domain header-only C library that uses less than a 100 modern AZDO OpenGL functions to draw 3D
geometry, post-process textures and compute arrays on GPU.

The contract:

 * Linux and X11 only. Doesn't target Windows, macOS, WebGL or OpenGL ES devices.
 * No multithreaded or asynchronous CPU<->GPU interactions. No barriers or sync points except for glFinish calls.
 * Not all modern OpenGL extensions are used, only those which are supported on low-end hardware and latest Mesa.

Features:

 * ~70 ms of startup time (compared to ~500 ms of SDL 2.0.4), 56 ms of which are spent on a `glXChooseFBConfig` call.
 * 23 kb for 70 lines of Hello Triangle code: `./build.sh -Os && strip --strip-all a.out`, Ubuntu 16.04, Clang 3.9.1.
 * Minimum number of shared library dependencies: `libX11`, `libXrender`, `libXi`, `libGL`, `libm`, `libc`.

Naming convention:

 * `cmd`: Command
 * `buf`: Buffer
 * `idb`: Index Buffer
 * `dib`: Draw Indirect Buffer
 * `tex`: Texture
 * `pix`: Pixel
 * `img`: Image
 * `cbm`: Cubemap
 * `msi`: Multisampled Image
 * `cpi`: Compressed Image
 * `smp`: Sampler
 * `pro`: Program Object
 * `ppo`: Pipeline Program Object
 * `fbo`: Framebuffer Object
 * `xfb`: Transform Feedback Object

Special thanks to Nicolas [@nlguillemot](https://github.com/nlguillemot) and Andreas [@ands](https://github.com/ands) for
answering my OpenGL questions and Micha [@vurtun](https://github.com/vurtun) for suggestions on how to improve the library!

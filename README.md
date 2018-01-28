GpuLib
------

<img width="800px" src="https://i.imgur.com/dQEm83w.gif" />

GpuLib is a public domain header-only C library that uses less than a 100 modern AZDO OpenGL functions to draw 3D
geometry, post-process textures and compute arrays on GPU.

The contract:

 * x64 Linux and X11 only. Doesn't target Windows, macOS, WebGL or OpenGL ES devices.
 * Not all modern OpenGL extensions are used, only those which are supported on low-end GPUs and latest Mesa.

Features:

 * ~70 ms of startup time (compared to ~500 ms of SDL 2.0.4), 56 ms of which are spent on a `glXChooseFBConfig` call.
 * 30 kb for 70 lines of Hello Triangle code: `./build.sh -Os && strip --strip-all main`, Ubuntu 18.04, Clang 5.0.1.
 * Minimum number of shared library dependencies: `libX11`, `libXrender`, `libXi`, `libdl`.

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

Special thanks to Nicolas [@nlguillemot](https://github.com/nlguillemot) and Andreas [@ands](https://github.com/ands)
for answering my OpenGL questions!
Micha [@vurtun](https://github.com/vurtun) for suggestions on how to improve the library!
Rich [@JodiTheTigger](https://github.com/JodiTheTigger) for helping me debugging a very hard problem I had!
Mārtiņš [@mmozeiko](https://github.com/mmozeiko) for explaining me why I had a serious problem on some Linux distro!

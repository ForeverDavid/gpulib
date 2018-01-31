GpuLib
------

<img width="800px" src="https://i.imgur.com/dQEm83w.gif" />

GpuLib is a public domain header-only C library that uses less than a 100 modern AZDO OpenGL functions to draw 3D
geometry, post-process images, asynchronously transfer and compute data on GPU.

The contract:

 * x64 Linux and X11 only. Doesn't target Windows, macOS, WebGL or OpenGL ES devices.
 * Not all modern OpenGL extensions are used, only those which are supported on low-end GPUs and latest Mesa 3D.
 * Data is guaranteed to be aligned, wrong alignment bugs are very hard to find, thus SSBOs and UBOs are not used.

Features:

 * ~70 ms of startup time (compared to ~500 ms of SDL 2.0.4), 56 ms of which are spent on a `glXChooseFBConfig` call.
 * 30 kb for 70 lines of Hello Triangle code: `./build.sh -Os && strip --strip-all main`, Ubuntu 18.04, Clang 5.0.1.
 * Minimum number of shared library dependencies: `libX11`, `libXrender`, `libXi`, `libdl`.

List of `gpulib.h` structs:

```c
struct gpu_cmd_t;
struct gpu_libgl_t;
```

List of `gpulib.h` enums:

```c
enum gpu_draw_mode_e;
enum gpu_buf_format_e;
enum gpu_tex_format_e;
enum gpu_smp_filter_e;
enum gpu_smp_wrapping_e;
enum gpu_pix_format_e;
enum gpu_pix_type_e;
```

List of `gpulib.h` global variables:

```c
struct gpu_libgl_t   g_gpulib_libgl_data;
struct gpu_libgl_t * g_gpulib_libgl;
```

List of `gpulib.h` procedures:

```c
```

List of `gpulib_x11_wsi.h` structs:

```c
struct gpu_libc_t;
struct gpu_libglx_t;
```

List of `gpulib_x11_wsi.h` global variables:

```c
struct gpu_libc_t     g_gpulib_libc_data;
struct gpu_libc_t   * g_gpulib_libc;
struct gpu_libglx_t   g_gpulib_libglx_data;
struct gpu_libglx_t * g_gpulib_libglx;
```

List of `gpulib_x11_wsi.h` procedures:

```c
static inline void GpuWsiGetLibcProcedureAddresses();
static inline void GpuWsiGetGLXProcedureAddresses();
static inline void GpuWsiGetGLProcedureAddresses();
static inline long GpuWsiShell(char * cmd, char * out);
static inline char * GpuWsiGetBasePath();
static inline void GpuWsiSetRelativeMouseMode(Display * dpy, Window win, int enabled);
static inline int GpuWsiIsExtensionSupported(char * extension);
static inline void GpuWsiCheckExtensions(int extension_count, char ** extensions);
static inline void GpuWsiX11Window(char * title, int title_bytes, int x, int y, int w, int h, int msaa_sample_count, Display ** out_display, Window * out_window);
static inline void GpuWsiWindow(char * window_title, int window_title_bytes, int window_width, int window_height, int msaa_samples, char * out_scancodes, Display ** out_dpy, Window * out_win);
static inline void GpuWsiSwap(Display * dpy, Window win);
static inline unsigned GpuWsiProgram(unsigned shader_type, char * shader_filepath);
static inline unsigned GpuWsiProgramVert(char * shader_filepath);
static inline unsigned GpuWsiProgramFrag(char * shader_filepath);
static inline int GpuWsiBinaryRgbImage(unsigned tex_id, int width, int height, int layer_count, char * img_binary_filepath);
static inline int GpuWsiBinaryRgbCubemap(unsigned tex_id, int width, int height, int layer_count, char * cbm_binary_filepath);
```

Special thanks to Nicolas [@nlguillemot](https://github.com/nlguillemot) and Andreas [@ands](https://github.com/ands)
for answering my OpenGL questions!
Micha [@vurtun](https://github.com/vurtun) for suggestions on how to improve the library!
Rich [@JodiTheTigger](https://github.com/JodiTheTigger) for helping me debugging a very hard problem I had!
Mārtiņš [@mmozeiko](https://github.com/mmozeiko) for explaining me why I had a serious problem on some Linux distro!

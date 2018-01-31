GpuLib
------

<img width="800px" src="https://i.imgur.com/dQEm83w.gif" />

GpuLib is a public domain header-only C library that uses 80 modern AZDO OpenGL procedures and reduces them down to 50
to draw 3D geometry, post-process images, asynchronously transfer and compute data on GPU.

The contract:

 * x64 Linux and X11 only. Doesn't target Windows, macOS, WebGL or OpenGL ES devices.
 * Not all modern OpenGL extensions are used, only those which are supported on low-end GPUs and latest Mesa 3D.
 * Data is guaranteed to be aligned, wrong alignment bugs are very hard to find, thus SSBOs and UBOs are not used.

Features:

 * ~70 ms of startup time (compared to ~500 ms of SDL 2.0.4), 56 ms of which are spent on a `glXChooseFBConfig` call.
 * 30 kb for 70 lines of Hello Triangle code: `./build.sh -Os && strip --strip-all main`, Ubuntu 18.04, Clang 5.0.1.
 * Minimum number of shared library dependencies: `libX11`, `libXrender`, `libXi`, `libdl`.

Supported GPUs with open source Mesa 3D driver:
 * AMD: r600 and higher.
 * Intel: gen7 and higher.
 * Nvidia: nvc0 and higher.

List of `gpulib.h` structs:

```c
struct gpu_cmd_t;
struct gpu_libgl_t;
```

List of `gpulib.h` enums:

```c
enum gpu_draw_mode_e;
enum gpu_buffer_format_e;
enum gpu_texture_format_e;
enum gpu_sampler_filter_e;
enum gpu_sampler_wrapping_e;
enum gpu_pixel_format_e;
enum gpu_pixel_type_e;
```

List of `gpulib.h` global variables:

```c
struct gpu_libgl_t   g_gpulib_libgl_data;
struct gpu_libgl_t * g_gpulib_libgl;
```

List of `gpulib.h` procedures:

```c
static inline void GpuSetDebugCallback(void * callback);
static inline void GpuDebugCallback(unsigned source, unsigned type, unsigned id, unsigned severity, int length, char * message, void * user_data);
static inline void * GpuMalloc(ptrdiff_t bytes, unsigned * out_buffer_id);
static inline void GpuMallocDeviceLocal(ptrdiff_t bytes, unsigned * out_buffer_id);
static inline unsigned * GpuMallocIndices(ptrdiff_t count, unsigned * out_indices_id);
static inline void GpuMallocIndicesDeviceLocal(ptrdiff_t count, unsigned * out_indices_id);
static inline struct gpu_cmd_t * GpuMallocCommands(ptrdiff_t count, unsigned * out_commands_id);
static inline void GpuMallocCommandsDeviceLocal(ptrdiff_t count, unsigned * out_commands_id);
static inline unsigned GpuMallocImage(enum gpu_texture_format_e format, int width, int height, int layer_count, int mipmap_count);
static inline unsigned GpuMallocCubemap(enum gpu_texture_format_e format, int width, int height, int layer_count, int mipmap_count);
static inline unsigned GpuMallocMultisampledImage(enum gpu_texture_format_e format, int width, int height, int layer_count, int msaa_samples);
static inline void * GpuMap(unsigned buffer_id, ptrdiff_t bytes_first, ptrdiff_t bytes_count);
static inline unsigned * GpuMapIndices(ptrdiff_t first, ptrdiff_t count);
static inline struct gpu_cmd_t * GpuMapCommands(ptrdiff_t first, ptrdiff_t count);
static inline unsigned GpuView(unsigned buffer_id, enum gpu_buffer_format_e format, ptrdiff_t bytes_first, ptrdiff_t bytes_count);
static inline unsigned GpuViewImage(unsigned tex_id, enum gpu_texture_format_e format, int layer_first, int layer_count, int mipmap_first, int mipmap_count);
static inline unsigned GpuViewCubemap(unsigned tex_id, enum gpu_texture_format_e format, int layer_first, int layer_count, int mipmap_first, int mipmap_count);
static inline unsigned GpuViewMultisampledImage(unsigned tex_id, enum gpu_texture_format_e format, int layer_first, int layer_count, int mipmap_first, int mipmap_count);
static inline unsigned GpuSampler(int max_anisotropy, enum gpu_sampler_filter_e min_filter, enum gpu_sampler_filter_e mag_filter, enum gpu_sampler_wrapping_e wrapping);
static inline unsigned GpuProgram(unsigned shader_type, char * shader_string);
static inline unsigned GpuProgramVertex(char * shader_string);
static inline unsigned GpuProgramFragment(char * shader_string);
static inline unsigned GpuProgramCompute(char * shader_string);
static inline unsigned GpuFramebuffer(unsigned color_tex_id_0, int color_tex_layer_0, unsigned color_tex_id_1, int color_tex_layer_1, unsigned color_tex_id_2, int color_tex_layer_2, unsigned color_tex_id_3, int color_tex_layer_3, unsigned depth_tex_id_0, int depth_tex_layer_0);
static inline unsigned GpuPipeline(unsigned vert_id, unsigned frag_id);
static inline void GpuBarrier();
static inline void * GpuFence();
static inline unsigned GpuQuery();
static inline void GpuUniformInt(unsigned program_id, int location, int count, int * value);
static inline void GpuUniformFloat4(unsigned program_id, int location, int count, float * value);
static inline int GpuFenceIsComplete(void * fence);
static inline void GpuQueryBeginTimeElapsed(unsigned query_id);
static inline void GpuQueryEndTimeElapsed();
static inline int GpuQueryIsResultAvailable(unsigned query_id);
static inline size_t GpuQueryGetResult(unsigned query_id);
static inline void GpuBindFramebuffer(unsigned fbo_id);
static inline void GpuBindIndices(unsigned indices_id);
static inline void GpuBindCommands(unsigned commands_id);
static inline void GpuBindSamplers(int first, int count, unsigned * sampler_ids);
static inline void GpuBindTextures(int first, int count, unsigned * texture_ids);
static inline void GpuBindImages(int first, int count, unsigned * texture_ids);
static inline void GpuBindPipeline(unsigned ppo_id);
static inline void GpuBindProgram(unsigned pro_id);
static inline void GpuDraw(enum gpu_draw_mode_e mode, unsigned first, unsigned count, unsigned instance_count);
static inline void GpuDrawIndirect(enum gpu_draw_mode_e mode, unsigned binded_commands_first, unsigned binded_commands_count);
static inline void GpuDispatch(int x, int y, int z);
static inline void GpuBlit(unsigned source_fbo_id, int source_color_id, int source_x, int source_y, int source_width, int source_height, unsigned target_fbo_id, int target_color_id, int target_x, int target_y, int target_width, int target_height);
static inline void GpuClear();
static inline void GpuEnable(unsigned flags);
static inline void GpuDisable(unsigned flags);
static inline void GpuViewport(int x, int y, int width, int height);
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
static inline unsigned GpuWsiProgramVertex(char * shader_filepath);
static inline unsigned GpuWsiProgramFragment(char * shader_filepath);
static inline unsigned GpuWsiProgramCompute(char * shader_filepath);
static inline int GpuWsiBinaryRgbImage(unsigned tex_id, int width, int height, int layer_count, char * img_binary_filepath);
static inline int GpuWsiBinaryRgbCubemap(unsigned tex_id, int width, int height, int layer_count, char * cbm_binary_filepath);
```

Special thanks to Nicolas [@nlguillemot](https://github.com/nlguillemot) and Andreas [@ands](https://github.com/ands)
for answering my OpenGL questions!
Micha [@vurtun](https://github.com/vurtun) for suggestions on how to improve the library!
Rich [@JodiTheTigger](https://github.com/JodiTheTigger) for helping me debugging a very hard problem I had!
Mārtiņš [@mmozeiko](https://github.com/mmozeiko) for explaining me why I had a serious problem on some Linux distro!

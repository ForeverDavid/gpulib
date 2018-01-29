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
 * `ppo`: Program Pipeline Object
 * `fbo`: Framebuffer Object
 * `xfb`: Transform Feedback Object

List of structs:

```c
struct gpu_cmd_t;
struct gpu_libc_t;
struct gpu_libglx_t;
struct gpu_libgl_t;
```

List of enums:

```c
enum gpu_mode_e;
enum gpu_buf_format_e;
enum gpu_tex_format_e;
enum gpu_smp_filter_e;
enum gpu_smp_wrapping_e;
enum gpu_pix_format_e;
enum gpu_pix_type_e;
```

List of global variables:

```c
struct gpu_libc_t     g_gpulib_libc_data;
struct gpu_libc_t   * g_gpulib_libc;
struct gpu_libglx_t   g_gpulib_libglx_data;
struct gpu_libglx_t * g_gpulib_libglx;
struct gpu_libgl_t    g_gpulib_libgl_data;
struct gpu_libgl_t  * g_gpulib_libgl;
```

List of procedures:

```c
static inline void GpuSysGetLibcProcedureAddresses();
static inline void GpuSysGetGLXProcedureAddresses();
static inline void GpuSysGetGLProcedureAddresses();
static inline long GpuSysShell(char * cmd, char * out);
static inline char * GpuSysGetBasePath();
static inline void GpuSysSetRelativeMouseMode(Display * dpy, Window win, int enabled);
static inline int GpuSysIsExtensionSupported(char * extension);
static inline void GpuSysCheckExtensions(int extension_count, char ** extensions);
static inline void GpuSysX11Window(char * title, int title_bytes, int x, int y, int w, int h, int msaa_sample_count, Display ** out_display, Window * out_window);
static inline void GpuWindow(char * window_title, int window_title_bytes, int window_width, int window_height, int msaa_samples, char * out_scancodes, Display ** out_dpy, Window * out_win);
static inline void * GpuMalloc(ptrdiff_t bytes, unsigned * out_buf_id);
static inline void * GpuCalloc(ptrdiff_t bytes, unsigned * out_buf_id);
static inline void GpuMallocDeviceLocal(ptrdiff_t bytes, unsigned * out_buf_id);
static inline void GpuCallocDeviceLocal(ptrdiff_t bytes, unsigned * out_buf_id);
static inline unsigned GpuCast(unsigned buf_id, enum gpu_buf_format_e format, ptrdiff_t bytes_first, ptrdiff_t bytes_count);
static inline unsigned * GpuMallocIndices(ptrdiff_t count, unsigned * out_idb_id);
static inline unsigned * GpuCallocIndices(ptrdiff_t count, unsigned * out_idb_id);
static inline struct gpu_cmd_t * GpuMallocCommands(ptrdiff_t count, unsigned * out_dib_id);
static inline struct gpu_cmd_t * GpuCallocCommands(ptrdiff_t count, unsigned * out_dib_id);
static inline void * GpuMap(unsigned buf_id, ptrdiff_t bytes_first, ptrdiff_t bytes_count);
static inline void * GpuMapCommands(ptrdiff_t bytes_first, ptrdiff_t bytes_count);
static inline unsigned GpuMallocImg(enum gpu_tex_format_e format, int width, int height, int layer_count, int mipmap_count);
static inline unsigned GpuMallocCbm(enum gpu_tex_format_e format, int width, int height, int layer_count, int mipmap_count);
static inline unsigned GpuMallocMsi(enum gpu_tex_format_e format, int width, int height, int layer_count, int msaa_samples);
static inline unsigned GpuCallocImg(enum gpu_tex_format_e format, int width, int height, int layer_count, int mipmap_count);
static inline unsigned GpuCallocCbm(enum gpu_tex_format_e format, int width, int height, int layer_count, int mipmap_count);
static inline unsigned GpuCallocMsi(enum gpu_tex_format_e format, int width, int height, int layer_count, int msaa_samples);
static inline unsigned GpuCastImg(unsigned tex_id, enum gpu_tex_format_e format, int layer_first, int layer_count, int mipmap_first, int mipmap_count);
static inline unsigned GpuCastCbm(unsigned tex_id, enum gpu_tex_format_e format, int layer_first, int layer_count, int mipmap_first, int mipmap_count);
static inline unsigned GpuCastMsi(unsigned tex_id, enum gpu_tex_format_e format, int layer_first, int layer_count, int mipmap_first, int mipmap_count);
static inline void GpuGetImg(unsigned tex_id, int layer, int x, int y, int width, int height, int count, int mipmap_level, enum gpu_pix_format_e pixel_format, enum gpu_pix_type_e pixel_type, unsigned pixels_bytes, void * pixels);
static inline void GpuSetImg(unsigned tex_id, int layer, int x, int y, int width, int height, int count, int mipmap_level, enum gpu_pix_format_e pixel_format, enum gpu_pix_type_e pixel_type, void * pixels);
static inline void GpuSetPix(unsigned tex_id, int layer, int x, int y, int width, int height, int count, int mipmap_level, enum gpu_pix_format_e pixel_format, enum gpu_pix_type_e pixel_type, void * pixel);
static inline void GpuGetCpi(unsigned tex_id, int layer, int x, int y, int width, int height, int count, int mipmap_level, unsigned pixels_bytes, void * pixels);
static inline void GpuSetCpi(unsigned tex_id, int layer, int x, int y, int width, int height, int count, int mipmap_level, enum gpu_tex_format_e compression_format, unsigned pixels_bytes, void * pixels);
static inline int GpuLoadRgbImgBinary(unsigned tex_id, int width, int height, int layer_count, char * img_binary_filepath);
static inline int GpuLoadRgbCbmBinary(unsigned tex_id, int width, int height, int layer_count, char * cbm_binary_filepath);
static inline unsigned GpuSmp(int max_anisotropy, enum gpu_smp_filter_e min_filter, enum gpu_smp_filter_e mag_filter, enum gpu_smp_wrapping_e wrapping);
static inline unsigned GpuPro(unsigned shader_type, char * shader_string);
static inline unsigned GpuProFile(unsigned shader_type, char * shader_filepath);
static inline unsigned GpuVert(char * shader_string);
static inline unsigned GpuFrag(char * shader_string);
static inline unsigned GpuVertFile(char * shader_filepath);
static inline unsigned GpuFragFile(char * shader_filepath);
static inline void GpuU32(unsigned program, int location, int count, unsigned * value);
static inline void GpuI32(unsigned program, int location, int count, int * value);
static inline void GpuF32(unsigned program, int location, int count, float * value);
static inline void GpuV2F(unsigned program, int location, int count, float * value);
static inline void GpuV3F(unsigned program, int location, int count, float * value);
static inline void GpuV4F(unsigned program, int location, int count, float * value);
static inline unsigned GpuPpo(unsigned vert_pro_id, unsigned frag_pro_id);
static inline unsigned GpuFbo(unsigned color_tex_id_0, int color_tex_layer_0, unsigned color_tex_id_1, int color_tex_layer_1, unsigned color_tex_id_2, int color_tex_layer_2, unsigned color_tex_id_3, int color_tex_layer_3, unsigned depth_tex_id_0, int depth_tex_layer_0);
static inline unsigned GpuXfb(unsigned buf_0_id, ptrdiff_t buf_0_bytes_first, ptrdiff_t buf_0_bytes_count, unsigned buf_1_id, ptrdiff_t buf_1_bytes_first, ptrdiff_t buf_1_bytes_count, unsigned buf_2_id, ptrdiff_t buf_2_bytes_first, ptrdiff_t buf_2_bytes_count, unsigned buf_3_id, ptrdiff_t buf_3_bytes_first, ptrdiff_t buf_3_bytes_count);
static inline unsigned GpuQuery();
static inline void GpuQueryBeginTimeElapsed(unsigned query_id);
static inline void GpuQueryEndTimeElapsed();
static inline int GpuQueryIsResultAvailable(unsigned query_id);
static inline size_t GpuQueryGetResult(unsigned query_id);
static inline void GpuBindFbo(unsigned fbo_id);
static inline void GpuBindXfb(unsigned xfb_id);
static inline void GpuBindIndices(unsigned idb_id);
static inline void GpuBindCommands(unsigned dib_id);
static inline void GpuBindTextures(int first, int count, unsigned * textures);
static inline void GpuBindSamplers(int first, int count, unsigned * samplers);
static inline void GpuBindPpo(unsigned ppo);
static inline void GpuDraw(enum gpu_mode_e mode, unsigned binded_dib_cmd_first, unsigned binded_dib_cmd_count);
static inline void GpuDrawXfb(enum gpu_mode_e mode, unsigned binded_dib_cmd_first, unsigned binded_dib_cmd_count);
static inline void GpuDrawOnce(enum gpu_mode_e mode, unsigned first, unsigned count, unsigned instance_count);
static inline void GpuDrawOnceXfb(enum gpu_mode_e mode, unsigned first, unsigned count, unsigned instance_count);
static inline void GpuBlit(unsigned source_fbo_id, int source_color_id, int source_x, int source_y, int source_width, int source_height, unsigned target_fbo_id, int target_color_id, int target_x, int target_y, int target_width, int target_height);
static inline void GpuBlitToScreen(unsigned source_fbo_id, int source_color_id, int source_x, int source_y, int source_width, int source_height, int screen_x, int screen_y, int screen_width, int screen_height);
static inline void GpuClear();
static inline void GpuSwap(Display * dpy, Window win);
static inline void GpuEnable(unsigned flags);
static inline void GpuDisable(unsigned flags);
static inline void GpuViewport(int x, int y, int width, int height);
static inline void * GpuFence();
static inline int GpuFenceIsComplete(void * fence);
static inline void GpuSetDebugCallback(void * callback);
static inline void GpuDebugCallback(unsigned source, unsigned type, unsigned id, unsigned severity, int length, char * message, void * userdata);
```

Special thanks to Nicolas [@nlguillemot](https://github.com/nlguillemot) and Andreas [@ands](https://github.com/ands)
for answering my OpenGL questions!
Micha [@vurtun](https://github.com/vurtun) for suggestions on how to improve the library!
Rich [@JodiTheTigger](https://github.com/JodiTheTigger) for helping me debugging a very hard problem I had!
Mārtiņš [@mmozeiko](https://github.com/mmozeiko) for explaining me why I had a serious problem on some Linux distro!

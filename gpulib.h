#pragma once

#ifndef GPULIB_MAX_PRINT_BYTES
#define GPULIB_MAX_PRINT_BYTES (4096)
#endif

#ifndef profB
#define profB(x)
#endif

#ifndef profE
#define profE(x)
#endif

#include "stdlib/stdlib.h"
#include <stddef.h>

struct gpu_cmd_t {
  unsigned count;
  unsigned instance_count;
  unsigned first;
  unsigned base_vertex;
  unsigned instance_first;
};

enum {
  gpu_depth_e = 0x0B71, // GL_DEPTH_TEST
};

enum {
  gpu_buf_map_flags_e = 0xC2, // GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT
};

enum gpu_draw_mode_e {
  gpu_points_e    = 0x0000, // GL_POINTS
  gpu_lines_e     = 0x0001, // GL_LINES
  gpu_triangles_e = 0x0004, // GL_TRIANGLES
};

enum gpu_buf_format_e {
  gpu_x_b8_e     = 0x8229, // GL_R8
  gpu_x_f16_e    = 0x822D, // GL_R16F
  gpu_x_f32_e    = 0x822E, // GL_R32F
  gpu_x_i8_e     = 0x8231, // GL_R8I
  gpu_x_i16_e    = 0x8233, // GL_R16I
  gpu_x_i32_e    = 0x8235, // GL_R32I
  gpu_x_u8_e     = 0x8232, // GL_R8UI
  gpu_x_u16_e    = 0x8234, // GL_R16UI
  gpu_x_u32_e    = 0x8236, // GL_R32UI
  gpu_xy_b8_e    = 0x822B, // GL_RG8
  gpu_xy_f16_e   = 0x822F, // GL_RG16F
  gpu_xy_f32_e   = 0x8230, // GL_RG32F
  gpu_xy_i8_e    = 0x8237, // GL_RG8I
  gpu_xy_i16_e   = 0x8239, // GL_RG16I
  gpu_xy_i32_e   = 0x823B, // GL_RG32I
  gpu_xy_u8_e    = 0x8238, // GL_RG8UI
  gpu_xy_u16_e   = 0x823A, // GL_RG16UI
  gpu_xy_u32_e   = 0x823C, // GL_RG32UI
  gpu_xyz_f32_e  = 0x8815, // GL_RGB32F
  gpu_xyz_i32_e  = 0x8D83, // GL_RGB32I
  gpu_xyz_u32_e  = 0x8D71, // GL_RGB32UI
  gpu_xyzw_b8_e  = 0x8058, // GL_RGBA8
  gpu_xyzw_f16_e = 0x881A, // GL_RGBA16F
  gpu_xyzw_f32_e = 0x8814, // GL_RGBA32F
  gpu_xyzw_i8_e  = 0x8D8E, // GL_RGBA8I
  gpu_xyzw_i16_e = 0x8D88, // GL_RGBA16I
  gpu_xyzw_i32_e = 0x8D82, // GL_RGBA32I
  gpu_xyzw_u8_e  = 0x8D7C, // GL_RGBA8UI
  gpu_xyzw_u16_e = 0x8D76, // GL_RGBA16UI
  gpu_xyzw_u32_e = 0x8D70, // GL_RGBA32UI
};

enum gpu_tex_format_e {
  gpu_d_f32_e    = 0x8CAC, // GL_DEPTH_COMPONENT32F
  gpu_rgb_b8_e   = 0x8051, // GL_RGB8
  gpu_rgba_b8_e  = 0x8058, // GL_RGBA8
  gpu_srgb_b8_e  = 0x8C41, // GL_SRGB8
  gpu_srgba_b8_e = 0x8C43, // GL_SRGB8_ALPHA8
  gpu_rgba_f32_e = 0x8814, // GL_RGBA32F
};

enum gpu_smp_filter_e {
  gpu_nearest_e                = 0x2600, // GL_NEAREST
  gpu_linear_e                 = 0x2601, // GL_LINEAR
  gpu_nearest_mipmap_nearest_e = 0x2700, // GL_NEAREST_MIPMAP_NEAREST
  gpu_linear_mipmap_nearest_e  = 0x2701, // GL_LINEAR_MIPMAP_NEAREST
  gpu_nearest_mipmap_linear_e  = 0x2702, // GL_NEAREST_MIPMAP_LINEAR
  gpu_linear_mipmap_linear_e   = 0x2703, // GL_LINEAR_MIPMAP_LINEAR
};

enum gpu_smp_wrapping_e {
  gpu_repeat_e                 = 0x2901, // GL_REPEAT
  gpu_clamp_to_edge_e          = 0x812F, // GL_CLAMP_TO_EDGE
  gpu_clamp_to_border_e        = 0x812D, // GL_CLAMP_TO_BORDER
  gpu_mirrored_repeat_e        = 0x8370, // GL_MIRRORED_REPEAT
  gpu_mirror_clamp_e           = 0x8742, // GL_MIRROR_CLAMP
  gpu_mirror_clamp_to_edge_e   = 0x8743, // GL_MIRROR_CLAMP_TO_EDGE
  gpu_mirror_clamp_to_border_e = 0x8912, // GL_MIRROR_CLAMP_TO_BORDER
};

enum gpu_pix_format_e {
  gpu_d_e    = 0x1902, // GL_DEPTH_COMPONENT
  gpu_rgb_e  = 0x1907, // GL_RGB
  gpu_bgr_e  = 0x80E0, // GL_BGR
  gpu_rgba_e = 0x1908, // GL_RGBA
  gpu_bgra_e = 0x80E1, // GL_BGRA
};

enum gpu_pix_type_e {
  gpu_i8_e  = 0x1400, // GL_BYTE
  gpu_i16_e = 0x1402, // GL_SHORT
  gpu_i32_e = 0x1404, // GL_INT
  gpu_u8_e  = 0x1401, // GL_UNSIGNED_BYTE
  gpu_u16_e = 0x1403, // GL_UNSIGNED_SHORT
  gpu_u32_e = 0x1405, // GL_UNSIGNED_INT
  gpu_f32_e = 0x1406, // GL_FLOAT
};

#define GPULIB_VERT_HEADER                                     \
  "#version 330"                                          "\n" \
  "#extension GL_ARB_gpu_shader5                : enable" "\n" \
  "#extension GL_ARB_shader_precision           : enable" "\n" \
  "#extension GL_ARB_enhanced_layouts           : enable" "\n" \
  "#extension GL_ARB_texture_cube_map_array     : enable" "\n" \
  "#extension GL_ARB_separate_shader_objects    : enable" "\n" \
  "#extension GL_ARB_shading_language_420pack   : enable" "\n" \
  "#extension GL_ARB_shading_language_packing   : enable" "\n" \
  "#extension GL_ARB_explicit_uniform_location  : enable" "\n" \
  "#extension GL_ARB_fragment_coord_conventions : enable" "\n" \
  "out gl_PerVertex { vec4 gl_Position; };"               "\n" \
  ""                                                      "\n"

#define GPULIB_FRAG_HEADER                                     \
  "#version 330"                                          "\n" \
  "#extension GL_ARB_gpu_shader5                : enable" "\n" \
  "#extension GL_ARB_shader_precision           : enable" "\n" \
  "#extension GL_ARB_enhanced_layouts           : enable" "\n" \
  "#extension GL_ARB_texture_cube_map_array     : enable" "\n" \
  "#extension GL_ARB_separate_shader_objects    : enable" "\n" \
  "#extension GL_ARB_shading_language_420pack   : enable" "\n" \
  "#extension GL_ARB_shading_language_packing   : enable" "\n" \
  "#extension GL_ARB_explicit_uniform_location  : enable" "\n" \
  "#extension GL_ARB_fragment_coord_conventions : enable" "\n" \
  "layout(origin_upper_left) in vec4 gl_FragCoord;"       "\n" \
  ""                                                      "\n"

struct gpu_libc_t {
  int (*access)(char *, int);
  void * (*calloc)(size_t, size_t);
  int (*fgetc)(int *);
  void (*free)(void *);
  pid_t (*getpid)();
  int (*pclose)(int *);
  int * (*popen)(char *, char *);
  ssize_t (*readlink)(char *, char *, size_t);
  void * (*realloc)(void *, size_t);
  char * (*setlocale)(int, char *);
  char * (*strcat)(char *, char *);
  int (*strcmp)(char *, char *);
  size_t (*strlen)(char *);
  char * (*strndup)(char *, size_t);
  char * (*strrchr)(char *, int);
  long (*strtol)(char *, char **, int);
  int (*usleep)(unsigned);
} g_gpulib_libc_data = {0};

struct gpu_libc_t * g_gpulib_libc = &g_gpulib_libc_data;

struct gpu_libgl_t {
  void (*AttachShader)(unsigned, unsigned);
  void (*BeginQuery)(unsigned, unsigned);
  void (*BeginTransformFeedback)(unsigned);
  void (*BindBuffer)(unsigned, unsigned);
  void (*BindFramebuffer)(unsigned, unsigned);
  void (*BindProgramPipeline)(unsigned);
  void (*BindSamplers)(int, int, unsigned *);
  void (*BindTextures)(int, int, unsigned *);
  void (*BindTransformFeedback)(unsigned, unsigned);
  void (*BindVertexArray)(unsigned);
  void (*BlendFunc)(unsigned, unsigned);
  void (*BlitNamedFramebuffer)(unsigned, unsigned, int, int, int, int, int, int, int, int, unsigned, unsigned);
  void (*BufferStorage)(unsigned, ptrdiff_t, void *, unsigned);
  void (*Clear)(unsigned);
  void (*ClearDepth)(double);
  void (*ClearTexSubImage)(unsigned, int, int, int, int, int, int, int, unsigned, unsigned, void *);
  void (*ClipControl)(unsigned, unsigned);
  void (*CompileShader)(unsigned);
  void (*CreateBuffers)(int, unsigned *);
  void (*CreateFramebuffers)(int, unsigned *);
  unsigned (*CreateProgram)();
  void (*CreateProgramPipelines)(int, unsigned *);
  void (*CreateSamplers)(int, unsigned *);
  unsigned (*CreateShader)(unsigned);
  void (*CreateTextures)(unsigned, int, unsigned *);
  void (*CreateTransformFeedbacks)(int, unsigned *);
  void (*CreateVertexArrays)(int, unsigned *);
  void (*DebugMessageCallback)(void *, void *);
  void (*DeleteBuffers)(int, unsigned *);
  void (*DeleteFramebuffers)(int, unsigned *);
  void (*DeleteProgram)(unsigned);
  void (*DeleteProgramPipelines)(int, unsigned *);
  void (*DeleteQueries)(int, unsigned *);
  void (*DeleteSamplers)(int, unsigned *);
  void (*DeleteShader)(unsigned);
  void (*DeleteSync)(void *);
  void (*DeleteTextures)(int, unsigned *);
  void (*DeleteTransformFeedbacks)(int, unsigned *);
  void (*DepthFunc)(unsigned);
  void (*DepthRange)(double, double);
  void (*DetachShader)(unsigned, unsigned);
  void (*Disable)(unsigned);
  void (*DrawArraysInstanced)(unsigned, unsigned, unsigned, unsigned);
  void (*Enable)(unsigned);
  void (*EndQuery)(unsigned);
  void (*EndTransformFeedback)();
  void * (*FenceSync)(unsigned, unsigned);
  void (*FrontFace)(unsigned);
  void (*GenBuffers)(int, unsigned *);
  void (*GenerateTextureMipmap)(unsigned);
  void (*GenQueries)(int, unsigned *);
  void (*GenTextures)(int, unsigned *);
  void (*GetIntegerv)(unsigned, int *);
  void (*GetProgramInfoLog)(unsigned, int, int *, char *);
  void (*GetProgramiv)(unsigned, unsigned, int *);
  void (*GetQueryObjectui64v)(unsigned, unsigned, size_t *);
  void (*GetShaderInfoLog)(unsigned, int, int *, char *);
  void (*GetShaderiv)(unsigned, unsigned, int *);
  char * (*GetStringi)(unsigned, unsigned);
  void (*GetSynciv)(void *, unsigned, int, int *, int *);
  void (*GetTextureLevelParameteriv)(unsigned, int, unsigned, int *);
  void (*GetTextureSubImage)(unsigned, int, int, int, int, int, int, int, unsigned, unsigned, unsigned, void *);
  void (*LinkProgram)(unsigned);
  void * (*MapBufferRange)(unsigned, ptrdiff_t, ptrdiff_t, unsigned);
  void * (*MapNamedBufferRange)(unsigned, ptrdiff_t, ptrdiff_t, unsigned);
  void (*MultiDrawElementsIndirect)(unsigned, unsigned, void *, int, int);
  void (*NamedBufferStorage)(unsigned, ptrdiff_t, void *, unsigned);
  void (*NamedFramebufferDrawBuffer)(unsigned, int);
  void (*NamedFramebufferDrawBuffers)(unsigned, int, int *);
  void (*NamedFramebufferReadBuffer)(unsigned, int);
  void (*NamedFramebufferTextureLayer)(unsigned, int, unsigned, int, int);
  void (*ProgramParameteri)(unsigned, unsigned, int);
  void (*ProgramUniform1iv)(unsigned, int, int, int *);
  void (*ProgramUniform4fv)(unsigned, int, int, float *);
  void (*SamplerParameteri)(unsigned, unsigned, int);
  void (*Scissor)(int, int, int, int);
  void (*ShaderSource)(unsigned, int, char **, int *);
  void (*TextureBufferRange)(unsigned, unsigned, unsigned, ptrdiff_t, ptrdiff_t);
  void (*TextureStorage3D)(unsigned, int, unsigned, int, int, int);
  void (*TextureStorage3DMultisample)(unsigned, int, unsigned, int, int, int, int);
  void (*TextureSubImage3D)(unsigned, int, int, int, int, int, int, int, unsigned, unsigned, void *);
  void (*TextureView)(unsigned, unsigned, unsigned, unsigned, int, int, int, int);
  void (*TransformFeedbackBufferRange)(unsigned, int, unsigned, ptrdiff_t, ptrdiff_t);
  void (*TransformFeedbackVaryings)(unsigned, int, char **, unsigned);
  void (*UseProgramStages)(unsigned, unsigned, unsigned);
  void (*Viewport)(int, int, int, int);
} g_gpulib_libgl_data = {0};

struct gpu_libgl_t * g_gpulib_libgl = &g_gpulib_libgl_data;

static inline void GpuSetDebugCallback(void * callback) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  gl->DebugMessageCallback(callback, NULL);
  profE(__func__);
}

static inline void GpuDebugCallback(unsigned source, unsigned type, unsigned id, unsigned severity, int length, char * message, void * user_data) {
  char * GL_ERROR_SOURCE[] = {
    "API",
    "WINDOW SYSTEM",
    "SHADER COMPILER",
    "THIRD PARTY",
    "APPLICATION",
    "OTHER"
  };

  char * GL_ERROR_SEVERITY[] = {
    "HIGH",
    "MEDIUM",
    "LOW",
    "NOTIFICATION"
  };

  char * GL_ERROR_TYPE[] = {
    "ERROR",
    "DEPRECATED BEHAVIOR",
    "UNDEFINED DEHAVIOUR",
    "PORTABILITY",
    "PERFORMANCE",
    "OTHER"
  };

  stdlib_nprintf(GPULIB_MAX_PRINT_BYTES,
    "[GpuLib] OpenGL Debug Callback: ID: %u, Source: %s, Severity: %s, Type: %s\n"
    "[GpuLib] Message: %s\n\n",
    id,
    GL_ERROR_SOURCE[source - 0x8246], // GL_DEBUG_SOURCE_API
    GL_ERROR_SEVERITY[severity != 0x826B ? severity - 0x9146 : 3], // GL_DEBUG_SEVERITY_NOTIFICATION, GL_DEBUG_SEVERITY_HIGH
    GL_ERROR_TYPE[type - 0x824C], // GL_DEBUG_TYPE_ERROR
    message);
}

static inline void * GpuMalloc(ptrdiff_t bytes, unsigned * out_buf_id) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  unsigned buf_id = 0;
  gl->CreateBuffers(1, &buf_id);
  out_buf_id[0] = buf_id;
  gl->NamedBufferStorage(buf_id, bytes, NULL, 0xC2); // GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT
  void * buf_ptr = gl->MapNamedBufferRange(buf_id, 0, bytes, 0xC2);
  profE(__func__);
  return buf_ptr;
}

static inline void * GpuCalloc(ptrdiff_t bytes, unsigned * out_buf_id) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  void * buf_ptr = GpuMalloc(bytes, out_buf_id);
  memset(buf_ptr, 0, bytes);
  profE(__func__);
  return buf_ptr;
}

static inline void GpuMallocDeviceLocal(ptrdiff_t bytes, unsigned * out_buf_id) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  unsigned buf_id = 0;
  gl->CreateBuffers(1, &buf_id);
  out_buf_id[0] = buf_id;
  gl->NamedBufferStorage(buf_id, bytes, NULL, 0);
  profE(__func__);
}

static inline void GpuCallocDeviceLocal(ptrdiff_t bytes, unsigned * out_buf_id) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  __auto_type libc = g_gpulib_libc;
  unsigned buf_id = 0;
  gl->CreateBuffers(1, &buf_id);
  out_buf_id[0] = buf_id;
  void * data = libc->calloc(1, bytes);
  gl->NamedBufferStorage(buf_id, bytes, data, 0);
  libc->free(data);
  profE(__func__);
}

static inline unsigned * GpuMallocIndices(ptrdiff_t count, unsigned * out_idb_id) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  unsigned idb_id = 0;
  gl->GenBuffers(1, &idb_id);
  out_idb_id[0] = idb_id;
  gl->BindBuffer(0x8893, idb_id); // GL_ELEMENT_ARRAY_BUFFER
  gl->BufferStorage(0x8893, count * sizeof(unsigned), NULL, 0xC2); // GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT
  unsigned * idb_ptr = gl->MapBufferRange(0x8893, 0, count * sizeof(unsigned), 0xC2);
  gl->BindBuffer(0x8893, 0);
  profE(__func__);
  return idb_ptr;
}

static inline unsigned * GpuCallocIndices(ptrdiff_t count, unsigned * out_idb_id) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  unsigned * idb_ptr = GpuMallocIndices(count, out_idb_id);
  memset(idb_ptr, 0, count * sizeof(unsigned));
  profE(__func__);
  return idb_ptr;
}

static inline void GpuMallocIndicesDeviceLocal(ptrdiff_t count, unsigned * out_idb_id) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  unsigned idb_id = 0;
  gl->GenBuffers(1, &idb_id);
  out_idb_id[0] = idb_id;
  gl->BindBuffer(0x8893, idb_id); // GL_ELEMENT_ARRAY_BUFFER
  gl->BufferStorage(0x8893, count * sizeof(unsigned), NULL, 0);
  gl->BindBuffer(0x8893, 0);
  profE(__func__);
}

static inline void GpuCallocIndicesDeviceLocal(ptrdiff_t count, unsigned * out_idb_id) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  __auto_type libc = g_gpulib_libc;
  unsigned idb_id = 0;
  gl->GenBuffers(1, &idb_id);
  out_idb_id[0] = idb_id;
  void * data = libc->calloc(1, count * sizeof(unsigned));
  gl->BindBuffer(0x8893, idb_id); // GL_ELEMENT_ARRAY_BUFFER
  gl->BufferStorage(0x8893, count * sizeof(unsigned), data, 0);
  gl->BindBuffer(0x8893, 0);
  libc->free(data);
  profE(__func__);
}

static inline struct gpu_cmd_t * GpuMallocCommands(ptrdiff_t count, unsigned * out_dib_id) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  unsigned dib_id = 0;
  gl->GenBuffers(1, &dib_id);
  out_dib_id[0] = dib_id;
  gl->BindBuffer(0x8F3F, dib_id); // GL_DRAW_INDIRECT_BUFFER
  gl->BufferStorage(0x8F3F, count * sizeof(struct gpu_cmd_t), NULL, 0xC2); // GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT
  struct gpu_cmd_t * dib_ptr = gl->MapBufferRange(0x8F3F, 0, count * sizeof(struct gpu_cmd_t), 0xC2);
  gl->BindBuffer(0x8F3F, 0);
  profE(__func__);
  return dib_ptr;
}

static inline struct gpu_cmd_t * GpuCallocCommands(ptrdiff_t count, unsigned * out_dib_id) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  struct gpu_cmd_t * dib_ptr = GpuMallocCommands(count, out_dib_id);
  memset(dib_ptr, 0, count * sizeof(struct gpu_cmd_t));
  profE(__func__);
  return dib_ptr;
}

static inline void GpuMallocCommandsDeviceLocal(ptrdiff_t count, unsigned * out_dib_id) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  unsigned dib_id = 0;
  gl->GenBuffers(1, &dib_id);
  out_dib_id[0] = dib_id;
  gl->BindBuffer(0x8F3F, dib_id); // GL_DRAW_INDIRECT_BUFFER
  gl->BufferStorage(0x8F3F, count * sizeof(struct gpu_cmd_t), NULL, 0);
  gl->BindBuffer(0x8F3F, 0);
  profE(__func__);
}

static inline void GpuCallocCommandsDeviceLocal(ptrdiff_t count, unsigned * out_dib_id) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  __auto_type libc = g_gpulib_libc;
  unsigned dib_id = 0;
  gl->GenBuffers(1, &dib_id);
  out_dib_id[0] = dib_id;
  void * data = libc->calloc(1, count * sizeof(struct gpu_cmd_t));
  gl->BindBuffer(0x8F3F, dib_id); // GL_DRAW_INDIRECT_BUFFER
  gl->BufferStorage(0x8F3F, count * sizeof(struct gpu_cmd_t), data, 0);
  gl->BindBuffer(0x8F3F, 0);
  libc->free(data);
  profE(__func__);
}

static inline unsigned GpuMallocImg(enum gpu_tex_format_e format, int width, int height, int layer_count, int mipmap_count) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  unsigned tex_id = 0;
  gl->CreateTextures(0x8C1A, 1, &tex_id); // GL_TEXTURE_2D_ARRAY
  if (width != height && mipmap_count > 1)
    stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "[GpuLib] Warning: Rectangle image (width: %d, height: %d) is set to have more than one mipmap (mipmap_count: %d).\n\n", width, height, mipmap_count);
  if (width / (1 << (mipmap_count - 1)) < 1)
    stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "[GpuLib] Warning: Image (width: %d) mipmap count (mipmap_count: %d) is greater than the max count of %d.\n\n", width, mipmap_count, stdlib_log2i(width) + 1);
  gl->TextureStorage3D(tex_id, mipmap_count, format, width, height, layer_count);
  profE(__func__);
  return tex_id;
}

static inline unsigned GpuMallocCbm(enum gpu_tex_format_e format, int width, int height, int layer_count, int mipmap_count) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  unsigned tex_id = 0;
  gl->CreateTextures(0x9009, 1, &tex_id); // GL_TEXTURE_CUBE_MAP_ARRAY
  if (width != height)
    stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "[GpuLib] Warning: Rectangle cubemap (width: %d, height: %d).\n\n", width, height);
  if (width / (1 << (mipmap_count - 1)) < 1)
    stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "[GpuLib] Warning: Cubemap (width: %d) mipmap count (mipmap_count: %d) is greater than the max count of %d.\n\n", width, mipmap_count, stdlib_log2i(width) + 1);
  gl->TextureStorage3D(tex_id, mipmap_count, format, width, height, layer_count * 6);
  profE(__func__);
  return tex_id;
}

static inline unsigned GpuMallocMsi(enum gpu_tex_format_e format, int width, int height, int layer_count, int msaa_samples) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  unsigned tex_id = 0;
  gl->CreateTextures(0x9102, 1, &tex_id); // GL_TEXTURE_2D_MULTISAMPLE_ARRAY
  gl->TextureStorage3DMultisample(tex_id, msaa_samples, format, width, height, layer_count, 0);
  profE(__func__);
  return tex_id;
}

static inline unsigned GpuCallocImg(enum gpu_tex_format_e format, int width, int height, int layer_count, int mipmap_count) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  unsigned tex_id = GpuMallocImg(format, width, height, layer_count, mipmap_count);
  switch (format) {
    break; case 0x8CAC: { for (int i = 0; i < mipmap_count; i += 1) gl->ClearTexSubImage(tex_id, i, 0, 0, 0, width / (1 << i), height / (1 << i), layer_count, 0x1902, 0x1406, (float [1]){0}); }                  // GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_FLOAT
    break; case 0x8051: { for (int i = 0; i < mipmap_count; i += 1) gl->ClearTexSubImage(tex_id, i, 0, 0, 0, width / (1 << i), height / (1 << i), layer_count, 0x1907, 0x1400, (unsigned char [3]){0, 0, 0}); }    // GL_RGB8, GL_RGB, GL_BYTE
    break; case 0x8058: { for (int i = 0; i < mipmap_count; i += 1) gl->ClearTexSubImage(tex_id, i, 0, 0, 0, width / (1 << i), height / (1 << i), layer_count, 0x1908, 0x1400, (unsigned char [4]){0, 0, 0, 0}); } // GL_RGBA8, GL_RGBA, GL_BYTE
    break; case 0x8C41: { for (int i = 0; i < mipmap_count; i += 1) gl->ClearTexSubImage(tex_id, i, 0, 0, 0, width / (1 << i), height / (1 << i), layer_count, 0x1907, 0x1400, (unsigned char [3]){0, 0, 0}); }    // GL_SRGB8, GL_RGB, GL_BYTE
    break; case 0x8C43: { for (int i = 0; i < mipmap_count; i += 1) gl->ClearTexSubImage(tex_id, i, 0, 0, 0, width / (1 << i), height / (1 << i), layer_count, 0x1908, 0x1400, (unsigned char [4]){0, 0, 0, 0}); } // GL_SRGB8_ALPHA8, GL_RGBA, GL_BYTE
    break; case 0x8814: { for (int i = 0; i < mipmap_count; i += 1) gl->ClearTexSubImage(tex_id, i, 0, 0, 0, width / (1 << i), height / (1 << i), layer_count, 0x1908, 0x1406, (float [4]){0, 0, 0, 0}); }         // GL_RGBA32F, GL_RGBA, GL_FLOAT
  }
  profE(__func__);
  return tex_id;
}

static inline unsigned GpuCallocCbm(enum gpu_tex_format_e format, int width, int height, int layer_count, int mipmap_count) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  unsigned tex_id = GpuMallocCbm(format, width, height, layer_count, mipmap_count);
  switch (format) {
    break; case 0x8CAC: { for (int i = 0; i < mipmap_count; i += 1) gl->ClearTexSubImage(tex_id, i, 0, 0, 0, width / (1 << i), height / (1 << i), layer_count * 6, 0x1902, 0x1406, (float [1]){0}); }                  // GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_FLOAT
    break; case 0x8051: { for (int i = 0; i < mipmap_count; i += 1) gl->ClearTexSubImage(tex_id, i, 0, 0, 0, width / (1 << i), height / (1 << i), layer_count * 6, 0x1907, 0x1400, (unsigned char [3]){0, 0, 0}); }    // GL_RGB8, GL_RGB, GL_BYTE
    break; case 0x8058: { for (int i = 0; i < mipmap_count; i += 1) gl->ClearTexSubImage(tex_id, i, 0, 0, 0, width / (1 << i), height / (1 << i), layer_count * 6, 0x1908, 0x1400, (unsigned char [4]){0, 0, 0, 0}); } // GL_RGBA8, GL_RGBA, GL_BYTE
    break; case 0x8C41: { for (int i = 0; i < mipmap_count; i += 1) gl->ClearTexSubImage(tex_id, i, 0, 0, 0, width / (1 << i), height / (1 << i), layer_count * 6, 0x1907, 0x1400, (unsigned char [3]){0, 0, 0}); }    // GL_SRGB8, GL_RGB, GL_BYTE
    break; case 0x8C43: { for (int i = 0; i < mipmap_count; i += 1) gl->ClearTexSubImage(tex_id, i, 0, 0, 0, width / (1 << i), height / (1 << i), layer_count * 6, 0x1908, 0x1400, (unsigned char [4]){0, 0, 0, 0}); } // GL_SRGB8_ALPHA8, GL_RGBA, GL_BYTE
    break; case 0x8814: { for (int i = 0; i < mipmap_count; i += 1) gl->ClearTexSubImage(tex_id, i, 0, 0, 0, width / (1 << i), height / (1 << i), layer_count * 6, 0x1908, 0x1406, (float [4]){0, 0, 0, 0}); }         // GL_RGBA32F, GL_RGBA, GL_FLOAT
  }
  profE(__func__);
  return tex_id;
}

static inline unsigned GpuCallocMsi(enum gpu_tex_format_e format, int width, int height, int layer_count, int msaa_samples) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  unsigned tex_id = GpuMallocMsi(format, width, height, layer_count, msaa_samples);
  switch (format) {
    break; case 0x8CAC: { gl->ClearTexSubImage(tex_id, 0, 0, 0, 0, width, height, layer_count, 0x1902, 0x1406, (float [1]){0}); }                  // GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_FLOAT
    break; case 0x8051: { gl->ClearTexSubImage(tex_id, 0, 0, 0, 0, width, height, layer_count, 0x1907, 0x1400, (unsigned char [3]){0, 0, 0}); }    // GL_RGB8, GL_RGB, GL_BYTE
    break; case 0x8058: { gl->ClearTexSubImage(tex_id, 0, 0, 0, 0, width, height, layer_count, 0x1908, 0x1400, (unsigned char [4]){0, 0, 0, 0}); } // GL_RGBA8, GL_RGBA, GL_BYTE
    break; case 0x8C41: { gl->ClearTexSubImage(tex_id, 0, 0, 0, 0, width, height, layer_count, 0x1907, 0x1400, (unsigned char [3]){0, 0, 0}); }    // GL_SRGB8, GL_RGB, GL_BYTE
    break; case 0x8C43: { gl->ClearTexSubImage(tex_id, 0, 0, 0, 0, width, height, layer_count, 0x1908, 0x1400, (unsigned char [4]){0, 0, 0, 0}); } // GL_SRGB8_ALPHA8, GL_RGBA, GL_BYTE
    break; case 0x8814: { gl->ClearTexSubImage(tex_id, 0, 0, 0, 0, width, height, layer_count, 0x1908, 0x1406, (float [4]){0, 0, 0, 0}); }         // GL_RGBA32F, GL_RGBA, GL_FLOAT
  }
  profE(__func__);
  return tex_id;
}

static inline void * GpuMap(unsigned buf_id, ptrdiff_t bytes_first, ptrdiff_t bytes_count) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  void * buf_ptr = gl->MapNamedBufferRange(buf_id, bytes_first, bytes_count, 0xC2); // GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT
  profE(__func__);
  return buf_ptr;
}

static inline void * GpuMapIndices(ptrdiff_t bytes_first, ptrdiff_t bytes_count) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  void * buf_ptr = gl->MapBufferRange(0x8893, bytes_first, bytes_count, 0xC2); // GL_ELEMENT_ARRAY_BUFFER, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT
  profE(__func__);
  return buf_ptr;
}

static inline void * GpuMapCommands(ptrdiff_t bytes_first, ptrdiff_t bytes_count) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  void * buf_ptr = gl->MapBufferRange(0x8F3F, bytes_first, bytes_count, 0xC2); // GL_DRAW_INDIRECT_BUFFER, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT
  profE(__func__);
  return buf_ptr;
}

static inline unsigned GpuCast(unsigned buf_id, enum gpu_buf_format_e format, ptrdiff_t bytes_first, ptrdiff_t bytes_count) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  unsigned tex_id = 0;
  gl->CreateTextures(0x8C2A, 1, &tex_id); // GL_TEXTURE_BUFFER
  gl->TextureBufferRange(tex_id, format, buf_id, bytes_first, bytes_count);
  profE(__func__);
  return tex_id;
}

static inline unsigned GpuCastImg(
    unsigned tex_id, enum gpu_tex_format_e format, int layer_first, int layer_count, int mipmap_first, int mipmap_count)
{
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  unsigned new_tex_id = 0;
  gl->GenTextures(1, &new_tex_id);
  gl->TextureView(new_tex_id, 0x8C1A, tex_id, format, mipmap_first, mipmap_count, layer_first, layer_count); // GL_TEXTURE_2D_ARRAY
  profE(__func__);
  return new_tex_id;
}

static inline unsigned GpuCastCbm(
    unsigned tex_id, enum gpu_tex_format_e format, int layer_first, int layer_count, int mipmap_first, int mipmap_count)
{
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  unsigned new_tex_id = 0;
  gl->GenTextures(1, &new_tex_id);
  gl->TextureView(new_tex_id, 0x9009, tex_id, format, mipmap_first, mipmap_count, layer_first * 6, layer_count * 6); // GL_TEXTURE_CUBE_MAP_ARRAY
  profE(__func__);
  return new_tex_id;
}

static inline unsigned GpuCastMsi(
    unsigned tex_id, enum gpu_tex_format_e format, int layer_first, int layer_count, int mipmap_first, int mipmap_count)
{
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  unsigned new_tex_id = 0;
  gl->GenTextures(1, &new_tex_id);
  gl->TextureView(new_tex_id, 0x9102, tex_id, format, mipmap_first, mipmap_count, layer_first, layer_count); // GL_TEXTURE_2D_MULTISAMPLE_ARRAY
  profE(__func__);
  return new_tex_id;
}

static inline void GpuGetImg(
    unsigned tex_id, int layer, int x, int y, int width, int height, int count, int mipmap_level,
    enum gpu_pix_format_e pixel_format, enum gpu_pix_type_e pixel_type, unsigned pixels_bytes, void * pixels)
{
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  gl->GetTextureSubImage(tex_id, mipmap_level, x, y, layer, width, height, count, pixel_format, pixel_type, pixels_bytes, pixels);
  profE(__func__);
}

static inline void GpuSetImg(
    unsigned tex_id, int layer, int x, int y, int width, int height, int count, int mipmap_level,
    enum gpu_pix_format_e pixel_format, enum gpu_pix_type_e pixel_type, void * pixels)
{
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  gl->TextureSubImage3D(tex_id, mipmap_level, x, y, layer, width, height, count, pixel_format, pixel_type, pixels);
  profE(__func__);
}

static inline void GpuSetPix(
    unsigned tex_id, int layer, int x, int y, int width, int height, int count, int mipmap_level,
    enum gpu_pix_format_e pixel_format, enum gpu_pix_type_e pixel_type, void * pixel)
{
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  gl->ClearTexSubImage(tex_id, mipmap_level, x, y, layer, width, height, count, pixel_format, pixel_type, pixel);
  profE(__func__);
}

static inline unsigned GpuSmp(
    int max_anisotropy, enum gpu_smp_filter_e min_filter, enum gpu_smp_filter_e mag_filter, enum gpu_smp_wrapping_e wrapping)
{
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  unsigned smp_id = 0;
  gl->CreateSamplers(1, &smp_id);
  if (max_anisotropy > 0)
    gl->SamplerParameteri(smp_id, 0x84FE, max_anisotropy); // GL_TEXTURE_MAX_ANISOTROPY_EXT
  gl->SamplerParameteri(smp_id, 0x2801, min_filter);       // GL_TEXTURE_MIN_FILTER
  gl->SamplerParameteri(smp_id, 0x2800, mag_filter);       // GL_TEXTURE_MAG_FILTER
  gl->SamplerParameteri(smp_id, 0x2802, wrapping);         // GL_TEXTURE_WRAP_S
  gl->SamplerParameteri(smp_id, 0x2803, wrapping);         // GL_TEXTURE_WRAP_T
  gl->SamplerParameteri(smp_id, 0x8072, wrapping);         // GL_TEXTURE_WRAP_R
  profE(__func__);
  return smp_id;
}

static inline unsigned GpuPro(unsigned shader_type, char * shader_string)
{
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  unsigned shader_id = gl->CreateShader(shader_type);

  gl->ShaderSource(shader_id, 1, (char **)&shader_string, NULL);
  gl->CompileShader(shader_id);

  {
    int is_compiled = 0;
    gl->GetShaderiv(shader_id, 0x8B81, &is_compiled); // GL_COMPILE_STATUS
    if (!is_compiled) {
      int info_len = 0;
      gl->GetShaderiv(shader_id, 0x8B84, &info_len); // GL_INFO_LOG_LENGTH
      if (info_len > 1) {
        char info_log[info_len + 1];
        info_log[info_len] = 0;
        gl->GetShaderInfoLog(shader_id, info_len, NULL, info_log);
        stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "[GpuLib] Shader compiler: %s\n", info_log);
        {
          int line = 1;
          stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "[GpuLib] %05d: ", line);
          for (char c = *shader_string; c != '\0'; c = *++shader_string) {
            stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "%c", c);
            if (c == '\n') {
              line += 1;
              stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "[GpuLib] %05d: ", line);
            }
          }
          stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "\n\n");
        }
      }
      gl->DeleteShader(shader_id);
      return 0;
    }
  }

  unsigned pro_id = gl->CreateProgram();
  gl->ProgramParameteri(pro_id, 0x8258, 1); // GL_PROGRAM_SEPARABLE

  gl->AttachShader(pro_id, shader_id);

  gl->LinkProgram(pro_id);

  {
    int is_linked = 0;
    gl->GetProgramiv(pro_id, 0x8B82, &is_linked); // GL_LINK_STATUS
    if (!is_linked) {
      int info_len = 0;
      gl->GetProgramiv(pro_id, 0x8B84, &info_len); // GL_INFO_LOG_LENGTH
      if (info_len > 1) {
        char info_log[info_len + 1];
        info_log[info_len] = 0;
        gl->GetProgramInfoLog(pro_id, info_len, NULL, info_log);
        stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "[GpuLib] Program linker: %s\n", info_log);
        {
          int line = 1;
          stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "[GpuLib] %05d: ", line);
          for (char c = *shader_string; c != '\0'; c = *++shader_string) {
            stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "%c", c);
            if (c == '\n') {
              line += 1;
              stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "[GpuLib] %05d: ", line);
            }
          }
          stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "\n\n");
        }
      }
      gl->DetachShader(pro_id, shader_id);
      gl->DeleteShader(shader_id);
      return 0;
    }
  }

  gl->DetachShader(pro_id, shader_id);
  gl->DeleteShader(shader_id);
  profE(__func__);
  return pro_id;
}

static inline unsigned GpuVert(char * shader_string) { return GpuPro(0x8B31, shader_string); } // GL_VERTEX_SHADER
static inline unsigned GpuFrag(char * shader_string) { return GpuPro(0x8B30, shader_string); } // GL_FRAGMENT_SHADER

static inline unsigned GpuPpo(unsigned vert_pro_id, unsigned frag_pro_id) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  unsigned ppo_id = 0;
  gl->CreateProgramPipelines(1, &ppo_id);
  if (vert_pro_id) gl->UseProgramStages(ppo_id, 1, vert_pro_id);
  if (frag_pro_id) gl->UseProgramStages(ppo_id, 2, frag_pro_id);
  profE(__func__);
  return ppo_id;
}

static inline unsigned GpuFbo(
    unsigned color_tex_id_0, int color_tex_layer_0,
    unsigned color_tex_id_1, int color_tex_layer_1,
    unsigned color_tex_id_2, int color_tex_layer_2,
    unsigned color_tex_id_3, int color_tex_layer_3,
    unsigned depth_tex_id_0, int depth_tex_layer_0)
{
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  unsigned fbo_id = 0;
  gl->CreateFramebuffers(1, &fbo_id);
  gl->NamedFramebufferTextureLayer(fbo_id, 0x8CE0 + 0, color_tex_id_0, 0, color_tex_layer_0); // GL_COLOR_ATTACHMENT0
  gl->NamedFramebufferTextureLayer(fbo_id, 0x8CE0 + 1, color_tex_id_1, 0, color_tex_layer_1);
  gl->NamedFramebufferTextureLayer(fbo_id, 0x8CE0 + 2, color_tex_id_2, 0, color_tex_layer_2);
  gl->NamedFramebufferTextureLayer(fbo_id, 0x8CE0 + 3, color_tex_id_3, 0, color_tex_layer_3);
  gl->NamedFramebufferTextureLayer(fbo_id, 0x8D00 + 0, depth_tex_id_0, 0, depth_tex_layer_0); // GL_DEPTH_ATTACHMENT
  int attachments[4] = {
    color_tex_id_0 ? 0x8CE0 + 0 : 0,
    color_tex_id_1 ? 0x8CE0 + 1 : 0,
    color_tex_id_2 ? 0x8CE0 + 2 : 0,
    color_tex_id_3 ? 0x8CE0 + 3 : 0
  };
  gl->NamedFramebufferDrawBuffers(fbo_id, 4, attachments);
  profE(__func__);
  return fbo_id;
}

static inline unsigned GpuXfb(
    unsigned buf_0_id, ptrdiff_t buf_0_bytes_first, ptrdiff_t buf_0_bytes_count,
    unsigned buf_1_id, ptrdiff_t buf_1_bytes_first, ptrdiff_t buf_1_bytes_count,
    unsigned buf_2_id, ptrdiff_t buf_2_bytes_first, ptrdiff_t buf_2_bytes_count,
    unsigned buf_3_id, ptrdiff_t buf_3_bytes_first, ptrdiff_t buf_3_bytes_count)
{
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  unsigned xfb_id = 0;
  gl->CreateTransformFeedbacks(1, &xfb_id);
  if (buf_0_id) gl->TransformFeedbackBufferRange(xfb_id, 0, buf_0_id, buf_0_bytes_first, buf_0_bytes_count);
  if (buf_1_id) gl->TransformFeedbackBufferRange(xfb_id, 1, buf_1_id, buf_1_bytes_first, buf_1_bytes_count);
  if (buf_2_id) gl->TransformFeedbackBufferRange(xfb_id, 2, buf_2_id, buf_2_bytes_first, buf_2_bytes_count);
  if (buf_3_id) gl->TransformFeedbackBufferRange(xfb_id, 3, buf_3_id, buf_3_bytes_first, buf_3_bytes_count);
  profE(__func__);
  return xfb_id;
}

static inline void * GpuFence() {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  void * fence = gl->FenceSync(0x9117, 0); // GL_SYNC_GPU_COMMANDS_COMPLETE
  profE(__func__);
  return fence;
}

static inline unsigned GpuQuery() {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  unsigned query_id = 0;
  gl->GenQueries(1, &query_id);
  profE(__func__);
  return query_id;
}

static inline void GpuUniformInt(unsigned program, int location, int count, int * value) {
  __auto_type gl = g_gpulib_libgl;
  gl->ProgramUniform1iv(program, location, count, value);
}

static inline void GpuUniformFloat4(unsigned program, int location, int count, float * value) {
  __auto_type gl = g_gpulib_libgl;
  gl->ProgramUniform4fv(program, location, count, value);
}

static inline int GpuFenceIsComplete(void * fence) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  int fence_status = 0;
  gl->GetSynciv(fence, 0x9114, 1, NULL, &fence_status); // GL_SYNC_STATUS
  profE(__func__);
  return fence_status == 0x9119 ? 1 : 0; // GL_SIGNALED
}

static inline void GpuQueryBeginTimeElapsed(unsigned query_id) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  gl->BeginQuery(0x88BF, query_id); // GL_TIME_ELAPSED
  profE(__func__);
}

static inline void GpuQueryEndTimeElapsed() {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  gl->EndQuery(0x88BF); // GL_TIME_ELAPSED
  profE(__func__);
}

static inline int GpuQueryIsResultAvailable(unsigned query_id) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  size_t query_is_result_available = 0;
  gl->GetQueryObjectui64v(query_id, 0x8867, &query_is_result_available); // GL_QUERY_RESULT_AVAILABLE
  profE(__func__);
  return query_is_result_available == 1 ? 1 : 0;
}

static inline size_t GpuQueryGetResult(unsigned query_id) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  size_t query_result = 0;
  gl->GetQueryObjectui64v(query_id, 0x8866, &query_result); // GL_QUERY_RESULT
  profE(__func__);
  return query_result;
}

static inline void GpuBindFbo(unsigned fbo_id) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  gl->BindFramebuffer(0x8D40, fbo_id); // GL_FRAMEBUFFER
  profE(__func__);
}

static inline void GpuBindXfb(unsigned xfb_id) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  gl->BindTransformFeedback(0x8E22, xfb_id); // GL_TRANSFORM_FEEDBACK
  profE(__func__);
}

static inline void GpuBindIndices(unsigned idb_id) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  gl->BindBuffer(0x8893, idb_id); // GL_ELEMENT_ARRAY_BUFFER
  profE(__func__);
}

static inline void GpuBindCommands(unsigned dib_id) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  gl->BindBuffer(0x8F3F, dib_id); // GL_DRAW_INDIRECT_BUFFER
  profE(__func__);
}

static inline void GpuBindTextures(int first, int count, unsigned * textures) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  gl->BindTextures(first, count, textures);
  profE(__func__);
}

static inline void GpuBindSamplers(int first, int count, unsigned * samplers) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  gl->BindSamplers(first, count, samplers);
  profE(__func__);
}

static inline void GpuBindPpo(unsigned ppo) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  gl->BindProgramPipeline(ppo);
  profE(__func__);
}

static inline void GpuDraw(enum gpu_draw_mode_e mode, unsigned binded_dib_cmd_first, unsigned binded_dib_cmd_count) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  gl->MultiDrawElementsIndirect(mode, 0x1405, (void *)(binded_dib_cmd_first * 5 * sizeof(unsigned)), binded_dib_cmd_count, 0); // GL_UNSIGNED_INT
  profE(__func__);
}

static inline void GpuDrawXfb(enum gpu_draw_mode_e mode, unsigned binded_dib_cmd_first, unsigned binded_dib_cmd_count) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  gl->Enable(0x8C89); // GL_RASTERIZER_DISCARD
  gl->BeginTransformFeedback(mode);
  gl->MultiDrawElementsIndirect(mode, 0x1405, (void *)(binded_dib_cmd_first * 5 * sizeof(unsigned)), binded_dib_cmd_count, 0); // GL_UNSIGNED_INT
  gl->EndTransformFeedback();
  gl->Disable(0x8C89);
  profE(__func__);
}

static inline void GpuDrawOnce(enum gpu_draw_mode_e mode, unsigned first, unsigned count, unsigned instance_count) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  gl->DrawArraysInstanced(mode, first, count, instance_count);
  profE(__func__);
}

static inline void GpuDrawOnceXfb(enum gpu_draw_mode_e mode, unsigned first, unsigned count, unsigned instance_count) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  gl->Enable(0x8C89); // GL_RASTERIZER_DISCARD
  gl->BeginTransformFeedback(mode);
  gl->DrawArraysInstanced(mode, first, count, instance_count);
  gl->EndTransformFeedback();
  gl->Disable(0x8C89);
  profE(__func__);
}

static inline void GpuBlit(
    unsigned source_fbo_id, int source_color_id, int source_x, int source_y, int source_width, int source_height,
    unsigned target_fbo_id, int target_color_id, int target_x, int target_y, int target_width, int target_height)
{
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  gl->NamedFramebufferReadBuffer(source_fbo_id, 0x8CE0 + source_color_id); // GL_COLOR_ATTACHMENT0
  gl->NamedFramebufferDrawBuffer(target_fbo_id, 0x8CE0 + target_color_id);
  gl->BlitNamedFramebuffer(
      source_fbo_id, target_fbo_id,
      source_x, source_y, source_width, source_height,
      target_x, target_y, target_width, target_height, 0x00004000, 0x2600); // GL_COLOR_BUFFER_BIT, GL_NEAREST
  profE(__func__);
}

static inline void GpuBlitToScreen(
    unsigned source_fbo_id, int source_color_id,
    int source_x, int source_y, int source_width, int source_height,
    int screen_x, int screen_y, int screen_width, int screen_height)
{
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  gl->NamedFramebufferReadBuffer(source_fbo_id, 0x8CE0 + source_color_id); // GL_COLOR_ATTACHMENT0
  gl->NamedFramebufferDrawBuffer(0, 0x0405); // GL_BACK
  gl->BlitNamedFramebuffer(
      source_fbo_id, 0,
      source_x, source_y, source_width, source_height,
      screen_x, screen_y, screen_width, screen_height, 0x00004000, 0x2600); // GL_COLOR_BUFFER_BIT, GL_NEAREST
  profE(__func__);
}

static inline void GpuClear() {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  gl->Clear(0x4100); // GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT
  profE(__func__);
}

static inline void GpuEnable(unsigned flags) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  gl->Enable(flags);
  profE(__func__);
}

static inline void GpuDisable(unsigned flags) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  gl->Disable(flags);
  profE(__func__);
}

static inline void GpuViewport(int x, int y, int width, int height) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  gl->Viewport(x, y, width, height);
  profE(__func__);
}

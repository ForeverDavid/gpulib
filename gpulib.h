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

#include <X11/extensions/Xrender.h>
#include <X11/extensions/XInput2.h>
#include <X11/XKBlib.h>
#include "stdlib/stdlib.h"

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

enum gpu_mode_e {
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
  gpu_d_f32_e              = 0x8CAC, // GL_DEPTH_COMPONENT32F
  gpu_rgb_b8_e             = 0x8051, // GL_RGB8
  gpu_rgba_b8_e            = 0x8058, // GL_RGBA8
  gpu_srgb_b8_e            = 0x8C41, // GL_SRGB8
  gpu_srgba_b8_e           = 0x8C43, // GL_SRGB8_ALPHA8
  gpu_rgba_f32_e           = 0x8814, // GL_RGBA32F
  gpu_rgb_s3tc_dxt1_b8_e   = 0x83F0, // GL_COMPRESSED_RGB_S3TC_DXT1_EXT
  gpu_rgba_s3tc_dxt1_b8_e  = 0x83F1, // GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
  gpu_rgba_s3tc_dxt3_b8_e  = 0x83F2, // GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
  gpu_rgba_s3tc_dxt5_b8_e  = 0x83F3, // GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
  gpu_srgb_s3tc_dxt1_b8_e  = 0x8C4C, // GL_COMPRESSED_SRGB_S3TC_DXT1_EXT
  gpu_srgba_s3tc_dxt1_b8_e = 0x8C4D, // GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT
  gpu_srgba_s3tc_dxt3_b8_e = 0x8C4E, // GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT
  gpu_srgba_s3tc_dxt5_b8_e = 0x8C4F, // GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT
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

struct XVisualInfo {
  void * visual;
  VisualID visualid;
  int screen;
  int depth;
  int class;
  unsigned long red_mask;
  unsigned long green_mask;
  unsigned long blue_mask;
  int colormap_size;
  int bits_per_rgb;
};

struct MWMHints {
 long flags;
 long functions;
 long decorations;
 long input_mode;
 long status;
};

#define MWM_HINTS_FUNCTIONS     (1L << 0)
#define MWM_HINTS_DECORATIONS   (1L << 1)
#define MWM_HINTS_INPUT_MODE    (1L << 2)
#define MWM_HINTS_STATUS        (1L << 3)

#define MWM_FUNC_ALL            (1L << 0)
#define MWM_FUNC_RESIZE         (1L << 1)
#define MWM_FUNC_MOVE           (1L << 2)
#define MWM_FUNC_MINIMIZE       (1L << 3)
#define MWM_FUNC_MAXIMIZE       (1L << 4)
#define MWM_FUNC_CLOSE          (1L << 5)

#define MWM_DECOR_ALL           (1L << 0)
#define MWM_DECOR_BORDER        (1L << 1)
#define MWM_DECOR_RESIZEH       (1L << 2)
#define MWM_DECOR_TITLE         (1L << 3)
#define MWM_DECOR_MENU          (1L << 4)
#define MWM_DECOR_MINIMIZE      (1L << 5)
#define MWM_DECOR_MAXIMIZE      (1L << 6)

#define MWM_INPUT_MODELESS 0
#define MWM_INPUT_PRIMARY_APPLICATION_MODAL 1
#define MWM_INPUT_SYSTEM_MODAL 2
#define MWM_INPUT_FULL_APPLICATION_MODAL 3
#define MWM_INPUT_APPLICATION_MODAL MWM_INPUT_PRIMARY_APPLICATION_MODAL

#define MWM_TEAROFF_WINDOW      (1L<<0)

#define GPULIB_VERT_HEADER                                     \
  "#version 330"                                          "\n" \
  "#extension GL_ARB_gpu_shader5                : enable" "\n" \
  "#extension GL_ARB_shader_precision           : enable" "\n" \
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
  "#extension GL_ARB_texture_cube_map_array     : enable" "\n" \
  "#extension GL_ARB_separate_shader_objects    : enable" "\n" \
  "#extension GL_ARB_shading_language_420pack   : enable" "\n" \
  "#extension GL_ARB_shading_language_packing   : enable" "\n" \
  "#extension GL_ARB_explicit_uniform_location  : enable" "\n" \
  "#extension GL_ARB_fragment_coord_conventions : enable" "\n" \
  "layout(origin_upper_left) in vec4 gl_FragCoord;"       "\n" \
  ""                                                      "\n"

struct g_gpulib_libc_t {
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

struct g_gpulib_libc_t * g_gpulib_libc = &g_gpulib_libc_data;

struct g_gpulib_libglx_t {
  void ** (*ChooseFBConfig)(Display *, int, int *, int *);
  int (*GetFBConfigAttrib)(Display *, void *, int, int *);
  void * (*GetProcAddressARB)(char *);
  struct XVisualInfo * (*GetVisualFromFBConfig)(Display *, void *);
  int (*MakeContextCurrent)(Display *, XID, XID, void *);
  void (*SwapBuffers)(Display *, XID);
} g_gpulib_libglx_data = {0};

struct g_gpulib_libglx_t * g_gpulib_libglx = &g_gpulib_libglx_data;

struct g_gpulib_libgl_t {
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
  void (*CompressedTextureSubImage3D)(unsigned, int, int, int, int, int, int, int, unsigned, unsigned, void *);
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
  void (*GetCompressedTextureSubImage)(unsigned, int, int, int, int, int, int, int, int, void *);
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
  void (*ProgramUniform1fv)(unsigned, int, int, float *);
  void (*ProgramUniform1iv)(unsigned, int, int, int *);
  void (*ProgramUniform1uiv)(unsigned, int, int, unsigned *);
  void (*ProgramUniform2fv)(unsigned, int, int, float *);
  void (*ProgramUniform3fv)(unsigned, int, int, float *);
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

struct g_gpulib_libgl_t * g_gpulib_libgl = &g_gpulib_libgl_data;

static inline void GpuSysGetLibcProcedureAddresses() {
  __auto_type libc = g_gpulib_libc;
  libc->access = dlsym(NULL, "access");
  libc->calloc = dlsym(NULL, "calloc");
  libc->fgetc = dlsym(NULL, "fgetc");
  libc->free = dlsym(NULL, "free");
  libc->getpid = dlsym(NULL, "getpid");
  libc->pclose = dlsym(NULL, "pclose");
  libc->popen = dlsym(NULL, "popen");
  libc->readlink = dlsym(NULL, "readlink");
  libc->realloc = dlsym(NULL, "realloc");
  libc->setlocale = dlsym(NULL, "setlocale");
  libc->strcat = dlsym(NULL, "strcat");
  libc->strcmp = dlsym(NULL, "strcmp");
  libc->strlen = dlsym(NULL, "strlen");
  libc->strndup = dlsym(NULL, "strndup");
  libc->strrchr = dlsym(NULL, "strrchr");
  libc->strtol = dlsym(NULL, "strtol");
  libc->usleep = dlsym(NULL, "usleep");
}

static inline void GpuSysGetGLXProcedureAddresses() {
  __auto_type glx = g_gpulib_libglx;
  void * libgl = dlopen("libGL.so", 1);
  glx->ChooseFBConfig = dlsym(libgl, "glXChooseFBConfig");
  glx->GetFBConfigAttrib = dlsym(libgl, "glXGetFBConfigAttrib");
  glx->GetProcAddressARB = dlsym(libgl, "glXGetProcAddressARB");
  glx->GetVisualFromFBConfig = dlsym(libgl, "glXGetVisualFromFBConfig");
  glx->MakeContextCurrent = dlsym(libgl, "glXMakeContextCurrent");
  glx->SwapBuffers = dlsym(libgl, "glXSwapBuffers");
}

static inline void GpuSysGetGLProcedureAddresses() {
  __auto_type gl = g_gpulib_libgl;
  __auto_type glx = g_gpulib_libglx;
  gl->AttachShader = glx->GetProcAddressARB("glAttachShader");
  gl->BeginQuery = glx->GetProcAddressARB("glBeginQuery");
  gl->BeginTransformFeedback = glx->GetProcAddressARB("glBeginTransformFeedback");
  gl->BindBuffer = glx->GetProcAddressARB("glBindBuffer");
  gl->BindFramebuffer = glx->GetProcAddressARB("glBindFramebuffer");
  gl->BindProgramPipeline = glx->GetProcAddressARB("glBindProgramPipeline");
  gl->BindSamplers = glx->GetProcAddressARB("glBindSamplers");
  gl->BindTextures = glx->GetProcAddressARB("glBindTextures");
  gl->BindTransformFeedback = glx->GetProcAddressARB("glBindTransformFeedback");
  gl->BindVertexArray = glx->GetProcAddressARB("glBindVertexArray");
  gl->BlendFunc = glx->GetProcAddressARB("glBlendFunc");
  gl->BlitNamedFramebuffer = glx->GetProcAddressARB("glBlitNamedFramebuffer");
  gl->BufferStorage = glx->GetProcAddressARB("glBufferStorage");
  gl->Clear = glx->GetProcAddressARB("glClear");
  gl->ClearDepth = glx->GetProcAddressARB("glClearDepth");
  gl->ClearTexSubImage = glx->GetProcAddressARB("glClearTexSubImage");
  gl->ClipControl = glx->GetProcAddressARB("glClipControl");
  gl->CompileShader = glx->GetProcAddressARB("glCompileShader");
  gl->CompressedTextureSubImage3D = glx->GetProcAddressARB("glCompressedTextureSubImage3D");
  gl->CreateBuffers = glx->GetProcAddressARB("glCreateBuffers");
  gl->CreateFramebuffers = glx->GetProcAddressARB("glCreateFramebuffers");
  gl->CreateProgram = glx->GetProcAddressARB("glCreateProgram");
  gl->CreateProgramPipelines = glx->GetProcAddressARB("glCreateProgramPipelines");
  gl->CreateSamplers = glx->GetProcAddressARB("glCreateSamplers");
  gl->CreateShader = glx->GetProcAddressARB("glCreateShader");
  gl->CreateTextures = glx->GetProcAddressARB("glCreateTextures");
  gl->CreateTransformFeedbacks = glx->GetProcAddressARB("glCreateTransformFeedbacks");
  gl->CreateVertexArrays = glx->GetProcAddressARB("glCreateVertexArrays");
  gl->DebugMessageCallback = glx->GetProcAddressARB("glDebugMessageCallback");
  gl->DeleteBuffers = glx->GetProcAddressARB("glDeleteBuffers");
  gl->DeleteFramebuffers = glx->GetProcAddressARB("glDeleteFramebuffers");
  gl->DeleteProgram = glx->GetProcAddressARB("glDeleteProgram");
  gl->DeleteProgramPipelines = glx->GetProcAddressARB("glDeleteProgramPipelines");
  gl->DeleteQueries = glx->GetProcAddressARB("glDeleteQueries");
  gl->DeleteSamplers = glx->GetProcAddressARB("glDeleteSamplers");
  gl->DeleteShader = glx->GetProcAddressARB("glDeleteShader");
  gl->DeleteSync = glx->GetProcAddressARB("glDeleteSync");
  gl->DeleteTextures = glx->GetProcAddressARB("glDeleteTextures");
  gl->DeleteTransformFeedbacks = glx->GetProcAddressARB("glDeleteTransformFeedbacks");
  gl->DepthFunc = glx->GetProcAddressARB("glDepthFunc");
  gl->DepthRange = glx->GetProcAddressARB("glDepthRange");
  gl->DetachShader = glx->GetProcAddressARB("glDetachShader");
  gl->Disable = glx->GetProcAddressARB("glDisable");
  gl->DrawArraysInstanced = glx->GetProcAddressARB("glDrawArraysInstanced");
  gl->Enable = glx->GetProcAddressARB("glEnable");
  gl->EndQuery = glx->GetProcAddressARB("glEndQuery");
  gl->EndTransformFeedback = glx->GetProcAddressARB("glEndTransformFeedback");
  gl->FenceSync = glx->GetProcAddressARB("glFenceSync");
  gl->FrontFace = glx->GetProcAddressARB("glFrontFace");
  gl->GenBuffers = glx->GetProcAddressARB("glGenBuffers");
  gl->GenerateTextureMipmap = glx->GetProcAddressARB("glGenerateTextureMipmap");
  gl->GenQueries = glx->GetProcAddressARB("glGenQueries");
  gl->GenTextures = glx->GetProcAddressARB("glGenTextures");
  gl->GetCompressedTextureSubImage = glx->GetProcAddressARB("glGetCompressedTextureSubImage");
  gl->GetIntegerv = glx->GetProcAddressARB("glGetIntegerv");
  gl->GetProgramInfoLog = glx->GetProcAddressARB("glGetProgramInfoLog");
  gl->GetProgramiv = glx->GetProcAddressARB("glGetProgramiv");
  gl->GetQueryObjectui64v = glx->GetProcAddressARB("glGetQueryObjectui64v");
  gl->GetShaderInfoLog = glx->GetProcAddressARB("glGetShaderInfoLog");
  gl->GetShaderiv = glx->GetProcAddressARB("glGetShaderiv");
  gl->GetStringi = glx->GetProcAddressARB("glGetStringi");
  gl->GetSynciv = glx->GetProcAddressARB("glGetSynciv");
  gl->GetTextureLevelParameteriv = glx->GetProcAddressARB("glGetTextureLevelParameteriv");
  gl->GetTextureSubImage = glx->GetProcAddressARB("glGetTextureSubImage");
  gl->LinkProgram = glx->GetProcAddressARB("glLinkProgram");
  gl->MapBufferRange = glx->GetProcAddressARB("glMapBufferRange");
  gl->MapNamedBufferRange = glx->GetProcAddressARB("glMapNamedBufferRange");
  gl->MultiDrawElementsIndirect = glx->GetProcAddressARB("glMultiDrawElementsIndirect");
  gl->NamedBufferStorage = glx->GetProcAddressARB("glNamedBufferStorage");
  gl->NamedFramebufferDrawBuffer = glx->GetProcAddressARB("glNamedFramebufferDrawBuffer");
  gl->NamedFramebufferDrawBuffers = glx->GetProcAddressARB("glNamedFramebufferDrawBuffers");
  gl->NamedFramebufferReadBuffer = glx->GetProcAddressARB("glNamedFramebufferReadBuffer");
  gl->NamedFramebufferTextureLayer = glx->GetProcAddressARB("glNamedFramebufferTextureLayer");
  gl->ProgramParameteri = glx->GetProcAddressARB("glProgramParameteri");
  gl->ProgramUniform1fv = glx->GetProcAddressARB("glProgramUniform1fv");
  gl->ProgramUniform1iv = glx->GetProcAddressARB("glProgramUniform1iv");
  gl->ProgramUniform1uiv = glx->GetProcAddressARB("glProgramUniform1uiv");
  gl->ProgramUniform2fv = glx->GetProcAddressARB("glProgramUniform2fv");
  gl->ProgramUniform3fv = glx->GetProcAddressARB("glProgramUniform3fv");
  gl->ProgramUniform4fv = glx->GetProcAddressARB("glProgramUniform4fv");
  gl->SamplerParameteri = glx->GetProcAddressARB("glSamplerParameteri");
  gl->Scissor = glx->GetProcAddressARB("glScissor");
  gl->ShaderSource = glx->GetProcAddressARB("glShaderSource");
  gl->TextureBufferRange = glx->GetProcAddressARB("glTextureBufferRange");
  gl->TextureStorage3D = glx->GetProcAddressARB("glTextureStorage3D");
  gl->TextureStorage3DMultisample = glx->GetProcAddressARB("glTextureStorage3DMultisample");
  gl->TextureSubImage3D = glx->GetProcAddressARB("glTextureSubImage3D");
  gl->TextureView = glx->GetProcAddressARB("glTextureView");
  gl->TransformFeedbackBufferRange = glx->GetProcAddressARB("glTransformFeedbackBufferRange");
  gl->TransformFeedbackVaryings = glx->GetProcAddressARB("glTransformFeedbackVaryings");
  gl->UseProgramStages = glx->GetProcAddressARB("glUseProgramStages");
  gl->Viewport = glx->GetProcAddressARB("glViewport");
}

static inline long GpuSysShell(char * cmd, char * out) {
  __auto_type libc = g_gpulib_libc;
  int * ret = libc->popen(cmd, "r");
  long i = 0;
  for (int c = libc->fgetc(ret); c != -1; i += 1) {
    if (out) out[i] = (char)c;
    c = libc->fgetc(ret);
  }
  if (out) out[i] = 0;
  libc->pclose(ret);
  return i + 1;
}

static inline char * GpuSysReadSymLink(char * path) {
  __auto_type libc = g_gpulib_libc;
  char * retval = NULL;
  ssize_t len = 64;
  ssize_t rc = -1;
  for (;;) {
    char * ptr = libc->realloc(retval, (size_t)len);
    retval = ptr;
    rc = libc->readlink(path, retval, len);
    if (rc == -1) {
      break;
    } else if (rc < len) {
      retval[rc] = '\0';
      return retval;
    }
    len *= 2;
  }
  libc->free(retval);
  return NULL;
}

static inline char * GpuSysGetBasePath() {
  __auto_type libc = g_gpulib_libc;
  char * retval = NULL;
  if (retval == NULL && (libc->access("/proc", 0) == 0)) {
    retval = GpuSysReadSymLink("/proc/self/exe");
    if (retval == NULL) {
      char path[64] = {0};
      int rc = stdlib_snprintf(path, sizeof(path), "/proc/%llu/exe", (unsigned long long)libc->getpid());
      if ((rc > 0) && (rc < sizeof(path)))
        retval = GpuSysReadSymLink(path);
    }
  }
  if (retval != NULL) {
    char * ptr = libc->strrchr(retval, '/');
    if (ptr != NULL) {
      *(ptr + 1) = '\0';
    } else {
      libc->free(retval);
      retval = NULL;
    }
  }
  if (retval != NULL) {
    char * ptr = libc->realloc(retval, libc->strlen(retval) + 1);
    if (ptr != NULL)
      retval = ptr;
  }
  return retval;
}

static inline void GpuSysSetRelativeMouseMode(Display * dpy, Window win, int enabled) {
  __auto_type libc = g_gpulib_libc;
  if (enabled) {
    XColor black = {0};
    char nil[8]  = {0};
    Pixmap bitmap = XCreateBitmapFromData(dpy, win, nil, 8, 8);
    Cursor cursor = XCreatePixmapCursor(dpy, bitmap, bitmap, &black, &black, 0, 0);
    XDefineCursor(dpy, win, cursor);
    XFreeCursor(dpy, cursor);
    XFreePixmap(dpy, bitmap);
    for (int attempts = 0; attempts < 100; attempts += 1) {
      int result = XGrabPointer(
        dpy, win, True, ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask,
        GrabModeAsync, GrabModeAsync, win, None, CurrentTime);
      if (result == GrabSuccess)
        break;
      libc->usleep(50 * 1000);
    }
  } else {
    XUndefineCursor(dpy, win);
    XUngrabPointer(dpy, CurrentTime);
  }
}

static inline int GpuSysIsExtensionSupported(char * extension) {
  __auto_type gl = g_gpulib_libgl;
  __auto_type libc = g_gpulib_libc;
  int num_extensions = 0;
  gl->GetIntegerv(0x821D, &num_extensions); // GL_NUM_EXTENSIONS
  for (int i = 0; i < num_extensions; i += 1) {
    char * ext = gl->GetStringi(0x1F03, i); // GL_EXTENSIONS
    if (libc->strcmp(ext, extension) == 0)
      return 1;
  }
  return 0;
}

static inline void GpuSysCheckExtensions(int extension_count, char ** extensions) {
  profB(__func__);
  for (int i = 0; i < extension_count; i += 1) {
    if (GpuSysIsExtensionSupported(extensions[i]) == 0) {
      char cmd[GPULIB_MAX_PRINT_BYTES];
      stdlib_snprintf(cmd, GPULIB_MAX_PRINT_BYTES, "notify-send \"[GpuLib] Error: %s is not supported.\"", extensions[i]);
      GpuSysShell(cmd, NULL);
    }
  }
  profE(__func__);
}

static inline void GpuSysX11Window(char * title, int title_bytes, int x, int y, int w, int h, int msaa_sample_count, Display ** out_display, Window * out_window) {
  __auto_type glx = g_gpulib_libglx;
  __auto_type libc = g_gpulib_libc;
  
  profB("Load libGL.so");
  GpuSysGetGLXProcedureAddresses();
  profE("Load libGL.so");

  profB("Set locale");
  libc->setlocale(6, ""); // LC_ALL
  if (XSupportsLocale())
    XSetLocaleModifiers("@im=none");
  profE("Set locale");

  profB("XOpenDisplay");
  Display * dpy = XOpenDisplay(NULL);
  profE("XOpenDisplay");
  stdlib_assert(dpy != NULL);

  void * fbconfig = NULL;
  struct XVisualInfo * visual = NULL;
  {
    int glx_attribs[25] = {0};
    int glx_attribs_with_msaa[25] = {
      0x8010, 0x00000001, // GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT
      0x8011, 0x00000001, // GLX_RENDER_TYPE, GLX_RGBA_BIT
      0x8012, 1, // GLX_X_RENDERABLE
      5,      1, // GLX_DOUBLEBUFFER
      8,      8, // GLX_RED_SIZE
      9,      8, // GLX_GREEN_SIZE
      10,     8, // GLX_BLUE_SIZE
      11,     8, // GLX_ALPHA_SIZE
      12,     24, // GLX_DEPTH_SIZE
      13,     8, // GLX_STENCIL_SIZE
      100000, 1, // GLX_SAMPLE_BUFFERS
      100001, msaa_sample_count, // GLX_SAMPLES
      None
    };
    int glx_attribs_without_msaa[25] = {
      0x8010, 0x00000001, // GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT
      0x8011, 0x00000001, // GLX_RENDER_TYPE, GLX_RGBA_BIT
      0x8012, 1, // GLX_X_RENDERABLE
      5,      1, // GLX_DOUBLEBUFFER
      8,      8, // GLX_RED_SIZE
      9,      8, // GLX_GREEN_SIZE
      10,     8, // GLX_BLUE_SIZE
      11,     8, // GLX_ALPHA_SIZE
      12,     24, // GLX_DEPTH_SIZE
      13,     8, // GLX_STENCIL_SIZE
      None
    };
    memcpy(glx_attribs, msaa_sample_count > 0 ? glx_attribs_with_msaa : glx_attribs_without_msaa, 25 * sizeof(int));
    int fbconfigs_count = 0;
    profB("glx->ChooseFBConfig");
    void ** fbconfigs = glx->ChooseFBConfig(dpy, DefaultScreen(dpy), glx_attribs, &fbconfigs_count);
    profE("glx->ChooseFBConfig");
    stdlib_assert(fbconfigs_count != 0);
    stdlib_assert(fbconfigs != NULL);
    profB("fbconfig search");
    for (int i = fbconfigs_count - 1; i >= 0; i -= 1) {
#if 0
      {
        int red_size = 0, green_size = 0, blue_size = 0, alpha_size = 0, depth_size = 0, stencil_size = 0, doublebuffer = 0, sample_buffers = 0, samples = 0;
        glx->GetFBConfigAttrib(dpy, fbconfigs[i], GLX_RED_SIZE,       &red_size);
        glx->GetFBConfigAttrib(dpy, fbconfigs[i], GLX_GREEN_SIZE,     &green_size);
        glx->GetFBConfigAttrib(dpy, fbconfigs[i], GLX_BLUE_SIZE,      &blue_size);
        glx->GetFBConfigAttrib(dpy, fbconfigs[i], GLX_ALPHA_SIZE,     &alpha_size);
        glx->GetFBConfigAttrib(dpy, fbconfigs[i], GLX_DEPTH_SIZE,     &depth_size);
        glx->GetFBConfigAttrib(dpy, fbconfigs[i], GLX_STENCIL_SIZE,   &stencil_size);
        glx->GetFBConfigAttrib(dpy, fbconfigs[i], GLX_DOUBLEBUFFER,   &doublebuffer);
        glx->GetFBConfigAttrib(dpy, fbconfigs[i], GLX_SAMPLE_BUFFERS, &sample_buffers);
        glx->GetFBConfigAttrib(dpy, fbconfigs[i], GLX_SAMPLES,        &samples);
        stdlib_nprintf(GPULIB_MAX_PRINT_BYTES,
          "fbconfigs[%d]: %p, "
          "GLX_RED_SIZE: %d, "
          "GLX_GREEN_SIZE: %d, "
          "GLX_BLUE_SIZE: %d, "
          "GLX_ALPHA_SIZE: %d, "
          "GLX_DEPTH_SIZE: %d, "
          "GLX_STENCIL_SIZE: %d, "
          "GLX_DOUBLEBUFFER: %d, "
          "GLX_SAMPLE_BUFFERS: %d, "
          "GLX_SAMPLES: %d\n",
          i, fbconfigs[i],
          red_size,
          green_size,
          blue_size,
          alpha_size,
          depth_size,
          stencil_size,
          doublebuffer,
          sample_buffers,
          samples);
      }
#endif
      XFree(visual);
      visual = glx->GetVisualFromFBConfig(dpy, fbconfigs[i]);
      if (visual == NULL)
        continue;
      XRenderPictFormat * format = XRenderFindVisualFormat(dpy, visual->visual);
      if (format == NULL)
        continue;
      fbconfig = fbconfigs[i];
#if 0
      if (format->direct.alphaMask > 0)
        break;
#endif
    }
    XFree(fbconfigs);
    profE("fbconfig search");
  }
  stdlib_assert(fbconfig != NULL);

#if 0
  {
    int red_size = 0, green_size = 0, blue_size = 0, alpha_size = 0, depth_size = 0, stencil_size = 0, doublebuffer = 0, sample_buffers = 0, samples = 0;
    glx->GetFBConfigAttrib(dpy, fbconfig, GLX_RED_SIZE,       &red_size);
    glx->GetFBConfigAttrib(dpy, fbconfig, GLX_GREEN_SIZE,     &green_size);
    glx->GetFBConfigAttrib(dpy, fbconfig, GLX_BLUE_SIZE,      &blue_size);
    glx->GetFBConfigAttrib(dpy, fbconfig, GLX_ALPHA_SIZE,     &alpha_size);
    glx->GetFBConfigAttrib(dpy, fbconfig, GLX_DEPTH_SIZE,     &depth_size);
    glx->GetFBConfigAttrib(dpy, fbconfig, GLX_STENCIL_SIZE,   &stencil_size);
    glx->GetFBConfigAttrib(dpy, fbconfig, GLX_DOUBLEBUFFER,   &doublebuffer);
    glx->GetFBConfigAttrib(dpy, fbconfig, GLX_SAMPLE_BUFFERS, &sample_buffers);
    glx->GetFBConfigAttrib(dpy, fbconfig, GLX_SAMPLES,        &samples);
    stdlib_nprintf(GPULIB_MAX_PRINT_BYTES,
      "fbconfig: %p, "
      "GLX_RED_SIZE: %d, "
      "GLX_GREEN_SIZE: %d, "
      "GLX_BLUE_SIZE: %d, "
      "GLX_ALPHA_SIZE: %d, "
      "GLX_DEPTH_SIZE: %d, "
      "GLX_STENCIL_SIZE: %d, "
      "GLX_DOUBLEBUFFER: %d, "
      "GLX_SAMPLE_BUFFERS: %d, "
      "GLX_SAMPLES: %d\n",
      fbconfig,
      red_size,
      green_size,
      blue_size,
      alpha_size,
      depth_size,
      stencil_size,
      doublebuffer,
      sample_buffers,
      samples);
  }
#endif

  Window win = 0;
  {
    XSetWindowAttributes win_attrs = {0};
    profB("XCreateColormap");
    Colormap colormap = XCreateColormap(dpy, DefaultRootWindow(dpy), visual->visual, AllocNone);
    profE("XCreateColormap");
    win_attrs.colormap          = colormap;
    win_attrs.background_pixmap = None;
    win_attrs.border_pixmap     = None;
    win_attrs.border_pixel      = 0;
    win_attrs.event_mask        =
        ExposureMask
      | StructureNotifyMask
      | KeyPressMask
      | KeyReleaseMask
      | ButtonPressMask
      | ButtonReleaseMask
      | ButtonMotionMask
      | Button1MotionMask
      | Button2MotionMask
      | Button3MotionMask
      | Button4MotionMask
      | Button5MotionMask
      | PointerMotionMask;
    profB("XCreateWindow");
    win = XCreateWindow(
      dpy,
      DefaultRootWindow(dpy),
      x, y, w, h,
      0,
      visual->depth,
      InputOutput,
      visual->visual,
      CWBorderPixel | CWColormap | CWEventMask,
      &win_attrs);
    profE("XCreateWindow");
    XFree(visual);
    visual = NULL;
    stdlib_assert(win != 0);
  }

  {
    XTextProperty win_title = {0};
    win_title.value    = (unsigned char *)title;
    win_title.encoding = XInternAtom(dpy, "UTF8_STRING", 1);
    win_title.format   = 8;
    win_title.nitems   = title_bytes;
    XSizeHints hints = {0};
    hints.x      = x;
    hints.y      = y;
    hints.width  = w;
    hints.height = h;
    hints.flags  = USPosition | USSize;
    XWMHints startup_state = {0};
    startup_state.initial_state = NormalState;
    startup_state.flags         = StateHint;
    profB("XSetWMProperties");
    XSetWMProperties(dpy, win, &win_title, &win_title, NULL, 0, &hints, &startup_state, NULL);
    profE("XSetWMProperties");
  }

  {
    profB("XInternAtom _MOTIF_WM_HINTS");
    Atom MOTIF_WM_HINTS = XInternAtom(dpy, "_MOTIF_WM_HINTS", 0);
    profE("XInternAtom _MOTIF_WM_HINTS");
    struct MWMHints hints = {0};
    hints.flags       = MWM_HINTS_FUNCTIONS | MWM_HINTS_DECORATIONS;
    hints.functions   = MWM_FUNC_ALL;
    hints.decorations = MWM_DECOR_ALL;
    profB("XChangeProperty");
    XChangeProperty(
      dpy, win,
      MOTIF_WM_HINTS,
      MOTIF_WM_HINTS, 32,
      PropModeReplace,
      (unsigned char *)&hints,
      sizeof(struct MWMHints) / sizeof(long)
    );
    profE("XChangeProperty");
  }

  void * glx_ctx = NULL;
  {
    void * (*glXCreateContextAttribsARB)(Display *, void *, void *, int, int *) = glx->GetProcAddressARB("glXCreateContextAttribsARB");
    stdlib_assert(glXCreateContextAttribsARB != NULL);
    int attribs[] = {
      0x2091, 3, // GLX_CONTEXT_MAJOR_VERSION_ARB
      0x2092, 3, // GLX_CONTEXT_MINOR_VERSION_ARB
      0x9126, 0x00000001, // GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB
      None
    };
    profB("glXCreateContextAttribsARB");
    glx_ctx = glXCreateContextAttribsARB(dpy, fbconfig, 0, 1, attribs);
    profE("glXCreateContextAttribsARB");
    stdlib_assert(glx_ctx != NULL);
    profB("glx->MakeContextCurrent");
    int is_glx_context_current = glx->MakeContextCurrent(dpy, win, win, glx_ctx);
    profE("glx->MakeContextCurrent");
    stdlib_assert(is_glx_context_current != 0);
  }

  {
    profB("XInternAtom WM_DELETE_WINDOW");
    Atom delete_win_atom = XInternAtom(dpy, "WM_DELETE_WINDOW", 0);
    profE("XInternAtom WM_DELETE_WINDOW");
    stdlib_assert(delete_win_atom != None);
    profB("XSetWMProtocols");
    XSetWMProtocols(dpy, win, &delete_win_atom, 1);
    profE("XSetWMProtocols");
  }

  {
    XIEventMask eventmask = {0};
    unsigned char mask[3] = {0};
    eventmask.deviceid = XIAllMasterDevices;
    eventmask.mask_len = sizeof(mask);
    eventmask.mask = mask;
    XISetMask(mask, XI_RawMotion);
    XISetMask(mask, XI_RawButtonPress);
    XISetMask(mask, XI_RawButtonRelease);
    profB("XISelectEvents");
    XISelectEvents(dpy, DefaultRootWindow(dpy), &eventmask, 1);
    profE("XISelectEvents");
  }

  profB("XMapWindow");
  XMapWindow(dpy, win);
  profE("XMapWindow");

  out_display[0] = dpy;
  out_window[0]  = win;
}

static inline void GpuWindow(
    char * window_title, int window_title_bytes, int window_width, int window_height, int msaa_samples, char * out_scancodes, Display ** out_dpy, Window * out_win)
{
  __auto_type gl = g_gpulib_libgl;

  GpuSysGetLibcProcedureAddresses();

  profB(__func__);
  Display * dpy = NULL;
  Window win = 0;
  GpuSysX11Window(window_title, window_title_bytes, 0, 0, window_width, window_height, msaa_samples, &dpy, &win);

  profB("GpuSysGetGLProcedureAddresses");
  GpuSysGetGLProcedureAddresses();
  profE("GpuSysGetGLProcedureAddresses");

  {
    char * extensions[] = {
      "GL_KHR_debug",
      "GL_ARB_multi_bind",
      "GL_ARB_gpu_shader5",
      "GL_ARB_clip_control",
      "GL_ARB_texture_view",
      "GL_EXT_texture_sRGB",
      "GL_ARB_clear_texture",
      "GL_ARB_buffer_storage",
      "GL_ARB_texture_storage",
      "GL_ARB_shader_precision",
      "GL_ARB_get_program_binary",
      "GL_ARB_transform_feedback2",
      "GL_ARB_direct_state_access",
      "GL_ARB_multi_draw_indirect",
      "GL_ARB_texture_buffer_range",
      "GL_EXT_texture_mirror_clamp",
      "GL_ARB_get_texture_sub_image",
      "GL_ARB_texture_cube_map_array",
      "GL_ARB_separate_shader_objects",
      "GL_ARB_shading_language_420pack",
      "GL_ARB_shading_language_packing",
      "GL_EXT_texture_compression_s3tc",
      "GL_EXT_texture_filter_anisotropic",
      "GL_ARB_fragment_coord_conventions",
      "GL_ARB_texture_buffer_object_rgb32",
      "GL_ARB_texture_storage_multisample"
    };
    GpuSysCheckExtensions(sizeof(extensions) / sizeof(extensions[0]), extensions);
  }

  profB("OpenGL state setup");
  {
    gl->Viewport(0, 0, window_width, window_height);
#ifndef RELEASE
    gl->Enable(0x92E0); // GL_DEBUG_OUTPUT
    gl->Enable(0x8242); // GL_DEBUG_OUTPUT_SYNCHRONOUS
#endif
    gl->Enable(0x884F); // GL_TEXTURE_CUBE_MAP_SEAMLESS
    gl->Enable(0x8DB9); // GL_FRAMEBUFFER_SRGB
    gl->Enable(0x809D); // GL_MULTISAMPLE
    gl->Enable(0x864f); // GL_DEPTH_CLAMP
    gl->Enable(0x0B71); // GL_DEPTH_TEST
    gl->Enable(0x0B44); // GL_CULL_FACE
    gl->Enable(0x0BE2); // GL_BLEND
    gl->BlendFunc(0x0302, 0x0303); // GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA
    gl->ClipControl(0x8CA1, 0x935F); // GL_LOWER_LEFT, GL_ZERO_TO_ONE
    gl->DepthRange(1, 0);
    gl->ClearDepth(0);
    gl->DepthFunc(0x0204); // GL_GREATER
    gl->FrontFace(0x0900); // GL_CW
  }
  {
    // OPENGL REQUIRED GARBAGE ////////
    unsigned vao = 0;                //
    gl->CreateVertexArrays(1, &vao); //
    gl->BindVertexArray(vao);        //
    ///////////////////////////////////
  }
  profE("OpenGL state setup");

  if (out_scancodes != NULL) {
    profB("Scancode caching");
    XkbDescPtr xkbdesc = XkbGetMap(dpy, 0, XkbUseCoreKbd);
    XkbGetNames(dpy, XkbKeyNamesMask, xkbdesc);
    for (int i = xkbdesc->min_key_code; i <= xkbdesc->max_key_code; i += 1) {
      char * name = xkbdesc->names->keys[i].name;
      out_scancodes[i * 5 + 0] = name[0];
      out_scancodes[i * 5 + 1] = name[1];
      out_scancodes[i * 5 + 2] = name[2];
      out_scancodes[i * 5 + 3] = name[3];
      out_scancodes[i * 5 + 4] = 0;
    }
    XkbFreeNames(xkbdesc, XkbKeyNamesMask, 1);
    XkbFreeClientMap(xkbdesc, 0, 1);
    XFree(xkbdesc);
    profE("Scancode caching");
  }

  out_dpy[0] = dpy;
  out_win[0] = win;
  profE(__func__);
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

static inline unsigned GpuCast(unsigned buf_id, enum gpu_buf_format_e format, ptrdiff_t bytes_first, ptrdiff_t bytes_count) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  unsigned tex_id = 0;
  gl->CreateTextures(0x8C2A, 1, &tex_id); // GL_TEXTURE_BUFFER
  gl->TextureBufferRange(tex_id, format, buf_id, bytes_first, bytes_count);
  profE(__func__);
  return tex_id;
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
    break; case 0x83F0: // GL_COMPRESSED_RGB_S3TC_DXT1_EXT
           case 0x83F1: // GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
           case 0x83F2: // GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
           case 0x83F3: // GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
           case 0x8C4C: // GL_COMPRESSED_SRGB_S3TC_DXT1_EXT
           case 0x8C4D: // GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT
           case 0x8C4E: // GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT
           case 0x8C4F: { // GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT
             stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "[GpuLib] Warning: ARB_clear_texture forbids clearing of compressed textures.\n\n");
           }
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
    break; case 0x83F0: // GL_COMPRESSED_RGB_S3TC_DXT1_EXT
           case 0x83F1: // GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
           case 0x83F2: // GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
           case 0x83F3: // GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
           case 0x8C4C: // GL_COMPRESSED_SRGB_S3TC_DXT1_EXT
           case 0x8C4D: // GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT
           case 0x8C4E: // GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT
           case 0x8C4F: { // GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT
             stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "[GpuLib] Warning: ARB_clear_texture forbids clearing of compressed textures.\n\n");
           }
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
    break; case 0x83F0: // GL_COMPRESSED_RGB_S3TC_DXT1_EXT
           case 0x83F1: // GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
           case 0x83F2: // GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
           case 0x83F3: // GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
           case 0x8C4C: // GL_COMPRESSED_SRGB_S3TC_DXT1_EXT
           case 0x8C4D: // GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT
           case 0x8C4E: // GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT
           case 0x8C4F: { // GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT
             stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "[GpuLib] Warning: ARB_clear_texture forbids clearing of compressed textures.\n\n");
           }
  }
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

static inline void GpuGet(
    unsigned tex_id, int layer, int x, int y, int width, int height, int count, int mipmap_level,
    enum gpu_pix_format_e pixel_format, enum gpu_pix_type_e pixel_type, unsigned pixels_bytes, void * pixels)
{
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  gl->GetTextureSubImage(tex_id, mipmap_level, x, y, layer, width, height, count, pixel_format, pixel_type, pixels_bytes, pixels);
  profE(__func__);
}

static inline void GpuSet(
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

static inline void GpuGetCpi(
    unsigned tex_id, int layer, int x, int y, int width, int height, int count, int mipmap_level,
    unsigned pixels_bytes, void * pixels)
{
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  gl->GetCompressedTextureSubImage(tex_id, mipmap_level, x, y, layer, width, height, count, pixels_bytes, pixels);
  profE(__func__);
}

static inline void GpuSetCpi(
    unsigned tex_id, int layer, int x, int y, int width, int height, int count, int mipmap_level,
    enum gpu_tex_format_e compression_format, unsigned pixels_bytes, void * pixels)
{
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  gl->CompressedTextureSubImage3D(tex_id, mipmap_level, x, y, layer, width, height, count, compression_format, pixels_bytes, pixels);
  profE(__func__);
}

static inline int GpuLoadRgbImgBinary(unsigned tex_id, int width, int height, int layer_count, char * img_binary_filepath) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  int fd = stdlib_open(img_binary_filepath, O_RDONLY);
  if (fd == 0) {
    profE(__func__);
    return 1;
  }
  char * p = stdlib_mmap(0, (width * height * 3) * layer_count, PROT_READ, MAP_PRIVATE, fd, 0);
  if (p == NULL) {
    profE(__func__);
    return 1;
  }
  profB("gl->TextureSubImage3D");
  gl->TextureSubImage3D(tex_id, 0, 0, 0, 0, width, height, layer_count, 0x1907, 0x1401, p); // GL_RGB, GL_UNSIGNED_BYTE
  profE("gl->TextureSubImage3D");
  profB("gl->GenerateTextureMipmap");
  gl->GenerateTextureMipmap(tex_id);
  profE("gl->GenerateTextureMipmap");
  stdlib_munmap(p, (width * height * 3) * layer_count);
  stdlib_close(fd);
  profE(__func__);
  return 0;
}

static inline int GpuLoadRgbCbmBinary(unsigned tex_id, int width, int height, int layer_count, char * cbm_binary_filepath) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  int fd = stdlib_open(cbm_binary_filepath, O_RDONLY);
  if (fd == 0) {
    profE(__func__);
    return 1;
  }
  char * p = stdlib_mmap(0, (width * height * 3) * (layer_count * 6), PROT_READ, MAP_PRIVATE, fd, 0);
  if (p == NULL) {
    profE(__func__);
    return 1;
  }
  profB("gl->TextureSubImage3D");
  gl->TextureSubImage3D(tex_id, 0, 0, 0, 0, width, height, layer_count * 6, 0x1907, 0x1401, p); // GL_RGB, GL_UNSIGNED_BYTE
  profE("gl->TextureSubImage3D");
  profB("gl->GenerateTextureMipmap");
  gl->GenerateTextureMipmap(tex_id);
  profE("gl->GenerateTextureMipmap");
  stdlib_munmap(p, (width * height * 3) * (layer_count * 6));
  stdlib_close(fd);
  profE(__func__);
  return 0;
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

static inline unsigned GpuPro(
    unsigned shader_type, char * shader_string,
    char * xfb_name_0,
    char * xfb_name_1,
    char * xfb_name_2,
    char * xfb_name_3)
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

  int xfb_count = 0;
  {
    char * x0 = xfb_name_0;
    char * x1 = xfb_name_1;
    char * x2 = xfb_name_2;
    char * x3 = xfb_name_3;
    int xfb_place = 0;
    if (x0) { xfb_count += 1; xfb_place = 1; }
    if (x1) { xfb_count += 1; xfb_place = 2; }
    if (x2) { xfb_count += 1; xfb_place = 3; }
    if (x3) { xfb_count += 1; xfb_place = 4; }
    if (xfb_count != xfb_place) {
      stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "[GpuLib] Error: Transform feedback varying names should not have NULL values in-between.\n");
      stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "[GpuLib] Transform feedback varyings count: %d\n", xfb_count);
      stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "[GpuLib] Transform feedback varying name 0: %s%s%s\n", xfb_name_0 ? "\"" : "", xfb_name_0 ? xfb_name_0 : "NULL", xfb_name_0 ? "\"" : "");
      stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "[GpuLib] Transform feedback varying name 1: %s%s%s\n", xfb_name_1 ? "\"" : "", xfb_name_1 ? xfb_name_1 : "NULL", xfb_name_1 ? "\"" : "");
      stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "[GpuLib] Transform feedback varying name 2: %s%s%s\n", xfb_name_2 ? "\"" : "", xfb_name_2 ? xfb_name_2 : "NULL", xfb_name_2 ? "\"" : "");
      stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "[GpuLib] Transform feedback varying name 3: %s%s%s\n", xfb_name_3 ? "\"" : "", xfb_name_3 ? xfb_name_3 : "NULL", xfb_name_3 ? "\"" : "");
      stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "\n");
    }
    if (xfb_count > 0) {
      char * xfb_names[4] = {x0, x1, x2, x3};
      gl->TransformFeedbackVaryings(pro_id, xfb_count, xfb_names, 0x8C8D); // GL_SEPARATE_ATTRIBS
    }
  }

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
        stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "[GpuLib] Transform feedback varyings count: %d\n", xfb_count);
        stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "[GpuLib] Transform feedback varying name 0: %s%s%s\n", xfb_name_0 ? "\"" : "", xfb_name_0 ? xfb_name_0 : "NULL", xfb_name_0 ? "\"" : "");
        stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "[GpuLib] Transform feedback varying name 1: %s%s%s\n", xfb_name_1 ? "\"" : "", xfb_name_1 ? xfb_name_1 : "NULL", xfb_name_1 ? "\"" : "");
        stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "[GpuLib] Transform feedback varying name 2: %s%s%s\n", xfb_name_2 ? "\"" : "", xfb_name_2 ? xfb_name_2 : "NULL", xfb_name_2 ? "\"" : "");
        stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "[GpuLib] Transform feedback varying name 3: %s%s%s\n", xfb_name_3 ? "\"" : "", xfb_name_3 ? xfb_name_3 : "NULL", xfb_name_3 ? "\"" : "");
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

static inline unsigned GpuProFile(
    unsigned shader_type, char * shader_filepath,
    char * xfb_name_0,
    char * xfb_name_1,
    char * xfb_name_2,
    char * xfb_name_3)
{
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  int fd = stdlib_open(shader_filepath, O_RDONLY);
  if (fd == 0) {
    profE(__func__);
    return 0;
  }
  char * shader_string = stdlib_mmap(0, 256 * 1024 * 1024, PROT_READ, MAP_PRIVATE, fd, 0);
  if (shader_string == NULL) {
    profE(__func__);
    return 0;
  }
  int pro_id = GpuPro(shader_type, shader_string, xfb_name_0, xfb_name_1, xfb_name_2, xfb_name_3);
  stdlib_munmap(shader_string, 256 * 1024 * 1024);
  stdlib_close(fd);
  profE(__func__);
  return pro_id;
}

static inline unsigned GpuVert(char * shader_string) { return GpuPro(0x8B31, shader_string, NULL, NULL, NULL, NULL); } // GL_VERTEX_SHADER
static inline unsigned GpuFrag(char * shader_string) { return GpuPro(0x8B30, shader_string, NULL, NULL, NULL, NULL); } // GL_FRAGMENT_SHADER
static inline unsigned GpuVertFile(char * shader_filepath) { return GpuProFile(0x8B31, shader_filepath, NULL, NULL, NULL, NULL); } // GL_VERTEX_SHADER
static inline unsigned GpuFragFile(char * shader_filepath) { return GpuProFile(0x8B30, shader_filepath, NULL, NULL, NULL, NULL); } // GL_FRAGMENT_SHADER
static inline unsigned GpuVertXfb(char * shader_string, char * xfb_name_0, char * xfb_name_1, char * xfb_name_2, char * xfb_name_3) { return GpuPro(0x8B31, shader_string, xfb_name_0, xfb_name_1, xfb_name_2, xfb_name_3); } // GL_VERTEX_SHADER
static inline unsigned GpuFragXfb(char * shader_string, char * xfb_name_0, char * xfb_name_1, char * xfb_name_2, char * xfb_name_3) { return GpuPro(0x8B30, shader_string, xfb_name_0, xfb_name_1, xfb_name_2, xfb_name_3); } // GL_FRAGMENT_SHADER
static inline unsigned GpuVertXfbFile(char * shader_filepath, char * xfb_name_0, char * xfb_name_1, char * xfb_name_2, char * xfb_name_3) { return GpuProFile(0x8B31, shader_filepath, xfb_name_0, xfb_name_1, xfb_name_2, xfb_name_3); } // GL_VERTEX_SHADER
static inline unsigned GpuFragXfbFile(char * shader_filepath, char * xfb_name_0, char * xfb_name_1, char * xfb_name_2, char * xfb_name_3) { return GpuProFile(0x8B30, shader_filepath, xfb_name_0, xfb_name_1, xfb_name_2, xfb_name_3); } // GL_FRAGMENT_SHADER

static inline void GpuU32(unsigned program, int location, int count, unsigned * value) { __auto_type gl = g_gpulib_libgl; gl->ProgramUniform1uiv(program, location, count, value); }
static inline void GpuI32(unsigned program, int location, int count, int      * value) { __auto_type gl = g_gpulib_libgl; gl->ProgramUniform1iv(program, location, count, value);  }
static inline void GpuF32(unsigned program, int location, int count, float    * value) { __auto_type gl = g_gpulib_libgl; gl->ProgramUniform1fv(program, location, count, value);  }
static inline void GpuV2F(unsigned program, int location, int count, float    * value) { __auto_type gl = g_gpulib_libgl; gl->ProgramUniform2fv(program, location, count, value);  }
static inline void GpuV3F(unsigned program, int location, int count, float    * value) { __auto_type gl = g_gpulib_libgl; gl->ProgramUniform3fv(program, location, count, value);  }
static inline void GpuV4F(unsigned program, int location, int count, float    * value) { __auto_type gl = g_gpulib_libgl; gl->ProgramUniform4fv(program, location, count, value);  }

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

static inline void GpuDraw(enum gpu_mode_e mode, unsigned binded_dib_cmd_first, unsigned binded_dib_cmd_count) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  gl->MultiDrawElementsIndirect(mode, 0x1405, (void *)(binded_dib_cmd_first * 5 * sizeof(unsigned)), binded_dib_cmd_count, 0); // GL_UNSIGNED_INT
  profE(__func__);
}

static inline void GpuDrawXfb(enum gpu_mode_e mode, unsigned binded_dib_cmd_first, unsigned binded_dib_cmd_count) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  gl->Enable(0x8C89); // GL_RASTERIZER_DISCARD
  gl->BeginTransformFeedback(mode);
  gl->MultiDrawElementsIndirect(mode, 0x1405, (void *)(binded_dib_cmd_first * 5 * sizeof(unsigned)), binded_dib_cmd_count, 0); // GL_UNSIGNED_INT
  gl->EndTransformFeedback();
  gl->Disable(0x8C89);
  profE(__func__);
}

static inline void GpuDrawOnce(enum gpu_mode_e mode, unsigned first, unsigned count, unsigned instance_count) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  gl->DrawArraysInstanced(mode, first, count, instance_count);
  profE(__func__);
}

static inline void GpuDrawOnceXfb(enum gpu_mode_e mode, unsigned first, unsigned count, unsigned instance_count) {
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

static inline void GpuSwap(Display * dpy, Window win) {
  profB(__func__);
  __auto_type glx = g_gpulib_libglx;
  glx->SwapBuffers(dpy, win);
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

static inline void * GpuFence() {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  void * fence = gl->FenceSync(0x9117, 0); // GL_SYNC_GPU_COMMANDS_COMPLETE
  profE(__func__);
  return fence;
}

static inline int GpuFenceIsComplete(void * fence) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  int fence_status = 0;
  gl->GetSynciv(fence, 0x9114, 1, NULL, &fence_status); // GL_SYNC_STATUS
  profE(__func__);
  return fence_status == 0x9119 ? 1 : 0; // GL_SIGNALED
}

static inline void GpuSetDebugCallback(void * callback) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  gl->DebugMessageCallback(callback, NULL);
  profE(__func__);
}

static inline void GpuDebugCallback(unsigned source, unsigned type, unsigned id, unsigned severity, int length, char * message, void * userdata) {
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

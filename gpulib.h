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
#include <GL/glx.h>
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

#define GPU_VERT_HEAD                                          \
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

#define GPU_FRAG_HEAD                                          \
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

void (*glAttachShader)(unsigned, unsigned);
void (*glBeginTransformFeedback)(unsigned);
void (*glBindBuffer)(unsigned, unsigned);
void (*glBindFramebuffer)(unsigned, unsigned);
void (*glBindProgramPipeline)(unsigned);
void (*glBindSamplers)(int, int, unsigned *);
void (*glBindTextures)(int, int, unsigned *);
void (*glBindTransformFeedback)(unsigned, unsigned);
void (*glBindVertexArray)(unsigned);
void (*glBlitNamedFramebuffer)(unsigned, unsigned, int, int, int, int, int, int, int, int, unsigned, unsigned);
void (*glBufferStorage)(unsigned, ptrdiff_t, void *, unsigned);
void (*glClearTexSubImage)(unsigned, int, int, int, int, int, int, int, unsigned, unsigned, void *);
void (*glClipControl)(unsigned, unsigned);
void (*glCompileShader)(unsigned);
void (*glCompressedTextureSubImage3D)(unsigned, int, int, int, int, int, int, int, unsigned, unsigned, void *);
void (*glCreateBuffers)(int, unsigned *);
void (*glCreateFramebuffers)(int, unsigned *);
unsigned (*glCreateProgram)();
void (*glCreateProgramPipelines)(int, unsigned *);
void (*glCreateSamplers)(int, unsigned *);
unsigned (*glCreateShader)(unsigned);
void (*glCreateTextures)(unsigned, int, unsigned *);
void (*glCreateTransformFeedbacks)(int, unsigned *);
void (*glCreateVertexArrays)(int, unsigned *);
void (*glDebugMessageCallback)(void *, void *);
void (*glDeleteBuffers)(int, unsigned *);
void (*glDeleteFramebuffers)(int, unsigned *);
void (*glDeleteProgram)(unsigned);
void (*glDeleteProgramPipelines)(int, unsigned *);
void (*glDeleteSamplers)(int, unsigned *);
void (*glDeleteShader)(unsigned);
void (*glDeleteTransformFeedbacks)(int, unsigned *);
void (*glDetachShader)(unsigned, unsigned);
void (*glDrawArraysInstanced)(unsigned, unsigned, unsigned, unsigned);
void (*glEndTransformFeedback)();
void (*glGenBuffers)(int, unsigned *);
void (*glGenerateTextureMipmap)(unsigned);
void (*glGetCompressedTextureSubImage)(unsigned, int, int, int, int, int, int, int, int, void *);
void (*glGetProgramInfoLog)(unsigned, int, int *, char *);
void (*glGetProgramiv)(unsigned, unsigned, int *);
void (*glGetShaderInfoLog)(unsigned, int, int *, char *);
void (*glGetShaderiv)(unsigned, unsigned, int *);
char * (*glGetStringi)(unsigned, unsigned);
void (*glGetTextureSubImage)(unsigned, int, int, int, int, int, int, int, unsigned, unsigned, unsigned, void *);
void (*glLinkProgram)(unsigned);
void * (*glMapBufferRange)(unsigned, ptrdiff_t, ptrdiff_t, unsigned);
void * (*glMapNamedBufferRange)(unsigned, ptrdiff_t, ptrdiff_t, unsigned);
void (*glMultiDrawElementsIndirect)(unsigned, unsigned, void *, int, int);
void (*glNamedBufferStorage)(unsigned, ptrdiff_t, void *, unsigned);
void (*glNamedFramebufferDrawBuffer)(unsigned, int);
void (*glNamedFramebufferDrawBuffers)(unsigned, int, int *);
void (*glNamedFramebufferReadBuffer)(unsigned, int);
void (*glNamedFramebufferTextureLayer)(unsigned, int, unsigned, int, int);
void (*glProgramParameteri)(unsigned, unsigned, int);
void (*glProgramUniform1fv)(unsigned, int, int, float *);
void (*glProgramUniform1iv)(unsigned, int, int, int *);
void (*glProgramUniform1uiv)(unsigned, int, int, unsigned *);
void (*glProgramUniform2fv)(unsigned, int, int, float *);
void (*glProgramUniform3fv)(unsigned, int, int, float *);
void (*glProgramUniform4fv)(unsigned, int, int, float *);
void (*glSamplerParameteri)(unsigned, unsigned, int);
void (*glShaderSource)(unsigned, int, char **, int *);
void (*glTextureBufferRange)(unsigned, unsigned, unsigned, ptrdiff_t, ptrdiff_t);
void (*glTextureStorage3D)(unsigned, int, unsigned, int, int, int);
void (*glTextureStorage3DMultisample)(unsigned, int, unsigned, int, int, int, int);
void (*glTextureSubImage3D)(unsigned, int, int, int, int, int, int, int, unsigned, unsigned, void *);
void (*glTextureView)(unsigned, unsigned, unsigned, unsigned, int, int, int, int);
void (*glTransformFeedbackBufferRange)(unsigned, int, unsigned, ptrdiff_t, ptrdiff_t);
void (*glTransformFeedbackVaryings)(unsigned, int, char **, unsigned);
void (*glUseProgramStages)(unsigned, unsigned, unsigned);

struct gpu_sys_libc_t {
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
} g_gpulib_libc = {
  (void *)0xBAD,
  (void *)0xBAD,
  (void *)0xBAD,
  (void *)0xBAD,
  (void *)0xBAD,
  (void *)0xBAD,
  (void *)0xBAD,
  (void *)0xBAD,
  (void *)0xBAD,
  (void *)0xBAD,
  (void *)0xBAD,
  (void *)0xBAD,
  (void *)0xBAD,
  (void *)0xBAD,
  (void *)0xBAD,
  (void *)0xBAD,
  (void *)0xBAD,
};

static inline void GpuSysGetOpenGLProcedureAddresses() {
  glAttachShader = (void *)glXGetProcAddressARB((unsigned char *)"glAttachShader");
  glBeginTransformFeedback = (void *)glXGetProcAddressARB((unsigned char *)"glBeginTransformFeedback");
  glBindBuffer = (void *)glXGetProcAddressARB((unsigned char *)"glBindBuffer");
  glBindFramebuffer = (void *)glXGetProcAddressARB((unsigned char *)"glBindFramebuffer");
  glBindProgramPipeline = (void *)glXGetProcAddressARB((unsigned char *)"glBindProgramPipeline");
  glBindSamplers = (void *)glXGetProcAddressARB((unsigned char *)"glBindSamplers");
  glBindTextures = (void *)glXGetProcAddressARB((unsigned char *)"glBindTextures");
  glBindTransformFeedback = (void *)glXGetProcAddressARB((unsigned char *)"glBindTransformFeedback");
  glBindVertexArray = (void *)glXGetProcAddressARB((unsigned char *)"glBindVertexArray");
  glBlitNamedFramebuffer = (void *)glXGetProcAddressARB((unsigned char *)"glBlitNamedFramebuffer");
  glBufferStorage = (void *)glXGetProcAddressARB((unsigned char *)"glBufferStorage");
  glClearTexSubImage = (void *)glXGetProcAddressARB((unsigned char *)"glClearTexSubImage");
  glClipControl = (void *)glXGetProcAddressARB((unsigned char *)"glClipControl");
  glCompileShader = (void *)glXGetProcAddressARB((unsigned char *)"glCompileShader");
  glCompressedTextureSubImage3D = (void *)glXGetProcAddressARB((unsigned char *)"glCompressedTextureSubImage3D");
  glCreateBuffers = (void *)glXGetProcAddressARB((unsigned char *)"glCreateBuffers");
  glCreateFramebuffers = (void *)glXGetProcAddressARB((unsigned char *)"glCreateFramebuffers");
  glCreateProgram = (void *)glXGetProcAddressARB((unsigned char *)"glCreateProgram");
  glCreateProgramPipelines = (void *)glXGetProcAddressARB((unsigned char *)"glCreateProgramPipelines");
  glCreateSamplers = (void *)glXGetProcAddressARB((unsigned char *)"glCreateSamplers");
  glCreateShader = (void *)glXGetProcAddressARB((unsigned char *)"glCreateShader");
  glCreateTextures = (void *)glXGetProcAddressARB((unsigned char *)"glCreateTextures");
  glCreateTransformFeedbacks = (void *)glXGetProcAddressARB((unsigned char *)"glCreateTransformFeedbacks");
  glCreateVertexArrays = (void *)glXGetProcAddressARB((unsigned char *)"glCreateVertexArrays");
  glDebugMessageCallback = (void *)glXGetProcAddressARB((unsigned char *)"glDebugMessageCallback");
  glDeleteBuffers = (void *)glXGetProcAddressARB((unsigned char *)"glDeleteBuffers");
  glDeleteFramebuffers = (void *)glXGetProcAddressARB((unsigned char *)"glDeleteFramebuffers");
  glDeleteProgram = (void *)glXGetProcAddressARB((unsigned char *)"glDeleteProgram");
  glDeleteProgramPipelines = (void *)glXGetProcAddressARB((unsigned char *)"glDeleteProgramPipelines");
  glDeleteSamplers = (void *)glXGetProcAddressARB((unsigned char *)"glDeleteSamplers");
  glDeleteShader = (void *)glXGetProcAddressARB((unsigned char *)"glDeleteShader");
  glDeleteTransformFeedbacks = (void *)glXGetProcAddressARB((unsigned char *)"glDeleteTransformFeedbacks");
  glDetachShader = (void *)glXGetProcAddressARB((unsigned char *)"glDetachShader");
  glDrawArraysInstanced = (void *)glXGetProcAddressARB((unsigned char *)"glDrawArraysInstanced");
  glEndTransformFeedback = (void *)glXGetProcAddressARB((unsigned char *)"glEndTransformFeedback");
  glGenBuffers = (void *)glXGetProcAddressARB((unsigned char *)"glGenBuffers");
  glGenerateTextureMipmap = (void *)glXGetProcAddressARB((unsigned char *)"glGenerateTextureMipmap");
  glGetCompressedTextureSubImage = (void *)glXGetProcAddressARB((unsigned char *)"glGetCompressedTextureSubImage");
  glGetProgramInfoLog = (void *)glXGetProcAddressARB((unsigned char *)"glGetProgramInfoLog");
  glGetProgramiv = (void *)glXGetProcAddressARB((unsigned char *)"glGetProgramiv");
  glGetShaderInfoLog = (void *)glXGetProcAddressARB((unsigned char *)"glGetShaderInfoLog");
  glGetShaderiv = (void *)glXGetProcAddressARB((unsigned char *)"glGetShaderiv");
  glGetTextureSubImage = (void *)glXGetProcAddressARB((unsigned char *)"glGetTextureSubImage");
  glLinkProgram = (void *)glXGetProcAddressARB((unsigned char *)"glLinkProgram");
  glMapBufferRange = (void *)glXGetProcAddressARB((unsigned char *)"glMapBufferRange");
  glMapNamedBufferRange = (void *)glXGetProcAddressARB((unsigned char *)"glMapNamedBufferRange");
  glMultiDrawElementsIndirect = (void *)glXGetProcAddressARB((unsigned char *)"glMultiDrawElementsIndirect");
  glNamedBufferStorage = (void *)glXGetProcAddressARB((unsigned char *)"glNamedBufferStorage");
  glNamedFramebufferDrawBuffer = (void *)glXGetProcAddressARB((unsigned char *)"glNamedFramebufferDrawBuffer");
  glNamedFramebufferDrawBuffers = (void *)glXGetProcAddressARB((unsigned char *)"glNamedFramebufferDrawBuffers");
  glNamedFramebufferReadBuffer = (void *)glXGetProcAddressARB((unsigned char *)"glNamedFramebufferReadBuffer");
  glNamedFramebufferTextureLayer = (void *)glXGetProcAddressARB((unsigned char *)"glNamedFramebufferTextureLayer");
  glProgramParameteri = (void *)glXGetProcAddressARB((unsigned char *)"glProgramParameteri");
  glProgramUniform1fv = (void *)glXGetProcAddressARB((unsigned char *)"glProgramUniform1fv");
  glProgramUniform1iv = (void *)glXGetProcAddressARB((unsigned char *)"glProgramUniform1iv");
  glProgramUniform1uiv = (void *)glXGetProcAddressARB((unsigned char *)"glProgramUniform1uiv");
  glProgramUniform2fv = (void *)glXGetProcAddressARB((unsigned char *)"glProgramUniform2fv");
  glProgramUniform3fv = (void *)glXGetProcAddressARB((unsigned char *)"glProgramUniform3fv");
  glProgramUniform4fv = (void *)glXGetProcAddressARB((unsigned char *)"glProgramUniform4fv");
  glSamplerParameteri = (void *)glXGetProcAddressARB((unsigned char *)"glSamplerParameteri");
  glShaderSource = (void *)glXGetProcAddressARB((unsigned char *)"glShaderSource");
  glTextureBufferRange = (void *)glXGetProcAddressARB((unsigned char *)"glTextureBufferRange");
  glTextureStorage3D = (void *)glXGetProcAddressARB((unsigned char *)"glTextureStorage3D");
  glTextureStorage3DMultisample = (void *)glXGetProcAddressARB((unsigned char *)"glTextureStorage3DMultisample");
  glTextureSubImage3D = (void *)glXGetProcAddressARB((unsigned char *)"glTextureSubImage3D");
  glTextureView = (void *)glXGetProcAddressARB((unsigned char *)"glTextureView");
  glTransformFeedbackBufferRange = (void *)glXGetProcAddressARB((unsigned char *)"glTransformFeedbackBufferRange");
  glTransformFeedbackVaryings = (void *)glXGetProcAddressARB((unsigned char *)"glTransformFeedbackVaryings");
  glUseProgramStages = (void *)glXGetProcAddressARB((unsigned char *)"glUseProgramStages");
}

static inline void GpuSysGetLibcProcedureAddresses() {
  g_gpulib_libc.access = dlsym(NULL, "access");
  g_gpulib_libc.calloc = dlsym(NULL, "calloc");
  g_gpulib_libc.fgetc = dlsym(NULL, "fgetc");
  g_gpulib_libc.free = dlsym(NULL, "free");
  g_gpulib_libc.getpid = dlsym(NULL, "getpid");
  g_gpulib_libc.pclose = dlsym(NULL, "pclose");
  g_gpulib_libc.popen = dlsym(NULL, "popen");
  g_gpulib_libc.readlink = dlsym(NULL, "readlink");
  g_gpulib_libc.realloc = dlsym(NULL, "realloc");
  g_gpulib_libc.setlocale = dlsym(NULL, "setlocale");
  g_gpulib_libc.strcat = dlsym(NULL, "strcat");
  g_gpulib_libc.strcmp = dlsym(NULL, "strcmp");
  g_gpulib_libc.strlen = dlsym(NULL, "strlen");
  g_gpulib_libc.strndup = dlsym(NULL, "strndup");
  g_gpulib_libc.strrchr = dlsym(NULL, "strrchr");
  g_gpulib_libc.strtol = dlsym(NULL, "strtol");
  g_gpulib_libc.usleep = dlsym(NULL, "usleep");
}

static inline long GpuSysShell(char * cmd, char * out) {
  int * ret = g_gpulib_libc.popen(cmd, "r");
  long i = 0;
  for (int c = g_gpulib_libc.fgetc(ret); c != -1; i += 1) {
    if (out) out[i] = (char)c;
    c = g_gpulib_libc.fgetc(ret);
  }
  if (out) out[i] = 0;
  g_gpulib_libc.pclose(ret);
  return i + 1;
}

static inline char * GpuSysReadSymLink(char * path) {
  char * retval = NULL;
  ssize_t len = 64;
  ssize_t rc = -1;
  for (;;) {
    char * ptr = g_gpulib_libc.realloc(retval, (size_t)len);
    retval = ptr;
    rc = g_gpulib_libc.readlink(path, retval, len);
    if (rc == -1) {
      break;
    } else if (rc < len) {
      retval[rc] = '\0';
      return retval;
    }
    len *= 2;
  }
  g_gpulib_libc.free(retval);
  return NULL;
}

static inline char * GpuSysGetBasePath() {
  char * retval = NULL;
  if (retval == NULL && (g_gpulib_libc.access("/proc", 0) == 0)) {
    retval = GpuSysReadSymLink("/proc/self/exe");
    if (retval == NULL) {
      char path[64] = {0};
      int rc = stdlib_snprintf(path, sizeof(path), "/proc/%llu/exe", (unsigned long long)g_gpulib_libc.getpid());
      if ((rc > 0) && (rc < sizeof(path)))
        retval = GpuSysReadSymLink(path);
    }
  }
  if (retval != NULL) {
    char * ptr = g_gpulib_libc.strrchr(retval, '/');
    if (ptr != NULL) {
      *(ptr + 1) = '\0';
    } else {
      g_gpulib_libc.free(retval);
      retval = NULL;
    }
  }
  if (retval != NULL) {
    char * ptr = g_gpulib_libc.realloc(retval, g_gpulib_libc.strlen(retval) + 1);
    if (ptr != NULL)
      retval = ptr;
  }
  return retval;
}

static inline void GpuSysSetRelativeMouseMode(Display * dpy, Window win, int enabled) {
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
      g_gpulib_libc.usleep(50 * 1000);
    }
  } else {
    XUndefineCursor(dpy, win);
    XUngrabPointer(dpy, CurrentTime);
  }
}

static inline int GpuSysIsExtensionSupported(char * extension) {
  int num_extensions = 0;
  glGetIntegerv(GL_NUM_EXTENSIONS, &num_extensions);
  for (int i = 0; i < num_extensions; i += 1) {
    char * ext = glGetStringi(GL_EXTENSIONS, i);
    if (g_gpulib_libc.strcmp(ext, extension) == 0)
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

static inline void GpuSysX11Window(
    char * title, int title_bytes, int x, int y, int w, int h, int msaa_sample_count,
    Display ** out_display, Window * out_window)
{
  profB("Set locale");
  g_gpulib_libc.setlocale(6, ""); // LC_ALL
  if (XSupportsLocale())
    XSetLocaleModifiers("@im=none");
  profE("Set locale");

  profB("XOpenDisplay");
  Display * dpy = XOpenDisplay(NULL);
  profE("XOpenDisplay");
  stdlib_assert(dpy != NULL);

  GLXFBConfig fbconfig = 0;
  XVisualInfo * visual = NULL;
  {
    int glx_attribs[] = {
      GLX_DRAWABLE_TYPE,  GLX_WINDOW_BIT,
      GLX_RENDER_TYPE,    GLX_RGBA_BIT,
      GLX_RED_SIZE,       8,
      GLX_GREEN_SIZE,     8,
      GLX_BLUE_SIZE,      8,
      GLX_ALPHA_SIZE,     8,
      GLX_DEPTH_SIZE,     24,
      GLX_STENCIL_SIZE,   8,
      GLX_DOUBLEBUFFER,   1,
      GLX_SAMPLE_BUFFERS, 1,
      GLX_SAMPLES,        msaa_sample_count,
      None
    };
    int fbconfigs_count = 0;
    profB("glXChooseFBConfig");
    GLXFBConfig * fbconfigs = glXChooseFBConfig(dpy, DefaultScreen(dpy), glx_attribs, &fbconfigs_count);
    profE("glXChooseFBConfig");
    profB("fbconfig search");
    for (int i = 0; i < fbconfigs_count; i += 1) {
      XFree(visual);
      visual = glXGetVisualFromFBConfig(dpy, fbconfigs[i]);
      if (visual == NULL)
        continue;
      XRenderPictFormat * format = XRenderFindVisualFormat(dpy, visual->visual);
      if (format == NULL)
        continue;
      fbconfig = fbconfigs[i];
      if (format->direct.alphaMask > 0)
        break;
    }
    XFree(fbconfigs);
    profE("fbconfig search");
  }
  stdlib_assert(fbconfig != 0);

#if 0
  {
    int red_size = 0, green_size = 0, blue_size = 0, alpha_size = 0, depth_size = 0, stencil_size = 0, doublebuffer = 0, sample_buffers = 0, samples = 0;
    glXGetFBConfigAttrib(dpy, fbconfig, GLX_RED_SIZE,       &red_size);
    glXGetFBConfigAttrib(dpy, fbconfig, GLX_GREEN_SIZE,     &green_size);
    glXGetFBConfigAttrib(dpy, fbconfig, GLX_BLUE_SIZE,      &blue_size);
    glXGetFBConfigAttrib(dpy, fbconfig, GLX_ALPHA_SIZE,     &alpha_size);
    glXGetFBConfigAttrib(dpy, fbconfig, GLX_DEPTH_SIZE,     &depth_size);
    glXGetFBConfigAttrib(dpy, fbconfig, GLX_STENCIL_SIZE,   &stencil_size);
    glXGetFBConfigAttrib(dpy, fbconfig, GLX_DOUBLEBUFFER,   &doublebuffer);
    glXGetFBConfigAttrib(dpy, fbconfig, GLX_SAMPLE_BUFFERS, &sample_buffers);
    glXGetFBConfigAttrib(dpy, fbconfig, GLX_SAMPLES,        &samples);
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

  GLXContext glx_ctx = NULL;
  {
    GLXContext (*glXCreateContextAttribsARB)(Display *, GLXFBConfig, GLXContext, int, int *) = (void *)glXGetProcAddressARB((unsigned char *)"glXCreateContextAttribsARB");
    stdlib_assert(glXCreateContextAttribsARB != NULL);
    int attribs[] = {
      0x2091, 3, // GLX_CONTEXT_MAJOR_VERSION_ARB
      0x2092, 3, // GLX_CONTEXT_MINOR_VERSION_ARB
      GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
      None
    };
    profB("glXCreateContextAttribsARB");
    glx_ctx = glXCreateContextAttribsARB(dpy, fbconfig, 0, 1, attribs);
    profE("glXCreateContextAttribsARB");
    stdlib_assert(glx_ctx != NULL);
  }

  {
    profB("glXMakeContextCurrent");
    int is_glx_context_current = glXMakeContextCurrent(dpy, win, win, glx_ctx);
    profE("glXMakeContextCurrent");
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
    char * window_title, int window_title_bytes, int window_width, int window_height, int msaa_samples,
    char * out_scancodes, Display ** out_dpy, Window * out_win)
{
  GpuSysGetLibcProcedureAddresses();

  profB(__func__);
  Display * dpy = NULL;
  Window win = 0;
  GpuSysX11Window(window_title, window_title_bytes, 0, 0, window_width, window_height, msaa_samples, &dpy, &win);

  glGetStringi = (void *)glXGetProcAddressARB((unsigned char *)"glGetStringi");

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

  profB("GpuSysGetOpenGLProcedureAddresses");
  GpuSysGetOpenGLProcedureAddresses();
  profE("GpuSysGetOpenGLProcedureAddresses");

  profB("OpenGL state setup");
  {
    glViewport(0, 0, window_width, window_height);
#ifndef RELEASE
    glEnable(0x92E0); // GL_DEBUG_OUTPUT
    glEnable(0x8242); // GL_DEBUG_OUTPUT_SYNCHRONOUS
#endif
    glEnable(0x884F); // GL_TEXTURE_CUBE_MAP_SEAMLESS
    glEnable(0x8DB9); // GL_FRAMEBUFFER_SRGB
    glEnable(0x809D); // GL_MULTISAMPLE
    glEnable(0x864f); // GL_DEPTH_CLAMP
    glEnable(0x0B71); // GL_DEPTH_TEST
    glEnable(0x0B44); // GL_CULL_FACE
    glEnable(0x0BE2); // GL_BLEND
    glBlendFunc(0x0302, 0x0303); // GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA
    glClipControl(0x8CA1, 0x935F); // GL_LOWER_LEFT, GL_ZERO_TO_ONE
    glDepthRange(1, 0);
    glClearDepth(0);
    glDepthFunc(0x0204); // GL_GREATER
    glFrontFace(0x0900); // GL_CW
  }
  {
    // OPENGL REQUIRED GARBAGE //////
    unsigned vao = 0;              //
    glCreateVertexArrays(1, &vao); //
    glBindVertexArray(vao);        //
    /////////////////////////////////
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
  unsigned buf_id = 0;
  glCreateBuffers(1, &buf_id);
  out_buf_id[0] = buf_id;
  glNamedBufferStorage(buf_id, bytes, NULL, 0xC2); // GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT
  void * buf_ptr = glMapNamedBufferRange(buf_id, 0, bytes, 0xC2);
  profE(__func__);
  return buf_ptr;
}

static inline void * GpuCalloc(ptrdiff_t bytes, unsigned * out_buf_id) {
  profB(__func__);
  void * buf_ptr = GpuMalloc(bytes, out_buf_id);
  memset(buf_ptr, 0, bytes);
  profE(__func__);
  return buf_ptr;
}

static inline unsigned GpuCast(unsigned buf_id, enum gpu_buf_format_e format, ptrdiff_t bytes_first, ptrdiff_t bytes_count) {
  profB(__func__);
  unsigned tex_id = 0;
  glCreateTextures(0x8C2A, 1, &tex_id); // GL_TEXTURE_BUFFER
  glTextureBufferRange(tex_id, format, buf_id, bytes_first, bytes_count);
  profE(__func__);
  return tex_id;
}

static inline unsigned * GpuMallocIndices(ptrdiff_t count, unsigned * out_idb_id) {
  profB(__func__);
  unsigned idb_id = 0;
  glGenBuffers(1, &idb_id);
  out_idb_id[0] = idb_id;
  glBindBuffer(0x8893, idb_id); // GL_ELEMENT_ARRAY_BUFFER
  glBufferStorage(0x8893, count * sizeof(unsigned), NULL, 0xC2); // GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT
  unsigned * idb_ptr = glMapBufferRange(0x8893, 0, count * sizeof(unsigned), 0xC2);
  glBindBuffer(0x8893, 0);
  profE(__func__);
  return idb_ptr;
}

static inline unsigned * GpuCallocIndices(ptrdiff_t count, unsigned * out_idb_id) {
  profB(__func__);
  unsigned * idb_ptr = GpuMallocIndices(count, out_idb_id);
  memset(idb_ptr, 0, count * sizeof(unsigned));
  profE(__func__);
  return idb_ptr;
}

static inline struct gpu_cmd_t * GpuMallocCommands(ptrdiff_t count, unsigned * out_dib_id) {
  profB(__func__);
  unsigned dib_id = 0;
  glGenBuffers(1, &dib_id);
  out_dib_id[0] = dib_id;
  glBindBuffer(0x8F3F, dib_id); // GL_DRAW_INDIRECT_BUFFER
  glBufferStorage(0x8F3F, count * sizeof(struct gpu_cmd_t), NULL, 0xC2); // GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT
  struct gpu_cmd_t * dib_ptr = glMapBufferRange(0x8F3F, 0, count * sizeof(struct gpu_cmd_t), 0xC2);
  glBindBuffer(0x8F3F, 0);
  profE(__func__);
  return dib_ptr;
}

static inline struct gpu_cmd_t * GpuCallocCommands(ptrdiff_t count, unsigned * out_dib_id) {
  profB(__func__);
  struct gpu_cmd_t * dib_ptr = GpuMallocCommands(count, out_dib_id);
  memset(dib_ptr, 0, count * sizeof(struct gpu_cmd_t));
  profE(__func__);
  return dib_ptr;
}

static inline unsigned GpuMallocImg(enum gpu_tex_format_e format, int width, int height, int layer_count, int mipmap_count) {
  profB(__func__);
  unsigned tex_id = 0;
  glCreateTextures(0x8C1A, 1, &tex_id); // GL_TEXTURE_2D_ARRAY
  if (width != height && mipmap_count > 1)
    stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "[GpuLib] Warning: Rectangle image (width: %d, height: %d) is set to have more than one mipmap (mipmap_count: %d).\n\n", width, height, mipmap_count);
  if (width / (1 << (mipmap_count - 1)) < 1)
    stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "[GpuLib] Warning: Image (width: %d) mipmap count (mipmap_count: %d) is greater than the max count of %d.\n\n", width, mipmap_count, stdlib_log2i(width) + 1);
  glTextureStorage3D(tex_id, mipmap_count, format, width, height, layer_count);
  profE(__func__);
  return tex_id;
}

static inline unsigned GpuMallocCbm(enum gpu_tex_format_e format, int width, int height, int layer_count, int mipmap_count) {
  profB(__func__);
  unsigned tex_id = 0;
  glCreateTextures(0x9009, 1, &tex_id); // GL_TEXTURE_CUBE_MAP_ARRAY
  if (width != height)
    stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "[GpuLib] Warning: Rectangle cubemap (width: %d, height: %d).\n\n", width, height);
  if (width / (1 << (mipmap_count - 1)) < 1)
    stdlib_nprintf(GPULIB_MAX_PRINT_BYTES, "[GpuLib] Warning: Cubemap (width: %d) mipmap count (mipmap_count: %d) is greater than the max count of %d.\n\n", width, mipmap_count, stdlib_log2i(width) + 1);
  glTextureStorage3D(tex_id, mipmap_count, format, width, height, layer_count * 6);
  profE(__func__);
  return tex_id;
}

static inline unsigned GpuMallocMsi(enum gpu_tex_format_e format, int width, int height, int layer_count, int msaa_samples) {
  profB(__func__);
  unsigned tex_id = 0;
  glCreateTextures(0x9102, 1, &tex_id); // GL_TEXTURE_2D_MULTISAMPLE_ARRAY
  glTextureStorage3DMultisample(tex_id, msaa_samples, format, width, height, layer_count, 0);
  profE(__func__);
  return tex_id;
}

static inline unsigned GpuCallocImg(enum gpu_tex_format_e format, int width, int height, int layer_count, int mipmap_count) {
  profB(__func__);
  unsigned tex_id = GpuMallocImg(format, width, height, layer_count, mipmap_count);
  switch (format) {
    break; case 0x8CAC: { for (int i = 0; i < mipmap_count; i += 1) glClearTexSubImage(tex_id, i, 0, 0, 0, width / (1 << i), height / (1 << i), layer_count, 0x1902, 0x1406, (float [1]){0}); }                  // GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_FLOAT
    break; case 0x8051: { for (int i = 0; i < mipmap_count; i += 1) glClearTexSubImage(tex_id, i, 0, 0, 0, width / (1 << i), height / (1 << i), layer_count, 0x1907, 0x1400, (unsigned char [3]){0, 0, 0}); }    // GL_RGB8, GL_RGB, GL_BYTE
    break; case 0x8058: { for (int i = 0; i < mipmap_count; i += 1) glClearTexSubImage(tex_id, i, 0, 0, 0, width / (1 << i), height / (1 << i), layer_count, 0x1908, 0x1400, (unsigned char [4]){0, 0, 0, 0}); } // GL_RGBA8, GL_RGBA, GL_BYTE
    break; case 0x8C41: { for (int i = 0; i < mipmap_count; i += 1) glClearTexSubImage(tex_id, i, 0, 0, 0, width / (1 << i), height / (1 << i), layer_count, 0x1907, 0x1400, (unsigned char [3]){0, 0, 0}); }    // GL_SRGB8, GL_RGB, GL_BYTE
    break; case 0x8C43: { for (int i = 0; i < mipmap_count; i += 1) glClearTexSubImage(tex_id, i, 0, 0, 0, width / (1 << i), height / (1 << i), layer_count, 0x1908, 0x1400, (unsigned char [4]){0, 0, 0, 0}); } // GL_SRGB8_ALPHA8, GL_RGBA, GL_BYTE
    break; case 0x8814: { for (int i = 0; i < mipmap_count; i += 1) glClearTexSubImage(tex_id, i, 0, 0, 0, width / (1 << i), height / (1 << i), layer_count, 0x1908, 0x1406, (float [4]){0, 0, 0, 0}); }         // GL_RGBA32F, GL_RGBA, GL_FLOAT
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
  unsigned tex_id = GpuMallocCbm(format, width, height, layer_count, mipmap_count);
  switch (format) {
    break; case 0x8CAC: { for (int i = 0; i < mipmap_count; i += 1) glClearTexSubImage(tex_id, i, 0, 0, 0, width / (1 << i), height / (1 << i), layer_count * 6, 0x1902, 0x1406, (float [1]){0}); }                  // GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_FLOAT
    break; case 0x8051: { for (int i = 0; i < mipmap_count; i += 1) glClearTexSubImage(tex_id, i, 0, 0, 0, width / (1 << i), height / (1 << i), layer_count * 6, 0x1907, 0x1400, (unsigned char [3]){0, 0, 0}); }    // GL_RGB8, GL_RGB, GL_BYTE
    break; case 0x8058: { for (int i = 0; i < mipmap_count; i += 1) glClearTexSubImage(tex_id, i, 0, 0, 0, width / (1 << i), height / (1 << i), layer_count * 6, 0x1908, 0x1400, (unsigned char [4]){0, 0, 0, 0}); } // GL_RGBA8, GL_RGBA, GL_BYTE
    break; case 0x8C41: { for (int i = 0; i < mipmap_count; i += 1) glClearTexSubImage(tex_id, i, 0, 0, 0, width / (1 << i), height / (1 << i), layer_count * 6, 0x1907, 0x1400, (unsigned char [3]){0, 0, 0}); }    // GL_SRGB8, GL_RGB, GL_BYTE
    break; case 0x8C43: { for (int i = 0; i < mipmap_count; i += 1) glClearTexSubImage(tex_id, i, 0, 0, 0, width / (1 << i), height / (1 << i), layer_count * 6, 0x1908, 0x1400, (unsigned char [4]){0, 0, 0, 0}); } // GL_SRGB8_ALPHA8, GL_RGBA, GL_BYTE
    break; case 0x8814: { for (int i = 0; i < mipmap_count; i += 1) glClearTexSubImage(tex_id, i, 0, 0, 0, width / (1 << i), height / (1 << i), layer_count * 6, 0x1908, 0x1406, (float [4]){0, 0, 0, 0}); }         // GL_RGBA32F, GL_RGBA, GL_FLOAT
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
  unsigned tex_id = GpuMallocMsi(format, width, height, layer_count, msaa_samples);
  switch (format) {
    break; case 0x8CAC: { glClearTexSubImage(tex_id, 0, 0, 0, 0, width, height, layer_count, 0x1902, 0x1406, (float [1]){0}); }                  // GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_FLOAT
    break; case 0x8051: { glClearTexSubImage(tex_id, 0, 0, 0, 0, width, height, layer_count, 0x1907, 0x1400, (unsigned char [3]){0, 0, 0}); }    // GL_RGB8, GL_RGB, GL_BYTE
    break; case 0x8058: { glClearTexSubImage(tex_id, 0, 0, 0, 0, width, height, layer_count, 0x1908, 0x1400, (unsigned char [4]){0, 0, 0, 0}); } // GL_RGBA8, GL_RGBA, GL_BYTE
    break; case 0x8C41: { glClearTexSubImage(tex_id, 0, 0, 0, 0, width, height, layer_count, 0x1907, 0x1400, (unsigned char [3]){0, 0, 0}); }    // GL_SRGB8, GL_RGB, GL_BYTE
    break; case 0x8C43: { glClearTexSubImage(tex_id, 0, 0, 0, 0, width, height, layer_count, 0x1908, 0x1400, (unsigned char [4]){0, 0, 0, 0}); } // GL_SRGB8_ALPHA8, GL_RGBA, GL_BYTE
    break; case 0x8814: { glClearTexSubImage(tex_id, 0, 0, 0, 0, width, height, layer_count, 0x1908, 0x1406, (float [4]){0, 0, 0, 0}); }         // GL_RGBA32F, GL_RGBA, GL_FLOAT
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
  unsigned new_tex_id = 0;
  glGenTextures(1, &new_tex_id);
  glTextureView(new_tex_id, 0x8C1A, tex_id, format, mipmap_first, mipmap_count, layer_first, layer_count); // GL_TEXTURE_2D_ARRAY
  profE(__func__);
  return new_tex_id;
}

static inline unsigned GpuCastCbm(
    unsigned tex_id, enum gpu_tex_format_e format, int layer_first, int layer_count, int mipmap_first, int mipmap_count)
{
  profB(__func__);
  unsigned new_tex_id = 0;
  glGenTextures(1, &new_tex_id);
  glTextureView(new_tex_id, 0x9009, tex_id, format, mipmap_first, mipmap_count, layer_first * 6, layer_count * 6); // GL_TEXTURE_CUBE_MAP_ARRAY
  profE(__func__);
  return new_tex_id;
}

static inline unsigned GpuCastMsi(
    unsigned tex_id, enum gpu_tex_format_e format, int layer_first, int layer_count, int mipmap_first, int mipmap_count)
{
  profB(__func__);
  unsigned new_tex_id = 0;
  glGenTextures(1, &new_tex_id);
  glTextureView(new_tex_id, 0x9102, tex_id, format, mipmap_first, mipmap_count, layer_first, layer_count); // GL_TEXTURE_2D_MULTISAMPLE_ARRAY
  profE(__func__);
  return new_tex_id;
}

static inline void GpuGet(
    unsigned tex_id, int layer, int x, int y, int width, int height, int count, int mipmap_level,
    enum gpu_pix_format_e pixel_format, enum gpu_pix_type_e pixel_type, unsigned pixels_bytes, void * pixels)
{
  profB(__func__);
  glGetTextureSubImage(tex_id, mipmap_level, x, y, layer, width, height, count, pixel_format, pixel_type, pixels_bytes, pixels);
  profE(__func__);
}

static inline void GpuSet(
    unsigned tex_id, int layer, int x, int y, int width, int height, int count, int mipmap_level,
    enum gpu_pix_format_e pixel_format, enum gpu_pix_type_e pixel_type, void * pixels)
{
  profB(__func__);
  glTextureSubImage3D(tex_id, mipmap_level, x, y, layer, width, height, count, pixel_format, pixel_type, pixels);
  profE(__func__);
}

static inline void GpuSetPix(
    unsigned tex_id, int layer, int x, int y, int width, int height, int count, int mipmap_level,
    enum gpu_pix_format_e pixel_format, enum gpu_pix_type_e pixel_type, void * pixel)
{
  profB(__func__);
  glClearTexSubImage(tex_id, mipmap_level, x, y, layer, width, height, count, pixel_format, pixel_type, pixel);
  profE(__func__);
}

static inline void GpuGetCpi(
    unsigned tex_id, int layer, int x, int y, int width, int height, int count, int mipmap_level,
    unsigned pixels_bytes, void * pixels)
{
  profB(__func__);
  glGetCompressedTextureSubImage(tex_id, mipmap_level, x, y, layer, width, height, count, pixels_bytes, pixels);
  profE(__func__);
}

static inline void GpuSetCpi(
    unsigned tex_id, int layer, int x, int y, int width, int height, int count, int mipmap_level,
    enum gpu_tex_format_e compression_format, unsigned pixels_bytes, void * pixels)
{
  profB(__func__);
  glCompressedTextureSubImage3D(tex_id, mipmap_level, x, y, layer, width, height, count, compression_format, pixels_bytes, pixels);
  profE(__func__);
}

static inline int GpuLoadRgbImgBinary(unsigned tex_id, int width, int height, int layer_count, char * img_binary_filepath) {
  profB(__func__);
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
  profB("glTextureSubImage3D");
  glTextureSubImage3D(tex_id, 0, 0, 0, 0, width, height, layer_count, 0x1907, 0x1401, p); // GL_RGB, GL_UNSIGNED_BYTE
  profE("glTextureSubImage3D");
  profB("glGenerateTextureMipmap");
  glGenerateTextureMipmap(tex_id);
  profE("glGenerateTextureMipmap");
  stdlib_munmap(p, (width * height * 3) * layer_count);
  stdlib_close(fd);
  profE(__func__);
  return 0;
}

static inline int GpuLoadRgbCbmBinary(unsigned tex_id, int width, int height, int layer_count, char * cbm_binary_filepath) {
  profB(__func__);
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
  profB("glTextureSubImage3D");
  glTextureSubImage3D(tex_id, 0, 0, 0, 0, width, height, layer_count * 6, 0x1907, 0x1401, p); // GL_RGB, GL_UNSIGNED_BYTE
  profE("glTextureSubImage3D");
  profB("glGenerateTextureMipmap");
  glGenerateTextureMipmap(tex_id);
  profE("glGenerateTextureMipmap");
  stdlib_munmap(p, (width * height * 3) * (layer_count * 6));
  stdlib_close(fd);
  profE(__func__);
  return 0;
}

static inline unsigned GpuSmp(
    int max_anisotropy, enum gpu_smp_filter_e min_filter, enum gpu_smp_filter_e mag_filter, enum gpu_smp_wrapping_e wrapping)
{
  profB(__func__);
  unsigned smp_id = 0;
  glCreateSamplers(1, &smp_id);
  if (max_anisotropy > 0)
    glSamplerParameteri(smp_id, 0x84FE, max_anisotropy); // GL_TEXTURE_MAX_ANISOTROPY_EXT
  glSamplerParameteri(smp_id, 0x2801, min_filter);       // GL_TEXTURE_MIN_FILTER
  glSamplerParameteri(smp_id, 0x2800, mag_filter);       // GL_TEXTURE_MAG_FILTER
  glSamplerParameteri(smp_id, 0x2802, wrapping);         // GL_TEXTURE_WRAP_S
  glSamplerParameteri(smp_id, 0x2803, wrapping);         // GL_TEXTURE_WRAP_T
  glSamplerParameteri(smp_id, 0x8072, wrapping);         // GL_TEXTURE_WRAP_R
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
  unsigned shader_id = glCreateShader(shader_type);

  glShaderSource(shader_id, 1, (char **)&shader_string, NULL);
  glCompileShader(shader_id);

  {
    int is_compiled = 0;
    glGetShaderiv(shader_id, 0x8B81, &is_compiled); // GL_COMPILE_STATUS
    if (!is_compiled) {
      int info_len = 0;
      glGetShaderiv(shader_id, 0x8B84, &info_len); // GL_INFO_LOG_LENGTH
      if (info_len > 1) {
        char info_log[info_len + 1];
        info_log[info_len] = 0;
        glGetShaderInfoLog(shader_id, info_len, NULL, info_log);
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
      glDeleteShader(shader_id);
      return 0;
    }
  }

  unsigned pro_id = glCreateProgram();
  glProgramParameteri(pro_id, 0x8258, 1); // GL_PROGRAM_SEPARABLE

  glAttachShader(pro_id, shader_id);

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
      glTransformFeedbackVaryings(pro_id, xfb_count, xfb_names, 0x8C8D); // GL_SEPARATE_ATTRIBS
    }
  }

  glLinkProgram(pro_id);

  {
    int is_linked = 0;
    glGetProgramiv(pro_id, 0x8B82, &is_linked); // GL_LINK_STATUS
    if (!is_linked) {
      int info_len = 0;
      glGetProgramiv(pro_id, 0x8B84, &info_len); // GL_INFO_LOG_LENGTH
      if (info_len > 1) {
        char info_log[info_len + 1];
        info_log[info_len] = 0;
        glGetProgramInfoLog(pro_id, info_len, NULL, info_log);
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
      glDetachShader(pro_id, shader_id);
      glDeleteShader(shader_id);
      return 0;
    }
  }

  glDetachShader(pro_id, shader_id);
  glDeleteShader(shader_id);
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

static inline void GpuU32(unsigned program, int location, int count, unsigned * value) { glProgramUniform1uiv(program, location, count, value); }
static inline void GpuI32(unsigned program, int location, int count, int      * value) { glProgramUniform1iv(program, location, count, value);  }
static inline void GpuF32(unsigned program, int location, int count, float    * value) { glProgramUniform1fv(program, location, count, value);  }
static inline void GpuV2F(unsigned program, int location, int count, float    * value) { glProgramUniform2fv(program, location, count, value);  }
static inline void GpuV3F(unsigned program, int location, int count, float    * value) { glProgramUniform3fv(program, location, count, value);  }
static inline void GpuV4F(unsigned program, int location, int count, float    * value) { glProgramUniform4fv(program, location, count, value);  }

static inline unsigned GpuPpo(unsigned vert_pro_id, unsigned frag_pro_id) {
  profB(__func__);
  unsigned ppo_id = 0;
  glCreateProgramPipelines(1, &ppo_id);
  if (vert_pro_id) glUseProgramStages(ppo_id, 1, vert_pro_id);
  if (frag_pro_id) glUseProgramStages(ppo_id, 2, frag_pro_id);
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
  unsigned fbo_id = 0;
  glCreateFramebuffers(1, &fbo_id);
  glNamedFramebufferTextureLayer(fbo_id, 0x8CE0 + 0, color_tex_id_0, 0, color_tex_layer_0); // GL_COLOR_ATTACHMENT0
  glNamedFramebufferTextureLayer(fbo_id, 0x8CE0 + 1, color_tex_id_1, 0, color_tex_layer_1);
  glNamedFramebufferTextureLayer(fbo_id, 0x8CE0 + 2, color_tex_id_2, 0, color_tex_layer_2);
  glNamedFramebufferTextureLayer(fbo_id, 0x8CE0 + 3, color_tex_id_3, 0, color_tex_layer_3);
  glNamedFramebufferTextureLayer(fbo_id, 0x8D00 + 0, depth_tex_id_0, 0, depth_tex_layer_0); // GL_DEPTH_ATTACHMENT
  int attachments[4] = {
    color_tex_id_0 ? 0x8CE0 + 0 : 0,
    color_tex_id_1 ? 0x8CE0 + 1 : 0,
    color_tex_id_2 ? 0x8CE0 + 2 : 0,
    color_tex_id_3 ? 0x8CE0 + 3 : 0
  };
  glNamedFramebufferDrawBuffers(fbo_id, 4, attachments);
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
  unsigned xfb_id = 0;
  glCreateTransformFeedbacks(1, &xfb_id);
  if (buf_0_id) glTransformFeedbackBufferRange(xfb_id, 0, buf_0_id, buf_0_bytes_first, buf_0_bytes_count);
  if (buf_1_id) glTransformFeedbackBufferRange(xfb_id, 1, buf_1_id, buf_1_bytes_first, buf_1_bytes_count);
  if (buf_2_id) glTransformFeedbackBufferRange(xfb_id, 2, buf_2_id, buf_2_bytes_first, buf_2_bytes_count);
  if (buf_3_id) glTransformFeedbackBufferRange(xfb_id, 3, buf_3_id, buf_3_bytes_first, buf_3_bytes_count);
  profE(__func__);
  return xfb_id;
}

static inline void GpuBindFbo(unsigned fbo_id) {
  profB(__func__);
  glBindFramebuffer(0x8D40, fbo_id); // GL_FRAMEBUFFER
  profE(__func__);
}

static inline void GpuBindXfb(unsigned xfb_id) {
  profB(__func__);
  glBindTransformFeedback(0x8E22, xfb_id); // GL_TRANSFORM_FEEDBACK
  profE(__func__);
}

static inline void GpuBindIndices(unsigned idb_id) {
  profB(__func__);
  glBindBuffer(0x8893, idb_id); // GL_ELEMENT_ARRAY_BUFFER
  profE(__func__);
}

static inline void GpuBindCommands(unsigned dib_id) {
  profB(__func__);
  glBindBuffer(0x8F3F, dib_id); // GL_DRAW_INDIRECT_BUFFER
  profE(__func__);
}

static inline void GpuBindTextures(int first, int count, unsigned * textures) {
  profB(__func__);
  glBindTextures(first, count, textures);
  profE(__func__);
}

static inline void GpuBindSamplers(int first, int count, unsigned * samplers) {
  profB(__func__);
  glBindSamplers(first, count, samplers);
  profE(__func__);
}

static inline void GpuBindPpo(unsigned ppo) {
  profB(__func__);
  glBindProgramPipeline(ppo);
  profE(__func__);
}

static inline void GpuDraw(enum gpu_mode_e mode, unsigned binded_dib_cmd_first, unsigned binded_dib_cmd_count) {
  profB(__func__);
  glMultiDrawElementsIndirect(mode, 0x1405, (void *)(binded_dib_cmd_first * 5 * sizeof(unsigned)), binded_dib_cmd_count, 0); // GL_UNSIGNED_INT
  profE(__func__);
}

static inline void GpuDrawXfb(enum gpu_mode_e mode, unsigned binded_dib_cmd_first, unsigned binded_dib_cmd_count) {
  profB(__func__);
  glEnable(0x8C89); // GL_RASTERIZER_DISCARD
  glBeginTransformFeedback(mode);
  glMultiDrawElementsIndirect(mode, 0x1405, (void *)(binded_dib_cmd_first * 5 * sizeof(unsigned)), binded_dib_cmd_count, 0); // GL_UNSIGNED_INT
  glEndTransformFeedback();
  glDisable(0x8C89);
  profE(__func__);
}

static inline void GpuDrawOnce(enum gpu_mode_e mode, unsigned first, unsigned count, unsigned instance_count) {
  profB(__func__);
  glDrawArraysInstanced(mode, first, count, instance_count);
  profE(__func__);
}

static inline void GpuDrawOnceXfb(enum gpu_mode_e mode, unsigned first, unsigned count, unsigned instance_count) {
  profB(__func__);
  glEnable(0x8C89); // GL_RASTERIZER_DISCARD
  glBeginTransformFeedback(mode);
  glDrawArraysInstanced(mode, first, count, instance_count);
  glEndTransformFeedback();
  glDisable(0x8C89);
  profE(__func__);
}

static inline void GpuBlit(
    unsigned source_fbo_id, int source_color_id, int source_x, int source_y, int source_width, int source_height,
    unsigned target_fbo_id, int target_color_id, int target_x, int target_y, int target_width, int target_height)
{
  profB(__func__);
  glNamedFramebufferReadBuffer(source_fbo_id, 0x8CE0 + source_color_id); // GL_COLOR_ATTACHMENT0
  glNamedFramebufferDrawBuffer(target_fbo_id, 0x8CE0 + target_color_id);
  glBlitNamedFramebuffer(
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
  glNamedFramebufferReadBuffer(source_fbo_id, 0x8CE0 + source_color_id); // GL_COLOR_ATTACHMENT0
  glNamedFramebufferDrawBuffer(0, 0x0405); // GL_BACK
  glBlitNamedFramebuffer(
      source_fbo_id, 0,
      source_x, source_y, source_width, source_height,
      screen_x, screen_y, screen_width, screen_height, 0x00004000, 0x2600); // GL_COLOR_BUFFER_BIT, GL_NEAREST
  profE(__func__);
}

static inline void GpuClear() {
  profB(__func__);
  glClear(0x4100); // GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT
  profE(__func__);
}

static inline void GpuFinish() {
  profB(__func__);
  glFinish();
  profE(__func__);
}

static inline void GpuSwap(Display * dpy, Window win) {
  profB(__func__);
  glXSwapBuffers(dpy, win);
  profE(__func__);
  GpuFinish();
}

static inline void GpuEnable(unsigned flags) {
  profB(__func__);
  glEnable(flags);
  profE(__func__);
}

static inline void GpuDisable(unsigned flags) {
  profB(__func__);
  glDisable(flags);
  profE(__func__);
}

static inline void GpuViewport(int x, int y, int width, int height) {
  profB(__func__);
  glViewport(x, y, width, height);
  profE(__func__);
}

static inline void GpuSetDebugCallback(void * callback) {
  profB(__func__);
  glDebugMessageCallback(callback, NULL);
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

#pragma once

#include "gpulib.h"
#include "gpulib_imgui.h"

#ifndef GPULIB_DEBUG_MANUAL

#define GpuWindow(window_title, window_width, window_height, msaa_samples, out_scancodes, out_dpy, out_win) do { \
  char * __out_scancodes = out_scancodes;                                                                        \
  char __scancodes_temp[256 * 5] = {0};                                                                          \
  char * __scancodes = __out_scancodes != NULL ? __out_scancodes : __scancodes_temp;                             \
  GpuWindow(window_title, window_width, window_height, msaa_samples, __scancodes, out_dpy, out_win);             \
  ImguiInit(dpy, win, __scancodes);                                                                              \
  ImguiNewFrame();                                                                                               \
} while(0)

#define XNextEvent(dpy, event) do {                                              \
  XEvent * __event = event;                                                      \
  XNextEvent(dpy, __event);                                                      \
  ImguiProcessEvent(__event);                                                    \
  switch (__event->type) {                                                       \
    break; case ClientMessage: {                                                 \
      if (__event->xclient.data.l[0] == XInternAtom(dpy, "WM_DELETE_WINDOW", 0)) \
        ImguiDeinit();                                                           \
    }                                                                            \
  }                                                                              \
} while(0)

#define GpuSwap(dpy, win) do { \
  igRender();                  \
  GpuSwap(dpy, win);           \
  ImguiNewFrame();             \
} while(0)

#endif // #ifndef GPULIB_DEBUG_MANUAL

static char *   g_gpulib_debug_program_string   = NULL;
static unsigned g_gpulib_debug_program_type     = 0;
static unsigned g_gpulib_debug_program_id       = 0;
static bool     g_gpulib_debug_program_compiled = 0;

static inline int GpuDebugProgramCallback(struct ImGuiTextEditCallbackData * data) {
  glDeleteProgram(g_gpulib_debug_program_id);
  if (g_gpulib_debug_program_type == 0x8B31) { // GL_VERTEX_SHADER
    g_gpulib_debug_program_id = GpuVert(g_gpulib_debug_program_string);
  } else if (g_gpulib_debug_program_type == 0x8B30) { // GL_FRAGMENT_SHADER
    g_gpulib_debug_program_id = GpuFrag(g_gpulib_debug_program_string);
  } else {
    assert(0);
  }
  g_gpulib_debug_program_compiled = 1;
  return 0;
}

static inline int GpuDebugProgramEx(unsigned program_type, unsigned * program_id, char * string, size_t string_bytes, char * name) {
  if (g_gpulib_debug_program_compiled == 1)
      g_gpulib_debug_program_compiled  = 0;

  igSetNextWindowSize((struct ImVec2){640, 360}, (1 << 2)); // ImGuiSetCond_FirstUseEver
  static bool g_gpulib_is_debug_program_window_open = 1;
  igBegin(name, &g_gpulib_is_debug_program_window_open, (1 << 11)); // ImGuiWindowFlags_HorizontalScrollbar
  static bool g_gpulib_compile_on_tab = 0;
  igCheckbox("Compile on Tab", &g_gpulib_compile_on_tab);

  g_gpulib_debug_program_string = string;
  g_gpulib_debug_program_type   = program_type;
  g_gpulib_debug_program_id     = program_id[0];
  igInputTextMultiline("", string, string_bytes, (struct ImVec2){-1, -1},
                       g_gpulib_compile_on_tab ? (1 << 6) : (1 << 8), // ImGuiInputTextFlags_CallbackCompletion, ImGuiInputTextFlags_CallbackAlways
                       GpuDebugProgramCallback, NULL);
  program_id[0] = g_gpulib_debug_program_id;

  igEnd();
  return g_gpulib_debug_program_compiled;
}

static inline void GpuDebugImgEx(unsigned tex_id, char * name) {
  void (*glGetTextureLevelParameteriv)(unsigned, int, unsigned, int *) = (void *)glXGetProcAddressARB((unsigned char *)"glGetTextureLevelParameteriv");

  static unsigned g_gpulib_debug_texture = 0;
  if (g_gpulib_debug_texture != 0) {
    glDeleteTextures(1, &g_gpulib_debug_texture);
    g_gpulib_debug_texture = 0;
  }
  g_gpulib_debug_texture = tex_id;

  int w = 0, h = 0, layer_count = 0, format = 0;
  glGetTextureLevelParameteriv(g_gpulib_debug_texture, 0, 0x1000, &w); // GL_TEXTURE_WIDTH
  glGetTextureLevelParameteriv(g_gpulib_debug_texture, 0, 0x1001, &h); // GL_TEXTURE_HEIGHT
  glGetTextureLevelParameteriv(g_gpulib_debug_texture, 0, 0x8071, &layer_count); // GL_TEXTURE_DEPTH
  glGetTextureLevelParameteriv(g_gpulib_debug_texture, 0, 0x1003, &format); // GL_TEXTURE_INTERNAL_FORMAT

  igSetNextWindowSize((struct ImVec2){640, 360}, (1 << 2)); // ImGuiSetCond_FirstUseEver
  static bool g_gpulib_is_debug_texture_window_open = 1;
  igBegin(name, &g_gpulib_is_debug_texture_window_open, (1 << 11)); // ImGuiWindowFlags_HorizontalScrollbar
  igPushStyleVarVec(7, (struct ImVec2){6, 6}); // ImGuiStyleVar_ItemSpacing

  igText("Inspect pixel:");

  int max_mipmap_count = w != h ? 1 : (int)log2(w) + 1;

  static int g_gpulib_mipmap_level = 0;
  {
    igSliderInt("mipmap_level", &g_gpulib_mipmap_level, 0, max_mipmap_count - 1, NULL);
    if (g_gpulib_mipmap_level < 0) g_gpulib_mipmap_level = 0;
    if (g_gpulib_mipmap_level > max_mipmap_count - 1) g_gpulib_mipmap_level = max_mipmap_count - 1;
    igSameLine(0, 0);
    igTextDisabled(" (?)");
    if (igIsItemHovered()) {
      igBeginTooltip();
      igTextUnformatted("Ctrl + Click for manual input", "");
      igEndTooltip();
    }
  }

  static int g_gpulib_layer = 0;
  {
    igSliderInt("layer", &g_gpulib_layer, 0, layer_count - 1, NULL);
    if (g_gpulib_layer < 0) g_gpulib_layer = 0;
    if (g_gpulib_layer > layer_count - 1) g_gpulib_layer = layer_count - 1;
  }

  static int g_gpulib_x = 0;
  {
    int W = w / pow(2, g_gpulib_mipmap_level);
    igSliderInt("x", &g_gpulib_x, 0, W - 1, NULL);
    if (g_gpulib_x < 0) g_gpulib_x = 0;
    if (g_gpulib_x > W - 1) g_gpulib_x = W - 1;
  }

  static int g_gpulib_y = 0;
  {
    int H = h / pow(2, g_gpulib_mipmap_level);
    igSliderInt("y", &g_gpulib_y, 0, H - 1, NULL);
    if (g_gpulib_y < 0) g_gpulib_y = 0;
    if (g_gpulib_y > H - 1) g_gpulib_y = H - 1;
  }

  static bool g_gpulib_sync_pos = 1;
  igCheckbox("Sync pos transform", &g_gpulib_sync_pos);

  g_gpulib_debug_texture = GpuCastImg(tex_id, (enum gpu_tex_format_e)format, g_gpulib_layer, 1, g_gpulib_mipmap_level, 1);

  {
    int is_srgb = 0;
    unsigned e_count = 0, e_type = 0;
    switch (format) {
      break; case 0x8CAC: { is_srgb = 0; e_count = 0x1902; e_type = 0x1406; } // GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_FLOAT
      break; case 0x8051: { is_srgb = 0; e_count = 0x1907; e_type = 0x1400; } // GL_RGB8, GL_RGB, GL_BYTE
      break; case 0x8058: { is_srgb = 0; e_count = 0x1908; e_type = 0x1400; } // GL_RGBA8, GL_RGBA, GL_BYTE
      break; case 0x8C41: { is_srgb = 1; e_count = 0x1907; e_type = 0x1400; } // GL_SRGB8, GL_RGB, GL_BYTE
      break; case 0x8C43: { is_srgb = 1; e_count = 0x1908; e_type = 0x1400; } // GL_SRGB8_ALPHA8, GL_RGBA, GL_BYTE
      break; case 0x8814: { is_srgb = 0; e_count = 0x1908; e_type = 0x1406; } // GL_RGBA32F, GL_RGBA, GL_FLOAT
      break; default: { assert(0); }
    }
    if (e_type == 0x1406) { // GL_FLOAT
      if (e_count == 0x1902) { // GL_DEPTH_COMPONENT
        float pix[1] = {0};
        GpuGet(g_gpulib_debug_texture, 0, g_gpulib_x, g_gpulib_y, 1, 1, 1, 0, e_count, e_type, sizeof(pix), pix);
        igText("Pixel output: r: %.7f", pix[0]);
      } else if (e_count == 0x1908) { // GL_RGBA
        float pix[4] = {0};
        GpuGet(g_gpulib_debug_texture, 0, g_gpulib_x, g_gpulib_y, 1, 1, 1, 0, e_count, e_type, sizeof(pix), pix);
        igText("Pixel output: r: %.7f, g: %.7f, b: %.7f, a: %.7f", pix[0], pix[1], pix[2], pix[3]);
      } else {
        assert(0);
      }
    } else if (e_type == 0x1400) { // GL_BYTE
      if (e_count == 0x1907) { // GL_RGB
        unsigned char pix[3] = {0};
        GpuGet(g_gpulib_debug_texture, 0, g_gpulib_x, g_gpulib_y, 1, 1, 1, 0, e_count, e_type, sizeof(pix), pix);
        igText("Pixel output: r: %u, g: %u, b: %u", pix[0], pix[1], pix[2]);
      } else if (e_count == 0x1908) { // GL_RGBA
        unsigned char pix[4] = {0};
        GpuGet(g_gpulib_debug_texture, 0, g_gpulib_x, g_gpulib_y, 1, 1, 1, 0, e_count, e_type, sizeof(pix), pix);
        igText("Pixel output: r: %u, g: %u, b: %u, a: %u", pix[0], pix[1], pix[2], pix[3]);
      } else {
        assert(0);
      }
    } else {
      assert(0);
    }
  }

  igSeparator();
  igText("Texture transforms:");

  static float scale[2] = {1, 1};
  static int pos[2] = {0, 0};
  igDragFloat2("scale", scale, 0.001, 0, 0, NULL, 1);
  igDragInt2("pos", pos, 1, 0, 0, NULL);
  igText("Texture info: w: %d, h: %d, layer_count: %d, max_mipmap_count: %d", w, h, layer_count, max_mipmap_count);

  if (g_gpulib_sync_pos) {
    pos[0] = g_gpulib_x;
    pos[1] = g_gpulib_y;
  }

  igImage((ImTextureID)&g_gpulib_debug_texture,
          (struct ImVec2){w, h},
          (struct ImVec2){((float)pos[0] / w),
                          ((float)pos[1] / h)},
          (struct ImVec2){((float)pos[0] / w) + scale[0],
                          ((float)pos[1] / h) + scale[1]},
          (struct ImVec4){255, 255, 255, 255},
          (struct ImVec4){0, 0, 0, 0});

  igPopStyleVar(1);
  igEnd();
}

static inline void GpuDebugU32Ex(unsigned program, int location, int count, unsigned * value, char * value_name) {
  igDragInt(value_name, (int *)value, 1, 0, 0, NULL);
  GpuU32(program, location, count, value);
}

static inline void GpuDebugI32Ex(unsigned program, int location, int count, int * value, char * value_name) {
  igDragInt(value_name, value, 1, 0, 0, NULL);
  GpuI32(program, location, count, value);
}

static inline void GpuDebugF32Ex(unsigned program, int location, int count, float * value, char * value_name) {
  igDragFloat(value_name, value, 0.001, 0, 0, NULL, 1);
  GpuF32(program, location, count, value);
}

static inline void GpuDebugV2FEx(unsigned program, int location, int count, float * value, char * value_name) {
  igDragFloat2(value_name, value, 0.001, 0, 0, NULL, 1);
  GpuV2F(program, location, count, value);
}

static inline void GpuDebugV3FEx(unsigned program, int location, int count, float * value, char * value_name) {
  igDragFloat3(value_name, value, 0.001, 0, 0, NULL, 1);
  GpuV3F(program, location, count, value);
}

static inline void GpuDebugV4FEx(unsigned program, int location, int count, float * value, char * value_name) {
  igDragFloat4(value_name, value, 0.001, 0, 0, NULL, 1);
  GpuV4F(program, location, count, value);
}

#define GpuDebugVert(program_id, string, string_bytes) GpuDebugProgramEx(0x8B31, program_id, string, string_bytes, #program_id) // GL_VERTEX_SHADER
#define GpuDebugFrag(program_id, string, string_bytes) GpuDebugProgramEx(0x8B30, program_id, string, string_bytes, #program_id) // GL_FRAGMENT_SHADER
#define GpuDebugImg(tex_id) GpuDebugImgEx(tex_id, #tex_id)
#define GpuDebugU32(program, location, count, value) GpuDebugU32Ex(program, location, count, value, #value)
#define GpuDebugI32(program, location, count, value) GpuDebugI32Ex(program, location, count, value, #value)
#define GpuDebugF32(program, location, count, value) GpuDebugF32Ex(program, location, count, value, #value)
#define GpuDebugV2F(program, location, count, value) GpuDebugV2FEx(program, location, count, value, #value)
#define GpuDebugV3F(program, location, count, value) GpuDebugV3FEx(program, location, count, value, #value)
#define GpuDebugV4F(program, location, count, value) GpuDebugV4FEx(program, location, count, value, #value)

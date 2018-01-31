#pragma once

#include "gpulib.h"
#include "gpulib_x11_wsi.h"
#include "gpulib_x11_imgui.h"

#ifndef GPULIB_DEBUG_MANUAL

#define GpuWsiWindow(window_title, window_title_bytes, window_width, window_height, msaa_samples, out_scancodes, out_dpy, out_win) do { \
  char * __out_scancodes = out_scancodes;                                                                                               \
  char __scancodes_temp[256 * 5] = {0};                                                                                                 \
  char * __scancodes = __out_scancodes != NULL ? __out_scancodes : __scancodes_temp;                                                    \
  GpuWsiWindow(window_title, window_title_bytes, window_width, window_height, msaa_samples, __scancodes, out_dpy, out_win);             \
  ImguiInit(dpy, win, __scancodes);                                                                                                     \
  ImguiNewFrame();                                                                                                                      \
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

#define GpuWsiSwap(dpy, win) do { \
  igRender();                     \
  GpuWsiSwap(dpy, win);           \
  ImguiNewFrame();                \
} while(0)

#endif // #ifndef GPULIB_DEBUG_MANUAL

struct gpu_debug_state_t {
  float    texture_scale[2];
  int      texture_pos[2];
  char *   program_string;
  unsigned program_type;
  unsigned program_id;
  unsigned texture_id;
  int      texture_mipmap_level;
  int      texture_layer;
  int      texture_x;
  int      texture_y;
  bool     program_compiled;
  bool     program_compile_on_tab;
  bool     texture_sync_pos;
} g_gpulib_debug_state_data = {
  .texture_scale = {1, 1},
  .texture_sync_pos = 1,
};

struct gpu_debug_state_t * g_gpulib_debug_state = &g_gpulib_debug_state_data;

static inline int GpuDebugProgramCallback(struct ImGuiTextEditCallbackData * data) {
  __auto_type gl = g_gpulib_libgl;
  __auto_type state = g_gpulib_debug_state;
  
  gl->DeleteProgram(state->program_id);
  if (state->program_type == 0x8B31) { // GL_VERTEX_SHADER
    state->program_id = GpuProgramVertex(state->program_string);
  } else if (state->program_type == 0x8B30) { // GL_FRAGMENT_SHADER
    state->program_id = GpuProgramFragment(state->program_string);
  } else {
    stdlib_assert(0);
  }
  state->program_compiled = 1;
  return 0;
}

static inline int GpuDebugProgramEx(unsigned program_type, unsigned * program_id, char * string, size_t string_bytes, char * name) {
  __auto_type state = g_gpulib_debug_state;

  if (state->program_compiled == 1)
      state->program_compiled  = 0;

  igSetNextWindowSize((struct ImVec2){640, 360}, (1 << 2)); // ImGuiSetCond_FirstUseEver
  igBegin(name, NULL, (1 << 11)); // ImGuiWindowFlags_HorizontalScrollbar
  igCheckbox("Compile on Tab", &state->program_compile_on_tab);

  state->program_string = string;
  state->program_type   = program_type;
  state->program_id     = program_id[0];
  igInputTextMultiline("", string, string_bytes, (struct ImVec2){-1, -1},
                       state->program_compile_on_tab ? (1 << 6) : (1 << 8), // ImGuiInputTextFlags_CallbackCompletion, ImGuiInputTextFlags_CallbackAlways
                       GpuDebugProgramCallback, NULL);
  program_id[0] = state->program_id;

  igEnd();
  return state->program_compiled;
}

static inline void GpuDebugImageEx(unsigned tex_id, char * name) {
  __auto_type gl = g_gpulib_libgl;
  __auto_type state = g_gpulib_debug_state;
  
  if (state->texture_id != 0) {
    gl->DeleteTextures(1, &state->texture_id);
    state->texture_id = 0;
  }
  state->texture_id = tex_id;

  int w = 0, h = 0, layer_count = 0, format = 0;
  gl->GetTextureLevelParameteriv(state->texture_id, 0, 0x1000, &w); // GL_TEXTURE_WIDTH
  gl->GetTextureLevelParameteriv(state->texture_id, 0, 0x1001, &h); // GL_TEXTURE_HEIGHT
  gl->GetTextureLevelParameteriv(state->texture_id, 0, 0x8071, &layer_count); // GL_TEXTURE_DEPTH
  gl->GetTextureLevelParameteriv(state->texture_id, 0, 0x1003, &format); // GL_TEXTURE_INTERNAL_FORMAT

  igSetNextWindowSize((struct ImVec2){640, 360}, (1 << 2)); // ImGuiSetCond_FirstUseEver
  igBegin(name, NULL, (1 << 11)); // ImGuiWindowFlags_HorizontalScrollbar
  igPushStyleVarVec(7, (struct ImVec2){6, 6}); // ImGuiStyleVar_ItemSpacing

  igText("Inspect pixel:");

  int max_mipmap_count = w != h ? 1 : stdlib_log2i(w) + 1;

  {
    igSliderInt("mipmap_level", &state->texture_mipmap_level, 0, max_mipmap_count - 1, NULL);
    if (state->texture_mipmap_level < 0) state->texture_mipmap_level = 0;
    if (state->texture_mipmap_level > max_mipmap_count - 1) state->texture_mipmap_level = max_mipmap_count - 1;
    igSameLine(0, 0);
    igTextDisabled(" (?)");
    if (igIsItemHovered()) {
      igBeginTooltip();
      igTextUnformatted("Ctrl + Click for manual input", "");
      igEndTooltip();
    }
  }

  {
    igSliderInt("layer", &state->texture_layer, 0, layer_count - 1, NULL);
    if (state->texture_layer < 0) state->texture_layer = 0;
    if (state->texture_layer > layer_count - 1) state->texture_layer = layer_count - 1;
  }

  {
    int W = w / (1 << state->texture_mipmap_level);
    igSliderInt("x", &state->texture_x, 0, W - 1, NULL);
    if (state->texture_x < 0) state->texture_x = 0;
    if (state->texture_x > W - 1) state->texture_x = W - 1;
  }

  {
    int H = h / (1 << state->texture_mipmap_level);
    igSliderInt("y", &state->texture_y, 0, H - 1, NULL);
    if (state->texture_y < 0) state->texture_y = 0;
    if (state->texture_y > H - 1) state->texture_y = H - 1;
  }

  igCheckbox("Sync pos transform", &state->texture_sync_pos);

  state->texture_id = GpuViewImage(tex_id, (enum gpu_texture_format_e)format, state->texture_layer, 1, state->texture_mipmap_level, 1);

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
      break; default: { stdlib_assert(0); }
    }
    if (e_type == 0x1406) { // GL_FLOAT
      if (e_count == 0x1902) { // GL_DEPTH_COMPONENT
        float pix[1] = {0};
        gl->GetTextureSubImage(state->texture_id, 0, state->texture_x, state->texture_y, 0, 1, 1, 1, e_count, e_type, sizeof(pix), pix);
        igText("Pixel output: r: %.7f", pix[0]);
      } else if (e_count == 0x1908) { // GL_RGBA
        float pix[4] = {0};
        gl->GetTextureSubImage(state->texture_id, 0, state->texture_x, state->texture_y, 0, 1, 1, 1, e_count, e_type, sizeof(pix), pix);
        igText("Pixel output: r: %.7f, g: %.7f, b: %.7f, a: %.7f", pix[0], pix[1], pix[2], pix[3]);
      } else {
        stdlib_assert(0);
      }
    } else if (e_type == 0x1400) { // GL_BYTE
      if (e_count == 0x1907) { // GL_RGB
        unsigned char pix[3] = {0};
        gl->GetTextureSubImage(state->texture_id, 0, state->texture_x, state->texture_y, 0, 1, 1, 1, e_count, e_type, sizeof(pix), pix);
        igText("Pixel output: r: %u, g: %u, b: %u", pix[0], pix[1], pix[2]);
      } else if (e_count == 0x1908) { // GL_RGBA
        unsigned char pix[4] = {0};
        gl->GetTextureSubImage(state->texture_id, 0, state->texture_x, state->texture_y, 0, 1, 1, 1, e_count, e_type, sizeof(pix), pix);
        igText("Pixel output: r: %u, g: %u, b: %u, a: %u", pix[0], pix[1], pix[2], pix[3]);
      } else {
        stdlib_assert(0);
      }
    } else {
      stdlib_assert(0);
    }
  }

  igSeparator();
  igText("Texture transforms:");

  igDragFloat2("scale", state->texture_scale, 0.001, 0, 0, NULL, 1);
  igDragInt2("pos", state->texture_pos, 1, 0, 0, NULL);
  igText("Texture info: w: %d, h: %d, layer_count: %d, max_mipmap_count: %d", w, h, layer_count, max_mipmap_count);

  if (state->texture_sync_pos) {
    state->texture_pos[0] = state->texture_x;
    state->texture_pos[1] = state->texture_y;
  }

  igImage((ImTextureID)&state->texture_id,
          (struct ImVec2){w, h},
          (struct ImVec2){((float)state->texture_pos[0] / w),
                          ((float)state->texture_pos[1] / h)},
          (struct ImVec2){((float)state->texture_pos[0] / w) + state->texture_scale[0],
                          ((float)state->texture_pos[1] / h) + state->texture_scale[1]},
          (struct ImVec4){255, 255, 255, 255},
          (struct ImVec4){0, 0, 0, 0});

  igPopStyleVar(1);
  igEnd();
}

static inline void GpuDebugUniformIntEx(unsigned program, int location, int count, int * value, char * value_name) {
  igDragInt(value_name, value, 1, 0, 0, NULL);
  GpuUniformInt(program, location, count, value);
}

static inline void GpuDebugUniformFloat4Ex(unsigned program, int location, int count, float * value, char * value_name) {
  igDragFloat4(value_name, value, 0.001, 0, 0, NULL, 1);
  GpuUniformFloat4(program, location, count, value);
}

#define GpuDebugProgramVertex(program_id, string, string_bytes) GpuDebugProgramEx(0x8B31, program_id, string, string_bytes, #program_id) // GL_VERTEX_SHADER
#define GpuDebugProgramFragment(program_id, string, string_bytes) GpuDebugProgramEx(0x8B30, program_id, string, string_bytes, #program_id) // GL_FRAGMENT_SHADER
#define GpuDebugProgramCompute(program_id, string, string_bytes) GpuDebugProgramEx(0x91B9, program_id, string, string_bytes, #program_id) // GL_COMPUTE_SHADER
#define GpuDebugImage(tex_id) GpuDebugImageEx(tex_id, #tex_id)
#define GpuDebugUniformInt(program, location, count, value) GpuDebugUniformIntEx(program, location, count, value, #value)
#define GpuDebugUniformFloat4(program, location, count, value) GpuDebugUniformFloat4Ex(program, location, count, value, #value)

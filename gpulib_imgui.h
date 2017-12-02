#pragma once

#include "imgui/cimgui.h"

struct ImVec2 {
  float x, y;
};

struct ImVec3 {
  float x, y, z;
};

struct ImVec4 {
  float x, y, z, w;
};

struct ImGuiIO {
  struct ImVec2 DisplaySize;
  float DeltaTime;
  float IniSavingRate;
  char * IniFilename;
  char * LogFilename;
  float MouseDoubleClickTime;
  float MouseDoubleClickMaxDist;
  float MouseDragThreshold;
  int KeyMap[19];
  float KeyRepeatDelay;
  float KeyRepeatRate;
  void * UserData;
  struct ImFontAtlas * Fonts;
  float FontGlobalScale;
  bool FontAllowUserScaling;
  struct ImVec2 DisplayFramebufferScale;
  struct ImVec2 DisplayVisibleMin;
  struct ImVec2 DisplayVisibleMax;
  bool OSXBehaviors;
  void (*RenderDrawListsFn)(struct ImDrawData * data);
  char * (*GetClipboardTextFn)();
  void (*SetClipboardTextFn)(char * text);
  void * (*MemAllocFn)(size_t sz);
  void (*MemFreeFn)(void * ptr);
  void (*ImeSetInputScreenPosFn)(int x, int y);
  void * ImeWindowHandle;
  struct ImVec2 MousePos;
  bool MouseDown[5];
  float MouseWheel;
  bool MouseDrawCursor;
  bool KeyCtrl;
  bool KeyShift;
  bool KeyAlt;
  bool KeySuper;
  bool KeysDown[512];
  unsigned short InputCharacters[17];
  bool WantCaptureMouse;
  bool WantCaptureKeyboard;
  bool WantTextInput;
  float Framerate;
  int MetricsAllocs;
  int MetricsRenderVertices;
  int MetricsRenderIndices;
  int MetricsActiveWindows;
  struct ImVec2 MousePosPrev;
  struct ImVec2 MouseDelta;
  bool MouseClicked[5];
  struct ImVec2 MouseClickedPos[5];
  float MouseClickedTime[5];
  bool MouseDoubleClicked[5];
  bool MouseReleased[5];
  bool MouseDownOwned[5];
  float MouseDownDuration[5];
  float MouseDownDurationPrev[5];
  float MouseDragMaxDistanceSqr[5];
  float KeysDownDuration[512];
  float KeysDownDurationPrev[512];
};

struct ImDrawData {
  bool Valid;
  struct ImDrawList ** CmdLists;
  int CmdListsCount;
  int TotalVtxCount;
  int TotalIdxCount;
};

struct ImDrawCmd {
  int ElemCount;
  struct ImVec4 ClipRect;
  ImTextureID TextureId;
  ImDrawCallback UserCallback;
  void * UserCallbackData;
};

typedef struct {
  struct ImVec2 pos;
  struct ImVec2 uv;
  unsigned col;
} ImDrawVtx;

enum ImGuiKey {
  ImGuiKey_Tab,
  ImGuiKey_LeftArrow,
  ImGuiKey_RightArrow,
  ImGuiKey_UpArrow,
  ImGuiKey_DownArrow,
  ImGuiKey_PageUp,
  ImGuiKey_PageDown,
  ImGuiKey_Home,
  ImGuiKey_End,
  ImGuiKey_Delete,
  ImGuiKey_Backspace,
  ImGuiKey_Enter,
  ImGuiKey_Escape,
  ImGuiKey_A,
  ImGuiKey_C,
  ImGuiKey_V,
  ImGuiKey_X,
  ImGuiKey_Y,
  ImGuiKey_Z,
  ImGuiKey_COUNT
};

enum ImGuiCol {
  ImGuiCol_Text,
  ImGuiCol_TextDisabled,
  ImGuiCol_WindowBg,
  ImGuiCol_ChildWindowBg,
  ImGuiCol_PopupBg,
  ImGuiCol_Border,
  ImGuiCol_BorderShadow,
  ImGuiCol_FrameBg,
  ImGuiCol_FrameBgHovered,
  ImGuiCol_FrameBgActive,
  ImGuiCol_TitleBg,
  ImGuiCol_TitleBgCollapsed,
  ImGuiCol_TitleBgActive,
  ImGuiCol_MenuBarBg,
  ImGuiCol_ScrollbarBg,
  ImGuiCol_ScrollbarGrab,
  ImGuiCol_ScrollbarGrabHovered,
  ImGuiCol_ScrollbarGrabActive,
  ImGuiCol_ComboBg,
  ImGuiCol_CheckMark,
  ImGuiCol_SliderGrab,
  ImGuiCol_SliderGrabActive,
  ImGuiCol_Button,
  ImGuiCol_ButtonHovered,
  ImGuiCol_ButtonActive,
  ImGuiCol_Header,
  ImGuiCol_HeaderHovered,
  ImGuiCol_HeaderActive,
  ImGuiCol_Column,
  ImGuiCol_ColumnHovered,
  ImGuiCol_ColumnActive,
  ImGuiCol_ResizeGrip,
  ImGuiCol_ResizeGripHovered,
  ImGuiCol_ResizeGripActive,
  ImGuiCol_CloseButton,
  ImGuiCol_CloseButtonHovered,
  ImGuiCol_CloseButtonActive,
  ImGuiCol_PlotLines,
  ImGuiCol_PlotLinesHovered,
  ImGuiCol_PlotHistogram,
  ImGuiCol_PlotHistogramHovered,
  ImGuiCol_TextSelectedBg,
  ImGuiCol_ModalWindowDarkening,
  ImGuiCol_COUNT
};

struct ImGuiStyle {
  float Alpha;
  struct ImVec2 WindowPadding;
  struct ImVec2 WindowMinSize;
  float WindowRounding;
  struct ImVec2 WindowTitleAlign;
  float ChildWindowRounding;
  struct ImVec2 FramePadding;
  float FrameRounding;
  struct ImVec2 ItemSpacing;
  struct ImVec2 ItemInnerSpacing;
  struct ImVec2 TouchExtraPadding;
  float IndentSpacing;
  float ColumnsMinSpacing;
  float ScrollbarSize;
  float ScrollbarRounding;
  float GrabMinSize;
  float GrabRounding;
  struct ImVec2 ButtonTextAlign;
  struct ImVec2 DisplayWindowPadding;
  struct ImVec2 DisplaySafeAreaPadding;
  bool AntiAliasedLines;
  bool AntiAliasedShapes;
  float CurveTessellationTol;
  struct ImVec4 Colors[43];
};

struct ig_state_t {
  double    time;
  float     mouse_wheel;
  unsigned  font_texture;
  unsigned  ppo;
  unsigned  vert;
  unsigned  frag;
  Display * dpy;
  Window    win;
  char    * clipboard_copy;
  char    * clipboard_paste;
  unsigned  clipboard_paste_sleep_microseconds;
} g_ig_state_data = {
  .clipboard_paste_sleep_microseconds = 100000, // 1/10 of a second
};

struct ig_state_t * g_ig_state = &g_ig_state_data;

void ImguiRenderDrawList(struct ImDrawData * draw_data) {
  struct ImGuiIO * io = igGetIO();

  struct ImVec2 fb_scale = io->DisplayFramebufferScale;
  int w = (int)(io->DisplaySize.x * fb_scale.x);
  int h = (int)(io->DisplaySize.y * fb_scale.y);

  ImDrawData_ScaleClipRects(draw_data, fb_scale);
  glViewport(0, 0, w, h);

  glDisable(0x0B44); // GL_CULL_FACE
  glDisable(0x0B71); // GL_DEPTH_TEST
  glEnable(0x0C11);  // GL_SCISSOR_TEST
  glDisable(0x8DB9); // GL_FRAMEBUFFER_SRGB

  float scale[2] = {0}, translate[2] = {0};
  scale[0] = 2.f /  w;
  scale[1] = 2.f / -h;
  translate[0] = -1.0;
  translate[1] =  1.0;
  glProgramUniform2fv(g_ig_state->vert, 0, 1, scale);
  glProgramUniform2fv(g_ig_state->vert, 1, 1, translate);
  glBindProgramPipeline(g_ig_state->ppo);

  ptrdiff_t id_bytes = draw_data->TotalIdxCount * (ptrdiff_t)sizeof(ImDrawIdx);
  ptrdiff_t vt_bytes = draw_data->TotalVtxCount * (ptrdiff_t)sizeof(ImDrawVtx);

  unsigned id_mem_id = 0;
  unsigned vt_mem_id = 0;
  glCreateBuffers(1, &id_mem_id);
  glCreateBuffers(1, &vt_mem_id);
  glNamedBufferStorage(id_mem_id, id_bytes, 0, 194);
  glNamedBufferStorage(vt_mem_id, vt_bytes, 0, 194);
  void * id = glMapNamedBufferRange(id_mem_id, 0, id_bytes, 194);
  void * vt = glMapNamedBufferRange(vt_mem_id, 0, vt_bytes, 194);
  unsigned id_tex_id = 0;
  unsigned vt_f32_tex_id = 0;
  unsigned vt_u32_tex_id = 0;
  glCreateTextures(0x8C2A, 1, &id_tex_id); // GL_TEXTURE_BUFFER
  glCreateTextures(0x8C2A, 1, &vt_f32_tex_id);
  glCreateTextures(0x8C2A, 1, &vt_u32_tex_id);
  glTextureBufferRange(id_tex_id, 0x8234, id_mem_id, 0, id_bytes); // GL_R16UI
  glTextureBufferRange(vt_f32_tex_id, 0x822E, vt_mem_id, 0, vt_bytes); // GL_R32F
  glTextureBufferRange(vt_u32_tex_id, 0x8236, vt_mem_id, 0, vt_bytes); // GL_R32UI

  ImDrawIdx * id_dest = id;
  ImDrawVtx * vt_dest = vt;
  for (ptrdiff_t i = 0, c = draw_data->CmdListsCount; i < c; i += 1) {
    struct ImDrawList * cmd_list = draw_data->CmdLists[i];
    int id_size = ImDrawList_GetIndexBufferSize(cmd_list);
    int vt_size = ImDrawList_GetVertexBufferSize(cmd_list);
    memcpy(id_dest, ImDrawList_GetIndexPtr(cmd_list, 0), (size_t)id_size * sizeof(ImDrawIdx));
    memcpy(vt_dest, ImDrawList_GetVertexPtr(cmd_list, 0), (size_t)vt_size * sizeof(ImDrawVtx));
    id_dest += id_size;
    vt_dest += vt_size;
  }

  unsigned smp_id = 0;
  glCreateSamplers(1, &smp_id);
  glSamplerParameteri(smp_id, 0x2801, 0x2600); // GL_TEXTURE_MIN_FILTER, GL_NEAREST
  glSamplerParameteri(smp_id, 0x2800, 0x2600); // GL_TEXTURE_MAG_FILTER, GL_NEAREST

  unsigned tex_input[16] = {0};
  tex_input[0] = 0;
  tex_input[1] = vt_f32_tex_id;
  tex_input[2] = vt_u32_tex_id;
  tex_input[3] = id_tex_id;

  unsigned smp_input[16] = {0};
  smp_input[0] = smp_id;

  glBindTextures(0, 16, tex_input);
  glBindSamplers(0, 16, smp_input);

  int id_offset = 0;
  int vt_offset = 0;
  for (ptrdiff_t i = 0, c = draw_data->CmdListsCount; i < c; i += 1) {
    struct ImDrawList * cmd_list = draw_data->CmdLists[i];
    for (ptrdiff_t j = 0, c = ImDrawList_GetCmdSize(cmd_list); j < c; j += 1) {
      struct ImDrawCmd * pcmd = ImDrawList_GetCmdPtr(cmd_list, (int)j);
      if (pcmd->UserCallback) {
        pcmd->UserCallback(cmd_list, pcmd);
      } else {
        glScissor((int)(pcmd->ClipRect.x),
                  (int)(h - pcmd->ClipRect.w),
                  (int)(pcmd->ClipRect.z - pcmd->ClipRect.x),
                  (int)(pcmd->ClipRect.w - pcmd->ClipRect.y));
        glProgramUniform1iv(g_ig_state->vert, 2, 1, &vt_offset);
        tex_input[0] = *(unsigned *)pcmd->TextureId;
        glBindTextures(0, 1, tex_input);
        glDrawArraysInstanced(0x0004, id_offset, pcmd->ElemCount, 1); // GL_TRIANGLES
      }
      id_offset += pcmd->ElemCount;
    }
    vt_offset += ImDrawList_GetVertexBufferSize(cmd_list);
  }

  glDeleteBuffers(1, &id_mem_id);
  glDeleteBuffers(1, &vt_mem_id);
  glDeleteTextures(1, &id_tex_id);
  glDeleteTextures(1, &vt_f32_tex_id);
  glDeleteTextures(1, &vt_u32_tex_id);

  glEnable(0x8DB9);  // GL_FRAMEBUFFER_SRGB
  glDisable(0x0C11); // GL_SCISSOR_TEST
  glEnable(0x0B71);  // GL_DEPTH_TEST
  glEnable(0x0B44);  // GL_CULL_FACE
}

char * ImguiGetClipboardText() {
  Atom incr_atom = XInternAtom(g_ig_state->dpy, "INCR", 0);
  Atom xsel_atom = XInternAtom(g_ig_state->dpy, "XSEL_DATA", 0);
  Atom utf8_atom = XInternAtom(g_ig_state->dpy, "UTF8_STRING", 1);
  Atom clipboard_atom = XInternAtom(g_ig_state->dpy, "CLIPBOARD", 0);

  Window owner_win = XGetSelectionOwner(g_ig_state->dpy, clipboard_atom);
  if (owner_win == g_ig_state->win) {
    return g_ig_state->clipboard_copy;
  }

  XConvertSelection(g_ig_state->dpy, clipboard_atom, utf8_atom, xsel_atom, g_ig_state->win, CurrentTime);

  XEvent event = {0};
  XNextEvent(g_ig_state->dpy, &event);
  switch (event.type) {
    break; case SelectionNotify: {

      if (event.xselection.selection != clipboard_atom)
        break;
      if (event.xselection.property == 0)
        break;

      Atom target = 0;
      int format  = 0;
      unsigned long size = 0, remain = 0;
      char * data = NULL;
      XGetWindowProperty(event.xselection.display,
                         event.xselection.requestor,
                         event.xselection.property,
                         0,
                         0x7FFFFFFFL, // LONG_MAX
                         1,
                         AnyPropertyType,
                         &target,
                         &format,
                         &size,
                         &remain,
                         (unsigned char**)&data);

      g_gpulib_libc.usleep(g_ig_state->clipboard_paste_sleep_microseconds);

      if (target == incr_atom) {
        XFree(data);
        data = NULL;
        g_gpulib_libc.free(g_ig_state->clipboard_paste);
        g_ig_state->clipboard_paste = NULL;

        for (size_t total = 1;;) {
          XGetWindowProperty(event.xselection.display,
                             event.xselection.requestor,
                             event.xselection.property,
                             0,
                             0x7FFFFFFFL, // LONG_MAX
                             1,
                             AnyPropertyType,
                             &target,
                             &format,
                             &size,
                             &remain,
                             (unsigned char**)&data);

          g_gpulib_libc.usleep(g_ig_state->clipboard_paste_sleep_microseconds);

          if (size) {
            total += size;
            g_ig_state->clipboard_paste = g_gpulib_libc.realloc(g_ig_state->clipboard_paste, total);
            g_ig_state->clipboard_paste[total - size - 1] = '\0';
            g_gpulib_libc.strcat(g_ig_state->clipboard_paste, data);
          }

          XFree(data);

          if (size == 0)
            break;
        }
      } else if (target == utf8_atom || target == ((Atom)31)) { // XA_STRING
        g_gpulib_libc.free(g_ig_state->clipboard_paste);
        g_ig_state->clipboard_paste = g_gpulib_libc.strndup(data, size);
        XFree(data);
      }
    }
  }

  return g_ig_state->clipboard_paste;
}

void ImguiSetClipboardText(char * text) {
  XSetSelectionOwner(g_ig_state->dpy, XInternAtom(g_ig_state->dpy, "CLIPBOARD", 0), g_ig_state->win, 0);
  ptrdiff_t text_bytes = g_gpulib_libc.strlen(text);
  g_ig_state->clipboard_copy = g_gpulib_libc.realloc(g_ig_state->clipboard_copy, text_bytes + 1);
  memcpy(g_ig_state->clipboard_copy, text, text_bytes);
  g_ig_state->clipboard_copy[text_bytes] = 0;
}

static inline bool ImguiProcessEvent(XEvent * event) {
  struct ImGuiIO * io = igGetIO();
  switch (event->type) {
    break; case (KeyPress): {
      io->KeysDown[event->xkey.keycode] = true;

      char utf[32] = {0};
      KeySym keysym = 0;
      if (XLookupString(&event->xkey, utf, 32, &keysym, NULL) != NoSymbol)
        ImGuiIO_AddInputCharactersUTF8(utf);

      int keysym_count = 0;
      KeySym * sym = XGetKeyboardMapping(g_ig_state->dpy, event->xkey.keycode, 1, &keysym_count);

      if (sym[0] == XK_Shift_L   || sym[0] == XK_Shift_R)   io->KeyShift = true;
      if (sym[0] == XK_Control_L || sym[0] == XK_Control_R) io->KeyCtrl  = true;
      if (sym[0] == XK_Alt_L     || sym[0] == XK_Alt_R)     io->KeyAlt   = true;
      if (sym[0] == XK_Super_L   || sym[0] == XK_Super_R)   io->KeySuper = true;

      XFree(sym);

      return true;
    }
    break; case (KeyRelease): {
      io->KeysDown[event->xkey.keycode] = false;

      int keysym_count = 0;
      KeySym * sym = XGetKeyboardMapping(g_ig_state->dpy, event->xkey.keycode, 1, &keysym_count);

      if (sym[0] == XK_Shift_L   || sym[0] == XK_Shift_R)   io->KeyShift = false;
      if (sym[0] == XK_Control_L || sym[0] == XK_Control_R) io->KeyCtrl  = false;
      if (sym[0] == XK_Alt_L     || sym[0] == XK_Alt_R)     io->KeyAlt   = false;
      if (sym[0] == XK_Super_L   || sym[0] == XK_Super_R)   io->KeySuper = false;

      XFree(sym);

      return true;
    }
    break; case SelectionRequest: {
      Atom text_atom = XInternAtom(g_ig_state->dpy, "TEXT", 0);
      Atom utf8_atom = XInternAtom(g_ig_state->dpy, "UTF8_STRING", 1);
      Atom targets_atom = XInternAtom(g_ig_state->dpy, "TARGETS", 0);
      Atom clipboard_atom = XInternAtom(g_ig_state->dpy, "CLIPBOARD", 0);

      if (event->xselectionrequest.selection != clipboard_atom)
        break;

      XSelectionRequestEvent * xsr = &event->xselectionrequest;
      XSelectionEvent e = {0};
      e.type = SelectionNotify;
      e.display = xsr->display;
      e.requestor = xsr->requestor;
      e.selection = xsr->selection;
      e.time = xsr->time;
      e.target = xsr->target;
      e.property = xsr->property;

      int test = 0;
      if (e.target == targets_atom)
        test = XChangeProperty(e.display, e.requestor, e.property, ((Atom)4), 32, PropModeReplace, (unsigned char *)&utf8_atom, 1); // XA_ATOM
      else if (e.target == ((Atom)31) || e.target == text_atom) // XA_STRING
        test = XChangeProperty(e.display, e.requestor, e.property, ((Atom)31), 8, PropModeReplace, (unsigned char *)g_ig_state->clipboard_copy, g_gpulib_libc.strlen(g_ig_state->clipboard_copy));
      else if (e.target == utf8_atom)
        test = XChangeProperty(e.display, e.requestor, e.property, utf8_atom, 8, PropModeReplace, (unsigned char *)g_ig_state->clipboard_copy, g_gpulib_libc.strlen(g_ig_state->clipboard_copy));
      else
        e.property = None;
      if ((test & 2) == 0)
        XSendEvent(g_ig_state->dpy, e.requestor, 0, 0, (XEvent *)&e);
    }
    break; case (ButtonPress): {
      if (event->xbutton.button == Button1) io->MouseDown[0] = true;
      if (event->xbutton.button == Button2) io->MouseDown[1] = true;
      if (event->xbutton.button == Button3) io->MouseDown[2] = true;
      if (event->xbutton.button == Button4) g_ig_state->mouse_wheel =  1;
      if (event->xbutton.button == Button5) g_ig_state->mouse_wheel = -1;
      return true;
    }
    break; case (ButtonRelease): {
      if (event->xbutton.button == Button1) io->MouseDown[0] = false;
      if (event->xbutton.button == Button2) io->MouseDown[1] = false;
      if (event->xbutton.button == Button3) io->MouseDown[2] = false;
      return true;
    }
    break; case (MotionNotify): {
      int x = event->xmotion.x;
      int y = event->xmotion.y;
      io->MousePos = (struct ImVec2){x, y};
    }
  }
  return false;
}

static inline void ImguiCreateFontTexture() {
  struct ImGuiIO * io = igGetIO();
  unsigned char * pixels = NULL;
  int width = 0, height = 0, bpp = 0;
  ImFontAtlas_GetTexDataAsRGBA32(io->Fonts, &pixels, &width, &height, &bpp);
  glCreateTextures(0x8C1A, 1, &g_ig_state->font_texture); // GL_TEXTURE_2D_ARRAY
  glTextureStorage3D(g_ig_state->font_texture, 1, 0x8814, width, height, 1); // GL_RGBA32F
  glTextureSubImage3D(g_ig_state->font_texture, 0, 0, 0, 0, width, height, 1, 0x1908, 0x1401, pixels); // GL_RGBA, GL_UNSIGNED_BYTE
  ImFontAtlas_SetTexID(io->Fonts, &g_ig_state->font_texture);
}

static inline void ImguiCreateDeviceObjects() {
  char * vert_string =
      "#version 330"                                                               "\n"
      "#extension GL_ARB_gpu_shader5                : enable"                      "\n"
      "#extension GL_ARB_shader_precision           : enable"                      "\n"
      "#extension GL_ARB_texture_cube_map_array     : enable"                      "\n"
      "#extension GL_ARB_separate_shader_objects    : enable"                      "\n"
      "#extension GL_ARB_shading_language_420pack   : enable"                      "\n"
      "#extension GL_ARB_shading_language_packing   : enable"                      "\n"
      "#extension GL_ARB_explicit_uniform_location  : enable"                      "\n"
      "#extension GL_ARB_fragment_coord_conventions : enable"                      "\n"
      "out gl_PerVertex { vec4 gl_Position; };"                                    "\n"
      ""                                                                           "\n"
      "layout(location = 0) uniform vec2 g_scale;"                                 "\n"
      "layout(location = 1) uniform vec2 g_translate;"                             "\n"
      "layout(location = 2) uniform int  g_vt_offset;"                             "\n"
      ""                                                                           "\n"
      "layout(binding = 1) uniform  samplerBuffer s_vt_f32;"                       "\n"
      "layout(binding = 2) uniform usamplerBuffer s_vt_u32;"                       "\n"
      "layout(binding = 3) uniform isamplerBuffer s_id;"                           "\n"
      ""                                                                           "\n"
      "layout(location = 0) out vec2 g_uv;"                                        "\n"
      "layout(location = 1) out vec4 g_colour;"                                    "\n"
      ""                                                                           "\n"
      "void main() {"                                                              "\n"
      "  int i = texelFetch(s_id, gl_VertexID).x;"                                 "\n"
      "  float pos_x = texelFetch(s_vt_f32, (g_vt_offset + i) * 5 + 0).x;"         "\n"
      "  float pos_y = texelFetch(s_vt_f32, (g_vt_offset + i) * 5 + 1).x;"         "\n"
      "  float uv_x  = texelFetch(s_vt_f32, (g_vt_offset + i) * 5 + 2).x;"         "\n"
      "  float uv_y  = texelFetch(s_vt_f32, (g_vt_offset + i) * 5 + 3).x;"         "\n"
      "  uint  color = texelFetch(s_vt_u32, (g_vt_offset + i) * 5 + 4).x;"         "\n"
      "  g_uv = vec2(uv_x, uv_y);"                                                 "\n"
      "  g_colour = unpackUnorm4x8(color);"                                        "\n"
      "  gl_Position = vec4(fma(vec2(pos_x, pos_y), g_scale, g_translate), 0, 1);" "\n"
      "}"                                                                          "\n";

  char * frag_string =
      "#version 330"                                              "\n"
      "#extension GL_ARB_gpu_shader5                : enable"     "\n"
      "#extension GL_ARB_shader_precision           : enable"     "\n"
      "#extension GL_ARB_texture_cube_map_array     : enable"     "\n"
      "#extension GL_ARB_separate_shader_objects    : enable"     "\n"
      "#extension GL_ARB_shading_language_420pack   : enable"     "\n"
      "#extension GL_ARB_shading_language_packing   : enable"     "\n"
      "#extension GL_ARB_explicit_uniform_location  : enable"     "\n"
      "#extension GL_ARB_fragment_coord_conventions : enable"     "\n"
      "layout(origin_upper_left) in vec4 gl_FragCoord;"           "\n"
      ""                                                          "\n"
      "layout(binding = 0) uniform sampler2DArray s_texture;"     "\n"
      ""                                                          "\n"
      "layout(location = 0) in vec2 g_uv;"                        "\n"
      "layout(location = 1) in vec4 g_colour;"                    "\n"
      ""                                                          "\n"
      "layout(location = 0) out vec4 g_color;"                    "\n"
      ""                                                          "\n"
      "void main() {"                                             "\n"
      "  g_color = g_colour * texture(s_texture, vec3(g_uv, 0));" "\n"
      "}"                                                         "\n";

  unsigned vert_shader_id = glCreateShader(0x8B31); // GL_VERTEX_SHADER
  unsigned frag_shader_id = glCreateShader(0x8B30); // GL_FRAGMENT_SHADER

  glShaderSource(vert_shader_id, 1, (char **)&vert_string, NULL);
  glShaderSource(frag_shader_id, 1, (char **)&frag_string, NULL);

  glCompileShader(vert_shader_id);
  glCompileShader(frag_shader_id);

  g_ig_state->vert = glCreateProgram();
  g_ig_state->frag = glCreateProgram();

  glProgramParameteri(g_ig_state->vert, 0x8258, 1); // GL_PROGRAM_SEPARABLE
  glProgramParameteri(g_ig_state->frag, 0x8258, 1); // GL_PROGRAM_SEPARABLE

  glAttachShader(g_ig_state->vert, vert_shader_id);
  glAttachShader(g_ig_state->frag, frag_shader_id);

  glLinkProgram(g_ig_state->vert);
  glLinkProgram(g_ig_state->frag);

  glDetachShader(g_ig_state->vert, vert_shader_id);
  glDetachShader(g_ig_state->frag, frag_shader_id);

  glDeleteShader(vert_shader_id);
  glDeleteShader(frag_shader_id);

  glCreateProgramPipelines(1, &g_ig_state->ppo);

  glUseProgramStages(g_ig_state->ppo, 0x00000001, g_ig_state->vert); // GL_VERTEX_SHADER_BIT
  glUseProgramStages(g_ig_state->ppo, 0x00000002, g_ig_state->frag); // GL_FRAGMENT_SHADER_BIT

  ImguiCreateFontTexture();
}

static inline unsigned long ImguiSysGetTimeMs() {
  struct timeval tv;
  stdlib_gettimeofday(&tv, NULL);
  return tv.tv_sec * 1000UL + tv.tv_usec / 1000UL;
}

static void inline ImguiNewFrame() {
  struct ImGuiIO * io = igGetIO();
  if (!g_ig_state->font_texture)
    ImguiCreateDeviceObjects();

  int w = 0, h = 0;
  XWindowAttributes win_attrs = {0};
  XGetWindowAttributes(g_ig_state->dpy, g_ig_state->win, &win_attrs);
  io->DisplaySize = (struct ImVec2){win_attrs.width, win_attrs.height};
  io->DisplayFramebufferScale = (struct ImVec2){1, 1};

  unsigned long time = ImguiSysGetTimeMs();
  double current_time = time / 1000.0;
  io->DeltaTime = g_ig_state->time > 0 ? (float)(current_time - g_ig_state->time) : 1 / 60.f;
  g_ig_state->time = current_time;

  io->MouseWheel = g_ig_state->mouse_wheel;
  g_ig_state->mouse_wheel = 0;

  igNewFrame();
}

static inline void ImguiInvalidateDeviceObjects() {
  struct ImGuiIO * io = igGetIO();

  glDeleteProgram(g_ig_state->vert);
  glDeleteProgram(g_ig_state->frag);
  glDeleteProgramPipelines(1, &g_ig_state->ppo);
  g_ig_state->vert = 0, g_ig_state->frag = 0, g_ig_state->ppo = 0;
  if (g_ig_state->font_texture) {
    glDeleteTextures(1, &g_ig_state->font_texture);
    ImFontAtlas_SetTexID(io->Fonts, 0);
    g_ig_state->font_texture = 0;
  }
}

static inline void ImguiDeinit() {
  g_gpulib_libc.free(g_ig_state->clipboard_copy);
  g_gpulib_libc.free(g_ig_state->clipboard_paste);
  g_ig_state->clipboard_copy = NULL;
  g_ig_state->clipboard_paste = NULL;
  ImguiInvalidateDeviceObjects();
  igShutdown();
}

static inline int ImguiX11ScancodeToKeycode(char * scancodes, char * scancode) {
  for (int i = 0; i < 256; i += 1) {
    char * code = &scancodes[i * 5];
    if (stdlib_nstreq(4, code, scancode))
      return i;
  }
  return -1;
}

static inline void ImguiInit(Display * dpy, Window win, char * scancodes) {
  struct ImGuiIO * io = igGetIO();

  g_ig_state->dpy = dpy;
  g_ig_state->win = win;

  io->KeyMap[ImGuiKey_Tab] = ImguiX11ScancodeToKeycode(scancodes, "TAB\0");
  io->KeyMap[ImGuiKey_LeftArrow] = ImguiX11ScancodeToKeycode(scancodes, "LEFT");
  io->KeyMap[ImGuiKey_RightArrow] = ImguiX11ScancodeToKeycode(scancodes, "RGHT");
  io->KeyMap[ImGuiKey_UpArrow] = ImguiX11ScancodeToKeycode(scancodes, "UP\0\0");
  io->KeyMap[ImGuiKey_DownArrow] = ImguiX11ScancodeToKeycode(scancodes, "DOWN");
  io->KeyMap[ImGuiKey_PageUp] = ImguiX11ScancodeToKeycode(scancodes, "PGUP");
  io->KeyMap[ImGuiKey_PageDown] = ImguiX11ScancodeToKeycode(scancodes, "PGDN");
  io->KeyMap[ImGuiKey_Home] = ImguiX11ScancodeToKeycode(scancodes, "HOME");
  io->KeyMap[ImGuiKey_End] = ImguiX11ScancodeToKeycode(scancodes, "END\0");
  io->KeyMap[ImGuiKey_Delete] = ImguiX11ScancodeToKeycode(scancodes, "DELE");
  io->KeyMap[ImGuiKey_Backspace] = ImguiX11ScancodeToKeycode(scancodes, "BKSP");
  io->KeyMap[ImGuiKey_Enter] = ImguiX11ScancodeToKeycode(scancodes, "RTRN");
  io->KeyMap[ImGuiKey_Escape] = ImguiX11ScancodeToKeycode(scancodes, "ESC\0");
  io->KeyMap[ImGuiKey_A] = ImguiX11ScancodeToKeycode(scancodes, "AC01");
  io->KeyMap[ImGuiKey_C] = ImguiX11ScancodeToKeycode(scancodes, "AB03");
  io->KeyMap[ImGuiKey_V] = ImguiX11ScancodeToKeycode(scancodes, "AB04");
  io->KeyMap[ImGuiKey_X] = ImguiX11ScancodeToKeycode(scancodes, "AB02");
  io->KeyMap[ImGuiKey_Y] = ImguiX11ScancodeToKeycode(scancodes, "AD06");
  io->KeyMap[ImGuiKey_Z] = ImguiX11ScancodeToKeycode(scancodes, "AB01");

  io->RenderDrawListsFn = ImguiRenderDrawList;
  io->GetClipboardTextFn = ImguiGetClipboardText;
  io->SetClipboardTextFn = ImguiSetClipboardText;
}

static inline void ImguiEasyTheming(
    struct ImVec3 color_for_text,
    struct ImVec3 color_for_head,
    struct ImVec3 color_for_area,
    struct ImVec3 color_for_body,
    struct ImVec3 color_for_pops)
{
  struct ImGuiStyle * style = igGetStyle();

  style->Colors[ImGuiCol_Text]                 = (struct ImVec4){color_for_text.x, color_for_text.y, color_for_text.z, 1.00f};
  style->Colors[ImGuiCol_TextDisabled]         = (struct ImVec4){color_for_text.x, color_for_text.y, color_for_text.z, 0.58f};
  style->Colors[ImGuiCol_WindowBg]             = (struct ImVec4){color_for_body.x, color_for_body.y, color_for_body.z, 1.00f};
  style->Colors[ImGuiCol_ChildWindowBg]        = (struct ImVec4){color_for_area.x, color_for_area.y, color_for_area.z, 0.58f};
  style->Colors[ImGuiCol_Border]               = (struct ImVec4){color_for_body.x, color_for_body.y, color_for_body.z, 0.00f};
  style->Colors[ImGuiCol_BorderShadow]         = (struct ImVec4){color_for_body.x, color_for_body.y, color_for_body.z, 0.00f};
  style->Colors[ImGuiCol_FrameBg]              = (struct ImVec4){color_for_area.x, color_for_area.y, color_for_area.z, 1.00f};
  style->Colors[ImGuiCol_FrameBgHovered]       = (struct ImVec4){color_for_head.x, color_for_head.y, color_for_head.z, 0.78f};
  style->Colors[ImGuiCol_FrameBgActive]        = (struct ImVec4){color_for_head.x, color_for_head.y, color_for_head.z, 1.00f};
  style->Colors[ImGuiCol_TitleBg]              = (struct ImVec4){color_for_area.x, color_for_area.y, color_for_area.z, 1.00f};
  style->Colors[ImGuiCol_TitleBgCollapsed]     = (struct ImVec4){color_for_area.x, color_for_area.y, color_for_area.z, 0.75f};
  style->Colors[ImGuiCol_TitleBgActive]        = (struct ImVec4){color_for_head.x, color_for_head.y, color_for_head.z, 1.00f};
  style->Colors[ImGuiCol_MenuBarBg]            = (struct ImVec4){color_for_area.x, color_for_area.y, color_for_area.z, 1.00f};
  style->Colors[ImGuiCol_ScrollbarBg]          = (struct ImVec4){color_for_area.x, color_for_area.y, color_for_area.z, 1.00f};
  style->Colors[ImGuiCol_ScrollbarGrab]        = (struct ImVec4){color_for_head.x, color_for_head.y, color_for_head.z, 0.50f};
  style->Colors[ImGuiCol_ScrollbarGrabHovered] = (struct ImVec4){color_for_head.x, color_for_head.y, color_for_head.z, 0.78f};
  style->Colors[ImGuiCol_ScrollbarGrabActive]  = (struct ImVec4){color_for_head.x, color_for_head.y, color_for_head.z, 1.00f};
  style->Colors[ImGuiCol_ComboBg]              = (struct ImVec4){color_for_area.x, color_for_area.y, color_for_area.z, 1.00f};
  style->Colors[ImGuiCol_CheckMark]            = (struct ImVec4){color_for_head.x, color_for_head.y, color_for_head.z, 0.80f};
  style->Colors[ImGuiCol_SliderGrab]           = (struct ImVec4){color_for_head.x, color_for_head.y, color_for_head.z, 0.50f};
  style->Colors[ImGuiCol_SliderGrabActive]     = (struct ImVec4){color_for_head.x, color_for_head.y, color_for_head.z, 1.00f};
  style->Colors[ImGuiCol_Button]               = (struct ImVec4){color_for_head.x, color_for_head.y, color_for_head.z, 0.50f};
  style->Colors[ImGuiCol_ButtonHovered]        = (struct ImVec4){color_for_head.x, color_for_head.y, color_for_head.z, 0.86f};
  style->Colors[ImGuiCol_ButtonActive]         = (struct ImVec4){color_for_head.x, color_for_head.y, color_for_head.z, 1.00f};
  style->Colors[ImGuiCol_Header]               = (struct ImVec4){color_for_head.x, color_for_head.y, color_for_head.z, 0.76f};
  style->Colors[ImGuiCol_HeaderHovered]        = (struct ImVec4){color_for_head.x, color_for_head.y, color_for_head.z, 0.86f};
  style->Colors[ImGuiCol_HeaderActive]         = (struct ImVec4){color_for_head.x, color_for_head.y, color_for_head.z, 1.00f};
  style->Colors[ImGuiCol_Column]               = (struct ImVec4){color_for_head.x, color_for_head.y, color_for_head.z, 0.32f};
  style->Colors[ImGuiCol_ColumnHovered]        = (struct ImVec4){color_for_head.x, color_for_head.y, color_for_head.z, 0.78f};
  style->Colors[ImGuiCol_ColumnActive]         = (struct ImVec4){color_for_head.x, color_for_head.y, color_for_head.z, 1.00f};
  style->Colors[ImGuiCol_ResizeGrip]           = (struct ImVec4){color_for_head.x, color_for_head.y, color_for_head.z, 0.15f};
  style->Colors[ImGuiCol_ResizeGripHovered]    = (struct ImVec4){color_for_head.x, color_for_head.y, color_for_head.z, 0.78f};
  style->Colors[ImGuiCol_ResizeGripActive]     = (struct ImVec4){color_for_head.x, color_for_head.y, color_for_head.z, 1.00f};
  style->Colors[ImGuiCol_CloseButton]          = (struct ImVec4){color_for_text.x, color_for_text.y, color_for_text.z, 0.16f};
  style->Colors[ImGuiCol_CloseButtonHovered]   = (struct ImVec4){color_for_text.x, color_for_text.y, color_for_text.z, 0.39f};
  style->Colors[ImGuiCol_CloseButtonActive]    = (struct ImVec4){color_for_text.x, color_for_text.y, color_for_text.z, 1.00f};
  style->Colors[ImGuiCol_PlotLines]            = (struct ImVec4){color_for_text.x, color_for_text.y, color_for_text.z, 0.63f};
  style->Colors[ImGuiCol_PlotLinesHovered]     = (struct ImVec4){color_for_head.x, color_for_head.y, color_for_head.z, 1.00f};
  style->Colors[ImGuiCol_PlotHistogram]        = (struct ImVec4){color_for_text.x, color_for_text.y, color_for_text.z, 0.63f};
  style->Colors[ImGuiCol_PlotHistogramHovered] = (struct ImVec4){color_for_head.x, color_for_head.y, color_for_head.z, 1.00f};
  style->Colors[ImGuiCol_TextSelectedBg]       = (struct ImVec4){color_for_head.x, color_for_head.y, color_for_head.z, 0.43f};
  style->Colors[ImGuiCol_PopupBg]              = (struct ImVec4){color_for_pops.x, color_for_pops.y, color_for_pops.z, 0.92f};
  style->Colors[ImGuiCol_ModalWindowDarkening] = (struct ImVec4){color_for_area.x, color_for_area.y, color_for_area.z, 0.73f};
}

#pragma once

#include "../../stdlib/stdlib.h"
#define GPULIB_DEBUG_MANUAL
#include "../../gpulib_x11_debug.h"
#include "../../gpulib_globals.h"
#include "../../gpulib_x11_wsi_globals.h"
#include "../../gpulib_x11_imgui_globals.h"

struct api_t {
  void * (*Init)(Display *, Window, char *,
      struct gpu_libc_t *,
      struct gpu_libgl_t *,
      struct gpu_libglx_t *,
      struct gpu_debug_state_t *,
      struct ig_state_t *,
      struct ImGuiContext *);
  void   (*Load)(void *, Display *, Window, char *,
      struct gpu_libc_t *,
      struct gpu_libgl_t *,
      struct gpu_libglx_t *,
      struct gpu_debug_state_t *,
      struct ig_state_t *,
      struct ImGuiContext *);
  int    (*Step)(void *, Display *, Window, char *);
  void   (*Unload)(void *);
  void   (*Deinit)(void *);
};

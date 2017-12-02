#pragma once

#define GPULIB_DEBUG_MANUAL
#include "../../gpulib_debug.h"

struct api_t {
  void * (*Init)(Display *, Window, char *, struct ImGuiContext *, struct ig_state_t *);
  void   (*Load)(void *, Display *, Window, char *, struct ImGuiContext *, struct ig_state_t *);
  int    (*Step)(void *, Display *, Window, char *);
  void   (*Unload)(void *);
  void   (*Deinit)(void *);
};

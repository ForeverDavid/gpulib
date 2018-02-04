#include "../../stdlib/stdlib.h"
#include "../../gpulib.h"
#include "../../gpulib_globals.h"
#include "../../gpulib_x11_wsi.h"
#include "../../gpulib_x11_wsi_globals.h"

typedef struct { float x, y, z, w; } vec4;

int main() {
  Display * dpy = NULL;
  Window win = 0;
  GpuWsiWindow("Async Compute", sizeof("Async Compute"), 1280, 720, 0, NULL, &dpy, &win);
  GpuSetDebugCallback(GpuDebugCallback);

  unsigned v1_id = 0;
  unsigned v2_id = 0;
  unsigned v3_id = 0;
  vec4 * v1 = GpuMalloc(4 * sizeof(vec4), &v1_id);
  vec4 * v2 = GpuMalloc(4 * sizeof(vec4), &v2_id);
  vec4 * v3 = GpuMalloc(4 * sizeof(vec4), &v3_id);

  v1[0] = (vec4){ 1,  2,  3,  0};
  v1[1] = (vec4){ 4,  5,  6,  0};
  v1[2] = (vec4){ 7,  8,  9,  0};
  v1[3] = (vec4){10, 11, 12,  0};

  v2[0] = (vec4){13, 14, 15,  0};
  v2[1] = (vec4){16, 17, 18,  0};
  v2[2] = (vec4){19, 20, 21,  0};
  v2[3] = (vec4){22, 23, 24,  0};

  v3[0] = (vec4){ 0,  0,  0,  0};
  v3[1] = (vec4){ 0,  0,  0,  0};
  v3[2] = (vec4){ 0,  0,  0,  0};
  v3[3] = (vec4){ 0,  0,  0,  0};

  char comp_string[] = GPULIB_COMPUTE_HEADER
    "layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;"          "\n"
    ""                                                                          "\n"
    "layout(binding = 0) uniform samplerBuffer s_v1;"                           "\n"
    "layout(binding = 1) uniform samplerBuffer s_v2;"                           "\n"
    "layout(rgba32f, binding = 0) restrict writeonly uniform imageBuffer i_v3;" "\n"
    ""                                                                          "\n"
    "void main() {"                                                             "\n"
    "  int i = int(gl_GlobalInvocationID.x);"                                   "\n"
    "  int j = int(gl_GlobalInvocationID.y);"                                   "\n"
    "  int k = int(gl_GlobalInvocationID.z);"                                   "\n"
    ""                                                                          "\n"
    "  vec4 v1 = texelFetch(s_v1, i);"                                          "\n"
    "  vec4 v2 = texelFetch(s_v2, i);"                                          "\n"
    ""                                                                          "\n"
    "  imageStore(i_v3, i, v1 + v2);"                                           "\n"
    "}"                                                                         "\n";

  unsigned comp = GpuProgramCompute(comp_string);

  unsigned textures[16] = {
    [0] = GpuView(v1_id, gpu_xyzw_f32_e, 0, 4 * sizeof(vec4)),
    [1] = GpuView(v2_id, gpu_xyzw_f32_e, 0, 4 * sizeof(vec4)),
  };

  unsigned images[8] = {
    [0] = GpuView(v3_id, gpu_xyzw_f32_e, 0, 4 * sizeof(vec4)),
  };

  unsigned query = GpuQuery();

  GpuBindProgram(comp);
  GpuBindTextures(0, 16, textures);
  GpuBindImages(0, 8, images);
  GpuQueryBeginTimeElapsed(query);
  GpuDispatch(4, 1, 1);
  GpuQueryEndTimeElapsed();
  GpuBarrier();
  void * fence = GpuFence();

  for (int fence_is_complete = 0; fence_is_complete == 0;) {
    GpuWsiSwap(dpy, win);
    fence_is_complete = GpuFenceIsComplete(fence);
    stdlib_printf("[GpuLib] Fence is complete: %d\n", fence_is_complete);
    stdlib_printf(
      "[GpuLib] Returned values:" "\n"
      "v3[0].xyz: %.1f %.1f %.1f" "\n"
      "v3[1].xyz: %.1f %.1f %.1f" "\n"
      "v3[2].xyz: %.1f %.1f %.1f" "\n"
      "v3[3].xyz: %.1f %.1f %.1f" "\n\n",
      v3[0].x, v3[0].y, v3[0].z,
      v3[1].x, v3[1].y, v3[1].z,
      v3[2].x, v3[2].y, v3[2].z,
      v3[3].x, v3[3].y, v3[3].z);
  }

  if (GpuQueryIsResultAvailable(query) == 1) {
    stdlib_printf("[GpuLib] Query time elapsed: %zu\n\n", GpuQueryGetResult(query));
  }

  XDestroyWindow(dpy, win);
  XCloseDisplay(dpy);
  return 0;
}

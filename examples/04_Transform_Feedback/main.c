#include "../../gpulib.h"

enum {MAX_STR = 10000};

typedef struct { float x, y, z; } vec3;

int main() {
  Display * dpy = NULL;
  Window win = 0;
  GpuWindow("Transform Feedback", sizeof("Transform Feedback"), 1280, 720, 0, NULL, &dpy, &win);
  GpuSetDebugCallback(GpuDebugCallback);

  unsigned v1_id = 0;
  unsigned v2_id = 0;
  unsigned v3_id = 0;
  vec3 * v1 = GpuCalloc(4 * sizeof(vec3), &v1_id);
  vec3 * v2 = GpuCalloc(4 * sizeof(vec3), &v2_id);
  vec3 * v3 = GpuCalloc(4 * sizeof(vec3), &v3_id);

  v1[0].x = 1.0;
  v1[0].y = 2.0;
  v1[0].z = 3.0;

  v1[1].x = 4.0;
  v1[1].y = 5.0;
  v1[1].z = 6.0;

  v1[2].x = 7.0;
  v1[2].y = 8.0;
  v1[2].z = 9.0;

  v1[3].x = 10.0;
  v1[3].y = 11.0;
  v1[3].z = 12.0;

  v2[0].x = 13.0;
  v2[0].y = 14.0;
  v2[0].z = 15.0;

  v2[1].x = 16.0;
  v2[1].y = 17.0;
  v2[1].z = 18.0;

  v2[2].x = 19.0;
  v2[2].y = 20.0;
  v2[2].z = 21.0;

  v2[3].x = 22.0;
  v2[3].y = 23.0;
  v2[3].z = 24.0;

  char vert_string[] = GPULIB_VERT_HEADER
      "layout(binding = 0) uniform samplerBuffer s_v1;" "\n"
      "layout(binding = 1) uniform samplerBuffer s_v2;" "\n"
      ""                                                "\n"
      "out vec3 g_out;"                                 "\n"
      ""                                                "\n"
      "void main() {"                                   "\n"
      "  vec3 v1 = texelFetch(s_v1, gl_VertexID).xyz;"  "\n"
      "  vec3 v2 = texelFetch(s_v2, gl_VertexID).xyz;"  "\n"
      ""                                                "\n"
      "  g_out = v1 + v2;"                              "\n"
      "}"                                               "\n";

  unsigned compute_vert = GpuVertXfb(vert_string,
    "g_out",
    NULL,
    NULL,
    NULL);

  unsigned xfb = GpuXfb(
    v3_id, 0, 4 * sizeof(vec3),
    0, 0, 0,
    0, 0, 0,
    0, 0, 0);

  unsigned ppo = GpuPpo(compute_vert, 0);

  unsigned textures[16] = {
    [0] = GpuCast(v1_id, gpu_xyz_f32_e, 0, 4 * sizeof(vec3)),
    [1] = GpuCast(v2_id, gpu_xyz_f32_e, 0, 4 * sizeof(vec3))
  };

  GpuBindPpo(ppo);
  GpuBindTextures(0, 16, textures);
  GpuBindXfb(xfb);
  GpuDrawOnceXfb(gpu_points_e, 0, 4, 1);
  GpuBindXfb(0);

  GpuFinish();

  char cmd[MAX_STR] = {0};
  stdlib_snprintf(
    cmd, MAX_STR,
    "notify-send \""
    "[GpuLib] Completed "
    "v3[0].xyz: %.1f %.1f %.1f "
    "v3[1].xyz: %.1f %.1f %.1f "
    "v3[2].xyz: %.1f %.1f %.1f "
    "v3[3].xyz: %.1f %.1f %.1f \"",
    v3[0].x, v3[0].y, v3[0].z,
    v3[1].x, v3[1].y, v3[1].z,
    v3[2].x, v3[2].y, v3[2].z,
    v3[3].x, v3[3].y, v3[3].z);
  GpuSysShell(cmd, NULL);

  XDestroyWindow(dpy, win);
  XCloseDisplay(dpy);
  return 0;
}

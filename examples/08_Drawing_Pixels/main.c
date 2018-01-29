#include "../../gpulib.h"

static inline unsigned long GetTimeMs() {
  struct timeval tv;
  stdlib_gettimeofday(&tv, NULL);
  return tv.tv_sec * 1000UL + tv.tv_usec / 1000UL;
}

int main() {
  Display * dpy = NULL;
  Window win = 0;
  GpuWindow("Drawing Pixels", sizeof("Drawing Pixels"), 1280, 720, 0, NULL, &dpy, &win);
  GpuSetDebugCallback(GpuDebugCallback);

  unsigned vert = GpuVert(GPULIB_VERT_HEADER
      "layout(location = 0) out vec2 g_uv;"             "\n"
      ""                                                "\n"
      "const vec2 g_tri[] = vec2[]("                    "\n"
      "  vec2(-1,-1),"                                  "\n"
      "  vec2(-1, 3),"                                  "\n"
      "  vec2( 3,-1)"                                   "\n"
      ");"                                              "\n"
      ""                                                "\n"
      "void main() {"                                   "\n"
      "  g_uv = g_tri[gl_VertexID] * 0.5 + 0.5;"        "\n"
      "  gl_Position = vec4(g_tri[gl_VertexID], 0, 1);" "\n"
      "}"                                               "\n");

  unsigned frag = GpuFrag(GPULIB_FRAG_HEADER
      "layout(location = 0) uniform vec4 g_time;"                                         "\n"
      ""                                                                                  "\n"
      "layout(binding = 0) uniform sampler2DArray s_color;"                               "\n"
      ""                                                                                  "\n"
      "layout(location = 0) in vec2 g_uv;"                                                "\n"
      ""                                                                                  "\n"
      "layout(location = 0) out vec4 g_color;"                                            "\n"
      ""                                                                                  "\n"
      "vec3 ScreenSpaceDither(vec2 screen_pos) {"                                         "\n"
      "  vec3 dither = dot(vec2(171.0, 231.0), screen_pos.xy + g_time.x).xxx;"            "\n"
      "  dither.rgb = fract(dither.rgb / vec3(103.0, 71.0, 97.0)) - vec3(0.5, 0.5, 0.5);" "\n"
      "  return (dither.rgb / 255.0) * 0.375;"                                            "\n"
      "}"                                                                                 "\n"
      ""                                                                                  "\n"
      "void main() {"                                                                     "\n"
      "  vec4 color = texture(s_color, vec3(g_uv, 0));"                                   "\n"
      "  g_color = vec4(g_uv, 0, 1);"                                                     "\n"
      "  g_color.xyz += ScreenSpaceDither(gl_FragCoord.xy) * 10;"                         "\n"
      "}"                                                                                 "\n");

  unsigned ppo = GpuPpo(vert, frag);
  unsigned tex = GpuCallocImg(gpu_srgba_b8_e, 1280, 720, 1, 1);
  unsigned smp = GpuSmp(0, gpu_nearest_e, gpu_nearest_e, gpu_clamp_to_border_e);

  unsigned long t_init = GetTimeMs();
  unsigned long t_prev = GetTimeMs();

  for (Atom quit = XInternAtom(dpy, "WM_DELETE_WINDOW", 0);;) {
    unsigned long t_curr = GetTimeMs();
    double dt = ((t_curr - t_prev) * 60.0) / 1000.0;

    for (XEvent event = {0}; XPending(dpy);) {
      XNextEvent(dpy, &event);
      switch (event.type) {
        break; case ClientMessage: {
          if (event.xclient.data.l[0] == quit)
            goto exit;
        }
      }
    }
    GpuClear();
    GpuBindTextures(0, 16, (unsigned [16]){tex});
    GpuBindSamplers(0, 16, (unsigned [16]){smp});
    GpuBindPpo(ppo);
    GpuUniformFloat4(frag, 0, 1, (float [4]){(t_curr - t_init) / 1000.f, 0, 0, 0});
    GpuDrawOnce(gpu_triangles_e, 0, 3, 1);
    GpuSwap(dpy, win);

    t_prev = t_curr;
  }

exit:;
  XDestroyWindow(dpy, win);
  XCloseDisplay(dpy);
  return 0;
}

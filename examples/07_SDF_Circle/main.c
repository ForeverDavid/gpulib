#include "../../gpulib.h"

int main() {
  Display * dpy = NULL;
  Window win = 0;
  GpuWindow("SDF Circle", 1280, 720, 4, NULL, &dpy, &win);
  GpuSetDebugCallback(GpuDebugCallback);

  char vert_string[] = GPU_VERT_HEAD
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
    "}"                                               "\n";

  char frag_string[] = GPU_FRAG_HEAD
    "float ShapeCircle(vec2 p, float radius) {"                                "\n"
    "  return length(p) - radius;"                                             "\n"
    "}"                                                                        "\n"
    ""                                                                         "\n"
    "float DrawSolid(float d) {"                                               "\n"
    "  return smoothstep(0, 3.0 / 720.0, max(0, d));"                          "\n"
    "}"                                                                        "\n"
    ""                                                                         "\n"
    "layout(location = 0) in vec2 g_uv;"                                       "\n"
    ""                                                                         "\n"
    "layout(location = 0) out vec4 g_color;"                                   "\n"
    ""                                                                         "\n"
    "void main() {"                                                            "\n"
    "  vec2 circle_pos = g_uv - vec2(0.5, 0.5);"                               "\n"
    "  circle_pos.x *= 1280.0 / 720.0;"                                        "\n"
    "  float d = ShapeCircle(circle_pos, 0.2);"                                "\n"
    "  g_color = mix(vec4(1, 0.05, 0.05, 1), vec4(1, 1, 1, 1), DrawSolid(d));" "\n"
    "}"                                                                        "\n";

  unsigned vert = GpuVert(vert_string);
  unsigned frag = GpuFrag(frag_string);
  unsigned ppo  = GpuPpo(vert, frag);

  for (Atom quit = XInternAtom(dpy, "WM_DELETE_WINDOW", 0);;) {
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
    GpuBindPpo(ppo);
    GpuDrawOnce(gpu_triangles_e, 0, 3, 1);
    GpuSwap(dpy, win);
  }

exit:;
  return 0;
}

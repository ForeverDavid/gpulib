#include "../../stdlib/stdlib.h"
#include "../../gpulib_x11_debug.h"
#include "../../gpulib_globals.h"
#include "../../gpulib_x11_wsi_globals.h"
#include "../../gpulib_x11_imgui_globals.h"

enum {MAX_STR = 10000};

int main() {
  Display * dpy = NULL;
  Window win = 0;
  GpuWsiWindow("GPGPU", sizeof("GPGPU"), 1280, 720, 0, NULL, &dpy, &win);
  GpuSetDebugCallback(GpuDebugCallback);

  int dim_x = 800;
  int dim_y = 450;

  char vert_string[MAX_STR] = GPULIB_VERTEX_HEADER
      "const vec2 g_tri[] = vec2[]("                    "\n"
      "  vec2(-1,-1),"                                  "\n"
      "  vec2(-1, 3),"                                  "\n"
      "  vec2( 3,-1)"                                   "\n"
      ");"                                              "\n"
      ""                                                "\n"
      "void main() {"                                   "\n"
      "  gl_Position = vec4(g_tri[gl_VertexID], 0, 1);" "\n"
      "}"                                               "\n";

  char frag_string[MAX_STR] = GPULIB_FRAGMENT_HEADER
      "layout(location = 0) out vec4 g_color;"       "\n"
      ""                                             "\n"
      "void main() {"                                "\n"
      "  int W = 800;"                               "\n"
      "  int H = 450;"                               "\n"
      "  int X = int(floor(gl_FragCoord.x));"        "\n"
      "  int Y = int(floor(gl_FragCoord.y));"        "\n"
      "  float U = float(X) / (W - 1);"              "\n"
      "  float V = float(Y) / (H - 1);"              "\n"
      "  vec4 C = vec4(1, 0, 0, 1);"                 "\n"
      ""                                             "\n"
      "  vec2 z = vec2(0), c = vec2(0);"             "\n"
      "  c.x = (U - 0.5) * 3.0 * (16.0 / 9.0);"      "\n"
      "  c.y = (V - 0.5) * 3.0;"                     "\n"
      "  int i = 0, iter = 100;"                     "\n"
      "  z = c;"                                     "\n"
      "  for (i = 0; i < iter; i += 1) {"            "\n"
      "    float x = (z.x * z.x - z.y * z.y) + c.x;" "\n"
      "    float y = (z.y * z.x + z.x * z.y) + c.y;" "\n"
      "    if ((x * x + y * y) > 4.0)"               "\n"
      "      break;"                                 "\n"
      "    z.x = x;"                                 "\n"
      "    z.y = y;"                                 "\n"
      "  }"                                          "\n"
      ""                                             "\n"
      "  C.r = (i == iter ? 0.0 : float(i)) / 50.0;" "\n"
      ""                                             "\n"
      "  g_color = C;"                               "\n"
      "}"                                            "\n";

  unsigned vert = GpuProgramVertex(vert_string);
  unsigned frag = GpuProgramFragment(frag_string);
  unsigned ppo  = GpuPipeline(vert, frag);

  unsigned img_tex = GpuMallocImage(gpu_rgba_f32_e, dim_x, dim_y, 1, 1);
  unsigned fbo = GpuFramebuffer(img_tex, 0, 0, 0, 0, 0, 0, 0, 0, 0);

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

    if (GpuDebugProgramVertex(&vert, vert_string, sizeof(vert_string)) ||
        GpuDebugProgramFragment(&frag, frag_string, sizeof(frag_string))) {
      g_gpulib_libgl->DeleteProgramPipelines(1, &ppo);
      ppo = GpuPipeline(vert, frag);
    }

    GpuViewport(0, 0, dim_x, dim_y);
    GpuBindFramebuffer(fbo);
    GpuClear();
    GpuBindPipeline(ppo);
    GpuDraw(gpu_triangles_e, 0, 3, 1);
    GpuBindFramebuffer(0);
    GpuViewport(0, 0, 1280, 720);

    GpuClear();
    GpuDebugImage(img_tex);

    GpuWsiSwap(dpy, win);
  }

exit:;
  XDestroyWindow(dpy, win);
  XCloseDisplay(dpy);
  return 0;
}

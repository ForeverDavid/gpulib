#include "../../stdlib/stdlib.h"
#include "../../gpulib.h"
#include "../../gpulib_globals.h"
#include "../../gpulib_x11_wsi.h"
#include "../../gpulib_x11_wsi_globals.h"

typedef struct { float x, y, z; } vec3;

int main() {
  Display * dpy = NULL;
  Window win = 0;
  GpuWsiWindow("Hello Triangle", sizeof("Hello Triangle"), 1280, 720, 0, NULL, &dpy, &win);
  GpuSetDebugCallback(GpuDebugCallback);

  unsigned vertices_id = 0;
  vec3 * vertices = GpuMalloc(3 * sizeof(vec3), &vertices_id);
  vertices[0] = (vec3){ 0.0,  0.5, 0.0};
  vertices[1] = (vec3){ 0.5, -0.5, 0.0};
  vertices[2] = (vec3){-0.5, -0.5, 0.0};

  unsigned indices_id = 0;
  unsigned * indices = GpuMallocIndices(3, &indices_id);
  indices[0] = 0;
  indices[1] = 1;
  indices[2] = 2;

  unsigned commands_id = 0;
  struct gpu_cmd_t * commands = GpuMallocCommands(1, &commands_id);
  commands[0].first = 0;
  commands[0].count = 3;
  commands[0].instance_first = 0;
  commands[0].instance_count = 1;
  commands[0].base_vertex = 0;

  unsigned textures[16] = {0};
  textures[0] = GpuView(vertices_id, gpu_xyz_f32_e, 0, 3 * sizeof(vec3));

  unsigned vert = GpuProgramVertex(GPULIB_VERTEX_HEADER
      "layout(binding = 0) uniform samplerBuffer s_pos;" "\n"
      ""                                                 "\n"
      "void main() {"                                    "\n"
      "  vec3 pos = texelFetch(s_pos, gl_VertexID).xyz;" "\n"
      "  gl_Position = vec4(pos, 1);"                    "\n"
      "}"                                                "\n");

  unsigned frag = GpuProgramFragment(GPULIB_FRAGMENT_HEADER
      "layout(location = 0) out vec4 g_color;" "\n"
      ""                                       "\n"
      "void main() {"                          "\n"
      "  g_color = vec4(1, 0, 1, 1);"          "\n"
      "}"                                      "\n");

  unsigned ppo = GpuPipeline(vert, frag);

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
    GpuBindPipeline(ppo);
    GpuBindTextures(0, 16, textures);
    GpuBindIndices(indices_id);
    GpuBindCommands(commands_id);
    GpuDrawIndirect(gpu_triangles_e, 0, 1);
    GpuWsiSwap(dpy, win);
  }

exit:;
  XDestroyWindow(dpy, win);
  XCloseDisplay(dpy);
  return 0;
}

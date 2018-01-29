#include "../../gpulib.h"

#define auto __auto_type
#define countof(x) (sizeof(x) / sizeof((x)[0]))

enum {MAX_STR = 10000};

struct {
  char mesh_ib [MAX_STR];
  char mesh_vb [MAX_STR];
  char mesh_uv [MAX_STR];
} g_resources = {
  .mesh_ib = "meshes/MeshIB.binary",
  .mesh_vb = "meshes/MeshVB.binary",
  .mesh_uv = "meshes/MeshUV.binary",
};

#define GPUMESH_NO_HEADER_IMPORT
#define open stdlib_open
#define close stdlib_close
#define mmap stdlib_mmap
#define munmap stdlib_munmap
#define assert stdlib_assert
#include "../../gpulib_defines.h"
#include "meshes/MeshIBVB.h"
#include "meshes/MeshUV.h"
#include "../../gpulib_undefines.h"

struct gpu_cmd_t g_draw_commands[e_draw_count];

int main() {
  Display * dpy = NULL;
  Window win = 0;
  GpuWindow("Drawing Text", sizeof("Drawing Text"), 1280, 720, 0, NULL, &dpy, &win);
  GpuSetDebugCallback(GpuDebugCallback);

  unsigned di_buf = 0;
  unsigned ib_buf = 0;
  unsigned vb_tex = SimpleMeshUploadIBVB(g_resources.mesh_ib, g_resources.mesh_vb, 0, 0, 0, &di_buf, &ib_buf, NULL, &g_draw_commands[0].count);
  unsigned uv_tex = SimpleMeshUploadUV(g_resources.mesh_uv, 0, NULL);

  unsigned textures[16] = {
    vb_tex,
    uv_tex,
  };

  char text[] = "Nothing spectacular here.";

  unsigned chars_id = 0;
  auto chars = GpuCallocCommands(countof(text), &chars_id);
  for (int i = 0; i < countof(text); i += 1) {
    chars[i].instance_count = 1;
    chars[i].first = g_draw_commands[text[i] - 33].first;
    chars[i].count = g_draw_commands[text[i] - 33].count;
  }

  unsigned vert = GpuVert(GPULIB_VERT_HEADER
      "layout(binding = 0) uniform samplerBuffer s_vb;" "\n"
      "layout(binding = 1) uniform samplerBuffer s_uv;" "\n"
      ""                                                "\n"
      "layout(location = 0) uniform vec4 cid;"          "\n"
      ""                                                "\n"
      "layout(location = 0) out vec2 g_uv;"             "\n"
      ""                                                "\n"
      "void main() {"                                   "\n"
      "  vec3 pos = texelFetch(s_vb, gl_VertexID).xyz;" "\n"
      "  g_uv     = texelFetch(s_uv, gl_VertexID).xy;"  "\n"
      ""                                                "\n"
      "  pos += vec3(cid.x * 0.4521705, 0, 0);"         "\n"
      ""                                                "\n"
      "  pos -= vec3(5.5, 0.2, -4);"                    "\n"
      ""                                                "\n"
      "  pos.x *= 0.613861;"                            "\n"
      "  pos.y *= 1.091309;"                            "\n"
      ""                                                "\n"
      "  gl_Position = vec4(pos, pos.z + 0.1);"         "\n"
      "}"                                               "\n");

  unsigned frag = GpuFrag(GPULIB_FRAG_HEADER
      "layout(location = 0) in vec2 g_uv;"      "\n"
      ""                                        "\n"
      "layout(location = 0) out vec4 g_color;"  "\n"
      ""                                        "\n"
      "void main() {"                           "\n"
      "  g_color = vec4(g_uv.x, g_uv.y, 1, 1);" "\n"
      "}"                                       "\n");

  unsigned ppo = GpuPpo(vert, frag);

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
    GpuBindTextures(0, 16, textures);
    GpuBindIndices(ib_buf);
    GpuBindCommands(chars_id);
    for (int i = 0; i < countof(text); i += 1) {
      float character_index = (float)i;
      GpuUniformFloat4(vert, 0, 1, (float [4]){character_index, 0, 0, 0});
      GpuDraw(gpu_triangles_e, i, 1);
    }
    GpuSwap(dpy, win);
  }

exit:;
  XDestroyWindow(dpy, win);
  XCloseDisplay(dpy);
  return 0;
}

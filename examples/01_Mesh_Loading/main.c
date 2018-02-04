#include "../../stdlib/stdlib.h"
#include "../../gpulib.h"
#include "../../gpulib_globals.h"
#include "../../gpulib_x11_wsi.h"
#include "../../gpulib_x11_wsi_globals.h"

enum {MAX_STR = 10000};

struct {
  char mesh_ib     [MAX_STR];
  char mesh_id     [MAX_STR];
  char mesh_normals[MAX_STR];
  char mesh_uv     [MAX_STR];
  char mesh_vb     [MAX_STR];
  char xform_r     [MAX_STR];
  char xform_s     [MAX_STR];
  char xform_t     [MAX_STR];
} g_resources = {
  .mesh_ib      = "meshes/MeshIB.binary",
  .mesh_id      = "meshes/MeshID.binary",
  .mesh_normals = "meshes/MeshNormals.binary",
  .mesh_uv      = "meshes/MeshUV.binary",
  .mesh_vb      = "meshes/MeshVB.binary",
  .xform_r      = "meshes/XformsRotationQuaternion.binary",
  .xform_s      = "meshes/XformsScale.binary",
  .xform_t      = "meshes/XformsTranslation.binary",
};

#define GPUMESH_NO_HEADER_IMPORT
#define open stdlib_open
#define close stdlib_close
#define mmap stdlib_mmap
#define munmap stdlib_munmap
#define assert stdlib_assert
#include "../../gpulib_defines.h"
#include "meshes/MeshIBVB.h"
#include "meshes/MeshID.h"
#include "meshes/MeshNormals.h"
#include "meshes/MeshUV.h"
#include "meshes/Xforms.h"
#include "../../gpulib_undefines.h"

struct gpu_cmd_t g_draw_commands[e_draw_count] = {0};

int main() {
  Display * dpy = NULL;
  Window win = 0;
  GpuWsiWindow("Mesh Loading", sizeof("Mesh Loading"), 1280, 720, 0, NULL, &dpy, &win);
  GpuSetDebugCallback(GpuDebugCallback);

  unsigned di_buf = 0;
  unsigned ib_buf = 0;
  unsigned vb_tex = SimpleMeshUploadIBVB(g_resources.mesh_ib, g_resources.mesh_vb, 0, 0, 0, &di_buf, &ib_buf, NULL, (unsigned *)g_draw_commands);
  unsigned uv_tex = SimpleMeshUploadUV(g_resources.mesh_uv, 0, NULL);
  unsigned id_tex = SimpleMeshUploadID(g_resources.mesh_id, 0, NULL);
  unsigned normals_tex = SimpleMeshUploadNormals(g_resources.mesh_normals, 0, NULL);
  unsigned xform_s_tex = SimpleMeshUploadXformsScale(g_resources.xform_s, 0, NULL);
  unsigned xform_r_tex = SimpleMeshUploadXformsRotationQuaternion(g_resources.xform_r, 0, NULL);
  unsigned xform_t_tex = SimpleMeshUploadXformsTranslation(g_resources.xform_t, 0, NULL);

  unsigned textures[16] = {
    vb_tex,
    id_tex,
    uv_tex,
    normals_tex,
    xform_s_tex,
    xform_r_tex,
    xform_t_tex,
  };

  unsigned vert = GpuProgramVertex(GPULIB_VERTEX_HEADER
      "layout(binding = 0) uniform samplerBuffer  s_vb;"            "\n"
      "layout(binding = 1) uniform isamplerBuffer s_id;"            "\n"
      "layout(binding = 2) uniform samplerBuffer  s_uv;"            "\n"
      "layout(binding = 3) uniform samplerBuffer  s_normals;"       "\n"
      "layout(binding = 4) uniform samplerBuffer  s_xfs;"           "\n"
      "layout(binding = 5) uniform samplerBuffer  s_xfr;"           "\n"
      "layout(binding = 6) uniform samplerBuffer  s_xft;"           "\n"
      ""                                                            "\n"
      "layout(location = 0) out vec2 g_uv;"                         "\n"
      ""                                                            "\n"
      "vec4 qinv(vec4 v) {"                                         "\n"
      "  return vec4(-v.xyz, v.w);"                                 "\n"
      "}"                                                           "\n"
      ""                                                            "\n"
      "vec4 qmul(vec4 a, vec4 b) {"                                 "\n"
      "  vec3 c = a.xyz * b.w + b.xyz * a.w + cross(a.xyz, b.xyz);" "\n"
      "  float d = a.w * b.w - dot(a.xyz, b.xyz);"                  "\n"
      "  return vec4(c, d);"                                        "\n"
      "}"                                                           "\n"
      ""                                                            "\n"
      "vec3 qrot(vec3 p, vec4 q) {"                                 "\n"
      "  return qmul(qmul(q, vec4(p, 0)), qinv(q)).xyz;"            "\n"
      "}"                                                           "\n"
      ""                                                            "\n"
      "void main() {"                                               "\n"
      "  vec3 pos = texelFetch(s_vb,  gl_VertexID).xyz;"            "\n"
      "  int  id  = texelFetch(s_id,  gl_VertexID).x;"              "\n"
      "  g_uv     = texelFetch(s_uv,  gl_VertexID).xy;"             "\n"
      "  vec3 xfs = texelFetch(s_xfs, id).xyz;"                     "\n"
      "  vec4 xfr = texelFetch(s_xfr, id).xyzw;"                    "\n"
      "  vec3 xft = texelFetch(s_xft, id).xyz;"                     "\n"
      ""                                                            "\n"
      "  pos *= xfs;"                                               "\n"
      "  pos  = qrot(pos, xfr);"                                    "\n"
      "  pos += xft;"                                               "\n"
      ""                                                            "\n"
      "  pos -= vec3(0, 2.5, 0);"                                   "\n"
      ""                                                            "\n"
      "  pos.x *= 0.613861;"                                        "\n"
      "  pos.y *= 1.091309;"                                        "\n"
      ""                                                            "\n"
      "  gl_Position = vec4(pos, pos.z + 0.1);"                     "\n"
      "}"                                                           "\n");

  unsigned frag = GpuProgramFragment(GPULIB_FRAGMENT_HEADER
      "layout(location = 0) in vec2 g_uv;"                          "\n"
      ""                                                            "\n"
      "layout(location = 0) out vec4 g_color;"                      "\n"
      ""                                                            "\n"
      "void main() {"                                               "\n"
      "  g_color = vec4(g_uv.x, g_uv.y, 1, 1);"                     "\n"
      "}"                                                           "\n");

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
    MeshDraw(ppo, 0, 16, textures, ib_buf, di_buf, 0, e_draw_count);
    GpuWsiSwap(dpy, win);
  }

exit:;
  XDestroyWindow(dpy, win);
  XCloseDisplay(dpy);
  return 0;
}

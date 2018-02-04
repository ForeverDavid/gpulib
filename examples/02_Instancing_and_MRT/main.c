#include "../../stdlib/stdlib.h"

void * (*ProfCalloc)(size_t, size_t);
void (*ProfFree)(void *);

//#define USE_TINYPROFILER
#define TINYPROFILER_NO_HEADER_IMPORT
#define TINYPROFILER_MAX_JSON_LINE_LENGTH 10000
#define TINYPROFILER_OUTPUT_STRING(x) stdlib_nprintf(TINYPROFILER_MAX_JSON_LINE_LENGTH, "%s", x)
#define TINYPROFILER_CALLOC ProfCalloc
#define TINYPROFILER_FREE ProfFree
#define TINYPROFILER_SNPRINTF stdlib_snprintf
#define TINYPROFILER_GETTIMEOFDAY stdlib_gettimeofday
#include "../../tinyprofiler.h"

#include "../../gpulib.h"
#include "../../gpulib_globals.h"
#include "../../gpulib_x11_wsi.h"
#include "../../gpulib_x11_wsi_globals.h"

typedef struct { float x, y, z; }    vec3;
typedef struct { float x, y, z, w; } vec4;

enum {MAX_STR = 10000};

struct {
  char mesh_ib     [MAX_STR];
  char mesh_id     [MAX_STR];
  char mesh_normals[MAX_STR];
  char mesh_uv     [MAX_STR];
  char mesh_vb     [MAX_STR];
  char textures    [MAX_STR];
  char cubemaps    [MAX_STR];
  char vs_cube     [MAX_STR];
  char fs_cube     [MAX_STR];
  char vs_mesh     [MAX_STR];
  char fs_mesh     [MAX_STR];
  char vs_quad     [MAX_STR];
  char fs_quad     [MAX_STR];
} g_resources = {
  .mesh_ib      = "meshes/MeshIB.binary",
  .mesh_id      = "meshes/MeshID.binary",
  .mesh_normals = "meshes/MeshNormals.binary",
  .mesh_uv      = "meshes/MeshUV.binary",
  .mesh_vb      = "meshes/MeshVB.binary",
  .textures     = "textures/textures.binary",
  .cubemaps     = "textures/cubemaps.binary",
  .vs_cube      = "shaders/cube.vert",
  .fs_cube      = "shaders/cube.frag",
  .vs_mesh      = "shaders/mesh.vert",
  .fs_mesh      = "shaders/mesh.frag",
  .vs_quad      = "shaders/quad.vert",
  .fs_quad      = "shaders/quad.frag"
};

static inline vec3 v3addv4(vec3 a, vec4 b) {
  return (vec3){
    a.x + b.x,
    a.y + b.y,
    a.z + b.z
  };
}

static inline vec3 v3subv4(vec3 a, vec4 b) {
  return (vec3){
    a.x - b.x,
    a.y - b.y,
    a.z - b.z
  };
}

static inline vec4 qmul(vec4 a, vec4 b) {
  return (vec4){
    a.x * b.w + b.x * a.w + (a.y * b.z - b.y * a.z),
    a.y * b.w + b.y * a.w + (a.z * b.x - b.z * a.x),
    a.z * b.w + b.z * a.w + (a.x * b.y - b.x * a.y),
    a.w * b.w - (a.x * b.x + a.y * b.y + a.z * b.z)
  };
}

static inline vec4 qinv(vec4 v) {
  return (vec4){-v.x, -v.y, -v.z, v.w};
}

static inline vec4 qrot(vec4 p, vec4 v) {
  return qmul(qmul(v, p), qinv(v));
}

static inline float sindegdiv2(float d) { return stdlib_sinf(d * (M_PI / 180.0) / 2.0); }
static inline float cosdegdiv2(float d) { return stdlib_cosf(d * (M_PI / 180.0) / 2.0); }
static inline float tandegdiv2(float d) { return stdlib_tanf(d * (M_PI / 180.0) / 2.0); }

static inline unsigned long GetTimeMs() {
  struct timeval tv;
  stdlib_gettimeofday(&tv, NULL);
  return tv.tv_sec * 1000UL + tv.tv_usec / 1000UL;
}

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
#include "../../gpulib_undefines.h"

struct gpu_cmd_t g_draw_commands[e_draw_count];

int main() {
  GpuWsiGetLibcProcedureAddresses();
  ProfCalloc = g_gpulib_libc->calloc;
  ProfFree = g_gpulib_libc->free;
  profAlloc(1000000);

  char scancodes[256 * 5] = {0};
  Display * dpy = NULL;
  Window win = 0;
  GpuWsiWindow("Instancing and MRT", sizeof("Instancing and MRT"), 1280, 720, 0, scancodes, &dpy, &win);
  GpuSetDebugCallback(GpuDebugCallback);

  profB("Mesh upload");
  unsigned di_buf = 0;
  unsigned ib_buf = 0;
  unsigned vb_tex = SimpleMeshUploadIBVB(g_resources.mesh_ib, g_resources.mesh_vb, gpu_buffer_map_flags_e, 0, 0, &di_buf, &ib_buf, NULL, (unsigned *)g_draw_commands);
  unsigned ib_tex = SimpleMeshUploadID(g_resources.mesh_id, 0, NULL);
  unsigned no_tex = SimpleMeshUploadNormals(g_resources.mesh_normals, 0, NULL);
  unsigned uv_tex = SimpleMeshUploadUV(g_resources.mesh_uv, 0, NULL);
  profE("Mesh upload");

  GpuBindCommands(di_buf);
  struct gpu_cmd_t * cmds = GpuMapCommands(0, e_draw_count);
  cmds[0].instance_count = 30;
  cmds[1].instance_count = 30;
  cmds[2].instance_count = 30;
  GpuBindCommands(0);

  unsigned instance_pos_id = 0;
  vec3 * instance_pos = GpuMalloc((30 + 30 + 30) * sizeof(vec3), &instance_pos_id);

  for (int i = 0, row = 10, space = 3; i < (30 + 30 + 30); i += 1) {
    instance_pos[i].x = (float)i * space - (i / row) * row * space;
    instance_pos[i].y = 0;
    instance_pos[i].z = ((float)i / row) * space;
  }

  unsigned instance_pos_tex = GpuView(instance_pos_id, gpu_xyz_f32_e, 0, (30 + 30 + 30) * sizeof(vec3));

  unsigned textures = GpuMallocImage(gpu_srgb_b8_e, 512, 512, 3, 4);
  unsigned skyboxes = GpuMallocCubemap(gpu_srgb_b8_e, 512, 512, 2, 1);

  GpuWsiBinaryRgbImage(textures, 512, 512, 3, g_resources.textures);
  GpuWsiBinaryRgbCubemap(skyboxes, 512, 512, 2, g_resources.cubemaps);

  unsigned mrt_msi_depth = GpuMallocMultisampledImage(gpu_d_f32_e, 1280, 720, 1, 4);
  unsigned mrt_msi_color = GpuMallocMultisampledImage(gpu_srgba_b8_e, 1280, 720, 1, 4);
  unsigned mrt_nms_color = GpuMallocImage(gpu_srgba_b8_e, 1280, 720, 1, 1);

  unsigned mrt_msi_fbo = GpuFramebuffer(mrt_msi_color, 0, 0, 0, 0, 0, 0, 0, mrt_msi_depth, 0);
  unsigned mrt_nms_fbo = GpuFramebuffer(mrt_nms_color, 0, 0, 0, 0, 0, 0, 0, 0, 0);

  unsigned smp_textures = GpuSampler(4, gpu_linear_mipmap_linear_e, gpu_linear_e, gpu_repeat_e);
  unsigned smp_mrtcolor = GpuSampler(0, gpu_nearest_e, gpu_nearest_e, gpu_clamp_to_border_e);

  unsigned mesh_vert = GpuWsiProgramVertex(g_resources.vs_mesh);
  unsigned mesh_frag = GpuWsiProgramFragment(g_resources.fs_mesh);

  unsigned quad_vert = GpuWsiProgramVertex(g_resources.vs_quad);
  unsigned quad_frag = GpuWsiProgramFragment(g_resources.fs_quad);

  unsigned cube_vert = GpuWsiProgramVertex(g_resources.vs_cube);
  unsigned cube_frag = GpuWsiProgramFragment(g_resources.fs_cube);

  unsigned mesh_ppo = GpuPipeline(mesh_vert, mesh_frag);
  unsigned quad_ppo = GpuPipeline(quad_vert, quad_frag);
  unsigned cube_ppo = GpuPipeline(cube_vert, cube_frag);

  unsigned texture_ids[16] = {
    [0] = vb_tex,
    [1] = instance_pos_tex,
    [2] = textures,
    [3] = skyboxes,
    [4] = ib_tex,
    [5] = uv_tex,
    [6] = no_tex
  };

  unsigned sampler_ids[16] = {
    [2] = smp_textures,
    [3] = smp_mrtcolor,
  };

  unsigned sky_texture_ids[16] = {
    [0] = skyboxes,
    [1] = mrt_nms_color
  };

  unsigned sky_sampler_ids[16] = {
    [0] = smp_textures,
    [1] = smp_mrtcolor
  };

  vec3 cam_pos = {26.64900f, 5.673130f, 0.f};
  vec4 cam_rot = {0.231701f,-0.351835f, 0.090335f, 0.902411f};

  float fov = 1.f / tandegdiv2(85.f);
  float fov_x = fov / (1280 / 720.f);
  float fov_y = fov;

  char key_d = 0;
  char key_a = 0;
  char key_e = 0;
  char key_q = 0;
  char key_w = 0;
  char key_s = 0;
  char key_1 = 0;
  char key_2 = 0;
  char key_3 = 0;
  char key_4 = 0;
  char key_5 = 0;
  char key_6 = 0;
  char key_7 = 0;
  char key_8 = 0;
  char key_9 = 0;
  char key_0 = 0;

  GpuWsiSetRelativeMouseMode(dpy, win, 1);

  unsigned long t_init = GetTimeMs();
  unsigned long t_prev = GetTimeMs();

  void * fence = NULL;

  for (Atom quit = XInternAtom(dpy, "WM_DELETE_WINDOW", 0);;) {
    profB("Frame");
    unsigned long t_curr = GetTimeMs();
    double dt = ((t_curr - t_prev) * 60.0) / 1000.0;

    float mx = 0, my = 0;

    profB("Events");
    for (XEvent event = {0}; XPending(dpy);) {
      XNextEvent(dpy, &event);
      switch (event.type) {
        break; case ClientMessage: {
          if (event.xclient.data.l[0] == quit) {
            profE("Events");
            profE("Frame");
            goto exit;
          }
        }
        break; case KeyPress: {
          char * scancode = &scancodes[event.xkey.keycode * 5];
          if (stdlib_nstreq(4, scancode, "AC03")) key_d = 1;
          if (stdlib_nstreq(4, scancode, "AC01")) key_a = 1;
          if (stdlib_nstreq(4, scancode, "AD03")) key_e = 1;
          if (stdlib_nstreq(4, scancode, "AD01")) key_q = 1;
          if (stdlib_nstreq(4, scancode, "AD02")) key_w = 1;
          if (stdlib_nstreq(4, scancode, "AC02")) key_s = 1;
          if (stdlib_nstreq(4, scancode, "AE01")) key_1 = 1;
          if (stdlib_nstreq(4, scancode, "AE02")) key_2 = 1;
          if (stdlib_nstreq(4, scancode, "AE03")) key_3 = 1;
          if (stdlib_nstreq(4, scancode, "AE04")) key_4 = 1;
          if (stdlib_nstreq(4, scancode, "AE05")) key_5 = 1;
          if (stdlib_nstreq(4, scancode, "AE06")) key_6 = 1;
          if (stdlib_nstreq(4, scancode, "AE07")) key_7 = 1;
          if (stdlib_nstreq(4, scancode, "AE08")) key_8 = 1;
          if (stdlib_nstreq(4, scancode, "AE09")) key_9 = 1;
          if (stdlib_nstreq(4, scancode, "AE10")) key_0 = 1;
        }
        break; case KeyRelease: {
          char * scancode = &scancodes[event.xkey.keycode * 5];
          if (stdlib_nstreq(4, scancode, "AC03")) key_d = 0;
          if (stdlib_nstreq(4, scancode, "AC01")) key_a = 0;
          if (stdlib_nstreq(4, scancode, "AD03")) key_e = 0;
          if (stdlib_nstreq(4, scancode, "AD01")) key_q = 0;
          if (stdlib_nstreq(4, scancode, "AD02")) key_w = 0;
          if (stdlib_nstreq(4, scancode, "AC02")) key_s = 0;
          if (stdlib_nstreq(4, scancode, "AE01")) key_1 = 0;
          if (stdlib_nstreq(4, scancode, "AE02")) key_2 = 0;
          if (stdlib_nstreq(4, scancode, "AE03")) key_3 = 0;
          if (stdlib_nstreq(4, scancode, "AE04")) key_4 = 0;
          if (stdlib_nstreq(4, scancode, "AE05")) key_5 = 0;
          if (stdlib_nstreq(4, scancode, "AE06")) key_6 = 0;
          if (stdlib_nstreq(4, scancode, "AE07")) key_7 = 0;
          if (stdlib_nstreq(4, scancode, "AE08")) key_8 = 0;
          if (stdlib_nstreq(4, scancode, "AE09")) key_9 = 0;
          if (stdlib_nstreq(4, scancode, "AE10")) key_0 = 0;
        }
        break; case GenericEvent: {
          if (XGetEventData(dpy, &event.xcookie) &&
              event.xcookie.evtype == XI_RawMotion)
          {
            XIRawEvent * re = event.xcookie.data;
            if (re->valuators.mask_len > 0) {
              double x = 0;
              double y = 0;
              double * values = re->raw_values;
              if (XIMaskIsSet(re->valuators.mask, 0)) { x = values[0]; values += 1; };
              if (XIMaskIsSet(re->valuators.mask, 1)) { y = values[0]; }
              mx = x;
              my = y;
            }
          }
          XFreeEventData(dpy, &event.xcookie);
        }
      }
    }
    profE("Events");

    profB("Camera");
    mx *= 0.1f;
    my *= 0.1f;
    cam_rot = qmul(cam_rot, (vec4){sindegdiv2(my), 0, 0, cosdegdiv2(my)});
    cam_rot = qmul((vec4){0, sindegdiv2(mx), 0, cosdegdiv2(mx)}, cam_rot);

    if (key_d) cam_pos = v3addv4(cam_pos, qrot((vec4){0.05f, 0, 0}, cam_rot));
    if (key_a) cam_pos = v3subv4(cam_pos, qrot((vec4){0.05f, 0, 0}, cam_rot));
    if (key_e) cam_pos = v3addv4(cam_pos, qrot((vec4){0, 0.05f, 0}, cam_rot));
    if (key_q) cam_pos = v3subv4(cam_pos, qrot((vec4){0, 0.05f, 0}, cam_rot));
    if (key_w) cam_pos = v3addv4(cam_pos, qrot((vec4){0, 0, 0.05f}, cam_rot));
    if (key_s) cam_pos = v3subv4(cam_pos, qrot((vec4){0, 0, 0.05f}, cam_rot));
    profE("Camera");

    static int show_pass = 0;
    if (key_1) show_pass = 1;
    if (key_2) show_pass = 2;
    if (key_3) show_pass = 3;
    if (key_4) show_pass = 4;
    if (key_5) show_pass = 5;
    if (key_6) show_pass = 6;
    if (key_7) show_pass = 7;
    if (key_8) show_pass = 8;

    profB("Uniforms");
    static int cube_index = 0;
    if (key_9) { cube_index = 1; show_pass = 0; }
    if (key_0) { cube_index = 0; show_pass = 0; }

    GpuUniformFloat4(mesh_vert, 0, 1, (float [4]){cam_pos.x, cam_pos.y, cam_pos.z, 0});
    GpuUniformFloat4(mesh_vert, 1, 1, &cam_rot.x);
    GpuUniformFloat4(mesh_vert, 2, 1, (float [4]){fov_x, fov_y, 0, 0});

    GpuUniformFloat4(mesh_frag, 0, 1, (float [4]){cam_pos.x, cam_pos.y, cam_pos.z, 0});
    GpuUniformInt(mesh_frag, 1, 1, &show_pass);
    GpuUniformInt(mesh_frag, 2, 1, &cube_index);

    GpuUniformFloat4(cube_vert, 0, 1, &cam_rot.x);
    GpuUniformFloat4(cube_vert, 1, 1, (float [4]){fov_x, fov_y, 0, 0});

    GpuUniformInt(cube_frag, 0, 1, &cube_index);

    GpuUniformFloat4(quad_frag, 0, 1, (float [4]){(t_curr - t_init) / 1000.f, 0, 0, 0});
    profE("Uniforms");

    profB("Instance pos update");
    for (; fence != NULL && GpuFenceIsComplete(fence) == 0;) {}
    for (int i = 0; i < (30 + 30 + 30); i += 1)
      instance_pos[i].y = stdlib_sinf((t_curr - t_init) * 0.0015 + i * 0.5) * 0.3;
    profE("Instance pos update");

    GpuBindFramebuffer(mrt_msi_fbo);
    GpuClear();
    if (!show_pass) {
      GpuBindPipeline(cube_ppo);
      GpuBindTextures(0, 16, sky_texture_ids);
      GpuBindSamplers(0, 16, sky_sampler_ids);
      GpuDisable(gpu_depth_e);
      GpuDraw(gpu_triangles_e, 0, 36, 1);
      GpuEnable(gpu_depth_e);
    }
    GpuBindPipeline(mesh_ppo);
    GpuBindTextures(0, 16, texture_ids);
    GpuBindSamplers(0, 16, sampler_ids);
    GpuBindIndices(ib_buf);
    GpuBindCommands(di_buf);
    GpuDrawIndirect(gpu_triangles_e, 0, e_draw_count);
    fence = GpuFence();
    GpuBindFramebuffer(0);

    GpuBlit(mrt_msi_fbo, 0, 0, 0, 1280, 720,
            mrt_nms_fbo, 0, 0, 0, 1280, 720);

    GpuClear();
    GpuBindPipeline(quad_ppo);
    GpuDraw(gpu_triangles_e, 0, 3, 1);

    GpuWsiSwap(dpy, win);

    t_prev = t_curr;
    profE("Frame");
  }

exit:;
  XDestroyWindow(dpy, win);
  XCloseDisplay(dpy);
  profPrintAndFree();
  return 0;
}

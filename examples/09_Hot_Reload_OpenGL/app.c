#include "api.h"

typedef struct { float x, y, z; } vec3;

struct state_t {
  unsigned           vertices_id;
  vec3             * vertices;
  unsigned           cast_tex[4096];
  unsigned           indices_id;
  unsigned         * indices;
  unsigned           commands_id;
  struct gpu_cmd_t * commands;
  unsigned           textures[16];
  char               vert_string[4096];
  char               frag_string[4096];
  unsigned           vert;
  unsigned           frag;
  unsigned           ppo;
};

struct state_t * s = NULL;

enum {
  cast_tex_vertices_e,
};

static void * AppInit(Display * dpy, Window win, char * scancodes,
    struct gpu_libc_t * gpulib_libc,
    struct gpu_libgl_t * gpulib_libgl,
    struct gpu_libglx_t * gpulib_libglx,
    struct gpu_debug_state_t * gpulib_debug_state,
    struct ig_state_t * ig_state,
    struct ImGuiContext * ig_context)
{
  void * state = stdlib_mmap(0, 256L * 1024L * 1024L * 1024L, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE | MAP_NORESERVE, -1, 0);
  s = state;

  g_gpulib_libc = gpulib_libc;
  g_gpulib_libgl = gpulib_libgl;
  g_gpulib_libglx = gpulib_libglx;
  g_gpulib_debug_state = gpulib_debug_state;
  g_ig_state = ig_state;
  igSetCurrentContext(ig_context);

  s->vertices = GpuCalloc(4096 * sizeof(vec3), &s->vertices_id);
  s->indices  = GpuCallocIndices(4096, &s->indices_id);
  s->commands = GpuCallocCommands(4096, &s->commands_id);

  char vert_string[4096] = GPULIB_VERT_HEADER
      "layout(binding = 0) uniform samplerBuffer s_pos;" "\n"
      ""                                                 "\n"
      "void main() {"                                    "\n"
      "  vec3 pos = texelFetch(s_pos, gl_VertexID).xyz;" "\n"
      "  gl_Position = vec4(pos, 1);"                    "\n"
      "}"                                                "\n";

  char frag_string[4096] = GPULIB_FRAG_HEADER
      "layout(location = 0) out vec4 g_color;" "\n"
      ""                                       "\n"
      "void main() {"                          "\n"
      "  g_color = vec4(1, 0, 1, 1);"          "\n"
      "}"                                      "\n";

  for (int i = 0; i < 4096; i += 1)
    s->vert_string[i] = vert_string[i];

  for (int i = 0; i < 4096; i += 1)
    s->frag_string[i] = frag_string[i];

  s->vert = GpuVert(s->vert_string);
  s->frag = GpuFrag(s->frag_string);
  s->ppo = GpuPpo(s->vert, s->frag);

  return state;
}

static void AppLoad(void * state, Display * dpy, Window win, char * scancodes,
    struct gpu_libc_t * gpulib_libc,
    struct gpu_libgl_t * gpulib_libgl,
    struct gpu_libglx_t * gpulib_libglx,
    struct gpu_debug_state_t * gpulib_debug_state,
    struct ig_state_t * ig_state,
    struct ImGuiContext * ig_context)
{
  s = state;

  g_gpulib_libc = gpulib_libc;
  g_gpulib_libgl = gpulib_libgl;
  g_gpulib_libglx = gpulib_libglx;
  g_gpulib_debug_state = gpulib_debug_state;
  g_ig_state = ig_state;
  igSetCurrentContext(ig_context);

  s->vertices[0] = (vec3){ 0.0,  0.5, 0.0};
  s->vertices[1] = (vec3){ 0.5, -0.5, 0.0};
  s->vertices[2] = (vec3){-0.5, -0.5, 0.0};

  s->indices[0] = 0;
  s->indices[1] = 1;
  s->indices[2] = 2;

  s->commands[0].count = 3;
  s->commands[0].instance_count = 1;

  s->cast_tex[cast_tex_vertices_e] = GpuCast(s->vertices_id, gpu_xyz_f32_e, 0, 3 * sizeof(vec3));

  s->textures[0] = s->cast_tex[cast_tex_vertices_e];
}

static int AppStep(void * state, Display * dpy, Window win, char * scancodes) {
  s = state;

  for (XEvent event = {0}; XPending(dpy);) {
    XNextEvent(dpy, &event);
    ImguiProcessEvent(&event);
    switch (event.type) {
      break; case ClientMessage: {
        if (event.xclient.data.l[0] == XInternAtom(dpy, "WM_DELETE_WINDOW", 0))
          return 1;
      }
    }
  }

  ImguiNewFrame();

  if (GpuDebugFrag(&s->frag, s->frag_string, sizeof(s->frag_string))) {
    g_gpulib_libgl->DeleteProgramPipelines(1, &s->ppo);
    s->ppo = GpuPpo(s->vert, s->frag);
  }

  GpuClear();
  GpuBindPpo(s->ppo);
  GpuBindTextures(0, 16, s->textures);
  GpuBindIndices(s->indices_id);
  GpuBindCommands(s->commands_id);
  GpuDraw(gpu_triangles_e, 0, 1);

  igRender();
  GpuSwap(dpy, win);

  return 0;
}

static void AppUnload(void * state) {
  s = state;

  g_gpulib_libgl->DeleteTextures(4096, s->cast_tex);
}

static void AppDeinit(void * state) {
  s = state;

  stdlib_munmap(state, 256L * 1024L * 1024L * 1024L);
}

struct api_t APP_API = {
  .Init   = AppInit,
  .Load   = AppLoad,
  .Step   = AppStep,
  .Unload = AppUnload,
  .Deinit = AppDeinit
};

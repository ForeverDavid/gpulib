#pragma once

#include <X11/extensions/Xrender.h>
#include <X11/extensions/XInput2.h>
#include <X11/XKBlib.h>

struct XVisualInfo {
  void * visual;
  VisualID visualid;
  int screen;
  int depth;
  int class;
  unsigned long red_mask;
  unsigned long green_mask;
  unsigned long blue_mask;
  int colormap_size;
  int bits_per_rgb;
};

struct MWMHints {
 long flags;
 long functions;
 long decorations;
 long input_mode;
 long status;
};

#define MWM_HINTS_FUNCTIONS     (1L << 0)
#define MWM_HINTS_DECORATIONS   (1L << 1)
#define MWM_HINTS_INPUT_MODE    (1L << 2)
#define MWM_HINTS_STATUS        (1L << 3)

#define MWM_FUNC_ALL            (1L << 0)
#define MWM_FUNC_RESIZE         (1L << 1)
#define MWM_FUNC_MOVE           (1L << 2)
#define MWM_FUNC_MINIMIZE       (1L << 3)
#define MWM_FUNC_MAXIMIZE       (1L << 4)
#define MWM_FUNC_CLOSE          (1L << 5)

#define MWM_DECOR_ALL           (1L << 0)
#define MWM_DECOR_BORDER        (1L << 1)
#define MWM_DECOR_RESIZEH       (1L << 2)
#define MWM_DECOR_TITLE         (1L << 3)
#define MWM_DECOR_MENU          (1L << 4)
#define MWM_DECOR_MINIMIZE      (1L << 5)
#define MWM_DECOR_MAXIMIZE      (1L << 6)

#define MWM_INPUT_MODELESS 0
#define MWM_INPUT_PRIMARY_APPLICATION_MODAL 1
#define MWM_INPUT_SYSTEM_MODAL 2
#define MWM_INPUT_FULL_APPLICATION_MODAL 3
#define MWM_INPUT_APPLICATION_MODAL MWM_INPUT_PRIMARY_APPLICATION_MODAL

#define MWM_TEAROFF_WINDOW      (1L<<0)

struct gpu_libc_t {
  int (*access)(char *, int);
  void * (*calloc)(size_t, size_t);
  int (*fgetc)(int *);
  void (*free)(void *);
  pid_t (*getpid)();
  int (*pclose)(int *);
  int * (*popen)(char *, char *);
  ssize_t (*readlink)(char *, char *, size_t);
  void * (*realloc)(void *, size_t);
  char * (*setlocale)(int, char *);
  char * (*strcat)(char *, char *);
  int (*strcmp)(char *, char *);
  size_t (*strlen)(char *);
  char * (*strndup)(char *, size_t);
  char * (*strrchr)(char *, int);
  long (*strtol)(char *, char **, int);
  int (*usleep)(unsigned);
} g_gpulib_libc_data = {0};

struct gpu_libc_t * g_gpulib_libc = &g_gpulib_libc_data;

struct gpu_libglx_t {
  void ** (*ChooseFBConfig)(Display *, int, int *, int *);
  int (*GetFBConfigAttrib)(Display *, void *, int, int *);
  void * (*GetProcAddressARB)(char *);
  struct XVisualInfo * (*GetVisualFromFBConfig)(Display *, void *);
  int (*MakeContextCurrent)(Display *, XID, XID, void *);
  void (*SwapBuffers)(Display *, XID);
} g_gpulib_libglx_data = {0};

struct gpu_libglx_t * g_gpulib_libglx = &g_gpulib_libglx_data;

static inline void GpuWsiGetLibcProcedureAddresses() {
  __auto_type libc = g_gpulib_libc;
  libc->access = dlsym(NULL, "access");
  libc->calloc = dlsym(NULL, "calloc");
  libc->fgetc = dlsym(NULL, "fgetc");
  libc->free = dlsym(NULL, "free");
  libc->getpid = dlsym(NULL, "getpid");
  libc->pclose = dlsym(NULL, "pclose");
  libc->popen = dlsym(NULL, "popen");
  libc->readlink = dlsym(NULL, "readlink");
  libc->realloc = dlsym(NULL, "realloc");
  libc->setlocale = dlsym(NULL, "setlocale");
  libc->strcat = dlsym(NULL, "strcat");
  libc->strcmp = dlsym(NULL, "strcmp");
  libc->strlen = dlsym(NULL, "strlen");
  libc->strndup = dlsym(NULL, "strndup");
  libc->strrchr = dlsym(NULL, "strrchr");
  libc->strtol = dlsym(NULL, "strtol");
  libc->usleep = dlsym(NULL, "usleep");
}

static inline void GpuWsiGetGLXProcedureAddresses() {
  __auto_type glx = g_gpulib_libglx;
  void * libgl = dlopen("libGL.so", 1);
  glx->ChooseFBConfig = dlsym(libgl, "glXChooseFBConfig");
  glx->GetFBConfigAttrib = dlsym(libgl, "glXGetFBConfigAttrib");
  glx->GetProcAddressARB = dlsym(libgl, "glXGetProcAddressARB");
  glx->GetVisualFromFBConfig = dlsym(libgl, "glXGetVisualFromFBConfig");
  glx->MakeContextCurrent = dlsym(libgl, "glXMakeContextCurrent");
  glx->SwapBuffers = dlsym(libgl, "glXSwapBuffers");
}

static inline void GpuWsiGetGLProcedureAddresses() {
  __auto_type gl = g_gpulib_libgl;
  __auto_type glx = g_gpulib_libglx;
  gl->AttachShader = glx->GetProcAddressARB("glAttachShader");
  gl->BeginQuery = glx->GetProcAddressARB("glBeginQuery");
  gl->BeginTransformFeedback = glx->GetProcAddressARB("glBeginTransformFeedback");
  gl->BindBuffer = glx->GetProcAddressARB("glBindBuffer");
  gl->BindFramebuffer = glx->GetProcAddressARB("glBindFramebuffer");
  gl->BindProgramPipeline = glx->GetProcAddressARB("glBindProgramPipeline");
  gl->BindSamplers = glx->GetProcAddressARB("glBindSamplers");
  gl->BindTextures = glx->GetProcAddressARB("glBindTextures");
  gl->BindTransformFeedback = glx->GetProcAddressARB("glBindTransformFeedback");
  gl->BindVertexArray = glx->GetProcAddressARB("glBindVertexArray");
  gl->BlendFunc = glx->GetProcAddressARB("glBlendFunc");
  gl->BlitNamedFramebuffer = glx->GetProcAddressARB("glBlitNamedFramebuffer");
  gl->BufferStorage = glx->GetProcAddressARB("glBufferStorage");
  gl->Clear = glx->GetProcAddressARB("glClear");
  gl->ClearDepth = glx->GetProcAddressARB("glClearDepth");
  gl->ClearTexSubImage = glx->GetProcAddressARB("glClearTexSubImage");
  gl->ClipControl = glx->GetProcAddressARB("glClipControl");
  gl->CompileShader = glx->GetProcAddressARB("glCompileShader");
  gl->CreateBuffers = glx->GetProcAddressARB("glCreateBuffers");
  gl->CreateFramebuffers = glx->GetProcAddressARB("glCreateFramebuffers");
  gl->CreateProgram = glx->GetProcAddressARB("glCreateProgram");
  gl->CreateProgramPipelines = glx->GetProcAddressARB("glCreateProgramPipelines");
  gl->CreateSamplers = glx->GetProcAddressARB("glCreateSamplers");
  gl->CreateShader = glx->GetProcAddressARB("glCreateShader");
  gl->CreateTextures = glx->GetProcAddressARB("glCreateTextures");
  gl->CreateTransformFeedbacks = glx->GetProcAddressARB("glCreateTransformFeedbacks");
  gl->CreateVertexArrays = glx->GetProcAddressARB("glCreateVertexArrays");
  gl->DebugMessageCallback = glx->GetProcAddressARB("glDebugMessageCallback");
  gl->DeleteBuffers = glx->GetProcAddressARB("glDeleteBuffers");
  gl->DeleteFramebuffers = glx->GetProcAddressARB("glDeleteFramebuffers");
  gl->DeleteProgram = glx->GetProcAddressARB("glDeleteProgram");
  gl->DeleteProgramPipelines = glx->GetProcAddressARB("glDeleteProgramPipelines");
  gl->DeleteQueries = glx->GetProcAddressARB("glDeleteQueries");
  gl->DeleteSamplers = glx->GetProcAddressARB("glDeleteSamplers");
  gl->DeleteShader = glx->GetProcAddressARB("glDeleteShader");
  gl->DeleteSync = glx->GetProcAddressARB("glDeleteSync");
  gl->DeleteTextures = glx->GetProcAddressARB("glDeleteTextures");
  gl->DeleteTransformFeedbacks = glx->GetProcAddressARB("glDeleteTransformFeedbacks");
  gl->DepthFunc = glx->GetProcAddressARB("glDepthFunc");
  gl->DepthRange = glx->GetProcAddressARB("glDepthRange");
  gl->DetachShader = glx->GetProcAddressARB("glDetachShader");
  gl->Disable = glx->GetProcAddressARB("glDisable");
  gl->DrawArraysInstanced = glx->GetProcAddressARB("glDrawArraysInstanced");
  gl->Enable = glx->GetProcAddressARB("glEnable");
  gl->EndQuery = glx->GetProcAddressARB("glEndQuery");
  gl->EndTransformFeedback = glx->GetProcAddressARB("glEndTransformFeedback");
  gl->FenceSync = glx->GetProcAddressARB("glFenceSync");
  gl->FrontFace = glx->GetProcAddressARB("glFrontFace");
  gl->GenBuffers = glx->GetProcAddressARB("glGenBuffers");
  gl->GenerateTextureMipmap = glx->GetProcAddressARB("glGenerateTextureMipmap");
  gl->GenQueries = glx->GetProcAddressARB("glGenQueries");
  gl->GenTextures = glx->GetProcAddressARB("glGenTextures");
  gl->GetIntegerv = glx->GetProcAddressARB("glGetIntegerv");
  gl->GetProgramInfoLog = glx->GetProcAddressARB("glGetProgramInfoLog");
  gl->GetProgramiv = glx->GetProcAddressARB("glGetProgramiv");
  gl->GetQueryObjectui64v = glx->GetProcAddressARB("glGetQueryObjectui64v");
  gl->GetShaderInfoLog = glx->GetProcAddressARB("glGetShaderInfoLog");
  gl->GetShaderiv = glx->GetProcAddressARB("glGetShaderiv");
  gl->GetStringi = glx->GetProcAddressARB("glGetStringi");
  gl->GetSynciv = glx->GetProcAddressARB("glGetSynciv");
  gl->GetTextureLevelParameteriv = glx->GetProcAddressARB("glGetTextureLevelParameteriv");
  gl->GetTextureSubImage = glx->GetProcAddressARB("glGetTextureSubImage");
  gl->LinkProgram = glx->GetProcAddressARB("glLinkProgram");
  gl->MapBufferRange = glx->GetProcAddressARB("glMapBufferRange");
  gl->MapNamedBufferRange = glx->GetProcAddressARB("glMapNamedBufferRange");
  gl->MultiDrawElementsIndirect = glx->GetProcAddressARB("glMultiDrawElementsIndirect");
  gl->NamedBufferStorage = glx->GetProcAddressARB("glNamedBufferStorage");
  gl->NamedFramebufferDrawBuffer = glx->GetProcAddressARB("glNamedFramebufferDrawBuffer");
  gl->NamedFramebufferDrawBuffers = glx->GetProcAddressARB("glNamedFramebufferDrawBuffers");
  gl->NamedFramebufferReadBuffer = glx->GetProcAddressARB("glNamedFramebufferReadBuffer");
  gl->NamedFramebufferTextureLayer = glx->GetProcAddressARB("glNamedFramebufferTextureLayer");
  gl->ProgramParameteri = glx->GetProcAddressARB("glProgramParameteri");
  gl->ProgramUniform1iv = glx->GetProcAddressARB("glProgramUniform1iv");
  gl->ProgramUniform4fv = glx->GetProcAddressARB("glProgramUniform4fv");
  gl->SamplerParameteri = glx->GetProcAddressARB("glSamplerParameteri");
  gl->Scissor = glx->GetProcAddressARB("glScissor");
  gl->ShaderSource = glx->GetProcAddressARB("glShaderSource");
  gl->TextureBufferRange = glx->GetProcAddressARB("glTextureBufferRange");
  gl->TextureStorage3D = glx->GetProcAddressARB("glTextureStorage3D");
  gl->TextureStorage3DMultisample = glx->GetProcAddressARB("glTextureStorage3DMultisample");
  gl->TextureSubImage3D = glx->GetProcAddressARB("glTextureSubImage3D");
  gl->TextureView = glx->GetProcAddressARB("glTextureView");
  gl->TransformFeedbackBufferRange = glx->GetProcAddressARB("glTransformFeedbackBufferRange");
  gl->TransformFeedbackVaryings = glx->GetProcAddressARB("glTransformFeedbackVaryings");
  gl->UseProgramStages = glx->GetProcAddressARB("glUseProgramStages");
  gl->Viewport = glx->GetProcAddressARB("glViewport");
}

static inline long GpuWsiShell(char * cmd, char * out) {
  __auto_type libc = g_gpulib_libc;
  int * ret = libc->popen(cmd, "r");
  long i = 0;
  for (int c = libc->fgetc(ret); c != -1; i += 1) {
    if (out) out[i] = (char)c;
    c = libc->fgetc(ret);
  }
  if (out) out[i] = 0;
  libc->pclose(ret);
  return i + 1;
}

static inline char * GpuWsiReadSymLink(char * path) {
  __auto_type libc = g_gpulib_libc;
  char * retval = NULL;
  ssize_t len = 64;
  ssize_t rc = -1;
  for (;;) {
    char * ptr = libc->realloc(retval, (size_t)len);
    retval = ptr;
    rc = libc->readlink(path, retval, len);
    if (rc == -1) {
      break;
    } else if (rc < len) {
      retval[rc] = '\0';
      return retval;
    }
    len *= 2;
  }
  libc->free(retval);
  return NULL;
}

static inline char * GpuWsiGetBasePath() {
  __auto_type libc = g_gpulib_libc;
  char * retval = NULL;
  if (retval == NULL && (libc->access("/proc", 0) == 0)) {
    retval = GpuWsiReadSymLink("/proc/self/exe");
    if (retval == NULL) {
      char path[64] = {0};
      int rc = stdlib_snprintf(path, sizeof(path), "/proc/%llu/exe", (unsigned long long)libc->getpid());
      if ((rc > 0) && (rc < sizeof(path)))
        retval = GpuWsiReadSymLink(path);
    }
  }
  if (retval != NULL) {
    char * ptr = libc->strrchr(retval, '/');
    if (ptr != NULL) {
      *(ptr + 1) = '\0';
    } else {
      libc->free(retval);
      retval = NULL;
    }
  }
  if (retval != NULL) {
    char * ptr = libc->realloc(retval, libc->strlen(retval) + 1);
    if (ptr != NULL)
      retval = ptr;
  }
  return retval;
}

static inline void GpuWsiSetRelativeMouseMode(Display * dpy, Window win, int enabled) {
  __auto_type libc = g_gpulib_libc;
  if (enabled) {
    XColor black = {0};
    char nil[8]  = {0};
    Pixmap bitmap = XCreateBitmapFromData(dpy, win, nil, 8, 8);
    Cursor cursor = XCreatePixmapCursor(dpy, bitmap, bitmap, &black, &black, 0, 0);
    XDefineCursor(dpy, win, cursor);
    XFreeCursor(dpy, cursor);
    XFreePixmap(dpy, bitmap);
    for (int attempts = 0; attempts < 100; attempts += 1) {
      int result = XGrabPointer(
        dpy, win, True, ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask,
        GrabModeAsync, GrabModeAsync, win, None, CurrentTime);
      if (result == GrabSuccess)
        break;
      libc->usleep(50 * 1000);
    }
  } else {
    XUndefineCursor(dpy, win);
    XUngrabPointer(dpy, CurrentTime);
  }
}

static inline int GpuWsiIsExtensionSupported(char * extension) {
  __auto_type gl = g_gpulib_libgl;
  __auto_type libc = g_gpulib_libc;
  int num_extensions = 0;
  gl->GetIntegerv(0x821D, &num_extensions); // GL_NUM_EXTENSIONS
  for (int i = 0; i < num_extensions; i += 1) {
    char * ext = gl->GetStringi(0x1F03, i); // GL_EXTENSIONS
    if (libc->strcmp(ext, extension) == 0)
      return 1;
  }
  return 0;
}

static inline void GpuWsiCheckExtensions(int extension_count, char ** extensions) {
  profB(__func__);
  for (int i = 0; i < extension_count; i += 1) {
    if (GpuWsiIsExtensionSupported(extensions[i]) == 0) {
      char cmd[GPULIB_MAX_PRINT_BYTES];
      stdlib_snprintf(cmd, GPULIB_MAX_PRINT_BYTES, "notify-send \"[GpuLib] Error: %s is not supported.\"", extensions[i]);
      GpuWsiShell(cmd, NULL);
    }
  }
  profE(__func__);
}

static inline void GpuWsiX11Window(char * title, int title_bytes, int x, int y, int w, int h, int msaa_sample_count, Display ** out_display, Window * out_window) {
  __auto_type glx = g_gpulib_libglx;
  __auto_type libc = g_gpulib_libc;
  
  profB("Load libGL.so");
  GpuWsiGetGLXProcedureAddresses();
  profE("Load libGL.so");

  profB("Set locale");
  libc->setlocale(6, ""); // LC_ALL
  if (XSupportsLocale())
    XSetLocaleModifiers("@im=none");
  profE("Set locale");

  profB("XOpenDisplay");
  Display * dpy = XOpenDisplay(NULL);
  profE("XOpenDisplay");
  stdlib_assert(dpy != NULL);

  void * fbconfig = NULL;
  struct XVisualInfo * visual = NULL;
  {
    int glx_attribs[25] = {0};
    int glx_attribs_with_msaa[25] = {
      0x8010, 0x00000001, // GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT
      0x8011, 0x00000001, // GLX_RENDER_TYPE, GLX_RGBA_BIT
      0x8012, 1, // GLX_X_RENDERABLE
      5,      1, // GLX_DOUBLEBUFFER
      8,      8, // GLX_RED_SIZE
      9,      8, // GLX_GREEN_SIZE
      10,     8, // GLX_BLUE_SIZE
      11,     8, // GLX_ALPHA_SIZE
      12,     24, // GLX_DEPTH_SIZE
      13,     8, // GLX_STENCIL_SIZE
      100000, 1, // GLX_SAMPLE_BUFFERS
      100001, msaa_sample_count, // GLX_SAMPLES
      None
    };
    int glx_attribs_without_msaa[25] = {
      0x8010, 0x00000001, // GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT
      0x8011, 0x00000001, // GLX_RENDER_TYPE, GLX_RGBA_BIT
      0x8012, 1, // GLX_X_RENDERABLE
      5,      1, // GLX_DOUBLEBUFFER
      8,      8, // GLX_RED_SIZE
      9,      8, // GLX_GREEN_SIZE
      10,     8, // GLX_BLUE_SIZE
      11,     8, // GLX_ALPHA_SIZE
      12,     24, // GLX_DEPTH_SIZE
      13,     8, // GLX_STENCIL_SIZE
      None
    };
    memcpy(glx_attribs, msaa_sample_count > 0 ? glx_attribs_with_msaa : glx_attribs_without_msaa, 25 * sizeof(int));
    int fbconfigs_count = 0;
    profB("glx->ChooseFBConfig");
    void ** fbconfigs = glx->ChooseFBConfig(dpy, DefaultScreen(dpy), glx_attribs, &fbconfigs_count);
    profE("glx->ChooseFBConfig");
    stdlib_assert(fbconfigs_count != 0);
    stdlib_assert(fbconfigs != NULL);
    profB("fbconfig search");
    for (int i = fbconfigs_count - 1; i >= 0; i -= 1) {
#if 0
      {
        int red_size = 0, green_size = 0, blue_size = 0, alpha_size = 0, depth_size = 0, stencil_size = 0, doublebuffer = 0, sample_buffers = 0, samples = 0;
        glx->GetFBConfigAttrib(dpy, fbconfigs[i], GLX_RED_SIZE,       &red_size);
        glx->GetFBConfigAttrib(dpy, fbconfigs[i], GLX_GREEN_SIZE,     &green_size);
        glx->GetFBConfigAttrib(dpy, fbconfigs[i], GLX_BLUE_SIZE,      &blue_size);
        glx->GetFBConfigAttrib(dpy, fbconfigs[i], GLX_ALPHA_SIZE,     &alpha_size);
        glx->GetFBConfigAttrib(dpy, fbconfigs[i], GLX_DEPTH_SIZE,     &depth_size);
        glx->GetFBConfigAttrib(dpy, fbconfigs[i], GLX_STENCIL_SIZE,   &stencil_size);
        glx->GetFBConfigAttrib(dpy, fbconfigs[i], GLX_DOUBLEBUFFER,   &doublebuffer);
        glx->GetFBConfigAttrib(dpy, fbconfigs[i], GLX_SAMPLE_BUFFERS, &sample_buffers);
        glx->GetFBConfigAttrib(dpy, fbconfigs[i], GLX_SAMPLES,        &samples);
        stdlib_nprintf(GPULIB_MAX_PRINT_BYTES,
          "fbconfigs[%d]: %p, "
          "GLX_RED_SIZE: %d, "
          "GLX_GREEN_SIZE: %d, "
          "GLX_BLUE_SIZE: %d, "
          "GLX_ALPHA_SIZE: %d, "
          "GLX_DEPTH_SIZE: %d, "
          "GLX_STENCIL_SIZE: %d, "
          "GLX_DOUBLEBUFFER: %d, "
          "GLX_SAMPLE_BUFFERS: %d, "
          "GLX_SAMPLES: %d\n",
          i, fbconfigs[i],
          red_size,
          green_size,
          blue_size,
          alpha_size,
          depth_size,
          stencil_size,
          doublebuffer,
          sample_buffers,
          samples);
      }
#endif
      XFree(visual);
      visual = glx->GetVisualFromFBConfig(dpy, fbconfigs[i]);
      if (visual == NULL)
        continue;
      XRenderPictFormat * format = XRenderFindVisualFormat(dpy, visual->visual);
      if (format == NULL)
        continue;
      fbconfig = fbconfigs[i];
#if 0
      if (format->direct.alphaMask > 0)
        break;
#endif
    }
    XFree(fbconfigs);
    profE("fbconfig search");
  }
  stdlib_assert(fbconfig != NULL);

#if 0
  {
    int red_size = 0, green_size = 0, blue_size = 0, alpha_size = 0, depth_size = 0, stencil_size = 0, doublebuffer = 0, sample_buffers = 0, samples = 0;
    glx->GetFBConfigAttrib(dpy, fbconfig, GLX_RED_SIZE,       &red_size);
    glx->GetFBConfigAttrib(dpy, fbconfig, GLX_GREEN_SIZE,     &green_size);
    glx->GetFBConfigAttrib(dpy, fbconfig, GLX_BLUE_SIZE,      &blue_size);
    glx->GetFBConfigAttrib(dpy, fbconfig, GLX_ALPHA_SIZE,     &alpha_size);
    glx->GetFBConfigAttrib(dpy, fbconfig, GLX_DEPTH_SIZE,     &depth_size);
    glx->GetFBConfigAttrib(dpy, fbconfig, GLX_STENCIL_SIZE,   &stencil_size);
    glx->GetFBConfigAttrib(dpy, fbconfig, GLX_DOUBLEBUFFER,   &doublebuffer);
    glx->GetFBConfigAttrib(dpy, fbconfig, GLX_SAMPLE_BUFFERS, &sample_buffers);
    glx->GetFBConfigAttrib(dpy, fbconfig, GLX_SAMPLES,        &samples);
    stdlib_nprintf(GPULIB_MAX_PRINT_BYTES,
      "fbconfig: %p, "
      "GLX_RED_SIZE: %d, "
      "GLX_GREEN_SIZE: %d, "
      "GLX_BLUE_SIZE: %d, "
      "GLX_ALPHA_SIZE: %d, "
      "GLX_DEPTH_SIZE: %d, "
      "GLX_STENCIL_SIZE: %d, "
      "GLX_DOUBLEBUFFER: %d, "
      "GLX_SAMPLE_BUFFERS: %d, "
      "GLX_SAMPLES: %d\n",
      fbconfig,
      red_size,
      green_size,
      blue_size,
      alpha_size,
      depth_size,
      stencil_size,
      doublebuffer,
      sample_buffers,
      samples);
  }
#endif

  Window win = 0;
  {
    XSetWindowAttributes win_attrs = {0};
    profB("XCreateColormap");
    Colormap colormap = XCreateColormap(dpy, DefaultRootWindow(dpy), visual->visual, AllocNone);
    profE("XCreateColormap");
    win_attrs.colormap          = colormap;
    win_attrs.background_pixmap = None;
    win_attrs.border_pixmap     = None;
    win_attrs.border_pixel      = 0;
    win_attrs.event_mask        =
        ExposureMask
      | StructureNotifyMask
      | KeyPressMask
      | KeyReleaseMask
      | ButtonPressMask
      | ButtonReleaseMask
      | ButtonMotionMask
      | Button1MotionMask
      | Button2MotionMask
      | Button3MotionMask
      | Button4MotionMask
      | Button5MotionMask
      | PointerMotionMask;
    profB("XCreateWindow");
    win = XCreateWindow(
      dpy,
      DefaultRootWindow(dpy),
      x, y, w, h,
      0,
      visual->depth,
      InputOutput,
      visual->visual,
      CWBorderPixel | CWColormap | CWEventMask,
      &win_attrs);
    profE("XCreateWindow");
    XFree(visual);
    visual = NULL;
    stdlib_assert(win != 0);
  }

  {
    XTextProperty win_title = {0};
    win_title.value    = (unsigned char *)title;
    win_title.encoding = XInternAtom(dpy, "UTF8_STRING", 1);
    win_title.format   = 8;
    win_title.nitems   = title_bytes;
    XSizeHints hints = {0};
    hints.x      = x;
    hints.y      = y;
    hints.width  = w;
    hints.height = h;
    hints.flags  = USPosition | USSize;
    XWMHints startup_state = {0};
    startup_state.initial_state = NormalState;
    startup_state.flags         = StateHint;
    profB("XSetWMProperties");
    XSetWMProperties(dpy, win, &win_title, &win_title, NULL, 0, &hints, &startup_state, NULL);
    profE("XSetWMProperties");
  }

  {
    profB("XInternAtom _MOTIF_WM_HINTS");
    Atom MOTIF_WM_HINTS = XInternAtom(dpy, "_MOTIF_WM_HINTS", 0);
    profE("XInternAtom _MOTIF_WM_HINTS");
    struct MWMHints hints = {0};
    hints.flags       = MWM_HINTS_FUNCTIONS | MWM_HINTS_DECORATIONS;
    hints.functions   = MWM_FUNC_ALL;
    hints.decorations = MWM_DECOR_ALL;
    profB("XChangeProperty");
    XChangeProperty(
      dpy, win,
      MOTIF_WM_HINTS,
      MOTIF_WM_HINTS, 32,
      PropModeReplace,
      (unsigned char *)&hints,
      sizeof(struct MWMHints) / sizeof(long)
    );
    profE("XChangeProperty");
  }

  void * glx_ctx = NULL;
  {
    void * (*glXCreateContextAttribsARB)(Display *, void *, void *, int, int *) = glx->GetProcAddressARB("glXCreateContextAttribsARB");
    stdlib_assert(glXCreateContextAttribsARB != NULL);
    int attribs[] = {
      0x2091, 3, // GLX_CONTEXT_MAJOR_VERSION_ARB
      0x2092, 3, // GLX_CONTEXT_MINOR_VERSION_ARB
      0x9126, 0x00000001, // GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB
      None
    };
    profB("glXCreateContextAttribsARB");
    glx_ctx = glXCreateContextAttribsARB(dpy, fbconfig, 0, 1, attribs);
    profE("glXCreateContextAttribsARB");
    stdlib_assert(glx_ctx != NULL);
    profB("glx->MakeContextCurrent");
    int is_glx_context_current = glx->MakeContextCurrent(dpy, win, win, glx_ctx);
    profE("glx->MakeContextCurrent");
    stdlib_assert(is_glx_context_current != 0);
  }

  {
    profB("XInternAtom WM_DELETE_WINDOW");
    Atom delete_win_atom = XInternAtom(dpy, "WM_DELETE_WINDOW", 0);
    profE("XInternAtom WM_DELETE_WINDOW");
    stdlib_assert(delete_win_atom != None);
    profB("XSetWMProtocols");
    XSetWMProtocols(dpy, win, &delete_win_atom, 1);
    profE("XSetWMProtocols");
  }

  {
    XIEventMask eventmask = {0};
    unsigned char mask[3] = {0};
    eventmask.deviceid = XIAllMasterDevices;
    eventmask.mask_len = sizeof(mask);
    eventmask.mask = mask;
    XISetMask(mask, XI_RawMotion);
    XISetMask(mask, XI_RawButtonPress);
    XISetMask(mask, XI_RawButtonRelease);
    profB("XISelectEvents");
    XISelectEvents(dpy, DefaultRootWindow(dpy), &eventmask, 1);
    profE("XISelectEvents");
  }

  profB("XMapWindow");
  XMapWindow(dpy, win);
  profE("XMapWindow");

  out_display[0] = dpy;
  out_window[0]  = win;
}

static inline void GpuWsiWindow(
    char * window_title, int window_title_bytes, int window_width, int window_height, int msaa_samples, char * out_scancodes, Display ** out_dpy, Window * out_win)
{
  __auto_type gl = g_gpulib_libgl;

  GpuWsiGetLibcProcedureAddresses();

  profB(__func__);
  Display * dpy = NULL;
  Window win = 0;
  GpuWsiX11Window(window_title, window_title_bytes, 0, 0, window_width, window_height, msaa_samples, &dpy, &win);

  profB("GpuWsiGetGLProcedureAddresses");
  GpuWsiGetGLProcedureAddresses();
  profE("GpuWsiGetGLProcedureAddresses");

  {
    char * extensions[] = {
      "GL_KHR_debug",
      "GL_ARB_multi_bind",
      "GL_ARB_gpu_shader5",
      "GL_ARB_clip_control",
      "GL_ARB_texture_view",
      "GL_EXT_texture_sRGB",
      "GL_ARB_clear_texture",
      "GL_ARB_buffer_storage",
      "GL_ARB_texture_storage",
      "GL_ARB_shader_precision",
      "GL_ARB_enhanced_layouts",
      "GL_ARB_get_program_binary",
      "GL_ARB_transform_feedback2",
      "GL_ARB_direct_state_access",
      "GL_ARB_multi_draw_indirect",
      "GL_ARB_texture_buffer_range",
      "GL_EXT_texture_mirror_clamp",
      "GL_ARB_get_texture_sub_image",
      "GL_ARB_texture_cube_map_array",
      "GL_ARB_separate_shader_objects",
      "GL_ARB_shading_language_420pack",
      "GL_ARB_shading_language_packing",
      "GL_EXT_texture_filter_anisotropic",
      "GL_ARB_texture_buffer_object_rgb32",
      "GL_ARB_texture_storage_multisample"
    };
    GpuWsiCheckExtensions(sizeof(extensions) / sizeof(extensions[0]), extensions);
  }

  profB("OpenGL state setup");
  {
    gl->Viewport(0, 0, window_width, window_height);
#ifndef RELEASE
    gl->Enable(0x92E0); // GL_DEBUG_OUTPUT
    gl->Enable(0x8242); // GL_DEBUG_OUTPUT_SYNCHRONOUS
#endif
    gl->Enable(0x884F); // GL_TEXTURE_CUBE_MAP_SEAMLESS
    gl->Enable(0x8DB9); // GL_FRAMEBUFFER_SRGB
    gl->Enable(0x809D); // GL_MULTISAMPLE
    gl->Enable(0x864f); // GL_DEPTH_CLAMP
    gl->Enable(0x0B71); // GL_DEPTH_TEST
    gl->Enable(0x0B44); // GL_CULL_FACE
    gl->Enable(0x0BE2); // GL_BLEND
    gl->BlendFunc(0x0302, 0x0303); // GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA
    gl->ClipControl(0x8CA1, 0x935F); // GL_LOWER_LEFT, GL_ZERO_TO_ONE
    gl->DepthRange(1, 0);
    gl->ClearDepth(0);
    gl->DepthFunc(0x0204); // GL_GREATER
    gl->FrontFace(0x0900); // GL_CW
  }
  {
    // OPENGL REQUIRED GARBAGE ////////
    unsigned vao = 0;                //
    gl->CreateVertexArrays(1, &vao); //
    gl->BindVertexArray(vao);        //
    ///////////////////////////////////
  }
  profE("OpenGL state setup");

  if (out_scancodes != NULL) {
    profB("Scancode caching");
    XkbDescPtr xkbdesc = XkbGetMap(dpy, 0, XkbUseCoreKbd);
    XkbGetNames(dpy, XkbKeyNamesMask, xkbdesc);
    for (int i = xkbdesc->min_key_code; i <= xkbdesc->max_key_code; i += 1) {
      char * name = xkbdesc->names->keys[i].name;
      out_scancodes[i * 5 + 0] = name[0];
      out_scancodes[i * 5 + 1] = name[1];
      out_scancodes[i * 5 + 2] = name[2];
      out_scancodes[i * 5 + 3] = name[3];
      out_scancodes[i * 5 + 4] = 0;
    }
    XkbFreeNames(xkbdesc, XkbKeyNamesMask, 1);
    XkbFreeClientMap(xkbdesc, 0, 1);
    XFree(xkbdesc);
    profE("Scancode caching");
  }

  out_dpy[0] = dpy;
  out_win[0] = win;
  profE(__func__);
}

static inline void GpuWsiSwap(Display * dpy, Window win) {
  profB(__func__);
  __auto_type glx = g_gpulib_libglx;
  glx->SwapBuffers(dpy, win);
  profE(__func__);
}

static inline unsigned GpuWsiPro(unsigned shader_type, char * shader_filepath) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  int fd = stdlib_open(shader_filepath, O_RDONLY);
  if (fd == 0) {
    profE(__func__);
    return 0;
  }
  char * shader_string = stdlib_mmap(0, 256 * 1024 * 1024, PROT_READ, MAP_PRIVATE, fd, 0);
  if (shader_string == NULL) {
    profE(__func__);
    return 0;
  }
  int pro_id = GpuPro(shader_type, shader_string);
  stdlib_munmap(shader_string, 256 * 1024 * 1024);
  stdlib_close(fd);
  profE(__func__);
  return pro_id;
}

static inline unsigned GpuWsiVert(char * shader_filepath) { return GpuWsiPro(0x8B31, shader_filepath); } // GL_VERTEX_SHADER
static inline unsigned GpuWsiFrag(char * shader_filepath) { return GpuWsiPro(0x8B30, shader_filepath); } // GL_FRAGMENT_SHADER

static inline int GpuWsiBinaryRgbImg(unsigned tex_id, int width, int height, int layer_count, char * img_binary_filepath) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  int fd = stdlib_open(img_binary_filepath, O_RDONLY);
  if (fd == 0) {
    profE(__func__);
    return 1;
  }
  char * p = stdlib_mmap(0, (width * height * 3) * layer_count, PROT_READ, MAP_PRIVATE, fd, 0);
  if (p == NULL) {
    profE(__func__);
    return 1;
  }
  profB("gl->TextureSubImage3D");
  gl->TextureSubImage3D(tex_id, 0, 0, 0, 0, width, height, layer_count, 0x1907, 0x1401, p); // GL_RGB, GL_UNSIGNED_BYTE
  profE("gl->TextureSubImage3D");
  profB("gl->GenerateTextureMipmap");
  gl->GenerateTextureMipmap(tex_id);
  profE("gl->GenerateTextureMipmap");
  stdlib_munmap(p, (width * height * 3) * layer_count);
  stdlib_close(fd);
  profE(__func__);
  return 0;
}

static inline int GpuWsiBinaryRgbCbm(unsigned tex_id, int width, int height, int layer_count, char * cbm_binary_filepath) {
  profB(__func__);
  __auto_type gl = g_gpulib_libgl;
  int fd = stdlib_open(cbm_binary_filepath, O_RDONLY);
  if (fd == 0) {
    profE(__func__);
    return 1;
  }
  char * p = stdlib_mmap(0, (width * height * 3) * (layer_count * 6), PROT_READ, MAP_PRIVATE, fd, 0);
  if (p == NULL) {
    profE(__func__);
    return 1;
  }
  profB("gl->TextureSubImage3D");
  gl->TextureSubImage3D(tex_id, 0, 0, 0, 0, width, height, layer_count * 6, 0x1907, 0x1401, p); // GL_RGB, GL_UNSIGNED_BYTE
  profE("gl->TextureSubImage3D");
  profB("gl->GenerateTextureMipmap");
  gl->GenerateTextureMipmap(tex_id);
  profE("gl->GenerateTextureMipmap");
  stdlib_munmap(p, (width * height * 3) * (layer_count * 6));
  stdlib_close(fd);
  profE(__func__);
  return 0;
}

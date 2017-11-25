#define _BSD_SOURCE // usleep()
#include <unistd.h>
#include <sys/stat.h>
#include <dlfcn.h>
#include "api.h"

struct app_t {
  struct api_t api;
  void * handle;
  void * state;
  ino_t  id;
};

static void AppLoad(struct app_t * app, Display * dpy, Window win, char * scancodes) {
  struct stat attr = {0};
  if ((stat("./libapp.so", &attr) == 0) && (app->id != attr.st_ino)) {
    if (app->handle != NULL) {
      app->api.Unload(app->state);
      dlclose(app->handle);
    }
    void * handle = dlopen("./libapp.so", RTLD_NOW);
    if (handle != NULL) {
      app->handle = handle;
      app->id = attr.st_ino;
      struct api_t * api = dlsym(app->handle, "APP_API");
      if (api != NULL) {
        app->api = api[0];
        if (app->state == NULL)
          app->state = app->api.Init(dpy, win, scancodes);
        app->api.Load(app->state, dpy, win, scancodes);
      } else {
        dlclose(app->handle);
        app->handle = NULL;
        app->id = 0;
      }
    } else {
      app->handle = NULL;
      app->id = 0;
    }
  }
}

void AppUnload(struct app_t * app) {
  if (app->handle != NULL) {
    app->api.Unload(app->state);
    app->api.Deinit(app->state);
    app->state = NULL;
    dlclose(app->handle);
    app->handle = NULL;
    app->id = 0;
  }
}

int main() {
  char scancodes[256 * 5] = {0};
  Display * dpy = NULL;
  Window win = 0;
  GpuWindow("Hot Reload OpenGL", 1280, 720, 4, scancodes, &dpy, &win);
  GpuSetDebugCallback(GpuDebugCallback);

  struct app_t app = {0};
  for (;;) {
    AppLoad(&app, dpy, win, scancodes);
    if (app.handle != NULL)
      if (app.api.Step(app.state, dpy, win, scancodes) != 0)
        break;
  }
  AppUnload(&app);
  return 0;
}

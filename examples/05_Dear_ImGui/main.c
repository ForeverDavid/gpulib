#include "../../gpulib.h"
#include "../../gpulib_imgui.h"

int main() {
  char scancodes[256 * 5] = {0};
  Display * dpy = NULL;
  Window win = 0;
  GpuWindow("Dear ImGui", sizeof("Dear ImGui"), 1280, 720, 4, scancodes, &dpy, &win);
  GpuSetDebugCallback(GpuDebugCallback);

  ImguiInit(dpy, win, scancodes);

  struct ImGuiIO    * io    = igGetIO();
  struct ImGuiStyle * style = igGetStyle();

  style->ScrollbarRounding = 0;
  style->WindowRounding    = 0;
  style->FrameRounding     = 0;

  ImFontAtlas_AddFontFromFileTTF(io->Fonts, "NotoSans.ttf", 24, NULL, NULL);

  for (Atom quit = XInternAtom(dpy, "WM_DELETE_WINDOW", 0);;) {
    for (XEvent event = {0}; XPending(dpy);) {
      XNextEvent(dpy, &event);
      ImguiProcessEvent(&event);
      switch (event.type) {
        break; case ClientMessage: {
          if (event.xclient.data.l[0] == quit)
            goto exit;
        }
      }
    }

    ImguiNewFrame();

    GpuClear();

    static bool show_test_window = 1;
    igShowTestWindow(&show_test_window);

    {
      // Flat UI by yorick.penninks: https://color.adobe.com/Flat-UI-color-theme-2469224/
      static struct ImVec3 color_for_text = {236 / 255.f, 240 / 255.f, 241 / 255.f};
      static struct ImVec3 color_for_head = { 41 / 255.f, 128 / 255.f, 185 / 255.f};
      static struct ImVec3 color_for_area = { 57 / 255.f,  79 / 255.f, 105 / 255.f};
      static struct ImVec3 color_for_body = { 44 / 255.f,  62 / 255.f,  80 / 255.f};
      static struct ImVec3 color_for_pops = { 33 / 255.f,  46 / 255.f,  60 / 255.f};

      // Mint Y Dark:
      //static struct ImVec3 color_for_text = {211 / 255.f, 211 / 255.f, 211 / 255.f};
      //static struct ImVec3 color_for_head = { 95 / 255.f, 142 / 255.f,  85 / 255.f};
      //static struct ImVec3 color_for_area = { 47 / 255.f,  47 / 255.f,  47 / 255.f};
      //static struct ImVec3 color_for_body = { 64 / 255.f,  64 / 255.f,  64 / 255.f};
      //static struct ImVec3 color_for_pops = { 30 / 255.f,  30 / 255.f,  30 / 255.f};

      // Arc Theme:
      //static struct ImVec3 color_for_text = {211 / 255.f, 218 / 255.f, 227 / 255.f};
      //static struct ImVec3 color_for_head = { 64 / 255.f, 132 / 255.f, 214 / 255.f};
      //static struct ImVec3 color_for_area = { 47 / 255.f,  52 / 255.f,  63 / 255.f};
      //static struct ImVec3 color_for_body = { 56 / 255.f,  60 / 255.f,  74 / 255.f};
      //static struct ImVec3 color_for_pops = { 28 / 255.f,  30 / 255.f,  37 / 255.f};

      igColorEdit3("Text", &color_for_text.x);
      igColorEdit3("Head", &color_for_head.x);
      igColorEdit3("Area", &color_for_area.x);
      igColorEdit3("Body", &color_for_body.x);
      igColorEdit3("Pops", &color_for_pops.x);

      ImguiEasyTheming(color_for_text, color_for_head, color_for_area, color_for_body, color_for_pops);
    }

    igRender();

    GpuSwap(dpy, win);
  }

exit:;
  ImguiDeinit();
  XDestroyWindow(dpy, win);
  XCloseDisplay(dpy);
  return 0;
}

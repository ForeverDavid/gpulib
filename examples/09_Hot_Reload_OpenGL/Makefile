CFLAGS = -fPIC -O0 -g
LDLIBS = ../../libimgui.so -lX11 -lXrender -lXi -lGL -lm -ldl

all: main libapp.so

main: main.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)

libapp.so: app.c
	$(CC) $(CFLAGS) -shared $(LDFLAGS) -o $@ $< $(LDLIBS)

test: main libapp.so
	./$<

clean:
	$(RM) main libapp.so imgui.ini

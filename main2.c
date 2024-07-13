#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/cursorfont.h>
#include <string.h>

#define BUTTON_WIDTH 100
#define BUTTON_HEIGHT 30
#define TEXTBOX_WIDTH 200
#define TEXTBOX_HEIGHT 30
#define MARGIN 10
#define MAX_TEXT_LEN 256

typedef struct {
    int x, y, width, height;
    char text[MAX_TEXT_LEN];
    int text_len;
    int active;
} TextBox;

void draw_textbox(Display *display, Window win, GC gc, TextBox *textbox) {
    XDrawRectangle(display, win, gc, textbox->x, textbox->y, textbox->width, textbox->height);
    if (textbox->text_len > 0) {
        XDrawString(display, win, gc, textbox->x + 5, textbox->y + 20, textbox->text, textbox->text_len);
    }
}

void draw_button(Display *display, Window win, GC gc, XFontStruct *font_info, int x, int y, int width, int height, const char *label) {
    XDrawRectangle(display, win, gc, x, y, width, height);
    int len = strlen(label);
    int text_width = XTextWidth(font_info, label, len);
    XDrawString(display, win, gc, x + (width - text_width) / 2, y + (height + font_info->ascent) / 2, label, len);
}

int is_inside(TextBox *textbox, int x, int y) {
    return x >= textbox->x && x <= textbox->x + textbox->width &&
           y >= textbox->y && y <= textbox->y + textbox->height;
}

int main() {
    Display *display;
    Window window;
    XEvent event;
    int screen;
    GC gc;
    XGCValues values;
    XFontStruct *font_info;
    unsigned long valuemask = 0;
    Cursor cursor;
    TextBox textbox1 = {MARGIN, MARGIN, TEXTBOX_WIDTH, TEXTBOX_HEIGHT, "", 0, 0};
    TextBox textbox2 = {MARGIN, 2 * MARGIN + TEXTBOX_HEIGHT, TEXTBOX_WIDTH, TEXTBOX_HEIGHT, "", 0, 0};

    if (!(display = XOpenDisplay(NULL))) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    screen = DefaultScreen(display);
    int win_width = 2 * TEXTBOX_WIDTH + 3 * MARGIN;
    int win_height = 3 * TEXTBOX_HEIGHT + 4 * MARGIN;

    window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, win_width, win_height, 1,
                                 BlackPixel(display, screen), WhitePixel(display, screen));

    XSelectInput(display, window, ExposureMask | ButtonPressMask | KeyPressMask);
    XMapWindow(display, window);

    // Create and set a default cursor
    cursor = XCreateFontCursor(display, XC_left_ptr);
    XDefineCursor(display, window, cursor);

    gc = XCreateGC(display, window, valuemask, &values);
    XSetForeground(display, gc, BlackPixel(display, screen));

    font_info = XLoadQueryFont(display, "fixed");
    if (!font_info) {
        fprintf(stderr, "Unable to load font\n");
        XCloseDisplay(display);
        exit(1);
    }
    XSetFont(display, gc, font_info->fid);

    while (1) {
        XNextEvent(display, &event);
        if (event.type == Expose) {
            draw_textbox(display, window, gc, &textbox1);
            draw_textbox(display, window, gc, &textbox2);
            draw_button(display, window, gc, font_info, MARGIN, 3 * MARGIN + 2 * TEXTBOX_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT, "Close X");
        } else if (event.type == ButtonPress) {
            int x = event.xbutton.x;
            int y = event.xbutton.y;
            if (is_inside(&textbox1, x, y)) {
                textbox1.active = 1;
                textbox2.active = 0;
            } else if (is_inside(&textbox2, x, y)) {
                textbox1.active = 0;
                textbox2.active = 1;
            } else {
                textbox1.active = 0;
                textbox2.active = 0;
                if (x >= MARGIN && x <= MARGIN + BUTTON_WIDTH &&
                    y >= 3 * MARGIN + 2 * TEXTBOX_HEIGHT && y <= 3 * MARGIN + 2 * TEXTBOX_HEIGHT + BUTTON_HEIGHT) {
                    system("pkill Xorg");
                }
            }
        } else if (event.type == KeyPress) {
            TextBox *active_textbox = textbox1.active ? &textbox1 : textbox2.active ? &textbox2 : NULL;
            if (active_textbox) {
                char buf[32];
                KeySym keysym;
                int len = XLookupString(&event.xkey, buf, sizeof(buf), &keysym, NULL);
                if (keysym == XK_BackSpace) {
                    if (active_textbox->text_len > 0) {
                        active_textbox->text[--active_textbox->text_len] = '\0';
                    }
                } else if (len > 0 && active_textbox->text_len + len < MAX_TEXT_LEN) {
                    strncat(active_textbox->text, buf, len);
                    active_textbox->text_len += len;
                }
                XClearArea(display, window, active_textbox->x + 1, active_textbox->y + 1, active_textbox->width - 2, active_textbox->height - 2, False);
                draw_textbox(display, window, gc, active_textbox);
            }
        }
    }

    XFreeFont(display, font_info);
    XCloseDisplay(display);
    return 0;
}

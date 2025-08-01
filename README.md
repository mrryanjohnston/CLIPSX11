# CLIPSX11

A CLIPS X11 library

## Usage

Run `make` in order to:

1. Download the CLIPS 6.4.2 source code
2. Untar it to the `clips` dir
3. Copy the `userfunctions.c` file into the `clips` dir
4. Run `make` in the `clips` dir

Now you have an executable `clips/clips` file that has X11-related
functions available in it.

## Examples

### clipsmwm Window Manager

There are two files that provide an example window manager
based on [mwm](https://github.com/lslvr/mwm).
The first file `clipsmwm.multifield.clp` takes the output from
X11 functions and returns them as CLIPS Multifields
and asserts implied Facts.
The second file `clipsmwm.fact.clp` asserts them directly as CLIPS Facts.
The `deftemplates.clp` file is necessary if you use the `clipsmwm.fact.clp` file.

#### Display Managers

If you want to install this to your machine, use `sudo make install`
to install a `CLIPSX11` to your `/usr/local/bin` dir.
This will also attempt to install the `clipsmwm.desktop` file
into your `/usr/share/xsessions` dir
as well as the `.clp` and `.bat` files into your `/usr/local/share/CLIPSX11` dir.

#### Via `startx`

Run `sudo make install` and add this to the end of your `.xinitrc`:

```
exec clipsmwm.sh
```

### Misc examples

There are two other files `program.clp` `program2.clp`
showcasing some of the other functions provided by this library.

### Documentation

1. [Display Management](#display-management)
2. [Window Creation & Management](#window-creation--management)
3. [Cursor, Font & Color](#cursor-font--color)
4. [Graphics Context & Drawing](#graphics-context--drawing)
5. [Event Handling](#event-handling)
6. [Keyboard Utilities](#keyboard-utilities)
7. [Screen Conversion](#screen-conversion)

#### Display Management

##### `x-open-display`

```clips
(x-open-display [<display-name>]) → <DISPLAY-ADDRESS> | FALSE
```

###### Description

Connects to the X server.

###### Parameters

- `display-name` (SYMBOL, optional) - hostname and display number (e.g. `"localhost:0"`). If omitted, uses `DISPLAY` env var.

###### Returns

- External address wrapping `Display*` on success.
- `FALSE` if connection fails (prints error to STDERR).

###### Example

```clips
(bind ?d (x-open-display ":0"))
```

---

##### `default-screen`

```clips
(default-screen <display>) → <screen-number>
```

###### Description

Retrieves the default screen index for a display.

###### Parameters

- `display` (EXTERNAL-ADDRESS) - a `Display*` returned by `x-open-display`.

###### Returns

- Integer index of the default screen. 

---

##### `default-screen-of-display`

```clips
(default-screen-of-display <display>) → <screen-address>
```

##### Description

Returns the `Screen*` pointer for the default screen.

##### Parameters

- `display` (EXTERNAL-ADDRESS)

##### Returns

- External address wrapping `Screen*`.

---

##### `default-root-window`

```clips
(default-root-window <display>) → <window-id>
```

##### Description

Fetches the root window ID of the default screen.

##### Parameters

- `display` (EXTERNAL-ADDRESS)

##### Returns

- Window ID (INTEGER).

---

##### `root-window`

```clips
(root-window <display> <screen>) → <window-id>
```

##### Description

Fetches the root window ID for a specified screen index.

##### Parameters

- `display` (EXTERNAL-ADDRESS)
- `screen` (INTEGER)

##### Returns

- Window ID (INTEGER).

---

#### Window Creation & Management

##### `x-create-simple-window`

```clips
(x-create-simple-window <display> <parent> <x> <y> <width> <height> <border-width> <border> <background>) → <window-id>
```

##### Description

Creates a basic window.

##### Parameters

1. `display` (EXTERNAL-ADDRESS) - `Display*`
2. `parent` (INTEGER) - parent window ID
3. `x`, `y` (INTEGER) - position
4. `width`, `height` (INTEGER) - dimensions
5. `border-width` (INTEGER)
6. `border`, `background` (INTEGER) - pixel values

##### Returns

- New window ID (INTEGER).

##### Example

```clips
(bind ?w (x-create-simple-window ?d ?parent 10 10 400 300 1 0 65535))
```

---

##### `x-create-window`

```clips
(x-create-window <display> <parent> <x> <y> <width> <height> <border-width> <depth> <class> <visual> <valuemask> <attributes>) → <window-id>
```

##### Description

Creates a window with full attribute control.

##### Parameters

- Same as `XCreateWindow`: includes `depth`, `class`, `visual` (EXTERNAL-ADDRESS), `valuemask`, and pointer to `XSetWindowAttributes`.

##### Returns

- New window ID (INTEGER).

---

##### `x-map-window`

```clips
(x-map-window <display> <window>) → VOID
```

##### Description

Maps (shows) a window.

##### Parameters

1. `display` (EXTERNAL-ADDRESS)
2. `window` (INTEGER)

---

##### `x-move-resize-window`

```clips
(x-move-resize-window <display> <window> <x> <y> <width> <height>) → <status>
```

##### Description

Moves and resizes a window in one call.

##### Parameters

1. `<display>` – External address to an X11 Display object. Represents the connection to the X server.
2. `<window>` – Integer handle identifying the window to move/resize.
3. `<x>` – Integer specifying the new X coordinate (position) of the window’s origin relative to its parent.
4. `<y>` – Integer specifying the new Y coordinate of the window’s origin relative to its parent.
5. `<width>` – Integer giving the new width of the window in pixels.
6. `<height>` – Integer giving the new height of the window in pixels.

##### Returns

- Status code (INTEGER, non-zero on success).

---

##### `x-circulate-subwindows-up`

```clips
(x-circulate-subwindows-up <display> <window>) → <status>
```

##### Description

Raises all child windows of `window`.

---

##### `x-kill-client`

```
clips (x-kill-client <display> <resource>) → <status>
```

##### Description

Forces the X server to close a client identified by `resource` (window or pixmap).

---

##### `remove-hints-flags-from-window`

```
(remove-hints-flags-from-window <display> <window> [<hint-symbol> ...])
```

##### Returns

void

##### Description

Clears (removes) one or more size/position-related hint flags from the `WM_NORMAL_HINTS` property of a given X11 window. These hints influence how window managers position, size, and interpret the window; removing flags allows the application or window manager to ignore previously set constraints.

###### Arguments

1. `<display>` – External address to an X11 `Display` object.  
2. `<window>` – Integer representing the X11 `Window` whose hints are to be modified.  
3. Zero or more of the following hint symbols indicating which bits to **remove** from the current `XSizeHints.flags`:
   - `USPosition` – User-specified position.
   - `USSize` – User-specified size.
   - `PPosition` – Program-specified position.
   - `PSize` – Program-specified size.
   - `PMinSize` – Program-specified minimum size.
   - `PMaxSize` – Program-specified maximum size.
   - `PResizeInc` – Resize increment.
   - `PAspect` – Aspect ratio.
   - `PBaseSize` – Base size.
   - `PWinGravity` – Window gravity.

##### Example

```clips
(remove-hints-flags-from-window ?display ?window USPosition PSize)
```

---

##### `set-window-gravity`

```
(set-window-gravity <display> <window> <gravity-symbol>)  
```

##### Returns

void (v)

##### Description

Sets the window gravity in the `WM_NORMAL_HINTS` property for a given X11 window. Window gravity controls how the window's position is interpreted when its size or parent changes—for example, whether the origin stays fixed or is adjusted relative to a particular corner or edge.

##### Arguments

1. <display> – External address to an X11 Display object.
2. <window> – Integer representing the X11 Window whose gravity is to be set.
3. <gravity-symbol> – One of the supported gravity symbols:
   - ForgetGravity
   - NorthWestGravity
   - NorthGravity
   - NorthEastGravity
   - WestGravity
   - CenterGravity
   - EastGravity
   - SouthWestGravity
   - SouthGravity
   - SouthEastGravity
   - StaticGravity

##### Example

```
(set-window-gravity ?display ?window CenterGravity)
```

---

#### Cursor, Font & Color

##### `x-create-font-cursor`

```clips
(x-create-font-cursor <display> <shape-symbol>) → <cursor-id> | FALSE
```

##### Description

Creates a cursor from the X11 font cursor set.

##### Parameters

- `display` (EXTERNAL-ADDRESS)
- `shape-symbol` - The following symbol strings are recognised and mapped to their respective X cursor shapes:
    - `XC_X_cursor`
    - `XC_arrow`
    - `XC_based_arrow_down`
    - `XC_based_arrow_up`
    - `XC_boat`
    - `XC_bogosity`
    - `XC_bottom_left_corner`
    - `XC_bottom_right_corner`
    - `XC_bottom_side`
    - `XC_bottom_tee`
    - `XC_box_spiral`
    - `XC_center_ptr`
    - `XC_circle`
    - `XC_clock`
    - `XC_coffee_mug`
    - `XC_cross`
    - `XC_cross_reverse`
    - `XC_crosshair`
    - `XC_diamond_cross`
    - `XC_dot`
    - `XC_dotbox`
    - `XC_double_arrow`
    - `XC_draft_large`
    - `XC_draft_small`
    - `XC_draped_box`
    - `XC_exchange`
    - `XC_fleur`
    - `XC_gobbler`
    - `XC_gumby`
    - `XC_hand1`
    - `XC_hand2`
    - `XC_heart`
    - `XC_icon`
    - `XC_iron_cross`
    - `XC_left_ptr`
    - `XC_left_side`
    - `XC_left_tee`
    - `XC_leftbutton`
    - `XC_ll_angle`
    - `XC_lr_angle`
    - `XC_man`
    - `XC_middlebutton`
    - `XC_mouse`
    - `XC_pencil`
    - `XC_pirate`
    - `XC_plus`
    - `XC_question_arrow`
    - `XC_right_ptr`
    - `XC_right_side`
    - `XC_right_tee`
    - `XC_rightbutton`
    - `XC_rtl_logo`
    - `XC_sailboat`
    - `XC_sb_down_arrow`
    - `XC_sb_h_double_arrow`
    - `XC_sb_left_arrow`
    - `XC_sb_right_arrow`
    - `XC_sb_up_arrow`
    - `XC_sb_v_double_arrow`
    - `XC_shuttle`
    - `XC_sizing`
    - `XC_spider`
    - `XC_spraycan`
    - `XC_star`
    - `XC_target`
    - `XC_tcross`
    - `XC_top_left_arrow`
    - `XC_top_left_corner`
    - `XC_top_right_corner`
    - `XC_top_side`
    - `XC_top_tee`
    - `XC_trek`
    - `XC_ul_angle`
    - `XC_umbrella`
    - `XC_ur_angle`
    - `XC_watch`
    - `XC_xterm`

---

##### `x-define-cursor`

```clips
(x-define-cursor <display> <window> <cursor>) → VOID
```

##### Description

Associates a cursor with a window.

##### `black-pixel`
##### `white-pixel`

```clips
(black-pixel <display> <screen>) → <pixel>
(white-pixel <display> <screen>) → <pixel>
```

##### Description

Fetches the black or white pixel value for a screen.

---

#### Graphics Context & Drawing

##### `x-create-gc`

```clips
(x-create-gc <display> <drawable> <valuemask>) → <GC-ADDRESS>
```

##### Description Creates a graphics context; returns an external address. Uses default `XGCValues`.

##### `x-set-foreground`

```clips
(x-set-foreground <display> <gc> <pixel>) → <status>
```

##### Description

Sets the foreground color for drawing operations in a `GC`.

##### Drawing Primitives

```clips
(x-draw-arc <display> <drawable> <gc> <x> <y> <width> <height> <angle1> <angle2>)
(x-draw-line <display> <drawable> <gc> <x1> <y1> <x2> <y2>)
(x-draw-point <display> <drawable> <gc> <x> <y>)
(x-draw-rectangle <display> <drawable> <gc> <x> <y> <width> <height>)
(x-draw-string <display> <drawable> <gc> <x> <y> <text>)
```

Each wraps the corresponding `XDraw*` call and returns `VOID`.

---

#### Event Handling

##### `x-pending`

```clips
(x-pending <display>) → <count>
```

##### Description

Checks how many events are queued.

##### `x-peek-event`
##### `x-next-event`

```clips
(x-peek-event <display>) → <multifield>
(x-next-event <display>) → <multifield>
```

##### Description

Retrieves (or waits for) the next `XEvent`, converts it into a CLIPS multifield: 

`[ <xany> <type-symbol> <typed-detail> ]`

##### Return

##### Fact-Based Variants

```clips
(x-peek-event-to-fact <display>) → <fact>
(x-next-event-to-fact <display>) → <fact>
```

As above, but asserts an `x-event` fact template.

---

##### `x-pop-event`

```clips
(x-pop-event <display>) → VOID
```

##### Description

Removes the next event without returning it. Useful after an `x-peek-event`
to remove it from the event queue.

---

#### Keyboard Utilities

##### `x-lookup-string`

```clips
(x-lookup-string <event-address>) → [ <string> <keysym> ]
```

##### Description

Converts a `KeyPress` event to its text and keysym.

##### `x-string-to-keysym`

```clips
(x-string-to-keysym <symbol>) → <keysym>
```

##### Description

Maps a key name (e.g. `"Return"`) to its keysym.

##### `x-keysym-to-keycode`

```clips
(x-keysym-to-keycode <display> <keysym>) → <keycode>
```

##### `x-grab-key`

```clips
(x-grab-key <display> <keycode> <modifiers> <window> <owner-events?> <pointer-mode> <keyboard-mode>) → <status>
```

##### Description

Grabs a specific key (with optional modifier masks) on a given window so that the application receives key events even if another client would normally have focus. This is an X11 passive key grab.

##### Arguments

1. `<display>` – External address to an X11 Display object.
2. `<keycode>` – Integer keycode to grab.
3. `<modifiers>` – Either a symbol or a multifield list of symbols specifying modifier masks. Supported symbols:
     * `ShiftMask`
     * `LockMask`
     * `ControlMask`
     * `Mod1Mask`
     * `Mod2Mask`
     * `Mod3Mask`
     * `Mod4Mask`
     * `Mod5Mask`
     * `AnyModifier` (special; matches any combination)
   If a multifield is provided, each symbol is OR'ed together to form the modifier mask.
4. `<grab-window>` – Integer representing the X11 window in which the key is to be grabbed.
5. `<owner-events?>` – Boolean; if TRUE, events are reported as if the grabbing client owned the events (owner_events argument to XGrabKey).
6. `<pointer-mode-symbol>` – Symbol controlling pointer freezing behavior during the grab. Recognized value:
     * "GrabModeSync" – pointer is frozen until explicitly released (maps to X11 GrabModeSync)
     * anything else (typically "GrabModeAsync") – pointer operates asynchronously (maps to GrabModeAsync)
7. `<keyboard-mode-symbol>` – Symbol controlling keyboard freezing behavior during the grab. Same semantics as pointer-mode-symbol.

##### Example

```clips
;grabs key t when mod4 (typically windows key) is held down
(x-grab-key ?display (x-keysym-to-keycode ?display (x-string-to-keysym "t")) Mod4Mask ?window TRUE GrabModeAsync GrabModeAsync)))
```

---

#### Screen Conversion

##### `screen-to-fact`

```clips
(screen-to-fact <screen-address>) → <fact>
```

##### Description

Builds and asserts a `screen` fact with slots:

- `c-pointer`
- `ext-data`
- `display`
- `root`
- `width`
- `height`
- `mwidth`
- `mheight`
- `ndepths`
- `root-depth`
- `white-pixel`
- `black-pixel`
- `max-maps`
- `min-maps`
- `backing-store`
- `save-unders`
- `root-input-mask`.

---

##### `screen-to-multifield`

```clips
(screen-to-multifield <screen-address>) → <multifield>
```

##### Description

Returns the same information as a multifield vector.

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

## Documentation

1. [Display Management](#display-management)
2. [Window Creation & Management](#window-creation--management)
3. [Cursor, Font & Color](#cursor-font--color)
4. [Graphics Context & Drawing](#graphics-context--drawing)
5. [Event Handling](#event-handling)
6. [Keyboard Utilities](#keyboard-utilities)
7. [Screen Conversion](#screen-conversion)
8. [Utility](#utility)

### Display Management

#### `x-open-display`

```clips
(x-open-display [<display-name>]) → <DISPLAY-ADDRESS> | FALSE
```

##### Description

Connects to the X server.

##### Parameters

- `display-name` (SYMBOL, optional) - hostname and display number (e.g. `"localhost:0"`). If omitted, uses `DISPLAY` env var.

##### Returns

- External address wrapping `Display*` on success.
- `FALSE` if connection fails (prints error to STDERR).

##### Example

```clips
(bind ?d (x-open-display ":0"))
```

---

#### `default-screen`

```clips
(default-screen <display>) → <screen-number>
```

##### Description

Retrieves the default screen index for a display.

##### Parameters

- `display` (EXTERNAL-ADDRESS) - a `Display*` returned by `x-open-display`.

##### Returns

- Integer index of the default screen. 

---

#### `default-screen-of-display`

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

#### `default-root-window`

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

#### `root-window`

```clips
(root-window <display> <screen>) → <window-id>
```

#### Description

Fetches the root window ID for a specified screen index.

#### Parameters

- `display` (EXTERNAL-ADDRESS)
- `screen` (INTEGER)

#### Returns

- Window ID (INTEGER).

---

### Window Creation & Management

#### `x-create-simple-window`

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

#### `x-create-window`

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

#### `x-map-window`

```clips
(x-map-window <display> <window>) → VOID
```

##### Description

Maps (shows) a window.

##### Parameters

1. `display` (EXTERNAL-ADDRESS)
2. `window` (INTEGER)

---

#### `x-move-resize-window`

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

#### `x-circulate-subwindows-up`

```clips
(x-circulate-subwindows-up <display> <window>) → <status>
```

##### Description

Raises all child windows of `window`.

##### Arguments

1. `<display>` – External address to an X11 `Display` object.  
2. `<window>` – Integer representing the X11 `Window` to bring to the top.

---

#### `x-raise-window`

```clips
(x-raise-window <display> <window>) → <void>
```

##### Description

Raises `window` to the top of its siblings.

##### Arguments

1. `<display>` – External address to an X11 `Display` object.  
2. `<window>` – Integer representing the X11 `Window` to bring to the top.

---

#### `x-lower-window`

```clips
(x-lower-window <display> <window>) → <void>
```

##### Description

Lowers `window` to the bottom of its siblings.

##### Arguments

1. `<display>` – External address to an X11 `Display` object.  
2. `<window>` – Integer representing the X11 `Window` to lower to the bottom.

---

##### `x-kill-client`

```
clips (x-kill-client <display> <resource>) → <status>
```

##### Description

Forces the X server to close a client identified by `resource` (window or pixmap).

---

#### `remove-hints-flags-from-window`

```
(remove-hints-flags-from-window <display> <window> [<hint-symbol> ...])
```

##### Returns

void

##### Description

Clears (removes) one or more size/position-related hint flags from the `WM_NORMAL_HINTS` property of a given X11 window. These hints influence how window managers position, size, and interpret the window; removing flags allows the application or window manager to ignore previously set constraints.

##### Arguments

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

#### `set-window-gravity`

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

#### `x-list-properties`

```
(x-list-properties <display> <window>)  
```

##### Arguments

- `<display>`: External address to `Display *`.
- `<window>`: Integer window ID.

##### Return

A multifield of symbols: each is the string name of a property currently set on the window. If no properties or on failure, returns an empty multifield.

##### Behavior

- Internally calls `XListProperties`.
- Converts each returned atom to its name via `XGetAtomName`.
- Returns names as CLIPS symbols.

#### `x-get-property`

```
(x-get-property <display> <window> <name>)
```

##### Arguments

- `<display>`: External address to `Display *`.
- `<window>`: Integer window ID.
- `<name>`: Name of the property

##### Returns

- MULTIFIELD containing:
    1. SYMBOL representing the actual type of the value
    2. INTEGER representing the actual format of the value
    3. A series of STRINGs or INTEGERs which are the actual values

---

#### `x-change-property`

```
(x-change-property <display> <window> <property-name> <type-name> <format> <mode> [?data])
```

##### Arguments

- `<display>`: External address of the opened X display (from `x-open-display`).
- `<window>`: Integer window ID to operate on.
- `<property-name>`: Symbol/string naming the property to change (will be interned via `XInternAtom`).
- `<type-name>`: Symbol/string naming the type of the property (interned similarly).
- `<format>`: Integer; one of `8`, `16`, or `32`. Specifies the data format bits per item.
- `<mode>`: One of the symbols `"Replace"`, `"Append"`, or `"Prepend"`. Determines how the new data is combined with existing property data.
- `?data` (optional): The value to set. Accepts:
  - A single integer (interpreted according to `format`).
  - A string or symbol (automatically coerced to format `8`).
  - A multifield of integers (each mapped according to `format`).

If `?data` is omitted, the property is updated with zero elements (effectively clearing it or setting an empty value depending on mode).

##### Examples

```clips
(x-change-property ?display ?window "_NET_WM_NAME" "UTF8_STRING" 8 "Replace" "MyWindow")
(x-change-property ?display ?window "_NET_WM_NAME" "UTF8_STRING" 8 Append " - more")
(x-change-property ?display ?window "MY_PROP" "CARDINAL" 32 Prepend (create$ 1 2 3 4))
(x-change-property ?display ?window "MY_PROP" "CARDINAL" 32 "Replace")
```

---

#### `x-delete-property`

```
(x-delete-property <display> <window> <name>)
```

##### Arguments

- `<display>`: External address to `Display *`.
- `<window>`: Integer window ID.
- `<name>`: Name of the property

---

#### `x-get-geometry`

```
(x-get-geometry <display> <window>)
```

##### Arguments

- `<display>`: External address to `Display *`.
- `<window>`: Integer window ID.

##### Returns

- A multifield with the following ordered values:
    1. `root` Window ID of the window passed
    2. `x` position of the Window ID relative to `root`'s origin
    3. `y` position of the Window ID relative to `root`'s origin
    4. `width` of the Window ID
    5. `height` of the Window ID
    6. `border_width` of the Window ID in pixels
    7. `depth` of the drawable (bits per pixels of the object)

#### `x-get-window-attributes`
#### `x-get-window-attributes-to-fact`
#### `x-get-window-attributes-to-instance`


##### Description

Returns attributes about the window as either a multifield, a fact, or an instance.
For a multifield, use `x-get-window-attributes`. The attributes will be returned
in this order:

- x, y - location of window
- width, height - width and height of window
- border_width - border width of window
- depth - depth of window
- visual - the associated visual structure
- root - root of screen containing window
- class - InputOutput, InputOnly
- bit_gravity - one of the bit gravity values
- win_gravity - one of the window gravity values
- backing_store - NotUseful, WhenMapped, Always
- backing_planes - planes to be preserved if possible
- backing_pixel - value to be used when restoring planes
- save_under - boolean, should bits under be saved?
- colormap - color map to be associated with window
- map_installed - boolean, is color map currently installed
- map_state - IsUnmapped, IsUnviewable, IsViewable
- all_event_masks - set of events all people have interest in
- your_event_mask - my event mask
- do_not_propagate_mask - set of events that should not propagate
- override_redirect - boolean value for override-redirect
- screen - back pointer to correct screen

For `x-get-window-attributes-to-fact`, a fact will be asserted with the above slots.
For `x-get-window-attributes-to-instance`, an instance will be made with the above slots.

---

#### `x-query-tree`

```clips
(x-query-tree <display> <window>)
```

##### Description

Returns multifield whose members are:

- root - the root window
- parent - the parent window
- children - a list of windows that are children of the `<window> argument listed in stacking order (bottom-most first)

---

#### `x-fetch-name`

```
(x-fetch-name ?display ?window)
```

##### Arguments

- `<display>`: External address to `Display *`.
- `<window>`: Integer window ID.

##### Returns

` STRING of the window name

#### `x-store-name`

```
(x-fetch-name ?display ?window ?name)
```

##### Arguments

- `<display>`: External address to `Display *`.
- `<window>`: Integer window ID.
- `<name>`: The new name to set on the window

##### Example

```clips
(x-store-name ?window ?display "My new window!")
```

### Cursor, Font & Color

#### `x-query-pointer`

```clips
(x-query-pointer <display>) → MULTIFIELD
```

#### Description

Returns the x, y coordinates of the cursor.

#### Arguments

- `<display>`: External address to `Display *`.

#### Returns

A MULTIFIELD with two values `x` and `y` which are the coordinates of the cursor

---


#### `x-create-font-cursor`

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

#### `x-define-cursor`

```clips
(x-define-cursor <display> <window> <cursor>) → VOID
```

##### Description

Associates a cursor with a window.

---

#### `x-get-input-focus`

##### Description

Retrieves the current input focus window and the revert-to setting for the specified display.

##### Arguments

- `<display>`: External address to an X11 `Display` (as returned by `x-open-display`).

##### Returns

A multifield containing two elements:
1. The focus window (integer).
2. The revert-to policy as a symbol. Possible values:
   - `RevertToParent`
   - `RevertToPointerRoot`
   - `RevertToNone`

---

#### `x-select-input`

```clips
(x-select-input <display> <window> <mask1> <mask2> ... <maskn>)
```

##### Description

Requests the X Server to report events associated with the supplied event masks.

##### Example

```
(x-select-input ?display ?window SubstructureRedirectMask)
```

---

#### `x-warp-pointer`

```clips
(x-warp-pointer <display> <src-window> <dest-window> <src-x> <src-y> <src-width> <src-height> <dest-x> <dest-y>) => <lexeme or integer>
```

##### Description

Moves the pointer (mouse cursor) to a specified location, either relative to a source window or directly into a destination window. NOTE: Does not necessarily move the visual cursor icon on the screen; check the coordinates with `x-query-pointer` after `x-warp-pointer`.

##### Arguments

- `display`: External address to the X11 Display.
- `src-window`: Source window (integer). The pointer is warped relative to this window’s coordinate system. Use 0 if not constraining to a source region.
- `dest-window`: Destination window (integer) where the pointer will be moved. Use 0 to indicate the root or global coordinate space depending on your semantics.
- `src-x` / `src-y` / `src-width` / `src-height`: Defines a source rectangle within src-window. If the current pointer position is outside this rectangle, the warp does not occur. To ignore the source restriction, supply zeros appropriately (as per X11 API).
- `dest-x` / `dest-y`: Coordinates within dest-window to which the pointer will be moved.

#### `black-pixel`
#### `white-pixel`

```clips
(black-pixel <display> <screen>) → <pixel>
(white-pixel <display> <screen>) → <pixel>
```

##### Description

Fetches the black or white pixel value for a screen.

---

### Graphics Context & Drawing

#### `x-create-gc`

```clips
(x-create-gc <display> <drawable> <valuemask>) → <GC-ADDRESS>
```

##### Description

Creates a graphics context; returns an external address. Uses default `XGCValues`.

---

#### `x-set-foreground`

```clips
(x-set-foreground <display> <gc> <pixel>) → <status>
```

##### Description

Sets the foreground color for drawing operations in a `GC`.

---

#### Drawing Primitives

```clips
(x-draw-arc <display> <drawable> <gc> <x> <y> <width> <height> <angle1> <angle2>)
(x-draw-line <display> <drawable> <gc> <x1> <y1> <x2> <y2>)
(x-draw-point <display> <drawable> <gc> <x> <y>)
(x-draw-rectangle <display> <drawable> <gc> <x> <y> <width> <height>)
(x-draw-string <display> <drawable> <gc> <x> <y> <text>)
```

Each wraps the corresponding `XDraw*` call and returns `VOID`.

---

### Event Handling

#### `x-pending`

```clips
(x-pending <display>) → <count>
```

##### Description

Checks how many events are queued.

---

#### `x-peek-event`
#### `x-next-event`

```clips
(x-peek-event <display>) → <multifield>
(x-next-event <display>) → <multifield>
```

##### Description

Retrieves (or waits for) the next `XEvent`, converts it into a CLIPS multifield: 

`[ <xany> <type-symbol> <typed-detail> ]`

##### Return

A multifield consisting of fields combined from the XAny event as well as the type-specific event.

---

#### `x-peek-event-to-fact`
#### `x-next-event-to-fact`

```clips
(x-peek-event-to-fact <display>) → <fact>
(x-next-event-to-fact <display>) → <fact>
```

##### Description

As above, but asserts an `x-event`, `x-any-event`, and a typed fact template.
Check `deftemplates.clp` to see the structure of these deftemplates.

---

#### `x-peek-event-to-instance`
#### `x-next-event-to-instance`

```clips
(x-peek-event-to-instance <display>) → <instance>
(x-next-event-to-instance <display>) → <instance>
```

##### Description

As above, but asserts an `X-EVENT-*` typed COOL instance.
Check `defclasses.clp` to see the structure of these defclasses.

---

#### `x-pop-event`

```clips
(x-pop-event <display>) → VOID
```

##### Description

Removes the next event without returning it. Useful after an `x-peek-event`
to remove it from the event queue.

---

### Keyboard Utilities

#### `x-lookup-string`

```clips
(x-lookup-string <event-address>) → [ <string> <keysym> ]
```

##### Description

Converts a `KeyPress` event to its text and keysym.

---

#### `x-string-to-keysym`

```clips
(x-string-to-keysym <symbol>) → <keysym>
```

##### Description

Maps a key name (e.g. `"Return"`) to its keysym.

---

#### `x-keysym-to-keycode`

```clips
(x-keysym-to-keycode <display> <keysym>) → <keycode>
```

---

#### `x-grab-key`

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

### Screen Conversion

#### `screen-to-fact`

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
- `root-input-mask`

---

#### `screen-to-instance`

```clips
(screen-to-instance <screen-address>) → <instance>
```

##### Description

Builds and asserts a `SCREEN` instance with the same slots listed above.

---

#### `screen-to-multifield`

```clips
(screen-to-multifield <screen-address>) → <multifield>
```

##### Description

Returns the same information as a multifield vector.

---

### Utility

#### `x-event-mask-to-multifield`

```clips
(x-event-mask-to-multifield <mask integer>) → <multifield>
```

#### Description

Converts an integer event mask to a multifield of symbols
representing the event mask names. Possible event masks that will return:

- `KeyPressMask`
- `KeyReleaseMask`
- `ButtonPressMask`
- `ButtonReleaseMask`
- `EnterWindowMask`
- `LeaveWindowMask`
- `PointerMotionMask`
- `PointerMotionHintMask`
- `Button1MotionMask`
- `Button2MotionMask`
- `Button3MotionMask`
- `Button4MotionMask`
- `Button5MotionMask`
- `ButtonMotionMask`
- `KeymapStateMask`
- `ExposureMask`
- `VisibilityChangeMask`
- `StructureNotifyMask`
- `ResizeRedirectMask`
- `SubstructureNotifyMask`
- `SubstructureRedirectMask`
- `FocusChangeMask`
- `PropertyChangeMask`
- `ColormapChangeMask`
- `OwnerGrabButtonMask`

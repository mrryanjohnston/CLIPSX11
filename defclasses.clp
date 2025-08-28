(defclass X-WM-HINTS
  (is-a USER)
  (role concrete)

  (slot flags            (type INTEGER))

  (slot input            (type SYMBOL) (allowed-symbols TRUE FALSE))
  (slot initial_state    (type SYMBOL)
        (allowed-symbols WithdrawnState NormalState IconicState))

  (slot icon_pixmap      (type INTEGER))
  (slot icon_window      (type INTEGER))
  (slot icon_x           (type INTEGER))
  (slot icon_y           (type INTEGER))
  (slot icon_mask        (type INTEGER))
  (slot window_group     (type INTEGER)))

(defclass X-SIZE-HINTS
 (is-a USER)
 (role concrete)

 (slot flags            (type INTEGER))

 (slot x                (type INTEGER))
 (slot y                (type INTEGER))
 (slot width            (type INTEGER))
 (slot height           (type INTEGER))

 (slot min_width        (type INTEGER))
 (slot min_height       (type INTEGER))

 (slot max_width        (type INTEGER))
 (slot max_height       (type INTEGER))

 (slot width_inc        (type INTEGER))
 (slot height_inc       (type INTEGER))

 (slot min_aspect_num   (type INTEGER))
	(slot min_aspect_den   (type INTEGER))
	(slot max_aspect_num   (type INTEGER))
(slot max_aspect_den   (type INTEGER))

	(slot base_width       (type INTEGER))
(slot base_height      (type INTEGER))

	(slot win_gravity
	 (type SYMBOL)
	 (allowed-symbols
	  ForgetGravity
	  NorthWestGravity NorthGravity NorthEastGravity
	  WestGravity      CenterGravity      EastGravity
	  SouthWestGravity SouthGravity SouthEastGravity
	  StaticGravity)))
(defclass X-WINDOW-ATTRIBUTES
	(is-a USER)
	(slot x
		(type INTEGER))
	(slot y
		(type INTEGER))
	(slot width
		(type INTEGER))
	(slot height
		(type INTEGER))
	(slot border-width
		(type INTEGER))
	(slot depth
		(type INTEGER))
	(slot visual
		(type EXTERNAL-ADDRESS))
	(slot root
		(type INTEGER))
	(slot class
		(type INTEGER))
	(slot bit-gravity
		(type INTEGER))
	(slot win-gravity
		(type INTEGER))
	(slot backing-store
		(type INTEGER))
	(slot backing-planes
		(type INTEGER))
	(slot backing-pixel
		(type INTEGER))
	(slot save-under
		(type SYMBOL))
	(slot colormap
		(type INTEGER))
	(slot map-installed
		(type SYMBOL))
	(slot map-state
		(type SYMBOL))
	(multislot all-event-masks
		(type SYMBOL))
	(multislot your-event-mask
		(type SYMBOL))
	(multislot do-not-propagate-mask
		(type SYMBOL))
	(slot override-redirect
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot screen
		(type EXTERNAL-ADDRESS)))
(defclass SCREEN
	(is-a USER)
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot ext-data
		(type EXTERNAL-ADDRESS))
	(slot display
		(type EXTERNAL-ADDRESS))
	(slot root
		(type INTEGER))
	(slot width
		(type INTEGER))
	(slot height
		(type INTEGER))
	(slot mwidth
		(type INTEGER))
	(slot mheight
		(type INTEGER))
	(slot ndepths
		(type INTEGER))
	(slot root-depth
		(type INTEGER))
	(slot white-pixel
		(type INTEGER))
	(slot black-pixel
		(type INTEGER))
	(slot max-maps
		(type INTEGER))
	(slot min-maps
		(type INTEGER))
	(slot backing-store
		(type SYMBOL)
		(allowed-values
			NotUseful
			WhenMapped
			Always))
	(slot save-unders
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot root-input-mask
		(type INTEGER)))

(defclass X-EVENT
	(is-a USER)
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot type
		(type SYMBOL)
		(allowed-values
			ButtonPress
			ButtonRelease
			ColormapNotify
			CirculateNotify
			ClientMessage
			ConfigureNotify
			CreateNotify
			DestroyNotify
			EnterNotify
			Expose
			FocusIn
			FocusOut
			GraphicsExpose
			GravityNotify
			KeymapNotify
			KeyPress
			KeyRelease
			LeaveNotify
			MapNotify
			MappingNotify
			MotionNotify
			NoExpose
			PropertyNotify
			ResizeRequest
			ReparentNotify
			SelectionClear
			SelectionNotify
			SelectionRequest
			UnmapNotify
			VisibilityNotify))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS)))

(defclass X-KEY-EVENT
	(is-a X-EVENT)
	(slot type
		(type SYMBOL)
		(allowed-values
			KeyPress
			KeyRelease))
	(slot window
		(type INTEGER))
	(slot root
		(type INTEGER))
	(slot subwindow
		(type INTEGER))
	(slot time
		(type INTEGER))
	(slot x
		(type INTEGER))
	(slot y
		(type INTEGER))
	(slot x-root
		(type INTEGER))
	(slot y-root
		(type INTEGER))
	(multislot state
		(type SYMBOL)
		(allowed-values
			ShiftMask
			LockMask
			ControlMask
			Mod1Mask
			Mod2Mask
			Mod3Mask
			Mod4Mask
			Mod5Mask))
	(slot keycode
		(type INTEGER))
	(slot same-screen
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot buffer
		(type STRING))
	(slot keysym
		(type INTEGER))
	(slot compose-ptr
		(type EXTERNAL-ADDRESS))
	(slot chars-matched
		(type INTEGER)))

(defclass X-BUTTON-EVENT
	(is-a X-EVENT)
	(slot type
		(type SYMBOL)
		(allowed-values
			ButtonPress
			ButtonRelease))
	(slot window
		(type INTEGER))
	(slot root
		(type INTEGER))
	(slot subwindow
		(type INTEGER))
	(slot time
		(type INTEGER))
	(slot x
		(type INTEGER))
	(slot y
		(type INTEGER))
	(slot x-root
		(type INTEGER))
	(slot y-root
		(type INTEGER))
	(multislot state
		(type SYMBOL)
		(allowed-values
			ShiftMask
			LockMask
			ControlMask
			Mod1Mask
			Mod2Mask
			Mod3Mask
			Mod4Mask
			Mod5Mask))
	(slot button
		(type INTEGER))
	(slot same-screen
		(type SYMBOL)
		(allowed-values TRUE FALSE)))

(defclass X-MOTION-EVENT
	(is-a X-EVENT)
	(slot type
		(type SYMBOL)
		(allowed-values
			MotionNotify))
	(slot window
		(type INTEGER))
	(slot root
		(type INTEGER))
	(slot subwindow
		(type INTEGER))
	(slot time
		(type INTEGER))
	(slot x
		(type INTEGER))
	(slot y
		(type INTEGER))
	(slot x-root
		(type INTEGER))
	(slot y-root
		(type INTEGER))
	(multislot state
		(type SYMBOL)
		(allowed-values
			Button1Mask
			Button2Mask
			Button3Mask
			Button4Mask
			Button5Mask))
	(slot is-hint
		(type SYMBOL)
		(allowed-values NotifyNormal NotifyHint))
	(slot same-screen
		(type SYMBOL)
		(allowed-values TRUE FALSE)))

(defclass X-CROSSING-EVENT
	(is-a X-EVENT)
	(slot type
		(type SYMBOL)
		(allowed-values
			EnterNotify
			LeaveNotify))
	(slot window
		(type INTEGER))
	(slot root
		(type INTEGER))
	(slot subwindow
		(type INTEGER))
	(slot time
		(type INTEGER))
	(slot x
		(type INTEGER))
	(slot y
		(type INTEGER))
	(slot x-root
		(type INTEGER))
	(slot y-root
		(type INTEGER))
	(slot mode
		(type SYMBOL)
		(allowed-values
			NotifyNormal
			NotifyGrab
			NotifyUngrab))
	(slot detail
		(type SYMBOL)
		(allowed-values
			NotifyAncestor
			NotifyVirtual
			NotifyInferior
			NotifyNonlinear
			NotifyNonlinearVirtual))
	(slot same-screen
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot focus
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(multislot state
		(type SYMBOL)
		(allowed-values
			ShiftMask
			LockMask
			ControlMask
			Mod1Mask
			Mod2Mask
			Mod3Mask
			Mod4Mask
			Mod5Mask
			Button1Mask
			Button2Mask
			Button3Mask
			Button4Mask
			Button5Mask)))

(defclass X-FOCUS-CHANGE-EVENT
	(is-a X-EVENT)
	(slot type
		(type SYMBOL)
		(allowed-values
			FocusIn
			FocusOut))
	(slot window
		(type INTEGER))
	(slot mode
		(type SYMBOL)
		(allowed-values
			NotifyNormal
			NotifyGrab
			NotifyUngrab))
	(slot detail
		(type SYMBOL)
		(allowed-values
			NotifyAncestor
			NotifyVirtual
			NotifyInferior
			NotifyNonlinear
			NotifyNonlinearVirtual
			NotifyPointer
			NotifyPointerRoot
			NotifyDetailNone)))

(defclass X-KEYMAP-EVENT
	(is-a X-EVENT)
	(slot type
		(type SYMBOL)
		(allowed-values
			Keymap))
	(slot window
		(type INTEGER))
	(multislot key-down
		(type SYMBOL))
	(multislot key-vector
		(type SYMBOL)))

(defclass X-EXPOSE-EVENT
	(is-a X-EVENT)
	(slot type
		(type SYMBOL)
		(allowed-values
			Expose))
	(slot window
		(type INTEGER))
	(slot x
		(type INTEGER))
	(slot y
		(type INTEGER))
	(slot width
		(type INTEGER))
	(slot height
		(type INTEGER))
	(slot count
		(type INTEGER)))

(defclass X-GRAPHICS-EXPOSE-EVENT
	(is-a X-EVENT)
	(slot type
		(type SYMBOL)
		(allowed-values
			Graphics))
	(slot drawable
		(type INTEGER))
	(slot x
		(type INTEGER))
	(slot y
		(type INTEGER))
	(slot width
		(type INTEGER))
	(slot height
		(type INTEGER))
	(slot count
		(type INTEGER))
	(slot major-code
		(type INTEGER))
	(slot minor-code
		(type INTEGER)))

(defclass X-NO-EXPOSE-EVENT
	(is-a X-EVENT)
	(slot type
		(type SYMBOL)
		(allowed-values
			NoExpose))
	(slot drawable
		(type INTEGER))
	(slot major-code
		(type INTEGER))
	(slot minor-code
		(type INTEGER)))

(defclass X-VISIBILITY-EVENT
	(is-a X-EVENT)
	(slot type
		(type SYMBOL)
		(allowed-values
			VisibilityNotify))
	(slot window
		(type INTEGER))
	(slot state
		(type SYMBOL)
		(allowed-values
			VisibilityUnobscured
			VisibilityPartiallyObscured
			VisibilityFullyObscured)))

(defclass X-CREATE-WINDOW-EVENT
	(is-a X-EVENT)
	(slot type
		(type SYMBOL)
		(allowed-values
			CreateNotify))
	(slot parent
		(type INTEGER))
	(slot window
		(type INTEGER))
	(slot x
		(type INTEGER))
	(slot y
		(type INTEGER))
	(slot width
		(type INTEGER))
	(slot height
		(type INTEGER))
	(slot border-width
		(type INTEGER))
	(slot override-redirect
		(type SYMBOL)
		(allowed-values TRUE FALSE)))

(defclass X-DESTROY-WINDOW-EVENT
	(is-a X-EVENT)
	(slot type
		(type SYMBOL)
		(allowed-values
			DestroyNotify))
	(slot event
		(type INTEGER))
	(slot window
		(type INTEGER)))

(defclass X-UNMAP-EVENT
	(is-a X-EVENT)
	(slot type
		(type SYMBOL)
		(allowed-values
			UnmapNotify))
	(slot event
		(type INTEGER))
	(slot window
		(type INTEGER))
	(slot from-configure
		(type SYMBOL)
		(allowed-values TRUE FALSE)))

(defclass X-MAP-EVENT
	(is-a X-EVENT)
	(slot type
		(type SYMBOL)
		(allowed-values
			MapNotify))
	(slot event
		(type INTEGER))
	(slot window
		(type INTEGER))
	(slot override-redirect
		(type SYMBOL)
		(allowed-values TRUE FALSE)))

(defclass X-MAP-REQUEST-EVENT
	(is-a X-EVENT)
	(slot type
		(type SYMBOL)
		(allowed-values
			MapRequest))
	(slot parent
		(type INTEGER))
	(slot window
		(type INTEGER)))

(defclass X-REPARENT-EVENT
	(is-a X-EVENT)
	(slot type
		(type SYMBOL)
		(allowed-values
			ReparentNotify))
	(slot event
		(type INTEGER))
	(slot parent
		(type INTEGER))
	(slot x
		(type INTEGER))
	(slot y
		(type INTEGER))
	(slot override-redirect
		(type SYMBOL)
		(allowed-values TRUE FALSE)))

(defclass X-CONFIGURE-EVENT
	(is-a X-EVENT)
	(slot type
		(type SYMBOL)
		(allowed-values
			ConfigureNotify))
	(slot event
		(type INTEGER))
	(slot window
		(type INTEGER))
	(slot x
		(type INTEGER))
	(slot y
		(type INTEGER))
	(slot border-width
		(type INTEGER))
	(slot above
		(type INTEGER))
	(slot override-redirect
		(type SYMBOL)
		(allowed-values TRUE FALSE)))

(defclass X-CONFIGURE-REQUEST-EVENT
	(is-a X-EVENT)
	(slot type
		(type SYMBOL)
		(allowed-values
			ConfigureRequest))
	(slot parent
		(type INTEGER))
	(slot window
		(type INTEGER))
	(slot x
		(type INTEGER))
	(slot y
		(type INTEGER))
	(slot width
		(type INTEGER))
	(slot height
		(type INTEGER))
	(slot border-width
		(type INTEGER))
	(slot above
		(type INTEGER))
	(slot detail
		(type SYMBOL)
		(allowed-values Above Below TopIf BottomIf Opposite))
	(multislot value-mask
		(type SYMBOL)
		(allowed-values
			CWX
			CWY
			CWWidth
			CWHeight
			CWBorderWidth
			CWSibling
			CWStackMode)))

(defclass X-GRAVITY-EVENT
	(is-a X-EVENT)
	(slot type
		(type SYMBOL)
		(allowed-values
			GravityNotify))
	(slot event
		(type INTEGER))
	(slot window
		(type INTEGER))
	(slot x
		(type INTEGER))
	(slot y
		(type INTEGER)))

(defclass X-RESIZE-REQUEST-EVENT
	(is-a X-EVENT)
	(slot type
		(type SYMBOL)
		(allowed-values
			ResizeRequest))
	(slot window
		(type INTEGER))
	(slot width
		(type INTEGER))
	(slot height
		(type INTEGER)))

(defclass X-CIRCULATE-EVENT
	(is-a X-EVENT)
	(slot type
		(type SYMBOL)
		(allowed-values
			CirculateNotify))
	(slot event
		(type INTEGER))
	(slot window
		(type INTEGER))
	(slot place
		(type SYMBOL)
		(allowed-values
			PlaceOnTop
			PlaceOnBottom)))

(defclass X-CIRCULATE-REQUEST-EVENT
	(is-a X-EVENT)
	(slot type
		(type SYMBOL)
		(allowed-values
			CirculateRequest))
	(slot parent
		(type INTEGER))
	(slot window
		(type INTEGER))
	(slot place
		(type SYMBOL)
		(allowed-values
			PlaceOnTop
			PlaceOnBottom)))

(defclass X-PROPERTY-EVENT
	(is-a X-EVENT)
	(slot type
		(type SYMBOL)
		(allowed-values
			PropertyNotify))
	(slot window
		(type INTEGER))
	(slot atom
		(type INTEGER))
	(slot time
		(type INTEGER))
	(slot state
		(type SYMBOL)
		(allowed-values
			PropertyNewValue
			PropertyDelete)))

(defclass X-SELECTION-CLEAR-EVENT
	(is-a X-EVENT)
	(slot type
		(type SYMBOL)
		(allowed-values
			SelectionClear))
	(slot window
		(type INTEGER))
	(slot selection
		(type INTEGER))
	(slot time
		(type INTEGER)))

(defclass X-SELECTION-REQUEST-EVENT
	(is-a X-EVENT)
	(slot type
		(type SYMBOL)
		(allowed-values
			SelectionRequest))
	(slot owner
		(type INTEGER))
	(slot requestor
		(type INTEGER))
	(slot selection
		(type INTEGER))
	(slot target
		(type INTEGER))
	(slot property
		(type INTEGER SYMBOL))
	(slot time
		(type INTEGER)))

(defclass X-SELECTION-EVENT
	(is-a X-EVENT)
	(slot type
		(type SYMBOL)
		(allowed-values
			SelectionNotify))
	(slot requestor
		(type INTEGER))
	(slot selection
		(type INTEGER))
	(slot target
		(type INTEGER))
	(slot property
		(type INTEGER SYMBOL))
	(slot time
		(type INTEGER)))

(defclass X-COLORMAP-EVENT
	(is-a X-EVENT)
	(slot type
		(type SYMBOL)
		(allowed-values
			ColormapNotify))
	(slot window
		(type INTEGER))
	(slot colormap
		(type INTEGER SYMBOL))
	(slot new
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot state
		(type SYMBOL)
		(allowed-values
			ColormapInstalled
			ColormapUninstalled)))

(defclass X-CLIENT-MESSAGE-EVENT
	(is-a X-EVENT)
	(slot type
		(type SYMBOL)
		(allowed-values
			ClientMessage))
	(slot window
		(type INTEGER))
	(slot message-type
		(type INTEGER))
	(slot format
		(type INTEGER))
	(multislot data))

(defclass X-MAPPING-EVENT
	(is-a X-EVENT)
	(slot type
		(type SYMBOL)
		(allowed-values
			MappingNotify))
	(slot window
		(type INTEGER))
	(slot request
		(type SYMBOL)
		(allowed-values
			MappingModifier
			MappingKeyboard
			MappingPointer))
	(slot first-keycode
		(type INTEGER))
	(slot count
		(type INTEGER)))

(defclass X-GENERIC-EVENT
	(is-a X-EVENT)
	(slot type
		(type SYMBOL)
		(allowed-values
			GenericNotify))
	(slot extension
		(type INTEGER))
	(slot evtype
		(type INTEGER)))

(defclass X-ERROR
	(is-a USER)
	(slot serial
		(type INTEGER))
	(slot error-code
		(type INTEGER))
	(slot request-code
		(type INTEGER))
	(slot minor-code
		(type INTEGER))
	(slot resourceid
		(type INTEGER)))

(deftemplate x-window-attributes
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

(deftemplate screen
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

(deftemplate x-event
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
	(slot typed-event
		(type FACT-ADDRESS)))

(deftemplate x-any-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS))
	(slot window
		(type INTEGER)))

(deftemplate x-key-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot type
		(type SYMBOL)
		(allowed-values
			KeyPress
			KeyRelease))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS))
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

(deftemplate x-button-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot type
		(type SYMBOL)
		(allowed-values
			ButtonPress
			ButtonRelease))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS))
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

(deftemplate x-motion-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot type
		(type SYMBOL)
		(allowed-values
			MotionNotify))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS))
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

(deftemplate x-crossing-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot type
		(type SYMBOL)
		(allowed-values
			EnterNotify
			LeaveNotify))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS))
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

(deftemplate x-focus-change-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot type
		(type SYMBOL)
		(allowed-values
			FocusIn
			FocusOut))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS))
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

(deftemplate x-keymap-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot type
		(type SYMBOL)
		(allowed-values
			Keymap))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS))
	(slot window
		(type INTEGER))
	(multislot key-down
		(type SYMBOL))
	(multislot key-vector
		(type SYMBOL)))

(deftemplate x-expose-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot type
		(type SYMBOL)
		(allowed-values
			Expose))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS))
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

(deftemplate x-graphics-expose-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot type
		(type SYMBOL)
		(allowed-values
			Graphics))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS))
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

(deftemplate x-no-expose-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot type
		(type SYMBOL)
		(allowed-values
			NoExpose))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS))
	(slot drawable
		(type INTEGER))
	(slot major-code
		(type INTEGER))
	(slot minor-code
		(type INTEGER)))

(deftemplate x-visibility-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot type
		(type SYMBOL)
		(allowed-values
			VisibilityNotify))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS))
	(slot window
		(type INTEGER))
	(slot state
		(type SYMBOL)
		(allowed-values
			VisibilityUnobscured
			VisibilityPartiallyObscured
			VisibilityFullyObscured)))

(deftemplate x-create-window-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot type
		(type SYMBOL)
		(allowed-values
			CreateNotify))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS))
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

(deftemplate x-destroy-window-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot type
		(type SYMBOL)
		(allowed-values
			DestroyNotify))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS))
	(slot event
		(type INTEGER))
	(slot window
		(type INTEGER)))

(deftemplate x-unmap-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot type
		(type SYMBOL)
		(allowed-values
			UnmapNotify))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS))
	(slot event
		(type INTEGER))
	(slot window
		(type INTEGER))
	(slot from-configure
		(type SYMBOL)
		(allowed-values TRUE FALSE)))

(deftemplate x-map-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot type
		(type SYMBOL)
		(allowed-values
			MapNotify))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS))
	(slot event
		(type INTEGER))
	(slot window
		(type INTEGER))
	(slot override-redirect
		(type SYMBOL)
		(allowed-values TRUE FALSE)))

(deftemplate x-map-request-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot type
		(type SYMBOL)
		(allowed-values
			MapRequest))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS))
	(slot parent
		(type INTEGER))
	(slot window
		(type INTEGER)))

(deftemplate x-reparent-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot type
		(type SYMBOL)
		(allowed-values
			ReparentNotify))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS))
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

(deftemplate x-configure-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot type
		(type SYMBOL)
		(allowed-values
			ConfigureNotify))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS))
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

(deftemplate x-configure-request-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot type
		(type SYMBOL)
		(allowed-values
			ConfigureRequest))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS))
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

(deftemplate x-gravity-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot type
		(type SYMBOL)
		(allowed-values
			GravityNotify))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS))
	(slot event
		(type INTEGER))
	(slot window
		(type INTEGER))
	(slot x
		(type INTEGER))
	(slot y
		(type INTEGER)))

(deftemplate x-resize-request-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot type
		(type SYMBOL)
		(allowed-values
			ResizeRequest))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS))
	(slot window
		(type INTEGER))
	(slot width
		(type INTEGER))
	(slot height
		(type INTEGER)))

(deftemplate x-circulate-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot type
		(type SYMBOL)
		(allowed-values
			CirculateNotify))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS))
	(slot event
		(type INTEGER))
	(slot window
		(type INTEGER))
	(slot place
		(type SYMBOL)
		(allowed-values
			PlaceOnTop
			PlaceOnBottom)))

(deftemplate x-circulate-request-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot type
		(type SYMBOL)
		(allowed-values
			CirculateRequest))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS))
	(slot parent
		(type INTEGER))
	(slot window
		(type INTEGER))
	(slot place
		(type SYMBOL)
		(allowed-values
			PlaceOnTop
			PlaceOnBottom)))

(deftemplate x-property-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot type
		(type SYMBOL)
		(allowed-values
			PropertyNotify))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS))
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

(deftemplate x-selection-clear-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot type
		(type SYMBOL)
		(allowed-values
			SelectionClear))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS))
	(slot window
		(type INTEGER))
	(slot selection
		(type INTEGER))
	(slot time
		(type INTEGER)))

(deftemplate x-selection-request-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot type
		(type SYMBOL)
		(allowed-values
			SelectionRequest))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS))
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

(deftemplate x-selection-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot type
		(type SYMBOL)
		(allowed-values
			SelectionNotify))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS))
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

(deftemplate x-colormap-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot type
		(type SYMBOL)
		(allowed-values
			ColormapNotify))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS))
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

(deftemplate x-client-message-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot type
		(type SYMBOL)
		(allowed-values
			ClientMessage))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS))
	(slot window
		(type INTEGER))
	(slot message-type
		(type INTEGER))
	(slot format
		(type INTEGER))
	(multislot data))

(deftemplate x-mapping-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot type
		(type SYMBOL)
		(allowed-values
			MappingNotify))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS))
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

(deftemplate x-generic-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot type
		(type SYMBOL)
		(allowed-values
			GenericNotify))
	(slot serial
		(type INTEGER))
	(slot send-event
		(type SYMBOL)
		(allowed-values TRUE FALSE))
	(slot display
		(type EXTERNAL-ADDRESS))
	(slot extension
		(type INTEGER))
	(slot evtype
		(type INTEGER)))

(deftemplate x-error-event
	(slot c-pointer
		(type EXTERNAL-ADDRESS))
	(slot error-code
		(type INTEGER))
	(slot request-code
		(type INTEGER))
	(slot minor-code
		(type INTEGER))
	(slot resourceid
		(type INTEGER)))

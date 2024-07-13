(deftemplate x-event
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
		(type INTEGER))
	(slot window
		(type INTEGER)))

(deftemplate x-button-event
	(slot x-event
		(type FACT-ADDRESS))
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

(deftemplate x-key-event
	(slot x-event
		(type FACT-ADDRESS))
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
		(type FACT-ADDRESS))
	(slot chars-matched
		(type INTEGER)))

(deftemplate x-motion-event
	(slot x-event
		(type FACT-ADDRESS))
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
	(slot x-event
		(type FACT-ADDRESS))
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
	(slot x-event
		(type FACT-ADDRESS))
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

(deftemplate x-expose-event
	(slot x-event
		(type FACT-ADDRESS))
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
	(slot x-event
		(type FACT-ADDRESS))
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
	(slot x-event
		(type FACT-ADDRESS))
	(slot drawable
		(type INTEGER))
	(slot major-code
		(type INTEGER))
	(slot minor-code
		(type INTEGER)))

(deftemplate x-visibility-event
	(slot x-event
		(type FACT-ADDRESS))
	(slot state
		(type SYMBOL)
		(allowed-values
			VisibilityUnobscured
			VisibilityPartiallyObscured
			VisibilityFullyObscured)))

(deftemplate x-create-window-event
	(slot x-event
		(type FACT-ADDRESS))
	(slot parent
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
		(allowed-values TRUE FALSE))

(deftemplate x-destroy-window-event
	(slot x-event
		(type FACT-ADDRESS))
	(slot event
		(type INTEGER)))

(deftemplate x-unmap-event
	(slot x-event
		(type FACT-ADDRESS))
	(slot event
		(type INTEGER))
	(slot from-configure
		(type SYMBOL)
		(allowed-values TRUE FALSE)))

(deftemplate x-map-event
	(slot x-event
		(type FACT-ADDRESS))
	(slot event
		(type INTEGER))
	(slot override-redirect
		(type SYMBOL)
		(allowed-values TRUE FALSE)))

(deftemplate x-map-request-event
	(slot x-event
		(type FACT-ADDRESS))
	(slot parent
		(type INTEGER)))

(deftemplate x-reparent-event
	(slot x-event
		(type FACT-ADDRESS))
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
	(slot x-event
		(type FACT-ADDRESS))
	(slot event
		(type INTEGER))
	(slot parent
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

(deftemplate x-gravity-event
	(slot x-event
		(type FACT-ADDRESS))
	(slot event
		(type INTEGER))
	(slot x
		(type INTEGER))
	(slot y
		(type INTEGER)))

(deftemplate x-resize-request-event
	(slot x-event
		(type FACT-ADDRESS))
	(slot width
		(type INTEGER))
	(slot height
		(type INTEGER)))

(deftemplate x-configure-request-event
	(slot x-event
		(type FACT-ADDRESS))
	(slot parent
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

(deftemplate x-circulate-event
	(slot x-event
		(type FACT-ADDRESS))
	(slot event
		(type INTEGER))
	(slot place
		(type SYMBOL)
		(allowed-values
			PlaceOnTop
			PlaceOnBottom)))

(deftemplate x-circulate-request-event
	(slot x-event
		(type FACT-ADDRESS))
	(slot parent
		(type INTEGER))
	(slot place
		(type SYMBOL)
		(allowed-values
			PlaceOnTop
			PlaceOnBottom)))

(deftemplate x-property-event
	(slot x-event
		(type FACT-ADDRESS))
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
	(slot x-event
		(type FACT-ADDRESS))
	(slot selection
		(type INTEGER))
	(slot time
		(type INTEGER)))

(deftemplate x-selection-request-event
	(slot x-event
		(type FACT-ADDRESS))
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
	(slot x-event
		(type FACT-ADDRESS))
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
	(slot x-event
		(type FACT-ADDRESS))
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
	(slot x-event
		(type FACT-ADDRESS))
	(slot message-type
		(type INTEGER))
	(slot format
		(type INTEGER))
	(multislot data))

(deftemplate x-mapping-event
	(slot x-event
		(type FACT-ADDRESS))
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

(deftemplate x-keymap-event
	(slot x-event
		(type FACT-ADDRESS))
	(multislot key-vector
		(type SYMBOL)))

(deftemplate x-error-event
	(slot x-event
		(type FACT-ADDRESS))
	(slot error-code
		(type INTEGER))
	(slot request-code
		(type INTEGER))
	(slot minor-code
		(type INTEGER))
	(slot resourceid
		(type INTEGER)))

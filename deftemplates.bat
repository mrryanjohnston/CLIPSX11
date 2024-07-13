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
		(allowed-values TRUE FALSE)))

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

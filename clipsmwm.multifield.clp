(defrule always =>
	(bind ?display (x-open-display :0))
	(assert (display ?display))
	(assert (screen (screen-to-multifield (default-screen-of-display ?display))))
	(bind ?window (default-root-window ?display))
	(bind ?cursor (x-create-font-cursor ?display XC_left_ptr))
	(x-define-cursor ?display ?window ?cursor)
	(x-select-input ?display ?window SubstructureRedirectMask)
	(x-grab-key ?display (x-keysym-to-keycode ?display (x-string-to-keysym "n")) Mod4 ?window TRUE GrabModeAsync GrabModeAsync)
	(x-grab-key ?display (x-keysym-to-keycode ?display (x-string-to-keysym "q")) Mod4 ?window TRUE GrabModeAsync GrabModeAsync)
	(x-grab-key ?display (x-keysym-to-keycode ?display (x-string-to-keysym "e")) Mod4 ?window TRUE GrabModeAsync GrabModeAsync)
	(assert (next-event (x-next-event ?display))))

(defrule on-map-request
	(screen ? ? ? ? ?width ?height $?)
	?event <- (next-event
		?serial
		?send_event
		?display
		?parent
		MapRequest
		?parent
		?window)
	=>
	(x-map-window ?display ?window)
	(x-move-resize-window ?display ?window 0 0 ?width ?height)
	(x-set-input-focus ?display ?window RevertToParent 0)
	(retract ?event)
	(assert (next-event (x-next-event ?display))))

(defrule on-key-press-n
	?event <- (next-event
		?serial
		?send_event
		?display
		?window
		KeyPress
		?root
		?subwindow
		?time
		?x
		?y
		?x_root
		?y_root
		?
		=(x-keysym-to-keycode ?display (x-string-to-keysym "n"))
		$?)
	=>
	(x-circulate-subwindows-up ?display ?root)
	(x-set-input-focus ?display ?window RevertToParent 0)
	(retract ?event)
	(assert (next-event (x-next-event ?display))))

(defrule on-key-press-q
	?event <- (next-event
		?serial
		?send_event
		?display
		?window
		KeyPress
		?root
		?subwindow
		?time
		?x
		?y
		?x_root
		?y_root
		?
		=(x-keysym-to-keycode ?display (x-string-to-keysym "q"))
		$?)
	=>
	(x-kill-client ?display ?subwindow)
	(retract ?event)
	(assert (next-event (x-next-event ?display))))

(defrule on-key-press-e
	?event <- (next-event
		?serial
		?send_event
		?display
		?window
		KeyPress
		?root
		?subwindow
		?time
		?x
		?y
		?x_root
		?y_root
		?
		=(x-keysym-to-keycode ?display (x-string-to-keysym "e"))
		$?)
	=>
	(system "dmenu_run &")
	(retract ?event)
	(assert (next-event (x-next-event ?display))))

(defrule everything-else
	(declare (salience -1))
	(display ?display)
	?event <- (next-event $?)
	=>
	(retract ?event)
	(assert (next-event (x-next-event ?display))))

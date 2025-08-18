(deffunction grab-keys (?display ?window $?keys)
	(foreach ?key ?keys 
		(x-grab-key ?display (x-keysym-to-keycode ?display (x-string-to-keysym ?key)) (lexeme-to-mask Mod4Mask) ?window TRUE GrabModeAsync GrabModeAsync)))

(defrule always =>
	(bind ?display (x-open-display :0))
	(screen-to-instance (default-screen-of-display ?display))
	(bind ?window (default-root-window ?display))
	(x-select-input ?display ?window SubstructureRedirectMask)
	(grab-keys ?display ?window "e" "n" "q")
	(x-next-event-to-instance ?display))

(defrule on-map-request
	(object (is-a SCREEN) (width ?width) (height ?height))
	?event <- (object (is-a X-MAP-REQUEST-EVENT) (display ?display) (window ?window) (parent ?parent))
	=>
	(x-map-window ?display ?window)
	(x-move-resize-window ?display ?window 0 0 ?width ?height)
	(x-set-input-focus ?display ?window RevertToParent 0)
	(unmake-instance ?event)
	(x-next-event-to-instance ?display))

(defrule on-key-press-n
	?event <- (object (is-a X-KEY-EVENT) (type KeyPress) (display ?display) (window ?window) (root ?root) (keycode ?keycode))
	(test (= ?keycode (x-keysym-to-keycode ?display (x-string-to-keysym "n"))))
	=>
	(x-circulate-subwindows-up ?display ?root)
	(x-set-input-focus ?display ?window RevertToParent 0)
	(unmake-instance ?event)
	(x-next-event-to-instance ?display))

(defrule on-key-press-q
	?event <- (object (is-a X-KEY-EVENT) (type KeyPress) (display ?display) (keycode ?keycode) (subwindow ?subwindow))
	(test (= ?keycode (x-keysym-to-keycode ?display (x-string-to-keysym "q"))))
	=>
	(x-kill-client ?display ?subwindow)
	(unmake-instance ?event)
	(x-next-event-to-instance ?display))

(defrule on-key-press-e
	?event <- (object (is-a X-KEY-EVENT) (type KeyPress) (display ?display) (keycode ?keycode))
	(test (= ?keycode (x-keysym-to-keycode ?display (x-string-to-keysym "e"))))
	=>
	(system "dmenu_run &")
	(unmake-instance ?event)
	(x-next-event-to-instance ?display))

(defrule everything-else
	(declare (salience -1))
	?event <- (object (is-a X-EVENT) (display ?display))
	=>
	(unmake-instance ?event)
	(x-next-event-to-instance ?display))

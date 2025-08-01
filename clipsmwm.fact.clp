(deffunction grab-keys (?display ?window $?keys)
	(foreach ?key ?keys 
		(x-grab-key ?display (x-keysym-to-keycode ?display (x-string-to-keysym ?key)) Mod4Mask ?window TRUE GrabModeAsync GrabModeAsync)))

(defrule always =>
	(bind ?display (x-open-display :0))
	(screen-to-fact (default-screen-of-display ?display))
	(bind ?window (default-root-window ?display))
	(x-select-input ?display ?window SubstructureRedirectMask)
	(grab-keys ?display ?window "e" "n" "q")
	(x-next-event-to-fact ?display))

(defrule on-map-request
	(screen (width ?width) (height ?height))
	?aevent <- (x-any-event (display ?display) (window ?parent))
	?tevent <- (x-map-request-event (parent ?parent) (window ?window))
	?event <- (x-event (x-any-event ?aevent) (typed-event ?tevent))
	=>
	(x-map-window ?display ?window)
	(x-move-resize-window ?display ?window 0 0 ?width ?height)
	(x-set-input-focus ?display ?window RevertToParent 0)
	(retract ?event ?aevent ?tevent)
	(x-next-event-to-fact ?display))

(defrule on-key-press-n
	?aevent <- (x-any-event (display ?display) (window ?window))
	?tevent <- (x-key-event (root ?root) (keycode ?keycode))
	?event <- (x-event (type KeyPress) (x-any-event ?aevent) (typed-event ?tevent))
	(test (= ?keycode (x-keysym-to-keycode ?display (x-string-to-keysym "n"))))
	=>
	(x-circulate-subwindows-up ?display ?root)
	(x-set-input-focus ?display ?window RevertToParent 0)
	(retract ?event ?aevent ?tevent)
	(x-next-event-to-fact ?display))

(defrule on-key-press-q
	?aevent <- (x-any-event (display ?display))
	?tevent <- (x-key-event (keycode ?keycode) (subwindow ?subwindow))
	?event <- (x-event (type KeyPress) (x-any-event ?aevent) (typed-event ?tevent))
	(test (= ?keycode (x-keysym-to-keycode ?display (x-string-to-keysym "q"))))
	=>
	(x-kill-client ?display ?subwindow)
	(retract ?event ?aevent ?tevent)
	(x-next-event-to-fact ?display))

(defrule on-key-press-e
	?aevent <- (x-any-event (display ?display))
	?tevent <- (x-key-event (keycode ?keycode))
	?event <- (x-event (type KeyPress) (x-any-event ?aevent) (typed-event ?tevent))
	(test (= ?keycode (x-keysym-to-keycode ?display (x-string-to-keysym "e"))))
	=>
	(system "dmenu_run &")
	(retract ?event ?aevent ?tevent)
	(x-next-event-to-fact ?display))

(defrule everything-else
	(declare (salience -1))
	?aevent <- (x-any-event (display ?display))
	?event <- (x-event (x-any-event ?aevent) (typed-event ?tevent))
	=>
	(retract ?event ?aevent ?tevent)
	(x-next-event-to-fact ?display))

(deffunction grab-keys (?display ?window $?keys)
	(foreach ?key ?keys 
		(x-grab-key ?display (x-keysym-to-keycode ?display (x-string-to-keysym ?key)) (lexeme-to-mask Mod4Mask) ?window TRUE GrabModeAsync GrabModeAsync)))

(defrule always =>
	(bind ?display (x-open-display :0))
	(screen-to-fact (default-screen-of-display ?display))
	(bind ?window (default-root-window ?display))
	(x-select-input ?display ?window SubstructureRedirectMask)
	(grab-keys ?display ?window "e" "n" "q")
	(x-next-event-to-fact ?display))

(defrule on-map-request
	(screen (width ?width) (height ?height))
	?event <- (x-map-request-event (display ?display) (window ?window) (parent ?parent))
	?x <- (x-event (typed-event ?event))
	=>
	(x-map-window ?display ?window)
	(x-move-resize-window ?display ?window 0 0 ?width ?height)
	(x-set-input-focus ?display ?window RevertToParent 0)
	(retract ?event ?x)
	(x-next-event-to-fact ?display))

(defrule on-key-press-n
	?event <- (x-key-event (type KeyPress) (display ?display) (window ?window) (root ?root) (keycode ?keycode))
	?x <- (x-event (typed-event ?event))
	(test (= ?keycode (x-keysym-to-keycode ?display (x-string-to-keysym "n"))))
	=>
	(x-circulate-subwindows-up ?display ?root)
	(x-set-input-focus ?display ?window RevertToParent 0)
	(retract ?event ?x)
	(x-next-event-to-fact ?display))

(defrule on-key-press-q
	?event <- (x-key-event (type KeyPress) (display ?display) (keycode ?keycode) (subwindow ?subwindow))
	?x <- (x-event (typed-event ?event))
	(test (= ?keycode (x-keysym-to-keycode ?display (x-string-to-keysym "q"))))
	=>
	(x-kill-client ?display ?subwindow)
	(retract ?event ?x)
	(x-next-event-to-fact ?display))

(defrule on-key-press-e
	?event <- (x-key-event (type KeyPress) (display ?display) (keycode ?keycode))
	?x <- (x-event (typed-event ?event))
	(test (= ?keycode (x-keysym-to-keycode ?display (x-string-to-keysym "e"))))
	=>
	(system "dmenu_run &")
	(retract ?event ?x)
	(x-next-event-to-fact ?display))

(defrule everything-else
	(declare (salience -1))
	?x <- (x-event (typed-event ?event))
	=>
	(x-next-event-to-fact (fact-slot-value ?event display))
	(retract ?event ?x))

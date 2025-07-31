(watch all)
(deffunction draw-textbox (?display ?window ?gc ?x ?y ?width ?height ?text)
    (x-draw-rectangle ?display ?window ?gc ?x ?y ?width ?height)
    (x-draw-string ?display ?window ?gc (+ 5 ?x) (integer (+ (/ ?height 2) ?y)) ?text)
)
(defrule always =>
	(bind ?display (x-open-display :0))
	(bind ?screen (default-screen ?display))
	(bind ?window (x-create-simple-window ?display (root-window ?display ?screen) 10 10 500 300 1 (black-pixel ?display ?screen) (white-pixel ?display ?screen)))
	(x-map-window ?display ?window)
	(bind ?cursor (x-create-font-cursor ?display XC_left_ptr))
	(x-define-cursor ?display ?window ?cursor)
	(bind ?gc (x-create-gc ?display ?window 0))
	(x-set-foreground ?display ?gc (black-pixel ?display ?screen))
	(bind ?font (x-load-query-font ?display fixed))
	(x-set-font ?display ?gc ?font)
	(draw-textbox ?display ?window ?gc 20 20 100 50 "Test text.")
	(x-select-input ?display ?window ExposureMask ButtonPressMask KeyPressMask KeyReleaseMask)
	(assert (next-event (x-next-event ?display)))
)

(defrule got-button-press
	?event <- (next-event
		?serial
		?send_event
		?display
		?window
		ButtonPress
		?root
		?subwindow
		?time
		?x
		?y
		?x_root
		?y_root
		?state
		?button
		?same_screen)
	=>
	(println "Got ButtonPress event (" ?x ", " ?y ")")
	(retract ?event)
	(assert (next-event (x-next-event ?display))))

(defrule got-key-press
	?event <- (next-event
		?serial
		?send_event
		?display
		?window
		?name&KeyPress|KeyRelease
		?root
		?subwindow
		?time
		?x
		?y
		?x_root
		?y_root
		?state
		?keycode
		?same_screen
		$?rest)
	=>
	(println "Got " ?name " event " ?keycode " " ?state " (" ?x ", " ?y ") " ?rest)
	(retract ?event)
	(assert (next-event (x-next-event ?display))))

(defrule anything-else
	?event <- (next-event ? ? ?display ? ?name&~KeyPress&~KeyRelease&~ButtonPress $?)
	=>
	(retract ?event)
	(assert (next-event (x-next-event ?display))))
	
(run)
(facts)

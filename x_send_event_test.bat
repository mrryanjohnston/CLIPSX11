; send_next_event_full_suite.bat
; Tests x-send-event (multifield, fact, instance) and x-next-event variants.

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Setup
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(clear)

(load "deftemplates.clp")
(load "defclasses.clp")

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Helpers
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(deffunction expect-type (?have ?want ?label)
  (if (eq ?have ?want)
    then (printout t "PASS " ?label ": " ?want crlf)
    else (printout t "FAIL " ?label ": expected " ?want " got " ?have crlf)))

(deffunction next-type (?dpy)
  (bind ?ev (x-next-event ?dpy))
  ; Type symbol is the 2nd field of the returned multifield as per CLIPSX11 docs.
  (return (nth$ 2 ?ev)))

(deffunction send-and-check (?dpy ?win ?mask-sym $?payload)
  (x-send-event ?dpy ?win FALSE (lexeme-to-event-mask ?mask-sym) (create$ $?payload))
  (expect-type (next-type ?dpy) (nth$ 1 (create$ $?payload)) (nth$ 1 (create$ $?payload)))
  (x-sync ?dpy TRUE))

; Build a KeyPress or KeyRelease payload
(deffunction key-event (?d ?w ?root $?which)
  ; which: KeyPress | KeyRelease
  (bind ?ks (x-string-to-keysym "t"))
  (bind ?kc (x-keysym-to-keycode ?d ?ks))
  ; (Type window root subwindow time x y x_root y_root state keycode same_screen)
  (return (create$ $?which ?w ?root 0 0  12345  100 120  300 320  0  ?kc TRUE)))

; Button helpers
(deffunction button-event (?w ?root $?which)
  ; which: ButtonPress | ButtonRelease
  (return (create$ $?which ?w ?root 0 0  12346  110 130  310 330  0  1 TRUE)))

; Motion
(deffunction motion-event (?w ?root)
  (return (create$ MotionNotify ?w ?root 0 0  12347  180 200  380 400  0  NotifyNormal TRUE)))

; Crossing
(deffunction enter-event (?w ?root)
  (return (create$ EnterNotify ?w ?root 0 0  12348  10 10  10 10  NotifyNormal NotifyAncestor TRUE TRUE 0)))
(deffunction leave-event (?w ?root)
  (return (create$ LeaveNotify ?w ?root 0 0  12349  12 12  12 12  NotifyNormal NotifyNonlinear TRUE FALSE 0)))

; Focus
(deffunction focus-in-event (?w)
  (return (create$ FocusIn  ?w  NotifyNormal  NotifyAncestor)))
(deffunction focus-out-event (?w)
  (return (create$ FocusOut ?w  NotifyNormal  NotifyNonlinear)))

; Expose
(deffunction expose-event (?w)
  (return (create$ Expose ?w  5 5  80 40  0)))

; Visibility
(deffunction visibility-event (?w)
  (return (create$ VisibilityNotify ?w VisibilityUnobscured)))

; Structure
(deffunction mapnotify-event (?w)
  (return (create$ MapNotify   ?w ?w FALSE)))
(deffunction unmapnotify-event (?w)
  (return (create$ UnmapNotify ?w ?w FALSE)))
(deffunction configurenotify-event (?w)
  (return (create$ ConfigureNotify ?w ?w  50 60  640 420  0  0 FALSE)))

; Property
(deffunction propertynotify-event (?d ?w)
  (bind ?atom (x-intern-atom ?d "MY_PROP" FALSE))
  (return (create$ PropertyNotify ?w ?atom 12350 PropertyNewValue)))

; ClientMessage (format 32 -> five longs)
(deffunction clientmessage-event (?d ?w)
  (bind ?mt (x-intern-atom ?d "MY_CLIENT_MSG" FALSE))
  (return (create$ ClientMessage ?w ?mt 32  1 2 3 4 5)))

; MappingNotify
(deffunction mappingnotify-event (?w)
  (return (create$ MappingNotify ?w MappingKeyboard 8 4)))

; GenericEvent (extension, evtype)
(deffunction generic-event ()
  (return (create$ GenericEvent 0 0)))

(defrule always =>
(bind ?d (x-open-display ""))

(if (eq ?d FALSE) then
  (printout t "FAILED: could not open display" crlf)
  (return))

(bind ?scr (default-screen ?d))
(bind ?root (root-window ?d ?scr))

(bind ?w (x-create-simple-window ?d ?root 50 50 640 420 0
              (black-pixel ?d ?scr)
              (white-pixel ?d ?scr)))

(x-map-window ?d ?w)
(x-sync ?d)

; Select a wide set of masks so our synthetic events get delivered.
(x-select-input
  ?d ?w
  KeyPressMask KeyReleaseMask
  ButtonPressMask ButtonReleaseMask
  PointerMotionMask
  EnterWindowMask LeaveWindowMask
  FocusChangeMask
  ExposureMask VisibilityChangeMask
  StructureNotifyMask
  PropertyChangeMask
  SubstructureNotifyMask)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; TESTS: x-send-event (multifield) + x-next-event
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(printout t crlf "== MULTIFIELD round-trip tests ==" crlf)

; KeyPress / KeyRelease
(send-and-check ?d ?w KeyPressMask   (key-event ?d ?w ?root KeyPress))
(send-and-check ?d ?w KeyReleaseMask (key-event ?d ?w ?root KeyRelease))

; ButtonPress / ButtonRelease
(send-and-check ?d ?w ButtonPressMask   (button-event ?w ?root ButtonPress))
(send-and-check ?d ?w ButtonReleaseMask (button-event ?w ?root ButtonRelease))

; Motion
(send-and-check ?d ?w PointerMotionMask (motion-event ?w ?root))

; Enter / Leave
(send-and-check ?d ?w EnterWindowMask (enter-event ?w ?root))
(send-and-check ?d ?w LeaveWindowMask (leave-event ?w ?root))

; FocusIn / FocusOut
(send-and-check ?d ?w FocusChangeMask (focus-in-event ?w))
(send-and-check ?d ?w FocusChangeMask (focus-out-event ?w))

; Expose
(send-and-check ?d ?w ExposureMask (expose-event ?w))

; VisibilityNotify
(send-and-check ?d ?w VisibilityChangeMask (visibility-event ?w))

; MapNotify / UnmapNotify / ConfigureNotify
(send-and-check ?d ?w StructureNotifyMask (mapnotify-event ?w))
(send-and-check ?d ?w StructureNotifyMask (unmapnotify-event ?w))
(send-and-check ?d ?w StructureNotifyMask (configurenotify-event ?w))

; PropertyNotify
(send-and-check ?d ?w PropertyChangeMask (propertynotify-event ?d ?w))

; ClientMessage
; For ClientMessage delivery, StructureNotifyMask is commonly fine for synthetic messages.
(send-and-check ?d ?w StructureNotifyMask (clientmessage-event ?d ?w))

; MappingNotify (often on root, but we still exercise wrapper)
(send-and-check ?d ?w StructureNotifyMask (mappingnotify-event ?w))

; GenericEvent (extension hooks vary; still validate wrapping)
; This is commented out because GenericEvent cannot be sent with XSendEvent
; (send-and-check ?d ?w StructureNotifyMask (generic-event))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; TESTS: x-send-event with FACT, receive via x-next-event-to-fact
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(printout t crlf "== FACT round-trip test ==" crlf)

; Build a FACT per deftemplates.clp for Expose (slots vary by your template).
; Minimal: reuse the MF to generate a FACT matching the library’s typed template.
(bind ?mf (expose-event ?w))
; The library accepts a FACT with typed slots; use helper to create one if available.
; Fallback: wrap MF->FACT via provided converter name if you have one; else send MF-to-FACT directly.
; Here we just send the MF as FACT by constructing the (X-EXPOSE-EVENT ...) template if loaded.

(bind ?f (assert (x-expose-event
	     (window           (nth$ 2 ?mf))
	     (x                (nth$ 3 ?mf))
	     (y                (nth$ 4 ?mf))
	     (width            (nth$ 5 ?mf))
	     (height           (nth$ 6 ?mf))
	     (count            (nth$ 7 ?mf)))))
(x-send-event ?d ?w FALSE (lexeme-to-event-mask ExposureMask) ?f)
(expect-type (fact-slot-value (x-next-event-to-fact ?d) type) Expose "FACT->x-next-event-to-fact")

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; TESTS: x-send-event with INSTANCE, receive via x-next-event-to-instance
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(printout t crlf "== INSTANCE round-trip test ==" crlf)

; Build an INSTANCE for ClientMessage with minimal required slots.
(bind ?inst (make-instance [cm1] of X-CLIENT-MESSAGE-EVENT
	   (window ?w)
	   (type ClientMessage)
	   (format 32)
	   (data 10 20 30 40 50)))
(x-send-event ?d ?w FALSE (lexeme-to-event-mask StructureNotifyMask) ?inst)
(expect-type (send (x-next-event-to-instance ?d) get-type) ClientMessage "INSTANCE->x-next-event-to-instance")

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Cleanup
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(x-destroy-window ?d ?w)
(x-sync ?d TRUE)
(x-close-display ?d)

(printout t crlf "== DONE ==" crlf)
)
(reset)
(run)

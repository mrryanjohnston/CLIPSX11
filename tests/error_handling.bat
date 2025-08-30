(load deftemplates.clp)
(load defclasses.clp)
(defrule always =>
; 1) open a display
(bind ?d (x-open-display :0))
(printout t "Opened display: " ?d crlf)

; Prime the handler without a queue so early errors don't exit and aren't captured.
(x-start-collecting-errors ?d)
(x-stop-collecting-errors ?d)

; bogus window id to force BadWindow
(bind ?bogus 3735928559)
(printout t "Bogus window id: " ?bogus crlf)

; 2) trigger an error BEFORE watching/queue (not captured, process continues)
(printout t "Triggering an error..." crlf)
(x-get-window-attributes ?d ?bogus)

; 4) pop an error (expect FALSE / nothing)
(printout t "Step 4 pop -> " (x-pop-error ?d) crlf)

; Now actually start collecting
(printout t "Start collecting errors..." crlf)
(x-start-collecting-errors ?d)

; 5) trigger an error
(printout t "Trigger an error..." crlf)
(x-get-window-attributes ?d ?bogus)

; 6) pop as multifield
(bind ?mf (x-pop-error ?d))
(printout t "Step 6 mf -> " ?mf crlf)
(println "error text -> " (error-code-to-symbol (nth$ 2 ?mf)))
(println "request_code-> " (x-get-error-database-text ?d XRequest (nth$ 3 ?mf)))
(println "major_code -> " (x-get-error-database-text ?d XProtoError (nth$ 3 ?mf)))

; 7) trigger an error
(printout t "Trigger an error..." crlf)
(x-get-window-attributes ?d ?bogus)

; 8) pop as fact
(bind ?f (x-pop-error-to-fact ?d))
(if (neq ?f FALSE)
 then
   (printout t "Step 8 fact -> " ?f crlf)
   (ppfact ?f)
 else
   (printout t "Step 8 fact -> FALSE" crlf))

; 9) trigger an error
(printout t "Trigger an error..." crlf)
(x-get-window-attributes ?d ?bogus)

; 10) pop as instance
(bind ?i (x-pop-error-to-instance ?d))
(if (neq ?i FALSE)
 then
   (printout t "Step 10 instance -> " ?i crlf)
   (send ?i print)
 else
   (printout t "Step 10 instance -> FALSE" crlf))

; 11) stop watching the display for errors
(printout t "Stop collecting errors..." crlf)
(x-stop-collecting-errors ?d)

; 12) trigger an error AFTER stopping (won't be captured)
(printout t "Trigger an error..." crlf)
(x-get-window-attributes ?d ?bogus)

; 13) try to pop (expect FALSE)
(printout t "Step 13 pop after stop -> " (x-pop-error ?d) crlf)

; 14) reset default error handler
(println "Resetting default error handler...")
(x-set-default-error-handler)
(printout t "Trigger an error..." crlf)
(x-get-window-attributes ?d ?bogus)
)
(watch facts)
(watch instances)
(reset)
(run)

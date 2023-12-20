#lang racket

(require megaparsack megaparsack/text)
(require data/monad)
(require data/applicative)

(define word/p
  (do [x <- (many/p letter/p)]
    (pure (list->string x))))

(define comp/p
  (or/p
   (do (char/p #\<)
     (pure <))
   (do (char/p #\>)
     (pure >))))

(struct condition (fn c comp x next))

(define condition/p
   (do [n <- word/p]
     (or/p
      (do [comp <- comp/p]
      [x <- integer/p]
        (char/p #\:)
        (next <- word/p)
        (pure
         (condition (lambda (ht)
                (if (apply comp (list (hash-ref ht n) x)) next #f)) n comp x next)))
     (do (char/p #\})
       (pure
        (condition (lambda (ht) n) #f #f #f n))))))

(define instruction/p
  (do [name <- word/p]
    (char/p #\{)
    (conditions <- (many/p condition/p #:sep (char/p #\,)))
    (pure (cons name conditions))))

(define data/p
  (do (char/p #\{)
    (string/p "x=")
    (x <- integer/p)
    (string/p ",m=")
    (m <- integer/p)
    (string/p ",a=")
    (a <- integer/p)
    (string/p ",s=")
    (s <- integer/p)
    (char/p #\})
    (pure (hash
           "x" x
           "m" m
           "a" a
           "s" s))))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (accepts? workflows part)
  (letrec ([find-next
         (lambda (node)
           ((findf (lambda (f) (f part)) (map condition-fn (hash-ref workflows node))) part))
         ]
    [accept?
     (lambda (node)
       (cond
         [(equal? node "A") #t]
         [(equal? node "R") #f]
         [else (accept? (find-next node))]
         ))])
    (accept? "in")))

(define (part1 workflows parts)
  (let ([sum-part (lambda (part)
    (apply + (hash-values part)))])
    (apply + (map sum-part (filter (lambda (p) (accepts? workflows p)) parts)))))

(define INF 987654321)
(define (part2 workflows)
  (letrec ([min-bound 1]
           [max-bound 4000]
           [interval-size
            (lambda (p)
              (max 0 (+ 1 (- (cdr p) (car p)))))]
           [count-inputs
            (lambda (cur)
              (apply * (map interval-size (hash-values cur))))]
           [count
            (lambda (node cur)
              (cond
                [(equal? node "A") (count-inputs cur)]
                [(equal? node "R") 0]
                [else (count-node (hash-ref workflows node) cur)]
                  ))]
           [count-node
            (lambda (lis cur)
              (match lis
                [(cons l ls)
                 (begin
                   (if (condition-c l)
                       (let ([curs (clamp l cur)])
                         (+
                          (count (condition-next l) (car curs))
                          (count-node ls (cdr curs))))
                       (count (condition-next l) cur)))]
                ['() 0]
                 ))]
           [clamp-interval
            (lambda (p1 p2)
              (cons (max (car p1) (car p2))
                    (min (cdr p1) (cdr p2))))]
           [clamp
            (lambda (con cur)
              (let* ([x (condition-x con)]
                [c (condition-c con)]
                [con-intervals
                 (if (equal? (condition-comp con) <)
                     (cons (cons (- INF) (- x 1))
                           (cons x INF))
                     (cons (cons (+ x 1) INF)
                           (cons (- INF) x)))])
              (cons
               (hash-set cur c (clamp-interval (hash-ref cur c) (car con-intervals)))
               (hash-set cur c (clamp-interval (hash-ref cur c) (cdr con-intervals))))
                ))])
    (count "in" (hash
           "x" (cons min-bound max-bound)
           "m" (cons min-bound max-bound)
           "a" (cons min-bound max-bound)
           "s" (cons min-bound max-bound)))))


(define-values (workflows-inputs data-inputs)
  (splitf-at (string-split (port->string (open-input-file "in")) "\n") non-empty-string?))
 
(define workflows
  (let ([parse-instruction
        (lambda (x) (parse-result! (parse-string instruction/p x)))])
  (make-immutable-hash (map parse-instruction workflows-inputs))))
(define parts
  (let ([parse-data
     (lambda (x) (parse-result! (parse-string data/p x)))])
    (map parse-data (cdr data-inputs))))

(printf "Part 1: ~a\n" (part1 workflows parts))
(printf "Part 2: ~a\n" (part2 workflows))
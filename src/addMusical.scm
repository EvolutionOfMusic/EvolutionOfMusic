(define (addNode ID)
	(cog-new-node 'ConceptNode ID))

(define (addNodePair ID ID2 ID3 value)
	(cog-new-link 'Link ID ID2 ID3 (cog-new-stv value 0)))
;if the value of ID is the header, then the stv represents the guessed
;value of the entire chain.
;
;The name of ID3 must use the following format
;HeaderX.Y
;where X and Y are integer values and X refers to the header number
;and Y refers to the index number
;
;call the walkList function within C++ as ID to link up sub-tracks
;name is to be referred as linkerX.Y


(define (walkList Header index)
	(if (cog-atom? (cog-node 'ConceptNode + Header index)) 
		walkList(Header (+ index 1))
		(cog-node 'ConceptNode + Header (- index 1))))

(define (songHeader linkerList ID songLength)(
	(define x (addNode(ID)))
	(= i 0)
	(define y
		(lambda(n newList)
			(if(< i array-length newList)
				(newList i) y(+ i 1 newList)
				(newList i)
	)	)	)
	(cog-new-link 'Link ID y(0 linkerList) (cog-new-stv 0 0)))

(define (updateLinkerList linkerList value)
	(= Header (define getNextNode(Header Linker indexHeader indexLinker)
	define x (if (cog-atom? (cog-node 'ConceptNode + + + Header "." index)))
	)

(define 

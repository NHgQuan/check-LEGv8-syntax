.data
a: .word 1
LDA     S1, b

.text
b: .word 2
// sum a (1) and b (2) into X0
main:
	// load a into X0
	LDA     X0, 1000000000000000000000
	LDUR    X0, [X0, #0

	// load b into X1
	
	LDUR    X1, [X1, #0]

	// put a+b into X0
	ADD     X0, X0, X1
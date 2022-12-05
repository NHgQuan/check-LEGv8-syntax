.eqv N 80



.text

/*
 * sum elements from array into X3
 * used registers:
 *      X0 - address of the array
 *      X1 - size of the array
 *      X2 - current element
 *      X3 - accumulation
 */
main:
	MOVZ		X0, int_a, 17
	LDA     X0, array       /* load address of array into X0 */
	ADDI    X1, XZR, N      /* make X1 = N */
	MOV     X3, XZR         /* clean X3 */
loop_beg:
	CBZ     X1, loop_end
	LDUR    X2, [X0, 0]
	ADD     X3, X3, X2
	SUBI    X1, X1, 8
	ADDI    X0, X0, 8
	B       loop_be
loop_end:

.data
array: .word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
int_a: .word 100

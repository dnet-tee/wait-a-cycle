secure_memcmp:
	push.w	r4
	mov.w	r1, r4
	push.w	r11
	push.w	r10
	push.w	r9
	mov.w	#0, r12
	cmp.w	#1, r13
	jl	.LBB0_9
	mov.w	#1, r11
.LBB0_2:
    cmp.w	#1, r11
	jne	.LBB0_8 
    mov.b	0(r14), r11
	mov.b	0(r15), r10
	cmp.b	r10, r11
	jhs	.LBB0_5 
	mov.w	#0, r11
	mov.w	#1, r12
	jmp	.LBB0_8
.LBB0_5:
    mov.w	#-1, r9
	cmp.b	r11, r10
	jlo	.LBB0_7
	mov.w	r12, r9
.LBB0_7:
	cmp.b	r11, r10
	mov.w	r2, r11
	and.w	#1, r11
	mov.w	r9, r12
.LBB0_8:
	add.w	#1, r14
	add.w	#1, r15
	add.w	#-1, r13
	cmp.w	#0, r13
	jne	.LBB0_2
.LBB0_9:
	mov.w	r12, r15
	pop.w	r9
	pop.w	r10
	pop.w	r11
	pop.w	r4
	ret
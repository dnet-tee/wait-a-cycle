cmp_secret64:
	push.w	r4
	mov.w	r1, r4
	xor.w	10(r4), r15
	xor.w	6(r4), r13
	bis.w	r15, r13
	xor.w	8(r4), r14
	xor.w	4(r4), r12
	bis.w	r14, r12
	bis.w	r13, r12
	cmp.w	#0, r12
	jne	.LBB0_2
	call	#helper_func
.LBB0_2:
	pop.w	r4
	ret
cmp_secret32:
	push.w	r4
	mov.w	r1, r4
	xor.w	r13, r15
	xor.w	r12, r14
	bis.w	r15, r14
	cmp.w	#0, r14
	jne	.LBB1_2
	call	#helper_func
.LBB1_2:
	pop.w	r4
	ret
cmp_secret16:
	push.w	r4
	mov.w	r1, r4
	cmp.w	r14, r15
	jne	.LBB2_2
	call	#helper_func
.LBB2_2:
	pop.w	r4
	ret
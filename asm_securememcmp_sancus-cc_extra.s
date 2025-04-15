secure_memcmp:
	push.w	r4
	mov.w	r1, r4
	push.w	r11
	push.w	r10
	push.w	r9
	mov.w	#0, r12
	cmp.w	#1, r13
	jl	.LBB0_9				; k == no. wrong bytes
	mov.w	#1, r11			; n == no. correct bytes
.LBB0_2:                    ; Correct   | Smaller   | Greater 
    cmp.w	#1, r11         ; n         | n + k     | n + k 
	jne	.LBB0_8             ; n         | n + k     | n + k
    mov.b	0(r14), r11     ; n         | n + 1     | n + 1
	mov.b	0(r15), r10     ; n         | n + 1     | n + 1
	cmp.b	r10, r11        ; n         | n + 1     | n + 1
	jhs	.LBB0_5             ; n         | n + 1     | n + 1
	mov.w	#0, r11         ; 0         | 0         | 1
	mov.w	#1, r12         ; 0         | 0         | 1
	jmp	.LBB0_8             ; 0         | 0         | 1
.LBB0_5:
    mov.w	#-1, r9         ; n         | n + 1     | 0
	cmp.b	r11, r10        ; n         | n + 1     | 0
	jlo	.LBB0_7             ; n         | n + 1     | 0
	mov.w	r12, r9         ; 0         | 1         | 0
.LBB0_7:
	cmp.b	r11, r10        ; n         | n + 1     | 0
	mov.w	r2, r11         ; n         | n + 1     | 0
	and.w	#1, r11         ; n         | n + 1     | 0
	mov.w	r9, r12         ; n         | n + 1     | 0
.LBB0_8:
	add.w	#1, r14         ; n         | n + k     | n + k
	add.w	#1, r15         ; n         | n + k     | n + k
	add.w	#-1, r13        ; n         | n + k     | n + k
	cmp.w	#0, r13         ; n         | n + k     | n + k
	jne	.LBB0_2             ; n         | n + k     | n + k
.LBB0_9:
	mov.w	r12, r15
	pop.w	r9
	pop.w	r10
	pop.w	r11
	pop.w	r4
	ret
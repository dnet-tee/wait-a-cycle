cmp_secret64:
	PUSHM.W #2, R10
	MOV.W   8(R1), R9
	MOV.W   10(R1), R10
	MOV.W   12(R1), R11
	CMP.W   6(R1), R12
	JNE     .L1
	CMP.W   R9, R13
	JNE     .L1
	CMP.W   R10, R14
	JNE     .L1
	CMP.W   R11, R15
	JNE     .L1
	CALL    #helper_func
.L1:
	POPM.W  #2, r10
	RET
cmp_secret32:
	CMP.W   R14, R12
	JNE        .L3
	CMP.W   R15, R13
	JNE        .L3
	CALL    #helper_func
.L3:
	RET
cmp_secret16:
	CMP.W   R13, R12
	JNE        .L5
	CALL    #helper_func
.L5:
	RET

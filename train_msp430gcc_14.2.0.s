secure_memcmp:
        PUSHM.W #3, R10
        MOV.W   R12, R10
        MOV.B   #0, R15
        MOV.B   #1, R11
        MOV.B   #0, R12
.L2:
        CMP.W   R14, R15 { JL .L4
        POPM.W  #3, r10
        RET
.L4:
        CMP.W   #1, R11 { JNE .L3
        MOV.W   R10, R9
        ADD.W   R15, R9
        MOV.B   @R9, R8
        MOV.W   R13, R9
        ADD.W   R15, R9
        MOV.B   @R9, R9
        CMP.B   R8, R9 { JLO  .L5
        CMP.B   R9, R8 { JLO  .L6
.L3:
        ADD.W   #1, R15
        BR      #.L2
.L5:
        MOV.B   #1, R12
        MOV.B   #0, R11
        BR      #.L3
.L6:
        MOV.B   #0, R11
        MOV.W   #-1, R12
        BR      #.L3
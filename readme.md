# Wait a Cycle

Artifacts for the Wait a Cycle paper submitted to 8th Workshop on System Software for Trusted Execution.

## Standard Library Functions

- C++ authenticated encryption with associated data in Sancus: https://github.com/sancus-tee/sancus-compiler/blob/master/src/crypto/spongent.cpp.
- VatiCAN code is offline now, a zipped folder can be found here.
- The vulnerable VRASED function and an attack can be found secure_cmp folder. In addition, the following links bring you to vulnerable derivatives of VRASED:
  - https://github.com/sprout-uci/RATA/blob/d5ae4313ccb400b134e98edcf704a1f03317a183/vrased/sw-att/wrapper.c#L46
  - https://github.com/sprout-uci/vrased-plus/blob/6bd2537cc2fe88b0b5c89925d76bbf5a5eb2010a/vrased/sw-att/wrapper.c#L39
  - https://github.com/RIT-CHAOS-SEC/ACFA/blob/dcd92aa9c1fa990cd14b12eff6fe6770de290d15/tcb/wrapper.c#L344
  - https://github.com/RIT-CHAOS-SEC/ACFA/blob/dcd92aa9c1fa990cd14b12eff6fe6770de290d15/tcb/wrapper.c#L344

## Compiler Analysis

- The code used for analysing compilers: c_code_compare_full.c, c_train.c, cmp_msp430gcc_14.2.0.s, cmp_sancus-cc.s and train_msp430gcc_14.2.0.s.
- In addition you can find the vulnerable Leia code here: https://github.com/MoatazFarid/Lightweight-Authentication-Protocol-for-CAN-LeiA/blob/bb4c47ac6c56a0ee448eeb5639e65dc012c7f332/LeiA.c#L490.

## Hardware Timing Vulnerability

- The attack on the unwrap primitive of Sancus can be found in folder unwrap-break.
- The end-to-end attack on the authentic execution framework can be found in folder auth-ex-break.
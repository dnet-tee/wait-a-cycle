# Wait a Cycle: Eroding Cryptographic Trust in Low-End TEEs via Timing Side Channels
[![Build Status](https://github.com/dnet-tee/wait-a-cycle/actions/workflows/ci.yml/badge.svg)](https://github.com/dnet-tee/wait-a-cycle/actions/workflows/ci.yml)

This repository contains the artifacts accompanying our [paper](https://downloads.distrinet-research.be/software/sancus/publications/vandijck25wait.pdf) "Wait a Cycle: Eroding Cryptographic Trust in Low-End TEEs via Timing Side Channels" to appear at the 8th Workshop on System Software for Trusted Execution.

> R. Van Dijck, M. Bognar, and J. Van Bulck, "Wait a Cycle: Eroding Cryptographic Trust in Low-End TEEs via Timing Side Channels," in 2025 IEEE 8th Workshop on System Software for Trusted Execution (SysTEX).

Artifacts and repositories relevant to the findings in the paper can be found here. For more information about mitigations we suggest to look at the issues submitted to the affected repositories.

## Overview

### Standard Library Functions (Section §3.1)


| Description | Proof-of-concept attack | Issue |
|-----------------|---------------|:-------------:|
| C++ authenticated encryption with associated data in Sancus. | / | [sancus-compiler](https://github.com/sancus-tee/sancus-compiler/issues/42), [authentic execution](https://github.com/AuthenticExecution/spongent-cpp-rs/issues/1) |
| VatiCAN code is offline now, a zipped folder can be found here. | / | see /vatican-1.1/vatican/src/vatican.cpp#L.169 |
| The vulnerable VRASED function and an attack can be found in the secure_cmp folder. The results of this attack (Wait a Cycle: table 5) can be reproduced using the proof-of-concept attack. | [secure_memcmp](secure_memcmp/) | [VRASED+](https://github.com/sprout-uci/vrased-plus/issues/1), [TRAIN](https://github.com/sprout-uci/TRAIN/issues/1), [ACFA](https://github.com/RIT-CHAOS-SEC/ACFA/issues/1), [RATA](https://github.com/sprout-uci/RATA/issues/1), and [SpecCFA](https://github.com/RIT-CHAOS-SEC/SpecCFA/issues/1) |


### Compiler Analysis (Section §3.2)

| Description | Proof-of-concept | Issue |
|-----------------|---------------|:-------------:|
| The code used for analysing compilers can be found in the compiler-equal folder. To ease the artifact evaluation you can use Godbolt for different compilers (Wait a Cycle: listing 2, listing 3 and table 2): [MSP430 gcc 14.2.0](https://godbolt.org/z/b63qf4T76), [RISC-V gcc 14.2.0](https://godbolt.org/z/oqvhKPh7M), [MIPS (el) gcc 14.2.0](https://godbolt.org/z/7ffT77oMf) and [x86 msvc v19](https://godbolt.org/z/fYY8Phx9z). | [compiler-equal](compiler-equal/) | / |
| Vulnerable LeiA code. | / | [LeiA](https://github.com/MoatazFarid/Lightweight-Authentication-Protocol-for-CAN-LeiA/issues/1) |
| VulCAN is vulnerable in two places. | / | [VulCAN](https://github.com/sancus-tee/vulcan/issues/9) |

### Hardware Timing Vulnerability (Section §3.3)

| Description | Proof-of-concept attack | Issue |
|-----------------|---------------|:-------------:|
| Sancus' cryptographic unit is vulnerable (Wait a Cycle: figure 1 and table 3). | [unwrap-break](unwrap-break/) | [Sancus](https://github.com/sancus-tee/sancus-core/issues/34) |
| An end-to-end attack on the Authentic Execution framework is performed.  | [auth-ex-break](auth-ex-break/) | / |

### Hardware Mitigation (Section §4.3)

Two patches for the vulnerable Sancus core are provided in the [mitigations](mitigations/) folder. Changes are in comparison to the latest [commit](https://github.com/sancus-tee/sancus-core/blob/d83a5207dc5b079847dba39ac17e98fcb4bc088f). See section 4.3 in the paper for a full overview of the comparison and figure 2 and 3 for a graphical representation.


## Building and Running

The expected output can be viewed in the [GitHub Actions CI environment](https://github.com/dnet-tee/wait-a-cycle/actions).

To run the proof-of-concepts yourself in the cycle-accurate Sancus openMSP430 simulator in a Docker environment, proceed as follows:

```bash
$ docker pull ghcr.io/sancus-tee/sancus-main/sancus-devel-64:latest
$ docker run -it -v .:/sancus/wait-a-cycle ghcr.io/sancus-tee/sancus-main/sancus-devel-64:latest
========================================================================
= Sancus development Docker container                                  =
========================================================================
Description:	Ubuntu 20.04.6 LTS

To get started, see <https://distrinet.cs.kuleuven.be/software/sancus/>,
or have a look at the example programs under </sancus/sancus-examples/>.


root@df14e8828d23:/sancus# cd wait-a-cycle/secure_memcmp/
root@b56642e6b606:/sancus/wait-a-cycle/secure_memcmp# make clean sim
rm -f main.elf no_mac_main.elf main.o
rm -f sim-input.bin sim-output.bin sim.out
rm -f *.fst *.vcd
sancus-cc -I"/usr/local/share/sancus-support"/include/ -Wfatal-errors -fcolor-diagnostics -Os -g   -c -o main.o main.c
sancus-ld -L"/usr/local/share/sancus-support"/lib/ --ram 16K --rom 41K  -lsm-io -ldev --inline-arithmetic --standalone --verbose -o no_mac_main.elf main.o
INFO: No new Sancus modules found
INFO: No existing Sancus modules found
INFO: No asm Sancus modules found
INFO: Found MSP430 install directory: /usr/msp430
INFO: Found MSP430 GCC install directory: /usr/lib/gcc/msp430/4.6.3
INFO: Using output file no_mac_main.elf
INFO: Cleaning up temporary files: /tmp/tmpo8cpz3p_
sancus-crypto --fill-macs --key 4078d505d82099ba --verbose -o main.elf no_mac_main.elf
unbuffer sancus-sim  --dumpfile=sancus_sim.vcd main.elf | tee sim.out
2025-05-06 12:08:20.794 (   0.000s) [        C5C26740]               main.cpp:296   INFO| Using input file main.elf.
   v| 
INFO| arguments: sancus-sim --dumpfile=sancus_sim.vcd main.elf
INFO| Current dir: /sancus/wait-a-cycle/secure_memcmp
INFO| stderr verbosity: 0
INFO| -----------------------------------
INFO| ======================= Sancus Simulator =======================
INFO| { Performing objcopy of elf file
INFO| .   Generating temporary binary form of given elf file...
INFO| .   Temp file is /tmp/tmp_sancus_weNzE7
INFO| .   >> msp430-objcopy -O binary main.elf /tmp/tmp_sancus_weNzE7
INFO| .   ..done!
INFO| } 0.003 s: Performing objcopy of elf file
INFO| Using sancus_sim.vcd as simulation file.
INFO| Enabled automatic timeout after 1000000000 cycles.
INFO| Will abort simulation 0 cycles after any SM_VIOLATION
INFO| Read program memory of 41984 bytes.
=== SpongeWrap parameters ===
Rate:           16
Security:       64
Blocks in key:   4
=============================
=== Spongent parameters ===
Rate:        18
State size: 176
===========================

------


[main.c] comparison (0/5 bytes correct) with result: 1, took 60 cycles
[main.c] comparison (1/5 bytes correct) with result: 1, took 76 cycles
[main.c] comparison (2/5 bytes correct) with result: 1, took 95 cycles
[main.c] comparison (3/5 bytes correct) with result: 1, took 114 cycles
[main.c] comparison (4/5 bytes correct) with result: 1, took 133 cycles
[main.c] comparison (5/5 bytes correct) with result: 0, took 138 cycles
[main.c] arr2[0] = 5
[main.c] arr2[1] = 101
[main.c] arr2[2] = 232
[main.c] arr2[3] = 60
[main.c] arr2[4] = 171
all done; exiting..



INFO| ======================== Simulation ended ========================
INFO| Total/crypto cycles simulated: 204229/0.
INFO| ================ Simulation succeeded gracefully =================
INFO| atexit
```

We refer to the [Sancus documentation](https://github.com/sancus-tee/sancus-main) for more general installation instructions (e.g., beyond Docker).

## License

| Application | License |
|-----------------|---------------|
| Sancus compiler | [GPLv3](https://github.com/sancus-tee/sancus-compiler/blob/master/README.md?plain=1) |
| Sancus core | [BSD](https://github.com/sancus-tee/sancus-core/blob/master/LICENSE) |
| VulCAN | [GPLv3](https://github.com/sancus-tee/vulcan/blob/master/README.md?plain=1) |
| vatiCAN | Free to use for non-commercial purposes, see [vatican-1.1.zip](vatican-1.1.zip) |
| VRASED | [GPLv3](https://github.com/sprout-uci/vrased/blob/master/LICENSE) |
| RATA | [GPLv3](https://github.com/sprout-uci/RATA/blob/main/LICENSE) |
| TRAIN | [GPLv3](https://github.com/sprout-uci/TRAIN/blob/main/TRAINCASU/LICENSE) |
| Authentic Execution framework | [MIT](https://github.com/AuthenticExecution/.github/blob/master/LICENSE) |
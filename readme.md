# Wait a Cycle

This repository contains the artifacts accompanying our [paper](https://downloads.distrinet-research.be/software/sancus/publications/vandijck25wait.pdf) "Wait a Cycle: Eroding Cryptographic Trust in Low-End TEEs via Timing Side Channels" to appear at the 8th Workshop on System Software for Trusted Execution.
<!-- More information on the paper and links to other investigated systems can be
found in the top-level [gap-attacks](https://github.com/martonbognar/gap-attacks) repository. -->

> R. Van Dijck, M. Bognar, and J. Van Bulck, "Wait a Cycle: Eroding Cryptographic Trust in Low-End TEEs via Timing Side Channels," in 2025 IEEE 8th Workshop on System Software for Trusted Execution (SysTEX).

Artifacts and repositories relevant to the findings in the paper can be found here. For more information about mitigations we suggest to look at the issues submitted to the affected repositories.

## Overview

### Standard Library Functions (Section §3.1)


| Description | Proof-of-concept attack | Issue |
|-----------------|---------------|:-------------:|
| C++ authenticated encryption with associated data in Sancus. | / | / |
| VatiCAN code is offline now, a zipped folder can be found here. | / | / |
| The vulnerable VRASED function and an attack can be found in the secure_cmp folder. | [secure_memcmp](secure_memcmp/) | [VRASED+](https://github.com/sprout-uci/vrased-plus/issues/1), [TRAIN](https://github.com/sprout-uci/TRAIN/issues/1), [ACFA](https://github.com/RIT-CHAOS-SEC/ACFA/issues/1), [RATA](https://github.com/sprout-uci/RATA/issues/1), and [SpecCFA](https://github.com/RIT-CHAOS-SEC/SpecCFA/issues/1) |


### Compiler Analysis (Section §3.2)

| Description | Proof-of-concept attack | Issue |
|-----------------|---------------|:-------------:|
| The code used for analysing compilers can be found in the compiler-equal folder. To ease the artifact evaluation you can use Godbolt for different compilers e.g.: [MSP430 gcc 14.2.0](https://godbolt.org/z/b63qf4T76) or [RISC-V gcc 14.2.0](https://godbolt.org/z/oqvhKPh7M). | [compiler-equal](compiler-equal/) | / |
| Vulnerable LeiA code. | / | [LeiA](https://github.com/MoatazFarid/Lightweight-Authentication-Protocol-for-CAN-LeiA/issues/1) |
| VulCAN is vulnerable in two places. | / | [VulCAN](https://github.com/sancus-tee/vulcan/issues/9) |

### Hardware Timing Vulnerability (Section §3.3)

| Description | Proof-of-concept attack | Issue |
|-----------------|---------------|:-------------:|
| Sancus' cryptographic unit is vulnerable. | [unwrap-break](unwrap-break/) | [Sancus](https://github.com/sancus-tee/sancus-core/issues/34) |
| An end-to-end attack on the Authentic Execution framework is performed.  | [auth-ex-break](auth-ex-break/) | / |

### Hardware Mitigation (Section §4.3)

Two patches for the vulnerable Sancus core are provided in the [mitigations](mitigations/) folder. Changes are in comparison to the latest [commit](https://github.com/sancus-tee/sancus-core/blob/d83a5207dc5b079847dba39ac17e98fcb4bc088f).


## Installation

The general installation instructions of Sancus can be found [here](https://github.com/sancus-tee/sancus-main).

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
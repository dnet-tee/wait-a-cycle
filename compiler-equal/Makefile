include ../Makefile.include

SOURCES         = $(shell ls *.c)
OBJECTS         = $(SOURCES:.c=.o)
CLANG_VERSION   = $(shell clang --version | head -n 1 | awk '{print $3}')

all: $(OBJECTS)

sim: $(OBJECTS)
	@echo "==== sancus-cc ("$(CLANG_VERSION)") output below ==="
	msp430-objdump -d c_code_compare_full.o

clean:
	$(RM) $(OBJECTS)
	rm -f sim-input.bin sim-output.bin sim.out
	rm -f *.fst *.vcd

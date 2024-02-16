# release toolchain
MMCU = atmega88pa
CC_R = avr-gcc -mmcu=$(MMCU)
COPY = avr-objcopy
SIZE = avr-size
CFLAGS_R = -Wall -Os -fshort-enums --param=min-pagesize=0 $(INCLUDE_PATH) $(LIBS_PATH)
AVRDUDE_MMCU = m88p

# test toolchain
CC_T = gcc

# dependencies
INCLUDE_PATH = \
	-I/usr/local/include \
	-I$(DIR_INCLUDE)
LIBS_PATH = \
	-L/usr/local/lib
LIBS = \
	-lavrhal-gpio \
	-lavrhal-t1nrm \
	-lavrhal-t1int

# test dependencies
TEST_INCLUDE_PATH = \
	-I$(DIR_TEST_INCLUDE) \
	-I$(DIR_INCLUDE)
TEST_LIBS = -lunity

# directory structure
DIR_INCLUDE = include
DIR_SRC = src
DIR_BUILD = build
DIR_BUILD_RELEASE = build/release
DIR_DIST = dist
DIR_TEST_SRC = test
DIR_TEST_INCLUDE = test/include
DIR_TEST_BUILD = build/test
DIR_TEST_BIN = build/test/bin
DIR_TEST_OBJ = build/test/obj
DIR_TEST_RESULTS = build/test/results

# helper vars
SRCS = $(wildcard $(DIR_SRC)/*.c)
OBJS = $(patsubst $(DIR_SRC)/%.c,$(DIR_BUILD_RELEASE)/%.o,$(SRCS))
TSRC = $(wildcard $(DIR_TEST_SRC)/*.c)
TRES = $(patsubst $(DIR_TEST_SRC)/%_test.c, $(DIR_TEST_RESULTS)/%_test.txt, $(TSRC))

# tests summary
TESTSUM_PASSED = `grep :PASS $(DIR_TEST_RESULTS)/*.txt | wc -l`
TESTSUM_IGNORED = `grep :IGNORE $(DIR_TEST_RESULTS)/*.txt | wc -l`
TESTSUM_FAILED = `grep :FAIL $(DIR_TEST_RESULTS)/*.txt | wc -l`
TESTSUM_FAILED_DET = `cat $(DIR_TEST_RESULTS)/*.txt | grep FAIL`

all: $(DIR_DIST)/main.hex

$(DIR_DIST)/main.hex: $(DIR_BUILD_RELEASE)/main.elf
	@mkdir -p $(@D)
	@$(COPY) $< -O ihex $@

$(DIR_BUILD_RELEASE)/main.elf: $(OBJS)
	@$(CC_R) $(LIBS_PATH) $^ -o $@ $(LIBS)

$(DIR_BUILD_RELEASE)/%.o: $(DIR_SRC)/%.c
	@mkdir -p $(@D)
	@$(CC_R) $(INCLUDE_PATH) $(CFLAGS_R) -c $< -o $@

flash: $(DIR_DIST)/main.hex
	@avrdude -c usbasp -p $(AVRDUDE_MMCU) -U flash:w:"$<":a

size: $(DIR_BUILD_RELEASE)/main.elf
	@$(SIZE) --format=avr --mcu=$(MMCU) $<

clean:
	@rm -rf $(DIR_BUILD)
	@rm -rf $(DIR_DIST)

test: $(TRES)
	@printf "Test results:\n"
	@printf "PASSED:  $(TESTSUM_PASSED)\n"
	@printf "IGNORED: $(TESTSUM_IGNORED)\n"
	@printf "FAILED:  $(TESTSUM_FAILED)\n"
	@printf "$(TESTSUM_FAILED_DET)\n"

$(DIR_TEST_RESULTS)/%.txt: $(DIR_TEST_BIN)/%.out
	@mkdir -p $(@D)
	@-./$< > $@ 2>&1

$(DIR_TEST_BIN)/%_test.out: $(DIR_TEST_OBJ)/%.o $(DIR_TEST_OBJ)/%_test.o
	@mkdir -p $(@D)
	@$(CC_T) $^ -o $@ $(TEST_LIBS)

$(DIR_TEST_OBJ)/%.o:: $(DIR_TEST_SRC)/%.c
	@mkdir -p $(@D)
	@$(CC_T) $(TEST_INCLUDE_PATH) -c $< -o $@

$(DIR_TEST_OBJ)/%.o:: $(DIR_SRC)/%.c
	@mkdir -p $(@D)
	@$(CC_T) $(TEST_INCLUDE_PATH) -c $< -o $@

.PHONY: all flash size clean test
.PRECIOUS: $(DIR_TEST_BIN)/%.out $(DIR_TEST_RESULTS)/%.txt
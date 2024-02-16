# release toolchain
MMCU = atmega88pa
CC_R = avr-gcc -mmcu=$(MMCU)
COPY = avr-objcopy
SIZE = avr-size
CFLAGS_R = -Wall -Os -fshort-enums --param=min-pagesize=0 $(INCLUDE_PATH) $(LIBS_PATH)
AVRDUDE_MMCU = m88p

# dependencies
INCLUDE_PATH = \
	-I/usr/local/include \
	-I$(INCLUDES)
LIBS_PATH = \
	-L/usr/local/lib
LIBS = \
	-lavrhal-gpio

# structure
INCLUDES = include
SOURCES = src
BUILDS = build/release
DISTRIBUTION = dist
TEST_SOURCES = test
TEST_INCLUDES = test/include

# helper vars
SRCS = $(wildcard $(SOURCES)/*.c)
OBJS = $(patsubst $(SOURCES)/%.c,$(BUILDS)/%.o,$(SRCS))

all: $(DISTRIBUTION)/main.hex

$(DISTRIBUTION)/main.hex: $(BUILDS)/main.elf
	@mkdir -p $(@D)
	@$(COPY) $< -O ihex $@

$(BUILDS)/main.elf: $(OBJS)
	@$(CC_R) $(LIBS_PATH) $^ -o $@ $(LIBS)

$(BUILDS)/%.o: $(SOURCES)/%.c
	@mkdir -p $(@D)
	@$(CC_R) $(INCLUDE_PATH) $(CFLAGS_R) -c $< -o $@

flash: $(DISTRIBUTION)/main.hex
	@avrdude -c usbasp -p $(AVRDUDE_MMCU) -U flash:w:"$<":a

size: $(BUILDS)/main.elf
	@$(SIZE) --format=avr --mcu=$(MMCU) $<

clean:
	@rm -rf $(BUILDS)
	@rm -rf $(DISTRIBUTION)

.PHONY: all flash size clean
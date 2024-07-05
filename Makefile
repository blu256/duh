#### Options ####

## Memory dimensions
#
# For example, an 8x4 memory (default)
# gives you 32 single-byte memory blocks.
#
mem_x = 8
mem_y = 4

## Built-in protections
#
# Precautions against unexpected behaviour.
# You probably want this to be on.
#
use_safety = yes

## Random uses OpenSSL?
#
# The default generator doesn't give numbers
# random enough. This is why alternative
# backends are provided.
#
# Available backends: openssl system
#
rand_backend = openssl

## ANSI extension
#
# Not currently considered a part of the Duh
# standard (we do have one, duh! what do you
# mean?).
#
extension_ansi = yes

## Debug extension
#
# Useful debugging functions, also not part
# of the Duh standard.
#
extension_debug = yes


#################
#  DO NOT EDIT  #
#  UNLESS SURE  #
#################

SHELL=/bin/bash

src = main.c memory.c trace.c random.c
cc  = gcc

cflags  =
ldflags =

def  = -DMEMX=$(mem_x) -DMEMY=$(mem_y)

ifeq ($(use_safety), yes)
	def += -DSAFETY
endif

ifeq ($(rand_backend), openssl)
  cflags  += $(shell pkg-config --cflags openssl)
  ldflags += $(shell pkg-config --libs   openssl)
  def += -DRAND_BACKEND=RAND_OPENSSL
else ifeq ($(rand_backend), system)
  $(warning System random number backend produces suboptimal results.)
  def += -DRAND_BACKEND=RAND_SYSTEM
else
  $(error Invalid random number backend: $(rand_backend))
endif

# Extensions
ext_def =
ext_src =

ifeq ($(extension_ansi), yes)
  ext_def += -DEXTENSION_ANSI
  ext_src += ansi.c
endif

ifeq ($(extension_debug), yes)
  ext_def += -DEXTENSION_DEBUG -ggdb
  ext_src += debug.c
endif

duh: $(src) $(ext_src)
	@echo
	@echo "==[ Duh configuration ]======================"
	@echo
	@echo "  C Compiler:              $(cc)"
	@echo "  Compiler flags:          $(cflags)"
	@echo "  Linker flags:            $(ldflags)"
	@echo
	@echo "  VM memory size:          $(mem_x) x $(mem_y) = $$(( $(mem_x) * $(mem_y) )) bytes"
	@echo "  Random number subsystem: $(rand_backend)"
	@echo
	@echo
	@echo "-- Features ---------------------------------"
	@echo
	@echo "  Safety:                  $(use_safety)"
	@echo
	@echo
	@echo "-- Extensions -------------------------------"
	@echo
	@echo "  ANSI:                    $(extension_ansi)"
	@echo "  Debug:                   $(extension_debug)"
	@echo
	@echo

	$(cc) $(src) $(ext_src) -o$@ -O2 -Wall \
		$(def) \
                $(ext_def) \
		$(cflags) $(ldflags)

clean:
	@-rm -f duh *~

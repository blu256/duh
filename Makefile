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




#################
#  DO NOT EDIT  #
#  UNLESS SURE  #
#################

src = main.c memory.c trace.c
cc  = gcc

def = -DMEMX=$(mem_x) -DMEMY=$(mem_y)

ifeq "$(use_safety)" "yes"
def += -DSAFETY
endif

duh: $(src)
	$(cc) main.c -o$@ -O2 -Wall \
		$(def)

duh-dbg: $(src) debug.c
	$(cc) main.c -o$@ -O2 -Wall \
		-DDEBUG -ggdb \
		$(def)

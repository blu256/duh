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
# Available backends: openssl
#
rand_backend = openssl


#################
#  DO NOT EDIT  #
#  UNLESS SURE  #
#################

src = main.c memory.c trace.c random.c
cc  = gcc

cflags  =
ldflags =

def  = -DMEMX=$(mem_x) -DMEMY=$(mem_y)

def += -DRAND_BACKEND=$(rand_backend)

ifeq "$(use_safety)" "yes"
def += -DSAFETY
endif

ifeq "$(rand_backend)" "openssl"
cflags  += $(shell pkg-config --cflags openssl)
ldflags += $(shell pkg-config --libs   openssl)
endif

duh: $(src)
	$(cc) main.c -o$@ -O2 -Wall \
		$(def) \
		$(cflags) $(ldflags)

duh-dbg: $(src) debug.c
	$(cc) main.c -o$@ -O2 -Wall \
		-DDEBUG -ggdb \
		$(def) \
		$(cflags) $(ldflags)

clean:
	@-rm -f duh duh-dbg *~

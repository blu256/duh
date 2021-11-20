#### Options ####

## Memory dimensions
#
# For example, an 8x4 memory (default)
# gives you 32 single-byte memory blocks.
#
mem_x = 8
mem_y = 4





#################
#  DO NOT EDIT  #
#  UNLESS SURE  #
#################

src = main.c memory.c trace.c
cc  = gcc

duh: $(src)
	$(cc) main.c -o$@ -O2 -Wall \
		-DSAFETY \
		-DMEMX=$(mem_x) -DMEMY=$(mem_y)

duh-dbg: $(src) debug.c
	$(cc) main.c -o$@ -O2 -Wall \
		-DSAFETY \
		-DMEMX=$(mem_x) -DMEMY=$(mem_y) \
		-DDEBUG -ggdb

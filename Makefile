#### Options ####

## Memory dimensions
#
# For example, an 8x4 memory (default)
# gives you 32 single-byte memory blocks.
#
mem_x = 3
mem_y = 3





#################
#  DO NOT EDIT  #
#  UNLESS SURE  #
#################

src = main.c memory.c
cc  = gcc

duh: $(src)
	$(cc) main.c -o$@ -O2 -Wall \
		-DMEMX=$(mem_x) -DMEMY=$(mem_y)

duh-dbg: $(src) debug.c
	$(cc) main.c -o$@ -O2 -Wall \
		-DMEMX=$(mem_x) -DMEMY=$(mem_y) \
		-DDEBUG -ggdb

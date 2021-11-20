# duh is an esolang (duh!)

**duh** is a little just-for-fun esoteric language project.

In this repository you can find the `duh` interpreter.

This is written and tested on a Linux box, so on other systems your mileage
may vary. The interpreter itself is written in C and is compiled with standard
GNU `gcc`.

## Building

For a **release**, the following is enough:

```
$ make
```

You will find the `duh` binary in the current working directory.

For a **debugging** build with additional (debugging, duh!) features use:

```
$ make duh-dbg
```

## The `duh` language

Below is a short summary of the currently available instructions:

### Value instructions
```
  -   decrease value of current cell
  +   increase value of current cell
  0   reset value in current cell
```

### Pointer instructions
```
  (   previous memory cell    (decrement pointer)
  )   next memory cell        (increment pointer)
  '   jump to cell 0          (reset pointer)
```

### Seeking instructions
```
  @  go to the instruction N
  ^  seek forward by N instructions
```
(where `N` the current cell value)

### Conditions
```
  & if current value is zero, skip next instruction
```

### Input/output
```
   :  get single-byte value and place it in current cell
   ;  print value of current cell
```

### Debugging
**NOTE**: These options are available only in debugging builds.
```
   M  print memory map
```

All other symbols are ignored by design.

The language itself is prone to change, major breakages etc. Keep in mind I'm doing this just for fun (and as a practice in C ;-)

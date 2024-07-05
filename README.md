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

**Features and quirks**:
 * 2D memory block of preconfigurable size;
 * Transparent Unicode support;
 * Several flavours of directional/numeric `goto` statements instead of using functions/labels (very evil!);
 * Value manipulation done entirely by incrementing/decrementing and performing binary left-shifts/right-shifts by one (evil!);
 * Not entirely unlike the always popular Brainf*** language.

This list, like the language and the interpreter, are a constant work-in-progress and, as such, prone to changes.

See the `examples/` directory for code samples.

----

Below is a short summary of the currently available instructions:

### Value instructions
```
  -  decrease value of current cell
  +  increase value of current cell
  <  left-shift value by 1
  >  right-shift value by 1
  \  reset value in current cell
  *  replace value with a random number between 0 and the original value
  %  replace value with the instruction at position indicated by original value
  ~  swap value with register
  .  assign current value to register
  ,  assign current register to value
```

### Pointer instructions
```
  (  previous memory cell    (decrement pointer)
  )  next memory cell        (increment pointer)
  '  jump to cell 0          (reset pointer)
```

### Seeking instructions
```
  @  go to the instruction N
  ^  seek forward by N instructions
```
(where `N` is the current cell value)

### Jumping instructions
You can mark points in code with the `|` symbol and then use the
following instructions to jump back to them.

```
  _  jump to first | to the left
  =  jump to first | to the right
  $  jump to the nth occurence of |, according to current value
```

### Conditions
```
  &  if current value is void, skip next instruction
  `  if current value is void, exit
```

The following control characters are considered void values: 0 (NUL), 10 (LF), 13 (CR).

### Input/output
```
   :  get value and place it in current cell
   ;  print value of current cell
```

### Debugging
**NOTE**: These options are available only in debugging builds.
```
   M  print memory map
   T  print stack trace
   P  print cell information
   R  print register information
```

----

All other symbols are ignored by design.

The language itself is prone to change, major breakages etc. Keep in mind I'm doing this just for fun (and as a practice in C ;-)

## Notes

### Memory and Register

The memory is a (virtually 2D) memory block of predefined size. Each memory cell inside the block can contain one wide character code.

Apart from the main memory there is one additional register, which can be accessed and modified with the `~` instruction.

The register can store a value temporarily. You could probably use it to rearrange cells inside the memory.

### Comments

Any characted unused by the `duh` language is ignored. Thus, it is a safe bet that you can use all the lowercase letters (some
uppercase letters are reserved for debugging features) and all numbers.

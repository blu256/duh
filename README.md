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
  -  decrease value of current cell
  +  increase value of current cell
  <  left-shift value by 1
  >  right-shift value by 1
  \  reset value in current cell
  *  replace value with a random number between 0 and the original value
  ~  swap value with register
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
(where `N` the current cell value)

### Jumping instructions
You can mark points in code with the `|` symbol and then use the
following instructions to jumb back to them.

```
  _  jump to first | to the left
  =  jump to first | to the right
  #  jump to the nth occurence of |, according to current value
```

### Conditions
```
  &  if current value is zero, skip next instruction
  `  if current value is zero, exit
```

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

All other symbols are ignored by design.

The language itself is prone to change, major breakages etc. Keep in mind I'm doing this just for fun (and as a practice in C ;-)

## Notes

### Register

Apart from the main memory there is one additional register, which can be accessed and modified with the `~` instruction.

The register can store a value temporary. You could even use it to move values in memory!

### Comments

Any characted unused by the `duh` language is ignored. Thus, it is a safe bet that you can use all lowercase letters (some
uppercase letters are reserved for debugging features) and all numbers.

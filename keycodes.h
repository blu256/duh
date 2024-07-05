/***************************
 * Name:       keycodes.h  *
 * Programmer: blu.256     *
 * Date:       2021/11/21  *
 ***************************/

/* Control characters */
#define CR 13
#define LF 10

/* Value instructions */
#define VAL_INCR 43  // +  increase value
#define VAL_DECR 45  // -  decrease value
#define VAL_RSET 92  // \  reset value
#define VAL_RAND 42  // *  0 < random < current value
#define VAL_INST 37  // %  get instruction at value position
#define VAL_SWAP 126 // ~  swap value and register
#define VAL_VTOR 46  // .  assign value to register
#define VAL_RTOV 44  // ,  assign register to value
#define VAL_LSFT 60  // <  left shift by 1
#define VAL_RSFT 62  // >  right shift by 1

/* Pointer instructions */
#define PTR_INCR 41  // (  increase pointer
#define PTR_DECR 40  // )  decrease pointer
#define PTR_RSET 39  // '  reset pointer

/* Seeking instructions */
#define SRC_GOTO 64  // @  go to instruction by value
#define SRC_SEEK 94  // ^  seek from current by value

/* Jumping instructions */
#define JMP_LEFT 95  // _  jump to first mark to the left
#define JMP_RGHT 61  // =  jump to first mark to the right
#define JMP_GOTO 36  // $  jump to mark by value

/* Conditions */
#define CND_SKIP 38  // & if value is zero, skip next instruction
#define CND_TERM 96  // ` if value is zero, terminate

/* Input / output */
#define VAL_SCAN 58  // :  get a value
#define VAL_PRIN 59  // ;  print value

/* Misc. */
#define JMP_MARK 124 // |  mark

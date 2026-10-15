// Format narrow output with its actual byte capacity and variadic EE inputs, forwarding the compiler-generated argument list through the original bounded formatter and returning its integer length. The EE builtin argument-list mechanism emits all original GP and FPR saves without executable assembly.
// Reference algorithm: src/hand/func_001B0808.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef char *va_list;
#define va_start(ap,last) (ap=((char *)__builtin_next_arg(last)-(__builtin_args_info(2)>=8?0:(8-__builtin_args_info(2))*8)))
int func_00271490(char *output,unsigned int capacity,const char *format,va_list arguments);
int func_00271530(char *output,unsigned int capacity,const char *format,...){va_list arguments;va_start(arguments,format);return func_00271490(output,capacity,format,arguments);}

// Sly 2 counterpart: next_stack_level (decomp src/lib/next_stack_level.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef int ptr_type __attribute__ ((mode (pointer)));
typedef int word_type __attribute__ ((mode (DI)));
typedef struct frame_state {
  void *cfa; void *eh_ptr; long cfa_offset; long args_size;
  long reg_or_offset[80];
  unsigned short cfa_reg; unsigned short retaddr_column;
  char saved[80];
} frame_state;
#define REG_SAVED_OFFSET 1
#define REG_SAVED_REG 2
void abort(void);
word_type *func_0029D628(unsigned reg, frame_state *udata, frame_state *sub_udata);
frame_state *func_0029EAF8(void *, frame_state *);
static inline void *get_reg(unsigned reg, frame_state *udata, frame_state *sub_udata)
{ return (void *)(ptr_type)*func_0029D628(reg, udata, sub_udata); }
frame_state *func_0029D730(void *pc, frame_state *udata, frame_state *caller_udata)
{
  caller_udata = func_0029EAF8(pc, caller_udata);
  if (!caller_udata)
    return 0;
  if (udata->saved[caller_udata->cfa_reg])
    caller_udata->cfa = get_reg(caller_udata->cfa_reg, udata, 0);
  else
    caller_udata->cfa = udata->cfa;
  caller_udata->cfa += caller_udata->cfa_offset;
  return caller_udata;
}

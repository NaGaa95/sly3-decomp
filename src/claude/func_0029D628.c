// Sly 2 counterpart: get_reg_addr (decomp src/lib/get_reg_addr.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0 -fexceptions
// SLY3_ASM: gnu-reorder-db
#define FIRST_PSEUDO_REGISTER 79
#define REG_SAVED_OFFSET 1
#define REG_SAVED_REG 2
typedef int word_type __attribute__ ((mode (DI)));
typedef struct frame_state
{
  void *cfa;
  void *eh_ptr;
  long cfa_offset;
  long args_size;
  long reg_or_offset[FIRST_PSEUDO_REGISTER+1];
  unsigned short cfa_reg;
  unsigned short retaddr_column;
  char saved[FIRST_PSEUDO_REGISTER+1];
} frame_state;
extern void func_0029EFA8 (void);

static inline int
in_reg_window (int reg, frame_state *udata)
{
  return 0;
}

word_type *
func_0029D628 (unsigned reg, frame_state *udata, frame_state *sub_udata)
{
  while (udata->saved[reg] == REG_SAVED_REG)
    {
      reg = udata->reg_or_offset[reg];
      if (in_reg_window (reg, udata))
	{
          udata = sub_udata;
	  sub_udata = 0;
	}
    }
  if (udata->saved[reg] == REG_SAVED_OFFSET)
    return (word_type *)(udata->cfa + udata->reg_or_offset[reg]);
  else
    func_0029EFA8 ();
}

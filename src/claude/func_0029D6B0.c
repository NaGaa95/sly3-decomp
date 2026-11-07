// Sly 2 counterpart: copy_reg (decomp src/lib/copy_reg.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0 -fexceptions
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
void *func_00291E8C(void *, const void *, unsigned long);
static inline int dwarf_reg_size(int reg) { return reg < 31 ? 16 : reg < 64 ? 4 : 8; }
void func_0029D6B0(unsigned reg, frame_state *udata, frame_state *target_udata)
{
  word_type *preg = func_0029D628(reg, udata, 0);
  word_type *ptreg = func_0029D628(reg, target_udata, 0);
  func_00291E8C(ptreg, preg, dwarf_reg_size(reg));
}


// Sly 2 counterpart: __rethrow (decomp src/lib/__rethrow.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0 -fexceptions
// SLY3_ASM: gnu-reorder-db
#define FIRST_PSEUDO_REGISTER 79
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
struct eh_context
{
  void *handler_label;
  void **dynamic_handler_chain;
  void *info;
  void *table_index;
};
extern struct eh_context *(*get_eh_context) (void);
extern void __terminate (void);
extern struct frame_state *func_0029EAF8 (void *, struct frame_state *);
extern void *func_0029D7C8 (struct eh_context *eh, void *pc, frame_state *my_udata, frame_state **udata_p);

void
func_0029DCD8 (void *index)
{
  struct eh_context *eh = (*get_eh_context) ();
  void *pc, *handler;

  /* XXX maybe make my_ustruct static so we don't have to look it up for
     each throw.  */
  frame_state ustruct;
  frame_state *udata = &ustruct;
  frame_state my_ustruct, *my_udata = &my_ustruct;

  if (! eh->info)
    __terminate ();

  eh->table_index = index;

label:
  udata = func_0029EAF8 (&&label, udata);
  if (! udata)
    __terminate ();

  udata->cfa = __builtin_dwarf_cfa ();

  __builtin_memcpy (my_udata, udata, sizeof (*udata));

  __builtin_unwind_init ();

  pc = __builtin_extract_return_addr (__builtin_return_address (0)) - 1;

  handler = func_0029D7C8 (eh, pc, my_udata, &udata);

  __builtin_eh_return ((void *)eh, udata->cfa - my_udata->cfa, handler);
}


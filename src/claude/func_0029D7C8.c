// Sly 2 counterpart: throw_helper (decomp src/lib/throw_helper.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0 -fexceptions
// SLY3_ASM: gnu-reorder-db
#define FIRST_PSEUDO_REGISTER 79
#define DWARF_FRAME_REGISTERS FIRST_PSEUDO_REGISTER
#define REG_SAVED_REG 2
#define NEW_EH_RUNTIME ((void *) -2)
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
struct eh_context
{
  void *handler_label;
  void **dynamic_handler_chain;
  void *info;
  void *table_index;
};
typedef struct exception_descriptor
{
  void *runtime_id_field;
} exception_descriptor;
typedef struct __eh_info __eh_info;
extern void __terminate (void);
extern void func_0029D7C0 (void);
extern void *func_0029D4E0 (void *pc, exception_descriptor *table, __eh_info *eh_info, int rethrow, int *cleanup);
extern void *old_find_exception_handler (void *pc, void *table);
extern word_type *func_0029D628 (unsigned reg, frame_state *udata, frame_state *sub_udata);
extern void func_0029D6B0 (unsigned reg, frame_state *udata, frame_state *target_udata);
extern frame_state *func_0029D730 (void *pc, frame_state *udata, frame_state *caller_udata);

static inline int
in_reg_window (int reg, frame_state *udata)
{
  return 0;
}

static inline word_type
get_reg (unsigned reg, frame_state *udata, frame_state *sub_udata)
{
  return *func_0029D628 (reg, udata, sub_udata);
}

static inline void *
get_return_addr (frame_state *udata, frame_state *sub_udata)
{
  return (void *) (int) get_reg (udata->retaddr_column, udata, sub_udata);
}

void *
func_0029D7C8 (struct eh_context *eh, void *pc, frame_state *my_udata, frame_state **udata_p)
{
  frame_state *udata = *udata_p;
  frame_state sub_ustruct;
  frame_state *sub_udata = &sub_ustruct;
  void *saved_pc = pc;
  void *handler;
  void *handler_p;
  void *pc_p;
  frame_state saved_ustruct;
  int new_eh_model;
  int cleanup = 0;
  int only_cleanup = 0;
  int rethrow = 0;
  int saved_state = 0;
  __eh_info *eh_info = (__eh_info *)eh->info;

  if (eh->table_index != (void *) 0)
    rethrow = 1;

  handler = (void *) 0;
  for (;;)
    {
      frame_state *p = udata;
      udata = func_0029D730 (pc, udata, sub_udata);
      sub_udata = p;

      if (! udata)
	break;

      if (udata->eh_ptr == 0)
        new_eh_model = 0;
      else
        new_eh_model = (((exception_descriptor *)(udata->eh_ptr))->
                                          runtime_id_field == NEW_EH_RUNTIME);

      if (rethrow)
        {
          rethrow = 0;
          handler = func_0029D4E0 (eh->table_index, udata->eh_ptr,
                                          eh_info, 1, &cleanup);
          eh->table_index = (void *)0;
        }
      else
        if (new_eh_model)
          handler = func_0029D4E0 (pc, udata->eh_ptr, eh_info,
                                            0, &cleanup);
        else
          handler = old_find_exception_handler (pc, udata->eh_ptr);

      if (handler)
	{
	  if (cleanup)
	    {
	      if (!saved_state)
		{
		  saved_ustruct = *udata;
		  handler_p = handler;
		  pc_p = pc;
		  saved_state = 1;
		  only_cleanup = 1;
		}
	    }
	  else
	    {
	      only_cleanup = 0;
	      break;
	    }
	}

      pc = get_return_addr (udata, sub_udata) - 1;
    }

  if (saved_state)
    {
      udata = &saved_ustruct;
      handler = handler_p;
      pc = pc_p;
      if (only_cleanup)
        func_0029D7C0 ();
    }

  if (! handler)
    __terminate();

  eh->handler_label = handler;

  if (pc == saved_pc)
    udata = my_udata;
  else
    {
      int i;
      void *handler_pc = pc;

      pc = saved_pc;
      __builtin_memcpy (udata, my_udata, sizeof (*udata));

      while (pc != handler_pc)
	{
	  frame_state *p = udata;
	  udata = func_0029D730 (pc, udata, sub_udata);
	  sub_udata = p;

	  for (i = 0; i < DWARF_FRAME_REGISTERS; ++i)
	    if (i != udata->retaddr_column && udata->saved[i])
	      {
		if (in_reg_window (i, udata)
		    && udata->saved[udata->retaddr_column] == REG_SAVED_REG
		    && udata->reg_or_offset[udata->retaddr_column] == i)
		  continue;
		func_0029D6B0 (i, udata, my_udata);
	      }

	  pc = get_return_addr (udata, sub_udata) - 1;
	}

      if (udata->saved[udata->retaddr_column] == REG_SAVED_REG)
	{
	  i = udata->reg_or_offset[udata->retaddr_column];
	  if (in_reg_window (i, udata))
	    func_0029D6B0 (i, udata, my_udata);
	}
    }
  *udata_p = udata;
  return handler;
}

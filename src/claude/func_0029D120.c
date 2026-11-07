// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0 -fexceptions
// SLY3_ASM: gnu-reorder-db
struct eh_context
{
  void *handler_label;
  void **dynamic_handler_chain;
  void *info;
  void *table_index;
};
extern struct eh_context *(*get_eh_context) (void);
extern void __terminate (void);

void
func_0029D120 ()
{
  struct eh_context *eh = (*get_eh_context) ();
  void ***dhc = &eh->dynamic_handler_chain;
  void *jmpbuf;
  void (*func)(void *, int);
  void *arg;
  void ***cleanup = (void***)&(*dhc)[1];

  if (cleanup[0])
    {
      double store[200];
      void **buf = (void**)store;
      buf[1] = 0;
      buf[0] = (*dhc);

      if (! __builtin_setjmp (&buf[2]))
	{
	  *dhc = buf;
	  while (cleanup[0])
	    {
	      func = (void(*)(void*, int))cleanup[0][1];
	      arg = (void*)cleanup[0][2];

	      cleanup[0] = (void **)cleanup[0][0];

	      (*func)(arg, 2);
	    }
	  *dhc = buf[0];
	}
      else
	{
	  __terminate ();
	}
    }
  
  if (! eh->info || (*dhc)[0] == 0)
    __terminate ();
    
  jmpbuf = &(*dhc)[2];

  *dhc = (void**)(*dhc)[0];

  __builtin_longjmp (jmpbuf, 1);
}

extern void func_0029D120 (void) __attribute__ ((__noreturn__));

void
func_0029D298 ()
{
  struct eh_context *eh = (*get_eh_context) ();
  void ***dhc = &eh->dynamic_handler_chain;
  void (*func)(void *, int);
  void *arg;
  void ***cleanup;

  cleanup = (void***)&(*dhc)[1];

  if (cleanup[0])
    {
      double store[200];
      void **buf = (void**)store;
      buf[1] = 0;
      buf[0] = (*dhc);

      if (! __builtin_setjmp (&buf[2]))
	{
	  *dhc = buf;
	  while (cleanup[0])
	    {
	      func = (void(*)(void*, int))cleanup[0][1];
	      arg = (void*)cleanup[0][2];

	      cleanup[0] = (void **)cleanup[0][0];

	      (*func)(arg, 2);
	    }
	  *dhc = buf[0];
	}
      else
	{
	  __terminate ();
	}
    }

  *dhc = (void**)(*dhc)[0];

  func_0029D120 ();
}

short func_0029D3F8(void *p) { return ((short *)p)[3]; }
short func_0029D400(void *p) { return ((short *)p)[2]; }

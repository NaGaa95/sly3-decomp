// Sly 2 counterpart: frame_init (decomp src/lib/frame_init.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef unsigned int size_t;
typedef unsigned int uword;
typedef unsigned int uaddr;
typedef int sword;
typedef struct dwarf_fde { uword length; sword CIE_delta; void *pc_begin; uword pc_range; } fde;
struct object { void *pc_begin; void *pc_end; fde *fde_begin; fde **fde_array; size_t count; struct object *next; };
typedef struct fde_vector { fde **array; size_t count; } fde_vector;
typedef struct fde_accumulator { fde_vector linear; fde_vector erratic; } fde_accumulator;
void *func_001D27E0(size_t);
#define func_001D27E0 func_001D27E0
size_t count_fdes(fde *);
#define count_fdes count_fdes
void add_fdes(fde *, fde_accumulator *, void **, void **);
#define add_fdes add_fdes
fde **func_0029E058(fde_accumulator *, size_t);
#define end_fde_sort func_0029E058

static inline void
start_fde_sort (fde_accumulator *accu, size_t count)
{
  accu->linear.array = (fde **) func_001D27E0 (sizeof (fde *) * count);
  accu->erratic.array = (fde **) func_001D27E0 (sizeof (fde *) * count);
  accu->linear.count = 0;
  accu->erratic.count = 0;
}

void
func_0029E390 (struct object* ob)
{
  size_t count;
  fde_accumulator accu;
  void *pc_begin, *pc_end;

  if (ob->fde_array)
    {
      fde **p = ob->fde_array;
      for (count = 0; *p; ++p)
	count += count_fdes (*p);
    }
  else
    count = count_fdes (ob->fde_begin);

  ob->count = count;

  start_fde_sort (&accu, count);
  pc_begin = (void*)(uaddr)-1;
  pc_end = 0;

  if (ob->fde_array)
    {
      fde **p = ob->fde_array;
      for (; *p; ++p)
	add_fdes (*p, &accu, &pc_begin, &pc_end);
    }
  else
    add_fdes (ob->fde_begin, &accu, &pc_begin, &pc_end);

  ob->fde_array = end_fde_sort (&accu, count);
  ob->pc_begin = pc_begin;
  ob->pc_end = pc_end;
}

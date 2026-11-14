// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
// Sly 2 counterpart: end_fde_sort (decomp src/lib/end_fde_sort.c)
// libgcc frame.c (gcc 2.95) func_0029E058 with the original inline frame_heapsort
typedef unsigned int size_t;
typedef unsigned int uword;
typedef int sword;
typedef int saddr;
typedef struct dwarf_fde { uword length; sword CIE_delta; void *pc_begin; uword pc_range; } fde;
typedef struct fde_vector { fde **array; size_t count; } fde_vector;
typedef struct fde_accumulator { fde_vector linear; fde_vector erratic; } fde_accumulator;
extern void func_0029EFA8 (void) __attribute__((noreturn));
extern void func_001D27E8 (void *);
extern void func_0029ECD0 (fde_vector *, fde_vector *);
extern void func_0029DF58 (fde_vector *, fde_vector *);

static inline saddr
fde_compare (fde *x, fde *y)
{
  return (saddr)x->pc_begin - (saddr)y->pc_begin;
}

static inline void
frame_heapsort (fde_vector *erratic)
{
  fde ** a = erratic->array;
#define SWAP(x,y) do { fde * tmp = x; x = y; y = tmp; } while (0)
  size_t n = erratic->count;
  size_t m = n;
  size_t i;

  while (m > 0)
    {
      m--;
      for (i = m; 2*i+1 < n; )
        {
          if (2*i+2 < n
              && fde_compare (a[2*i+2], a[2*i+1]) > 0
              && fde_compare (a[2*i+2], a[i]) > 0)
            {
              SWAP (a[i], a[2*i+2]);
              i = 2*i+2;
            }
          else if (fde_compare (a[2*i+1], a[i]) > 0)
            {
              SWAP (a[i], a[2*i+1]);
              i = 2*i+1;
            }
          else
            break;
        }
    }
  while (n > 1)
    {
      n--;
      SWAP (a[0], a[n]);
      for (i = 0; 2*i+1 < n; )
        {
          if (2*i+2 < n
              && fde_compare (a[2*i+2], a[2*i+1]) > 0
              && fde_compare (a[2*i+2], a[i]) > 0)
            {
              SWAP (a[i], a[2*i+2]);
              i = 2*i+2;
            }
          else if (fde_compare (a[2*i+1], a[i]) > 0)
            {
              SWAP (a[i], a[2*i+1]);
              i = 2*i+1;
            }
          else
            break;
        }
    }
#undef SWAP
}

fde **
func_0029E058 (fde_accumulator *accu, size_t count)
{
  if (accu->linear.count != count)
    func_0029EFA8 ();
  func_0029ECD0 (&accu->linear, &accu->erratic);
  if (accu->linear.count + accu->erratic.count != count)
    func_0029EFA8 ();
  frame_heapsort (&accu->erratic);
  func_0029DF58 (&accu->linear, &accu->erratic);
  func_001D27E8 (accu->erratic.array);
  return accu->linear.array;
}

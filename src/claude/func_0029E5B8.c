// Sly 2 counterpart: extract_cie_info (decomp src/lib/extract_cie_info.c)
// SLY3_CC: tools/third_party/ee-gcc2.95.3-114
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
// SLY3_SAVES: sd
typedef unsigned int size_t;
typedef unsigned int uword;
typedef int sword;
typedef unsigned char ubyte;
typedef struct dwarf_cie { uword length; sword CIE_id; ubyte version; char augmentation[0]; } __attribute__ ((packed, aligned (__alignof__ (void *)))) dwarf_cie;
typedef struct dwarf_fde { uword length; sword CIE_delta; void *pc_begin; uword pc_range; } __attribute__ ((packed, aligned (__alignof__ (void *)))) fde;
struct cie_info { char *augmentation; void *eh_ptr; int code_align; int data_align; unsigned ra_regno; };
union unaligned { void *p; unsigned b2 __attribute__ ((mode (HI))); unsigned b4 __attribute__ ((mode (SI))); unsigned b8 __attribute__ ((mode (DI))); } __attribute__ ((packed));
int func_0029EE58(const char *, const char *);
#define strcmp func_0029EE58
size_t func_002715F8(const char *);
#define func_002715F8 func_002715F8
void *decode_uleb128(void *, unsigned *);
#define decode_uleb128 decode_uleb128
void *decode_sleb128(void *, int *);
#define decode_sleb128 decode_sleb128

static inline dwarf_cie *
get_cie (fde *f)
{
  return ((void *)&f->CIE_delta) - f->CIE_delta;
}

static inline void *
read_pointer (void *p)
{ union unaligned *up = p; return up->p; }

void *
func_0029E5B8 (fde *f, struct cie_info *c)
{
  void *p;
  int i;
  int r;

  c->augmentation = get_cie (f)->augmentation;

  r = strcmp (c->augmentation, "");
  __asm__ __volatile__ (""); /* emulates Sony scheduler: nothing hoisted above the strcmp call (PRE-inserted lui stays after it) */
  if (r != 0
      && strcmp (c->augmentation, "eh") != 0
      && c->augmentation[0] != 'z')
    return 0;

  p = c->augmentation + func_002715F8 (c->augmentation) + 1;

  if (strcmp (c->augmentation, "eh") == 0)
    {
      c->eh_ptr = read_pointer (p);
      p += sizeof (void *);
    }
  else
    c->eh_ptr = 0;

  p = decode_uleb128 (p, &c->code_align);
  p = decode_sleb128 (p, &c->data_align);
  c->ra_regno = *(unsigned char *)p++;

  if (c->augmentation[0] == 'z')
    {
      p = decode_uleb128 (p, &i);
      p += i;
    }

  return p;
}

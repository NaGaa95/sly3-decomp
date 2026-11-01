// Build the selection list around an item: collect up to five other candidates (skipping kind 7 and the item itself) that pass the plane test against the item, then refresh the list when it holds at least two.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct Method { short delta, reserved; void *(*call)(void *); };
struct Matrix { unsigned char opaque00[0x30]; qword position; };
struct Candidate {
    unsigned char opaque00[0xC];
    Method *methods;
    unsigned char opaque10[0x1B0 - 0x10];
    int kind;
};
struct Selection {
    unsigned char opaque00[0x44];
    Candidate *entries[5];
    int count;
    unsigned char opaque5C[0xA8 - 0x5C];
    int flag;
};
struct DL { void *pvFirst, *pvLast; int ibDle; };
struct DLI;
extern "C" DLI *D_0036AE94;
struct DLI {
    DL *pdl;
    void **ppv;
    int ibDle;
    DLI *pdliNext;
    DLI(DL *list) : pdl(list), ppv((void **)list), ibDle(list->ibDle), pdliNext(D_0036AE94) { D_0036AE94 = this; }
    ~DLI() { D_0036AE94 = pdliNext; }
    void *Next()
    {
        void *value = *ppv;
        ppv = (void **)((unsigned int)value + (unsigned int)ibDle);
        return value;
    }
};
extern "C" {
extern DL D_00479BEC;
int func_0021A710(void *object);
void *func_001F4A80(void *object);
int func_00167F60(void *target, qword position, qword extent);
void func_0021A1C8(Selection *selection, Candidate *item);
}
union QwordBox { qword q; float f; };
static inline qword BcG(float f) { QwordBox u; qword r; __asm__("mfc1 %0,%1" : "=r"(r) : "f"(f)); u.q = r; return r; }
#define MATRIX(o) ((Matrix *)(o)->methods[36].call((unsigned char *)(o) + (o)->methods[36].delta))
extern "C" void func_0021A068(Selection *selection, Candidate *item)
{
    if (func_0021A710(selection)) return;
    if (!item) return;
    selection->entries[0] = item;
    selection->count = 1;
    DLI iterator(&D_00479BEC);
    Candidate *entry;
    while ((entry = (Candidate *)iterator.Next()) != 0) {
        if (entry->kind == 7) continue;
        if (entry == item) continue;
        {
            void *target = func_001F4A80(item);
            qword position = MATRIX(entry)->position;
            
            if (func_00167F60(target, position, BcG(0.0f))) {
                if ((unsigned int)selection->count >= 5) break;
                selection->entries[selection->count++] = entry;
            }
        }
    }
    if (selection->count >= 2) {
        selection->flag = 0;
        func_0021A1C8(selection, item);
    }
}

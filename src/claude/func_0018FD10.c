// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
void *memset(void *, int, unsigned int);
struct Header { float value; int pad; int count; };
struct Desc { unsigned char pad[3]; signed char kind; };
float func_00119260(void *stream);
int func_00119128(void *stream);
void func_0018FF98(void *self, struct Desc *desc, void *a, struct Header *h, void *b, void *c, void *stream, void *d);
void func_00194558(void *self, struct Desc *desc, void *a, struct Header *h, void *b, void *c, void *stream, void *d);
void func_00192BB0(void *self, struct Desc *desc, void *a, struct Header *h, void *b, void *c, void *stream, void *d);
void func_00192FD8(void *self, struct Desc *desc, void *a, struct Header *h, void *b, void *c, void *stream, void *d);
void func_0018FD10(void *self, struct Desc *desc, void *a, void *b, void *c, void *stream, void *d)
{
    struct Header h;
    memset(&h, 0, sizeof(h));
    h.value = func_00119260(stream);
    h.count = func_00119128(stream);
    switch (desc->kind) {
    case 0: func_0018FF98(self, desc, a, &h, b, c, stream, d); break;
    case 1: func_00194558(self, desc, a, &h, b, c, stream, d); break;
    case 2: func_00192BB0(self, desc, a, &h, b, c, stream, d); break;
    case 3: func_00192FD8(self, desc, a, &h, b, c, stream, d); break;
    }
}

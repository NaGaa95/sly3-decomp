// SLY3_CFLAGS: -Os -G0
struct WidgetEntry { short delta; short pad; void (*method)(void *); };
struct Widget { unsigned char prefix[0xC]; struct WidgetEntry *table; unsigned char gap10[0x40 - 0x10]; int word40; float f44; unsigned char gap48[0x50 - 0x48]; float f50; int word54; };
struct WidgetSelf { unsigned char prefix[0x47A8]; struct Widget *w[9]; };
struct Widget *func_00150690(int kind, int a, int id, int b);
void func_00173C10(struct WidgetSelf *self)
{
    {
        struct Widget *w = func_00150690(0x8B, 0, 0x319, -1);
        w->word40 = 0;
        self->w[0] = w;
        w->table[9].method((char *)w + w->table[9].delta);
    }
    {
        struct Widget *w = func_00150690(0x8B, 0, 0x31A, -1);
        w->f50 = -1.0f;
        w->word40 = 1;
        self->w[1] = w;
        w->table[9].method((char *)w + w->table[9].delta);
    }
    {
        struct Widget *w = func_00150690(0x8B, 0, 0x31B, -1);
        w->word40 = 0;
        w->f44 = 750.0f;
        self->w[2] = w;
        w->table[9].method((char *)w + w->table[9].delta);
    }
    {
        struct Widget *w = func_00150690(0x8B, 0, 0x31C, -1);
        w->f44 = 2500.0f;
        w->f50 = 0.35f;
        w->word40 = 0;
        self->w[3] = w;
        w->table[9].method((char *)w + w->table[9].delta);
    }
    {
        struct Widget *w = func_00150690(0x8B, 0, 0x31E, -1);
        w->f50 = -1.0f;
        w->word54 = 3;
        w->word40 = 0;
        self->w[5] = w;
        w->table[9].method((char *)w + w->table[9].delta);
    }
    {
        struct Widget *w = func_00150690(0x8B, 0, 0x31D, -1);
        w->f44 = 1500.0f;
        w->f50 = 0.5f;
        w->word40 = 0;
        self->w[4] = w;
        w->table[9].method((char *)w + w->table[9].delta);
    }
    {
        struct Widget *w = func_00150690(0x8B, 0, 0x31F, -1);
        w->word40 = 0;
        w->f44 = 1000.0f;
        self->w[6] = w;
        w->table[9].method((char *)w + w->table[9].delta);
    }
}

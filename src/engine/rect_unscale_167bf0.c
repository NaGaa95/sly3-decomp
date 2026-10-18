// SLY3_CFLAGS: -Os -G0
struct ScreenSize { void *vtable; int width; int height; };
struct RectEntry { short delta, padding; void (*fn)(void *); };
struct RectTable { unsigned char prefix[0x1B8]; struct RectEntry entry; };
struct RectOwner {
    unsigned char prefix[0xC]; struct RectTable *table;
    unsigned char gap10[0x150 - 0x10];
    int left, top, right, bottom;
    int scaledLeft, scaledTop, scaledRight, scaledBottom;
};
extern struct ScreenSize D_0036DBE0;
void func_00167BF0(struct RectOwner *self, int left, int top, int right, int bottom)
{
    self->left = left;
    self->top = top;
    self->right = right;
    self->bottom = bottom;
    self->scaledLeft = left * D_0036DBE0.width / 640;
    self->scaledTop = top * D_0036DBE0.height / 480;
    self->scaledRight = right * D_0036DBE0.width / 640;
    self->scaledBottom = bottom * D_0036DBE0.height / 480;
    self->table->entry.fn((char *)self + self->table->entry.delta);
}

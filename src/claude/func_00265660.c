// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Lay out and draw a text block glyph by glyph into the packet, clipped to the screen (cf. func_00266240).
typedef unsigned long u_long;
typedef int QW __attribute__((mode(TI)));
struct R { char pad[0xC]; unsigned char *cur; };
struct GS { int pad0; int w; int h; };
struct SPR { int pad0; int fVisible; };
struct GLYPH { char pad[8]; struct SPR *spr; };
struct FONT { char pad[0x14]; struct GLYPH **aglyph; };
struct LINE { int end; float width; };
struct TEXT {
    unsigned short *start; unsigned short *cur; struct FONT *font; char padC[0x20 - 0xC];
    QW q20; QW q30; char pad40[0x60 - 0x40]; int fLimit; char pad64[0x74 - 0x64];
    float width; float height; float xScale; float yScale; float lineScale; float advScale;
    char pad8C[0x94 - 0x8C]; int cline; struct LINE aline[0x20]; int valign; int halign; int depth;
};
struct POS { char pad[0x20]; float x; float y; };
struct D { int a; int mode; float z; int xC; QW q10; QW q20; };
struct CMD { int op; float z; unsigned int addr; int x; };
extern struct R D_0036C308;
extern struct GS D_0036DBE0;
float func_002BE228(struct GS *, float);
float func_002BE230(struct GS *, float);
int func_002BC640(struct GS *, int);
int func_002BC648(struct GS *, int);
void func_00264B18(struct TEXT *, int);
unsigned int func_00264BB0(struct TEXT *);
int func_002718D8(unsigned int);
struct GLYPH *func_00265D68(struct FONT *, unsigned int);
float func_00265DE0(struct FONT *, unsigned int);
void func_00266240(struct SPR *, struct POS *, struct D *, int);
struct CMD *func_00209B60(void);
static inline void Align(struct R *r) {
    while((int)r->cur&15) { *(int *)r->cur=0; r->cur+=4; }
}
void func_00265660(struct TEXT *p, struct POS *pos, struct D *data)
{
    unsigned char *tag;
    struct LINE *line = p->aline;
    int fNeedLine = 1;
    float x0 = pos->x;
    int fSkip = 1;
    float lineH = func_002BE230(&D_0036DBE0, p->lineScale * p->yScale * (float)D_0036DBE0.h * 0.0020833334f);
    int n;
    struct LINE *lineEnd;
    int cDrawn;
    int cLimit;
    float xMin, xMax, yMin, yMax;
    unsigned int ch;
    struct CMD *cmd;
    tag = D_0036C308.cur;
    data->a = 0;
    n = p->cline;
    lineEnd = line + n;
    if (p->valign) {
        float d = func_002BE230(&D_0036DBE0, p->height * p->yScale * (float)D_0036DBE0.h * 0.0020833334f) - (float)n * lineH;
        if (p->valign == 2)
            pos->y += d;
        else
            pos->y += d * 0.5f;
    }
    cDrawn = 0;
    xMin = (float)(0x800 - func_002BC640(&D_0036DBE0, D_0036DBE0.w) / 2) + -128.0f + 786432.0f;
    cLimit = 2;
    xMax = (float)func_002BC640(&D_0036DBE0, D_0036DBE0.w) + 128.0f + (float)(0x800 - func_002BC640(&D_0036DBE0, D_0036DBE0.w) / 2) + 786432.0f;
    yMin = (float)(0x800 - func_002BC648(&D_0036DBE0, D_0036DBE0.h) / 2) + -128.0f + 786432.0f;
    yMax = (float)func_002BC648(&D_0036DBE0, D_0036DBE0.h) + 128.0f + (float)(0x800 - func_002BC648(&D_0036DBE0, D_0036DBE0.h) / 2) + 786432.0f;
    if (yMax < pos->y)
        return;
    func_00264B18(p, 0);
    while ((ch = func_00264BB0(p)) != 0) {
        int iChar;
        struct GLYPH *glyph;
        struct FONT *font;
        int fRight, fVisible;
        float adv;
        if (p->fLimit)
            cLimit = cDrawn + 3;
        iChar = p->cur - p->start - 1;
        if (!fNeedLine && line < lineEnd && iChar >= line->end) {
            fSkip = 1;
            fNeedLine = 1;
            pos->y += lineH;
            if (yMax < pos->y)
                break;
        }
        if (fNeedLine) {
            if (!p->halign) {
                pos->x = x0;
            } else {
                float w = func_002BE228(&D_0036DBE0, line->width * p->xScale * (float)D_0036DBE0.w * 0.0015625f);
                float d = func_002BE228(&D_0036DBE0, p->width * p->xScale * (float)D_0036DBE0.w * 0.0015625f);
                pos->x = p->halign == 2 ? x0 + (d - w) : x0 + (d - w) * 0.5f;
            }
            line++;
            fNeedLine = 0;
        }
        if (fSkip && func_002718D8(ch))
            continue;
        fSkip = 0;
        font = p->font;
        if (ch < 0x100)
            glyph = font->aglyph[ch];
        else
            glyph = func_00265D68(font, ch);
        if (!glyph)
            continue;
        fRight = xMax < pos->x;
        if (fRight && line == lineEnd)
            break;
        fVisible = 0;
        if (xMin <= pos->x && !fRight && yMin <= pos->y)
            fVisible = 1;
        if (glyph->spr->fVisible && fVisible) {
            int flags = cDrawn < 2;
            if (cDrawn < cLimit) {
                flags |= 2;
                data->q10 = p->q20;
                data->q20 = p->q30;
            }
            func_00266240(glyph->spr, pos, data, flags);
            cDrawn++;
        }
        adv = func_00265DE0(p->font, ch);
        pos->x += func_002BE228(&D_0036DBE0, adv * p->advScale * p->xScale * (float)D_0036DBE0.w * 0.0015625f);
    }
    Align(&D_0036C308);
    *(u_long *)D_0036C308.cur = 0x60000000UL;
    D_0036C308.cur += 16;
    cmd = func_00209B60();
    cmd->op = 0x90;
    cmd->z = data->z + (float)p->depth * 65536.0f;
    cmd->x = 0;
    cmd->addr = (unsigned int)tag & 0x0FFFFFFF;
}

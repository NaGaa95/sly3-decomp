// Set scalar defaults, initialize the resource from the explicit input stream, and fill missing duration and selection values from their fallback fields.
// Reference algorithm: src/hand/func_002035A8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0xD0]; float gE0; float gE4; float gE8; char p2[8]; int nF4; int nF8; char p3[8]; float g104; };
void func_0028FDE0(struct S *p, void *input);
void func_0024D4F8(struct S *p, void *input)
{
    p->gE4 = 0.0f;
    p->gE0 = 75.0f;
    p->gE8 = 0.25f;
    p->g104 = 5000.0f;
    func_0028FDE0(p, input);
    if (p->gE4 == 0.0f) p->gE4 = p->gE0;
    if (p->nF8 == -2) p->nF8 = p->nF4;
}

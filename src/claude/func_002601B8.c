// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Upload a 2-qword packet and start the VU1 microprogram at 0xC0 (VIFS chain).
struct VIFS;
extern char D_004BB1F0[];
extern char D_000000C0[];
void func_001746C0(struct VIFS *);            /* DMAS::AddDmaCnt */
void func_0027E2A8(struct VIFS *);            /* VIFS::AddVifFlusha */
void func_0027E660(struct VIFS *, int, void *, int); /* VIFS::AddVifDirect */
void func_0027E260(struct VIFS *, void *);    /* VIFS::AddVifMscal */
void func_001748F8(struct VIFS *);            /* DMAS::EndDmaCnt */
void func_002601B8(void *a, void *b, struct VIFS *pvifs)
{
    func_001746C0(pvifs);
    func_0027E2A8(pvifs);
    func_0027E660(pvifs, 2, D_004BB1F0, 0);
    func_0027E260(pvifs, D_000000C0);
    func_0027E2A8(pvifs);
    func_001748F8(pvifs);
}

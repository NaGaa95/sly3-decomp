// Sly 2 reference: src/hand/func_00128F70.cpp.
// GNU declaration labels establish canonical Sly 3 symbols without executable assembly.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct X;
struct Y;
struct SPX { X *p; ~SPX(); SPX &operator=(X *px) __asm__("func_002BAA50"); };
struct SPY { Y *p; ~SPY(); SPY &operator=(Y *py) __asm__("func_002BA780"); };
struct O {
    int cref;
    int x4;
    SPX spx;
    int xC;
    int x10;
    SPY spy14;
    SPY spy18;
    ~O();
};
struct SPO {
    O *p;
    void Set(O *po) __asm__("func_002BAB68");
    SPO() {}
    SPO(O *po) { Set(po); }
    SPO(const SPO &);
    ~SPO() { O *po = p; if (po && --po->cref == 0) delete po; }
    O *operator->() { return p; }
};
extern "C" {
O *func_002BAAB8() __asm__("func_002BAAB8");
SPO func_0012ACC8(O *poSrc, X *px) __asm__("func_0012ACC8");
}
SPO func_0012ACC8(O *poSrc, X *px)
{
    SPO sp;
    sp.Set(func_002BAAB8());
    if (px)
        sp->spx = px;
    else
        sp->spx = poSrc->spx.p;
    sp->spy14 = poSrc->spy14.p;
    sp->xC = poSrc->xC;
    sp->x10 = poSrc->x10;
    sp->spy18 = poSrc->spy18.p;
    return SPO(sp.p);
}

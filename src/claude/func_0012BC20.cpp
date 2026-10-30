// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// CRef::Decref (Sly 3): adapted from the matched Sly 2 source src/hand/Decref__4CRef.cpp (short tag, tags 2 lower,
// pooled payloads freed through POOLSTATE::Free, node/frame/object payloads deleted through their destructors).
typedef int qword __attribute__((mode(TI)));
struct POOLSTATE { void Free(void *pv); };
extern POOLSTATE D_004D2F28, D_004D2F40, D_004D2F58, D_004D2F70, D_004D2F88;
struct VT { short d; short pad; void (*pfn)(void *); };
struct O1F { char pad[0xC]; VT *vt; };
struct NV { qword v; int cref; };
struct NM { qword m[4]; int cref; };
struct N2 { int a[2]; int cref; };
struct N3 { int a[3]; int cref; };
struct NODE { short x0; short cref; };
struct O { int cref; ~O(); };
struct O20 { int cref; };
extern "C" void func_002BA840(NODE *p, int f); /* NODE deleting destructor */
extern "C" void func_002BB798(O20 *p, int f); /* deleting destructor */
struct CRef {
    short m_tagk;
    void *m_pv;
    void Decref();
};
void CRef::Decref()
{
    switch (m_tagk) {
    case 0x18: {
        NV *p = (NV *)m_pv;
        if (--p->cref == 0)
            D_004D2F28.Free(p);
        break;
    }
    case 0x19: {
        NM *p = (NM *)m_pv;
        if (--p->cref == 0)
            D_004D2F40.Free(p);
        break;
    }
    case 0x1A: {
        NV *p = (NV *)m_pv;
        if (--p->cref == 0)
            D_004D2F58.Free(p);
        break;
    }
    case 0x1B: {
        N2 *p = (N2 *)m_pv;
        if (--p->cref == 0)
            D_004D2F70.Free(p);
        break;
    }
    case 0x1C: {
        N3 *p = (N3 *)m_pv;
        if (--p->cref == 0)
            D_004D2F88.Free(p);
        break;
    }
    case 0x1D: {
        NODE *p = (NODE *)m_pv;
        if (--p->cref == 0 && p)
            func_002BA840(p, 3);
        break;
    }
    case 0x1E: {
        O *p = (O *)m_pv;
        if (--p->cref == 0)
            delete p;
        break;
    }
    case 0x1F: {
        O1F *p = (O1F *)m_pv;
        if (p)
            p->vt[2].pfn((char *)p + p->vt[2].d);
        break;
    }
    case 0x20: {
        O20 *p = (O20 *)m_pv;
        if (--p->cref == 0 && p)
            func_002BB798(p, 3);
        break;
    }
    }
}

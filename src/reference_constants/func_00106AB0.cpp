// Complete original function, inputs and emitted data independently reviewed.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct CRef {
    short m_tagk;
    short padding;
    union {
        int n;
        float g;
        void *pv;
    }
    u;
    CRef() {
        m_tagk = -1;
    }
    CRef(int tagk) {
        InitTag(tagk);
    }
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    ~CRef() {
        Decref();
    }
    CRef &operator=(const CRef &r);
    CRef &operator=(void *pv);
    CRef &operator=(qword q);
    CRef &operator=(bool f);
    CRef &operator=(int n);
    CRef &operator=(float g);
};
extern "C" CRef func_0024B2B8(int c, void *aref, int *ak, ...);
extern "C" {
    void func_00224ED0(void *p, int, float, float, float, int, int, float, float, float, int);
    CRef func_00106AB0(void *p, int c, void *aref);
}
CRef func_00106AB0(void *p, int c, void *aref) {
    int ak[10] = {
        0x6, 0x1, 0x1, 0x1, 0x100b, 0x6, 0x1, 0x1, 0x1, 0x100b
    };
    int v0;
    float v1;
    float v2;
    float v3;
    int v4;
    int v5;
    float v6;
    float v7;
    float v8;
    int v9;
    CRef ref = func_0024B2B8(10, aref, ak, &v0, &v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, &v9);
    ref.Decref();
    ref.InitTag(0x22);
    func_00224ED0(p, v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
    return ref;
}

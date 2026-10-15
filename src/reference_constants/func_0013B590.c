// Reference algorithm: src/hand/func_00132BC8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
/* EnsureLoSidebagBool (Sly 1 name); C++ original inlined CRef ctor/Set*, ~CRef -> Decref (func_0012BC20) */
struct LO;
struct CRef { short m_tagk; short unknown_tag_padding; union { int m_n; float m_g; } m_tag; };
void func_0024AD00(struct CRef *pref, struct LO *pbasic, int optid, struct CRef *prefValue);
void func_0012BC20(struct CRef *);
void func_0013B590(struct LO *plo, int optid, int v)
{
    struct CRef ref;
    struct CRef refT;
    ref.m_tagk = 0x15;
    ref.m_tag.m_n = v != 0;
    func_0024AD00(&refT, plo, optid, &ref);
    func_0012BC20(&refT);
    func_0012BC20(&ref);
}

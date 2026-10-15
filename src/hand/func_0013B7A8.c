// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
/* EnsureLoSidebag* with a 128-bit by-value argument (VECTOR/QW?) passed to func_0012AFA0 (CRef setter/ctor) */
struct LO;
typedef int ti128 __attribute__((mode(TI)));
struct CRef { int m_tagk; union { int m_n; float m_g; } m_tag; };
void RefEnsureOption(struct CRef *pref, struct LO *pbasic, int optid, struct CRef *prefValue);
void func_0012BC20(struct CRef *);
void func_0012AFA0(struct CRef *, ti128);
void func_0013B7A8(struct LO *plo, int optid, ti128 v)
{
    struct CRef ref;
    struct CRef refT;
    func_0012AFA0(&ref, v);
    RefEnsureOption(&refT, plo, optid, &ref);
    func_0012BC20(&refT);
    func_0012BC20(&ref);
}

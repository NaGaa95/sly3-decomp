// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct EYES { char pad[0x64]; int n64; char pad2[0x74-0x68]; float g74; float g78; };
void func_002378C0(struct EYES *p, int eyess);
void func_00237220(struct EYES *p, int iframe);
void func_00237B70(struct EYES *p, float g)
{
    p->g78 = g;
    if (g >= 1.0f) {
        func_002378C0(p, 2);
    } else {
        p->n64 = -1;
        func_002378C0(p, 0);
    }
    func_00237220(p, (int)p->g74);
}

// Reference algorithm: src/hand/func_001ABB10.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct SAVE { char ab[0x6864]; };
struct M { char pad[0x24]; struct SAVE asave[4]; };
extern char D_00323AA0[], D_00323AB0[], D_00323AC8[];
int func_00271448(char *buf, char *fmt, ...);
void func_001CFB40(struct M *pm, struct SAVE *ps, char *buf)
{
    func_00271448(buf, D_00323AA0, D_00323AB0, D_00323AC8, ps - pm->asave + 1);
}

// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct BMP { char pad[8]; unsigned short w; unsigned short h; unsigned char psm; unsigned char bw; char pad2[0x18-0xE]; int cqw; };
void func_00196D28(int dbp, int dbw, int psm, int w, int h, int cqw, void *pgifs);
void func_00236298(struct BMP *pbmp, int dbp, void *pgifs)
{
    func_00196D28(dbp, pbmp->bw, pbmp->psm, pbmp->w, pbmp->h, pbmp->cqw, pgifs);
}

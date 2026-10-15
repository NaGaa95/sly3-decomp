// SLY3_CFLAGS: -Os -G0
/* Render-mode setup callback. The dispatcher supplies two integer IDs followed
   by the global VIFS receiver; this method consumes only that third input. */
typedef struct VIFS VIFS;
extern const unsigned char D_002C1420[], D_002C1CF0[];
extern unsigned char D_0036E340[];
extern unsigned char D_004BAD10[], D_004BB0B0[], D_004BB0D0[];
extern unsigned char D_004BB0F0[], D_004BB120[], D_004BB1A0[], D_004BB160[];
extern int D_004BADB0;
extern unsigned char D_004BADC0[];

/* Linker labels in VU microinstruction byte address space. The original MPG
   stream uploads 280 instructions at byte zero; these entries are at PC24/32.
   These declarations do not define or allocate EE data objects. */
extern const unsigned char VU_RenderSetup_entry_C0[];
extern const unsigned char VU_RenderSetup_entry_100[];

void func_00182D60(VIFS *receiver, const void *begin, const void *end);
void func_001746C0(VIFS *receiver);
void func_0027E2A8(VIFS *receiver);
void func_001747A0(VIFS *receiver, const void *chain);
void func_0027E228(VIFS *receiver, int base, int offset);
void func_0027E4C0(VIFS *receiver, int format, int count, const void *data, int address);
void func_0027E260(VIFS *receiver, const void *microEntry);
void func_0027E660(VIFS *receiver, int quadwords, const void *packet, int interrupt);
void func_001748F8(VIFS *receiver);

void func_00260020(int currentID, int previousID, VIFS *receiver)
{
    func_00182D60(receiver, D_002C1420, D_002C1CF0);
    func_001746C0(receiver);
    func_0027E2A8(receiver);
    func_001747A0(receiver, D_0036E340);
    func_0027E228(receiver, 0, 0);
    func_0027E4C0(receiver, 12, 7, D_004BAD10, 15);
    func_0027E4C0(receiver, 12, 2, D_004BB0B0, 23);
    func_0027E4C0(receiver, 12, 2, D_004BB0D0, 25);
    func_0027E4C0(receiver, 12, 3, D_004BB0F0, 27);
    func_0027E4C0(receiver, 12, 4, D_004BB120, 30);
    func_0027E4C0(receiver, 12, 3, D_004BB1A0, 34);
    func_0027E4C0(receiver, 12, 4, D_004BB160, 37);
    func_0027E228(receiver, 52, 486);
    func_0027E260(receiver, VU_RenderSetup_entry_C0);
    func_0027E2A8(receiver);
    func_0027E660(receiver, D_004BADB0, D_004BADC0, 0);
    func_0027E2A8(receiver);
    func_0027E260(receiver, VU_RenderSetup_entry_100);
    func_0027E2A8(receiver);
    func_001748F8(receiver);
}

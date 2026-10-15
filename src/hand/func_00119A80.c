// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
typedef struct X { int n0; char pad[0x30]; int n34; int n38; } X;

void func_00119A80(X *px, int n34, int n38, int n0)
{
    px->n34 = n34;
    px->n38 = n38;
    px->n0 = n0;
}

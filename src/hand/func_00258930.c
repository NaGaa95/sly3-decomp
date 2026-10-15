// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct S { int a; char pad[0x8C]; int b; float g; float h; };
void func_00258930(struct S *p, int a, int b) {
  p->a = a;
  p->b = b;
  p->h = 1.0f;
  p->g = 0.6f;
}

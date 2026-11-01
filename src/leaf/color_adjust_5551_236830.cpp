// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Convert a packed 5551 colour (when the colour-processing flag in D_0036DBEC is set) through func_00236908 (adjust
// RGBA bytes in place) and pack it back. Based on Sly 2 func_001ED1A8.
struct RGBA { unsigned char r, g, b, a;
  RGBA() {}
  RGBA(unsigned char r_, unsigned char g_, unsigned char b_, unsigned char a_) { r = r_; g = g_; b = b_; a = a_; }
};
struct BF { unsigned short r : 5; unsigned short g : 5; unsigned short b : 5; unsigned short a : 1; };
union U { unsigned short w; BF bf; };
extern "C" { extern int D_0036DBEC; void func_00236908(RGBA *prgba); void func_00236830(U *pu); }
static inline U Pack(RGBA c) { U u; u.bf.r = c.r >> 3; u.bf.g = c.g >> 3; u.bf.b = c.b >> 3; u.bf.a = c.a >> 7; return u; }
void func_00236830(U *pu)
{
    if ((D_0036DBEC >> 1) & 1) {
        RGBA c(pu->bf.r << 3, pu->bf.g << 3, pu->bf.b << 3, pu->bf.a ? 0xFF : 0);
        func_00236908(&c);
        *pu = Pack(c);
    }
}

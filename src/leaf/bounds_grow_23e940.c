// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Grow the owner's bounding volume (min/max corners, centre and radius) so that it contains the sphere (c, r). Sly 3 variant of
// Sly 2 func_001F5480: the radius check adds the sphere radius to the centre distance.

typedef int qword __attribute__((mode(TI)));
struct B { qword min; qword max; qword c; float r; };
struct P { char pad[0xDC]; struct B *pb; };

void func_0023E940(struct P *p, qword c, float r)
{
    qword rr, hi, d, one; register qword lo __asm__("vf3"); /* register pin: low corner lives in vf3 */ float dist;
    
    __asm__("pextlw %0, %1, %1
	pextlw %0, %0, %0" : "=r"(rr) : "r"(r));
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(lo) : "j"(c), "j"(rr));
    __asm__("vmini.xyz %0, %1, %2" : "=j"(p->pb->min) : "j"(p->pb->min), "j"(lo));
    __asm__("vadd.xyzw %0, %1, %0" : "+j"(rr) : "j"(c)); hi = rr;
    __asm__("vmax.xyz %0, %1, %2" : "=j"(p->pb->max) : "j"(p->pb->max), "j"(hi));
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(c) : "0"(c), "j"(p->pb->c));
    __asm__("vmul.xyz %0, %2, %2
	vaddw.x %1, $vf0, $vf0w
	vadday.x $ACC, %0, %0y
	vmaddz.x %0, %1, %0z
	vsqrt $Q, %0x
	vwaitq
	vaddq.x %0, $vf0, $Q" : "=j"(d), "=&j"(one) : "0"(c));
    __asm__("mtc1 %1, %0" : "=f"(dist) : "r"(d));
    {
        float total = dist + r;
        if (p->pb->r < total) p->pb->r = total;
    }
}

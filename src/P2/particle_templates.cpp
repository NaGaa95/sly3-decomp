// Readable runtime GIF template builders, reconstructed from complete original helpers.
// Sly2 algorithm reference: references/sly2/src/hand/func_00138F08.cpp.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "gifs.h"

enum GifRegister { GIF_RGBAQ=1, GIF_ST=2, GIF_XYZF2=4, GIF_AD=14 };
enum GsRegister { GS_ALPHA_1=0x42, GS_TEST_1=0x47 };
enum AlphaTest { ALPHA_GEQUAL=5 };
enum AlphaFailure { ALPHA_KEEP=0, ALPHA_FRAME_ONLY=1 };
enum DepthTest { DEPTH_GEQUAL=2, DEPTH_GREATER=3 };

static __inline__ long ParticleTest(int reference,int failure,int depth)
{
    return 1L | ((long)ALPHA_GEQUAL<<1) | ((long)reference<<4)
         | ((long)failure<<12) | (1L<<16) | ((long)depth<<17);
}
static __inline__ ulong ParticleRegisterOrder(void)
{
    return (ulong)GIF_AD | ((ulong)GIF_ST<<4) | ((ulong)GIF_RGBAQ<<8)
         | ((ulong)GIF_XYZF2<<12) | ((ulong)GIF_ST<<16)
         | ((ulong)GIF_XYZF2<<20) | ((ulong)GIF_ST<<24)
         | ((ulong)GIF_XYZF2<<28) | ((ulong)GIF_ST<<32)
         | ((ulong)GIF_XYZF2<<36);
}

extern "C" void func_001493B0(void *destination)
{
    GIFS gifs;
    gifs.AllocStatic(4,static_cast<QW *>(destination));
    gifs.AddPrimPack(0,1,GIF_AD);
    gifs.PackAD(GS_TEST_1,ParticleTest(126,ALPHA_KEEP,DEPTH_GREATER));
    gifs.PackAD(GS_ALPHA_1,0x45);
    gifs.AddPrimBulk(4 | (1<<4) | (1<<6),0,10,ParticleRegisterOrder(),0);
    gifs.EndDmaCnt();
}

extern "C" void func_00149458(int blend,void *destination)
{
    GIFS gifs;
    gifs.AllocStatic(4,static_cast<QW *>(destination));
    gifs.AddPrimPack(0,1,GIF_AD);
    gifs.PackAD(GS_TEST_1,ParticleTest(128,ALPHA_FRAME_ONLY,DEPTH_GEQUAL));
    gifs.PackAD(GS_ALPHA_1,((long)blend<<2) | (1L<<6));
    gifs.AddPrimBulk(4 | (1<<4) | (1<<6),0,10,ParticleRegisterOrder(),0);
    gifs.EndDmaCnt();
}

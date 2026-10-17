// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Region { unsigned char prefix[0x2C]; float extentX; float extentY; unsigned char gap34[0x1C]; float scaleX; float scaleY; float sizeX; float sizeY; };
float func_00237D48(struct Region *region)
{
    float sum=0.0f;
    if(region->scaleX!=0.0f)
        sum=region->extentX/region->sizeX*0.5f;
    else
        sum=0.5f;
    if(region->scaleY!=0.0f)
        sum+=region->extentY/region->sizeY*0.5f;
    else
        sum+=0.5f;
    return sum;
}

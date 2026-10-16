// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct PointPosition {
    float x,y,z;
    unsigned int opaqueFourthWord;
} __attribute__((aligned(16)));

struct PathPoint {
    float parameter;
    unsigned int unaccessed04[3];
    struct PointPosition position;
    int state;
    unsigned int unaccessed24[3];
};

struct PointOwner {
    char unaccessed[0x1A0];
    int count;
    char unaccessed1A4[12];
    struct PathPoint points[10];
    int cursor,counter;
    char unaccessed398[8];
    struct PointPosition base;
};

void CopyAb(void *destination,void *source,unsigned int bytes);
void func_0020A6D0(void *owner,int mode);

static inline void SetPointXYZ(struct PointPosition *position,float x,float y,float z)
{
    position->x=x;
    position->y=y;
    position->z=z;
}

void func_0020A758(struct PointOwner *owner,int mode,int count,void *points)
{
    owner->count=count;
    if(count) {
        float first,scale;
        int index;

        CopyAb(owner->points,points,count*sizeof(struct PathPoint));
        first=owner->points[0].parameter;
        scale=440.0f/(owner->points[owner->count-1].parameter-first);
        SetPointXYZ(&owner->base,100.0f,456.0f,0.0f);
        for(index=0;index<owner->count;++index) {
            struct PathPoint *point=&owner->points[index];
            point->position=owner->base;
            point->state=0;
            point->position.x+=scale*(point->parameter-first);
        }
        SetPointXYZ(&owner->base,10.0f,456.0f,0.0f);
        owner->cursor=0;
        owner->counter=0;
    }
    func_0020A6D0(owner,mode);
}

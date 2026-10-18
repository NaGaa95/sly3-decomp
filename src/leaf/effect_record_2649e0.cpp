// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct Quad { int words[4]; } __attribute__((aligned(16)));
struct Transform { Quad first,second,third; };
struct Style { char prefix[0x8C]; float first,second; };
struct Definition {
    char prefix[0x94]; int identifier;
    char gap98[0x20]; Style *style;
};
struct Effect {
    char prefix[8]; Definition *definition;
    char gapC[8]; int color;
    float step,start,end;
    int first,second,record;
};
struct ScriptRecord { char data[0x30]; };
struct Script { char prefix[0x44]; ScriptRecord *records; };
struct Game { char prefix[0x4334]; Script *script; };
struct EffectRecord {
    const unsigned short *key,*textCursor;
    ScriptRecord *begin,*cursor,*end;
    int packed,currentColor;
    char gap1C[0x24]; Quad first,second;
    char gap60[4]; float styleFirst,styleSecond;
    int firstState,secondState;
    float start,finish,firstScale,secondScale,step,scaledStep;
    char gap8C[0x198-0x8C]; int secondId,firstId,definitionId;
};
extern "C" {
extern Game D_00475480;
void func_00265000(EffectRecord *);
void func_00264B18(EffectRecord *,const unsigned short *);
EffectRecord *func_002649E0(EffectRecord *self,const unsigned short *key,Effect *effect,
                          Transform transform,int useStart)
{
    self->key=key;
    self->firstState=0;
    self->secondState=0;
    self->start=useStart?effect->start:0.0f;
    self->finish=effect->end;
    self->firstScale=1.0f;
    self->secondScale=1.0f;
    self->firstId=effect->first;
    self->secondId=effect->second;
    self->styleFirst=effect->definition->style->first;
    self->styleSecond=effect->definition->style->second;
    self->definitionId=effect->definition->identifier;
    self->step=effect->step;
    self->scaledStep=self->step*0.01953125f;
    self->begin=self->cursor=D_00475480.script->records+effect->record;
    self->end=D_00475480.script->records+1;
    self->currentColor=effect->color;
    self->first=transform.second;
    self->second=transform.third;
    func_00265000(self);
    func_00264B18(self,0);
    return self;
}
}
typedef char QuadSize[(sizeof(Quad)==16)?1:-1];
typedef char TransformSize[(sizeof(Transform)==48)?1:-1];
typedef char ScriptRecordSize[(sizeof(ScriptRecord)==48)?1:-1];

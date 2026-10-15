// Initialize the concrete actor cache, tasks, record arrays and shuffled identifiers.
// SLY3_CFLAGS: -Os -G0
#include "actor_task_api.h"
#include "actor_record_array_api.h"
#include "activation_selector_api.h"
typedef int qword __attribute__((mode(TI)));
#define FIELD(T,offset) (*(T *)((char *)actor+(offset)))
#define ADDRESS(offset) ((char *)actor+(offset))
struct ACTOR_FIELD { int flags,identifier,offset; };
struct SHUFFLED_IDENTIFIERS;
void func_00152488(void *actor);
void func_001C8970(void *actor,int fieldCount,const struct ACTOR_FIELD *descriptions,void *parent);
void *func_0023DDA0(void *actor,int identifier,int kind);
void func_00258958(void *record);
void func_001C1410(void *actor,void *record,void **output);
// Shared record-array helper writes a real produced object pointer.
// Shared task wrapper has actual owner/channel pointers and scalar mode.
void func_0028EDC8(void *actor,void *channel,void *task);
void func_00155190(void *actor,int message);
void func_001ACD28(void *actor);
// The shared array helper consumes byte stride, count and optional scalar arrays.
void func_002086B0(void *record,void *actor,void *optional);
void func_001C9118(void *actor,int state);
void *func_001D27F0(unsigned int bytes);
struct SHUFFLED_IDENTIFIERS *func_002BC1C8(void *storage,int count,const int *identifiers,void *heap);
extern const struct ACTOR_FIELD D_00345638[];
extern qword D_00317560;
extern char D_0036B118[];

void func_001AA2B0(void *actor) {
    void *task;
    func_00152488(actor);
    func_001C8970(actor,0xB,D_00345638,0);
    FIELD(void *,0x1190)=func_0023DDA0(actor,0x159,1);
    FIELD(void *,0x1AE8)=func_0023DDA0(actor,0x30,6);
    FIELD(void *,0x1AE4)=func_0023DDA0(actor,0x31,6);
    FIELD(void *,0x1AE0)=func_0023DDA0(actor,0x2B,1);
    FIELD(void *,0x1ADC)=func_0023DDA0(actor,0x2A,1);
    FIELD(void *,0x1AD8)=func_0023DDA0(actor,0x34,6);
    FIELD(void *,0x1AD4)=func_0023DDA0(actor,0x35,6);
    FIELD(void *,0x1AD0)=func_0023DDA0(actor,0x25,1);
    FIELD(void *,0x1ACC)=func_0023DDA0(actor,0x24,1);
    FIELD(void *,0x1AC8)=func_0023DDA0(actor,0x24,6);
    func_00258958(ADDRESS(0x1470));
    func_00258958(ADDRESS(0x1C90));
    func_001C1410(actor,ADDRESS(0x1B20),(void **)ADDRESS(0x1C20));
    func_001B0C70(actor,ADDRESS(0x1A70),(void **)ADDRESS(0x1A94));
    FIELD(void *,0x1AEC)=func_00130010(actor,FIELD(void *,0x1190),5);
    FIELD(void *,0x1AF0)=func_00130010(actor,FIELD(void *,0x1AD0),5);
    FIELD(void *,0x1AF4)=func_00130010(actor,FIELD(void *,0x1ACC),5);
    FIELD(void *,0x1AF8)=func_00130010(actor,FIELD(void *,0x1AE0),7);
    FIELD(void *,0x1AFC)=func_00130010(actor,FIELD(void *,0x1ADC),7);
    FIELD(void *,0x1B04)=func_00130010(FIELD(void *,0x1AA0),*(void **)((char *)FIELD(void *,0x1AA0)+0x48),5);
    FIELD(void *,0x1B00)=func_00130010(actor,FIELD(void *,0x1AC8),5);
    task=func_00130078(actor,FIELD(void *,0x1AC8),5,5,2,D_00317560);
    FIELD(void *,0x1B08)=task;
    func_0028EDC8(actor,FIELD(void *,0x1AC8),task);
    func_00155190(actor,0x2F);
    func_001ACD28(actor);
    func_001C1410(actor,ADDRESS(0x1520),(void **)ADDRESS(0x1620));
    func_00147E08(actor,0xC,4,ADDRESS(0x1E20),0,0,0,(void **)ADDRESS(0x1E50));
    func_00147E08(actor,0xC,3,ADDRESS(0x1EC4),0,0,0,(void **)ADDRESS(0x1EE8));
    //2086B0 actually dereferences this selectedactor pointer at record+34.
    FIELD(void *,0x1924)=FIELD(void *,0x1AA4);
    func_002086B0(ADDRESS(0x18F0),actor,0);
    func_001C9118(actor,1);
    if(FIELD(void *,0x1D44))
        FIELD(void *,0x1D48)=func_002399C8(FIELD(void *,0x1D44),FIELD(void *,0x1D40),-1,1);
    if(FIELD(void *,0x1F28))
        FIELD(void *,0x1F2C)=func_002399C8(FIELD(void *,0x1F28),actor,-1,1);
    {
        // Four real scalar identifiers copied by the shuffle-array constructor.
        int identifiers[4]={25,35,37,30};
        FIELD(struct SHUFFLED_IDENTIFIERS *,0x1450)=func_002BC1C8(func_001D27F0(20),4,identifiers,D_0036B118);
    }
}

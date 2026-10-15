// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Decode selector tables, retain the selected variant, and release the temporary archive heap.
// The two-argument lookup uses the native nontrivial C++ result ABI with hidden outputA0.
#include "common.h"
struct ArchiveLanguageSelection { int identity; int selector; };
struct ArchiveLookupKey { int unitCount; unsigned short *units; };
struct ArchivePredicateSelection { ArchiveLookupKey key; int identity; int selector; };
struct ArchivePredicateValue {
    short kind, header;
    union { int integer; float scalar; void *pointer; } value;
    ArchivePredicateValue(const ArchivePredicateValue &);
    ~ArchivePredicateValue();
};
extern "C" void func_0012BC20(ArchivePredicateValue *value);
inline ArchivePredicateValue::~ArchivePredicateValue() { func_0012BC20(this); }
struct ArchiveSelectionAllocation { int bytes; int alignment; };
struct ArchiveSelectionGame {
    byte beforeSelection[0x42CC];
    int selectionCount;
    int *selectionIds;
    int selectionCapacity;
};
struct ArchiveSelectionManager {
    byte beforeIdentity[0x1498];
    int firstIdentity;
    int betweenIdentities;
    int secondIdentity;
};
typedef char LanguageSelectionSize[(sizeof(ArchiveLanguageSelection)==8)?1:-1];
typedef char LookupKeySize[(sizeof(ArchiveLookupKey)==8)?1:-1];
typedef char PredicateSelectionSize[(sizeof(ArchivePredicateSelection)==16)?1:-1];
typedef char PredicateValueSize[(sizeof(ArchivePredicateValue)==8)?1:-1];
typedef char AllocationSize[(sizeof(ArchiveSelectionAllocation)==8)?1:-1];
extern "C" {
    extern ArchiveSelectionManager D_0036C700;
    extern byte D_00468D30[];
    extern byte D_0036BC10[];
    extern int D_0036BC20;
    extern int D_0036BD10;
    void *func_002BC528(void *heap);
    void func_002BC4D8(void *heap,int flags);
    void *func_00117D48(void *heap,int bytes,int allocationKind);
    unsigned int func_00118FF8(void *stream);
    unsigned int func_001190A8(void *stream);
    void func_00119968(void *stream,ArchiveLookupKey *key,void *heap);
    ArchivePredicateValue func_002BC010(ArchiveLookupKey *key,byte *buffer);
    void *func_001D2470(ArchiveSelectionAllocation *allocation);
    void func_00118DA0(void *stream,int bytes,void *destination);
    int func_001191E0(void *stream);
    void func_00118DF0(void *stream,int bytes);
    void func_001519C8(void *selection,void *stream);
    int func_00169150(void *selection,int identity);
    void func_001694D8(void *selection,int identity);
}
static inline ArchiveLanguageSelection *ArchiveLanguageRow(ArchiveLanguageSelection *base,int index) {
    return base+index;
}
static inline ArchivePredicateSelection *ArchivePredicateRow(ArchivePredicateSelection *base,int index) {
    return base+index;
}
static inline int ArchivePredicateInteger(ArchiveLookupKey *key) {
    return func_002BC010(key,D_00468D30).value.integer;
}
static inline void *ArchiveAllocateSelection(ArchiveSelectionAllocation *request,int bytes,int alignment) {
    request->bytes=bytes;
    request->alignment=alignment;
    return func_001D2470(request);
}
extern "C" {
    void func_001500F0(ArchiveSelectionGame *game,void *stream) {
        byte temporaryHeap[16];
        func_002BC528(temporaryHeap);
        int languageCount=func_00118FF8(stream);
        ArchiveLanguageSelection *languages=(ArchiveLanguageSelection *)func_00117D48(temporaryHeap,languageCount*sizeof(ArchiveLanguageSelection),0x37);
        if(languageCount>0) {
            ArchiveLanguageSelection *entry=languages;
            int remaining=languageCount;
            do {
                entry->identity=func_001190A8(stream);
                entry->selector=func_001190A8(stream);
                ++entry;
            } while(--remaining);
        }
        int predicateCount=func_00118FF8(stream);
        ArchivePredicateSelection *predicates=(ArchivePredicateSelection *)func_00117D48(temporaryHeap,predicateCount*sizeof(ArchivePredicateSelection),0x37);
        if(predicateCount>0) {
            ArchivePredicateSelection *entry=predicates;
            int remaining=predicateCount;
            do {
                func_00119968(stream,&entry->key,temporaryHeap);
                entry->identity=func_001190A8(stream);
                entry->selector=func_001190A8(stream);
                ++entry;
            } while(--remaining);
        }
        int selector=-1;
        if(D_0036C700.firstIdentity!=-1) {
            for(int i=0;i<languageCount;++i) {
                if(ArchiveLanguageRow(languages,i)->identity==D_0036C700.firstIdentity) {
                    selector=ArchiveLanguageRow(languages,i)->selector;
                    break;
                }
            }
        }
        if(selector==-1 && D_0036C700.secondIdentity!=-1) {
            for(int i=0;i<predicateCount;++i) {
                if(ArchivePredicateRow(predicates,i)->identity==D_0036C700.secondIdentity) {
                    selector=ArchivePredicateRow(predicates,i)->selector;
                    break;
                }
            }
        }
        if(selector==-1 && predicateCount>0) {
            ArchivePredicateSelection *entry=predicates;
            int remaining=predicateCount;
            do {
                int positive=ArchivePredicateInteger(&entry->key);
                if(positive>0) selector=entry->selector;
                ++entry;
            } while(--remaining);
        }
        if(selector==12) selector=-1;
        int variantCount=func_00118FF8(stream);
        int index=0;
        int chosenIndex=0;
        game->selectionCount=variantCount;
        {
            ArchiveSelectionAllocation allocation;
            game->selectionIds=(int *)ArchiveAllocateSelection(&allocation,variantCount*sizeof(int),16);
        }
        func_00118DA0(stream,game->selectionCount*sizeof(int),game->selectionIds);
        game->selectionCapacity=game->selectionCount;
        for(;index<game->selectionCount;++index) {
            if(game->selectionIds[index]==selector) {
                chosenIndex=index;
                break;
            }
        }
        if(!game->selectionIds) D_0036BC20=selector;
        else D_0036BC20=game->selectionIds[chosenIndex];
        for(int i=0;i<game->selectionCount;++i) {
            int bytes=func_001191E0(stream);
            if(i==chosenIndex) func_001519C8(D_0036BC10,stream);
            else func_00118DF0(stream,bytes);
        }
        if(selector!=-1 && !func_00169150(D_0036BC10,selector)) func_001694D8(D_0036BC10,selector);
        D_0036BD10=chosenIndex==0;
        func_002BC4D8(temporaryHeap,2);
    }
}

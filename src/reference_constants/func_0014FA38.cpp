// Read both archive directories, select the matching world mode and restore the temporary heap scope.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "common.h"
extern "C" {
    typedef struct ArchiveDirectoryChoice {
        int identity;
        int mode;
        int worldCount;
        int *worlds;
    }
    ArchiveDirectoryChoice;
    typedef char ArchiveDirectoryChoiceSize[(sizeof(ArchiveDirectoryChoice)==16)?1:-1];
    typedef struct ArchiveGameInput {
        byte beforeWorld[0x441C];
        int world;
    }
    ArchiveGameInput;
    typedef struct ArchiveSelectionInput {
        byte beforeSelections[0x1498];
        int firstIdentity;
        int betweenSelections;
        int secondIdentity;
    }
    ArchiveSelectionInput;
    extern ArchiveSelectionInput D_0036C700;
    extern int D_0036DBA4;
    extern byte D_0036DBE0[];
    void *func_002BC528(void *temporaryHeap);
    void func_002BC4D8(void *temporaryHeap,int destructorFlags);
    void *func_00117D48(void *temporaryHeap,int bytes,int allocationKind);
    unsigned int func_00118FF8(void *stream);
    int func_001191E0(void *stream);
    int func_00119128(void *stream);
    void func_00118DA0(void *stream,int bytes,void *destination);
    void func_00196228(void *state,int mode);
    void func_0014FA38(ArchiveGameInput *game,void *stream) {
        /* Original SP+00..0F temporary heap storage precedes RA at SP+10. */ byte temporaryHeap[16];
        func_002BC528(temporaryHeap);
        int firstCount=func_00118FF8(stream);
        ArchiveDirectoryChoice *first=(ArchiveDirectoryChoice *)func_00117D48(temporaryHeap,firstCount*sizeof(ArchiveDirectoryChoice),0x37);
        if(firstCount>0) {
            ArchiveDirectoryChoice *entry=first;
            int remaining=firstCount;
            do {
                entry->identity=func_001191E0(stream);
                entry->mode=func_00119128(stream);
                entry->worldCount=func_00118FF8(stream);
                entry->worlds=(int *)func_00117D48(temporaryHeap,entry->worldCount*sizeof(int),0x37);
                func_00118DA0(stream,entry->worldCount*sizeof(int),entry->worlds);
                ++entry;
            }
            while(--remaining);
        }
        int secondCount=func_00118FF8(stream);
        ArchiveDirectoryChoice *second=(ArchiveDirectoryChoice *)func_00117D48(temporaryHeap,secondCount*sizeof(ArchiveDirectoryChoice),0x37);
        if(secondCount>0) {
            ArchiveDirectoryChoice *entry=second;
            int remaining=secondCount;
            do {
                entry->identity=func_001191E0(stream);
                entry->mode=func_00119128(stream);
                entry->worldCount=func_00118FF8(stream);
                entry->worlds=(int *)func_00117D48(temporaryHeap,entry->worldCount*sizeof(int),0x37);
                func_00118DA0(stream,entry->worldCount*sizeof(int),entry->worlds);
                ++entry;
            }
            while(--remaining);
        }
        int mode=-1;
        if(D_0036C700.firstIdentity!=-1) {
            if(firstCount>0) {
                ArchiveDirectoryChoice *entry=first;
                int remaining=firstCount;
                do {
                    int worldCount=entry->worldCount;
                    int index=0;
                    int relevant=worldCount==0;
                    while(index<worldCount) {
                        if(entry->worlds[index]==game->world) {
                            relevant=1;
                            break;
                        }
                        ++index;
                    }
                    if(relevant && entry->identity==D_0036C700.firstIdentity) mode=entry->mode;
                    --remaining;
                    ++entry;
                }
                while(remaining);
            }
        }
        if(mode==-1 && D_0036C700.secondIdentity!=-1) {
            if(secondCount>0) {
                ArchiveDirectoryChoice *entry=second;
                int remaining=secondCount;
                do {
                    int worldCount=entry->worldCount;
                    int index=0;
                    int relevant=worldCount==0;
                    while(index<worldCount) {
                        if(entry->worlds[index]==game->world) {
                            relevant=1;
                            break;
                        }
                        ++index;
                    }
                    if(relevant && entry->identity==D_0036C700.secondIdentity) mode=entry->mode;
                    --remaining;
                    ++entry;
                }
                while(remaining);
            }
        }
        if(mode!=2) {
            if(D_0036DBA4!=0) {
                if(D_0036DBA4==1) mode=1;
            }
            else mode=0;
        }
        func_00196228(D_0036DBE0,mode==-1 ? 0 : mode);
        func_002BC4D8(temporaryHeap,2);
    }
}

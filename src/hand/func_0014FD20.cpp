// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "../../src/P2/heap.h"
#include "../../src/P2/bis.h"

typedef struct ArchiveLocalizedText {
    int identity;
    unsigned short *text;
} ArchiveLocalizedText;
typedef char ArchiveLocalizedTextSize[(sizeof(ArchiveLocalizedText)==8)?1:-1];

typedef struct ArchiveLocalizedGame {
    byte beforeLocalizedText[0x4E54];
    int textCount;
    ArchiveLocalizedText *texts;
    unsigned short *finalText;
} ArchiveLocalizedGame;

extern "C" {
extern int D_0036B120;
extern CGlobalHeap g_heapSw;
extern byte D_00389AB0[];
void *func_001D2470(ALLOCREQ *request);
void func_00119868(CBinaryInputStream *stream,unsigned short **text,HEAP *heap,int allocationKind);
void func_00119910(CBinaryInputStream *stream);
void func_0025E7B0(void *records);

void func_0014FD20(ArchiveLocalizedGame *game,CBinaryInputStream *stream)
{
    int selectedLanguage=0;
    int languageCount=stream->U8Read();
    for(int index=0;index<languageCount;++index) {
        if(stream->U8Read()==D_0036B120)
            selectedLanguage=index;
    }
    game->textCount=stream->S16Read();
    ALLOCREQ request;
    request.cb=game->textCount*sizeof(ArchiveLocalizedText);
    request.cbAlign=16;
    game->texts=(ArchiveLocalizedText *)func_001D2470(&request);
    for(int index=0;index<game->textCount;++index) {
        ArchiveLocalizedText *text=game->texts+index;
        text->identity=stream->S16Read();
        for(int language=0;language<languageCount;++language) {
            if(language==selectedLanguage)
                func_00119868(stream,&text->text,&g_heapSw,0x38);
            else
                func_00119910(stream);
        }
    }
    for(int language=0;language<languageCount;++language) {
        if(language==selectedLanguage)
            func_00119868(stream,&game->finalText,&g_heapSw,0x38);
        else
            func_00119910(stream);
    }
    func_0025E7B0(D_00389AB0);
}
}

#ifndef SLY3_P2_GAME_TEXT_H
#define SLY3_P2_GAME_TEXT_H
// Game strings use16-bit code units. Formatting buffers and source literals
// remain8-bit strings; the conversion helpers map their bytes into game text.
extern "C" const unsigned short *func_00150630(void *game,int stringId);
extern "C" unsigned short *func_00271730(unsigned short *destination,const unsigned short *source);
extern "C" unsigned short *func_00271780(unsigned short *destination,const unsigned short *source);
extern "C" unsigned short *func_002717E0(unsigned short *destination,const char *source);
extern "C" unsigned short *func_00271828(unsigned short *destination,const char *source);
#endif

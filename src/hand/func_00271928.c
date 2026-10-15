// Return whether the original narrowed16-bit character is accepted by its character-class helper or is hyphen. Actual helper input and integer Boolean result are explicit.
// Reference algorithm: src/hand/func_00132B78.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
int func_002718D8(int character);
int func_00271928(int character){unsigned short value=character;return func_002718D8(value)||value==0x2D;}

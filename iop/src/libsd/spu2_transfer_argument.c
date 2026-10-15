typedef char pointer4[(sizeof(void*)==4)?1:-1];
struct TransferRecord { int core; void *argument; };
extern struct TransferRecord TransferRecords[2];
void *sceSdGetTransIntrHandlerArgument(int channel) { return TransferRecords[channel].argument; }

typedef char pointer4[(sizeof(void*)==4)?1:-1];
typedef int(*Callback)(int);
extern Callback Data;
void sio2_mtap_get_slot_max2_set(Callback callback){Data=callback;}

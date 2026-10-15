typedef char pointer4[(sizeof(void*)==4)?1:-1];
typedef void(*Callback)(void);
extern Callback Data;
void sio2_mtap_update_slots_set(Callback callback){Data=callback;}

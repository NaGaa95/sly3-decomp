// Search original12-byte records by unsigned16 identifier, returning the matching record or null. Record addresses use the EE32-bit base plus the genuine sizeof-scaled byte offset.
// SLY3_CFLAGS: -Os -G0
struct Record {unsigned short identifier,unknown;float value;int auxiliary;};
struct S {char prefix[0xC];int count;struct Record *entries;};
struct Record *func_00265D68(struct S *p,unsigned short identifier){int low=0,high=p->count-1;struct Record *entry;while(high>=low){int middle=(high+low)/2;int difference=identifier-(entry=(struct Record *)(middle*sizeof(struct Record)+(unsigned int)p->entries))->identifier;if(!difference)return entry;if(difference>0)low=middle+1;else high=middle-1;}return 0;}

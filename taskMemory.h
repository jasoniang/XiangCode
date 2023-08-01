#include"shareMemory.h"
#include"public.h"
struct privatedata
{
    string userInfo;
    string key;
    char id[12];
    int age;
    int scores;
};

class privateMemory:public sharyMomoryBase 
{
public:
    privateMemory(key_t key, int size);
    privateMemory(string pathname, int size);
    ~privateMemory();
    void shyWrite(privatedata* personData);
    privatedata shyRead(char* strclientId, char* key);
    
private:
    int m_nGlobalSize;
};



#include"public.h"
//创建共享内存的基类
class sharyMomoryBase
{
public:
    ~sharyMomoryBase();
    sharyMomoryBase(key_t key, int size);
    sharyMomoryBase(string pathname, int size);
    sharyMomoryBase(key_t key, int size, int flag);
    
    void* ShmAt();
    void Shmdel();
    void ReleaseShm();
    void getShmId(key_t keyId, size_t size, int flag);
    
private:
    int nShmFd;
    void * ptr;
};
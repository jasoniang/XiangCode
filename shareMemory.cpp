#include"shareMemory.h"
const char nRand = 'x';
sharyMomoryBase::~sharyMomoryBase()
{
    
}

sharyMomoryBase::sharyMomoryBase(string pathname, int size)
{
    key_t nKey = ftok(pathname.data(), nRand);
    printf("sharyMomoryBase running key:%d\n", nKey);
    getShmId(nKey, size, IPC_CREAT | 0664);
}

sharyMomoryBase::sharyMomoryBase(key_t key, int size, int flag)
{
    printf("sharyMomoryBase running 2\n");
    getShmId(key, size, flag);
}

sharyMomoryBase::sharyMomoryBase(key_t key, int size)
{
    printf("sharyMomoryBase running 3\n");
    getShmId(key, size, IPC_CREAT|0664);
}

void* sharyMomoryBase::ShmAt()
{
    ptr = shmat(nShmFd, NULL, 0);
    return ptr;
}
    
void sharyMomoryBase::Shmdel()
{
    int ret = shmdt(ptr);
    if (ret != 0)
    {
        printf("del shymerory failed\n");
    }
}
    
void sharyMomoryBase::ReleaseShm()
{
    int ret = shmctl(nShmFd, IPC_RMID, NULL);
    if (ret == 0)
    {
        printf("del sharymemory success\n");
    }
}

void  sharyMomoryBase::getShmId(key_t keyId, size_t size, int flag)
{
    nShmFd =  shmget(keyId, size, flag);
    printf("shmId: %d keyId: %d size: %d flag: %d\n", nShmFd, keyId, size, flag);
}
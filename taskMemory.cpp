#include "taskMemory.h"

privateMemory::~privateMemory()
{
    
}

privateMemory::privateMemory(key_t key, int size):sharyMomoryBase(key, size*sizeof(privatedata))
{
    m_nGlobalSize = size;
}

privateMemory::privateMemory(string pathname, int size):sharyMomoryBase(pathname, size*sizeof(privatedata))
{
    m_nGlobalSize = size;
}

void privateMemory::shyWrite(privatedata* personData)
{
    privatedata* data = static_cast<privatedata*>(ShmAt());
    if (data == NULL)
    {
        printf("shyWrite address is NULL\n");
        return;
    }
    
    int i = 0;
    privatedata* pNewAdr = NULL;
    for (i = 0; i < m_nGlobalSize; i++)
    {
        pNewAdr = data + i;
        if (strcmp(pNewAdr->key.c_str(), personData->key.c_str()) == 0 && strcmp(pNewAdr->id, personData->id) == 0)
        {
            memcpy(pNewAdr, personData, sizeof(privatedata));
            printf("shyWrite  success\n");
            return;
        }
    }
    
    privatedata pNullNode;
    for (i = 0; i < m_nGlobalSize; i++)
    {
        pNewAdr = data + i;
        if (memcmp(&pNullNode, pNewAdr, sizeof(privatedata)))
        {
            if (memcpy(pNewAdr, personData, sizeof(privatedata) == 0))
            {
                memcpy(pNewAdr, personData, sizeof(privatedata)); 
                printf("shyWrite  success\n");
                break;
            }
        }
        
    }
    
    if (i == m_nGlobalSize)
    {
        return;
    }
    
    ReleaseShm();
}

privatedata privateMemory::shyRead(char* strclientId, char* key)
{
    privatedata* data = static_cast<privatedata*>(ShmAt());
    if (data == NULL)
    {
        printf("shyWrite address is NULL\n");
    }
    
    privatedata* pNewAdr = NULL;
    privatedata retData;
    for (int i = 0; i < m_nGlobalSize; i++)
    {
        pNewAdr = data + i;
        printf("shyRead  age: %d Id:%s\n", pNewAdr->age, pNewAdr->id);
        if (strcmp(pNewAdr->id, strclientId) == 0 && strcmp(pNewAdr->key.c_str(), key) == 0)
        {
            retData = *pNewAdr;
        }
    }
    
    return retData;
}

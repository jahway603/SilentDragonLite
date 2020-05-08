#ifndef DATASTORE_H
#define DATASTORE_H

#include "SietchDataStore.h"
#include "ChatDataStore.h"

class DataStore
{
public:
    static SietchDataStore* getSietchDataStore()
    {
        return SietchDataStore::getInstance();
    }

    static ChatDataStore* getChatDataStore()
    {
        return ChatDataStore::getInstance();
    }
}

#endif
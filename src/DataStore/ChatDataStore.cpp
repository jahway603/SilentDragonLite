#include "ChatDataStore.h"

ChatDataStore* ChatDataStore::getInstance()
{
    if(!ChatDataStore::instanced)
    {
        ChatDataStore::instanced = true;
        ChatDataStore::instance = new ChatDataStore();
    }
                
    return ChatDataStore::instance;
}

void ChatDataStore::clear()
{
    this->data.clear();
}


void ChatDataStore::setData(QString key, ChatItem value)
{
    this->data[key] = value;
}

ChatItem ChatDataStore::getData(QString key)
{
    return this->data[key];
}

QString ChatDataStore::dump()
{
	return "";
}

std::map<QString, ChatItem> ChatDataStore::getAllRawChatItems()
{
    return this->data;
}


ChatDataStore* ChatDataStore::instance = nullptr;
bool ChatDataStore::instanced = false;
#ifndef DATASTORE_H
#define DATASTORE_H

using json = nlohmann::json;

class ChatDataStore
{
    private:
        static bool instanced;
        static ChatDataStore* instance;
        std::map<QString, ChatItem> data;
        ChatDataStore()
        {

        }

    public:
        static ChatDataStore<T>* getInstance()
        {
            if(!ChatDataStore<T>::instanced)
            {
                ChatDataStore<T>::instanced = true;
                ChatDataStore<T>::instance = new ChatDataStore();
            }
                
            return ChatDataStore<ChatItem>::instance;
        }

        void clear();
        void setData(QString key, ChatItem value);
        ChatItem getData(QString key);
        QString dump();

        ~ChatDataStore()
        {
            ChatDataStore<T>::instanced = false;
        }
};

void ChatDataStore::clear()
{
    this->data.clear();
}


void ChatDataStore:setData(QString key, ChatItem value)
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

ChatDataStore* ChatDataStore::instance = nullptr;
bool ChatDataStore::instanced = false;

#endif
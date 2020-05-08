#ifndef CHATDATASTORE_H
#define CHATDATASTORE_H

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
        static ChatDataStore* getInstance()
        {
            if(!ChatDataStore::instanced)
            {
                ChatDataStore::instanced = true;
                ChatDataStore::instance = new ChatDataStore();
            }
                
            return ChatDataStore::instance;
        }

        void clear();
        void setData(QString key, ChatItem value);
        ChatItem getData(QString key);
        QString dump();

        ~ChatDataStore()
        {
            ChatDataStore::instanced = false;
            ChatDataStore::instance = nullptr;
        }
};

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

ChatDataStore* ChatDataStore::instance = nullptr;
bool ChatDataStore::instanced = false;

#endif
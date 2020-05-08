#ifndef SietchDataStore_H
#define SietchDataStore_H

using json = nlohmann::json;

class SietchDataStore
{
    private:
        static bool instanced;
        static SietchDataStore* instance;
        std::map<QString, QString> data;
        SietchDataStore()
        {

        }

    public:
        static SietchDataStore* getInstance()
        {
            if(!SietchDataStore::instanced)
            {
                SietchDataStore::instanced = true;
                SietchDataStore::instance = new SietchDataStore();
            }
                
            return SietchDataStore::instance;
        }

        void clear();
        void setData(QString key, QString value);
        QString getData(QString key);
        QString dump();

        ~ChatDataStore()
        {
            ChatDataStore::instanced = false;
        }
};

void SietchDataStore::clear()
{
    this->data.clear();
}

void SietchDataStore::setData(QString key, QString value)
{
    this->data[key] = value;
}

QString SietchDataStore::getData(QString key)
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
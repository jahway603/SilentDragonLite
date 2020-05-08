#ifndef SIETCHDATASTORE_H
#define SIETCHDATASTORE_H

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

        ~SietchDataStore()
        {
            SietchDataStore::instanced = false;
            SietchDataStore::instance = nullptr;
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

QString SietchDataStore::dump()
{
    return "";
}

SietchDataStore* SietchDataStore::instance = nullptr;
bool SietchDataStore::instanced = false;

#endif
// Copyright 2019-2020 The Hush developers
// GPLv3

#include "ContactDataStore.h"
#include <string>

ContactDataStore* ContactDataStore::getInstance()
{
    if(!ContactDataStore::instanced)
    {
        ContactDataStore::instanced = true;
        ContactDataStore::instance = new ContactDataStore();
    }
                
    return ContactDataStore::instance;
}

void ContactDataStore::clear()
{
    this->data.clear();
}


void ContactDataStore::setData(QString key, ContactItem value)
{
    this->data[key] = value;
}

ContactItem ContactDataStore::getData(QString key)
{
    return this->data[key];
}

QString ContactDataStore::dump()
{
    json contacts;
    contacts["count"] = this->data.size();
    json j = {};
    for (auto &c: this->data)
    {
        qDebug() << c.second.toQTString();
        c.second.toJson();
        j.push_back(c.second.toJson());
    }
    contacts["contacts"] = j;

    std::string dump = contacts.dump(4);
    qDebug() << dump.c_str();
	return "";
}

ContactDataStore* ContactDataStore::instance = nullptr;
bool ContactDataStore::instanced = false;
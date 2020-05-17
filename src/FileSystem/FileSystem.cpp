#include "FileSystem.h"

#include <QString>
#include <QList>

FileSystem::FileSystem()
{
}

FileSystem* FileSystem::getInstance()
{
    if(!FileSystem::instanced)
    {
        FileSystem::instanced = true;
        FileSystem::instance = new FileSystem();
        FileEncryption::showConfig();
    }
                
    return FileSystem::instance;
}

QList<ContactItem> FileSystem::readContacts(QString file)
{
    QList<ContactItem> contacts;
    QFile _file(file);
    if (_file.exists()) 
    {
        contacts.clear();
        _file.open(QIODevice::ReadOnly);
        QDataStream in(&_file);    // read the data serialized from the file
        QString version;
        in >> version;
        qDebug() << "Read " << version << " Hush contacts from disk...";
        qDebug() << "Detected old addressbook format";
        QList<QList<QString>> stuff;
        in >> stuff;
        //qDebug() << "Stuff: " << stuff;
        for (int i=0; i < stuff.size(); i++) 
        {
            ContactItem contact = ContactItem(stuff[i][0],stuff[i][1], stuff[i][2], stuff[i][3],stuff[i][4]);
            contacts.push_back(contact);
        }
        
        _file.close();
    }
    else
    { 
        qDebug() << "No Hush contacts found on disk!";
    }

    return contacts;
}

void FileSystem::writeContacts(QString file, QList<ContactItem> contacts)
{
    QFile _file(file);
    _file.open(QIODevice::ReadWrite | QIODevice::Truncate);
    QDataStream out(&_file);   // we will serialize the data into the file
    QList<QList<QString>> _contacts;
    for(auto &item: contacts)
    {
        QList<QString> c;
        c.push_back(item.getName());
        c.push_back(item.getPartnerAddress());
        c.push_back(item.getMyAddress());
        c.push_back(item.getCid());
        c.push_back(item.getAvatar());
        _contacts.push_back(c);
    }
    out << QString("v1") << _contacts;
    _file.close();
}

FileSystem::~FileSystem()
{
    this->instance = nullptr;
    this->instanced = false;
    delete this->instance;
}

FileSystem *FileSystem::instance = nullptr;
bool FileSystem::instanced = false;
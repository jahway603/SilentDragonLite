#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QString>
#include <QList>
#include "../Model/ContactItem.h"
#include "../Crypto/FileEncryption.h"

class FileSystem
{
    private:
        static bool instanced;
        static FileSystem* instance;
        FileSystem();

    public:
        static FileSystem* getInstance();
        QList<ContactItem> readContacts(QString file);
        void writeContacts(QString file, QList<ContactItem> contacts);
        ~FileSystem();
        
};

#endif
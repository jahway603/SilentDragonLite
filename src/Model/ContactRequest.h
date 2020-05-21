// Copyright 2019-2020 The Hush developers
// GPLv3

#ifndef CONTACTREQUEST_H
#define CONTACTREQUEST_H

#include <QString>
using json = nlohmann::json;

class ContactRequest
{
    private:
        QString _senderAddress;
        QString _receiverAddress;
        QString _memo;
        QString _cid;

    public:
        ContactRequest();
        ContactRequest(QString sender, QString receiver, QString memo, QString cid);
        QString getSenderAddress();
        QString getReceiverAddress();
        QString getMemo();
        QString getCid();
        void setSenderAddress(QString address);
        void setReceiverAddress(QString contact);
        void setMemo(QString memo);
        void setCid(QString cid);
        QString toString();
        ~ContactRequest();
};

#endif
// Copyright 2019-2020 The Hush developers
// GPLv3

#ifndef CHATITEM_H
#define CHATITEM_H

#include <QString>
using json = nlohmann::json;

class ChatItem
{
    private:
        long _timestamp;
        QString _address;
        QString _contact;
        QString _memo;
        QString _requestZaddr;
        QString _type; 
        QString _cid;
        QString _txid;
        int _confirmations;
        bool _outgoing = false;

    public:
        ChatItem();
        ChatItem(long timestamp, QString address, QString contact, QString memo,QString requestZaddr, QString type, QString cid, QString txid, int confirmations);
        ChatItem(long timestamp, QString address, QString contact, QString memo, QString requestZaddr, QString type,  QString cid, QString txid, int confirmations, bool outgoing);
        long getTimestamp();
        QString getAddress();
        QString getContact();
        QString getMemo();
        QString getRequestZaddr();
        QString getType();
        QString getCid();
        QString getTxid();
        int getConfirmations();
        bool isOutgoing();
        void setTimestamp(long timestamp);
        void setAddress(QString address);
        void setContact(QString contact);
        void setMemo(QString memo);
        void setRequestZaddr(QString requestZaddr);
        void setType(QString type);
        void setCid(QString cid);
        void setTxid(QString txid);
        void setConfirmations(int confirmations);
        void toggleOutgo();
        QString toChatLine();
        json toJson();
        ~ChatItem();
};

#endif
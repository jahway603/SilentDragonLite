#ifndef CHATMODEL_H
#define CHATMODEL_H
#include <QString>
#include <map>
#include <vector>
#include <QListWidget>
#include "precompiled.h"
#include "mainwindow.h"
#include "controller.h"
#include "settings.h"
#include "camount.h"

class ChatItem
{
    private:
        long _timestamp;
        QString _address;
        QString _contact;
        QString _memo; 
        QString _cid;
        QString _txid;
        bool _outgoing = false;

    public:
        ChatItem() {}

        ChatItem(long timestamp, QString address, QString contact, QString memo, QString cid, QString txid)
        {
            _timestamp = timestamp;
            _address = address;
            _contact = contact;
            _memo = memo;
            _cid = cid;
            _txid = txid;
            _outgoing = false;

        }

        ChatItem(long timestamp, QString address, QString contact, QString memo, QString cid, QString txid, bool outgoing)
        {
            _timestamp = timestamp;
            _address = address;
            _contact = contact;
            _memo = memo;
            _cid = cid;
            _txid = txid;
            _outgoing = outgoing;

        }

        long getTimestamp()
        {
            return _timestamp;
        }

        QString getAddress()
        {
            return _address;
        }

        QString getContact()
        {
            return _contact;
        }

        QString getMemo()
        {
            return _memo;
        }

        QString getCid()
        {
            return _cid;
        }

         QString getTxid()
        {
            return _txid;
        }

        bool isOutgoing()
        {
            return _outgoing;
        }

        void setTimestamp(long timestamp)
        {
            _timestamp = timestamp;
        }

        void setAddress(QString address)
        {
            _address = address;
        }

        void setContact(QString contact)
        {
            _contact = contact;
        }

        void setMemo(QString memo)
        {
            _memo = memo;
        }

        void setCid(QString cid)
        {
            _cid = cid;
        }
         void setTxid(QString txid)
        {
            _txid = txid;
        }

        void toggleOutgo()
        {
            _outgoing = true;
        }

        ~ChatItem()
        {
            /*delete timestamp;
            delete address;
            delete contact;
            delete memo;
            delete outgoing;*/
        }
};

class ChatModel
{
    private:
        std::map<long, ChatItem> chatItems; 
        QTableView* parent;
        Ui::MainWindow*             ui;
        MainWindow*                 main;

    public:
        ChatModel() {};
        ChatModel(std::map<long, ChatItem> chatItems);
        ChatModel(std::vector<ChatItem> chatItems);
        std::map<long, ChatItem> getItems();
        void setItems(std::map<long, ChatItem> items);
        QString zaddr();
        void setItems(std::vector<ChatItem> items);
        void renderChatBox(Ui::MainWindow* ui, QListWidget &view);
        void renderChatBox(Ui::MainWindow* ui, QListWidget *view);
        void showMessages();
        void clear();
        void addMessage(ChatItem item);
        void addMessage(long timestamp, ChatItem item);
};

#endif
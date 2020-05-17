// Copyright 2019-2020 The Hush developers
// GPLv3

#include "Chat.h"
#include "../addressbook.h"
#include "../DataStore/DataStore.h"
Chat::Chat() {}

void Chat::renderChatBox(Ui::MainWindow *ui, QListView *view)
{
    QStandardItemModel *chat = new QStandardItemModel();
    //    ui->lcdNumber->setStyleSheet("background-color: red");
    //    ui->lcdNumber->setPalette(Qt::red);
    //    ui->lcdNumber->display("1");
    DataStore::getChatDataStore()->dump(); // test to see if the chat items in datastore are correctly dumped to json
    for (auto &p : AddressBook::getInstance()->getAllAddressLabels())
    {
        for (auto &c : DataStore::getChatDataStore()->getAllMemos())
        {
            //////Render only Memos for selected contacts. Do not render empty Memos //// Render only memos where cid=cid

            if (
                (p.getName() == ui->contactNameMemo->text().trimmed()) &&
                (p.getPartnerAddress() == c.second.getAddress()) &&
                (c.second.isOutgoing() == true))
            {

                QStandardItem *Items = new QStandardItem(c.second.toChatLine());

                Items->setData(OUTGOING, Qt::UserRole + 1);
                chat->appendRow(Items);
                ui->listChat->setModel(chat);      
       
            }
            else
            {
                ui->listChat->setModel(chat);
            }

            if (
                (p.getName() == ui->contactNameMemo->text().trimmed()) &&
                (p.getMyAddress() == c.second.getAddress()) &&
                (c.second.isOutgoing() == false))

            {
                QStandardItem *Items1 = new QStandardItem(c.second.toChatLine());
                Items1->setData(INCOMING, Qt::UserRole + 1);
                chat->appendRow(Items1);
                ui->listChat->setModel(chat);
            }
            else
            {

                ui->listChat->setModel(chat);
            }
        }
    }   
}
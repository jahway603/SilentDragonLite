// Copyright 2019-2020 The Hush developers
// GPLv3

#include "Chat.h"
#include "../addressbook.h"
#include "../DataStore/DataStore.h"
Chat::Chat() {}

ChatMemoEdit::ChatMemoEdit(QWidget* parent) : QTextEdit(parent) {
    QObject::connect(this, &QTextEdit::textChanged, this, &ChatMemoEdit::updateDisplay);
}

void ChatMemoEdit::updateDisplay() {
    QString txt = this->toPlainText();
    if (lenDisplayLabel)
        lenDisplayLabel->setText(QString::number(txt.toUtf8().size()) + "/" + QString::number(maxlen));

    if (txt.toUtf8().size() <= maxlen) {
        // Everything is fine
        if (sendChatButton)
            sendChatButton->setEnabled(true);

        if (lenDisplayLabel)
            lenDisplayLabel->setStyleSheet("");
    }
    else {
        // Overweight
        if (sendChatButton)
            sendChatButton->setEnabled(false);

        if (lenDisplayLabel)
            lenDisplayLabel->setStyleSheet("color: red;");
    }
}

void ChatMemoEdit::setMaxLen(int len) {
    this->maxlen = len;
    updateDisplay();
}

void ChatMemoEdit::SetSendChatButton(QPushButton* button) {
    this->sendChatButton = button;
}

void ChatMemoEdit::setLenDisplayLabel(QLabel* label) {
    this->lenDisplayLabel = label;
}

void Chat::renderChatBox(Ui::MainWindow *ui, QListView *view, QLabel *label)
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
#include "chatmodel.h"

ChatModel::ChatModel(std::map<long, ChatItem> chatItems)
{
    this->chatItems = chatItems;
}

ChatModel::ChatModel(std::vector<ChatItem> chatItems)
{
   this->setItems(chatItems);
}

std::map<long, ChatItem> ChatModel::getItems()
{
    return this->chatItems;
}

void ChatModel::setItems(std::map<long, ChatItem> items)
{
    this->chatItems = chatItems;
}

void ChatModel::setItems(std::vector<ChatItem> items)
{
    for(ChatItem c : items)
    {
        this->chatItems[c.getTimestamp()] = c;
    }
}

void ChatModel::clear()
{
    this->chatItems.clear();
}

void ChatModel::addMessage(ChatItem item)
{
    this->chatItems[item.getTimestamp()] = item;
}

void ChatModel::addMessage(long timestamp, ChatItem item)
{
    this->chatItems[timestamp] = item;
}

void ChatModel::showMessages()
{
    for(auto &c : this->chatItems)
    {
        qDebug() << "[" << c.second.getTimestamp() << "] " << "<" << c.second.getAddress() << "> :" << c.second.getMemo(); 
    }
}

void ChatModel::renderChatBox(QListWidget &view)
{
    /*for(auto &c : this->chatItems)
    {
        //view.getItems().add(QString("[Timestamp] <Contactname|Me>: lorem ipsum ...."));
    }*/
    qDebug() << "not implemented yet";
    //todo render items to view
}

void ChatModel::renderChatBox(QListWidget *view)
{
    qDebug() << "called ChatModel::renderChatBox(QListWidget *view)";
    QString line = "";
    while(view->count() > 0)
    {
        view->takeItem(0);
    }

    for(auto &c : this->chatItems)
    {
        QDateTime myDateTime;
 
        myDateTime.setTime_t(c.second.getTimestamp());
        qDebug() << "[" << myDateTime.toString("dd.MM.yyyy hh:mm:ss ") << "] " << "<" << c.second.getAddress() << "> :" << c.second.getMemo(); 
        line += QString("[") + myDateTime.toString("dd.MM.yyyy hh:mm:ss ") +  QString("] ");
        line += QString("<") + QString(c.second.getAddress()) + QString("> :");
        line += QString(c.second.getMemo());
        view->addItem(line);
        line ="";
    }
}
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

void ChatModel::renderChatBox(QListView &view)
{
    /*for(auto &c : this->chatItems)
    {
        //view.getItems().add(QString("[Timestamp] <Contactname|Me>: lorem ipsum ...."));
    }*/
    qDebug() << "not implemented yet";
    //todo render items to view
}

void ChatModel::renderChatBox(QListView *view)
{
    /*for(auto &c : this->chatItems)
    {
        //view->getItems().add(QString("[Timestamp] <Contactname|Me>: lorem ipsum ...."));
    }*/
    qDebug() << "not implemented yet blyat";
    //todo render items to view
}
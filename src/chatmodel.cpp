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

void ChatModel::renderChatBox(QListView &view)
{
    for(ChatItem c : items)
    {
        view.getItems().add(QString("[Timestamp] <Contactname|Me>: lorem ipsum ...."));
    }
    
    //todo render items to view
}

void ChatModel::renderChatBox(QListView *view)
{
    for(ChatItem c : items)
    {
        view->getItems().add(QString("[Timestamp] <Contactname|Me>: lorem ipsum ...."));
    }
    
    //todo render items to view
}
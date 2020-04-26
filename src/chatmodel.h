#include <QString>
#include <map>
#include <vector>
#include <QListView>

class ChatItem
{
    private:
        long timestamp;
        QString address;
        QString contact;
        QString memo; 
        bool outgoing = false;

    public:
        ChatItem() {}
        ChatItem(long timestamp, QString address, QString contact, QString memo);
        ChatItem(long timestamp, QString address, QString contact, QString memo, bool outgoing = false);

        long getTimestamp()
        {
            return this->timestamp;
        }

        QString getAddress()
        {
            return this->address;
        }

        QString getContact()
        {
            return this->contact;
        }

        QString getMemo()
        {
            return this->memo;
        }

        bool isOutgoing()
        {
            return this->outgoing;
        }

        void setTimestamp(long timestamp)
        {
            this->timestamp = timestamp;
        }

        void setAddress(QString address)
        {
            this->address = address;
        }

        void setContact(QString contact)
        {
            this->contact = contact;
        }

        void setMemo(QString memo)
        {
            this->memo = memo;
        }

        void toggleOutgo()
        {
            this->outgoing = true;
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

    public:
        ChatModel() {};
        ChatModel(std::map<long, ChatItem> chatItems);
        ChatModel(std::vector<ChatItem> chatItems);
        std::map<long, ChatItem> getItems();
        void setItems(std::map<long, ChatItem> items);
        void setItems(std::vector<ChatItem> items);
        void renderChatBox(QListView &view);
        void renderChatBox(QListView *view);
        void showMessages();
        void clear();
        void addMessage(ChatItem item);
        void addMessage(long timestamp, ChatItem item);
};
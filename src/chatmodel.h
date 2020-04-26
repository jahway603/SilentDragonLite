#include <string>
#include <map>
#include <vector>
#include <QListView>

class ChatItem
{
    private:
        long timestamp;
        std::string address;
        std::string contact;
        std::string memo; 
        bool outgoing = false;

    public:
        ChatItem() {}
        ChatItem(long timestamp, std::string address, std::string contact, std::string memo);
        ChatItem(long timestamp, std::string address, std::string contact, std::string memo, bool outgoing = false);

        long getTimestamp()
        {
            return this->timestamp;
        }

        std::string getAddress()
        {
            return this->address;
        }

        std::string getContact()
        {
            return this->contact;
        }

        std::string getMemo()
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

        void setAddress(std::string address)
        {
            this->address = address;
        }

        void setContact(std::string contact)
        {
            this->contact = contact;
        }

        void setMemo(std::string memo)
        {
            this->memo = memo;
        }

        void toggleOutgo()
        {
            this->outgoing = true;
        }

        ~ChatItem()
        {
            delete timestamp;
            delete address;
            delete contact;
            delete memo;
            delete outgoing;
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
};
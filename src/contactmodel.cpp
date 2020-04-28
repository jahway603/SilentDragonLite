#include "contactmodel.h"
#include "addressbook.h"

void ContactModel::renderContactList(QListWidget* view)
{
    while(view->count() > 0)
    {
        view->takeItem(0);
    }
	for(auto &c : AddressBook::getInstance()->getAllAddressLabels())
    {
    	view->addItem(c.getName());
        
    }
}
#include "contactmodel.h"
#include "addressbook.h"

void ContactModel::renderContactList(QListWidget* view)
{
	for(auto &c : AddressBook::getInstance()->getAllAddressLabels())
    {
    	view->addItem(c.getName());
    }
}
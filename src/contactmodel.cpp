#include "contactmodel.h"

void ContactModel::renderContactList(QListWidget* view)
{
	for(auto &c : this->_contacts)
    {
    	view->addItem(c.getName());
    }
}
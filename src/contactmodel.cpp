#include "contactmodel.h"
#include "addressbook.h"
#include "mainwindow.h"

void ContactModel::renderContactList(QListView* view)
{    // QStandardItem(const QIcon & icon, const QString & text) 
     QStandardItemModel* contact = new QStandardItemModel();
    //}
	for(auto &c : AddressBook::getInstance()->getAllAddressLabels())
    {

        //QStandardItem* Items = new QStandardItem();
        QStandardItem* Items1 = new QStandardItem(QIcon("res/darkwing.png"),c.getName());
       // contact->appendRow(Items);
        contact->appendRow(Items1);
        view->setModel(contact);
        view->setIconSize(QSize(80,100));
        view->setUniformItemSizes(true);
        view->setDragDropMode(QAbstractItemView::DropOnly);;

        
        
    }
}
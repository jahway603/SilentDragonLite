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
         auto theme = Settings::getInstance()->get_theme_name();
    if ((theme == "dark" || theme == "midnight")) {
        QStandardItem* Items1 = new QStandardItem(QIcon("res/sdlogo.png"),c.getName());
             contact->appendRow(Items1);
        view->setModel(contact);
        view->setIconSize(QSize(80,100));
        view->setUniformItemSizes(true);
        view->setDragDropMode(QAbstractItemView::DropOnly);;
    }
    if (theme == "default" || theme == "blue"){

        QStandardItem* Items1 = new QStandardItem(QIcon("res/sdlogo2.png"),c.getName());
        contact->appendRow(Items1);
        view->setModel(contact);
        view->setIconSize(QSize(80,100));
        view->setUniformItemSizes(true);
        view->setDragDropMode(QAbstractItemView::DropOnly);;

    }

        
        
    }
}
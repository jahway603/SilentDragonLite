#include "contactmodel.h"
#include "addressbook.h"
#include "mainwindow.h"

void ContactModel::renderContactList(QListView* view)
{    
     QStandardItemModel* contact = new QStandardItemModel();
  
	for(auto &c : AddressBook::getInstance()->getAllAddressLabels())
    {

         auto theme = Settings::getInstance()->get_theme_name();
         if ((theme == "dark" || theme == "midnight")) {

        QString avatar = c.getAvatar();

             QStandardItem* Items1 = new QStandardItem(QIcon(avatar) ,c.getName());
             contact->appendRow(Items1); 
             view->setModel(contact);
             view->setIconSize(QSize(60,70));
             view->setUniformItemSizes(true);
             view->setDragDropMode(QAbstractItemView::DropOnly);      
             view->show();

    }
   

        
        
    }
}
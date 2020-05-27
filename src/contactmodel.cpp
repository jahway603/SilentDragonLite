// Copyright 2019-2020 The Hush developers
// GPLv3

#include "contactmodel.h"
#include "addressbook.h"
#include "mainwindow.h"
#include "chatmodel.h"
#include "requestdialog.h"
#include "ui_requestdialog.h"
#include "settings.h"
#include "controller.h"



void ContactModel::renderContactList(QListView* view)
{    
     QStandardItemModel* contact = new QStandardItemModel();
         
	for(auto &c : AddressBook::getInstance()->getAllAddressLabels())
    {


          QString avatar = c.getAvatar();

             QStandardItem* Items1 = new QStandardItem(c.getName());
             Items1->setData(QIcon(avatar),Qt::DecorationRole);
             
             contact->appendRow(Items1); 
             view->setModel(contact);
             view->setIconSize(QSize(60,70));
             view->setUniformItemSizes(true);
             view->setDragDropMode(QAbstractItemView::DropOnly);      
             view->show();
             
           
        
    }
}

void MainWindow::showRequesthush() {
 
    Ui_RequestDialog req;
    QDialog d(this);
    req.setupUi(&d);
        Settings::saveRestore(&d);

   // setupDialog(main, &d, &req);

    // Setup the Label completer for the Address
   
    
    d.exec();
   
}


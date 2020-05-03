#include "contactmodel.h"
#include "addressbook.h"
#include "mainwindow.h"

void ContactModel::renderContactList(QListView* view)
{
     QStandardItemModel* contact = new QStandardItemModel();
    //}
	for(auto &c : AddressBook::getInstance()->getAllAddressLabels())
    {
    //	view->addItem(c.getName()); 
   

        QStandardItem* Items = new QStandardItem(c.getName());
        contact->appendRow(Items);
     //   view->setItemDelegate({text: contact})
             // width: view->width })
               // height: avatar.implicitHeight,
             //   leftPadding: avatar.implicitWidth + 32})

               //  Image {
                 //   id: avatar
                   // source: "qrc:/" + modelData.replace(" ", "_") + ".png"
               // }
            //}
        view->setModel(contact);
        
        
    }
}
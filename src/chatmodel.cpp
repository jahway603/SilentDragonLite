// Copyright 2019-2020 The Hush developers
// GPLv3
#include "chatmodel.h"
#include "settings.h"
#include "ui_confirm.h"
#include "controller.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addressbook.h"
#include "ui_memodialog.h"
#include "ui_contactrequest.h"
#include "addressbook.h"
#include <QUuid>
#include <bits/stdc++.h> 
#include <boost/algorithm/string.hpp> 
#include <QtWidgets>

using namespace std; 
using namespace boost;

ChatModel::ChatModel(std::map<QString, ChatItem> chatItems)
{
    this->chatItems = chatItems;
}

ChatModel::ChatModel(std::vector<ChatItem> chatItems)
{
   this->setItems(chatItems);
}

QString ChatModel::generateChatItemID(ChatItem item)
{
    QString key = QString::number(item.getTimestamp()) +  QString("-");
    key += QString(QCryptographicHash::hash(
        QString(
            QString::number(item.getTimestamp()) +  
            item.getAddress() + 
            item.getContact() + 
            item.getMemo()
        ).toUtf8()
        ,QCryptographicHash::Md5).toHex());
    return key;
}

std::map<QString, ChatItem> ChatModel::getItems()
{
    return this->chatItems;
}

void ChatModel::setItems(std::map<QString, ChatItem> items)
{
    this->chatItems = chatItems;
}

void ChatModel::setItems(std::vector<ChatItem> items)
{
    for(ChatItem c : items)
    {
        this->chatItems[this->generateChatItemID(c)] = c;
        
    }
}

void ChatModel::clear()
{
    this->chatItems.clear();
}

void ChatModel::addMessage(ChatItem item)
{
    QString key = this->generateChatItemID(item);
  //  qDebug() << "inserting chatitem with id: " << key;
    this->chatItems[key] = item;
}

void ChatModel::addMessage(QString timestamp, ChatItem item)
{
    QString key = this->generateChatItemID(item);
    timestamp = "0";
    this->chatItems[key] = item;
}

void ChatModel::showMessages()
{
    for(auto &c : this->chatItems)
    {
        qDebug() << c.second.toChatLine();
    }
}

void ChatModel::renderChatBox(Ui::MainWindow* ui, QListView &view)
{
    /*for(auto &c : this->chatItems)
    {
        //view.getItems().add(QString("[Timestamp] <Contactname|Me>: lorem ipsum ...."));
    }*/
    qDebug() << "not implemented yet";
    //todo render items to view
}

void ChatModel::renderChatBox(Ui::MainWindow* ui, QListView *view)
{
        

        QStandardItemModel* chat = new QStandardItemModel();
         
    
        for (auto &c : this->chatItems)
        for (auto &p : AddressBook::getInstance()->getAllAddressLabels())
    {
       

   
        //////Render only Memos for selected contacts. Do not render empty Memos //// Render only memos where cid=cid

        if (
            (ui->contactNameMemo->text().trimmed() == c.second.getContact()) && 
            (c.second.getMemo().startsWith("{") == false) &&  
            (c.second.getMemo().isEmpty() == false) && 
            (p.getPartnerAddress() == c.second.getAddress())
            
        ) 
        {       
            
            QStandardItem* Items = new QStandardItem(c.second.toChatLine());
            Items->setData("Outgoing", Qt::UserRole +1);
            chat->appendRow(Items);
         
             ui->listChat->setModel(chat);          
             ui->listChat->setItemDelegate(new ListViewDelegate());
             
            }
    

        if (
            (ui->contactNameMemo->text().trimmed() == c.second.getContact()) && 
            (c.second.getMemo().startsWith("{") == false) && 
            (c.second.getMemo().isEmpty() == false) &&
            (p.getMyAddress() == c.second.getAddress())

        )
        {

            QStandardItem* Items1 = new QStandardItem(c.second.toChatLine());
            Items1->setData("Incoming", Qt::UserRole +1);
            chat->appendRow(Items1);
        }

             ui->listChat->setModel(chat);
             ui->listChat->setItemDelegate(new ListViewDelegate());
            
    
    }
 
}


void ChatModel::addCid(QString tx, QString cid)
{
    this->cidMap[tx] = cid;
}

QString ChatModel::getCidByTx(QString tx)
{
    for(auto& pair : this->cidMap)
    {
     //   qDebug() << "TXID=" << pair.first << " CID=" << pair.second;
    }

    if(this->cidMap.count(tx) > 0)
    {
        return this->cidMap[tx];
    }

    return QString("0xdeadbeef");
}

void ChatModel::killCidCache()
{
    this->cidMap.clear();
}

QString MainWindow::createHeaderMemo(QString type, QString cid, QString zaddr,  int version=0, int headerNumber=1)
{
    
    QString header="";
    QJsonDocument j;
    QJsonObject h;
    // We use short keynames to use less space for metadata and so allow
    // the user to send more actual data in memos
    h["h"]   = headerNumber;    // header number
    h["v"]   = version;         // HushChat version
    h["z"]   = zaddr;           // zaddr to respond to
    h["cid"] = cid;             // conversation id
    h["t"] = type;       // Memo or incoming contact request

    j.setObject(h);
    header = j.toJson();
    qDebug() << "made header=" << header;
    return header;
}


// Create a Tx from the current state of the Chat page. 
Tx MainWindow::createTxFromChatPage() {
   Tx tx;
    CAmount totalAmt;
    // For each addr/amt in the Chat tab
  {
       
        QString amtStr = "0";
        CAmount amt;  

         
            amt = CAmount::fromDecimalString("0");
            totalAmt = totalAmt + amt;

  
    for(auto &c : AddressBook::getInstance()->getAllAddressLabels())

     if (ui->contactNameMemo->text().trimmed() == c.getName()) {
     
            QString cid = c.getCid();
            QString myAddr = c.getMyAddress();
            QString type = "Memo";
            QString addr = c.getPartnerAddress();
           
     
        QString hmemo= createHeaderMemo(type,cid,myAddr);
        QString memo = ui->memoTxtChat->toPlainText().trimmed();

        // ui->memoSizeChat->setLenDisplayLabel();// Todo -> activate lendisplay for chat
            
     tx.toAddrs.push_back(ToFields{addr, amt, hmemo}) ;

     tx.toAddrs.push_back(ToFields{addr, amt, memo});

         qDebug() << "pushback chattx";
   } }

    tx.fee = Settings::getMinerFee();

     return tx;

     qDebug() << "ChatTx created";
}

void MainWindow::sendChatButton() {



      ////////////////////////////Todo: Check if a Contact is selected//////////

    // Create a Tx from the values on the send tab. Note that this Tx object
    // might not be valid yet.

    // Memos can only be used with zAddrs. So check that first
   // for(auto &c : AddressBook::getInstance()->getAllAddressLabels())

      if (ui->contactNameMemo->text().trimmed().isEmpty() || ui->memoTxtChat->toPlainText().trimmed().isEmpty()) {
     
  // auto addr = "";
  //  if (! Settings::isZAddress(AddressBook::addressFromAddressLabel(addr->text()))) {
        QMessageBox msg(QMessageBox::Critical, tr("You have to select a contact and insert a Memo"),
        tr("You have selected no Contact from Contactlist,\n")  + tr("\nor your Memo is empty"),
        QMessageBox::Ok, this);

        msg.exec();
        return;
    }

    Tx tx = createTxFromChatPage();

    QString error = doSendChatTxValidations(tx);

    if (!error.isEmpty()) {
        // Something went wrong, so show an error and exit
        QMessageBox msg(QMessageBox::Critical, tr("Message Error"), error,
                        QMessageBox::Ok, this);

        msg.exec();

        // abort the Tx
        return;
        qDebug() << "Tx aborted";
    }

        // Create a new Dialog to show that we are computing/sending the Tx
        auto d = new QDialog(this);
        auto connD = new Ui_ConnectionDialog();
        connD->setupUi(d);
        QMovie *movie1 = new QMovie(":/img/res/silentdragonlite-animated.gif");;
        QMovie *movie2 = new QMovie(":/img/res/silentdragonlite-animated-dark.gif");;
        auto theme = Settings::getInstance()->get_theme_name();
        if (theme == "dark" || theme == "midnight") {
            movie2->setScaledSize(QSize(512,512));
            connD->topIcon->setMovie(movie2);
            movie2->start();
        } else {
            movie1->setScaledSize(QSize(512,512));
            connD->topIcon->setMovie(movie1);
            movie1->start();
        }

        connD->status->setText(tr("Please wait..."));
        connD->statusDetail->setText(tr("Your Message will be send"));

        d->show();
        ui->memoTxtChat->clear();

        // And send the Tx
        rpc->executeTransaction(tx, 
            [=] (QString txid) { 
                ui->statusBar->showMessage(Settings::txidStatusMessage + " " + txid);

                connD->status->setText(tr("Done!"));
                connD->statusDetail->setText(txid);

                QTimer::singleShot(1000, [=]() {
                    d->accept();
                    d->close();
                    delete connD;
                    delete d;
                    
                  });
                
                // Force a UI update so we get the unconfirmed Tx
              //  rpc->refresh(true);
                ui->memoTxtChat->clear();

            },
            // Errored out
            [=] (QString opid, QString errStr) {
                ui->statusBar->showMessage(QObject::tr(" Tx ") % opid % QObject::tr(" failed"), 15 * 1000);
                
                d->accept();
                d->close();
                delete connD;
                delete d;

                if (!opid.isEmpty())
                    errStr = QObject::tr("The transaction with id ") % opid % QObject::tr(" failed. The error was") + ":\n\n" + errStr;            

                QMessageBox::critical(this, QObject::tr("Transaction Error"), errStr, QMessageBox::Ok);            
            }
        );
    }        


QString MainWindow::doSendChatTxValidations(Tx tx) {
    // Check to see if we have enough verified funds to send the Tx.

    CAmount total;
    for (auto toAddr : tx.toAddrs) {
        if (!Settings::isValidAddress(toAddr.addr)) {
            QString addr = (toAddr.addr.length() > 100 ? toAddr.addr.left(100) + "..." : toAddr.addr);
            return QString(tr("Recipient Address ")) % addr % tr(" is Invalid");
        }

        // This technically shouldn't be possible, but issue #62 seems to have discovered a bug
        // somewhere, so just add a check to make sure. 
        if (toAddr.amount.toqint64() < 0) {
            return QString(tr("Amount for address '%1' is invalid!").arg(toAddr.addr));
        }

        total = total + toAddr.amount;
    }
    total = total + tx.fee;

    auto available = rpc->getModel()->getAvailableBalance();

    if (available < total) {
        return tr("Not enough available funds to send this transaction\n\nHave: %1\nNeed: %2\n\nNote: Funds need 5 confirmations before they can be spent")
            .arg(available.toDecimalhushString(), total.toDecimalhushString());
    }

    return "";
}


// Create a Tx from the current state of the Chat page. 
Tx MainWindow::createTxForSafeContactRequest() {

 Ui_Dialog request;
    QDialog dialog(this);
    request.setupUi(&dialog);
    Settings::saveRestore(&dialog);
dialog.exec();

    Tx tx; 
    
    QObject::connect(request.cancel, &QPushButton::clicked, [&] () {

        dialog.close();
    });


    QObject::connect(request.sendRequestButton, &QPushButton::clicked, this, &MainWindow::ContactRequest);
    // For each addr/amt in the Chat tab
  {
       CAmount totalAmt;
        QString amtStr = "0";
        CAmount amt;  

         
            amt = CAmount::fromDecimalString("0");
            totalAmt = totalAmt + amt;

  
    for(auto &c : AddressBook::getInstance()->getAllAddressLabels())
     if (request.zaddr->text().trimmed() != c.getPartnerAddress()) {

          
            QString cid = c.getCid();
            QString myAddr = c.getMyAddress();
            QString type = "cont";
            QString addr = request.zaddr->text();

           
     
            QString hmemo= createHeaderMemo(type,cid,myAddr,0,0);
            QString memo = request.requestmemo->toPlainText().trimmed();

            
            tx.toAddrs.push_back(ToFields{addr, amt, hmemo});
            tx.toAddrs.push_back(ToFields{addr, amt, memo});

                qDebug() << "pushback chattx";
            tx.fee = Settings::getMinerFee();

     return tx;

     qDebug() << "ChatTx created";
   } if (request.zaddr->text().trimmed().isEmpty() == false){

    QMessageBox msg(QMessageBox::Critical, tr("Please insert a contact Address"), request.zaddr->text(),
                        QMessageBox::Ok, this);

        msg.exec();

   }

  }

}
void MainWindow::ContactRequest() {



      ////////////////////////////Todo: Check if a Contact is selected//////////

    // Create a Tx from the values on the send tab. Note that this Tx object
    // might not be valid yet.

    // Memos can only be used with zAddrs. So check that first
   // for(auto &c : AddressBook::getInstance()->getAllAddressLabels())

    //  if (ui->contactNameMemo->text().trimmed().isEmpty() || ui->memoTxtChat->toPlainText().trimmed().isEmpty()) {
     
  // auto addr = "";
  //  if (! Settings::isZAddress(AddressBook::addressFromAddressLabel(addr->text()))) {
     //   QMessageBox msg(QMessageBox::Critical, tr("You have to select a contact and insert a Memo"),
     //   tr("You have selected no Contact from Contactlist,\n")  + tr("\nor your Memo is empty"),
     //   QMessageBox::Ok, this);

    //    msg.exec();
    //    return;
  //  }

      
//};

  Tx tx = createTxForSafeContactRequest();

    QString error = doSendChatTxValidations(tx);

    if (!error.isEmpty()) {
        // Something went wrong, so show an error and exit
        QMessageBox msg(QMessageBox::Critical, tr("Message Error"), error,
                        QMessageBox::Ok, this);

        msg.exec();

        // abort the Tx
        return;
        qDebug() << "Tx aborted";
    }

        // Create a new Dialog to show that we are computing/sending the Tx
        auto d = new QDialog(this);
        auto connD = new Ui_ConnectionDialog();
        connD->setupUi(d);
        QMovie *movie1 = new QMovie(":/img/res/silentdragonlite-animated.gif");;
        QMovie *movie2 = new QMovie(":/img/res/silentdragonlite-animated-dark.gif");;
        auto theme = Settings::getInstance()->get_theme_name();
        if (theme == "dark" || theme == "midnight") {
            movie2->setScaledSize(QSize(512,512));
            connD->topIcon->setMovie(movie2);
            movie2->start();
        } else {
            movie1->setScaledSize(QSize(512,512));
            connD->topIcon->setMovie(movie1);
            movie1->start();
        }

        connD->status->setText(tr("Please wait..."));
        connD->statusDetail->setText(tr("Your Message will be send"));

        d->show();
        ui->memoTxtChat->clear();

        // And send the Tx
        rpc->executeTransaction(tx, 
            [=] (QString txid) { 
                ui->statusBar->showMessage(Settings::txidStatusMessage + " " + txid);

                connD->status->setText(tr("Done!"));
                connD->statusDetail->setText(txid);

                QTimer::singleShot(1000, [=]() {
                    d->accept();
                    d->close();
                    delete connD;
                    delete d;
                    
                  });
                
                // Force a UI update so we get the unconfirmed Tx
              //  rpc->refresh(true);
                ui->memoTxtChat->clear();

            },
            // Errored out
            [=] (QString opid, QString errStr) {
                ui->statusBar->showMessage(QObject::tr(" Tx ") % opid % QObject::tr(" failed"), 15 * 1000);
                
                d->accept();
                d->close();
                delete connD;
                delete d;

                if (!opid.isEmpty())
                    errStr = QObject::tr("The transaction with id ") % opid % QObject::tr(" failed. The error was") + ":\n\n" + errStr;            

                QMessageBox::critical(this, QObject::tr("Transaction Error"), errStr, QMessageBox::Ok);            
            }
        );
       
    }        


QString MainWindow::doSendRequestTxValidations(Tx tx) {
    // Check to see if we have enough verified funds to send the Tx.

    CAmount total;
    for (auto toAddr : tx.toAddrs) {
        if (!Settings::isValidAddress(toAddr.addr)) {
            QString addr = (toAddr.addr.length() > 100 ? toAddr.addr.left(100) + "..." : toAddr.addr);
            return QString(tr("Recipient Address ")) % addr % tr(" is Invalid");
        }

        // This technically shouldn't be possible, but issue #62 seems to have discovered a bug
        // somewhere, so just add a check to make sure. 
        if (toAddr.amount.toqint64() < 0) {
            return QString(tr("Amount for address '%1' is invalid!").arg(toAddr.addr));
        }

        total = total + toAddr.amount;
    }
    total = total + tx.fee;

    auto available = rpc->getModel()->getAvailableBalance();

    if (available < total) {
        return tr("Not enough available funds to send this transaction\n\nHave: %1\nNeed: %2\n\nNote: Funds need 5 confirmations before they can be spent")
            .arg(available.toDecimalhushString(), total.toDecimalhushString());
    }

    return "";
}
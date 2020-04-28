#ifndef CONTACTMODEL_H
#define CONTACTMODEL_H

#include <vector>
#include <QString>
#include <QListWidget>

class ContactItem
{
	private:
		QString _myAddress;
		QString _partnerAddress;
		QString _name;

	public:
		ContactItem();
		ContactItem(QString myAddress, QString partnerAddress, QString name)
		{
			_myAddress = myAddress;
			_partnerAddress = partnerAddress;
			_name = name;
		}

		QString getName() const
		{
			return _name;
		}

		QString getMyAddress() const
		{
			return _myAddress;
		}

		QString getPartnerAddress() const
		{
			return _partnerAddress;
		}

		void setName(QString name)
		{
			_name = name;
		}

		void setMyAddress(QString myAddress)
		{
			_myAddress = myAddress;
		}

		void setPartnerAddress(QString partnerAddress)
		{
			_partnerAddress = partnerAddress;
		}

		QString toQTString()
		{
			return _name +  "|" +  _partnerAddress + "|" + _myAddress;
		}

};

class ContactModel
{
	public:
		ContactModel() {}
		void renderContactList(QListWidget* view);
};

#endif
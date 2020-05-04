// Copyright 2019-2020 The Hush developers
// GPLv3
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
		QString _cid;
		QString _avatar;

	public:
		ContactItem();
		ContactItem(QString name, QString partnerAddress, QString myAddress, QString cid, QString avatar)
		{
			_name = name;
			_myAddress = myAddress;
			_partnerAddress = partnerAddress;
			_cid = cid;
			_avatar = avatar;
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

		QString getCid() const
		{
			return _cid;
		}

		QString getAvatar() const
		{
			return _avatar;
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

		void setcid(QString cid)
		{
			_cid = cid;
		}
		void setAvatar(QString avatar)
		{
			_avatar = avatar;
		}

		QString toQTString()
		{
			return _name +  "|" +  _partnerAddress + "|" + _myAddress + "|" + _cid + "|"+ _avatar;
		}

};

class ContactModel
{
	public:
		ContactModel() {}
		void renderContactList(QListView* view);
};

#endif
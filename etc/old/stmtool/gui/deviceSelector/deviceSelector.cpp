/*    
    stmtools - An ADE for practical Scanning Tunneling Microscopy
    Copyright (C) 2011 Jens Oliver John <jens.o.john@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "deviceSelector.h"

deviceSelector::deviceSelector(class deviceManager *devMgr, QWidget *parent)
    : QDialog(parent)
{
	ui.setupUi(this);
	this->devMgr = devMgr;
	this->populateDeviceList();
	this->init_SS();
}

deviceSelector::~deviceSelector()
{

}

void deviceSelector::slot_do_close() {
	disconnect(this,SIGNAL(signal_selected(devices::deviceID*)),0,0);
	this->close();
}

void deviceSelector::slot_do_select() {
	QList<QListWidgetItem*> selected_items = this->ui.listWidget->selectedItems();
	if (!selected_items.isEmpty()) {
		dsLWI *stub = dynamic_cast<dsLWI*>(selected_items.takeFirst());
		if (stub) {
			emit this->signal_selected(stub->getDeviceId());
		} else {
			QMessageBox::critical(this,
					this->windowTitle(),
					QString("Internal error: invalid device entry."));
		}
	} else {
		QMessageBox::information(this,
				this->windowTitle(),
				QString("No entry has been selected: no gain."));
	}
}

void deviceSelector::slot_do_viewProperties(QListWidgetItem* item) {
	if (item) {
		dsLWI *list_entry = dynamic_cast<dsLWI*>(item);
		if (list_entry) {
			devices::deviceID *stub = list_entry->getDeviceId();
			/*
			this->ui.lbl_dName->setText(*stub->devName);
			this->ui.pte_description->clear();
			this->ui.pte_description->insertPlainText(*stub->devDescription);
			this->ui.lbl_dAuthor->setText(*stub->devAuthor);
			this->ui.lbl_dVersion->setText(*stub->devVersion);
			if (stub->devType == devices::SDRIVER) {
				this->ui.lbl_dType->setText(QString("Pure Software"));
			} else {
				this->ui.lbl_dType->setText(QString("Hardware Driver"));
			}
			*/
			this->ui.lbl_dName->setText(stub->devName);
			this->ui.pte_description->clear();
			this->ui.pte_description->insertPlainText(stub->devDescription);
			this->ui.lbl_dAuthor->setText(stub->devAuthor);
			this->ui.lbl_dVersion->setText(stub->devVersion);
			if (stub->devType == devices::SDRIVER) {
				this->ui.lbl_dType->setText(QString("Pure Software"));
			} else {
				this->ui.lbl_dType->setText(QString("Hardware Driver"));
			}
		}
	}
}

void deviceSelector::init_SS() {
	connect(this->ui.listWidget,SIGNAL(itemActivated(QListWidgetItem*)),this,SLOT(slot_do_viewProperties(QListWidgetItem*)));
	connect(this->ui.btn_Cancel,SIGNAL(clicked()),this,SLOT(slot_do_close()));
	connect(this->ui.btn_Select,SIGNAL(clicked()),this,SLOT(slot_do_select()));
	connect(this,SIGNAL(signal_selected(devices::deviceID*)),this->devMgr,SLOT(slot_loadDevice(devices::deviceID*)));
}

void deviceSelector::populateDeviceList() {
	QList<devices::deviceID*> *device_list = this->devMgr->availableDevices();
	if (device_list) {
	QListIterator<devices::deviceID*> *iter = new QListIterator<devices::deviceID*>(*device_list);
	while (iter->hasNext()) {
		dsLWI *list_entry = new dsLWI(iter->next());
		this->ui.listWidget->addItem(list_entry);
	}
	}
}


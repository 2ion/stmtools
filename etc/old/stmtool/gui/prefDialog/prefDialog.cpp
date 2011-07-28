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

#include "prefDialog.h"

prefDialog::prefDialog(class settingsManager* setMgr, QWidget *parent)
    : QDialog(parent)
{
	ui.setupUi(this);
	this->setMgr = setMgr;
	this->connectGUI();
	this->setAttribute(Qt::WA_DeleteOnClose,true);
	this->loadSettings();
	this->installEditor();
}

prefDialog::~prefDialog()
{

}

QString prefDialog::browseForADirectory() {
	return QFileDialog::getExistingDirectory(this,QString("Select directory"),QString(this->setMgr->value(QString("app/cwd")).toString()));
}

void prefDialog::connectGUI() {
	connect(this->ui.brws_devicesPath,SIGNAL(clicked()),this,SLOT(slot_tbtn_devices()));
	connect(this->ui.brws_viewerspath,SIGNAL(clicked()),this,SLOT(slot_tbtn_viewers()));
	connect(this->ui.brws_logpath,SIGNAL(clicked()),this,SLOT(slot_tbtn_logs()));
	connect(this->ui.btn_Apply,SIGNAL(clicked()),this,SLOT(slot_apply()));
	connect(this->ui.btn_Cancel,SIGNAL(clicked()),this,SLOT(slot_cancel()));
}

void prefDialog::loadSettings() {
	this->ui.le_devices->setText(this->setMgr->value(QString("devices/path")).toString());
	this->ui.le_logs->setText(this->setMgr->value(QString("log/logpath")).toString());
	this->ui.le_settings->setText(this->setMgr->value(QString("settings/path")).toString());
	this->ui.le_viewers->setText(this->setMgr->value(QString("viewers/path")).toString());
}

void prefDialog::saveSettings() {
	this->setMgr->setValue(QString("devices/path"),QVariant(this->ui.le_devices->text()));
	this->setMgr->setValue(QString("log/logpath"),QVariant(this->ui.le_logs->text()));
	this->setMgr->setValue(QString("viewers/path"),QVariant(this->ui.le_viewers->text()));
}

void prefDialog::installEditor() {
	this->editor = new mightyEditor(this->setMgr);
	this->ui.tabWidget->addTab(this->editor,QString("Mighty Editor"));
}

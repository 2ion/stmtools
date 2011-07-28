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

#include "logViewDialog.h"

logViewDialog::logViewDialog(Sherlog* loggerInstance, settingsManager* settingsMgr, QWidget *parent)
    : QDialog(parent)
{
	ui.setupUi(this);
	this->shownLog = -1;
	this->setAttribute(Qt::WA_DeleteOnClose);
	this->loggerInstance = loggerInstance;
	this->setMgr = settingsMgr;
	this->establishLogging();
	this->connectGUI();
	this->buildList(-1);
}

logViewDialog::~logViewDialog()
{
	this->loggerInstance->releaseLogId(this->privateLogID);
}

void logViewDialog::buildList(int preferredLog) {
	this->ui.textEdit->clear();
	this->ui.listWidget->clear();
	this->activeLogs = this->loggerInstance->activeLogs();
	// builds the lwis.
	logLWI* tmp = 0x00;
	QListIterator<int>* iter = new QListIterator<int>(this->activeLogs);

	while (iter->hasNext()){
		int k = iter->next();
		tmp = new logLWI(QString("Channel ") + QVariant(k).toString(),k);
		this->ui.listWidget->addItem(tmp);
	}

	if(preferredLog > -1) {
		this->slot_refreshLogView(new logLWI(QString(""),preferredLog));
	}

	delete iter;
	this->activeLogs.clear();
}

void logViewDialog::connectGUI() {
	this->loggerInstance->log(QString("logViewDialog::connectGUI()"),this->privateLogID);
	connect(this->ui.listWidget,SIGNAL(itemActivated(QListWidgetItem*)),this,SLOT(slot_refreshLogView(QListWidgetItem*)));
	connect(this->ui.btn_submit,SIGNAL(clicked()),this,SLOT(slot_submitMessage()));
	connect(this->ui.btn_refresh,SIGNAL(clicked()),this,SLOT(slot_refreshList()));
	connect(this->ui.btn_print,SIGNAL(clicked()),this,SLOT(slot_printLog()));

	/* feature's not being fully implemented; button is hidden: */
	//connect(this->ui.btn_logDirBrowser,SIGNAL(clicked()),this,SLOT(slot_browseLogDir()));
	ui.btn_logDirBrowser->hide();
}

void logViewDialog::establishLogging() {
	this->privateLogID = this->loggerInstance->getLogId("class logViewDialog");
}

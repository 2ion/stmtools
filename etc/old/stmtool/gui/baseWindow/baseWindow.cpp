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

#include "baseWindow.h"

baseWindow::baseWindow(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);
}

baseWindow::~baseWindow()
{
	disconnect(this,0,0,0);
	this->setCentralWidget(0x00);
	this->loggerInstance->releaseLogId(this->baseWinLogId);
}

void baseWindow::gui_actions_connect() {
	connect(this->ui.action_Quit,SIGNAL(triggered()),this,SLOT(slot_quitApplication()));
	connect(this->ui.action_About_Qt,SIGNAL(triggered()),this,SLOT(slot_showAboutQt()));
	connect(this->ui.action_About_stmTool,SIGNAL(triggered()),this,SLOT(slot_showAboutDialog()));
	connect(this->ui.action_Preferences,SIGNAL(triggered()),this,SLOT(slot_showPreferencesDialog()));
	connect(this->ui.action_Fullscreen,SIGNAL(triggered()),this,SLOT(slot_showFullScreen()));
	connect(this->ui.action_Log_viewer,SIGNAL(triggered()),this,SLOT(slot_showLogViewDialog()));
	connect(this->ui.action_Select_device,SIGNAL(triggered()),this,SLOT(slot_showDeviceSelector()));
	connect(this->ui.action_Color_scale_viewer,SIGNAL(triggered()),this,SLOT(slot_showColorScaleViewer()));
}

void baseWindow::init(settingsManager* setMgr, Sherlog* loggingInstance) {
	this->loggerInstance = loggingInstance;
	this->setMgr = setMgr;
	this->baseWinLogId = this->loggerInstance->getLogId("class baseWindow");
	this->loggerInstance->log(QString("baseWindow::init()"),this->baseWinLogId);
	this->gui_layout_installation();
	this->gui_actions_connect();
}

void baseWindow::registerDeviceManager(class deviceManager* devMgr) {
	this->devMgr = devMgr;
	this->loggerInstance->log(QString("registerDeviceManager() -> have deviceManager."),this->baseWinLogId);
}

void baseWindow::gui_layout_installation() {
	homeWidget *homy = new homeWidget();
	homy->show();
	this->setCentralWidget(homy);
}

void baseWindow::displayErrorBox(QString title, QString message) {
	QMessageBox::critical(this,title,message);
}

void baseWindow::displayInfoBox(QString title, QString message) {
	QMessageBox::information(this,title,message);
}

QProgressDialog* baseWindow::displayProgressDialog() {
	QProgressDialog *dialog = new QProgressDialog(this, Qt::Dialog);
	return dialog;
}

void baseWindow::unregisterDeviceManager() {

}

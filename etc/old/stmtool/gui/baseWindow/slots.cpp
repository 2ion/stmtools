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

void baseWindow::slot_quitApplication() {
	emit this->signal_quitApplication(this,QString("baseWindow -> GUI Event"));
}

void baseWindow::slot_showAboutQt() {
	QApplication::aboutQt();
}

void baseWindow::slot_showAboutDialog(){
	aboutDialog* dialog = new aboutDialog(this->setMgr,this);
	dialog->show();
}

void baseWindow::slot_showPreferencesDialog() {
	prefDialog* dialog = new prefDialog(this->setMgr,this);
	dialog->show();
}

void baseWindow::slot_showFullScreen() {
	if(this->isFullScreen()) {
		this->showNormal();
	} else {
		this->showFullScreen();
	}
}

void baseWindow::slot_showLogViewDialog() {
	logViewDialog* dialog = new logViewDialog(this->loggerInstance,this->setMgr,this);
	dialog->show();
}

void baseWindow::slot_showDeviceSelector() {
	deviceSelector* dialog = new deviceSelector(this->devMgr,this);
	dialog->show();
}

void baseWindow::slot_setControllingWidget(QWidget *widget) {
	this->loggerInstance->log(QString("slot_setControllingWidget() -> called"),
				this->baseWinLogId);
	/*this->layout_splitter = new QSplitter(this);
	this->layout_splitter->addWidget(widget);
	this->setCentralWidget(this->layout_splitter);
	*/
	QDockWidget *dwidget = new QDockWidget(QString("Device Control"));
	dwidget->setWidget(widget);
	this->addDockWidget(Qt::LeftDockWidgetArea,dwidget);
	dwidget->show();
}

/* HAVE to be called after setControllingWidget(*)! That is a paradigm.*/
void baseWindow::slot_setConfigurationWidgets(QHash<QString*,QWidget*> *widgets) {
	this->loggerInstance->log(QString("slot_setConfigurationWidgets() -> called"),
			this->baseWinLogId);
	/*
	if (widgets) {
		if (this->layout_configurationWidgets)
			delete this->layout_configurationWidgets;
		this->layout_configurationWidgets = new QToolBox(this,Qt::Widget);
		QHashIterator<QString*,QWidget*> *iter = new QHashIterator<QString*,QWidget*>(*widgets);
		while (iter->hasNext()) {
			iter->next();
			this->layout_configurationWidgets->addItem(iter->value(),*iter->key());
		}
		this->layout_splitter->addWidget(this->layout_configurationWidgets);
	}
	*/
	if (widgets)
	{
		QHashIterator<QString*,QWidget*> *iter = new QHashIterator<QString*,QWidget*>(*widgets);
		while (iter->hasNext())
		{
			iter->next();
			QDockWidget *stub_widget = new QDockWidget(QString(*iter->key()));
			stub_widget->setWidget(iter->value());
			this->addDockWidget(Qt::RightDockWidgetArea,stub_widget);
			// IMPROVE: really necessary?
			stub_widget->show();
		}
	}
}

void baseWindow::slot_showColorScaleViewer() {
	MyColorScale exemplum;
	MAKE_MYCOLORSCALE
	exemplum.setName(QString("exemplumScaleGreen"));
	ColorScaleViewer *dialog = new ColorScaleViewer(exemplum,NULL);
	dialog->show();
}

void baseWindow::slot_setScanDataManager(class SDM *instance) {
	if(instance) {
		this->scan_data_manager = instance;
		connect(this->ui.action_Browser,SIGNAL(triggered()),
				this->scan_data_manager,SLOT(slot_gui_browser()));
	}
}

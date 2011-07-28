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

#include "aboutDialog.h"

aboutDialog::aboutDialog(settingsManager* setMgr, QWidget *parent)
    : QDialog(parent)
{
	ui.setupUi(this);

	// setting the values ...
	this->ui.lbl_Version->setText(QString(QString("Version ") + setMgr->value(QString("app/version")).toString()));
	/*
	 * REMOVED in 2010-8.0.3.0
	this->ui.le_appPath->setText(setMgr->value(QString("app/cwd")).toString());
	this->ui.le_logPath->setText(setMgr->value(QString("log/logpath")).toString());
	*/

	/* generate library information */
	ui.pte_libraries->appendPlainText(QString("Date of Compilation is " + QString(__DATE__)+QString(" ")+QString(__TIME__)));
	ui.pte_libraries->appendPlainText(QString("Compiled against Qt version ") + QString(QT_VERSION_STR));
	ui.pte_libraries->appendPlainText(QString("Runs with Qt version ") + QString(qVersion()));
	ui.pte_libraries->appendPlainText(QString("Compiled on ") + QString("Linux 2.6.35-23-generic x86_64"));

}

aboutDialog::~aboutDialog()
{

}

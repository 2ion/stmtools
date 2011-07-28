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

#ifndef LOGVIEWDIALOG_H
#define LOGVIEWDIALOG_H

#include <QtGui/QDialog>
#include <QtCore/QListIterator>
#include <QtGui/QListWidget>
#include <QtGui/QMessageBox>
#include <QtGui/QInputDialog>
#include <QtGui/QPrinter>
#include <QtGui/QPrintDialog>
#include <settingsManager/settingsManager.h>
#include <gui/logViewDialog/logDirBrowser.h>
#include <Sherlog.h>
#include "logLWI.h"
#include "ui_logViewDialog.h"

/*! \file logViewDialog.h
 * Implements logViewDialog.
 *
 * \class logViewDialog
 * \brief GUI to facilities of Sherlog.
 *
 * logViewDialog presents active log channels managed by Sherlog
 * and their content. The user can make annotations or print the content.
 *
 * \fn void logViewDialog::buildList(int)
 * \todo Provide a preferred log id.
 * */

class logViewDialog : public QDialog
{
    Q_OBJECT

public:
    logViewDialog(Sherlog* loggerInstance, settingsManager* settingsMgr, QWidget *parent = 0);
    ~logViewDialog();

private:
    Ui::logViewDialogClass ui;
    QList<int> activeLogs;
    void buildList(int preferredLog);
    void connectGUI();
    void establishLogging();
    Sherlog* loggerInstance;
    int privateLogID;
    int shownLog;
    settingsManager* setMgr;

private slots:
	//void slot_readDirectory();
	void slot_refreshLogView(QListWidgetItem*);
	void slot_submitMessage(); // via click.
	void slot_refreshList();
	void slot_printLog();
	void slot_browseLogDir();
};

#endif // LOGVIEWDIALOG_H

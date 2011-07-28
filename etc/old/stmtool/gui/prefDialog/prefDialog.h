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

#ifndef PREFDIALOG_H
#define PREFDIALOG_H

#include <QtGui/QDialog>
#include <QtGui/QFileDialog>
#include <QtGui/QLineEdit>
#include "ui_prefDialog.h"
#include <settingsManager/settingsManager.h>
#include <gui/mightyEditor/mightyEditor.h>

/*!
 * \class prefDialog
 * \brief A preferences dialog presenting switches etc to the user.
 * \todo Use a common interface to provide preferences for every
 * component in need; see the todo of Core.
 */

class prefDialog : public QDialog
{
    Q_OBJECT

public:
    prefDialog(class settingsManager* setMgr,QWidget *parent = 0);
    ~prefDialog();

private slots:
	void slot_apply();
	void slot_cancel();
	void slot_tbtn_logs();
	void slot_tbtn_settings();
	void slot_tbtn_devices();
	void slot_tbtn_viewers();

private:
    Ui::prefDialogClass ui;
    QString browseForADirectory();
    class settingsManager* setMgr;
    void connectGUI();
    void loadSettings();
    void saveSettings();
    void installEditor();
    class mightyEditor *editor;
};

#endif // PREFDIALOG_H

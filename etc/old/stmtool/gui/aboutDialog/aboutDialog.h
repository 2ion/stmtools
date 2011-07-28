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

#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

/*!
 * \file aboutDialog.h
 * Implements aboutDialog.
 *
 * \class aboutDialog
 * \brief Implements an about dialog with information on license, author and version.
 *
 * \fn aboutDialog::aboutDialog(settingsManager*,QWidget*)
 * \param setMgr Where currently only version information comes from.
 */

#include <QtGlobal>
#include <QtGui/QDialog>
#include "ui_aboutDialog.h"
#include <settingsManager/settingsManager.h>

class aboutDialog : public QDialog
{
    Q_OBJECT

public:
    aboutDialog(settingsManager* setMgr = 0,QWidget *parent = 0);
    ~aboutDialog();

private:
    Ui::aboutDialogClass ui;
};

#endif // ABOUTDIALOG_H

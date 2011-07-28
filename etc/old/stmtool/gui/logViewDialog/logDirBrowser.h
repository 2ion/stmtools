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

#ifndef LOGDIRBROWSER_H
#define LOGDIRBROWSER_H

#include <QtGui/QWidget>
#include <QtCore/QModelIndex>
#include <QtGui/QDirModel>
#include <QtGui/QSplitter>
#include <QtGui/QTreeView>
#include <QtGui/QTextEdit>
#include <QtGui/QHBoxLayout>
#include <QFile>
#include <QTextDocument>
#include <QTextCursor>
#include <QFileInfo>
#include "ui_logDirBrowser.h"

/*!
 * \file logDirBrowser.h
 * Implements logDirBrowser.
 *
 * \class logDirBrowser
 * \brief Views and manages log files stored on the fs.
 * \deprecated No real functionality is implemented, will be removed.
 */

class logDirBrowser : public QWidget
{
    Q_OBJECT

public:
    logDirBrowser(QString path, QWidget *parent = 0);
    ~logDirBrowser();

private slots:
	void slot_viewItem(const QModelIndex &);

private:
    Ui::logDirBrowserClass ui;
    QDirModel* dirModel;
    QTreeView* tree;
    QTextEdit* texte;
    QTextDocument* doc;
};

#endif // LOGDIRBROWSER_H

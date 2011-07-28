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

#ifndef MIGHTYEDITOR_H
#define MIGHTYEDITOR_H

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QStringListIterator>
#include <QtCore/QVariant>
#include <QList>
#include <QtGui/QWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QTableWidgetItem>
#include <settingsManager/settingsManager.h>
#include <gui/mightyEditor/keyValueDialog.h>
#include "ui_mightyEditor.h"

#include <QtGui/QMessageBox>

/*! \file mightyEditor.h
 * Implements mightyEditor.
 *
 * \class mightyEditor
 * \brief A DEBUG level GUI to settingsManager.
 *
 * mightyEditor is a widget bestowing unto the user the ability
 * to manipulate ANY data stored via settingsManager. It also
 * provides input masks for selected data types and a memory facility.
 *
 * It can be easily adapted to QSettings.
 *
 * \note Segmentation faults are easily to produce with our little toy.
 *
 * \todo Implement undo & memory facility.
 * \todo Make its compililation depend onto the defintion of a macro.
 *
 * \fn void mightyEditor::populateTable()
 * \brief Takes the keys from settingsManager and enlists them.
 *
 * \fn void mightyEditor::applyChanges()
 * \brief Part of the memory facility.
 * \deprecated If the memory facility will not be implemented, the stub should vanish.
 *
 */

struct deletion_task {
	QString *key;
};

struct change_insertion_task {
	QString *key;
	QVariant *value;
};

class mightyEditor : public QWidget
{
    Q_OBJECT

public:
	mightyEditor(class settingsManager* setMgr, QWidget *parent = 0);
	void populateTable();
	void applyChanges();
	~mightyEditor();

private:
	Ui::mightyEditorClass ui;
	class settingsManager *setMgr;

	/*! @name Memory / undo facility */
	//@{
	QList<struct change_insertion_task*> *changes;
	QList<struct deletion_task*> *deletions;
	QList<struct change_insertion_task*> *insertions;
	//@}

	QString obtainSelectedKey();
	QStringList makeHeaders();
private slots:
	/*! @name Memory / undo facility */
	//@{
	void slot_trackChange(QTableWidgetItem *item);
	void slot_trackDeletion(QTableWidgetItem *item);
	void slot_trackInsertion(QTableWidgetItem *item);
	//@}
	void slot_activateButtons();
	void slot_editItem();
	void slot_deleteItem();
	void slot_insertItem();
};

#endif // MIGHTYEDITOR_H

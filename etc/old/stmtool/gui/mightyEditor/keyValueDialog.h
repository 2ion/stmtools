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

#ifndef KEYVALUEDIALOG_H
#define KEYVALUEDIALOG_H

#include <QtGui/QDialog>
#include <QtGui/QMessageBox>
#include <QtCore/QVariant>
#include <QtCore/QString>
#include <QtGui/QLineEdit>
#include <QtGui/QComboBox>
#include <gui/mightyEditor/mightyEditor.h>
#include <gui/mightyEditor/cwBoolean.h>
#include "ui_keyValueDialog.h"

/*!
 * \class keyValueDialog
 * \brief Allows edition of key-value pairs provided by mightyEditor.
 *
 * keyValueDialog will allows the edition of all simple value types
 * QVariant can be casted to (numeric,string). For value types
 * requirering mapping (e.g. QString as HEX -> Binary for QByteArray),
 * there will be used input methods being invoked by keyValueDialog.
 *
 * \todo Add more input methods.
 */

class keyValueDialog : public QDialog
{
	Q_OBJECT
public:
	keyValueDialog(QString keyname = QString(), QVariant::Type type = QVariant::Invalid, QWidget *parent = 0);
	~keyValueDialog();
	struct change_insertion_task* obtainTask();
private:
	Ui::keyValueDialogClass ui;
	QVariant::Type target_type;
	bool isMappable;
	void populateTypeBox();
	struct change_insertion_task *task;
	QString *target_key;
private slots:
	void slot_checkForMappability(const QString & input);
	void slot_setTargetType(const QString & text);
	void slot_createTask();
	void slot_close();
};

/* Available QString -> QVariant conversion methods :: 0-terminated*/
/*
const int qvariant_values[] = {
		2,
		3,
		4,
		5,
		6,
		7,
		10,
		'\0'
};
*/
#endif // KEYVALUEDIALOG_H

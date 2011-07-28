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

#include "keyValueDialog.h"

keyValueDialog::keyValueDialog(QString keyname, QVariant::Type type, QWidget *parent)
    : QDialog(parent)
{
	ui.setupUi(this);
	this->task = 0x00;
	this->isMappable = false;
	if (type == QVariant::Invalid) {
		this->target_key = 0x00;
		this->populateTypeBox();
		connect(this->ui.comboBox_valueType,
				SIGNAL(currentIndexChanged(const QString &)),
				this,
				SLOT(slot_setTargetType(const QString &)));
	} else {
		this->target_key = new QString(keyname);
		this->ui.lineEdit_key->setText(keyname);
		this->ui.lineEdit_key->setEnabled(false);
		this->ui.comboBox_valueType->setEnabled(false);
		this->ui.comboBox_valueType->addItem(QString(QVariant::typeToName(type)));
	}
	this->target_type = type;
	connect(this->ui.lineEdit_value,
			SIGNAL(textChanged(const QString &)),
			this,
			SLOT(slot_checkForMappability(const QString &)));
	this->slot_checkForMappability(QString(""));
	connect(this->ui.btn_ok,
			SIGNAL(clicked()),
			this,
			SLOT(slot_createTask()));
	connect(this->ui.btn_cancel,
			SIGNAL(clicked()),
			this,
			SLOT(slot_close()));
}

keyValueDialog::~keyValueDialog()
{

}

void keyValueDialog::slot_checkForMappability(const QString & input) {
	QVariant stub(input);
	if (stub.canConvert(this->target_type) && stub.convert(this->target_type)) {
		this->isMappable = true;
		this->ui.lbl_valid->setText(QString("VALID INPUT"));
		this->ui.btn_ok->setEnabled(true);
	} else {
		this->isMappable = false;
		this->ui.lbl_valid->setText(QString("INVALID INPUT"));
		this->ui.btn_ok->setEnabled(false);
	}
}

void keyValueDialog::slot_setTargetType(const QString & text) {
	this->target_type = QVariant::nameToType(text.toLocal8Bit().data());

	if (this->target_type == QVariant::Bool) {

	}

	this->slot_checkForMappability(this->ui.lineEdit_value->text());
}

void keyValueDialog::populateTypeBox() {
	// IMPROVE: There are basically 28 data types by standard avaiable; 0 == INVALID.

	for (int i = 1; i < 29; ++i ) {
		QString typestr = QVariant::typeToName((QVariant::Type) i);
		this->ui.comboBox_valueType->addItem(typestr,QVariant(i));
	}

	/*int index = 0;
	this->ui.comboBox_valueType->clear();
	while (qvariant_values[index] != 0) {
		QString typestr = QVariant::typeToName((QVariant::Type) index);
		this->ui.comboBox_valueType->addItem(typestr,QVariant(index));
		++index;
	}*/
}

void keyValueDialog::slot_createTask() {
	this->task = new struct change_insertion_task;
	task->value = new QVariant(this->ui.lineEdit_value->text());
	if (this->target_key == 0x00) {
		task->key = new QString(this->ui.lineEdit_key->text());
		if (*task->key == QString("")) {
			*task->key = QString("NAMELESS");
		}

	} else {
		task->key = new QString(*this->target_key);
	}
	task->value->convert(this->target_type);
	this->close();
}

struct change_insertion_task* keyValueDialog::obtainTask() {
	return this->task ? this->task : 0x00;
}

void keyValueDialog::slot_close() {
	this->close();
}

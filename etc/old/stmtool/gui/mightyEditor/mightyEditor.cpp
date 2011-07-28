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

#include "mightyEditor.h"

mightyEditor::mightyEditor(class settingsManager *setMgr, QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);
	this->changes = new QList<struct change_insertion_task*>();
	this->insertions = new QList<struct change_insertion_task*>();
	this->deletions = new QList<struct deletion_task*>();
	this->setMgr = setMgr;
	connect(this->ui.tableWidget,
			SIGNAL(itemSelectionChanged()),
			this,
			SLOT(slot_activateButtons()));
	connect(this->ui.btn_add,
			SIGNAL(clicked()),
			this,
			SLOT(slot_insertItem()));
	connect(this->ui.btn_delete,
			SIGNAL(clicked()),
			this,
			SLOT(slot_deleteItem()));
	connect(this->ui.btn_edit,
			SIGNAL(clicked()),
			this,
			SLOT(slot_editItem()));
	this->populateTable();
}

mightyEditor::~mightyEditor()
{

}

void mightyEditor::populateTable() {
	if (this->setMgr) {
		QStringList items = this->setMgr->allKeys();
		QStringListIterator *iter = new QStringListIterator(items);
		this->ui.tableWidget->setRowCount(items.size());

		int row = 0;
		while (iter->hasNext()) {
			QString currentKey = iter->next();

			/* First column KEY */
			QTableWidgetItem *stub_key = new QTableWidgetItem(currentKey);
			stub_key->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
			this->ui.tableWidget->setItem(row,0,stub_key);

			/* Third column VALUE */
			QTableWidgetItem *stub_value = new QTableWidgetItem();
			stub_value->setData(Qt::UserRole,this->setMgr->value(currentKey));
			if (stub_value->data(Qt::UserRole).canConvert(QVariant::String)) {
				stub_value->setText(stub_value->data(Qt::UserRole).toString());
			} else {
				stub_value->setText(QString("<#>"));
			}
			stub_value->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
			this->ui.tableWidget->setItem(row,2,stub_value);

			/* Second column VALUETYPE */
			QTableWidgetItem *stub_type = new QTableWidgetItem();
			stub_type->setText(QString(stub_value->data(Qt::UserRole).typeName()));
			stub_type->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
			this->ui.tableWidget->setItem(row,1,stub_type);

			++row;
		}
	}
}

void mightyEditor::slot_trackChange(QTableWidgetItem *item) {
}

void mightyEditor::slot_trackDeletion(QTableWidgetItem *item) {

}

void mightyEditor::slot_trackInsertion(QTableWidgetItem *item) {

}

void mightyEditor::slot_activateButtons() {
	this->ui.btn_delete->setEnabled(true);
	this->ui.btn_edit->setEnabled(true);
}

void mightyEditor::slot_editItem() {
	keyValueDialog *dialog = new keyValueDialog(this->obtainSelectedKey(),this->setMgr->value(this->obtainSelectedKey()).type(),this);
	dialog->exec();
	struct change_insertion_task *stub = dialog->obtainTask();
	if (stub) {
		this->setMgr->setValue(*stub->key,*stub->value);
		this->populateTable();
	}
}

void mightyEditor::slot_deleteItem() {
	QMessageBox::StandardButton btn = QMessageBox::question(this,
			QString("Key deletion"),
			QString("If you proceed, all child keys are also going to be deleted. Continue?"),
			QMessageBox::Yes | QMessageBox::No);
	if (btn == QMessageBox::Yes) {
		this->setMgr->deleteValue(this->obtainSelectedKey());
		this->ui.tableWidget->clear();
		this->ui.tableWidget->setHorizontalHeaderLabels(this->makeHeaders());
		this->populateTable();
	}
}

void mightyEditor::slot_insertItem() {
	keyValueDialog *dialog = new keyValueDialog(QString(""),QVariant::Invalid,this);
	dialog->setWindowTitle(QString("Insert a new key"));
	dialog->exec();
	struct change_insertion_task *stub = dialog->obtainTask();
	if (stub) {
		this->setMgr->setValue(*stub->key,*stub->value);
		this->populateTable();
	}
}

QString mightyEditor::obtainSelectedKey() {
	QList<QTableWidgetItem*> selected = this->ui.tableWidget->selectedItems();
	if (selected.isEmpty())
		return QString("");
	return this->ui.tableWidget->item(selected.takeFirst()->row(),0)->text();
}

void mightyEditor::applyChanges() {

}

QStringList mightyEditor::makeHeaders() {
	QStringList stub;
	stub.append(QString("Key"));
	stub.append(QString("Type"));
	stub.append(QString("Value"));
	return stub;
}

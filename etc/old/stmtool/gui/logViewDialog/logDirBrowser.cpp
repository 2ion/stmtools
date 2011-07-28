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

#include "logDirBrowser.h"

logDirBrowser::logDirBrowser(QString path, QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QString("Log Viewer :: Directory Browser [") + path + QString("]"));
	this->doc = new QTextDocument();
	this->dirModel = new QDirModel();
	QSplitter* split = new QSplitter();
	this->tree = new QTreeView(split);
	this->texte = new QTextEdit(split);
	this->tree->setSortingEnabled(true);
	this->tree->setModel(this->dirModel);
	this->tree->setRootIndex(this->dirModel->index(path));
	for (int c = 0; c < this->dirModel->columnCount(); ++c) {
		this->tree->resizeColumnToContents(c);
	}
	split->setOrientation(Qt::Vertical);

	this->texte->setReadOnly(true);

	connect(this->tree,SIGNAL(expanded(const QModelIndex &)),this,SLOT(slot_viewItem(const QModelIndex &)));

	this->layout()->addWidget(split);

}

logDirBrowser::~logDirBrowser()
{

}

void logDirBrowser::slot_viewItem(const QModelIndex & index) {
	QString path = this->dirModel->fileInfo(index).absoluteFilePath();
	QFile* file = new QFile(path);
	this->doc->clear();
	QTextCursor* curse = new QTextCursor(this->doc);
	curse->insertText(QVariant(file->readAll()).toString());
	delete curse;
}

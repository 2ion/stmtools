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

#include "FilterTable.h"


FilterTable::FilterTable() {
	row_count = 0;
	column_count = 0;
	connect(this,
			SIGNAL(columnsInserted(const QModelIndex&,int,int)),
			this,
			SLOT(slot_columnsChanged(const QModelIndex&,int,int)));
	connect(this,
			SIGNAL(columnsRemoved(const QModelIndex&,int,int)),
			this,
			SLOT(slot_columnsChanged(const QModelIndex&,int,int)));
	connect(this,
			SIGNAL(rowsInserted(const QModelIndex&,int,int)),
			this,
			SLOT(slot_rowsChanged(const QModelIndex&,int,int)));
	connect(this,
			SIGNAL(rowsRemoved(const QModelIndex&,int,int)),
			this,
			SLOT(slot_rowsChanged(const QModelIndex&,int,int)));
}


FilterTable::~FilterTable() {

}

QVariant FilterTable::filterAt(const QModelIndex &index) const{
	if(!validateIndex(index))
		return qVariantFromValue(NULL);
	if(index.column() > table.size() || index.row() > table.at(index.column())->size())
		return qVariantFromValue(NULL);
	qVariantFromValue(table.at(index.column())->at(index.row()));
}

bool FilterTable::validateIndex(const QModelIndex &index) const {
	if(!index.isValid() ||
			!(index.row() < row_count) ||
			!(index.column() < column_count))
		return false;
	return true;
}

/*****************************************************************************/

int FilterTable::rowCount(const QModelIndex &parent) const {
	return row_count;
}


int FilterTable::columnCount(const QModelIndex &parent) const {
	return table.size();
}


QVariant FilterTable::data(const QModelIndex &index, int role) const {
	if(!validateIndex(index))
		return QVariant();

	void *fptr = NULL;
	switch(role) {
	case Qt::DisplayRole:;
		fptr = FT_FILTER(index.column(),index.row());
		if(fptr == NULL) {

		}

	;
	case Qt::DecorationPropertyRole:;;
	case Qt::EditRole:;;
	case Qt::ToolTipRole:;;
	case Qt::StatusTipRole:;;
	case Qt::WhatsThisRole:;;
	case Qt::SizeHintRole:;;
	case FT_FILTERPTR:
	  return qVariantFromValue(FT_FILTER(index.column(),index.row()));
	;
	}
}


bool FilterTable::setData(const QModelIndex &index, const QVariant &value, int role) {
	if(!validateIndex(index))
		return false;
}


Qt::ItemFlags FilterTable::flags(const QModelIndex &index) const {
	if(validateIndex(index))
		return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
	return Qt::NoItemFlags;
}


QVariant FilterTable::headerData(int section, enum Qt::Orientation orientation, int role) const {
	switch(orientation) {
	case Qt::Horizontal:
		return QVariant(QString("T") + QVariant(section).toString());
		break;
		;
	default:;
	case Qt::Vertical:
		return QVariant(section);
		;
	}
	return QVariant();
}

bool FilterTable::insertRows(int row, int count, const QModelIndex &parent) {
	if(!validateIndex(parent))
		return false;

	beginInsertRows(parent, row, row+count-1);

	for(int pos = row; pos < row+count; ++pos)
		table.at(parent.column())->insert(pos, NULL);

	endInsertRows();
	return true;
}

bool FilterTable::insertRow(int row, const QModelIndex &parent) {
	return insertRows(row,1,parent);
}


bool FilterTable::removeRows(int row, int count, const QModelIndex &parent) {
	if(!validateIndex(parent))
		return false;
	beginRemoveRows(parent, row, row+count-1);

	/* remove items from list */
	for(int pos = row; pos < row+count; ++pos)
		table.at(parent.column())->removeAt(pos);

	/* truncate the list, if gaps have been left */
	if((row + count) < table.at(parent.column())->size())
		for(int pos = row+count; pos < table.at(parent.column())->size(); ++pos)
			table.at(parent.column())->move(pos, pos-count);

	endInsertRows();
	return true;
}


bool FilterTable::removeRow(int row, const QModelIndex &parent) {
	return removeRows(row,1,parent);
}

bool FilterTable::insertColumns(int column, int count, const QModelIndex &parent) {
	beginInsertColumns(parent, column, column+count-1);
	/* prepend columns */
	if(column == 0) {
		for(int c=0; c < count; ++c)
			table.prepend(new QList<void*>());
	} else {
	/* append columns */
		if(column == column_count) {
			for(int c=0; c < count; ++c)
				table.append(new QList<void*>());
		} else {
			/* insert columns within table */
			for(int pos=column; pos < column+count; ++pos)
				table.insert(pos, new QList<void*>());
		}
	}
	endInsertColumns();
	return true;
}

bool FilterTable::insertColumn(int column, const QModelIndex &parent) {
	return insertColumns(column, 1, parent);
}

bool FilterTable::removeColumns(int column, int count, const QModelIndex &parent) {
	beginRemoveColumns(parent, column, column+count-1);

	for(int pos = column; pos < column+count; ++pos)
		table.removeAt(pos);

	if((column + count) < table.size())
		for(int pos=column+count; pos < table.size(); ++pos)
			table.move(pos, pos-count);

	endRemoveColumns();
	return true;
}


bool FilterTable::removeColumn(int column, const QModelIndex &parent) {
	return removeColumns(column, 1, parent);
}
/*****************************************************************************/

void FilterTable::slot_rowsChanged(const QModelIndex &parent, int start, int end) {
	QListIterator<QList<void*>*> iter(table);
	while(iter.hasNext()) {
		int s = iter.next()->size();
		if(s > row_count)
			row_count = s;
	}
}

void FilterTable::slot_columnsChanged(const QModelIndex &parent, int start, int end) {
	for(int pos=0; pos < table.size(); ++pos) {
		if(table.at(pos)->size() == 0) {
			insertRow(0, index(0,pos));
		}
	}
	column_count = table.size();
}

void FilterTable::slot_setStmbuf_t(enum stmt_lib::StmBufValueType type) {
	stmbuf_t = type;
}


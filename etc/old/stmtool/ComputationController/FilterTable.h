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

#ifndef FILTERTABLE_H_
#define FILTERTABLE_H_
/*!
 \file FilterTable.h
 */

#include <QtDebug>
#include <QtCore/QAbstractTableModel>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <ComputationController/StackableFilter.h>
#include <general/StmtLib.h>
#include <sys/types.h>

/*!
 * @name Macros for template emulation.
 * They can only be used with FilterTable.
 */
//@{
#define FT_FILTER(column,row) table.at((column))->at((row))
#define FT_VTSIZE (stmbuf_t == stmt_lib::FLOAT ? sizeof(float) : \
		(stmbuf_t == stmt_lib::UNSIGNED_INT ? sizeof(quint32) : \
				(stmbuf_t == stmt_lib::UNSIGNED_CHAR ? sizeof(unsigned char) : \
						(stmbuf_t == stmt_lib::INT ? sizeof(qint32) : (size_t) 0))))
#define FT_VTCAST_FLOAT(fptr) reinterpret_cast<StackableFilter<float>* >(fptr)
#define FT_VTCAST_UCHAR(fptr) reinterpret_cast<StackableFilter<unsigned char>* >(fptr)
#define FT_VTCAST_UINT(fptr) reinterpret_cast<StackableFilter<quint32>* >(fptr)
#define FT_VTCAST_INT(fptr) reinterpret_cast<StackableFilter<qint32>* >(fptr)
#define FT_TELL_FLOAT(fptr,request) FT_VTCAST_FLOAT(fptr)->tell(request)
#define FT_TELL_UCHAR(fptr,request) FT_VTCAST_UCHAR(fptr)->tell(request)
#define FT_TELL_UINT(fptr,request) FT_VTCAST_UINT(fptr)->tell(request)
#define FT_TELL_INT(fptr,request) FT_VTCAST_INT(fptr)->tell(request)
#define FT_TELL(fptr,request) (FT_VTSIZE == sizeof(float) ? FT_TELL_FLOAT(fptr,request) : \
		(FT_VTSIZE == sizeof(quint32) ? FT_TELL_UINT(fptr,request) : \
				(FT_VTSIZE == sizeof(unsigned char) ? FT_TELL_UCHAR(fptr,request) : \
						(FT_VTSIZE == sizeof(qint32) ? FT_TELL_INT(fptr,request) : QVariant()))))
//@}

class FilterTable : public QAbstractTableModel {
	Q_OBJECT
public:
	FilterTable();
	~FilterTable();

	/*! @name QAbstractTableModel interface */
	//@{
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
	Qt::ItemFlags flags (const QModelIndex &index) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	//QModelIndex parent(const QModelIndex &index) const;
	bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
	bool insertRow(int row, const QModelIndex &parent = QModelIndex());
	bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
	bool removeRow(int row, const QModelIndex &parent = QModelIndex());
	bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex());
	bool insertColumn(int column, const QModelIndex &parent = QModelIndex());
	bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex());
	bool removeColumn(int column, const QModelIndex &parent = QModelIndex());
	//@}

public slots:
	void slot_setStmbuf_t(enum stmt_lib::StmBufValueType type);
private:
	// for unexpensive rowCount & columnCount
	int row_count;
	int column_count;
	enum stmt_lib::StmBufValueType stmbuf_t;

	QVariant filterAt(const QModelIndex &index) const;
	bool validateIndex(const QModelIndex &index) const;

	// filter table as list of columns
	QList<QList<void*>*> table;

private slots:
	void slot_rowsChanged(const QModelIndex &parent, int start, int end);
	void slot_columnsChanged(const QModelIndex &parent, int start, int end);
};

#endif /* FILTERTABLE_H_ */

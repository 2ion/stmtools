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

#ifndef STMDATA_H_
#define STMDATA_H_

#include <QtCore/QObject>
#include <QtCore/QList>
//#include <devices/stmSample.h>

struct scan_parameters
{
        int *x_size;
        int *y_size;
};

typedef QList<QList<double*>*> datatable;

class stmData : public QObject
{
        Q_OBJECT
public:
        stmData();
        ~stmData();
        datatable* getData();
        datatable* getAdditionalData();
signals:
        void signal_newDataPending(datatable*);
        void signal_additionalDataPending(datatable*);
        void signal_changedScanParameters(struct scan_parameters*);
};

#endif /* stmData.h */

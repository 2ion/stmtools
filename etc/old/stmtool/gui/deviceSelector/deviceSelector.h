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

#ifndef DEVICESELECTOR_H
#define DEVICESELECTOR_H

#include <QtGui/QDialog>
#include <QtGui/QListWidgetItem>
#include <QtGui/QMessageBox>
#include <deviceManager/deviceManager.h>
#include "dsLWI.h"
#include "ui_deviceSelector.h"

/*!
 * \file deviceSelector.h
 * Implements deviceSelector.
 *
 * \class deviceSelector
 * \brief GUI to select the active device.
 *
 * deviceSelector is an interface to deviceManager's routines
 * managing the status of devices.
 * Here the user selects which available device should be
 * handled as data sources.
 *
 * \todo Implement unload facility.
 */

class deviceSelector : public QDialog
{
    Q_OBJECT

public:
    deviceSelector(class deviceManager *devMgr, QWidget *parent = 0);
    ~deviceSelector();

private:
	void init_SS();
	void populateDeviceList();
	Ui::deviceSelectorClass ui;
	class deviceManager *devMgr;
private slots:
	void slot_do_close();
	void slot_do_select();
	void slot_do_viewProperties(QListWidgetItem*);
signals:
	void signal_selected(devices::deviceID*);
};

#endif // DEVICESELECTOR_H

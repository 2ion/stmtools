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

#ifndef STMTCOMPONENTDOCK_H_
#define STMTCOMPONENTDOCK_H_
#include <QtPlugin>
#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QVector>
#include <QtGui/QApplication>
#include <QtGui/QWidget>

#include <Sherlog.h>

#include <general/StmtComponent.h>
#include <deviceManager/deviceManager.h>
#include <settingsManager/settingsManager.h>
#include <sdm/SDM.h>
#include <viewportManager/viewportManager.h>

class StmtComponentDock : public QObject {
	Q_OBJECT
public:
	StmtComponentDock();
	~StmtComponentDock();
public slots:
	void scd_slot_log(QString, enum StmtComponent::MessageLevel);
	void scd_slot_resolve(int,QWidget*);
signals:
	void scd_signal_init();
	void scd_signal_shutdown();
	void scd_signal_resolveDependencies();
	void scd_signal_sendDependencies(QList<StmtComponent*>);
	void scd_signal_verbosity(enum StmtComponent::VerbosityLevel);
private slots:
	void scd_slot_loadBasicComponents();
	void scd_slot_loadExtensionComponents();
private:
	QMap<QString,StmtComponent*> scd_components;
	QApplication *scd_qtr;
	Sherlog scd_sherlogger;
};

#endif /* STMTCOMPONENTDOCK_H_ */

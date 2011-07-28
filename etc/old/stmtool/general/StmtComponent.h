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

#ifndef STMTCOMPONENT_H_
#define STMTCOMPONENT_H_

#include <QtPlugin>
#include <QtCore/QObject>
#include <QtCore/QVector>

class StmtComponent : public QObject {
	Q_OBJECT
public:
	enum Component {
		cCORE = 			1 << 0,
		cDEVMGR = 		1 << 1,
		cBASEWINDOW = 	1 << 2,
		cSETMGR = 		1 << 3,
		cSDM = 			1 << 4,
		cQAPP = 		1 << 5
	};

	enum DepStatus {
		RESOLVED,
		UNRESOLVED
	};

	enum MessageLevel {
		mDEADLY,
		mCRITICAL,
		mURGENT,
		mINFO,
		mDEBUG
	};

	enum VerbosityLevel {
		vSILENT,
		vNORMAL,
		vDEBUG,
		vVERBOSE
	};


public slots:
	virtual void stmtc_slot_init() = 0;
	virtual void stmtc_slot_shutdown() = 0;
	virtual void stmtc_slot_resolveDependencies() = 0;
	virtual void stmtc_slot_receiveDependencies(QList<StmtComponent*>) = 0;
	virtual void stmtc_slot_setVerbosity(enum VerbosityLevel) = 0;
signals:
	void stmtc_signal_resolve(int,QWidget*);
	void stmtc_signal_log(QString,enum MessageLevel);
};
Q_DECLARE_INTERFACE(StmtComponent,"stmtc")


#endif /* STMTCOMPONENT_H_ */

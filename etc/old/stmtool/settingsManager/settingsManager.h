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

#ifndef SETTINGSMANAGER_H_
#define SETTINGSMANAGER_H_
/*! \class settingsManager
 * \brief Allows components to request previously stored
 * key-value-pairs with all the variety of QVariant.
 *
 * It is possible to depose default values in settingsManager's
 * implementation.
 *
 * \note See Qt's documentation on QSettings.
 */

#include <QtCore>
#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <QtCore/QVariant>
#include <QtCore/QDir>
#include <QtCore/QStringList>

#include <general/eStmError.h>
#include <general/StmtComponent.h>

class settingsManager : public StmtComponent {
	Q_OBJECT
public:
	settingsManager();
	~settingsManager();

	eStmError init ();
	QVariant value(const QString & key);
	void setValue(const QString & key, const QVariant & value);
	void deleteValue(const QString &key);
	QStringList allKeys();
public slots:
	/*! @name StmtComponent interface */
	//@{
	void stmtc_slot_init();
	void stmtc_slot_shutdown();
	void stmtc_slot_resolveDependencies();
	void stmtc_slot_receiveDependencies(QList<StmtComponent*>);
	void stmtc_slot_setVerbosity(enum StmtComponent::VerbosityLevel);
	//@}
private:
	QVariant makeDefaultValue(const QString & key);
	QSettings* settings;
	QString* settingsPath;
};

//#ifdef STMT_APPEND_SOURCE
//#include "settingsManager.cpp"
//#endif

#endif /* SETTINGSMANAGER_H_ */

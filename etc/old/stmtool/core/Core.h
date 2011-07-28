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

#ifndef CORE_H_
#define CORE_H_
/*!
 * \file Core.h
 * \brief Implements Core.
 *
 * \class Core
 * \brief Controls the startup of stmtool and links its components together.
 *
 * Each instance of Core results in another fully capable instance of stmtool,
 * but this may produce unexpected results.
 * Whatsoever your extension to this class may be, Core::init() has to be called
 * FIRST.
 *
 * \todo As everybody can see, the initialization layout of stmtool's component classes is
 * not uniform, and the initialization process itself is being interfused by ugly calls of
 * out-of-the-line created 'helper' methods in order to keep the dependencies of every
 * component satisfied. This regards especially baseWindow, SDM, deviceManager.
 * If stmtool should undergo a rewrite, all component classes should be derived from a common
 * interface, e.g. class StmtComponent, which might look like the following snippet:
 * \code
 * #include <Qt>
 * #include <QtCore>
 * #include <QtGui>
 *
 * class StmtComponent : public QObject {
 *
 * 	Q_OBJECT
 *
 * public:
 * 	enum stmtc_status {
 * 		OK,
 * 		UNRESOLVED_DEPENDENCY_*,
 * 		UNKNOWN
 * 	};
 *
 * public slots:
 * 	virtual void stmtc_slot_init() = 0;
 * 	virtual void stmtc_slot_shutdown() = 0;
 * 	// After all components would have been instancated,
 * 	// hereby they could resolve their dependencies from
 * 	// other components by submitting a request to Core.
 * 	virtual void stmtc_slot_resolveDependencies() = 0;
 *
 * signals:
 * 	// With a rewrite of Sherlog, the log modus could be also changed.
 * 	// By QMetaObject, wherefrom all components would be derived through
 * 	// QObject, the caller's name and properties could be acquired.
 *	void stmtc_signal_log(const QString &message, qint32 messageLevel);
 *	// For a general overview, i.e. if stmtool as the suite is ready
 *	// or not, such a report channel may be used.
 *	void stmtc_signal_status(enum stmtc_status status);
 *	// To provide an integrative way for different components to
 *	// make a preference page available, this signal should be caught
 *	// by baseWindow keeping the widgets in stock for prefDialog.
 *	void stmtc_signal_preferenceWidget(const QWidget *client = 0);
 * };
 * \endcode
 * ; which would allow all components being handled easily by a bus system.
 *
 * \todo While stmtool is being rewritten, all the helper classes of components
 * DIRECTLY related to them should be included in their namespaces / class definitions to
 * keep them cleanly arranged (currently, they're DANGLING. This would help to save effort
 * while writing this doc, too.
 *
 * \fn void Core::init(QApplication*,QString*)
 * \brief Executes all 'init_' member methods in the appropriate order.
 *
 * Its counterpart is solely the destructor calling all 'uinit_' member methods likewise.
 *
 * \param appObject Unrestricted (!) pointer to a QApplication.
 * \param settingsDir Directory to be used while initializing settingsManager.
 * \bug settingsDir parameter does not yet work as expected.
 *
 * \fn Sherlog* Core::logInstance(void)
 * \brief Returns a pointer to an instance of the Sherlog logging library.
 * \return Core::loggerInstance
 *
 * \fn void Core::init_establishSetMgr(QString*)
 * \brief Sets environment variables in an instance of settingsManager.
 *
 * \fn void Core::init_establishLogging(settingsManager*)
 * \brief Setups application-wide logging facility.
 *
 * \fn void Core::init_establishGUI(settingsManager*,Core*)
 * \brief Setups an instance of baseWindow.
 *
 * \fn void Core::init_establishDevMgr(Sherlog*,settingsManager*,baseWindow*)
 * \brief Setups an instance of deviceManager.
 *
 * \note Being rewritten, this method shall not call member methods of
 * another class.
 *
 * \fn void Core::init_establishSDM(Sherlog*,settingsManager*,deviceManager*)
 * \brief Setups an instance of SDM.
 *
 * \fn void Core::init_establishSSCS(void)
 * \brief Eventually connects slots and signals of Core with SS of other classes.
 *
 * \note At the moment, it is abused to call a method in Core::baseWin, which should
 * be adjusted by the next rewrite.
 *
 * \fn void Core::init_installUser(void)
 * \brief Handles the transition of the startup process to the
 * GUI main loop.
 *
 * Currently, it does only call QApplication::exec(), but because the
 * rendering of the STM images will be handled by the CImg library,
 * later it has to wrap QtGui's diverse input events up by creating an
 * instance of the yet not existent class QCImgWrap.
 *
 * \fn void Core::slot_quit(QObject*,QString)
 * \brief Allows the user to kill the Core at will ...
 * \param quitter The QObject calling.
 * \param message Reason for quitting; will be logged.
 *
 * \var Core::coreLogID
 * \brief Retrieved from Sherlog, identifies logging client.
 *
 * \typedef class Core Core
 * \brief Crappy, but necessary to bestride different shared libraries.
 * \note Please fix.
 */
#include <QtDebug>
#include <QtCore>
#include <QtPlugin>
#include <QtCore/QObject>
#include <QtCore/QDir>
#include <QtGui/QApplication>
#include <QtCore/QString>

#include <cassert>

#include <Sherlog.h>
#include <settingsManager/settingsManager.h>
#include <deviceManager/deviceManager.h>
#include <sdm/SDM.h>
#include <general/maindefs.h>
#include <gui/baseWindow/baseWindow.h>
#include <general/stmr.h>
#include <general/StmtComponent.h>
#include <general/StmtComponentDock.h>

class Core : public StmtComponent {
	Q_OBJECT
public:
	Core();
	~Core();
	void init(QApplication* appObject);
	Sherlog* logInstance();
public slots:
	// StmtComponent interface
	void stmtc_slot_init();
	void stmtc_slot_shutdown();
	void stmtc_slot_resolveDependencies();
	void stmtc_slot_receiveDependencies(QList<StmtComponent*>);
	void stmtc_slot_setVerbosity(enum StmtComponent::VerbosityLevel vbl);
private:
	/*! @name Callees of Core::init() */
	//@{
	void init_establishSetMgr();
	void init_establishLogging(settingsManager* setMgr);
	void init_establishGUI(settingsManager*,Core*);
	void init_establishDevMgr(Sherlog*,settingsManager*,class baseWindow*);
	void init_establishSDM(Sherlog*,settingsManager*,class deviceManager*);
	//void init_establishViewMgr(settingsManager*);
	void init_establishSSCS();
	void init_installUser();
	//@}

	/*! @name Un-initializing methods are callees of Core::~Core() */
	//@{
	void uinit_viewMgr();
	void uinit_devMgr();
	void uinit_GUI();
	void uinit_setMgr();
	void uinit_logging();
	void uinit_SDM();
	//@}

	QApplication* appObject;
	settingsManager* setManager;
	Sherlog* loggerInstance;
	class baseWindow* baseWin;
	class deviceManager* devManager;
	class SDM *scan_data_manager;
	int coreLogID;

private slots:
	void slot_quit(QObject* quitter, QString message);
};

typedef class Core Core;

#endif /* CORE_H_ */

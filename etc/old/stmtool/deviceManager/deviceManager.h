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

#ifndef DEVICEMANAGER_H_
#define DEVICEMANAGER_H_
/*!
 * \file deviceManager.h
 * \brief Implements deviceManger.
 *
 * \class deviceManager
 * \brief Handles device plugins and interfacing of other components with them.
 *
 * The deviceManager
 * <UL>
 * <LI>Loads available device plugins;</LI>
 * <LI>At request, it anchors their functionality within stmtool;</LI>
 * <LI>Exposes parameters and image buffers of devices to other components;</LI>
 * <LI>Announces changes in device and data status via signals;</LI>
 * <LI>Is responsible for the secure shutdown of any utilized devices.</LI>
 * </UL>
 *
 * \section devMgr_w How the user will be shown the device controls
 * A device has to provide at least a controlling widget and an arbitrary
 * number of parametric widgets (look at iDevice for more information).
 * If the device manager finds a device provides such widgets, or the device
 * demands a widget change while being active (not yet implemented), it emits
 * signal_device_controllingWidgetChanged() respective
 * signal_device_configurationWidgetsChanged(); this signals will be catched by
 * baseWindow, which does the layout & exposition task.
 *
 * \todo Usage of parametricWidgets <-> configurationWidgets is equivocal, must be
 * changed.
 *
 * \fn eStmError deviceManager::init_loadPlugins(void)
 * \brief Instanciates statically & dynamically linked device plugins
 * without calling iDevice::instruct().
 *
 * \todo Does not yet load statically linked plugins.
 *
 * \fn QList<devices::deviceID*>* deviceManager::availableDevices()
 * \brief One acquires a list of handles being used to call
 * slot_loadDevice(devices::deviceID*)
 *
 * \fn devices::runningDevice* deviceManager::runningDevice()
 * \brief One acquires a pointer if a device is busy.
 * \return NULL if no device's working.
 *
 * A device is considered a <EM>running</EM> device if it has signalled it
 * is working.
 *
 * \fn void deviceManager::signal_new_device_loaded(devices::runningDevice*)
 * \brief Emitted whenever a device announces it is going to work.
 *
 * \fn void deviceManager::signal_device_controllingWidgetChanged(QWidget*)
 * \brief Emitted whenever a devices signals it want to have another widget
 * being its controlling widget.
 *
 *
 * \struct device_representation
 * \brief Holds information necessary to unload any device.
 *
 */


#include <QtCore>
#include <QObject>
#include <QtCore/QLibrary>
#include <QtCore/QHash>
#include <QtCore/QList>
#include <QtCore/QPluginLoader>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QFileInfoList>
#include <QtCore/QFileInfo>
#include <QtCore/QListIterator>
#include <QtCore/QTimer>
#include <QtGui/QProgressDialog>

#include <unistd.h>
#include <cassert>

#include <Sherlog.h>
#include <settingsManager/settingsManager.h>
#include <general/eStmError.h>
#include <devices/iDevice.h>
#include <gui/baseWindow/baseWindow.h>
#include <general/StmtComponent.h>

struct device_representation {
	iDevice *r_interface;
	QPluginLoader *r_loader;
};

class deviceManager : public StmtComponent {
	Q_OBJECT
public:
	deviceManager(Sherlog* loggerInstance, settingsManager* setMgr, class baseWindow* gui);
	~deviceManager();

	eStmError init();
	QList<devices::deviceID*>* availableDevices();
	devices::runningDevice* runningDevice();

signals:
	void signal_new_device_loaded(devices::runningDevice*);
	void signal_device_controllingWidgetChanged(QWidget*);
	void signal_device_configurationWidgetsChanged(QHash<QString*,QWidget*>*);

public slots:
	void slot_loadDevice(devices::deviceID* device);
	/*! @name StmtComponent interface */
	//@{
	void stmtc_slot_init();
	void stmtc_slot_shutdown();
	void stmtc_slot_resolveDependencies();
	void stmtc_slot_receiveDependencies(QList<StmtComponent*>);
	void stmtc_slot_setVerbosity(enum StmtComponent::VerbosityLevel);
	//@}
private:
	struct device_representation *activeDevice;
	devices::deviceWidgets *activeDevice_Widgets;

	/*! @name Callees of deviceManager::init() */
	//@{
	eStmError init_loadPlugins();
	eStmError init_establishLogging();
	eStmError init_connectSS();
	//@}

	// QHash<devices::deviceID*,iDevice*>* loadedDevices;
	QHash<devices::deviceID*,struct device_representation*> *loadedDevices;
	Sherlog* loggerInstance;
	settingsManager* setMgr;
	baseWindow* gui;

	int myLogId;
};

#endif /* DEVICEMANAGER_H_ */

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

#include "deviceManager.h"

#ifndef FORCE_SHUTDOWN_TRIES
#define FORCE_SHUTDOWN_TRIES 5
#endif

deviceManager::deviceManager(Sherlog* loggerInstance, settingsManager* setMgr, baseWindow* gui) {
	if((loggerInstance != 0x00) && (setMgr != 0x00) && (gui != 0x00)) {
	this->loggerInstance = loggerInstance;
	this->setMgr = setMgr;
	this->gui = gui;
	} else {
		this->loggerInstance = 0x00;
		this->setMgr = 0x00;
		this->gui = 0x00;
	}
	this->myLogId = -1;
}

deviceManager::~deviceManager() {
	this->loggerInstance->log(QString("~deviceManager () -> going to unload plugins."),this->myLogId);
	disconnect(this,0,0,0);
	/* devices have to be unloaded. */
	if (this->loadedDevices) {
		QHashIterator<devices::deviceID*,struct device_representation*> *iter = new QHashIterator<devices::deviceID*,struct device_representation*>(*this->loadedDevices);
		assert(iter != NULL);
		while (iter->hasNext()) {
			iter->next();
			struct device_representation *stub = iter->value();
			stub->r_interface->instruct(devices::SHUTDOWN);
			/* TODO: Implement soft shutdown routine
			if (this->setMgr->value(QString("devices/flags/forceShutdown")).toBool()) {
				if (stub->r_interface->status() == devices::WORKING) {
					for (int tries = 0; tries < FORCE_SHUTDOWN_TRIES; ++tries) {
						sleep(2);

					}
				}
			} */
			stub->r_loader->unload();
		}
	}
	this->loggerInstance->releaseLogId(this->myLogId);
}

eStmError deviceManager::init() {
	eStmError errorLevel;
	errorLevel = this->init_establishLogging();
	errorLevel = this->init_loadPlugins();
	errorLevel = this->init_connectSS();
	return errorLevel;
}

eStmError deviceManager::init_loadPlugins() {
	QObject* currentObject = 0x00;
	iDevice* currentDevice = 0x00;
	struct device_representation* currentRepresentation = 0x00;

	QDir* deviceDirectory = new QDir(this->setMgr->value(QString("devices/path")).toString());
#ifdef DEBUG
	this->loggerInstance->log(QString("init_loadPlugins() -> deviceDirectory = ") + deviceDirectory->absolutePath(),
			this->myLogId);
#endif
	this->loadedDevices = new QHash<devices::deviceID*,struct device_representation*>();

	if(deviceDirectory->exists() && deviceDirectory->isReadable()) {
		QFileInfoList dirEntries = deviceDirectory->entryInfoList(QDir::Files);
#ifdef DEBUG
		this->loggerInstance->log(QString("Number of deviceDirectory's entries = " +
				QVariant(dirEntries.size()).toString()),
				this->myLogId);
#endif
		QListIterator<QFileInfo>* dirEntryIter = new QListIterator<QFileInfo>(dirEntries);

		while (dirEntryIter->hasNext()) {
			QFileInfo stub = dirEntryIter->next();
			if(QLibrary::isLibrary(stub.absoluteFilePath())) {
				QPluginLoader *currentPlugin = new QPluginLoader(stub.absoluteFilePath());
				//QPluginLoader currentPlugin(stub.absoluteFilePath());
#ifdef DEBUG
				this->loggerInstance->log(QString("QPluginLoader -> Attempting to load file ") + currentPlugin->fileName(),
						this->myLogId);
#endif
				currentObject = currentPlugin->instance();
				if (currentObject == 0x00) {
					this->loggerInstance->log(QString("currentObject == 0x00"),this->myLogId);
					delete currentPlugin;
				}
				if(currentObject) {
					currentDevice = qobject_cast<iDevice*>(currentObject);
					if(currentDevice != 0x00) {
						currentRepresentation = new struct device_representation;
						currentRepresentation->r_interface = currentDevice;
						currentRepresentation->r_loader = currentPlugin;
						this->loadedDevices->insert(currentDevice->Id(),currentRepresentation);
#ifdef DEBUG
						this->loggerInstance->log(QString("Device has been loaded: " + currentDevice->Id()->devName),
								this->myLogId);
#endif
					}
				}
			}
		}
	} else {
		this->loggerInstance->log(QString("Plugin directory is not available!!"),this->myLogId);
		return ERR_PLUGIN_DIRECTORY_NOT_AVAILABLE;
	}
	return OK;
}

eStmError deviceManager::init_establishLogging() {
	this->myLogId = this->loggerInstance->getLogId("deviceManager");
	this->loggerInstance->log(QString("deviceManager::init_establishLogging()"),this->myLogId);
	return OK;
}

QList<devices::deviceID*>* deviceManager::availableDevices() {
	if (this->loadedDevices->isEmpty())
		return 0x00;

	QList<devices::deviceID*> *stub = new QList<devices::deviceID*>();
	QHashIterator<devices::deviceID*,struct device_representation*> *iter = new QHashIterator<devices::deviceID*,struct device_representation*>(*this->loadedDevices);
	while (iter->hasNext()) {
		iter->next();
		stub->append(iter->key());
	}
	return stub;
}

eStmError deviceManager::init_connectSS() {
	connect(this,SIGNAL(signal_device_controllingWidgetChanged(QWidget*)),this->gui,SLOT(slot_setControllingWidget(QWidget*)));
	connect(this,SIGNAL(signal_device_configurationWidgetsChanged(QHash<QString*,QWidget*>*)),this->gui,SLOT(slot_setConfigurationWidgets(QHash<QString*,QWidget*>*)));
}

void deviceManager::slot_loadDevice(devices::deviceID* device) {
	this->loggerInstance->log(QString("slot_loadDevice() -> DEVICE: ") + QString(device->devName),
			this->myLogId);
	if  (this->loadedDevices->contains(device)) {
		this->activeDevice = this->loadedDevices->value(device);
		devices::reply reply = this->activeDevice->r_interface->instruct(devices::INIT);
		if (reply == devices::OK) {
			this->activeDevice_Widgets = this->activeDevice->r_interface->widgets();
			if (this->activeDevice_Widgets) {
				/* TODO: expose widgets to the GUI */
				if (this->activeDevice_Widgets->controllingWidget) {
					this->loggerInstance->log(QString("There is a controlling widget."),
							this->myLogId);
					emit this->signal_device_controllingWidgetChanged(this->activeDevice_Widgets->controllingWidget);
				}
				if (this->activeDevice_Widgets->parametricWidgets) {
					this->loggerInstance->log(QString("There are parametric widgets."),
							this->myLogId);
					emit this->signal_device_configurationWidgetsChanged(this->activeDevice_Widgets->parametricWidgets);
				}
			} else {
				this->gui->displayInfoBox(QString("Device Manager"),
						QString("The selected widget does not provide any controls."));
			}
			//TODO:emit this->signal_new_device_loaded();

		} else {
			this->gui->displayErrorBox(QString("Device Manager"),
						QString("The selected device could not be initialized."));
		}

	}
}

void deviceManager::stmtc_slot_init() {
}

void deviceManager::stmtc_slot_resolveDependencies() {
}

void deviceManager::stmtc_slot_receiveDependencies(QList<StmtComponent*> list) {

}

void deviceManager::stmtc_slot_setVerbosity(enum StmtComponent::VerbosityLevel vlevel) {
}

void deviceManager::stmtc_slot_shutdown() {
}



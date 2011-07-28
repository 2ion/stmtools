/*! \file deviceMgr_slots.cpp
 * \brief Implements the slots of deviceManager.
 */

#include "deviceManager.h"
#define STR_IERR_TITLE (tr("Device Manager :: Device initialization"))

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

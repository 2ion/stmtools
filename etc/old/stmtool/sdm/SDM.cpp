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

#include "SDM.h"

#ifndef SDM_INITFILES_KEY
#define SDM_INITFILES_KEY (QString("sdm/res/init_files"))
#endif
#ifndef SDM_CONFIGMAPS_KEY
#define SDM_CONFIGMAPS_KEY (QString("sdm/res/cfg_maps"))
#endif
#ifndef SDM_DATASPACE_MODULE_PATH_KEY
#define SDM_DATASPACE_MODULE_PATH_KEY (QString("sdm/res/ds_mod_path"))
#endif

SDM::SDM(Sherlog *logger_instance,
                class deviceManager *device_manager,
                settingsManager *settings_manager) :
                my_model(this)
{
	this->device_manager = device_manager;
	this->settings_manager = settings_manager;
	this->logger_instance = logger_instance;
	this->logger_id = this->logger_instance->getLogId("SDM");
	loadAvailableRessources();
	loadDataspaces(this->settings_manager->value(SDM_DATASPACE_MODULE_PATH_KEY).toString());
}

SDM::~SDM() {
	this->logger_instance->releaseLogId(this->logger_id);
}

void SDM::slot_gui_browser() {
	SDMBrowser *browser = new SDMBrowser();
	browser->show();
}

void SDM::slot_gui_recentRessources(QList<QString> *writable_list) {

}

void SDM::slot_ui_openDataspace() {
}

void SDM::slot_ui_closeDataspace() {

}

void SDM::loadDataspaces(const QString &directory) {
	dataspaces.append(builtinDataspaces());
}

QList<struct sdm_dataspace_instance*> SDM::builtinDataspaces() {
	QList<struct sdm_dataspace_instance*> result;

	struct sdm_dataspace_instance *ds_fs = new struct sdm_dataspace_instance;
	assert(ds_fs != NULL);
	ds_fs->instance = new sdm_dataspace_fs();
	assert(ds_fs->instance != NULL);
	lookupDataspace(ds_fs);
	ds_fs->loader = NULL;
	result.append(ds_fs);

	return result;
}
void SDM::lookupDataspace(struct sdm_dataspace_instance *instance) {
	instance->essence = new struct sdm_dataspace_essence;
	assert(instance->essence != NULL);
	instance->essence->dataspace_name = instance->instance->name();
	// look for possible configuration maps & init files
	// verify their exitence and accessibility.
	// go: cms.
	if(d_configurationMaps.size() != 0) {
		instance->essence->configuration_maps.append(readableExistingFiles(d_configurationMaps,
				instance->essence->dataspace_name));
	}
	// go: ifiles
	if(d_initFiles.size() != 0) {
		instance->essence->initialization_files.append(readableExistingFiles(d_initFiles,
				instance->essence->dataspace_name));
	}
}

QList<QFileInfo> SDM::readableExistingFiles(QHash<QString,QString> &pool,
		QString &key) {
	QList<QFileInfo> result;
	if(pool.size() > 0) {
		QStringList possible_files = pool.values(key);
		QListIterator<QString> iter(possible_files);
		while(iter.hasNext()) {
			QFileInfo stub(iter.next());
			if(stub.exists() && stub.isReadable()) {
				result.append(stub);
			}
		}
	}
	return result;

}

void SDM::loadAvailableRessources() {
	// go for init files.
	QVariant if_vals = settings_manager->value(SDM_INITFILES_KEY);
	if(!if_vals.isNull()) {
		QHash<QString,QVariant> if_vals_s1 = if_vals.toHash();
		QHashIterator<QString,QVariant> iter(if_vals_s1);
		while(iter.hasNext()) {
			iter.next();
			if(!iter.value().isNull()) {
				d_initFiles.insert(iter.key(),iter.value().toString());
			}
		}
	}
	// go for configuration maps
	QVariant cm_vals = settings_manager->value(SDM_CONFIGMAPS_KEY);
	if(!cm_vals.isNull()) {
		QHash<QString,QVariant>	cm_vals_s1 = cm_vals.toHash();
		QHashIterator<QString,QVariant> cm_iter(cm_vals_s1);
		while(cm_iter.hasNext()) {
			cm_iter.next();
			if(!cm_iter.value().isNull()) {
				d_configurationMaps.insert(cm_iter.key(),cm_iter.value().toString());
			}
		}
	}
}

QList<QString> SDM::availableDataspaces() {
	QStringList result;
	if(dataspaces.size() > 0 ) {
		QListIterator<sdm_dataspace_instance*> iter(dataspaces);
		while(iter.hasNext()) {
			result.append(iter.next()->essence->dataspace_name);
		}
	}
	return result;
}

/*
 * StmtComponent interface
 */

void SDM::stmtc_slot_init() {

}

void SDM::stmtc_slot_resolveDependencies() {

}

void SDM::stmtc_slot_receiveDependencies(QList<StmtComponent*> list) {

}

void SDM::stmtc_slot_setVerbosity(enum StmtComponent::VerbosityLevel vlevel) {

}

void SDM::stmtc_slot_shutdown() {

}

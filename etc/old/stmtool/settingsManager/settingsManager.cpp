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

#include "settingsManager.h"

settingsManager::settingsManager() {
	settings = NULL;
	settingsPath = NULL;
}

settingsManager::~settingsManager() {
	settings->sync();
}

eStmError settingsManager::init() {
	settings = new QSettings(QSettings::IniFormat,QSettings::UserScope,"jens.o.john","stmTool");
	if (settings)
		return OK;
	else
		return ERR_FATAL;
}


QVariant settingsManager::value(const QString & key) {
	if (this->settings->contains(key)) {
		return this->settings->value(key);
	} else {
		return this->makeDefaultValue(key);
	}
	return QVariant();
}

void settingsManager::setValue(const QString & key, const QVariant & value) {
	this->settings->setValue(key,value);
}

QVariant settingsManager::makeDefaultValue(const QString & key) {
	if(key == QString("baseWindow/allowFullscreen")) {
		this->setValue(key,QVariant(true));
		return this->value(key);
	}

	if(key == QString("log/logpath")) {
		this->setValue(key,QVariant(QString("/home/joj/workspace/STM/logs")));
		return this->value(key);
	}

	if(key == QString("devices/path")) {
			this->setValue(key,QVariant(QString("./devices")));
			return this->value(key);
	}

	if(key == QString("settings/path")) {
			this->setValue(key,QVariant(QString(".")));
			return this->value(key);
	}

	if(key == QString("viewers/path")) {
			this->setValue(key,QVariant(QString("./viewers")));
			return this->value(key);
	}

	if(key == QString("devices/flags/forceShutdown")) {
			this->setValue(key,QVariant(false));
			return this->value(key);
	}

	return QVariant();
}

QStringList settingsManager::allKeys() {
	return this->settings->allKeys();
}

void settingsManager::deleteValue(const QString & key) {
	this->settings->remove(key);
}

void settingsManager::stmtc_slot_init() {
}

void settingsManager::stmtc_slot_shutdown() {
}

void settingsManager::stmtc_slot_setVerbosity(enum StmtComponent::VerbosityLevel vlevel) {
}

void settingsManager::stmtc_slot_resolveDependencies() {
}

void settingsManager::stmtc_slot_receiveDependencies(QList<StmtComponent*> list) {

}

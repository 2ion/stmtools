#include "CSettingsManager.h"

CSettingsManager::CSettingsManager() {
	settings = NULL;	
}

CSettingsManager::~CSettingsManager() {
	delete settings;
}

int
CSettingsManager::set_value(const QString &key, const QVariant &val) {
	settings->setValue(key, val);
}

int
CSettingsManager::delete_value(const QString &key) {
	settings->remove(key);
}

QVariant
CSettingsManager::value(const QString &key) {
	if (settings->contains(key))
		return settings->value(key);
	else {
		#define XIM(k,v) if ((k) == key) return (v);
		#include "XI_CSettingsManager.h"
		#undef XIM
	}
	return QVariant();
}

QStringList
CSettingsManager::keys() {
	return settings->allKeys();
}

void
CSettingsManager::slot_init() {
	settings = new QSettings(QSettings::IniFormat,
		QSettings::UserScope,
		STMT_APPMAIL,
		STMT_APPNAME);
	Q_ASSERT(settings != NULL);
}

void
CSettingsManager::slot_shutdown() {
	settings->sync();
	disconnect();
}

void
CSettingsManager::slot_resolveDependencies() {
}

void CSettingsManager::slot_receiveDependencies(QList<const Component*> &cs) {
}

void
CSettingsManager::set_default_values() {
}



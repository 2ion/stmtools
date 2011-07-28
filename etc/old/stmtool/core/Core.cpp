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

#include "Core.h"

Core::Core() {
	/* DEPRECATED
	this->coreID.author = new QString(_INFO_VERSION_);
	assert(this->coreID.author != NULL);
	this->coreID.version = new QString(_INFO_AUTHORS_);
	assert(this->coreID.version != NULL);
	*/
}

Core::~Core() {
	this->loggerInstance->log(QString("~Core::Core() -> terminating components ..."),this->coreLogID);
	this->uinit_SDM();
	this->loggerInstance->log(QString("~Core::Core() -> uinit_SDM() completed."),this->coreLogID);
	this->uinit_devMgr();
	this->loggerInstance->log(QString("~Core::Core() -> uinit_devMgr() completed."),this->coreLogID);
	this->uinit_setMgr();
	this->loggerInstance->log(QString("~Core::Core() -> uninit_setMgr() completed."),this->coreLogID);
	this->uinit_viewMgr();
	this->loggerInstance->log(QString("~Core::Core() -> uninit_viewMgr() completed."),this->coreLogID);
	this->uinit_GUI();
	this->loggerInstance->log(QString("~Core::Core() -> uinit_GUI() completed."),this->coreLogID);
	this->uinit_logging();
}

void Core::init(QApplication* appObject) {
	if(appObject) {
		qDebug() << "Core::init() -> Arguments are valid.";
		this->appObject = appObject;
		this->init_establishSetMgr();
		qDebug() << "Core::init() -> SettingsManager has been instanziated.";
		this->init_establishLogging(this->setManager);
		qDebug() << "Core::init() -> Relayed logging to Sherlog.";
		this->init_establishGUI(this->setManager,this);
		this->init_establishDevMgr(this->loggerInstance,this->setManager,this->baseWin);
		this->init_establishSDM(this->loggerInstance,this->setManager,this->devManager);
		this->init_establishSSCS();
		this->init_installUser();
	}
}

void Core::init_establishSetMgr() {
	this->setManager = new settingsManager();
	assert(this->setManager != NULL);
	this->setManager->init();
	this->setManager->setValue(QString("app/cwd"),QVariant(this->appObject->applicationDirPath()));
	this->setManager->setValue(QString("app/version"),QVariant(QString(_INFO_VERSION_)));
}

void Core::init_establishLogging(settingsManager* setmgr) {
	qDebug() << "Core::init_establishLogging()";
	QString logDir = setmgr->value(QString("log/logpath")).toString();
	QString &logRef = logDir;
	this->loggerInstance = new Sherlog(const_cast<const QString&>(logDir));
	assert(this->loggerInstance != NULL);
	qDebug() << "Core::init_establishLogging() -> About to call Sherlog::getLogId()";
	this->coreLogID = this->loggerInstance->getLogId(QString(QString("stmCore version") + QString(_INFO_VERSION_)));
	qDebug() << "Core::init_establishLogging() -> Got logId.";
	this->loggerInstance->log(QString("Logging has been set up."),this->coreLogID);
}

void Core::init_establishGUI(settingsManager* setmgr,Core* instance) {
	this->loggerInstance->log(QString("init_establishGUI() -> entered."),this->coreLogID);
	this->baseWin = new baseWindow();
	assert(this->baseWin != NULL);
	this->loggerInstance->log(QString("init_establishGUI() -> baseWindow created."),this->coreLogID);
	this->baseWin->init(setmgr,this->loggerInstance);
	this->baseWin->show();
}

void Core::init_establishDevMgr(Sherlog* loggerInstance, settingsManager* setMgr, baseWindow* basewin) {
	this->devManager = new deviceManager(loggerInstance,setMgr,basewin);
	assert(this->devManager != NULL);
	if (this->devManager) {
		this->devManager->init();
		this->baseWin->registerDeviceManager(this->devManager);
	}
}

void Core::init_establishSDM(Sherlog *loggerInstance,
		settingsManager *setMgr,
		deviceManager *devMgr) {
	this->scan_data_manager = new SDM(this->loggerInstance,this->devManager,this->setManager);
	assert(this->scan_data_manager != NULL);
	if(this->scan_data_manager) {

	}
}

void Core::init_installUser() {
	this->loggerInstance->log(QString("init_installUser() -> Going to enter main loop."),this->coreLogID);
	this->appObject->exec();
}

void Core::init_establishSSCS() {
	connect(this->baseWin,SIGNAL(signal_quitApplication(QObject*,QString)),this,SLOT(slot_quit(QObject*,QString)));
	this->baseWin->slot_setScanDataManager(this->scan_data_manager);
}

void Core::uinit_GUI() {
	// TODO: ~Core() breaks hereby.
	this->loggerInstance->log(QString("uinit_GUI() -> entered."),this->coreLogID);
	delete this->baseWin;
}

void Core::uinit_devMgr() {
	this->loggerInstance->log(QString("uinit_devMgr() -> entered."),this->coreLogID);
	delete this->devManager;
}

void Core::uinit_logging() {
	this->loggerInstance->log(QString("uinit_logging() -> entered."),this->coreLogID);
	this->loggerInstance->releaseLogId(this->coreLogID);
}

void Core::uinit_setMgr(){
	this->loggerInstance->log(QString("uinit_setMgr() -> entered."),this->coreLogID);
	delete this->setManager;
}

void Core::uinit_viewMgr() {

}

void Core::uinit_SDM() {
	this->loggerInstance->log(QString("uinit_SDM() -> entered."),this->coreLogID);
	delete this->scan_data_manager;
}

Sherlog* Core::logInstance() {
	return this->loggerInstance;
}

void Core::slot_quit(QObject* quitter, QString message) {
	QString part1("Core::slot_quit() has been called.\nCaller: ");
	QString part2(quitter->metaObject()->className());
	QString part3(QString("\nMessage: ") + message);
	this->loggerInstance->log(QString(part1 + part2 + part3),this->coreLogID);
	// FIXME: segfault due this call. IMPROVE: eventually fixed.
	// this->appObject->exit(0);
	this->appObject->quit();
}

void Core::stmtc_slot_init() {

}

void Core::stmtc_slot_shutdown() {

}

void Core::stmtc_slot_resolveDependencies() {

}

void Core::stmtc_slot_receiveDependencies(QList<StmtComponent*> list) {

}

void Core::stmtc_slot_setVerbosity(enum StmtComponent::VerbosityLevel vlevel) {

}

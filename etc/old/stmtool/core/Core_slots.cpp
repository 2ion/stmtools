/*! \file Core_slots.cpp
 * \brief Implements the slots of Core.
 *
 */

#include "Core.h"

void Core::slot_quit(QObject* quitter, QString message) {
	QString part1("Core::slot_quit() has been called.\nCaller: ");
	QString part2(quitter->metaObject()->className());
	QString part3(QString("\nMessage: ") + message);
	this->loggerInstance->log(QString(part1 + part2 + part3),this->coreLogID);
	// FIXME: segfault due this call. IMPROVE: eventually fixed.
	// this->appObject->exit(0);
	this->appObject->quit();
}

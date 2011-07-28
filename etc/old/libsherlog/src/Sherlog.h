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

/*!
 * \class Sherlog
 * \brief Provides logging facilities for stmtool. Implemented using a shared library.
 *
 * Sherlog is a component of stmtool doing all logging work.
 * Within the library, there exist log channels (represented by struct logChannel), each
 * being assigned to a logClient (struct logClient) being its opener. A log client is capable
 * of keeping multiple channels.
 *
 * Sherlog uses log files going to be created in a particular folder on the filesystem. This
 * folder is required to be specified via the constructors of the pattern Sherlog::Sherlog(*)
 * or via calling Sherlog::initialize(const QString&). If the library is not being set up,
 * Sherlog::status() will return the UNCALLED value.
 *
 * \fn int Sherlog::getLogId(const char*)
 * \brief Wrapper for Sherlog::getLogId(const QString&)
 *
 * Its return value can be evaluated by comparison with the macros prefixed with
 * SHERLOG_GETLOGID.
 *
 * \fn int Sherlog::getLogId(const QString &clientName)
 * \brief Where a log channel can be obtained.
 * \param clientName Identification of the log file owner.
 * \return The logID for use with several methods.
 *
 *	A client calling himself by clientName can register a log channel being addressed
 *  using the returned logID.
 *
 *  \fn bool Sherlog::releaseLogId(int logID)
 *  \brief Closes a log channel and renders its logID invalid.
 *	\return true if no error occured.

 *  If a client wishes to release, i.e. close a log channel, it has to submit the fitting
 *  logID. If the file has been successfully flushed and closed, TRUE is returned.
 *
 * \fn int Sherlog::log(QString logMessage, int logID)
 * \brief Logs a message to a log channel.
 * \param logMessage The log message.
 * \param logID The target channel's logID.
 *
 *
 */

#ifndef SHERLOG_H_
#define SHERLOG_H_
#include <QtDebug>
#include <QtGui/QTextDocument>
#include <QtGui/QTextCursor>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <QtCore/QString>
#include <QtCore/QMap>
#include <QtCore/QList>
#include <QtCore/QListIterator>
#include <QtCore/QMapIterator>
#include <QtCore/QDateTime>
#include <QtCore/QTextStream>
#include <QtCore/QThread>
#include <QtCore/QVariant>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cassert>
#include "global_header.h"

#ifndef _VERSION_
#define _VERSION_ ("2.0b1")
#endif
#ifndef _VERSION_
#define _AUTHOR_ ("2010 by Jens Oliver John <jens.o.john@gmail.com>")
#endif

/*! @name Return codes of Sherlog::getLogId() */
//@{
#ifndef SHERLOG_GETLOGID__FALSEARG
#define SHERLOG_GETLOGID__FALSEARG 				(-1)
#endif

#ifndef SHERLOG_GETLOGID__UNCALLED
#define SHERLOG_GETLOGID__UNCALLED 				(-2)
#endif

#ifndef SHERLOG_GETLOGID__ERROR
#define SHERLOG_GETLOGID__ERROR 				(-3)
#endif

#ifndef SHERLOG_GETLOGID__RESSOURCE_OCCUPIED
#define SHERLOG_GETLOGID__RESSOURCE_OCCUPIED	(-4)
#endif
//@}

/*! @name Return codes of Sherlog::log() */
//@{
#ifndef SHERLOG_LOG__FALSEID
#define SHERLOG_LOG__FALSEID					(-1)
#endif

#ifndef SHERLOG_LOG__EMPTYMSG
#define SHERLOG_LOG__EMPTYMSG					(-2)
#endif

#ifndef SHERLOG_LOG__OK
#define SHERLOG_LOG__OK							(0)
#endif
//@}

#ifndef SHERLOG_FILENAME_DIVISOR
#define SHERLOG_FILENAME_DIVISOR				('-')
#endif


#ifndef SHERLOG_FILENAME_SUFFIX
#define SHERLOG_FILENAME_SUFFIX					(".log")
#endif

#ifndef SHERLOG_LOGFILE_SUFFIX
#define SHERLOG_LOGFILE_SUFFIX					("# Closed #")
#endif

struct logChannel;
struct logClient;

struct logChannel {
	QFile *logFile;
	QTextStream logStream;
	struct logClient *parent;
	logChannel(QFile *file) {
		if(file) {
			logFile = file;
			logFile->open(QIODevice::ReadWrite | QIODevice::Text);
			logStream.setDevice(logFile);
		} else {
			logFile = NULL;
		}
	}
	~logChannel() {
		logStream.flush();
		logStream.device()->close();
		//delete logFile;
	}
};

struct logClient {
	QString clientName;
	QMap<int,struct logChannel*> logChannels;

	void addChannel(int logId, struct logChannel *ch) {
		if(ch)
			ch->parent = this;
			logChannels.insert(logId,ch);
	}
};

class SL_EXPORT Sherlog {
public:
	enum SherlogLibraryStatus {
		CALLED,
		UNCALLED
	};

	Sherlog();
	~Sherlog();
	Sherlog(const char* logDirectory);
	Sherlog(const QString & logDirectory);
	//Sherlog(QString &logDirectory);
	enum SherlogLibraryStatus status();
	int getLogId(const char* clientName);
	int getLogId(QString clientName);
	bool releaseLogId(int logID);
	int log(QString logMessage, int logID);
	void initialize(const QString &logDirectory);
	QTextDocument* readLog(int logID);
	QList<int> activeLogs();
	QMap<int,QFileInfo> clientLogs(const QString &name);
	QStringList activeClients();
	QString clientName(int logId);
	QFileInfo logFile(int logId);

private:
	struct logClient* clientExists(const QString &name);
	struct logClient* getClient(const QString &name);
	QFile* getFile(struct logClient *client);
	struct logChannel* getChannel(int logId);
	void printMessageHeader(struct logChannel *channel, int importance = -1);
	QString timeStamp();
	QString datedTimeStamp();

	int nextId;
	QDir my_logDirectory;
	enum SherlogLibraryStatus my_status;
	QList<struct logClient*> my_clients;
	QMap<int,struct logChannel*> my_channelTable;

};

#endif /* SHERLOG_H_ */

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

#include "Sherlog.h"

Sherlog::Sherlog() {
	this->nextId = 0;
}

Sherlog::Sherlog(const char* logDirectory) {
	assert(logDirectory != NULL);
	this->nextId = 0;
	this->initialize(QString(logDirectory));
}

Sherlog::Sherlog(const QString &logDirectory) {
	this->nextId = 0;
	this->initialize(logDirectory);
}

/*
Sherlog::Sherlog(QString &logDirectory) {
	this->nextId = 0;
	this->initialize(QString(logDirectory));
}
*/

Sherlog::~Sherlog() {
	QList<int> ids = my_channelTable.keys();
	QListIterator<int> ids_iter(ids);
	while(ids_iter.hasNext()) {
		int lid = ids_iter.next();
		log(QString(SHERLOG_LOGFILE_SUFFIX),lid);
		releaseLogId(ids_iter.next());
	}
}

void Sherlog::initialize(const QString &logDirectory) {
	my_logDirectory.setPath(logDirectory);
	if (my_logDirectory.exists() && my_logDirectory.isReadable()) {
		my_status = CALLED;
	} else {
		my_status = UNCALLED;
	}
}

enum Sherlog::SherlogLibraryStatus Sherlog::status() {
	return my_status;
}

int Sherlog::getLogId(const char* clientName) {
	return getLogId(QString(clientName));
}

int Sherlog::getLogId(QString clientName) {
	if(my_status == UNCALLED)
		return SHERLOG_GETLOGID__UNCALLED;
	if(clientName.isEmpty())
		return SHERLOG_GETLOGID__FALSEARG;
	struct logClient *client = getClient(clientName);
	QFile *client_file = getFile(client);
	if(client_file == NULL)
		return SHERLOG_GETLOGID__RESSOURCE_OCCUPIED;
	struct logChannel* client_channel = new struct logChannel(client_file);
	client->addChannel(nextId, client_channel);
	my_channelTable.insert(nextId,client_channel);
	return nextId++;
}

struct logClient* Sherlog::getClient(const QString &name) {
	struct logClient *c_ptr = clientExists(name);
	if(c_ptr != NULL)
		return c_ptr;
	c_ptr = new struct logClient;
	assert(c_ptr);
	c_ptr->clientName = name;
	my_clients.append(c_ptr);
	return c_ptr;
}

QStringList Sherlog::activeClients() {
	QStringList result;
	if((my_status == UNCALLED) || (my_clients.isEmpty()))
		return result;
	QListIterator<struct logClient*> c_iter(my_clients);
	while(c_iter.hasNext()) {
		result.append(c_iter.next()->clientName);
	}
	return result;
}

QMap<int,QFileInfo> Sherlog::clientLogs(const QString &name) {
	QMap<int,QFileInfo> result;
	if((my_status == UNCALLED) || (my_clients.isEmpty()) || (name.isEmpty()))
		return result;
	struct logClient *c = clientExists(name);
	if(c == NULL)
		return result;
	QMapIterator<int,struct logChannel*> ch_iter(c->logChannels);
	while(ch_iter.hasNext()) {
		ch_iter.next();
		QFileInfo fi_item(*const_cast<const QFile*>(ch_iter.value()->logFile));
		result.insert(ch_iter.key(),fi_item);
	}
	return result;
}

QFile* Sherlog::getFile(struct logClient *client) {
	QString filename = client->clientName + SHERLOG_FILENAME_DIVISOR + datedTimeStamp() + \
			QString(SHERLOG_FILENAME_SUFFIX);
	int replica = 0;
	while(my_logDirectory.exists(filename + '.' + QVariant(replica).toString())) {
		replica++;
	}
	filename = filename + '.' + QVariant(replica).toString();
	QFile *theFile = new QFile(my_logDirectory.absoluteFilePath(filename));
	return theFile;
}

struct logClient* Sherlog::clientExists(const QString &name) {
	if(my_clients.isEmpty())
		return NULL;
	QListIterator<struct logClient*> citer(my_clients);
	while(citer.hasNext()) {
		struct logClient *ptr = citer.next();
		if(ptr->clientName == name)
			return ptr;
	}
	return NULL;
}

int Sherlog::log(QString logMessage,int logId) {
	if(logMessage.isEmpty())
		return SHERLOG_LOG__EMPTYMSG;
#ifdef SHERLOG_DEBUG
	qDebug() << "Message: " << logMessage << "\"by " << logId;
#endif
	struct logChannel *target = getChannel(logId);
	if(target == NULL)
		return SHERLOG_LOG__FALSEID;
	printMessageHeader(target,-1);
	target->logStream << logMessage << '\n';
	target->logStream.flush();
	return SHERLOG_LOG__OK;
}

void Sherlog::printMessageHeader(struct logChannel *channel, int importance) {
	QString Header = '[' + datedTimeStamp() + ']' + '\n';
	channel->logStream << Header;
	//channel->logStream.flush();
}

struct logChannel* Sherlog::getChannel(int logId) {
	if(!my_channelTable.contains(logId))
		return NULL;
	return my_channelTable.value(logId);
}

bool Sherlog::releaseLogId(int logID) {
	struct logChannel* target = getChannel(logID);
	if(target == NULL)
		return false;
	log(QString(SHERLOG_LOGFILE_SUFFIX),logID);
	target->parent->logChannels.remove(logID);
	delete target;
	return true;
}

QString Sherlog::timeStamp() {
	return QDateTime::currentDateTime().toString("hh-mm-ss-z");
}

QString Sherlog::datedTimeStamp() {
	return QDateTime::currentDateTime().toString("dd-MM-yyyy--hh-mm-ss-z");
}

QTextDocument* Sherlog::readLog(int logID) {
	struct logChannel *target = getChannel(logID);
	if(target == NULL) {
		QTextDocument();
	}
	QTextStream reader(target->logFile);
	qint64 pos = reader.pos();
	reader.seek(0);
	QTextDocument* document = new QTextDocument();
	QTextCursor* writer = new QTextCursor(document);
	writer->insertText(reader.readAll());
	reader.seek(pos);
	delete writer;
	return document;
}

QList<int> Sherlog::activeLogs() {
	return my_channelTable.keys();
}

QString Sherlog::clientName(int logId) {
	QString result;
	struct logChannel *sibling = getChannel(logId);
	if(sibling != NULL)
		result = sibling->parent->clientName;
	return result;
}

QFileInfo Sherlog::logFile(int logId) {
	struct logChannel *ch = getChannel(logId);
	if(ch == NULL)
		return QFileInfo("");
	return QFileInfo(*ch->logFile);
}

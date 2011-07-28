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

#ifndef MYUNDOER_H_
#define MYUNDOER_H_

#include <QtCore/QObject>
#include <QtCore/QStack>

class UndoerStatus;
class MyUndoStack;
class MyUndoer;

class UndoerStatus {
public:
	UndoerStatus(const QString &title) {
		myTitle = title;
	}
	~UndoerStatus() {
	}
	QString title() {
		return myTitle;
	}
private:
	QString myTitle;
};

class MyUndoer : public QObject {
	Q_OBJECT
public slots:
	virtual void receiveStatus(UndoerStatus*) = 0;
signals:
	void requestStatus();
	void sendStatus(UndoerStatus*);

};

class MyUndoStack : public QObject {
	Q_OBJECT
public:
	MyUndoStack(MyUndoer *client) {
		setClient(client);
	}
	~MyUndoStack() {
		disconnect(0,0,0,0);
	}
	MyUndoer* client() {
		return my_undoer;
	}
	MyUndoer* setClient(MyUndoer* client) {
		my_undoer = client;
		connectSS();
		if(my_undoer != NULL)
			return my_undoer;
	}
public slots:
	void requester() {
		emit undo(my_stack.pop());
	}
	void receiver(UndoerStatus* input) {
		my_stack.push(input);
	}
signals:
	void undo(UndoerStatus*);
private:
	void connectSS() {
		connect(this,SIGNAL(undo(UndoerStatus)),
				my_undoer,SLOT(receiveStatus(UndoerStatus)));
		connect(my_undoer,SIGNAL(requestStatus()),
				this,SLOT(requester()));
		connect(my_undoer,SIGNAL(sendStatus(UndoerStatus)),
				this,SLOT(receiver(UndoerStatus)));
	}
	QStack<UndoerStatus*> my_stack;
	MyUndoer *my_undoer;
};




#endif /* MYUNDOER_H_ */

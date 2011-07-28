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

#include "logViewDialog.h"

void logViewDialog::slot_refreshList() {
	this->buildList(this->shownLog);
}

void logViewDialog::slot_refreshLogView(QListWidgetItem* item) {
	this->loggerInstance->log(QString("slot::refreshLogView(QListWidgetItem*)"),this->privateLogID);
	logLWI* cc = dynamic_cast<logLWI*>(item);
	QTextDocument* doc = this->loggerInstance->readLog(cc->logID());
	this->shownLog = cc->logID();
	this->ui.lbl_client_data->setText(this->loggerInstance->clientName(cc->logID()));
	this->ui.le_logfilepath->setText(this->loggerInstance->logFile(cc->logID()).absoluteFilePath());
	this->ui.textEdit->setDocument(doc);
}

void logViewDialog::slot_submitMessage() {
	if(this->shownLog < 0) {
		QMessageBox::warning(this,QString("Submit message"),QString("There has been no valid channel selected."));
	} else {
		QString text = QInputDialog::getText(this,QString("Submit message to channel ") + QVariant(this->shownLog).toString(),QString("You shall enter your message. Now."));
		if(text == QString("")) {
		QMessageBox::information(this,QString("Annotation"),QString("You have typed nothing. This will make nothing happen."));
		} else {
			this->loggerInstance->log(QString("<Annotation>\n") + text,this->shownLog);
			this->buildList(this->shownLog);
		}
	}
}

void logViewDialog::slot_printLog() {
	if(this->shownLog < 0) {
			QMessageBox::warning(this,QString("Print log"),QString("There has been no valid channel selected."));
		} else {
			QPrinter* paintDevice = new QPrinter();
			QPrintDialog* dialog = new QPrintDialog(paintDevice,this);
			if(dialog->exec() == QDialog::Accepted) {
				this->ui.textEdit->print(paintDevice);
				delete paintDevice;
			}
		}
}

void logViewDialog::slot_browseLogDir() {
	logDirBrowser* dialog = new logDirBrowser(this->setMgr->value(QString("log/logpath")).toString());
	dialog->show();
}

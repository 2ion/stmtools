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

#ifndef BASEWINDOW_H
#define BASEWINDOW_H

/*! \file baseWindow.h
 * Implements baseWindow.
 *
 * \class baseWindow
 * \brief The application's main window wherefrom all user interaction is being done.
 *
 * \fn QProgressDialog* baseWindow::displayProgressDialog()
 * \brief Bestows an always properly aligned progress dialog unto the requester.
 * \deprecated If not used: 'pastebin'.
 *
 * \fn void baseWindow::registerDeviceManager(deviceManager*)
 * \brief Handles the signal/slot connections of deviceManager and baseWindow,
 * mainly in order to allow deviceManager to install the devices' widgets.
 *
 */

#include <QtGui/QMainWindow>
#include <QtGui/QApplication>
#include <QtGui/QMessageBox>
#include <QtGui/QWidget>
#include <QtGui/QDockWidget>
#include <QtGui/QSplitter>
#include <QtGui/QToolBox>
#include <QtGui/QProgressDialog>
#include <QtCore/QHash>
#include <QtCore/QHashIterator>
#include <core/Core.h>
#include <settingsManager/settingsManager.h>
#include <deviceManager/deviceManager.h>
#include <gui/aboutDialog/aboutDialog.h>
#include <gui/prefDialog/prefDialog.h>
#include <gui/logViewDialog/logViewDialog.h>
#include <gui/deviceSelector/deviceSelector.h>
#include <gui/homeWidget/homeWidget.h>
#include <gui/colorScales/ColorScaleViewer.h>
#include <gui/colorScales/MyColorScale.h>
#include <general/DebugMacros.h>
#include <sdm/SDM.h>
#include <Sherlog.h>
#include "ui_baseWindow.h"

class baseWindow : public QMainWindow
{
    Q_OBJECT

public:
    baseWindow(QWidget *parent = 0);
    ~baseWindow();
    void init(settingsManager* setMgr,Sherlog* loggerInstance);
    void registerDeviceManager(class deviceManager* devMgr);
    void unregisterDeviceManager();
    void displayErrorBox(QString title, QString message);
    void displayInfoBox(QString title, QString message);
    QProgressDialog* displayProgressDialog();

public slots:
	void slot_setControllingWidget(QWidget*);
	void slot_setConfigurationWidgets(QHash<QString*,QWidget*>*);
	void slot_setScanDataManager(class SDM*);
	//void slot_establishNewViewer();

signals:
	void signal_quitApplication(QObject*,QString);

private:
	void gui_actions_connect();
	void gui_layout_installation();

    Ui::baseWindowClass ui;
    QApplication* appObject;
    class Core* coreInstance;
    Sherlog* loggerInstance;
    class settingsManager* setMgr;
    class deviceManager* devMgr;
    class SDM *scan_data_manager;
    int baseWinLogId;
    QSplitter *layout_splitter;
    QToolBox *layout_configurationWidgets;

private slots:
	/*! @name UI slots */
	//@{
	void slot_quitApplication();
	void slot_showAboutQt();
	void slot_showAboutDialog();
	void slot_showPreferencesDialog();
	void slot_showFullScreen();
	void slot_showLogViewDialog();
	void slot_showDeviceSelector();
	void slot_showColorScaleViewer();
	//@}
};

typedef class baseWindow baseWindow;

#endif // BASEWINDOW_H

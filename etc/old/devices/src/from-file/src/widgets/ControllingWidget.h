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

#ifndef CONTROLLINGWIDGET_H
#define CONTROLLINGWIDGET_H

#include <QtGui/QWidget>
#include <QtCore/QByteArray>
#include <QtGui/QFileDialog>
#include <QtGui/QImage>
#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>
#include <QtCore/QFile>
#include <QtCore/QSize>
#include <QtXml/QXmlStreamWriter>
#include <QtWebKit/QWebView>
#include "ui_ControllingWidget.h"

#include <src/mkxml/mkxml.h>
#include <src/mkxml/GMakeXml.h>

#define MKXML_IMAGE_FILTER (QString("Supported images (*.bmp *.jpg *.jpeg *.mng *.png *.pbm *.pgm *.ppm *.tiff *.tif *.xbm *.xpm);; All files (*.*)"))
#define MKXML_IMAGE_TOOLTIP1 ("<html><head><meta name=\"qrichtext\" content=\"1\" /></head><body><img  width=\"300\" src=\"")
#define MKXML_IMAGE_TOOLTIP3 ("\" /></body></html>")

class ControllingWidget : public QWidget
{
    Q_OBJECT

public:
    ControllingWidget(QWidget *parent = 0);
    ~ControllingWidget();

private:
    void connectSS();
    void mxf1_deriveImageProperties(const QString &);

    Ui::ControllingWidgetClass ui;
    QByteArray mkxml_last_result;

private slots:
	void slot_checkb_mxf1_useImage_toggle(bool);
	void slot_tb_mxf1_browseImage_clicked();
	void slot_mkxml_go();
	void slot_mkxml_saveResults();
};

#endif // CONTROLLINGWIDGET_H

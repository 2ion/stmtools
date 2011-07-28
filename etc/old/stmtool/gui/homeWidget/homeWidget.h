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

#ifndef HOMEWIDGET_H
#define HOMEWIDGET_H

#include <QtGui/QWidget>
#include "ui_homeWidget.h"

/*!
 * \file homeWidget.h
 * Implements homeWidget.
 *
 * \class homeWidget
 * \brief The fancy widget presented as baseWindow's initial background.
 * \note To be held simple in order to decrease costs of rendering.
 * \todo Neverending quest: Design the transcendent home widget!
 */

class homeWidget : public QWidget
{
    Q_OBJECT

public:
    homeWidget(QWidget *parent = 0);
    ~homeWidget();


private:
    Ui::homeWidgetClass ui;
};

#endif // HOMEWIDGET_H

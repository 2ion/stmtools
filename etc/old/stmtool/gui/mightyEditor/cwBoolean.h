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

#ifndef CWBOOLEAN_H
#define CWBOOLEAN_H

#include <QtGui/QWidget>
#include "ui_cwBoolean.h"

/*!
 * \class cwBoolean
 * \brief Provides input method for boolean values. Part of mightyEditor.
 * \todo Use it.
 */

class cwBoolean : public QWidget
{
	Q_OBJECT
public:
	cwBoolean(QWidget *parent = 0);
	~cwBoolean();
signals:
	void signal_validValue(QVariant);
private:
	Ui::cwBooleanClass ui;
private slots:
	void slot_toogle(bool value);
};

#endif // CWBOOLEAN_H

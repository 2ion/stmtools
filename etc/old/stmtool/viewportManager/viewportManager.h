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

#ifndef VIEWPORTMANAGER_H_
#define VIEWPORTMANAGER_H_
/*!
 * \file viewportManager.h
 * Related to viewportManager
 *
 * \class viewportManager
 * \brief A device provides raw data, and thi class' task is it
 * to make up some convenient data that the viewports can
 * render easily and apply different transformations on quickly.
 * For this purpose, the image format of CImg library comes
 * into use. Therefrom, viewportManager provides for every single
 * buffer having been made available through deviceManager a CImg<T>
 * class representation, where <T> is being determined by the buffer's
 * output format.
 */

#include <Qt>
#include <CImg.h>
#include <general/StmtComponent.h>

class viewportManager : public StmtComponent {
	Q_OBJECT
public:
	viewportManager();
	~viewportManager();
public slots:
	void stmtc_slot_init();
	void stmtc_slot_shutdown();
	void stmtc_slot_setVerbosity(enum StmtComponent::VerbosityLevel);
	void stmtc_slot_resolveDependencies();
	void stmtc_slot_receiveDependencies(QList<StmtComponent*>);
};

#endif /* viewportManager.h */

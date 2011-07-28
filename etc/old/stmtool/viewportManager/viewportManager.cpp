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

#include "viewportManager.h"

viewportManager::viewportManager() {
	cimg_library::CImg<unsigned char> image(500,400,1,3,0);
}

viewportManager::~viewportManager() {
}

void viewportManager::stmtc_slot_init() {

}

void viewportManager::stmtc_slot_shutdown() {

}

void viewportManager::stmtc_slot_resolveDependencies() {

}

void viewportManager::stmtc_slot_setVerbosity(enum StmtComponent::VerbosityLevel vlevel) {

}

void viewportManager::stmtc_slot_receiveDependencies(QList<StmtComponent*> list) {

}

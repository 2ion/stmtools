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

#include "CSKodak1.h"

CSKodak1::CSKodak1() {
	build();
}

CSKodak1::~CSKodak1() {
}

QHash<quint32,QColor> CSKodak1::colors() {
	return scale;
}

QHash<quint32,QColor>* CSKodak1::data() {
	return &scale;
}

quint32 CSKodak1::indizes() {
	return scale.size();
}

void CSKodak1::build() {

}

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

#ifndef PLACEHOLDER_H_
#define PLACEHOLDER_H_
/*!
 \file Placeholder.h
 \class Placeholder
 \brief A dummy filter used in FilterTable for holding place.
 */
#include <ComputationController/StackableFilter.h>

OF_STMBUF_T
class Placeholder : public StackableFilter {
public:
	Placeholder() {

	}

	~Placeholder() {

	}

	int filter(cimg_library::CImg<stmbuf_t> *data) {

	}

	stmt_lib::SFArgList* combine(QList<const StackableFilter<stmbuf_t>*> filters) {

	}

	stmt_lib::SFArgList arguments() {

	}

	void setArguments(stmt_lib::SFArgList arguments) {

	}

	QVariant tell(enum stmt_lib::SFRequisition req) {

	}

	quint32 id() {

	}
};

#endif /* PLACEHOLDER_H_ */

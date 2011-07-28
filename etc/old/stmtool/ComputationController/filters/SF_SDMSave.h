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

#ifndef SF_SDMSAVE_H_
#define SF_SDMSAVE_H_
/*!
 \file SF_SDMSave.h

 \class SF_SDMSave
 \brief Brings data from filter threads unto the SDM. Standard way to save data.
 \note Is not to be implement as a plugin, but provided through a SDM instance.
 */

#include <ComputationController/StackableFilter.h>

OF_STMBUF_T
class SF_SDMSave: public StackableFilter<stmbuf_t> {
public:
	SF_SDMSave();
	~SF_SDMSave();

	int filter(cimg_library::CImg<stmbuf_t> *data);
	stmt_lib::SFArgList* combine(QList<const StackableFilter<stmbuf_t>*> filters);
	stmt_lib::SFArgList arguments();
	void setArguments(stmt_lib::SFArgList arguments);
	QVariant tell(enum stmt_lib::SFRequisition req);
	quint32 id();
};

#endif /* SF_SDMSAVE_H_ */

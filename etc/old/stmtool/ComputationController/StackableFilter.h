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

#ifndef STACKABLEFILTER_H_
#define STACKABLEFILTER_H_
/*!
	\file StackableFilter.h
	\class StackableFilter
	\brief Interface for filters one can arrange within a FilterTable.

	\enum StackableFilter::SFRequisition
	\brief Questionaire for StackableFilter::tell().

	\struct StackableFilter::SFArgument
	\brief Holds information on an argument required by StackableFilter::filter().

	SFArgument does both hold the specification and value of an argument of
	StackableFilter::filter().<BR>
	The specification defines the valuetype, and how it is to be obtained.
	SFArgument can hold a input Widget for more complex user input, otherwise,
	according to its valuetype, an input method defined by the appliction will be used.
	
	\fn virtual int StackableFilter::filter(void *data, QList<struct SFArgument> args)
	\brief Make the implemented filter operate on data as the arguments in args specify.
	\todo Determine apppropriate valuetype of data.
*/

#include <QtPlugin>
#include <QtGlobal>
#include <QtCore/QVariant>
#include <QtCore/QList>
#include <CImg.h>
#include <general/StmtLib.h>

OF_STMBUF_T
class StackableFilter {
public:
	virtual int filter(cimg_library::CImg<stmbuf_t> *data) = 0;
	virtual stmt_lib::SFArgList* combine(QList<StackableFilter*> filters) = 0;
	virtual void setArguments(stmt_lib::SFArgList arguments) = 0;
	virtual stmt_lib::SFArgList arguments() = 0;
	virtual QVariant tell(enum stmt_lib::SFRequisition req) = 0;
	virtual quint32 id() = 0;
};

//nec Q_DECLARE_INTERFACE(StackableFilter, "StackableFilterInterface")

#endif /* STACKABLEFILTER_H_ */

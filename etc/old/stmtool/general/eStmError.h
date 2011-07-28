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

/*!
 * \file eStmError.h
 * \brief Declares enum eStmError.
 *
 * \enum eStmError
 * \brief A data type used to evaluate called function's
 * return values in a common way through stmtool.
 *
 * \todo By now, its usage turns out to be inconsistent. Rewriting
 * the source, it should be assured that every init-method uses it.
 * It's not close to any logging facility, either. Fix, fix.
 */

#ifndef ESTMERROR_H_
#define ESTMERROR_H_

enum eStmError {
	OK,
	OK_FIXED,
	ERR_WORKAROUND,
	ERR_FATAL,
	DEBUG_ERR_DUE_ARGUMENT,
	DEBUG_ERR_DUE_INSTANCIATION,
	ERR_PLUGIN_DIRECTORY_NOT_AVAILABLE
};

typedef enum eStmError eStmError;

#endif /* ESTMERROR_H_ */

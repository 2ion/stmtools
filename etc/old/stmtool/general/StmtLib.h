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

#ifndef STML_NAMESPACE
#define STML_NAMESPACE

namespace stmt_lib {

	enum SFRequisition {
		NAME = 0,					//!< QString: filter's short name
		DESCRIPTION = 1,			//!< QString: Useful description
		HELPDOC = 3,				//!< QString: Explicit description of the filter. May contain QML
		REPRESENTING_STRING = 5,	//!< QString: String wherethrough one can recognize the configuration status
		ICON = 6					//!< QIcon: Optional icon for display in filter table
	};

	enum StmBufValueType {
		FLOAT = 0,
		UNSIGNED_INT = 1,
		UNSIGNED_CHAR = 2,
		INT = 3,
		CHAR = 4
	};

	struct SFArgument {
		QVariant::Type type;	//!< QVariant::Invalid -> UI widget will be assumed.
		union {
			QWidget *Warg;		//!< If SFArgument::type == QVariant::Invalid, this should be an pointer upon an input widget.
			QVariant *Varg;		//!< If SFargument::type != QVariant::Invalid, this should be an pointer upon an valid QVariant.
		} value;
	};

	typedef QList<struct SFArgument> SFArgList;

} /* namespace StmtLib */

#endif

#ifndef OF_STMBUF_T
/*! stmbuf_t is the value type provided by a STM device */
#define OF_STMBUF_T template<typename stmbuf_t>
#endif

#ifndef SF_BUILTINS_DEFAULT_IDS
#define SF_BUILTINS_DEFAULT_IDS
/*! @name Filter IDs for builtin variants of StackedFilter. */
//@{
/*! Placeholder used in FilterTable */
#define SF_DFID_PLACEHOLDER 0
//@}

#endif


#ifndef FT_USERROLES
#define FT_USERROLES

//! In the FilterTable view implemention, if a cell has been initialized,
//! the data available on that field, a pointer to a StackableFilter instance,
//! will be accessible using FT_FILTERPTR as a Qt::Userrole.
#define FT_FILTERPTR 32

#endif

#ifndef CECHO
#define CECHO qCritical() << __FILE__ << __LINE__
#endif

#ifndef DECHO
#define DECHO qCritical() << __FILE__ << __LINE__
#endif



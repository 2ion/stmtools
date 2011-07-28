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

/*! \file main.cpp
 * Contains main() and is mainly being used to kick off an instance
 * of the Core class.
 * Farther, every single statically linked plugin DOES require a
 * Q_IMPORT_PLUGIN statement in main.cpp in order to be available
 * through QPluginLoader.
 *
 * \def RELATIVE_LIBSHERLOG_PATH
 * \brief Adds the path to libsherlog.so to the QApplication instance.
 *
 * This is necessary in order to relieve the user to edit his system's
 * ld.so configuration, i.e. where the linker looks for shared libraries.
 */

#include <QtDebug>
#include <QtGlobal>
#include <QApplication>
#include <QtPlugin>
#include <core/Core.h>

#define RELATIVE_LIBSHERLOG_PATH ("/../../libsherlog")

// Load statically linked plugins
// Color scales
Q_IMPORT_PLUGIN(colorScale_KODAK1)
// Devices
// Dataspaces

int main(int argc, char *argv[])
{
    QApplication qApplication(argc,argv);
    qApplication.setStyle("plastique");
    Core* c = new Core();
    Q_ASSERT(c != NULL);
    c->init(&qApplication);
    return 0;
}

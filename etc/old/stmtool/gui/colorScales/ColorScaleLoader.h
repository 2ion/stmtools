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

#ifndef COLORSCALELOADER_H_
#define COLORSCALELOADER_H_
#include <QtPlugin>
#include <QtDebug>
#include <QtCore/QObject>
#include <QtCore/QPluginLoader>
#include <QtCore/QObjectList>
#include <QtCore/QFileInfoList>
#include <QtCore/QDir>
#include <QtCore/QListIterator>
#include <QtCore/QList>
#include <QtCore/QLibrary>
#include <settingsManager/settingsManager.h>
#include <gui/colorScales/ColorScale.h>
#include <cassert>

/*!
 * \file ColorScaleLoader.h
 * Implements ColorScaleLoader.
 *
 * \class ColorScaleLoader
 * \brief Makes color scales loaded either from statically linked
 * or dynamically loaded plugins or from files written by
 * ColorScaleViewer and makes them available to user and components.
 *
 * These plugins use the interface defined by ColorScale, which has
 * been designed to be as simple as possible. Hence, it is 'used'
 * only by ColorScaleLoader to identify color scale plugins through
 * a qobject_cast<>() invocation.
 * Interternally, every ColorScale instance will, if it is requested
 * for application, be wrapped up by an instance of MyColorScale providing
 * lots of convenience methods for user and component interaction.
 *
 * \todo Make it load dynamically loaded and statically linked plugins
 * \todo Make it somewhere available, possibly through settingsManger (
 * may produce crap, I've never tried to store a POINTER therein).
 * \todo Make it use SDM for color scale defintion import.
 *
 */

struct csl_plugin_representation {

};

/*
 * TODO: Concentrate plugin loading tasks within
 * a class named PluginManager.
 */

/*!
 * Provides built-in color scales, or loads them from a plugin.
 */
class ColorScaleLoader : public QObject {
	Q_OBJECT
public:
	/*!
	 * @param setMgr Tells where to look for color scale plugins.
	 */
	ColorScaleLoader(settingsManager *setMgr);
	~ColorScaleLoader();

	QList<QString> scales();
	/*!
	 * @return The requested scale, if it exists.
	 * @param preference If 0, statically linked scales
	 * of the same name will be preferred;
	 * if 1, dynamically loaded scales will be preferred;
	 * if > 1, if scales with the same name do exist,
	 * NULL will be returned.
	 */
	QHash<QString,ColorScale*> scale(const QString &name, char preference = 0);

public slots:
	void slot_reloadInstances();

private:
	void loadStaticInstances();
	void loadDynamicInstances();

	QList<ColorScale*> static_instances;
	QPluginLoader *static_loader;
	QList<ColorScale*> dynamic_instances;
	QList<QPluginLoader*> dynamic_loaders;
	settingsManager *my_settingsManager;
};


#endif /* ColorScaleLoader.h */

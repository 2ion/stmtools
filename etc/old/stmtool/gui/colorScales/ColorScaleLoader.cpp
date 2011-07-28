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

#include "ColorScaleLoader.h"

ColorScaleLoader::ColorScaleLoader(settingsManager *setMgr) {
	assert(setMgr != NULL);
	this->my_settingsManager = setMgr;
	this->static_loader = NULL;
	loadStaticInstances();
}

ColorScaleLoader::~ColorScaleLoader() {
	this->static_instances.clear();
	this->dynamic_instances.clear();
	delete this->static_loader;
}

void ColorScaleLoader::loadStaticInstances() {
	static_loader = new QPluginLoader();
	assert(static_loader != NULL);
	QObjectList objects = static_loader->staticInstances();
	if(objects.size() == 0)
		return;
	QListIterator<QObject*> objects_iter(objects);
	while(objects_iter.hasNext()) {
		QObject *stub = objects_iter.next();
		ColorScale *visconti = qobject_cast<ColorScale*>(stub);
		if(visconti) {
			static_instances.append(visconti);
		} else {
			delete visconti;
		}
	}
}

void ColorScaleLoader::loadDynamicInstances() {
	QString plugin_path = my_settingsManager->value(QString("color-scales/dir_dynamic")).toString();
	if(plugin_path.isEmpty())
		return;
	QDir plugin_dir(plugin_path);
	if (!(plugin_dir.exists() && plugin_dir.isReadable()))
		return;
	QFileInfoList plugin_dir_entries = plugin_dir.entryInfoList(QDir::Files);
	QListIterator<QFileInfo> pdir_iter(plugin_dir_entries);
	while(pdir_iter.hasNext()) {
		QFileInfo next_file = pdir_iter.next();
		if(!QLibrary::isLibrary(next_file.absoluteFilePath()))
			continue;
		QPluginLoader *loader = new QPluginLoader(next_file.absoluteFilePath());
		ColorScale *cs_ptr = qobject_cast<ColorScale*>(loader->instance());
		if(cs_ptr == NULL) {
			loader->unload();
			delete loader;
			continue;
		}
		dynamic_loaders.append(loader);
		dynamic_instances.append(cs_ptr);
	}
}

void ColorScaleLoader::slot_reloadInstances() {

}

QList<QString> ColorScaleLoader::scales() {
	QList<QString> output;
	if(static_instances.size() == 0 &&
			dynamic_instances.size() == 0)
		return output;
	if(static_instances.size() != 0) {
		QListIterator<ColorScale*> static_iter(static_instances);
		while(static_iter.hasNext()) {
			output.append(static_iter.next()->name());
		}
	}
	if(dynamic_instances.size() != 0) {
		QListIterator<ColorScale*> dynamic_iter(dynamic_instances);
		while(dynamic_iter.hasNext()) {
			output.append(dynamic_iter.next()->name());
		}

	}
	return output;
}

QHash<QString,ColorScale*> ColorScaleLoader::scale(const QString &name, char preference) {
	if(name.size() == 0)
		return QHash<QString,ColorScale*>();
	QListIterator<ColorScale*> static_iter(static_instances);
	QListIterator<ColorScale*> dynamic_iter(dynamic_instances);
	QHash<QString,ColorScale*> results_static;
	QHash<QString,ColorScale*> results_dynamic;
	while(static_iter.hasNext()) {
		ColorScale *stub = static_iter.next();
		if(stub->name() == name)
			results_static.insert(stub->name(),stub);
	}
	while(dynamic_iter.hasNext()) {
		ColorScale *stub = dynamic_iter.next();
		if(stub->name() == name)
			results_dynamic.insert(stub->name(),stub);
	}
	if(results_static.size() > 0 && results_dynamic.size() > 0) {
		switch(preference) {
		case 0:
			return results_static;
			break; // pro forma
			;
		case 1:
			return results_dynamic;
		default:
			return QHash<QString,ColorScale*>();
			;
		}
	}
	if(results_static.size() > 0) {
		return results_static;
	} else {
		return results_dynamic;
	}
	return results_static;
}

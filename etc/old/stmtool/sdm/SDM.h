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

#ifndef SDM_H_
#define SDM_H_
/*!
 * \file SDM.h
 * Implements SDM and related classes.
 *
 * \class SDM
 * \brief Provides an interface for components to produce I/O with dataspace
 * modules by implementing QAbstractItemModel, which atop allows the application
 * of Qt's Model/View facility.
 *
 * SDM is the data recorder used by the stmtool for storage of STM scan data such as images,
 * filtered images and metadata, color scales and other essential products of its user.
 * In order to make the widest range of data storing platforms available,
 *
 * \fn void slot_gui_browser()
 * \brief Displays the Dataspace Browser dialog.
 *
 * \fn void slot_gui_recentRessources(QList<QString>*)
 * \brief In fact, takes a QStringList as its argument and writes a list
 * of the most recent used ressource paths to it. To be used for GUI menu building.
 * \todo It will surely be better to simply popup a QMenu at the current pointer
 * position.
 *
 *
 *
 *
 *
 * \class sdm_dataspace
 *
 * \class sdm_dataspace_fs
 *
 * \class sdm_dataspace_entity
 * \brief  Represents a node inside a dataspace.
 *
 * Every object has to be assigned a single
 * role (enum EntityRole), whereupon its behaviour depends.
 * sdm_dataspace_entity's role-specific data is being provided by either scan_meta_data
 * or image_meta_data, where the latter is not being directly stored inside the object but
 * referenced by a unique ressource path retrieved from the sdm_dataspace instance directly.
 * All sdm_dataspace_entity objects do have a set of properties in common which shall be
 * referenced as tag values.
 * In later revisions, sdm_dataspace_entity will inherit QObject and be connected to a
 * dataspace-wide bus-system built of signals & slots to simplify the management.
 *
 * \struct scan_meta_data
 * Holds technical and typological data on a single scan process.
 * Uitlized by sdm_dataspace_entity.
 *
 * \fn QByteArray scan_meta_data::pack()
 * \brief  Returns the whole data hold by the object in a byte format.
   \return QByteArray with bytewise arranged data.
   \see upack()

   \fn bool scan_meta_data::upack(const QByteArray&)
   \brief Reassigns the data from the QByteArray.
 * @param pkg A QByteArray produced by pack(). In later versions,
 * it will be verified if the package is valid before processing,
 * but for now, you have to assure the right package comes in.
 * @return True if the package had a size > 0 Bytes and has been
 * processed.
 * @return False if the package's size had been == 0.
 * @see pack()
 *
 * \struct image_meta_data
 * \brief  Holds either an edited, converted or RAW scan image along with its parametric
 * data (image range, postprocessing steps etc).
 *
 * \struct sdm_dataspace_instance
 *
 * \struct sdm_dataspace_essence
 *
 */
#include <QtGlobal>
#include <QtDebug>
#include <QtPlugin>
#include <QtCore/QDataStream>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QList>
#include <QtCore/QListIterator>
#include <QtCore/QMap>
#include <QtCore/QMapIterator>
#include <QtCore/QHash>
#include <QtCore/QHashIterator>
#include <QtCore/QByteArray>
#include <QtCore/QDateTime>
#include <QtCore/QVariant>
#include <QtCore/QPluginLoader>
#include <QtCore/QAbstractItemModel>
#include <QtCore/QModelIndex>
#include <QtGui/QAction>
#include <QtGui/QImage>
#include <QtGui/QMenu>

#include <ctime>
#include <cassert>

#include <Sherlog.h>
#include <deviceManager/deviceManager.h>
#include <settingsManager/settingsManager.h>
#include <devices/stmData.h>
#include <devices/iDevice.h>
#include <sdm/SDMBrowser.h>
#include <general/StmtComponent.h>

/* Prototypes */
class SDM;
class SDM_Model;
class sdm_dataspace;
class sdm_dataspace_fs;
class sdm_dataspace_entity;
struct scan_meta_data;
struct image_meta_data;
struct sdm_dataspace_instance;
struct sdm_dataspace_essence;

struct scan_meta_data {
	QString probe_name;
	QString probe_description;
	quint32 probe_dimension_x;
	quint32 probe_dimension_y;
	scan_meta_data() {
		probe_name = QString("probe_name");
		probe_description = QString("probe_description");
	}
	void operator=(const struct scan_meta_data &rvalue) {
		probe_name = rvalue.probe_name;
		probe_description = rvalue.probe_description;
		probe_dimension_x = rvalue.probe_dimension_x;
		probe_dimension_y = rvalue.probe_dimension_y;
	}
	QByteArray pack() {
		QByteArray package;
		QDataStream writer(&package,QIODevice::WriteOnly);
		writer << probe_name;
		writer << probe_description;
		writer << probe_dimension_x;
		writer << probe_dimension_y;
		return package;
	}
	bool upack(const QByteArray &pkg) {
		if(pkg.size() > 0) {
			QByteArray input(pkg);
			QDataStream reader(&input,QIODevice::ReadOnly);
			reader >> probe_name;
			reader >> probe_description;
			reader >> probe_dimension_x;
			reader >> probe_dimension_y;
			return true;
		} else {
			return false;
		}
	}
};

/*
 * ANNOTATION
 * qt coordinate system:
 * 0 x x x
 * y
 * y
 * y
 */

/*****************************************************************************/
struct image_meta_data {
	QString image_name;			// displayed image name
	QString ressource_path;			// ressource path within dataspace, e.g. a simple filepath
	QByteArray *ressource_data;		// RESSOURCE
	QString preview_path;			// eventually a prerendered image for aesthetics.
	QByteArray *preview_data;		// PREVIEW ressource DECR in 8-2010.0.3.1
	quint32 dimension_x;			// width in pixels
	quint32 dimension_y;			// height in pixels
	quint32 anker_x;			// x anker coordinate within probe
	quint32 anker_y;			// y anker coordinate within probe
	bool image_is_edited;			// 'true' if data has been manipulated
	enum QImage::Format image_format_qt;	// if QImage::Format_Invalid => RAW data

	QByteArray pack() {
		QByteArray output;
		QDataStream writer(&output,QIODevice::WriteOnly);
		writer << image_name;
		writer << ressource_path;
		if(ressource_data) {
			writer << (quint32) 1;
			QByteArray ressource_data_copy(*ressource_data);
			writer << ressource_data_copy;
		} else {
			writer << (quint32) 0;
		}
		writer << preview_path;
		if(preview_data) {
			writer << (quint32) 1;
			QByteArray preview_data_copy(*preview_data);
			writer << preview_data_copy;
		} else {
			writer << (quint32) 0;
		}
		writer << dimension_x;
		writer << dimension_y;
		writer << anker_x;
		writer << anker_y;
		writer << image_is_edited;
		writer << (qint32) image_format_qt;
		return output;
	}
	bool upack(const QByteArray &pkg) {
		if(pkg.size() > 0) {
			QByteArray input(pkg);
			QDataStream reader(&input,QIODevice::ReadOnly);
			reader >> image_name;
			reader >> ressource_path;
			quint32 choice;
			reader >> choice;
			if(choice == 1) {
				if(ressource_data)
					delete ressource_data;
				QByteArray new_ressource_data;
				reader >> new_ressource_data;
				ressource_data = new QByteArray(new_ressource_data);
			} else {
				if(ressource_data)
					delete ressource_data;
				ressource_data = NULL;
			}
			reader >> preview_path;
			reader >> choice;
			if(choice == 1) {
				if(preview_data)
					delete preview_data;
				QByteArray new_preview_data;
				reader >> new_preview_data;
				preview_data = new QByteArray(new_preview_data);
			} else {
				if(preview_data)
					delete preview_data;
				preview_data = NULL;
			}
			reader >> dimension_x;
			reader >> dimension_y;
			reader >> anker_x;
			reader >> anker_y;
			reader >> image_is_edited;
			qint32 to_enum;
			reader >> to_enum;
			image_format_qt = (enum QImage::Format) to_enum;
			return true;
		} else {
			return false;
		}
	}
	~image_meta_data() {
		delete ressource_data;
		delete preview_data;
	}
	image_meta_data() {
		image_name = QString("$NONE$");
		ressource_path = QString("$NONE$");
		ressource_data = NULL;
		preview_path = QString("$NONE$");
		preview_data = NULL;
		dimension_x = 0;
		dimension_y = 0;
		anker_x = 0;
		anker_y = 0;
		image_is_edited = false;
		image_format_qt = QImage::Format_Invalid;
	}
	image_meta_data(const struct image_meta_data &src) {
		image_name = src.image_name;
		ressource_path = src.ressource_path;
		ressource_data = src.ressource_data ? new QByteArray(*src.ressource_data) : NULL;
		preview_path = src.preview_path;
		preview_data = src.preview_data ? new QByteArray(*src.preview_data) : NULL;
		dimension_x = src.dimension_x;
		dimension_y = src.dimension_y;
		anker_x = src.anker_x;
		anker_y = src.anker_y;
		image_is_edited = src.image_is_edited;
		image_format_qt = src.image_format_qt;
	}
	image_meta_data(const struct image_meta_data &src, bool withData) {
		image_name = src.image_name;
		ressource_path = src.ressource_path;
		ressource_data = src.ressource_data && withData ? new QByteArray(*src.ressource_data) : NULL;
		preview_path = src.preview_path;
		preview_data = src.preview_data && withData ? new QByteArray(*src.preview_data) : NULL;
		dimension_x = src.dimension_x;
		dimension_y = src.dimension_y;
		anker_x = src.anker_x;
		anker_y = src.anker_y;
		image_is_edited = src.image_is_edited;
		image_format_qt = src.image_format_qt;
	}
	image_meta_data(const struct image_meta_data *src) {
		image_name = src->image_name;
		ressource_path = src->ressource_path;
		ressource_data = src->ressource_data ? new QByteArray(*src->ressource_data) : NULL;
		preview_path = src->preview_path;
		preview_data = src->preview_data ? new QByteArray(*src->preview_data) : NULL;
		dimension_x = src->dimension_x;
		dimension_y = src->dimension_y;
		anker_x = src->anker_x;
		anker_y = src->anker_y;
		image_is_edited = src->image_is_edited;
		image_format_qt = src->image_format_qt;
	}
	image_meta_data(const struct image_meta_data *src, bool withData) {
		image_name = src->image_name;
		ressource_path = src->ressource_path;
		ressource_data = src->ressource_data && withData ? new QByteArray(*src->ressource_data) : NULL;
		preview_path = src->preview_path;
		preview_data = src->preview_data && withData ? new QByteArray(*src->preview_data) : NULL;
		dimension_x = src->dimension_x;
		dimension_y = src->dimension_y;
		anker_x = src->anker_x;
		anker_y = src->anker_y;
		image_is_edited = src->image_is_edited;
		image_format_qt = src->image_format_qt;
	}
	void operator=(const struct image_meta_data &meta) {
		image_name = meta.image_name;
		ressource_path = meta.ressource_path;
		preview_path = meta.preview_path;
		dimension_x = meta.dimension_x;
		dimension_y = meta.dimension_y;
		anker_x = meta.anker_x;
		anker_y = meta.anker_y;
		image_is_edited = meta.image_is_edited;
		image_format_qt = meta.image_format_qt;
	}
};

/*****************************************************************************/

/*!
 * Represents a node inside a dataspace. every object has to be assigned a single
 * role (enum EntityRole), whereupon its behaviour depends.
 * sdm_dataspace_entity's role-specific data is being provided by either scan_meta_data
 * or image_meta_data, where the latter is not being directly stored inside the object but
 * referenced by a unique ressource path retrieved from the sdm_dataspace instance directly.
 * All sdm_dataspace_entity objects do have a set of properties in common which shall be
 * referenced as tag values.
 * In later revisions, sdm_dataspace_entity will inherit QObject and be connected to a
 * dataspace-wide bus-system built of signals & slots to simplify the management and
 * provide refraction-like facilities.
 */
class sdm_dataspace_entity {
public:
	/*!
	 * Specifies the role of a sdm_dataspace_entity.
	 */
	enum EntityRole {
		FOLDER,
		SCAN,
		IMAGE
	};

	sdm_dataspace_entity(const QString &dataspace, sdm_dataspace_entity *parent) {
		setDataspace(dataspace);
		setParent(parent);
		setEntityRole(FOLDER);
		setText("<NEW FOLDER>");
	}
	sdm_dataspace_entity(const QString &dataspace = QString("/dev/null"),
			enum EntityRole role = FOLDER,
			const QString &text = QString(""),
			sdm_dataspace_entity *parent = NULL) {
		setDataspace(dataspace);
		setParent(parent);
		setEntityRole(role);
		setText(text);
	}
	sdm_dataspace_entity(sdm_dataspace_entity &src) {
		setParent(src.parent());
		setText(src.text());
		setDateTime(src.dateTime());
		setEntityRole(src.entityRole());
		setScanMetaData(src.scanMetaData());
		setImageRessource(src.imageRessource());
		setChildren(src.children());
	}
	sdm_dataspace_entity(sdm_dataspace_entity *src) {

	}
	sdm_dataspace_entity(const QByteArray &pkg) {

	}

	~sdm_dataspace_entity() {
		my_children.clear();
	}

	sdm_dataspace_entity* parent() const {
		return my_parent;
	}
	void setParent(sdm_dataspace_entity *parent = NULL) {
		my_parent = parent;
	}

	void setText(const QString &text = QString("<TEXT>")) {
		my_text = text;
	}
	QString text() const {
		return my_text;
	}

	void setDateTime(const QDateTime &datetime) {
		my_dateTime = datetime;
	}
	QDateTime dateTime() const {
		return my_dateTime;
	}

	void setEntityRole(enum EntityRole role = FOLDER) {
		my_role = role;
	}
	enum EntityRole entityRole() const {
		return my_role;
	}

	void setScanMetaData(const struct scan_meta_data &meta) {
		if(my_role == SCAN) {
			my_scan_meta_data = meta;
		}
	}
	struct scan_meta_data scanMetaData() const {
		return my_scan_meta_data;
	}

	/*
	void setImageMetaData(const struct image_meta_data &meta) {
		if(my_role == IMAGE) {
			my_image_meta_data = meta;
		}
	}
	struct image_meta_data imageMetaData() {
		return my_image_meta_data;
	}

	void addImageRessource(const QString &ressourcepath) {

	}
	*/

	void setImageRessource(const QString &ressourcepath) {
		my_image_ressource_path = ressourcepath;
	}

	QString imageRessource() const {
		return my_image_ressource_path;
	}

	QList<sdm_dataspace_entity*> children() const {
		return my_children;

	}
	void addChild(sdm_dataspace_entity *add = NULL) {
		if(add) {
			my_children.append(add);
		}
	}
	// IMPROVE: Is 'takeChild(*) const' here allowed?
	sdm_dataspace_entity* takeChild(const QString &text) {
		if(text != QString("")) {
			QListIterator<sdm_dataspace_entity*> iter(my_children);
			while(iter.hasNext()) {
				sdm_dataspace_entity *sub = iter.next();
				if(sub->text() == text) {
					return sub;
				}
			}
			return NULL;
		}
		return NULL;
	}
	QString dataspace() {
		return my_dataspace;
	}

	/*
	 * Finally, this method has to be called by the dataspace
	 * only once, from the dataspace root.
	 */
	QByteArray pack() {
		QByteArray package;
		QDataStream writer(&package,QIODevice::WriteOnly);
		writer << my_dataspace;
		writer << my_image_ressource_path;
		writer << (qint32) my_role;
		writer << my_text;
		writer << my_dateTime;
		writer << my_scan_meta_data.pack();
		writer << (qint32) my_children.size();
		for(int counter = 0;
		counter < my_children.size();
		++counter) {
			writer << my_children.at(counter)->pack();
		}
		return package;
	}
	bool upack(const QByteArray &pkg) {
		if(pkg.size() > 0) {
			bool error_level = true;
			QByteArray pkg_copy(pkg);
			QDataStream reader (&pkg_copy,QIODevice::ReadOnly);
			reader >> my_dataspace;
			reader >> my_image_ressource_path;
			qint32 int_role;
			reader >> int_role;
			my_role = (enum EntityRole) int_role;
			reader >> my_text;
			reader >> my_dateTime;
			QByteArray pkg_scan_meta_data;
			reader >> pkg_scan_meta_data;
			error_level = my_scan_meta_data.upack(pkg_scan_meta_data);
			qint32 pkg_children_count;
			reader >> pkg_children_count;
			for(int counter = 0;
			counter < pkg_children_count;
			++counter) {
				sdm_dataspace_entity *a_child = new sdm_dataspace_entity(my_dataspace,this);
				QByteArray this_childs_package;
				reader >> this_childs_package;
				error_level = a_child->upack(this_childs_package);
			}
			return error_level;
		}
		return false;
	}

private:
	void setDataspace(const QString &dataspace) {
		my_dataspace = dataspace;
	}
	void setChildren(const QList<sdm_dataspace_entity*> &children) {
		my_children.append(children);
	}
	QString my_dataspace;
	QString my_image_ressource_path;
	enum EntityRole my_role;
	QString my_text;
	QDateTime my_dateTime;
	QList<sdm_dataspace_entity*> my_children;
	sdm_dataspace_entity *my_parent;
	struct scan_meta_data my_scan_meta_data;
};

/*****************************************************************************/

/*!
 * sdm_dataspace is an abstract class inherited by all dataspace modules.
 * in later revisions, for plugin-provided dataspace modules it will be
 * declared solely as a Qt interface.
 */
class sdm_dataspace : public StmtComponent {
	Q_OBJECT
public slots:
	virtual void stmtc_slot_init() = 0;
	virtual void stmtc_slot_shutdown() = 0;
	virtual void stmtc_slot_resolveDependencies() = 0;
	virtual void stmtc_slot_receiveDependencies(QList<StmtComponent*>) = 0;
	virtual void stmtc_slot_setVerbosity(enum StmtComponent::VerbosityLevel) = 0;
public:
	/*!
	 * @return the dataspace name, e.g. http
	 */
	virtual QString name() = 0;
	/*!
	 * Loads specific configurations from a file
	 * previously obtained by initFile().
	 * @param file A QByteArray retrieved from initFile().
	 */
	virtual void setInitFile(const QByteArray &file) = 0;
	/*!
	 * Stores flexible dataspace configuration, e.g.
	 * pwd, login data. contains AT LEAST
	 * the my_configuration member.
	 * @return A QByteArray with all dataspace entities including ressources.
	 */
	virtual QByteArray initFile() = 0;
	/*!
	 * @return The constructed ressource tree,
	 * the root is of role FOLDER and begets
	 * all data.
	 */
	virtual sdm_dataspace_entity root() = 0;
	/*!
	 * Before any ressources can be retrieved via
	 * call of ressource(), open() has to return
	 * true.
	 */
	virtual bool open() = 0;
	/*!
	 * For every single I/O operation, the dataspace needs to be open.
	 * @return True if the dataspace has been opened.
	 */
	virtual bool isOpen() = 0;
	/*!
	 * After all operations finished, you call close()
	 * to properly shutdown the dataspace.
	 * @return True if the closure has been successfully executed.
	 */
	virtual bool close() = 0;
	/*
	 * ressource management methods
	 */
	/*!
	 * Retrieves ressources from the dataspace.
	 * @param ressourcepath A ressource's path
	 * @param with_image_data If false, the actual image ressource will not
	 * be retrieved.
	 * @return The image ressource.
	 */
	virtual struct image_meta_data ressource(const QString &ressourcepath,bool with_image_data) = 0;
	/*!
	 * Adds a ressource to the dataspace's ressource system.
	 * @param ressource An image ressource holding valid image data.
	 * @return The new ressourcepath if the ressource has been successfully added.
	 * @return QString("") if the operation could not have been completed.
	 */
	virtual QString addRessource(const struct image_meta_data &ressource) = 0;
	/*!
	 * @param with_image_data If false, no actual image data will be retrieved.
	 * @return A complete ressource list
	 */
	virtual QList<struct image_meta_data> ressourceList(bool with_image_data) = 0;
	/*
	 * Provides a QMap<key,value> requesting ESSENTIAL
	 * configuration.
	 * key-string := "${PROPERTY_NAME}\\${PROPERTY_TYPE}"
	 * for ${PROPERTY_TYPE} in { str quint32 qint32 bool }
	 * The value-string has to be mappable via QVariant to
	 * the property type.
	 * IMPROVE: define code properties by preprocessor
	 */
	/*!
	 * @return The key-value based configuration map.
	 */
	virtual QMap<QString,QString> configuration() = 0;
	/*!
	 * Sets up a new configuration map replacing already exiting keys.
	 * @param config The configuration map.
	 */
	virtual bool setConfiguration(const QMap<QString,QString> &config) = 0;
	/*!
	 * @return True if the dataspace structure is integer.
	 */
	virtual bool isValid() = 0;
protected:
	/*!
	 * Holds the dataspace's configuration map-
	 */
	QMap<QString,QString> my_configuration;
	/*!
	 * True if the dataspace has not yet been closed.
	 */
	bool flag_isOpen;
};
Q_DECLARE_INTERFACE(sdm_dataspace, "sdm-dataspace")

/*****************************************************************************/

/*!
 * the single built-in dataspace module operating on the local filesystem.
 */
class sdm_dataspace_fs : public sdm_dataspace {
	/*
	 * TODO:Ensure flag_isOpen is being used as
	 * an indicator by access methods.
	 */
	Q_OBJECT
	Q_INTERFACES(sdm_dataspace)
public slots:
	void stmtc_slot_init() {

	}
	void stmtc_slot_shutdown() {

	}
	void stmtc_slot_resolveDependencies() {

	}
	void stmtc_slot_receiveDependencies(QList<StmtComponent*>) {

	}
	void stmtc_slot_setVerbosity(enum StmtComponent::VerbosityLevel) {

	}
public:
	/*
	 * std configuration flags:
	 * droot\\str => directory root for filetree creation
	 * scanfile_suffix\\str => default scan data file suffix & nameFilter in QDir.
	 * imgfile_suffix\\str => suffix for image ressource data.
	 * *_suffx\\str => additional name filters
	 */

	sdm_dataspace_fs() {
		flag_isOpen = false;
		my_root = NULL;
		//PROPERTY: "rootfile\\str" "" provides path to db
		//my_configuration.insert(QString("rootfile\\str"),QString(""));
		my_configuration.insert(QString("scanfile_suffix\\str"),QString("scnf"));
		my_configuration.insert(QString("imgfile_suffix\\str"),QString("imgf"));
	}
	~sdm_dataspace_fs() {

	}

	QString name() {
		return QString("file-system");
	}

	void setInitFile(const QByteArray &file) {
		if(file.size() > 0 && (!flag_isOpen)) {
			QByteArray in(file);
			QDataStream reader(&in,QIODevice::ReadOnly);
			reader >> my_configuration;
			/*
			 * restores document tree.
			 */
			if(my_root)
				delete my_root;
			my_root = newRoot();
			QByteArray document_tree;
			reader >> document_tree;
			my_root->upack(document_tree);
			/*
			 * restores ressource tree.
			 */
			document_tree.clear();
			reader >> document_tree;
			loadRessourcePackage(document_tree);
		}
		qCritical() << "sdm_dataspace_fs -> could not load ressource package.";
	}

	QByteArray initFile() {
		if(my_configuration.size() > 0) {
			QByteArray output;
			QDataStream writer (&output,QIODevice::WriteOnly);
			writer << my_configuration;
			/*
			 * stores the document tree.
			 * be aware: to prevent data drain,
			 * we hafta the database CLOSED.
			 */
			if(!flag_isOpen) {
				writer << my_root->pack();
			}
			/*
			 * stores the ressource tree.
			 */
			writer << ressourcePackage();
			return output;
		}
		return QByteArray();
	}

	sdm_dataspace_entity root() {
		if(!flag_isOpen) {
			sdm_dataspace_entity to_return;
			return to_return;
		}
		sdm_dataspace_entity my_root_copy(my_root);
		return my_root_copy;
	}

	bool open() {
		if(flag_isOpen) {
			qCritical() << "file-system dataspace has been already opened.";
			return false;
		}
		if(my_configuration.contains(QString("rootfile\\str"))) {
			QFile rf(my_configuration.value(QString("rootfile\\str")));
			if(!rf.open(QIODevice::ReadOnly)) {
				qCritical() << "file-system -> cannot open rootfile:";
				qCritical() << "\trootfile\\str";
				return false;
			}
			QByteArray theInitFile;
			QDataStream reader(&rf);
			reader >> theInitFile;
			if(theInitFile.size() < 0) {
				qCritical() << "corrupt or empty rootfile.";
				return false;
			}
			setInitFile(theInitFile);
			flag_isOpen = true;
			return true;
		} else {
			my_root = newRoot();
			flag_isOpen = my_root ? true : false;
			return isOpen();
		}
		return false;
	}

	bool isOpen() {
		return flag_isOpen;
	}

	bool close() {
		if(flag_isOpen) {
			flag_isOpen = false;
			return true;
		} else {
			return false;
		}
	}

	struct image_meta_data ressource(const QString &ressourcepath, bool with_image_data) {
		if((ressourcepath == QString("")) ||
				!my_ressources.contains(ressourcepath)) {
			struct image_meta_data to_return;
			to_return.image_name = "$RESSOURCE NOT EXISTENT$";
		}
		struct image_meta_data ressource(my_ressources.value(ressourcepath),with_image_data);
		return ressource;
	}

	QString addRessource(const struct image_meta_data &ressource) {
		if(ressource.ressource_data == NULL)
			return QString("");
		struct image_meta_data *stub = new struct image_meta_data(ressource);
		stub->ressource_path = stub->image_name.append(rptc());
		while(my_ressources.contains(stub->ressource_path)) {
			stub->ressource_path.append(rptc());
		}
		if(stub->preview_data) {
			stub->preview_path = stub->ressource_path + QString("_preview");
		}
		my_ressources.insert(stub->ressource_path,stub);
		return stub->ressource_path;
	}

	QList<struct image_meta_data> ressourceList(bool with_image_data) {
		QList<struct image_meta_data> to_return;
		if(my_ressources.size() > 0) {
			QHashIterator<QString,struct image_meta_data*> iter(my_ressources);
			while(iter.hasNext()) {
				struct image_meta_data ta(iter.value(),with_image_data);
				to_return.append(ta);
			}
		}
		return to_return;
	}

	QMap<QString,QString> configuration() {
		return QMap<QString,QString>(my_configuration);
	}

	bool setConfiguration(const QMap<QString,QString> &config) {
		if(config.size() > 0) {
			my_configuration = QMap<QString,QString>(config);
		}
	}

	bool isValid() {
		return true;
	}
private:
	/*
	 * ressource path time component
	 */
	QString rptc() const {
		using std::time;
		return QVariant((qint32) time(NULL)).toString();
	}
	sdm_dataspace_entity* newRoot() {
		sdm_dataspace_entity *new_root = new sdm_dataspace_entity(QString(name()),NULL);
		new_root->setText(QString("Local FS"));
		return new_root;
	}
	QByteArray ressourcePackage() {
		QByteArray output;
		QDataStream writer(&output,QIODevice::WriteOnly);
		writer << my_ressources.size();
		QHashIterator<QString,struct image_meta_data*> iter(my_ressources);
		while(iter.hasNext()) {
			iter.next();
			writer << iter.value()->pack();
		}
		return output;
	}
	bool loadRessourcePackage(const QByteArray &pkg) {
		if(pkg.size() > 0) {
			QByteArray pkg_copy(pkg);
			QDataStream reader(&pkg_copy,QIODevice::ReadOnly);
			my_ressources.clear();
			qint32 ressource_count;
			reader >> ressource_count;
			for(int counter = 0;
			counter < ressource_count;
			++counter) {
				struct image_meta_data *stub = new struct image_meta_data();
				QByteArray current_pkg;
				reader >> current_pkg;
				if(!stub->upack(current_pkg)) {
					delete stub;
					continue;
				}
				my_ressources.insert(stub->ressource_path,
						stub);
			}
			if(my_ressources.size() != ressource_count) {
				qCritical() << "instance of dataspace " << name();
				qCritical() << "loadRessourcePackage(): There has been a number \
						of dropped ressource packages, at least:";
				qCritical() << ressource_count - my_ressources.size();
			}
			return true;
		} else {
			return false;
		}
	}
	void clearRessourceTree() {
		//IMPROVE:Does QHash<>::clear() invoke destructors?
		// I assume:yes,hence this method shall not be called
		// if no evidence has been brought.
		if(my_ressources.size() > 0) {

		}
	}

	QHash<QString,struct image_meta_data*> my_ressources;
	sdm_dataspace_entity *my_root;
};

/*****************************************************************************/

/*!
 * A helper of class SDM. It comes in handy if dataspace modules have been
 * loaded from plugins by securing the module can be safely unloaded.
 */
struct sdm_dataspace_instance {
	sdm_dataspace *instance;
	sdm_dataspace_essence *essence;
	QPluginLoader *loader;
};

/*****************************************************************************/

/*!
 * A helper of class SDM. If the either the configuration map or the init-file
 * of an arbitrary instance of sdm_dataspace has been retrieved, it will be
 * handled by SDM class using this very capsule.
 * @see sdm_dataspace
 */
struct sdm_dataspace_essence {
	QList<QFileInfo> configuration_maps;
	QList<QFileInfo> initialization_files;
	QString dataspace_name;

	/*
	QByteArray pack() {
		QByteArray output;
		QDataStream writer(&output,QIODevice::WriteOnly);
		writer << map_filepath;
		writer << map_filesize;
		writer << map_dateOfChange;
		writer << if_filepath;
		writer << if_filesize;
		writer << if_dateOfChange;
		writer << dataspace_name;
		return output;
	}
	bool upack(const QByteArray &pkg) {
		if(pkg.size() > 0) {
			QByteArray input(pkg);
			QDataStream reader(&input,QIODevice::ReadOnly);
			reader >> map_filepath;
			reader >> map_filesize;
			reader >> map_dateOfChange;
			reader >> if_filepath;
			reader >> if_filesize;
			reader >> if_dateOfChange;
			reader >> dataspace_name;
			return true;

		} else {
			return false;
		}
		return false; // for compiler warnings
	}
*/
};

/*****************************************************************************/
/*!
 * The scan data manager is the database holding all parametrical and ressource
 * data of STM scan operations.
 * It is based off a hierarchical structure built of "sdm_dataspace_entity"s wielding
 * the data.
 * Data can be stored in various places whither the bits are ushered by different
 * dataspaces modules. In the data tree, each level-1-node (level 0 is the nameless root)
 * represents the entry to a so-called dataspace handling its own I/O operations, having
 * its own configuration, its own implementation in form of pluggable modules. Therefore,
 * data can be transparently stored e.g. on the web, the local fs, SQL databases etc
 * without bothering the user with tasks like transferring data in hell different ways.
 * As for the module interface, sdm_dataspace must be inherited by all dataspace modules.
 * Within this abstraction layer, ressources can be dataspace-crossing linked to form a
 * hyperspace. For that reason, is is ABSOLUTELY NECESSARY to implement the method
 * sdm_dataspace::addRessource() meticulously to ensure UNIQUE ressource paths. Hence it
 * come, they shall follow *THIS* outline:
 * ${dataspace_name}:${ressource_name}:${timestamp}:${revision}
 * In version 0.3.5, I've changed the parent class of SDM to QAbstractItemModel to make
 * it easier to implement SDMBrowser wherein I use a QTreeView to represent the structure
 * of the dataspace tree.
 */

class SDM_Model : public QAbstractItemModel {
	Q_OBJECT
	friend class SDM;
public:
	SDM_Model(SDM* parent) {

	}

	~SDM_Model() {

	}

	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const {

	}

	QModelIndex parent(const QModelIndex &index) const {

	}

	int rowCount(const QModelIndex &parent = QModelIndex()) const {

	}

	int columnCount(const QModelIndex &parent = QModelIndex()) const {

	}

	QVariant data(const QModelIndex &index, int role) const {

	}
};

class SDM : public StmtComponent
{
        Q_OBJECT
public:
        SDM(Sherlog *logger_instance,
        		class deviceManager *device_manager,
        		settingsManager *settings_manager);
        ~SDM();
public slots:
	void slot_gui_browser();
	void slot_gui_recentRessources(QList<QString>*);

	/*! @name StmtComponent interface */
		//@{
		void stmtc_slot_init();
		void stmtc_slot_shutdown();
		void stmtc_slot_resolveDependencies();
		void stmtc_slot_receiveDependencies(QList<StmtComponent*>);
		void stmtc_slot_setVerbosity(enum StmtComponent::VerbosityLevel);
		//@}

private slots:
        /*void slot_scanStarted();
        void slot_newDataPending(datatable*);
        void slot_additionalDataPending(datatable*);
        void slot_changedScanParameters(struct scan_parameters*);*/
	void slot_ui_openDataspace();
	void slot_ui_closeDataspace();
	//void slot_ui_openRessource(const QString &ressourcepath);
private:
	QList<QString> availableDataspaces();
	QMap<QString,QString> availableConfigurationMaps();
	bool dataspaceExists(const QString &name);
	void loadDataspaces(const QString &directory);
	bool unloadDataspace(const QString &name);
	QList<struct sdm_dataspace_instance*> builtinDataspaces();
	void lookupDataspace(struct sdm_dataspace_instance *instance);
	QList<QFileInfo> readableExistingFiles(QHash<QString,QString> &pool,
			QString &key);
	void loadAvailableRessources();

	// format: <dataspace_name> <Filepath>
	QHash<QString,QString> d_initFiles;
	// format: <dataspace_name> <Filepath>
	QHash<QString,QString> d_configurationMaps;
	Sherlog *logger_instance;
	qint32 logger_id;
	class deviceManager *device_manager;
	settingsManager *settings_manager;
	sdm_dataspace_entity data_root;
	//QList<sdm_dataspace*> dataspaces;
	QList<QString> recently_used_ressources;
	QList<struct sdm_dataspace_instance*> dataspaces;
	SDM_Model my_model;
};

#endif /* SDM.h */

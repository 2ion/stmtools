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

#ifndef COLORSCALEVIEWER_H
#define COLORSCALEVIEWER_H

#include <Qt>
#include <QtGlobal>
#include <QtGui/QWidget>
#include <QtGui/QListWidgetItem>
#include <QtGui/QBrush>
#include <QtGui/QMenu>
#include <QtGui/QAction>
#include <QtGui/QMessageBox>
#include <QtGui/QInputDialog>
#include <QtGui/QFileDialog>
#include <QtGui/QCursor>
#include <QtGui/QColorDialog>
#include <QtGui/QScrollArea>
#include <QtGui/QPainter>
#include <QtCore/QPoint>
#include <QtGui/QDockWidget>
#include <QtCore/QList>
#include <QtCore/QListIterator>
#include <QtCore/QVariant>
#include <QtCore/QDataStream>
#include <QtCore/QFile>
#include <QtCore/QByteArray>
#include <QtCore/QStack>
#include <gui/colorScales/MyColorScale.h>
#include <gui/colorScales/ColorOperations.h>
#include <gui/GuiHelper/GuiHelper.h>
#include <gui/colorScales/GradientLabel.h>
#include <gui/colorScales/GradientScrollbar.h>
#include "ui_ColorScaleViewer.h"
#include <general/maindefs.h>
#include <time.h>
#include <math.h>

#define RNDRGB ((int) ceil(((double)((double)qrand() / (double)RAND_MAX) * 255.0)))

/*!
 * \file ColorScaleViewer.h
 * Implements ColorScaleViewer.
 *
 * \class ColorScaleViewer
 * \brief Provides an user interface to the color scale subsystem.
 *
 * ColorScaleViewer has the ability to fully utilize the underlying features
 * of MyColorScale and the methods of ColorOperations, whence it becomes the
 * most mighty utility to work with color scales.
 * The user can view every color scale made available by ColorScaleLoader or
 * loaded from a specifically created file, and edit them. Every color scale
 * viewed can be exported to a file, wherefrom it can be reloaded by
 * ColorScaleLoader anytime.
 * Despite ColorScaleViewer's editor facilities, every color scale being put
 * to use can be only made available for profiscient usage by ColorScaleLoader.
 * For file export/import, ColorScaleViewer uses the SDM system.
 *
 * \todo Implement MyColorScale QMenu usage fully
 * \todo Implement memory facility
 * \todo Implement remaining UI things.
 * \todo Make it use SDM for file i/o.
 * \todo Add a batch mode.
 */

#ifndef CSW_STR_TITLE_SET_NAME_DIALOG
#define CSW_STR_TITLE_SET_NAME_DIALOG ("Set scale name")
#endif
#ifndef CSW_STR_TITLE_APPEND_COLOR_DIALOG
#define CSW_STR_TITLE_APPEND_COLOR_DIALOG ("Append color")
#endif
#ifndef CSW_STR_TITLE_REMOVE_COLOR_DIALOG
#define CSW_STR_TITLE_REMOVE_COLOR_DIALOG ("Delete color")
#endif
#ifndef CSW_STR_QUESTION_IF_SURE
#define CSW_STR_QUESTION_IF_SURE ("Are you sure?")
#endif
#ifndef CSW_STR_TOOLBOX_RENAME_ACTION
#define CSW_STR_TOOLBOX_RENAME_ACTION ("Rename scale")
#endif
#ifndef CSW_STR_TITLE_EDIT_COLOR_DIALOG
#define CSW_STR_TITLE_EDIT_COLOR_DIALOG ("Edit color")
#endif
#ifndef CSW_STR_TITLE_CLEAR_SCALE_DIALOG
#define CSW_STR_TITLE_CLEAR_SCALE_DIALOG ("Clear scale")
#endif

class ColorScaleViewer : public QWidget {
	Q_OBJECT
public:
	struct ColorLine {
		QPen my_pen;
		QLine my_line;
		ColorLine(const QColor &color, int y, int length, int width) {
			my_pen.setColor(color);
			my_pen.setWidth(width);
			my_line.setLine(0,y,length,y);
		}
	};

	ColorScaleViewer(QWidget *parent = 0);
	ColorScaleViewer(MyColorScale &scale,QWidget *parent = 0);
	~ColorScaleViewer();
	void setScale(MyColorScale &scale);
	MyColorScale currentScale();
signals:
	void signal_scaleChanged(MyColorScale);
	void signal_buildView();
	void signal_buildGradient(QHash<quint32,QColor> colors);
private:
	void connectSS();
	Ui::ColorScaleViewerClass ui;
	MyColorScale scale_work;
	/* context menues compiled by connectSS() */
	QList<QAction*> actions_toolsmenu;
	/* operational */
	quint32 current_color_index;
	GradientLabel *myGradientLabel;
	QStack<QByteArray*> scale_memory;

private slots:
	// corresponds with QListWidgetItem::currentItemChanged(*).
	void slot_displayColor(QListWidgetItem *current, QListWidgetItem *previous);
	void slot_buildView();
	void slot_ui_setName();
	void slot_ui_appendColor();
	void slot_ui_removeColor();
	void slot_ui_recall(int);
	void slot_ui_clear();
	void slot_ui_invert();
	void slot_ui_memorize();
	void slot_ui_toolsmenu();
	void slot_ui_colorDialog();
	void slot_ui_saveXML();
	void slot_ui_loadXML();
	void slot_ui_spin_R();
	void slot_ui_spin_G();
	void slot_ui_spin_B();
	void slot_ui_spin_A();
	void slot_ui_randomScale();
#ifdef DEBUG
	void slot_ui_DUMMY();
#endif

};

#endif // COLORSCALEVIEWER_H

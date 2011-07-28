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

#include "ColorScaleViewer.h"
ColorScaleViewer::ColorScaleViewer(QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);
	connectSS();
}

ColorScaleViewer::ColorScaleViewer(MyColorScale &scale, QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);
	connectSS();
	setScale(scale);
}

ColorScaleViewer::~ColorScaleViewer()
{

}

void ColorScaleViewer::slot_ui_clear() {
	if(!GuiHelper::askForBoolean(QString(CSW_STR_TITLE_CLEAR_SCALE_DIALOG),
			QString(CSW_STR_QUESTION_IF_SURE)))
			return;
	scale_work.clearScale();
	emit signal_buildView();
}

void ColorScaleViewer::slot_ui_memorize() {
	ui.cb_memory->insertItem(-1,
			scale_work.name(),
			QVariant(scale_work.toXML()));
}

void ColorScaleViewer::slot_ui_recall(int index) {
	scale_work.clearScale();
	scale_work.fromXML(ui.cb_memory->itemData(index).toByteArray());
	ui.cb_memory->removeItem(index);
	emit signal_buildView();
}

void ColorScaleViewer::slot_ui_setName() {
	QString text = QInputDialog::getText(this,QString(CSW_STR_TITLE_SET_NAME_DIALOG),
			QString("Scale name:"));
	if(text == QString(""))
		return;
	scale_work.setName(text);
	emit signal_buildView();
}

void ColorScaleViewer::slot_ui_appendColor() {
	QColor newcolor = QColorDialog::getColor(scale_work.color(current_color_index),this,
				QString(CSW_STR_TITLE_APPEND_COLOR_DIALOG),QColorDialog::ShowAlphaChannel);
	for(int X=0; X < ui.sb_colortimes->value(); ++X) {
		scale_work.appendColor(newcolor);
	}
	emit signal_buildView();
}

void ColorScaleViewer::slot_ui_removeColor() {
	if(!GuiHelper::askForBoolean(QString(CSW_STR_TITLE_REMOVE_COLOR_DIALOG),QString(CSW_STR_QUESTION_IF_SURE)))
		return;
	scale_work.deleteColor(current_color_index);
	emit signal_buildView();
}

void ColorScaleViewer::slot_ui_invert() {
	bool answer = GuiHelper::askForBoolean(QString("Invert scale"),
			QString("Invert the color's alpha value altogehter?"));
	scale_work.invertScale(answer);
	emit signal_buildView();
}

void ColorScaleViewer::setScale(MyColorScale &scale) {
	scale_work = scale;
	emit signal_buildView();
}

void ColorScaleViewer::slot_buildView() {
	setWindowTitle(QString("[") + scale_work.name() + QString("]") + \
				QString(" - ") + QVariant(scale_work.indizes()).toString() + \
				QString(" colors"));
	ui.listWidget->clear();
	if(scale_work.indizes() != 0) {
		QHash<quint32,QColor> raw = scale_work.colors();
		QHashIterator<quint32,QColor> iter(raw);
		while(iter.hasNext()) {
			iter.next();
			QListWidgetItem *entry = new QListWidgetItem();
			// sets the background color displayed.
			QColor seen = iter.value();
			entry->setBackground(QBrush(seen));
			// sets foreground color to a weighted complementary
			entry->setForeground(QBrush(INVERT_RGB(seen)));
			//entry->setForeground(QBrush(ColorOperations().weightedComplement(seen)));
			// sets a descriptive text including the index.
			entry->setText(QString("# ") + QVariant(iter.key()).toString());
			// sets the index as user-role data for usage in
			// manipulative gui-methods.
			entry->setData(Qt::UserRole,QVariant(iter.key()));
			ui.listWidget->addItem(entry);
		}
	}
	emit signal_buildGradient(scale_work.colors());
}

void ColorScaleViewer::connectSS() {
	GradientScrollbar *aScrollbar = new GradientScrollbar();
	connect(this,
			SIGNAL(signal_buildGradient(QHash<quint32,QColor>)),
			aScrollbar,
			SLOT(slot_displayScale(QHash<quint32,QColor>)));
	ui.listWidget->addScrollBarWidget(aScrollbar,Qt::AlignBottom);

#ifdef DEBUG
	QAction *dummy = new QAction(NULL);
	dummy->setText(QString("<DUMMY>"));
	connect(dummy,SIGNAL(triggered()),this,SLOT(slot_ui_DUMMY()));
	actions_toolsmenu.append(dummy);
#endif

	QAction *rename = new QAction(NULL);
	rename->setText(QString(CSW_STR_TOOLBOX_RENAME_ACTION));
	connect(rename,SIGNAL(triggered()),this,SLOT(slot_ui_setName()));
	actions_toolsmenu.append(rename);

	QAction *invert = new QAction(NULL);
	invert->setText(QString("Invert all colors"));
	connect(invert,SIGNAL(triggered()),this,SLOT(slot_ui_invert()));
	actions_toolsmenu.append(invert);

	QAction *xmlExport = new QAction(NULL);
	xmlExport->setText(QString("Export as XML file"));
	connect(xmlExport,SIGNAL(triggered()),this,SLOT(slot_ui_saveXML()));
	actions_toolsmenu.append(xmlExport);

	QAction *xmlImport = new QAction(NULL);
	xmlImport->setText("Import from XML file");
	connect(xmlImport,SIGNAL(triggered()),this,SLOT(slot_ui_loadXML()));
	actions_toolsmenu.append(xmlImport);

	QAction *randoms = new QAction(NULL);
	randoms->setText("Generate random scale");
	connect(randoms,SIGNAL(triggered()),this,SLOT(slot_ui_randomScale()));
	actions_toolsmenu.append(randoms);

	connect(ui.btn_scaletools,SIGNAL(clicked()),this,SLOT(slot_ui_toolsmenu()));
	/* trivial SS connections */
	connect(this,SIGNAL(signal_buildView()),this,SLOT(slot_buildView()));
	connect(this->ui.listWidget,
			SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
					this,SLOT(slot_displayColor(QListWidgetItem*,QListWidgetItem*)));
	connect(this->ui.pb_wheel,SIGNAL(clicked()),
			this,SLOT(slot_ui_colorDialog()));
	connect(this->ui.pb_addColor,SIGNAL(clicked()),
			this,SLOT(slot_ui_appendColor()));
	connect(this->ui.pb_removeColor,SIGNAL(clicked()),
			this,SLOT(slot_ui_removeColor()));
	connect(this->ui.pb_clear,SIGNAL(clicked()),
			this,SLOT(slot_ui_clear()));
	connect(this->ui.sb_R,SIGNAL(editingFinished()),this,SLOT(slot_ui_spin_R()));
	connect(this->ui.sb_G,SIGNAL(editingFinished()),this,SLOT(slot_ui_spin_G()));
	connect(this->ui.sb_B,SIGNAL(editingFinished()),this,SLOT(slot_ui_spin_B()));
	connect(this->ui.sb_ALPHA,SIGNAL(editingFinished()),this,SLOT(slot_ui_spin_A()));
	connect(this->ui.pb_memorize,SIGNAL(clicked()),this,SLOT(slot_ui_memorize()));
	connect(this->ui.cb_memory,SIGNAL(activated(int)),this,SLOT(slot_ui_recall(int)));
}

void ColorScaleViewer::slot_displayColor(QListWidgetItem *current,
		QListWidgetItem *previous) {
	if(current) {
		quint32 color_index = current->data(Qt::UserRole).toUInt();
		QColor selection = scale_work.color(color_index);
		ui.sb_R->setValue(selection.red());
		ui.sb_dR->setValue((double) selection.red() / 255.0);
		ui.sb_G->setValue(selection.green());
		ui.sb_dG->setValue((double) selection.green() / 255.0);
		ui.sb_B->setValue(selection.blue());
		ui.sb_dB->setValue((double) selection.blue() / 255.0);
		ui.sb_ALPHA->setValue(selection.alpha());

		current_color_index = color_index;
	}
}

void ColorScaleViewer::slot_ui_saveXML() {
	QString whereTo = QFileDialog::getSaveFileName(this,
			QString("Select output file"));
	QByteArray xml = scale_work.toXML();
	QFile target(whereTo);
	if(!target.open(QIODevice::WriteOnly))
		QMessageBox::information(this,
				QString("Error"),
				QString("The specified file is unaccessible."));
	target.write(xml);
	target.flush();
	target.close();
}

void ColorScaleViewer::slot_ui_loadXML() {
	QString whither = QFileDialog::getOpenFileName(this,
			"Select input file");
	if(GuiHelper::askForBoolean("Procedure",
			"Replace existing colors?"))
		scale_work.clearScale();
	QFile source(whither);
	if(!source.open(QIODevice::ReadOnly)) {
		QMessageBox::information(this,
				"Error",
				"The specified file is unaccessible.");
		return;
	}
	if(!scale_work.fromXML(source.readAll()))
		QMessageBox::information(this,
				"Error",
				"An parser error occured while processing the file.");
	source.close();
	emit signal_buildView();
}

void ColorScaleViewer::slot_ui_toolsmenu() {
	QMenu::exec(actions_toolsmenu,QCursor::pos());
}

void ColorScaleViewer::slot_ui_colorDialog() {
	QColor newcolor = QColorDialog::getColor(scale_work.color(current_color_index),this,
			QString(tr(CSW_STR_TITLE_EDIT_COLOR_DIALOG)),QColorDialog::ShowAlphaChannel);
	scale_work.setColor(current_color_index,newcolor);
	slot_buildView();
}

void ColorScaleViewer::slot_ui_spin_R() {
	QColor ncolor = scale_work.color(current_color_index);
	ncolor.setRed(ui.sb_R->value());
	scale_work.setColor(current_color_index,ncolor);
	emit signal_buildView();
}

void ColorScaleViewer::slot_ui_spin_G() {
	QColor ncolor = scale_work.color(current_color_index);
	ncolor.setGreen(ui.sb_G->value());
	scale_work.setColor(current_color_index,ncolor);
	emit signal_buildView();
}

void ColorScaleViewer::slot_ui_spin_B() {
	QColor ncolor = scale_work.color(current_color_index);
	ncolor.setBlue(ui.sb_B->value());
	scale_work.setColor(current_color_index,ncolor);
	emit signal_buildView();
}

void ColorScaleViewer::slot_ui_spin_A() {
	QColor ncolor = scale_work.color(current_color_index);
	ncolor.setAlpha(ui.sb_ALPHA->value());
	scale_work.setColor(current_color_index,ncolor);
	emit signal_buildView();
}

void ColorScaleViewer::slot_ui_randomScale() {
	int colors = QInputDialog::getInt(this,
			"Generate a random color scale",
			"Number of colors:",
			256,
			1);
	MyColorScale random;
	qsrand(time(0));
	for ( int index = 0; index < colors*3; ++index) {
		random.appendColor(QColor(RNDRGB,RNDRGB,RNDRGB));
	}
	setScale(random);
}

#ifdef DEBUG
void ColorScaleViewer::slot_ui_DUMMY() {
	QMessageBox::warning(this,QString("DUMMYTITLE"),QString("Nothing's worth to be announced."));
}
#endif

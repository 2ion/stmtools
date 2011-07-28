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

#include "ControllingWidget.h"

ControllingWidget::ControllingWidget(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);
	ui.frame_mxf1_imgparam->setVisible(false);
	connectSS();
}

ControllingWidget::~ControllingWidget()
{

}

void ControllingWidget::connectSS() {
	connect(ui.checkb_mxf1_useImage,
			SIGNAL(toggled(bool)),
			this,
			SLOT(slot_checkb_mxf1_useImage_toggle(bool)));
	connect(ui.tb_mxf1_browseImage,
			SIGNAL(clicked()),
			this,
			SLOT(slot_tb_mxf1_browseImage_clicked()));
	connect(ui.pb_mkxml_go,
			SIGNAL(clicked()),
			this,
			SLOT(slot_mkxml_go()));
	connect(ui.pb_mkxml_saveResults,
			SIGNAL(clicked()),
			this,
			SLOT(slot_mkxml_saveResults()));
}

void ControllingWidget::slot_checkb_mxf1_useImage_toggle(bool status) {
	if(!status && !ui.cb_mxf1_imgValueScaling->isChecked())
		ui.cb_mxf1_imgValueScaling->setChecked(true);
}

void ControllingWidget::slot_tb_mxf1_browseImage_clicked() {
	QString img_filepath = QFileDialog::getOpenFileName(this,
			"Select image file",
			"/",
			MKXML_IMAGE_FILTER);
	if(img_filepath != QString("")) {
		ui.le_mxf1_imagepath->setText(img_filepath);
		mxf1_deriveImageProperties(img_filepath);
	}
}

void ControllingWidget::mxf1_deriveImageProperties(const QString &imagepath) {
	QImage img(imagepath);
	if(img.isNull()) {
		QMessageBox::critical(this,
				"I/O error",
				"An image could not have been read from the specified file.");
		ui.le_mxf1_imagepath->clear();
		return;
	}
	// display image in the lineedit's tooltip
	ui.le_mxf1_imagepath->setToolTip(QString(MKXML_IMAGE_TOOLTIP1)+
			imagepath +
			QString(MKXML_IMAGE_TOOLTIP3));
	// adjust input masks
	QSize img_size = img.size();
	ui.mkxml_xsize->setValue(img_size.width());
	ui.mkxml_ysize->setValue(img_size.height());
	ui.sb_mxf1_originX->setMaximum(img_size.width());
	ui.sb_mxf1_originY->setMaximum(img_size.height());
	// determine & display the appropriate image format
	QImage::Format img_format;
	switch(img.format()) {
	// X Macro trick! google, if you do not get it.
#define X_FORMAT(value) case QImage::value:\
		ui.lbl_mxf1_imageFormatData->setText(#value);\
		img_format = QImage::value;\
		break;;
#include "xmacro_qimg_formats.h"
#undef X_FORMAT
	}
	// adjust "reported value per pixel" radio box selection
	// lookup: QtDoc->QImage::Format.
	if((int) img_format > 3)
		ui.rb_mxf1_reportOriginal->hide();
}

void ControllingWidget::slot_mkxml_go() {
	MakeXml op;
	op.params.x_size = ui.mkxml_xsize->value();
	op.params.y_size = ui.mkxml_ysize->value();
	op.params.z_top = (float) ui.mkxml_z_top->value();
	op.params.z_bottom = (float) ui.mkxml_z_bottom->value();
	op.params.identity_x = ui.mkxml_identity_x->value();
	op.params.identity_y = ui.mkxml_identity_y->value();
	op.params.identity_yl = ui.mkxml_identity_yl->value();
	op.params.identity_yr = ui.mkxml_identity_yr->value();
	op.params.p_permanence_x = (float) ui.mkxml_p_permanence_x->value();
	op.params.p_permanence_y = (float) ui.mkxml_p_permanence_y->value();
	op.params.p_permanence_yl = (float) ui.mkxml_p_permanence_yl->value();
	op.params.p_permanence_yr = (float) ui.mkxml_p_permanence_yr->value();
	op.params.img_source = ui.le_mxf1_imagepath->text();
	op.params.img_anchor_x = ui.sb_mxf1_originX->value();
	op.params.img_anchor_y = ui.sb_mxf1_originY->value();
	op.params.img_scale = ui.cb_mxf1_imgValueScaling->isChecked();
	op.params.img_use = ui.checkb_mxf1_useImage->isChecked();
	op.params.img_reported = ui.rb_mxf1_reportOriginal->isChecked() ? MakeXml::VAL :
		ui.rb_mxf1_reportRed->isChecked() ? MakeXml::RVAL :
		ui.rb_mxf1_reportGreen->isChecked() ? MakeXml::GVAL :
		ui.rb_mxf1_reportBlue->isChecked() ? MakeXml::BVAL :
		ui.rb_reportArithmeticMean->isChecked() ? MakeXml::MVAL :
		ui.rb_reportHarmonicalMean->isChecked() ? MakeXml::HVAL :
		MakeXml::GREY;

	mkxml_last_result = op.mkxml();
	ui.mkxml_viewer->clear();
	ui.mkxml_viewer->appendPlainText(QVariant(mkxml_last_result).toString());
	ui.pb_mkxml_saveResults->setEnabled(true);
}

void ControllingWidget::slot_mkxml_saveResults() {
	if(mkxml_last_result.isEmpty())
		return;
	QString whereTo = QFileDialog::getSaveFileName(this,
				QString("Select output file"));
	QFile target(whereTo);
		if(!target.open(QIODevice::WriteOnly))
			QMessageBox::information(this,
					QString("Error"),
					QString("The specified file is unaccessible."));
		target.write(mkxml_last_result);
		target.flush();
		target.close();
}

/********************************************************************************
** Form generated from reading UI file 'ControllingWidget.ui'
**
** Created: Wed Apr 6 13:04:29 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLLINGWIDGET_H
#define UI_CONTROLLINGWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ControllingWidgetClass
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *src_xmlfile;
    QGridLayout *gridLayout_2;
    QPushButton *pb_txtOpen;
    QLineEdit *le_txtFilepath;
    QLabel *lbl_txtValidity;
    QLabel *lbl_txtSanity;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pb_txtWrite;
    QSpacerItem *verticalSpacer;
    QWidget *make_textfile;
    QGridLayout *gridLayout_3;
    QLabel *label;
    QTabWidget *tabWidget_mkxmlfile;
    QWidget *tab_input;
    QGridLayout *gridLayout_4;
    QLabel *lbl_01imgdata_info;
    QHBoxLayout *horizontalLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QGridLayout *gridLayout_6;
    QFormLayout *formLayout;
    QLabel *lbl_mxf1_x;
    QSpinBox *mkxml_xsize;
    QLabel *lbl_mxf1_y;
    QSpinBox *mkxml_ysize;
    QLabel *lbl_mxf1_topValue;
    QDoubleSpinBox *mkxml_z_top;
    QLabel *lbl_mxf1_bottomValue;
    QDoubleSpinBox *mkxml_z_bottom;
    QLabel *lbl_mkxml_z_step_max;
    QDoubleSpinBox *mkxml_z_step_max;
    QLabel *lbl_mkxml_z_step_min;
    QDoubleSpinBox *mkxml_z_step_min;
    QLabel *lbl_mxf1_minIdentity;
    QSpinBox *mkxml_identity_x;
    QLabel *lbl_mxf1_maxIdentity;
    QSpinBox *mkxml_identity_y;
    QLabel *label_2;
    QSpinBox *mkxml_identity_yl;
    QLabel *label_3;
    QSpinBox *mkxml_identity_yr;
    QLabel *lbl_mxf1_layerPermHorizontal;
    QDoubleSpinBox *mkxml_p_permanence_x;
    QLabel *label_4;
    QDoubleSpinBox *mkxml_p_permanence_y;
    QLabel *label_5;
    QDoubleSpinBox *mkxml_p_permanence_yl;
    QLabel *label_6;
    QDoubleSpinBox *mkxml_p_permanence_yr;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkb_mxf1_useImage;
    QFrame *frame_mxf1_imgparam;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *le_mxf1_imagepath;
    QToolButton *tb_mxf1_browseImage;
    QHBoxLayout *horizontalLayout_6;
    QSpinBox *sb_mxf1_originX;
    QSpinBox *sb_mxf1_originY;
    QLabel *lbl_mxf1_origin;
    QLabel *lbl_mxf1_imagefile;
    QCheckBox *cb_mxf1_imgValueScaling;
    QRadioButton *rb_mxf1_reportOriginal;
    QLabel *lbl_mxf1_reportedImgValues;
    QRadioButton *rb_mxf1_reportRed;
    QRadioButton *rb_mxf1_reportGreen;
    QRadioButton *rb_mxf1_reportBlue;
    QRadioButton *rb_reportArithmeticMean;
    QLabel *lbl_mxf1_imageFormat;
    QLabel *lbl_mxf1_imageFormatData;
    QRadioButton *rb_reportHarmonicalMean;
    QRadioButton *rb_reportGrey;
    QSpacerItem *verticalSpacer_3;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pb_mkxml_go;
    QPushButton *pb_mkxml_saveResults;
    QSpacerItem *verticalSpacer_2;
    QPlainTextEdit *mkxml_viewer;
    QWidget *src_random;
    QWidget *src_image;
    QWidget *src_tcp;

    void setupUi(QWidget *ControllingWidgetClass)
    {
        if (ControllingWidgetClass->objectName().isEmpty())
            ControllingWidgetClass->setObjectName(QString::fromUtf8("ControllingWidgetClass"));
        ControllingWidgetClass->resize(648, 618);
        gridLayout = new QGridLayout(ControllingWidgetClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(ControllingWidgetClass);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        src_xmlfile = new QWidget();
        src_xmlfile->setObjectName(QString::fromUtf8("src_xmlfile"));
        gridLayout_2 = new QGridLayout(src_xmlfile);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pb_txtOpen = new QPushButton(src_xmlfile);
        pb_txtOpen->setObjectName(QString::fromUtf8("pb_txtOpen"));

        gridLayout_2->addWidget(pb_txtOpen, 0, 0, 1, 1);

        le_txtFilepath = new QLineEdit(src_xmlfile);
        le_txtFilepath->setObjectName(QString::fromUtf8("le_txtFilepath"));

        gridLayout_2->addWidget(le_txtFilepath, 0, 1, 1, 1);

        lbl_txtValidity = new QLabel(src_xmlfile);
        lbl_txtValidity->setObjectName(QString::fromUtf8("lbl_txtValidity"));

        gridLayout_2->addWidget(lbl_txtValidity, 1, 0, 1, 1);

        lbl_txtSanity = new QLabel(src_xmlfile);
        lbl_txtSanity->setObjectName(QString::fromUtf8("lbl_txtSanity"));

        gridLayout_2->addWidget(lbl_txtSanity, 1, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pb_txtWrite = new QPushButton(src_xmlfile);
        pb_txtWrite->setObjectName(QString::fromUtf8("pb_txtWrite"));
        pb_txtWrite->setCheckable(false);

        horizontalLayout->addWidget(pb_txtWrite);


        gridLayout_2->addLayout(horizontalLayout, 2, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 3, 0, 1, 1);

        tabWidget->addTab(src_xmlfile, QString());
        make_textfile = new QWidget();
        make_textfile->setObjectName(QString::fromUtf8("make_textfile"));
        gridLayout_3 = new QGridLayout(make_textfile);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label = new QLabel(make_textfile);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(8);
        label->setFont(font);
        label->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        label->setWordWrap(true);

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        tabWidget_mkxmlfile = new QTabWidget(make_textfile);
        tabWidget_mkxmlfile->setObjectName(QString::fromUtf8("tabWidget_mkxmlfile"));
        tab_input = new QWidget();
        tab_input->setObjectName(QString::fromUtf8("tab_input"));
        gridLayout_4 = new QGridLayout(tab_input);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        lbl_01imgdata_info = new QLabel(tab_input);
        lbl_01imgdata_info->setObjectName(QString::fromUtf8("lbl_01imgdata_info"));
        lbl_01imgdata_info->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        lbl_01imgdata_info->setWordWrap(true);

        gridLayout_4->addWidget(lbl_01imgdata_info, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        scrollArea = new QScrollArea(tab_input);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setLineWidth(0);
        scrollArea->setWidgetResizable(true);
        scrollArea->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 238, 431));
        gridLayout_6 = new QGridLayout(scrollAreaWidgetContents_2);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        lbl_mxf1_x = new QLabel(scrollAreaWidgetContents_2);
        lbl_mxf1_x->setObjectName(QString::fromUtf8("lbl_mxf1_x"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lbl_mxf1_x->sizePolicy().hasHeightForWidth());
        lbl_mxf1_x->setSizePolicy(sizePolicy);

        formLayout->setWidget(0, QFormLayout::LabelRole, lbl_mxf1_x);

        mkxml_xsize = new QSpinBox(scrollAreaWidgetContents_2);
        mkxml_xsize->setObjectName(QString::fromUtf8("mkxml_xsize"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(mkxml_xsize->sizePolicy().hasHeightForWidth());
        mkxml_xsize->setSizePolicy(sizePolicy1);
        mkxml_xsize->setMinimum(1);
        mkxml_xsize->setMaximum(999999999);
        mkxml_xsize->setValue(200);

        formLayout->setWidget(0, QFormLayout::FieldRole, mkxml_xsize);

        lbl_mxf1_y = new QLabel(scrollAreaWidgetContents_2);
        lbl_mxf1_y->setObjectName(QString::fromUtf8("lbl_mxf1_y"));
        sizePolicy.setHeightForWidth(lbl_mxf1_y->sizePolicy().hasHeightForWidth());
        lbl_mxf1_y->setSizePolicy(sizePolicy);

        formLayout->setWidget(1, QFormLayout::LabelRole, lbl_mxf1_y);

        mkxml_ysize = new QSpinBox(scrollAreaWidgetContents_2);
        mkxml_ysize->setObjectName(QString::fromUtf8("mkxml_ysize"));
        mkxml_ysize->setMinimum(1);
        mkxml_ysize->setMaximum(999999999);
        mkxml_ysize->setValue(200);

        formLayout->setWidget(1, QFormLayout::FieldRole, mkxml_ysize);

        lbl_mxf1_topValue = new QLabel(scrollAreaWidgetContents_2);
        lbl_mxf1_topValue->setObjectName(QString::fromUtf8("lbl_mxf1_topValue"));
        sizePolicy.setHeightForWidth(lbl_mxf1_topValue->sizePolicy().hasHeightForWidth());
        lbl_mxf1_topValue->setSizePolicy(sizePolicy);

        formLayout->setWidget(2, QFormLayout::LabelRole, lbl_mxf1_topValue);

        mkxml_z_top = new QDoubleSpinBox(scrollAreaWidgetContents_2);
        mkxml_z_top->setObjectName(QString::fromUtf8("mkxml_z_top"));
        mkxml_z_top->setDecimals(4);
        mkxml_z_top->setMaximum(999);
        mkxml_z_top->setSingleStep(0.0001);
        mkxml_z_top->setValue(5.5);

        formLayout->setWidget(2, QFormLayout::FieldRole, mkxml_z_top);

        lbl_mxf1_bottomValue = new QLabel(scrollAreaWidgetContents_2);
        lbl_mxf1_bottomValue->setObjectName(QString::fromUtf8("lbl_mxf1_bottomValue"));
        sizePolicy.setHeightForWidth(lbl_mxf1_bottomValue->sizePolicy().hasHeightForWidth());
        lbl_mxf1_bottomValue->setSizePolicy(sizePolicy);

        formLayout->setWidget(3, QFormLayout::LabelRole, lbl_mxf1_bottomValue);

        mkxml_z_bottom = new QDoubleSpinBox(scrollAreaWidgetContents_2);
        mkxml_z_bottom->setObjectName(QString::fromUtf8("mkxml_z_bottom"));
        mkxml_z_bottom->setDecimals(4);
        mkxml_z_bottom->setMaximum(999);
        mkxml_z_bottom->setSingleStep(0.0001);
        mkxml_z_bottom->setValue(1.4);

        formLayout->setWidget(3, QFormLayout::FieldRole, mkxml_z_bottom);

        lbl_mkxml_z_step_max = new QLabel(scrollAreaWidgetContents_2);
        lbl_mkxml_z_step_max->setObjectName(QString::fromUtf8("lbl_mkxml_z_step_max"));
        sizePolicy.setHeightForWidth(lbl_mkxml_z_step_max->sizePolicy().hasHeightForWidth());
        lbl_mkxml_z_step_max->setSizePolicy(sizePolicy);

        formLayout->setWidget(4, QFormLayout::LabelRole, lbl_mkxml_z_step_max);

        mkxml_z_step_max = new QDoubleSpinBox(scrollAreaWidgetContents_2);
        mkxml_z_step_max->setObjectName(QString::fromUtf8("mkxml_z_step_max"));
        mkxml_z_step_max->setDecimals(4);
        mkxml_z_step_max->setMaximum(999);
        mkxml_z_step_max->setSingleStep(0.0001);
        mkxml_z_step_max->setValue(1.3);

        formLayout->setWidget(4, QFormLayout::FieldRole, mkxml_z_step_max);

        lbl_mkxml_z_step_min = new QLabel(scrollAreaWidgetContents_2);
        lbl_mkxml_z_step_min->setObjectName(QString::fromUtf8("lbl_mkxml_z_step_min"));
        sizePolicy.setHeightForWidth(lbl_mkxml_z_step_min->sizePolicy().hasHeightForWidth());
        lbl_mkxml_z_step_min->setSizePolicy(sizePolicy);

        formLayout->setWidget(5, QFormLayout::LabelRole, lbl_mkxml_z_step_min);

        mkxml_z_step_min = new QDoubleSpinBox(scrollAreaWidgetContents_2);
        mkxml_z_step_min->setObjectName(QString::fromUtf8("mkxml_z_step_min"));
        mkxml_z_step_min->setDecimals(4);
        mkxml_z_step_min->setMaximum(999);
        mkxml_z_step_min->setSingleStep(0.0001);
        mkxml_z_step_min->setValue(0.1);

        formLayout->setWidget(5, QFormLayout::FieldRole, mkxml_z_step_min);

        lbl_mxf1_minIdentity = new QLabel(scrollAreaWidgetContents_2);
        lbl_mxf1_minIdentity->setObjectName(QString::fromUtf8("lbl_mxf1_minIdentity"));
        sizePolicy.setHeightForWidth(lbl_mxf1_minIdentity->sizePolicy().hasHeightForWidth());
        lbl_mxf1_minIdentity->setSizePolicy(sizePolicy);

        formLayout->setWidget(6, QFormLayout::LabelRole, lbl_mxf1_minIdentity);

        mkxml_identity_x = new QSpinBox(scrollAreaWidgetContents_2);
        mkxml_identity_x->setObjectName(QString::fromUtf8("mkxml_identity_x"));
        mkxml_identity_x->setValue(4);

        formLayout->setWidget(6, QFormLayout::FieldRole, mkxml_identity_x);

        lbl_mxf1_maxIdentity = new QLabel(scrollAreaWidgetContents_2);
        lbl_mxf1_maxIdentity->setObjectName(QString::fromUtf8("lbl_mxf1_maxIdentity"));
        sizePolicy.setHeightForWidth(lbl_mxf1_maxIdentity->sizePolicy().hasHeightForWidth());
        lbl_mxf1_maxIdentity->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setPointSize(9);
        lbl_mxf1_maxIdentity->setFont(font1);
        lbl_mxf1_maxIdentity->setFrameShape(QFrame::NoFrame);

        formLayout->setWidget(7, QFormLayout::LabelRole, lbl_mxf1_maxIdentity);

        mkxml_identity_y = new QSpinBox(scrollAreaWidgetContents_2);
        mkxml_identity_y->setObjectName(QString::fromUtf8("mkxml_identity_y"));
        mkxml_identity_y->setValue(70);

        formLayout->setWidget(7, QFormLayout::FieldRole, mkxml_identity_y);

        label_2 = new QLabel(scrollAreaWidgetContents_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(8, QFormLayout::LabelRole, label_2);

        mkxml_identity_yl = new QSpinBox(scrollAreaWidgetContents_2);
        mkxml_identity_yl->setObjectName(QString::fromUtf8("mkxml_identity_yl"));
        mkxml_identity_yl->setValue(41);

        formLayout->setWidget(8, QFormLayout::FieldRole, mkxml_identity_yl);

        label_3 = new QLabel(scrollAreaWidgetContents_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(9, QFormLayout::LabelRole, label_3);

        mkxml_identity_yr = new QSpinBox(scrollAreaWidgetContents_2);
        mkxml_identity_yr->setObjectName(QString::fromUtf8("mkxml_identity_yr"));
        mkxml_identity_yr->setValue(24);

        formLayout->setWidget(9, QFormLayout::FieldRole, mkxml_identity_yr);

        lbl_mxf1_layerPermHorizontal = new QLabel(scrollAreaWidgetContents_2);
        lbl_mxf1_layerPermHorizontal->setObjectName(QString::fromUtf8("lbl_mxf1_layerPermHorizontal"));
        sizePolicy.setHeightForWidth(lbl_mxf1_layerPermHorizontal->sizePolicy().hasHeightForWidth());
        lbl_mxf1_layerPermHorizontal->setSizePolicy(sizePolicy);

        formLayout->setWidget(10, QFormLayout::LabelRole, lbl_mxf1_layerPermHorizontal);

        mkxml_p_permanence_x = new QDoubleSpinBox(scrollAreaWidgetContents_2);
        mkxml_p_permanence_x->setObjectName(QString::fromUtf8("mkxml_p_permanence_x"));
        mkxml_p_permanence_x->setValue(0.42);

        formLayout->setWidget(10, QFormLayout::FieldRole, mkxml_p_permanence_x);

        label_4 = new QLabel(scrollAreaWidgetContents_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        formLayout->setWidget(11, QFormLayout::LabelRole, label_4);

        mkxml_p_permanence_y = new QDoubleSpinBox(scrollAreaWidgetContents_2);
        mkxml_p_permanence_y->setObjectName(QString::fromUtf8("mkxml_p_permanence_y"));
        mkxml_p_permanence_y->setValue(0.9);

        formLayout->setWidget(11, QFormLayout::FieldRole, mkxml_p_permanence_y);

        label_5 = new QLabel(scrollAreaWidgetContents_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(12, QFormLayout::LabelRole, label_5);

        mkxml_p_permanence_yl = new QDoubleSpinBox(scrollAreaWidgetContents_2);
        mkxml_p_permanence_yl->setObjectName(QString::fromUtf8("mkxml_p_permanence_yl"));
        mkxml_p_permanence_yl->setValue(0.41);

        formLayout->setWidget(12, QFormLayout::FieldRole, mkxml_p_permanence_yl);

        label_6 = new QLabel(scrollAreaWidgetContents_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(13, QFormLayout::LabelRole, label_6);

        mkxml_p_permanence_yr = new QDoubleSpinBox(scrollAreaWidgetContents_2);
        mkxml_p_permanence_yr->setObjectName(QString::fromUtf8("mkxml_p_permanence_yr"));
        mkxml_p_permanence_yr->setValue(0.1);

        formLayout->setWidget(13, QFormLayout::FieldRole, mkxml_p_permanence_yr);


        gridLayout_6->addLayout(formLayout, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents_2);

        horizontalLayout_2->addWidget(scrollArea);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        checkb_mxf1_useImage = new QCheckBox(tab_input);
        checkb_mxf1_useImage->setObjectName(QString::fromUtf8("checkb_mxf1_useImage"));

        verticalLayout->addWidget(checkb_mxf1_useImage);

        frame_mxf1_imgparam = new QFrame(tab_input);
        frame_mxf1_imgparam->setObjectName(QString::fromUtf8("frame_mxf1_imgparam"));
        frame_mxf1_imgparam->setFrameShape(QFrame::StyledPanel);
        frame_mxf1_imgparam->setFrameShadow(QFrame::Raised);
        gridLayout_5 = new QGridLayout(frame_mxf1_imgparam);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        le_mxf1_imagepath = new QLineEdit(frame_mxf1_imgparam);
        le_mxf1_imagepath->setObjectName(QString::fromUtf8("le_mxf1_imagepath"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(le_mxf1_imagepath->sizePolicy().hasHeightForWidth());
        le_mxf1_imagepath->setSizePolicy(sizePolicy2);
        le_mxf1_imagepath->setReadOnly(true);

        horizontalLayout_3->addWidget(le_mxf1_imagepath);

        tb_mxf1_browseImage = new QToolButton(frame_mxf1_imgparam);
        tb_mxf1_browseImage->setObjectName(QString::fromUtf8("tb_mxf1_browseImage"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(tb_mxf1_browseImage->sizePolicy().hasHeightForWidth());
        tb_mxf1_browseImage->setSizePolicy(sizePolicy3);

        horizontalLayout_3->addWidget(tb_mxf1_browseImage);


        gridLayout_5->addLayout(horizontalLayout_3, 0, 1, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        sb_mxf1_originX = new QSpinBox(frame_mxf1_imgparam);
        sb_mxf1_originX->setObjectName(QString::fromUtf8("sb_mxf1_originX"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(sb_mxf1_originX->sizePolicy().hasHeightForWidth());
        sb_mxf1_originX->setSizePolicy(sizePolicy4);

        horizontalLayout_6->addWidget(sb_mxf1_originX);

        sb_mxf1_originY = new QSpinBox(frame_mxf1_imgparam);
        sb_mxf1_originY->setObjectName(QString::fromUtf8("sb_mxf1_originY"));
        sizePolicy4.setHeightForWidth(sb_mxf1_originY->sizePolicy().hasHeightForWidth());
        sb_mxf1_originY->setSizePolicy(sizePolicy4);

        horizontalLayout_6->addWidget(sb_mxf1_originY);


        gridLayout_5->addLayout(horizontalLayout_6, 5, 0, 2, 2);

        lbl_mxf1_origin = new QLabel(frame_mxf1_imgparam);
        lbl_mxf1_origin->setObjectName(QString::fromUtf8("lbl_mxf1_origin"));

        gridLayout_5->addWidget(lbl_mxf1_origin, 4, 0, 1, 2);

        lbl_mxf1_imagefile = new QLabel(frame_mxf1_imgparam);
        lbl_mxf1_imagefile->setObjectName(QString::fromUtf8("lbl_mxf1_imagefile"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(lbl_mxf1_imagefile->sizePolicy().hasHeightForWidth());
        lbl_mxf1_imagefile->setSizePolicy(sizePolicy5);

        gridLayout_5->addWidget(lbl_mxf1_imagefile, 0, 0, 1, 1);

        cb_mxf1_imgValueScaling = new QCheckBox(frame_mxf1_imgparam);
        cb_mxf1_imgValueScaling->setObjectName(QString::fromUtf8("cb_mxf1_imgValueScaling"));
        cb_mxf1_imgValueScaling->setChecked(true);

        gridLayout_5->addWidget(cb_mxf1_imgValueScaling, 7, 0, 1, 2);

        rb_mxf1_reportOriginal = new QRadioButton(frame_mxf1_imgparam);
        rb_mxf1_reportOriginal->setObjectName(QString::fromUtf8("rb_mxf1_reportOriginal"));

        gridLayout_5->addWidget(rb_mxf1_reportOriginal, 9, 0, 1, 2);

        lbl_mxf1_reportedImgValues = new QLabel(frame_mxf1_imgparam);
        lbl_mxf1_reportedImgValues->setObjectName(QString::fromUtf8("lbl_mxf1_reportedImgValues"));

        gridLayout_5->addWidget(lbl_mxf1_reportedImgValues, 8, 0, 1, 2);

        rb_mxf1_reportRed = new QRadioButton(frame_mxf1_imgparam);
        rb_mxf1_reportRed->setObjectName(QString::fromUtf8("rb_mxf1_reportRed"));

        gridLayout_5->addWidget(rb_mxf1_reportRed, 10, 0, 1, 2);

        rb_mxf1_reportGreen = new QRadioButton(frame_mxf1_imgparam);
        rb_mxf1_reportGreen->setObjectName(QString::fromUtf8("rb_mxf1_reportGreen"));

        gridLayout_5->addWidget(rb_mxf1_reportGreen, 11, 0, 1, 2);

        rb_mxf1_reportBlue = new QRadioButton(frame_mxf1_imgparam);
        rb_mxf1_reportBlue->setObjectName(QString::fromUtf8("rb_mxf1_reportBlue"));

        gridLayout_5->addWidget(rb_mxf1_reportBlue, 12, 0, 1, 1);

        rb_reportArithmeticMean = new QRadioButton(frame_mxf1_imgparam);
        rb_reportArithmeticMean->setObjectName(QString::fromUtf8("rb_reportArithmeticMean"));
        sizePolicy1.setHeightForWidth(rb_reportArithmeticMean->sizePolicy().hasHeightForWidth());
        rb_reportArithmeticMean->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(rb_reportArithmeticMean, 13, 0, 1, 2);

        lbl_mxf1_imageFormat = new QLabel(frame_mxf1_imgparam);
        lbl_mxf1_imageFormat->setObjectName(QString::fromUtf8("lbl_mxf1_imageFormat"));
        sizePolicy.setHeightForWidth(lbl_mxf1_imageFormat->sizePolicy().hasHeightForWidth());
        lbl_mxf1_imageFormat->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(lbl_mxf1_imageFormat, 2, 0, 1, 2);

        lbl_mxf1_imageFormatData = new QLabel(frame_mxf1_imgparam);
        lbl_mxf1_imageFormatData->setObjectName(QString::fromUtf8("lbl_mxf1_imageFormatData"));
        sizePolicy2.setHeightForWidth(lbl_mxf1_imageFormatData->sizePolicy().hasHeightForWidth());
        lbl_mxf1_imageFormatData->setSizePolicy(sizePolicy2);
        lbl_mxf1_imageFormatData->setWordWrap(true);

        gridLayout_5->addWidget(lbl_mxf1_imageFormatData, 3, 0, 1, 2);

        rb_reportHarmonicalMean = new QRadioButton(frame_mxf1_imgparam);
        rb_reportHarmonicalMean->setObjectName(QString::fromUtf8("rb_reportHarmonicalMean"));
        sizePolicy1.setHeightForWidth(rb_reportHarmonicalMean->sizePolicy().hasHeightForWidth());
        rb_reportHarmonicalMean->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(rb_reportHarmonicalMean, 14, 0, 1, 1);

        rb_reportGrey = new QRadioButton(frame_mxf1_imgparam);
        rb_reportGrey->setObjectName(QString::fromUtf8("rb_reportGrey"));

        gridLayout_5->addWidget(rb_reportGrey, 15, 0, 1, 1);


        verticalLayout->addWidget(frame_mxf1_imgparam);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);


        horizontalLayout_2->addLayout(verticalLayout);


        gridLayout_4->addLayout(horizontalLayout_2, 4, 0, 1, 1);

        tabWidget_mkxmlfile->addTab(tab_input, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout_4 = new QHBoxLayout(tab);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        pb_mkxml_go = new QPushButton(tab);
        pb_mkxml_go->setObjectName(QString::fromUtf8("pb_mkxml_go"));

        verticalLayout_2->addWidget(pb_mkxml_go);

        pb_mkxml_saveResults = new QPushButton(tab);
        pb_mkxml_saveResults->setObjectName(QString::fromUtf8("pb_mkxml_saveResults"));
        pb_mkxml_saveResults->setEnabled(false);

        verticalLayout_2->addWidget(pb_mkxml_saveResults);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout_4->addLayout(verticalLayout_2);

        mkxml_viewer = new QPlainTextEdit(tab);
        mkxml_viewer->setObjectName(QString::fromUtf8("mkxml_viewer"));

        horizontalLayout_4->addWidget(mkxml_viewer);

        tabWidget_mkxmlfile->addTab(tab, QString());

        gridLayout_3->addWidget(tabWidget_mkxmlfile, 1, 0, 1, 1);

        tabWidget->addTab(make_textfile, QString());
        src_random = new QWidget();
        src_random->setObjectName(QString::fromUtf8("src_random"));
        tabWidget->addTab(src_random, QString());
        src_image = new QWidget();
        src_image->setObjectName(QString::fromUtf8("src_image"));
        tabWidget->addTab(src_image, QString());
        src_tcp = new QWidget();
        src_tcp->setObjectName(QString::fromUtf8("src_tcp"));
        tabWidget->addTab(src_tcp, QString());

        gridLayout->addWidget(tabWidget, 2, 0, 1, 1);


        retranslateUi(ControllingWidgetClass);
        QObject::connect(checkb_mxf1_useImage, SIGNAL(toggled(bool)), frame_mxf1_imgparam, SLOT(setVisible(bool)));
        QObject::connect(cb_mxf1_imgValueScaling, SIGNAL(toggled(bool)), mkxml_z_top, SLOT(setEnabled(bool)));
        QObject::connect(cb_mxf1_imgValueScaling, SIGNAL(toggled(bool)), mkxml_z_bottom, SLOT(setEnabled(bool)));

        tabWidget->setCurrentIndex(1);
        tabWidget_mkxmlfile->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ControllingWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *ControllingWidgetClass)
    {
        ControllingWidgetClass->setWindowTitle(QApplication::translate("ControllingWidgetClass", "ControllingWidget", 0, QApplication::UnicodeUTF8));
        pb_txtOpen->setText(QApplication::translate("ControllingWidgetClass", "Open", 0, QApplication::UnicodeUTF8));
        lbl_txtValidity->setText(QApplication::translate("ControllingWidgetClass", "File sanity:", 0, QApplication::UnicodeUTF8));
        lbl_txtSanity->setText(QApplication::translate("ControllingWidgetClass", "<>", 0, QApplication::UnicodeUTF8));
        pb_txtWrite->setText(QApplication::translate("ControllingWidgetClass", "Write to buffer", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(src_xmlfile), QApplication::translate("ControllingWidgetClass", "src:xmlfile", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ControllingWidgetClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<table style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Henceforth, a STM dummy scan procedure, including parametrical and image data, will be generated and written to a XML file fitting into the src:xmlfile tool. So, Please proceed by number.</p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
        lbl_01imgdata_info->setText(QApplication::translate("ControllingWidgetClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<table style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">As for the image values, an existing image can be used, or they will be pulled out of nowhere.</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
        lbl_mxf1_x->setText(QApplication::translate("ControllingWidgetClass", "x size", 0, QApplication::UnicodeUTF8));
        mkxml_xsize->setSuffix(QApplication::translate("ControllingWidgetClass", " px", 0, QApplication::UnicodeUTF8));
        lbl_mxf1_y->setText(QApplication::translate("ControllingWidgetClass", "y size", 0, QApplication::UnicodeUTF8));
        mkxml_ysize->setSuffix(QApplication::translate("ControllingWidgetClass", " px", 0, QApplication::UnicodeUTF8));
        lbl_mxf1_topValue->setText(QApplication::translate("ControllingWidgetClass", "z top", 0, QApplication::UnicodeUTF8));
        lbl_mxf1_bottomValue->setText(QApplication::translate("ControllingWidgetClass", "Z bottom", 0, QApplication::UnicodeUTF8));
        lbl_mkxml_z_step_max->setText(QApplication::translate("ControllingWidgetClass", "z step max", 0, QApplication::UnicodeUTF8));
        lbl_mkxml_z_step_min->setText(QApplication::translate("ControllingWidgetClass", "z step min", 0, QApplication::UnicodeUTF8));
        lbl_mxf1_minIdentity->setText(QApplication::translate("ControllingWidgetClass", "identity x", 0, QApplication::UnicodeUTF8));
        lbl_mxf1_maxIdentity->setText(QApplication::translate("ControllingWidgetClass", "identity y", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ControllingWidgetClass", "identity yl", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ControllingWidgetClass", "identity yr", 0, QApplication::UnicodeUTF8));
        lbl_mxf1_layerPermHorizontal->setText(QApplication::translate("ControllingWidgetClass", "P permanence x", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ControllingWidgetClass", "P permanence y", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("ControllingWidgetClass", "P permanence yl", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("ControllingWidgetClass", "P permanence yr", 0, QApplication::UnicodeUTF8));
        checkb_mxf1_useImage->setText(QApplication::translate("ControllingWidgetClass", "Use an image file as value source", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        le_mxf1_imagepath->setToolTip(QApplication::translate("ControllingWidgetClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<table style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/icons/folder-saved.svg.png\" /></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        tb_mxf1_browseImage->setText(QApplication::translate("ControllingWidgetClass", "...", 0, QApplication::UnicodeUTF8));
        sb_mxf1_originX->setPrefix(QApplication::translate("ControllingWidgetClass", "x: ", 0, QApplication::UnicodeUTF8));
        sb_mxf1_originY->setPrefix(QApplication::translate("ControllingWidgetClass", "y: ", 0, QApplication::UnicodeUTF8));
        lbl_mxf1_origin->setText(QApplication::translate("ControllingWidgetClass", "Origin of operation area:", 0, QApplication::UnicodeUTF8));
        lbl_mxf1_imagefile->setText(QApplication::translate("ControllingWidgetClass", "File:", 0, QApplication::UnicodeUTF8));
        cb_mxf1_imgValueScaling->setText(QApplication::translate("ControllingWidgetClass", "Scale image values", 0, QApplication::UnicodeUTF8));
        rb_mxf1_reportOriginal->setText(QApplication::translate("ControllingWidgetClass", "Original value", 0, QApplication::UnicodeUTF8));
        lbl_mxf1_reportedImgValues->setText(QApplication::translate("ControllingWidgetClass", "Reported value per pixel:", 0, QApplication::UnicodeUTF8));
        rb_mxf1_reportRed->setText(QApplication::translate("ControllingWidgetClass", "Red", 0, QApplication::UnicodeUTF8));
        rb_mxf1_reportGreen->setText(QApplication::translate("ControllingWidgetClass", "Green", 0, QApplication::UnicodeUTF8));
        rb_mxf1_reportBlue->setText(QApplication::translate("ControllingWidgetClass", "Blue", 0, QApplication::UnicodeUTF8));
        rb_reportArithmeticMean->setText(QApplication::translate("ControllingWidgetClass", "Arithmetich mean over RGB", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lbl_mxf1_imageFormat->setToolTip(QApplication::translate("ControllingWidgetClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<table style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:15px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#f6f6f6;\"><span style=\" font-family:'Verdana'; font-size:large; font-weight:600; color:#363534; background-color:#f6f6f6;\">enum QImage::Format</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Verdana'; font-size:medium; color:#363534;\">The following image formats are availab"
                        "le in Qt. Values greater than QImage::Format_RGB16 were added in Qt 4.4. See the notes after the table.</span></p>\n"
"<table border=\"0\" style=\" margin-top:0px; margin-bottom:25px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\" bgcolor=\"#f6f6f6\">\n"
"<tr>\n"
"<td></td>\n"
"<td></td>\n"
"<td></td></tr>\n"
"<tr>\n"
"<td bgcolor=\"#e1e1e1\" style=\" padding-left:15; padding-right:15; padding-top:5; padding-bottom:5;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Verdana'; font-size:medium; font-weight:600; color:#363534; background-color:#e1e1e1;\">Constant</span></p></td>\n"
"<td bgcolor=\"#e1e1e1\" style=\" padding-left:15; padding-right:15; padding-top:5; padding-bottom:5;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Verdana'; fon"
                        "t-size:medium; font-weight:600; color:#363534; background-color:#e1e1e1;\">Value</span></p></td>\n"
"<td bgcolor=\"#e1e1e1\" style=\" padding-left:15; padding-right:15; padding-top:5; padding-bottom:5;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Verdana'; font-size:medium; font-weight:600; color:#363534; background-color:#e1e1e1;\">Description</span></p></td></tr>\n"
"<tr>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier'; font-size:medium; color:#363534;\">QImage::Format_Invalid</span></p></td>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; marg"
                        "in-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier'; font-size:medium; color:#363534;\">0</span></p></td>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Verdana'; font-size:medium; color:#363534;\">The image is invalid.</span></p></td></tr>\n"
"<tr>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier'; font-size:medium; color:#363534;\">QImage::Format_Mono</span></p></td>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; "
                        "margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier'; font-size:medium; color:#363534;\">1</span></p></td>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Verdana'; font-size:medium; color:#363534;\">The image is stored using 1-bit per pixel. Bytes are packed with the most significant bit (MSB) first.</span></p></td></tr>\n"
"<tr>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier'; font-size:medium; color:#363534;\">QImage::Format_MonoLSB</span></p></td>\n"
"<td style=\" vertical-align:t"
                        "op; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier'; font-size:medium; color:#363534;\">2</span></p></td>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Verdana'; font-size:medium; color:#363534;\">The image is stored using 1-bit per pixel. Bytes are packed with the less significant bit (LSB) first.</span></p></td></tr>\n"
"<tr>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier'; "
                        "font-size:medium; color:#363534;\">QImage::Format_Indexed8</span></p></td>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier'; font-size:medium; color:#363534;\">3</span></p></td>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Verdana'; font-size:medium; color:#363534;\">The image is stored using 8-bit indexes into a colormap.</span></p></td></tr>\n"
"<tr>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-in"
                        "dent:0px;\"><span style=\" font-family:'Courier New,courier'; font-size:medium; color:#363534;\">QImage::Format_RGB32</span></p></td>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier'; font-size:medium; color:#363534;\">4</span></p></td>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Verdana'; font-size:medium; color:#363534;\">The image is stored using a 32-bit RGB format (0xffRRGGBB).</span></p></td></tr>\n"
"<tr>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; "
                        "margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier'; font-size:medium; color:#363534;\">QImage::Format_ARGB32</span></p></td>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier'; font-size:medium; color:#363534;\">5</span></p></td>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Verdana'; font-size:medium; color:#363534;\">The image is stored using a 32-bit ARGB format (0xAARRGGBB).</span></p></td></tr>\n"
"<tr>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-"
                        "bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier'; font-size:medium; color:#363534;\">QImage::Format_ARGB32_Premultiplied</span></p></td>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier'; font-size:medium; color:#363534;\">6</span></p></td>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Verdana'; font-size:medium; color:#363534;\">The image is stored using a premultiplied 32-bit ARGB format (0xAARRGGBB), i.e. the red, green, and blue cha"
                        "nnels are multiplied by the alpha component divided by 255. (If RR, GG, or BB has a higher value than the alpha channel, the results are undefined.) Certain operations (such as image composition using alpha blending) are faster using premultiplied ARGB32 than with plain ARGB32.</span></p></td></tr>\n"
"<tr>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier'; font-size:medium; color:#363534;\">QImage::Format_RGB16</span></p></td>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier'; font-size:medium; color:#363534;\">7</span></p></td>\n"
"<td style=\" vertical"
                        "-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Verdana'; font-size:medium; color:#363534;\">The image is stored using a 16-bit RGB format (5-6-5).</span></p></td></tr>\n"
"<tr>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier'; font-size:medium; color:#363534;\">QImage::Format_ARGB8565_Premultiplied</span></p></td>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier'; font"
                        "-size:medium; color:#363534;\">8</span></p></td>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Verdana'; font-size:medium; color:#363534;\">The image is stored using a premultiplied 24-bit ARGB format (8-5-6-5).</span></p></td></tr>\n"
"<tr>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier'; font-size:medium; color:#363534;\">QImage::Format_RGB666</span></p></td>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0"
                        "; text-indent:0px;\"><span style=\" font-family:'Courier New,courier'; font-size:medium; color:#363534;\">9</span></p></td>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Verdana'; font-size:medium; color:#363534;\">The image is stored using a 24-bit RGB format (6-6-6). The unused most significant bits is always zero.</span></p></td></tr>\n"
"<tr>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier'; font-size:medium; color:#363534;\">QImage::Format_ARGB6666_Premultiplied</span></p></td>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; pa"
                        "dding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier'; font-size:medium; color:#363534;\">10</span></p></td>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Verdana'; font-size:medium; color:#363534;\">The image is stored using a premultiplied 24-bit ARGB format (6-6-6-6).</span></p></td></tr>\n"
"<tr>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier'; font-size:medium; color:#363534;\">QImage::Format_RGB555</span></p></td>\n"
"<td style"
                        "=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier'; font-size:medium; color:#363534;\">11</span></p></td>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Verdana'; font-size:medium; color:#363534;\">The image is stored using a 16-bit RGB format (5-5-5). The unused most significant bit is always zero.</span></p></td></tr>\n"
"<tr>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'C"
                        "ourier New,courier'; font-size:medium; color:#363534;\">QImage::Format_ARGB8555_Premultiplied</span></p></td>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier'; font-size:medium; color:#363534;\">12</span></p></td>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Verdana'; font-size:medium; color:#363534;\">The image is stored using a premultiplied 24-bit ARGB format (8-5-5-5).</span></p></td></tr>\n"
"<tr>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left"
                        ":0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier'; font-size:medium; color:#363534;\">QImage::Format_RGB888</span></p></td>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier'; font-size:medium; color:#363534;\">13</span></p></td>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Verdana'; font-size:medium; color:#363534;\">The image is stored using a 24-bit RGB format (8-8-8).</span></p></td></tr>\n"
"<tr>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
""
                        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier'; font-size:medium; color:#363534;\">QImage::Format_RGB444</span></p></td>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier'; font-size:medium; color:#363534;\">14</span></p></td>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Verdana'; font-size:medium; color:#363534;\">The image is stored using a 16-bit RGB format (4-4-4). The unused bits are always zero.</span></p></td></tr>\n"
"<tr>\n"
"<td style=\" ver"
                        "tical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier'; font-size:medium; color:#363534;\">QImage::Format_ARGB4444_Premultiplied</span></p></td>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier'; font-size:medium; color:#363534;\">15</span></p></td>\n"
"<td style=\" vertical-align:top; padding-left:20; padding-right:15; padding-top:3; padding-bottom:3;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Verdana'; font-size:medium; color:#363534;\">The image is stored using a pr"
                        "emultiplied 16-bit ARGB format (4-4-4-4).</span></p></td></tr></table>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Verdana'; font-size:medium; color:#363534;\">This text has been copied from the Qt documentation addressed as follows:</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Verdana'; font-size:medium; color:#363534;\">&quot;qthelp://com.trolltech.qt.470/qdoc/qimage.html#Format-enum&quot;.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Verdana'; font-size:medium; color:#363534;\">All copyrights held by its procuder do fully apply.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0"
                        "; text-indent:0px; font-family:'Verdana'; font-size:medium; color:#363534;\"></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        lbl_mxf1_imageFormat->setText(QApplication::translate("ControllingWidgetClass", "Image format:", 0, QApplication::UnicodeUTF8));
        lbl_mxf1_imageFormatData->setText(QApplication::translate("ControllingWidgetClass", "?", 0, QApplication::UnicodeUTF8));
        rb_reportHarmonicalMean->setText(QApplication::translate("ControllingWidgetClass", "Harmonical mean over RGB", 0, QApplication::UnicodeUTF8));
        rb_reportGrey->setText(QApplication::translate("ControllingWidgetClass", "Grey value", 0, QApplication::UnicodeUTF8));
        tabWidget_mkxmlfile->setTabText(tabWidget_mkxmlfile->indexOf(tab_input), QApplication::translate("ControllingWidgetClass", "&Input", 0, QApplication::UnicodeUTF8));
        pb_mkxml_go->setText(QApplication::translate("ControllingWidgetClass", "&Compute simulation", 0, QApplication::UnicodeUTF8));
        pb_mkxml_saveResults->setText(QApplication::translate("ControllingWidgetClass", "&Save results to file", 0, QApplication::UnicodeUTF8));
        tabWidget_mkxmlfile->setTabText(tabWidget_mkxmlfile->indexOf(tab), QApplication::translate("ControllingWidgetClass", "&Exec", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(make_textfile), QApplication::translate("ControllingWidgetClass", "mk:xmlfile", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(src_random), QApplication::translate("ControllingWidgetClass", "src:random", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(src_image), QApplication::translate("ControllingWidgetClass", "src:image", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(src_tcp), QApplication::translate("ControllingWidgetClass", "src:tcp", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ControllingWidgetClass: public Ui_ControllingWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLLINGWIDGET_H

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

#ifndef MYCOLORSCALE_H_
#define MYCOLORSCALE_H_

#include <Qt>
#include <QtAlgorithms>
#include <QtDebug>
#include <QtCore/QObject>
#include <QtCore/QHashIterator>
#include <QtCore/QDataStream>
#include <QtCore/QByteArray>
#include <QtCore/QVector>
#include <QtXml/QXmlStreamReader>
#include <QtXml/QXmlStreamWriter>
#include <QtXml/QXmlStreamAttributes>
#include <QtGui/QMenu>
#include <QtGui/QAction>
#include <gui/colorScales/ColorOperations.h>
#include <gui/colorScales/ColorScale.h>
#include <general/maindefs.h>

/*!
 * \file MyColorScale.h
 * Implements MyColorScale.
 *
 * \class MyColorScale
 * \brief Represents a color scale and allows various customization
 * and edition of both color scales defined by the user or loaded from
 * a plugin employing methods from ColorOperations.
 *
 * MyColorScale makes handling and editing of color scales easier. Aside from
 * operating on its colors, it provides diverse signals and slots making the
 * creating of color scale using components a heyday.
 *
 * \todo Fully implement the basic facilities.
 * \todo Create a filter interface using ColorOperations.
 * \todo Employ signal_changed().
 *
 * \fn QMenu MyColorScale::actionMenu()
 * \brief Results in a QMenu holding QAction objects being each linked
 * to a available operation MyColorScale is capable of.
 * \return A QMenu usable appropriable for GUI creation.
 *
 * The resulting QMenu *is* a list of actions the user can perform on this
 * special color scale. It is for example used in ColorScaleViewer's toolbox.
 *
 * \fn QColor MyColorScale::color(quint32)
 * \return The color at <I>index</I>.
 * \param index If of invalid value, an 'invalid' QColor will be returned.
 *
 * \fn void MyColorScale::setName(const QString&)
 * \brief Sets the color scale's name.
 * \param name Does nothing if name is empty.
 *
 * \fn bool MyColorScale::setColor(quint32,const QColor&)
 * \brief Sets the color at index to color.
 * \return False if at index did not exist already a color.
 * \note Gaps within the scale are not allowed.
 *
 * \fn quint32 MyColorScale::appendColor(const QColor&)
 * \brief Appends color to the scale.
 * \return Index of the appended color.
 *
 * \fn bool MyColorScale::swapColors(quint32,quint32)
 * \brief Swaps colors of indizes A and B.
 * \return False if any invalid index has been specified.
 * swapColors does not create non-existent indizes.
 *
 * \fn bool MyColorScale::deleteColor(quint32)
 * \brief Removes color at index from the scale.
 * \note All indizes greater than index will be lowered by one.
 * \return False if an invalid index has been specified.
 *
 * \fn bool MyColorScale::invertScale(bool)
 * \brief Inverts all colors throughout the scale.
 * \return False if anything went wrong.
 * \param withAlpha If true, the alpha channel's value will be inverted.
 * \todo Hereby, a very simple inversion alogorithm is being used.
 * It should be accompanied by some mightier version.
 *
 * \fn bool MyColorScale::commonRGBValue(enum commonValue,quint32)
 * \brief All colors of the scale shall have the RGB component inCommon in common,
 * namely beset with value.
 * \param inCommon If non-RGB, false will be returned and nothing have been done.
 * \return False if value > 255.
 *
 * \fn bool MyColorScale::commonHSVValue(enum commonValue,quint32)
 * \brief Like commonRGBValue(), but using the HSV system.
 * @see commonRGBValue()
 *
 * \fn void MyColorScale::signal_chaned()
 * \brief Emitted whenever a manipulative operation has been successfully completed.
 *
 * \fn QByteArray MyColorScale::getBinary()
 * \brief Returns a QByteArray containing all data of the scale.
 *
 * Using MyColorScale::setBinary(), a MyColorScale may be constructed or fed
 * with a QByteArray from this very method. It will hold all data having been
 * previously available.
 *
 * The serialized data format:
 * 1) qint32 (number of colors)
 * 2) {QColor}*N (each representing a single scale color)
 * 3) QString (scale name)
 * 4) QString (description field)
 *
 * \fn QByteArray MyColorScale::toXML()
 * \brief Produces a XML representation of the color scale.
 *
 * The QByteArray contains valid UTF-8 encoded XML, can be written to a
 * regular file (as implemented in ColorScaleViewer) or be imported therefrom
 * (also implemented in ColorScaleViewer).
 *
 * I think the XML format can be easily recognized from the source code.
 *
 * For XML import, you have to use the MyColorScale::fromXML() methods, each of them
 * works similar. Imported properties and colors will REPLACE all existing properties
 * and colors.
 *
 * \todo I decided against making the parser after the simpliest thinkable
 * pattern, because there may be some functionality requiring a more complex
 * parse tree in the future.
 *
 * \fn bool MyColorScale::fromXML(const QString &)
 * \fn bool MyColorScale::fromXML(const QByteArray &)
 *
 *
 */

#ifndef MCS_XML_NAMESPACE
#define MCS_XML_NAMESPACE ("com.wordpress.jeojohn.stmtool")
#endif
#ifndef MCS_XML_ROOTELEMENT
#define MCS_XML_ROOTELEMENT ("colorscale")
#endif

class MyColorScale : public QObject, public ColorScale {
	Q_OBJECT
public:
	enum commonValue {
		RED, GREEN, BLUE, ALPHA,
		HUE, VALUE, SATURATION
	};
	enum XMLMethod {
		APPEND, REPLACE
	};

	MyColorScale();
	/*! @name Wrapping constructors
	 * These are COPYING constructors / operators, the passed values
	 * will be not touched.
	 * \todo Employ const specifiers.
	 *  */
	//@{
	MyColorScale(MyColorScale &base);
	MyColorScale(MyColorScale *base);
	MyColorScale(ColorScale *base);
	void operator=(MyColorScale &ref);
	//@}
	~MyColorScale();

	/*! @name ColorScale interface */
	//@{
	QHash<quint32,QColor> colors();
	quint32 indizes();
	QHash<quint32,QColor>* data();
	QString name();
	//@}

	QMenu actionMenu();
	QColor color(quint32 index);
	void setName(const QString &name);
	void setDescription(const QString &descr);
	QString description();
	bool setColor(quint32 index, const QColor &color);
	quint32 appendColor(const QColor &color);
	quint32 insertColor(const QColor &color, quint32 at);
	void appendColors(QList<QColor> colors);
	bool swapColors(quint32 indexA, quint32 indexB);
	bool deleteColor(quint32 index);
	bool invertScale(bool withAlpha = false);
	bool commonRGBValue(enum commonValue inCommon, quint32 value);
	bool commonHSVValue(enum commonValue inCommon, quint32 value);
	bool clearScale();

	/*! @name XML data export | import*/
	//@{
	QByteArray toXML();
	bool fromXML(const QByteArray &xml);
	bool fromXML(const QString &xml);
	//@}

signals:
	void signal_changed();
private:
	QHash<quint32,QColor> scale;
	QString my_name;
	QString my_description;
};

#endif /* MyColorScale.h */

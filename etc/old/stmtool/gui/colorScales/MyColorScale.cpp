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

#include "MyColorScale.h"

MyColorScale::MyColorScale() {

}

MyColorScale::MyColorScale(MyColorScale &base) {
	scale = base.colors();
	my_name = base.name();
}

MyColorScale::MyColorScale(MyColorScale *base) {
	if(base) {
		scale = base->colors();
		my_name = base->name();
		my_description = base->description();
	}
}

MyColorScale::MyColorScale(ColorScale *base) {
	if(base) {
		scale = base->colors();
		my_name = base->name();
	}
}

MyColorScale::~MyColorScale() {
}

QHash<quint32,QColor> MyColorScale::colors() {
	return scale;
}

QHash<quint32,QColor>* MyColorScale::data() {
	return &scale;
}

quint32 MyColorScale::indizes() {
	return scale.size();
}

QString MyColorScale::name() {
	return my_name;
}

void MyColorScale::setName(const QString &name) {
		my_name = name;
}

QColor MyColorScale::color(quint32 index) {
	if(!scale.contains(index))
		return QColor();
	return scale.value(index);
}

bool MyColorScale::setColor(quint32 index, const QColor &color) {
	if(scale.contains(index))
		scale.remove(index);
	scale.insert(index,color);
	return true;
}

quint32 MyColorScale::appendColor(const QColor &color) {
	quint32 new_index = (quint32) scale.size();
	scale.insert(new_index,color);
	return new_index;
}

bool MyColorScale::swapColors(quint32 indexA, quint32 indexB) {
	if(scale.contains(indexA) && scale.contains(indexB)) {
		QColor tmp = scale.value(indexA);
		setColor(indexA,scale.value(indexB));
		setColor(indexB,tmp);
		return true;
	}
	return false;
}

bool MyColorScale::deleteColor(quint32 index) {
	if(scale.contains(index)) {
		scale.remove(index);
		return true;
	}
	return false;
}

bool MyColorScale::invertScale(bool withAlpha) {
	if(scale.size() == 0)
		return false;
	if(withAlpha) {
		QHashIterator<quint32,QColor> iter(scale);
		while(iter.hasNext()) {
			iter.next();
			// this prevents multiple calls to iter.key() due
			// INVERT_RGBA's usage.
			QColor toInvert = color(iter.key());
			//setColor(iter.key(),INVERT_RGBA(toInvert));
			setColor(iter.key(),ColorOperations::invert(toInvert));
		}
		return true;
	} else {
		QHashIterator<quint32,QColor> iter(scale);
		while(iter.hasNext()) {
			iter.next();
			QColor toInvert = color(iter.key());
			setColor(iter.key(),INVERT_RGB(toInvert));
		}
		return true;
	}
	return false;
}

bool MyColorScale::clearScale() {
	if(scale.size() == NULL)
		return true;
	scale.clear();
	return true;
}

bool MyColorScale::commonHSVValue(enum commonValue inCommon, quint32 value) {
	if(scale.size() == 0)
		return false;
	QHashIterator<quint32,QColor> iter(scale);
	while(iter.hasNext()) {
		iter.next();
		switch(inCommon) {
		case HUE:
			;
		case SATURATION:;
		case VALUE:;
		}
	}
	return true;
}

bool MyColorScale::commonRGBValue(enum commonValue inCommon, quint32 value) {
	return true;
}

void MyColorScale::operator =(MyColorScale &ref) {
	if(scale.size() != 0)
		scale.clear();
	scale = ref.colors();
	my_name = ref.name();
	my_description = ref.description();
}

QMenu MyColorScale::actionMenu() {
	QMenu to_return;
}

void MyColorScale::setDescription(const QString & descr) {
	my_description = descr;
}

QString MyColorScale::description() {
	return my_description;
}

QByteArray MyColorScale::toXML() {
	QByteArray result;
	QXmlStreamWriter xmlwriter(&result);
	xmlwriter.setAutoFormatting(true);
	xmlwriter.setAutoFormattingIndent(-1);
	xmlwriter.writeStartDocument();
	xmlwriter.writeStartElement(QString(MCS_XML_ROOTELEMENT));
	xmlwriter.writeAttribute(QString("application"),QString("stmtool"));
	xmlwriter.writeAttribute(QString("appversion"),QString(_INFO_VERSION_));
	xmlwriter.writeAttribute(QString("name"),name());
	xmlwriter.writeAttribute(QString("description"),description());
	QHashIterator<quint32,QColor> colorIter(scale);
	while(colorIter.hasNext()) {
		colorIter.next();
		QColor theColor = colorIter.value();
		xmlwriter.writeStartElement(QString("color"));
		xmlwriter.writeAttribute(QString("red"),
				QVariant(theColor.red()).toString());
		xmlwriter.writeAttribute(QString("green"),
						QVariant(theColor.green()).toString());
		xmlwriter.writeAttribute(QString("blue"),
						QVariant(theColor.blue()).toString());
		xmlwriter.writeAttribute(QString("alpha"),
						QVariant(theColor.alpha()).toString());
		xmlwriter.writeEndElement();
	}
	xmlwriter.writeEndDocument();
	return result;
}

bool MyColorScale::fromXML(const QByteArray &xml) {
	QXmlStreamReader xmlreader(xml);
	QList<QColor> parsedColors;
	QXmlStreamAttributes attribs;
	while(!xmlreader.atEnd()) {
		switch(xmlreader.readNext()) {
		case QXmlStreamReader::Invalid:
			return false;
			;
		case QXmlStreamReader::StartDocument:
			break;
			;
		case QXmlStreamReader::EndDocument:
			appendColors(parsedColors);
			break;
			;
		case QXmlStreamReader::StartElement:
			attribs = xmlreader.attributes();
			if(xmlreader.name() == MCS_XML_ROOTELEMENT) {
				setName(attribs.value("name").toString());
				setDescription(attribs.value("description").toString());
				break;
			}
			if(xmlreader.name() == "color") {
				parsedColors.append(QColor(QVariant(attribs.value("red").toString()).toInt(),
						QVariant(attribs.value("green").toString()).toInt(),
						QVariant(attribs.value("blue").toString()).toInt(),
						QVariant(attribs.value("alpha").toString()).toInt()));
			}
			break;
			;
		case QXmlStreamReader::EndElement:
			break;
			;
		case QXmlStreamReader::Characters:
			break;
			;
		case QXmlStreamReader::Comment:
			break;
			;
		case QXmlStreamReader::DTD:
			break;
			;
		case QXmlStreamReader::EntityReference:
			break;
			;
		case QXmlStreamReader::ProcessingInstruction:
			break;
			;
		case QXmlStreamReader::NoToken:
			break;
			;
		default:
			break;
			;
		}
	}
	return true;
}

bool MyColorScale::fromXML(const QString &xml) {
	QXmlStreamReader xmlreader(xml);
	QList<QColor> parsedColors;
	QXmlStreamAttributes attribs;
	while(!xmlreader.atEnd()) {
		switch(xmlreader.readNext()) {
		case QXmlStreamReader::Invalid:
			return false;
			;
		case QXmlStreamReader::StartDocument:
			break;
			;
		case QXmlStreamReader::EndDocument:
			appendColors(parsedColors);
			break;
			;
		case QXmlStreamReader::StartElement:
			attribs = xmlreader.attributes();
			if(xmlreader.name() == MCS_XML_ROOTELEMENT) {
				setName(attribs.value("name").toString());
				setDescription(attribs.value("description").toString());
				break;
			}
			if(xmlreader.name() == "color") {
				parsedColors.append(QColor(QVariant(attribs.value("red").toString()).toInt(),
						QVariant(attribs.value("green").toString()).toInt(),
						QVariant(attribs.value("blue").toString()).toInt(),
						QVariant(attribs.value("alpha").toString()).toInt()));
			}
			break;
			;
		case QXmlStreamReader::EndElement:
			break;
			;
		case QXmlStreamReader::Characters:
			break;
			;
		case QXmlStreamReader::Comment:
			break;
			;
		case QXmlStreamReader::DTD:
			break;
			;
		case QXmlStreamReader::EntityReference:
			break;
			;
		case QXmlStreamReader::ProcessingInstruction:
			break;
			;
		case QXmlStreamReader::NoToken:
			break;
			;
		default:
			break;
			;
		}
	}
	return true;
}

quint32 MyColorScale::insertColor(const QColor &color, quint32 at) {
	if(at > (scale.size() - 1))
		return appendColor(color);
	QVector<quint32> keys = scale.uniqueKeys().toVector();
	qSort(keys.begin(),keys.end());
	for(int index = at + 1; index < keys.size(); ++index) {
		keys.replace(index,keys.value(index)+1);
	}
	keys.insert(at,at);

}

void MyColorScale::appendColors(QList<QColor> colors) {
	QListIterator<QColor> citer(colors);
	while(citer.hasNext()) {
		appendColor(citer.next());
	}
}

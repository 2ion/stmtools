#include "colorScale_KODAK1.h"
#define SCALE_NAME ("KODAK1")
#define INSERT_COLOR(r,g,b) do{scale.insert(next_index++,QColor((r),(g),(b)));}while(0);

colorScale_KODAK1::colorScale_KODAK1() {
	build();
	next_index = 0;
}

colorScale_KODAK1::~colorScale_KODAK1() {
}

QHash<quint32,QColor> colorScale_KODAK1::colors() {
	return scale;

}

QHash<quint32,QColor>* colorScale_KODAK1::data() {
	return &scale;
}

quint32 colorScale_KODAK1::indizes() {
	return scale.size();
}

QString colorScale_KODAK1::name() {
	return QString((SCALE_NAME));
}
void colorScale_KODAK1::build() {
	/*
	int red = 255;
	int green = 255;
	int blue = 255;
	while((red != 0) &&
			(green != 0) &&
			(blue != 0)
			) {
		for(int Hindex = 1; Hindex < 100; Hindex++) {
			if((Hindex % 2 == 0) && (green != 0))
				green = green - 2 * Hindex;
			if((Hindex % 4 == 0) && (blue != 0)) {
				blue = blue - 4 * Hindex;
			}
			if(red != 0)
				red = (quint32) (0xFFFFFF - 1.5 * Hindex);
			scale.insert((quint32) (Hindex - 1),QColor(0,0,0));
		}
	}
	*/



}

Q_EXPORT_PLUGIN2(colorScale_KODAK1,colorScale_KODAK1)

#ifndef COLORSCALE_KODAK1_H_
#define COLORSCALE_KODAK1_H_

/* interface */
#include <ColorScale.h>
#include <QtPlugin>


class colorScale_KODAK1 : public QObject, public ColorScale {
	Q_OBJECT
	Q_INTERFACES(ColorScale)
public:
	colorScale_KODAK1();
	~colorScale_KODAK1();

	/* interface */
	QHash<quint32,QColor> colors();
	QHash<quint32,QColor>* data();
	quint32 indizes();
	QString name();
private:
	void build(void);
	quint32 next_index;
	QHash<quint32,QColor> scale;
};

#endif /* colorScale_KODAK1.h */

#ifndef ISIMPLE_H_
#define ISIMPLE_H_

class iSimple {
public:
	virtual QString sayHello();
};

Q_DECLARE_INTERFACE(iSimple,"simpleI");


#endif /* iSimple.h */

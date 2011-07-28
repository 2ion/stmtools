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

/*!
 * \file mkxml.h
 * Functions on producing binary XML data representing
 * dummy STM output.
 *
 * \class MakeXml
 * \brief Produces an pattern encoded in binary XML resembling the output of
 * an STM scan.
 *
 * MakeXml requires several input paramters to be set, of which all are contained in MakeXml::params.
 * Validation of this settings can be achieved by calling MakeXml::isValid(). Output values will base on either
 * scaled random values, original values read from an existing sample image, or value scaling may be applied to the
 * latter input stream, too.
 *
 * \section mkxml_algorithm The underlying algorithm.
 * Our algrithm's result will a list of vectors (x,y,z) of size x*y, where x,y are the coordinates
 * in the STM scan's plane of a point, and z is by value the numeric representation of an assumed tip deflection.
 * Internally, the data will be represented as an 3-dimensional array of double values.
 *
 * \enum MakeXml::ImgReport
 * \brief If an image is used as value source, these are values thereby, if the image's pixels do contain more information
 * entities as a single value can express, the reported value is being chosen.
 *
 * For further reading, have a look into the qtdoc on enum QImage::Format.
 *
 * \enum MakeXml::PersistenceLevel
 * \brief Every point within the x-y-plane inherits one or more of the hereby discerned 'degrees of freedom' in things
 * of value permanence.
 *
 * In order to describe a point upon whom more than one degree of permanence has been bestowed, use bitwise OR junctions.
 *
 * \struct MakeXml::Neighbours
 * \brief Holds data implicitly describing a fields relative position to others.
 *
 * \struct MakeXml::Parameters
 * \brief The set of parameters MakeXml requires in order to do its work.
 *
 * A set of parameters is required for every generation procedure. You may validate a struct MakeXml::Parameters via
 * MakeXml::isValid().
 *
 * \fn QByteArray MakeXml::mkxml()
 * \brief Returns the generated data in binary XML.
 *
 * All generated data is being stored in a double array valmap where every value is accessible via valmap[column][line].
 * In the process, for every field its relations are determined and stored in a struct MakeXml::Neighbours. Then, a pointer to
 * the existing value map is added, and passed onto MakeXml::zValue(), a function returning a value for the field having been
 * described in the aforementioned way.
 *
 * \fn bool MakeXml::isValid()
 * \brief Returns true, if the existing parametrical values were in whatsoever ways 
 */
#ifndef MKXML_H_
#define MKXML_H_
#include <Qt>
#include <QtGlobal>
#include <QtAlgorithms>
#include <QtDebug>
#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QString>
#include <QtCore/QVector>
#include <QtCore/QFile>
#include <QtGui/QImage>
#include <QtXml/QXmlStreamWriter>

#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <cstdarg>

#include <iDevice.h>
#include <src/stmDevice.h>

#define ONESHIFTL(x) (1 << (x))
/*!
 * Produces a value addressed with (x,y) from a 2d-array.
 * pointer := pointer to 1st element of the array
 * x := column of value
 * y := line of value
 * columns := linewidth
 */
#define NARRAY_VAL(pointer,columns,x,y) *((pointer)+(x)+((y)*(columns)))
#define ZUFALL (float) qrand() / (float) RAND_MAX
#define TOSTR(x) QVariant((x)).toString()
#define PSTR(x) #x
#define WATTR(writer,attribute) writer.writeAttribute(#attribute,TOSTR(attribute))
#define MKXML_START_ELEMENT ("stmscan")

#define ECHO qDebug() << __FILE__ << __LINE__

class MakeXml {
public:
	MakeXml() {
		qsrand(time(NULL));
#ifdef DEBUG
		dbgCounters.random_results = 0;
		dbgCounters.image_results = 0;
		dbgCounters.permanence_results = 0;
#endif
	}
	~MakeXml() {}

	enum ImgReport {
		VAL,								//!< Orignal image value. Possible only using true black/white or evenly greyscaled images
		RVAL,								//!< Red RGB component
		BVAL,								//!< Blue RGB component
		GVAL,								//!< Green RGB component
		MVAL,								//!< Arithmetic mean of RGB
		HVAL,								//!< Harmonical mean of RGB
		GREY								//!< qGrey(QRgb)
	};

	enum PersistenceLevel {
		NOP = ONESHIFTL(0),					//!< Field is not obliged to any permanence
		H = ONESHIFTL(1),					//!< Field is part of a HORIZONTAL permanence, where the latter's origin is the LOWER RIGHT
		V = ONESHIFTL(2),					//!< Field is part of a VERTICAL permanence, where the latter's origin is the field BENEATH
		VL = ONESHIFTL(3),					//!< Field is part of a DIAGONAL permanence, where the latter's origin is the LOWER RIGHT field
		VR = ONESHIFTL(4)					//!< Field is part of a DIAGONAL permanence, where the latter's origin is the LOWER LEFT field
	};

	struct Neighbours {
			int pLevel;						//!< For a determined field, herein all possible types of permanence are stored as OR junctions of enum PersistenceLevel
			float *valmap;					//!< 1st element of output value map (allocated by MakeXml::mkxml())
		};

	struct Parameters {
		qint32 x_size; 						//!< Width of output map (length of X axis)
		qint32 y_size;						//!< Height of output map (length of Y axis)
		float z_top;						//!< Maximum z value output
		float z_bottom;					//!< Minimum z value output
		float z_step_max;					//!< Maximum dZ between fields both being or not being part of a permanence
		float z_step_min;      			//!< Minimum dZ between fields both being or not being part of a permanence
		qint32 identity_x;					//!< Longest x permanence in fields, val < 2 => infinite. For no permanence, set p_permanence_* = 0.0
		qint32 identity_y;					//!< Longest y permanence in fields
		qint32 identity_yl;					//!< Longest yl permanence in fields
		qint32 identity_yr;					//!< Longest yr permanence in fields
		/*! @name Probabilities for particular cases of permanence. Sum has to be 1, with any number of zero.*/
		//@{
		float p_permanence_nop;			//!< Probability that no permanence occurs.
		float p_permanence_x;				//!< Probability of a x permanence on valid fields
		float p_permanence_y;				//!< Probability of a y permanence on valid fields
		float p_permanence_yl;				//!< Probability of a yl permanence on valid fields
		float p_permanence_yr;				//!< Probability of a yr permanence on valid fields
		//@}
		/*! @name For image input */
		//@{
		enum ImgReport img_reported;		//!< Component of image pixel values that will be used
		QString img_source;					//!< Path to the image to use
		qint32 img_anchor_x;				//!< With an area defined by Parameters::x_size, Parameters::y_size, its upper left anchor point's X coordinate.
		qint32 img_anchor_y;				//!< With an area defined by Parameters::x_size, Parameters::y_size, its upper left anchor point's Y coordinate.
		bool img_scale;						//!< If true, value scaling will apply on values obtained from an image
		bool img_use;						//!< If false, none of image-related memebers will be given any heed
		//@}
	};


	template<typename T>
	static T sum(int elements, ...) {
		va_list VAL;
		va_start(VAL,elements);
		T sum = (T) 0;
		for(int i = 0; i < elements; ++i) {
			/*! FIXME
			 * \todo This move has to be done because
			 * g++ promotes a float to a double here and
			 * threatens to abort our program! One should
			 * check out the compiler flags.
			 */
			if(sizeof(T) == sizeof(float)) {
				sum += (T) va_arg(VAL,double);
			} else {
				sum += (T) va_arg(VAL,T);
			}
		}
		return sum;
	}

	template<typename T>
	static T reciproke(T value) {
		return (T) (  ((T) 1) / value );
	}

	template<typename T>
	static T reciprokeSum(int elements, ...) {
		va_list VAL;
		va_start(VAL,elements);
		T sum = (T) 0;
		for(int i = 0; i < elements; ++i) {
			/*! FIXME
			 * \todo This move has to be done because
			 * g++ promotes a float to a double here and
			 * threatens to abort our program! One should
			 * check out the compiler flags.
			 */
			if(sizeof(T) == sizeof(float)) {
				sum += (T) va_arg(VAL,double);
			} else {
				sum += (T) va_arg(VAL,T);
			}
		}
		return (T) (((T) 1.0) / sum);
	}

	template<typename T>
	static T* valPtr(T value) {
		T *ptr = (T*) malloc(sizeof(T));
		*ptr = value;
		return ptr;
	}

	template<typename T>
	static const T* cvalPtr(T value) {
		return const_cast<const T*>(MakeXml::valPtr<T>(value));
	}

	QByteArray mkxml() {
		//ECHO << "MakeXml::mkxml()";
		QByteArray result;
		precomputations.precompute(const_cast<const struct Parameters*>(&params));
		if(!isValid())
			return result;
		float valmap[params.x_size][params.y_size];
		for (int line = 0; line < params.y_size; ++line) {
			for (int column = 0; column < params.x_size; ++column) {
				//ECHO << line << " " << column;
				struct Neighbours nigh = {persistenceLevel(column,line), &valmap[0][0]};
				valmap[column][line] = zValue(column, line, nigh);
			}
		}

		QXmlStreamWriter xmlw(&result);
		xmlw.setAutoFormatting(true);
		xmlw.setAutoFormattingIndent(-1);
		xmlw.writeStartDocument();

#define a_w(attribute) WATTR(xmlw,attribute)
#define e_start(name) xmlw.writeStartElement(#name)
#define e_end xmlw.writeEndElement()
		e_start(stmscan);
			xmlw.writeAttribute("generator", __FILE__);
			xmlw.writeAttribute("version", __DATE__);

			e_start(input);

				a_w(params.x_size);
				a_w(params.y_size);
				a_w(params.z_top);
				a_w(params.z_bottom);
				a_w(params.z_step_max);
				a_w(params.z_step_min);
				a_w(params.identity_x);
				a_w(params.identity_y);
				a_w(params.identity_yl);
				a_w(params.identity_yr);
				a_w(params.p_permanence_x);
				a_w(params.p_permanence_y);
				a_w(params.p_permanence_yl);
				a_w(params.p_permanence_yr);

				e_start(imagerc);
				a_w(params.img_source);
				a_w(params.img_reported);
				a_w(params.img_anchor_x);
				a_w(params.img_anchor_y);
				a_w(params.img_scale);
				a_w(params.img_use);
				e_end;

			e_end;

			e_start(output);
			for(int y = 0; y < params.y_size; ++y)
				for(int x = 0; x < params.x_size; ++x) {
					e_start(vector);
					xmlw.writeAttribute("x", TOSTR(x));
					xmlw.writeAttribute("y", TOSTR(y));
					xmlw.writeAttribute("z", TOSTR(NARRAY_VAL(&valmap[0][0],params.x_size,x,y)));
					e_end;
				}
			e_end;

		e_end;
#undef e_end
#undef e_start
#undef a_w
		xmlw.writeEndDocument();
#ifdef DEBUG
		dbgCounters.print();
#endif
		return result;
	}

	bool isValid() {
		return true;
		if(params.img_use) {
			if(params.img_source.isEmpty())
				return false;
			QFile stub(params.img_source);
			return stub.exists() && stub.isReadable();
		}
		return true;
	}

	struct Parameters params;

private:

	int persistenceLevel(int column, int line) {
		//ECHO << "persistenceLevel()";
		if(column == 0 && line == 0) {
			//ECHO << PSTR(NOP);
			return NOP;
		}
		if(column == 0 && line > 0) {
			//ECHO << PSTR(V | L);
			return V | VL;
		}
		if(column > 0 && line == 0) {
			//ECHO << PSTR(H);
			return H;
		}
		if(column == params.x_size - 1) {
			//ECHO << PSTR(H | VR | V);
			return H | VR | V;
		}
		//ECHO << PSTR(H | VL | VR | V);
		return H | VL | VR | V;
	}

	float* checkPermanenceLimit(enum PersistenceLevel pLevel, int column, int line, struct Neighbours *nigh) {
		float aZ = 0.0;
		quint32 pCounter = 2;
		switch(pLevel) {
		case NOP:
			return NULL;
			break;
			;
		case H:
			if(params.identity_x <= 2)
				return &NARRAY_VAL(nigh->valmap,params.x_size,column-1,line);

			aZ = NARRAY_VAL(nigh->valmap,params.x_size,column-1,line);

			for(int c = column - 2; c > -1; --c, ++pCounter)
				if(NARRAY_VAL(nigh->valmap,params.x_size,c,line) != aZ)
					break;

			if((params.identity_x - pCounter) < 1)
				return NULL;

			return &NARRAY_VAL(nigh->valmap,params.x_size,column-1,line);
			break;
			;
		case V:
			if(params.identity_y <= 2)
				return &NARRAY_VAL(nigh->valmap,params.x_size,column,line-1);

			aZ = NARRAY_VAL(nigh->valmap,params.x_size,column,line-1);

			for(int l = line-2; l > -1; --l, ++pCounter)
				if(NARRAY_VAL(nigh->valmap,params.x_size,column,l) != aZ)
					break;

			if((params.identity_y - pCounter < 1))
				return NULL;

			return &NARRAY_VAL(nigh->valmap,params.x_size,column,line-1);
			break;
			;
		case VL:
			if(params.identity_yl <= 2)
				return &NARRAY_VAL(nigh->valmap,params.x_size,column-1,line-1);

			aZ = NARRAY_VAL(nigh->valmap,params.x_size,column-1,line-1);

			for(int l = line - 2, c = column - 2; l > -1 && c > -1; --l, --c, ++pCounter)
				if(NARRAY_VAL(nigh->valmap,params.x_size,c,l) != aZ)
					break;

			if((params.identity_yl - pCounter) < 1)
				return NULL;

			return &NARRAY_VAL(nigh->valmap,params.x_size,column-1,line-1);
			break;
			;
		case VR:
			if(params.identity_yr <= 2)
				return &NARRAY_VAL(nigh->valmap,params.x_size,column+1,line-1);

			aZ = NARRAY_VAL(nigh->valmap,params.x_size,column+1,line-1);

			for(int l = line - 2, c = column + 2; l > -1 && c < params.x_size; --l, ++c, ++pCounter)
				if(NARRAY_VAL(nigh->valmap,params.x_size,c,l) != aZ)
					break;

			if((params.identity_yr - pCounter) < 1)
				return NULL;

			return &NARRAY_VAL(nigh->valmap,params.x_size,column+1,line-1);
			break;
			;
		default:
			;
		}
		return NULL;
	}

	float zValue(int column, int line, struct Neighbours nigh) {
		float RESULT = 0.0;
		bool voteV, voteVL, voteH, voteVR = false;
		enum PersistenceLevel pLevel = NOP;

		/* Determine if, and if yes what kind of, permanence shall be applied to
		 * the new z value.
		 * 1. Since there currently are CONCURRING kinds of permanence, we are
		 * going to elect a single one of a kind.
		 * 2. If any permanence: check whether the permanence limit stored in params.identity_* is surpassed.
		 * 3. Determine z value.
		 */
		switch(nigh.pLevel) {
		case NOP:
			pLevel = NOP;
			break;
			;
		case H:
			pLevel = incase(params.p_permanence_x) ? H : NOP;
			break;
			;
		case V | VL:
			voteV = incase(params.p_permanence_y);
			voteVL = incase(params.p_permanence_yl);
			pLevel = !(voteV || voteVL) ? NOP : (voteV && voteVL ? (incase(0.5) ? V : VL) : (voteV ? V : VL));
			break;
		;
		case H | VR | V:
			voteH = incase(params.p_permanence_x);
			voteVR = incase(params.p_permanence_yr);
			voteV = incase(params.p_permanence_y);
			if(voteH || voteVR || voteV) {
				if(voteH && (voteVR || voteV)) {
					if(voteVR && voteV) {
						/*! \todo Optimize by producing pattern 011 || 101 || 110, and deciding by incase(0.5).*/
						while(
								(voteH && (voteVR || voteV)) ||
								(!voteH && (voteVR && voteV))
								) {
							voteH = incase(params.p_permanence_x);
							voteVR = incase(params.p_permanence_yr);
							voteV = incase(params.p_permanence_y);
						}
						// now, we have one out of: 100, 010, 001
						pLevel = voteH ? H : (voteVR ? VR : V);
					} else {
						if(voteVR) {
							pLevel = incase(0.5) ? H : VR;
						} else {
							pLevel = incase(0.5) ? H : V;
						}
					}
				} else {
					if(!voteH && (voteVR || voteV)) {
						if(voteVR && voteV) {
							pLevel = incase(0.5) ? VR : V;
						} else {
							if(voteVR) {
								pLevel = VR;
							} else {
								pLevel = V;
							}
						}
					}
				}

			} else {
				pLevel = NOP;
			}
			break;
		;
		case H | VL | VR | V:
			voteH = incase(params.p_permanence_x);
			voteV = incase(params.p_permanence_y);
			voteVL = incase(params.p_permanence_yl);
			voteVR = incase(params.p_permanence_yr);
			if(voteH || voteV || voteVL || voteVR) {
				if(voteH && (voteV || voteVL || voteVR)) {
					if(voteV && (voteVL || voteVR)) {
						if(voteVL && voteVR) {
							// voteH,voteV,voteVL,voteVR
							while(
									(voteH && (voteV || voteVL || voteVR)) ||
									(!voteH && ( (voteV && voteVL) || (voteV && voteVR) || (voteVL && voteVR) ))
									) {
								voteH = incase(params.p_permanence_x);
								voteV = incase(params.p_permanence_y);
								voteVL = incase(params.p_permanence_yl);
								voteVR = incase(params.p_permanence_yr);
							}
							pLevel = voteH ? H : (voteV ? V : (voteVL ? VL : VR));
						} else {
							if(voteVL) {
								//voteH,voteV,voteVL
								while(
										(voteH && (voteV || voteVL)) ||
										(!voteH && (voteV && voteVL))
										) {
									voteH = incase(params.p_permanence_x);
									voteV = incase(params.p_permanence_y);
									voteVL = incase(params.p_permanence_yl);
								}
								pLevel = voteH ? H : (voteV ? V : VL);
							} else {
								//voteH,voteV,VoteVR
								while(
										(voteH && (voteV || voteVR)) ||
										(!voteH && (voteV && voteVR))
										) {
									voteH = incase(params.p_permanence_x);
									voteV = incase(params.p_permanence_y);
									voteVR = incase(params.p_permanence_yr);
								}
								pLevel = voteH ? H : (voteV ? V : VR);
							}
						}
					} else {
						if(!voteV && (voteVL || voteVR)) {
							if(voteVL && voteVR) {
								//voteH,voteVL,voteVR
								while(
										(voteH && (voteVL || voteVR)) ||
										(!voteH && (voteVL && voteVR))
										) {
									voteH = incase(params.p_permanence_x);
									voteVL = incase(params.p_permanence_yl);
									voteVR = incase(params.p_permanence_yr);
								}
								pLevel = voteH ? H : (voteVL ? VL : VR);
							} else {
								if(voteVL) {
									//voteH,voteVL
									pLevel = incase(0.5) ? H : VL;
								} else {
									//voteH,voteVR
									pLevel = incase(0.5) ? H : VR;
								}
							}
						} else {
							pLevel = H;
						}
					}
				} else {
					if(!voteH && (voteV || voteVL || voteVR)) {
						if(voteV && (voteVL || voteVR)) {
							if(voteVL && voteVR) {
								while(
										(voteV && (voteVL || voteVR)) ||
										(!voteV && (voteVL && voteVR))
										) {
									voteV = incase(params.p_permanence_y);
									voteVL = incase(params.p_permanence_yl);
									voteVR = incase(params.p_permanence_yr);
								}
								pLevel = voteV ? V : (voteVL ? VL : VR);
							} else {
								if(voteVL) {
									pLevel = incase(0.5) ? V : VL;
								} else {
									pLevel = incase(0.5) ? V : VR;
								}
							}
						} else {
							if(!voteV && (voteVL || voteVR)) {
								if(voteVL && voteVR) {
									pLevel = incase(0.5) ? VL : VR;
								} else {
									if(voteVL) {
										pLevel = VL;
									} else {
										pLevel = VR;
									}
								}
							} else {
								pLevel = NOP;
							}
						}
					}
				}
			} else {
				pLevel = NOP;
			}
			break;
		;
		default:
			pLevel = NOP;
		}

#ifdef DEBUG
		if(pLevel != NOP) {
			++dbgCounters.permanence_results;
		} else {
			if(params.img_use) {
				++dbgCounters.image_results;
			} else {
				++dbgCounters.random_results;
			}
		}
#endif

		if(pLevel != NOP) {
			float *copydouble = checkPermanenceLimit(pLevel,column,line,&nigh);
			if(copydouble)
				RESULT = *copydouble;
		} else {
			if(params.img_use) {
				RESULT = imagePixelValue(column,line);
			} else {
				RESULT = randomValue();
				//qDebug() << "RND result" << RESULT;
			}
		}

		//applyLimitersFactors(&RESULT,column,line);
		//ECHO << line << column << RESULT;
		//qDebug() << RESULT;
		return RESULT;
	}

	bool incase(float p) {
		if(p == 1.0)
			return true;
		if(p == 0.0)
			return false;
#undef DEBUG
#ifdef DEBUG
		float r = ZUFALL;
		qDebug() << "incase() I:" << p << "R:" << r;
		if(r >= p)
			return true;
		return false;
#else
		if( ( ZUFALL ) >= p)
					return true;
				return false;
#endif
#ifndef DEBUG
#define DEBUG
#endif
	}


/*!
 * \param permanence_level := (H)|(V | VL)|(H | V | VR)|(H | V | VL | VR)
 * \param ... P(NOP), P(H) [ , ... , P(VR) ]
 *
 */
	////0 1 2 3 4 5 6 7 8 9 10
	enum PersistenceLevel pickPermanence(int permanence_level) {
		float rndnum = ZUFALL;

		switch(permanence_level) {
		case H:
			if(params.p_permanence_nop == 0.0 &&
					params.p_permanence_x == 0.0)
				return NOP;

			if(params.p_permanence_nop == 0.0)
				return H;

			if(params.p_permanence_x == 0.0)
				return NOP; // Permanence is exceptional!

			if(params.p_permanence_nop == params.p_permanence_x)
				if(rndnum == 0.5) {
					while(rndnum == 0.5) {
						rndnum = ZUFALL;
					}
					return *precomputations.pickPermanence.case_nop_h.p_nop < rndnum ? H : NOP;
				} else {
					return *precomputations.pickPermanence.case_nop_h.p_nop < rndnum ? H : NOP;
				}

			if(*precomputations.pickPermanence.case_nop_h.p_nop >
					*precomputations.pickPermanence.case_nop_h.p_h) {

				while(rndnum == *precomputations.pickPermanence.case_nop_h.p_h)
					rndnum = ZUFALL;
				return *precomputations.pickPermanence.case_nop_h.p_h < rndnum ? NOP : H;

			} else {

				while(rndnum == *precomputations.pickPermanence.case_nop_h.p_nop)
					rndnum = ZUFALL;
				return *precomputations.pickPermanence.case_nop_h.p_nop < rndnum ? H : NOP;

			}
			break;
			;
		case V | VL:
			if(params.p_permanence_nop == 0.0 &&
					params.p_permanence_y == 0.0 &&
					params.p_permanence_yl == 0.0)
				return NOP;




		;
		case H | V | VR:;
		case H | V | VL | VR:;
		default:;
		}
	}

	float imagePixelValue(int column, int line) {
		if(!imageOpen())
			return 0.0;
		return NARRAY_VAL(imgSourcerer.data,params.x_size,column,line);
	}

	float randomValue() {
		//qsrand(time(NULL));
		return ZUFALL;
	}

	void applyLimitersFactors(double *input, int column, int line) {

	}

	int pixelComponent(QRgb rgba) {
		switch(params.img_reported) {
		case RVAL:
			return qRed(rgba);
			;
		case GVAL:
			return qGreen(rgba);
			;
		case BVAL:
			return qBlue(rgba);
			;
		case MVAL:
			return (int) ceil((double)(((double)(qBlue(rgba) + qGreen(rgba) + qRed(rgba)))/3.0));
			;
		case HVAL:
			return 0;
			;
		case GREY:
			return qGray(rgba);
			;
		default:
			return 0;
			;
		}
		return 0;
	}

	bool imageOpen() {
		// If the image has been already opened.
		// If something went wrong copying the image data.
		if(imgSourcerer.image.isNull() || !imgSourcerer.data)
			return false;

		imgSourcerer.image = QImage(params.img_source);

		imgSourcerer.data = (float*) malloc(params.x_size * params.y_size * sizeof(float));
		if(imgSourcerer.data == NULL)
			return false;

		if(params.img_anchor_x != 0 || params.img_anchor_y != 0)
			imgSourcerer.image = imgSourcerer.image.copy(params.img_anchor_x,
					params.img_anchor_y,
					params.x_size,
					params.y_size);

		for(int line = params.y_size;
				line > -1;
				--line) {
			uchar *linecol_ptr = imgSourcerer.image.scanLine(line);
			if(linecol_ptr == NULL) {
				qCritical() << "imageOpen: linecol_ptr == NULL";
				return false;
			}

			for(int column = 0;
					column < params.x_size;
					++column) {
				if(imgSourcerer.image.format() == QImage::Format_Mono ||
						imgSourcerer.image.format() == QImage::Format_MonoLSB ||
						imgSourcerer.image.format() == QImage::Format_Indexed8) {
					// pixel data width is sizeof(uchar)
					bool *casted_b = NULL;
					qint32 *casted_i = NULL;
					switch(imgSourcerer.image.format()) {
					case QImage::Format_Mono:;
					case QImage::Format_MonoLSB:
						casted_b = reinterpret_cast<bool*>(linecol_ptr);
						if(casted_b == NULL)
							return false;

						if(*casted_b) {
							NARRAY_VAL(imgSourcerer.data,params.x_size,column,params.y_size-line) = params.z_top;
						} else {
							NARRAY_VAL(imgSourcerer.data,params.x_size,column,params.y_size-line) = params.z_bottom;
						}
						break;
						;
					case QImage::Format_Indexed8:
						if(imgSourcerer.bit8_color_table.isEmpty())
							imgSourcerer.bit8_color_table = imgSourcerer.image.colorTable();

						casted_i = reinterpret_cast<qint32*>(linecol_ptr);
						if(casted_i == NULL)
							return false;

						NARRAY_VAL(imgSourcerer.data,params.x_size,column,params.y_size-line) = (float) pixelComponent(imgSourcerer.bit8_color_table.value(*casted_i));
						break;
						;
					default:
						break;
					}
				} else {
					QRgb *casted_r = reinterpret_cast<QRgb*>(linecol_ptr);
					if(casted_r == NULL)
						return false;

					NARRAY_VAL(imgSourcerer.data,params.x_size,column,params.y_size-line) = (float) pixelComponent(*casted_r);
				}
				++linecol_ptr;
			}
		}
		return true;
	}

	struct {
		QImage image;
		float *data;
		QVector<QRgb> bit8_color_table;
	} imgSourcerer;

	struct {

		struct {
			struct {
				const float *p_nop;
				const float *p_h;
					} case_nop_h;
			struct {
				const float *p_nop;
				const float *p_v;
				const float *p_vl;
			} case_nop_v_vl;
			struct {
				const float *p_nop;
				const float *p_h;
				const float *p_v;
				const float *p_vr;
			} case_nop_h_v_vr;
		} pickPermanence; /* for pickPermanence() method */

		void precompute(const struct Parameters *input) {
			/* for pickPermanence() */
			float psum = 0.0;

			psum = MakeXml::sum<float>(2, input->p_permanence_nop, input->p_permanence_x);
			if(psum < 1.0) {
				float factor = MakeXml::reciproke<float>(psum);
				pickPermanence.case_nop_h.p_nop = MakeXml::cvalPtr<float>(factor * input->p_permanence_nop);
				pickPermanence.case_nop_h.p_h = MakeXml::cvalPtr<float>(factor * input->p_permanence_x);
			} else {
				pickPermanence.case_nop_h.p_nop = &input->p_permanence_nop;
				pickPermanence.case_nop_h.p_h = &input->p_permanence_x;
			}

			psum = MakeXml::sum<float>(3,
					input->p_permanence_nop,
					input->p_permanence_y,
					input->p_permanence_yl);
			if(psum < 1.0) {
				float factor = MakeXml::reciproke<float>(psum);
				pickPermanence.case_nop_v_vl.p_nop = MakeXml::cvalPtr<float>(factor * input->p_permanence_nop);
				pickPermanence.case_nop_v_vl.p_v = MakeXml::cvalPtr<float>(factor * input->p_permanence_y);
				pickPermanence.case_nop_v_vl.p_vl = MakeXml::cvalPtr<float>(factor * input->p_permanence_yl);
			} else {
				pickPermanence.case_nop_v_vl.p_nop = &input->p_permanence_nop;
				pickPermanence.case_nop_v_vl.p_v = &input->p_permanence_y;
				pickPermanence.case_nop_v_vl.p_vl = &input->p_permanence_yl;
			}

			psum = MakeXml::sum<float>(4,
					input->p_permanence_nop,
					input->p_permanence_x,
					input->p_permanence_y,
					input->p_permanence_yr);
			if(psum < 1.0) {
				float factor = MakeXml::reciproke<float>(psum);
				pickPermanence.case_nop_h_v_vr.p_nop = MakeXml::cvalPtr<float>(factor * input->p_permanence_nop);
				pickPermanence.case_nop_h_v_vr.p_h = MakeXml::cvalPtr<float>(factor * input->p_permanence_x);
				pickPermanence.case_nop_h_v_vr.p_v = MakeXml::cvalPtr<float>(factor * input->p_permanence_y);
				pickPermanence.case_nop_h_v_vr.p_vr = MakeXml::cvalPtr<float>(factor * input->p_permanence_yr);
			} else {
				pickPermanence.case_nop_h_v_vr.p_nop = &input->p_permanence_nop;
				pickPermanence.case_nop_h_v_vr.p_h = &input->p_permanence_x;
				pickPermanence.case_nop_h_v_vr.p_v = &input->p_permanence_y;
				pickPermanence.case_nop_h_v_vr.p_vr = &input->p_permanence_yr;
			}
		}
	} precomputations;

#ifdef DEBUG
	struct {
		int permanence_results;
		int random_results;
		int image_results;
		void print() {
			qDebug() << "random results" << random_results;
			qDebug() << "permanence results" << permanence_results;
			qDebug() << "image results" << image_results;
		}
	} dbgCounters;
#endif

};

Q_DECLARE_METATYPE(MakeXml::ImgReport)
#endif /* MKXML_H_ */

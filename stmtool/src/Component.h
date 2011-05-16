#ifndef COMPONENT_H
#define COMPONENT_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtGui/QWidget>

class Component : public QObject {
	Q_OBJECT
	public:
		//! Available toplevel components.
		//! Used with Component:signal_resolve() as OR'ed int
		enum Type {
			CORE =			1,
			DEVICE_MANAGER = 	1<<1,
			BASE_WINDOW =		1<<2,
			SETTINGS_MANAGER =	1<<3,
			SDM =			1<<4
		};
		
		//! Used with Component::signal_log() and logging facility of
		//! ComponentDock
		enum LogMessageLevel {
			DEBUG,
			INFO,
			CRITICAL,
			DEADLY
		};
		
		//! Used as OR'ed int with Component:signal_flag()
		enum Flag {
			READY =			1,
			SHUTDOWN =		1<<1,
			DEPS_RESOLVED =		1<<2,
			DEPS_UNRESOLVED =	1<<3
		};

	public slots:
		virtual void slot_init() = 0;
		virtual void slot_shutdown() = 0;
		virtual void slot_resolveDependencies() = 0;
		virtual void slot_receiveDependencies(QList<const Component*>) = 0;
	signals:
		void signal_resolve(int ctypes, const QWidget* prefgui);
		void signal_log(const QString& msg, enum LogMessageLevel msglv);
		void signal_flag(int Flag);
};

Q_DECLARE_INTERFACE(Component,"iComponent")

#endif

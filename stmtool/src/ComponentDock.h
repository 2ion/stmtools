#ifndef COMPONENTDOCK_H
#define COMPONENTDOCK_H

#include "main.h"
#include "Component.h"

class ComponentDock : public QObject {
	Q_OBJECT
	public:
		ComponentDock();
		~ComponentDock();
		int load_components();
		int load_modules();
		int resolve();
		int run();

	public slots:
		void slot_log(const QString& msg, enum Component::LogMessageLevel msglv);
		void slot_resolve(int ored, const QWidget *pref);

	private:

};

#endif

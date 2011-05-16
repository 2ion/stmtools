#ifndef CSETTINGSMANAGER_H
#define CSETTINGSMANAGER_H

#include "Component.h"
#include "main.h"

class CSettingsManager : public Component {
	Q_OBJECT
	public:
		CSettingsManager();
		~CSettingsManager();

		int set_value(const QString &key, const QVariant &val);
		QVariant* value(const QString &key);
		int delete_value(const QString &key);
		QStringList keys();

	public slots:

		/* Component interface */
		void slot_init();
		void slot_shutdown();
		void slot_resolveDependencies();
		void slot_receiveDependencies(QList<const Component*>);

	signals:
		/* Component interface */
		void signal_resolve(int ctypes, const QWidget* prefgui);
		void signal_log(const QString& msg, enum Component::LogMessageLevel msglv);
		void signal_flag(int flag);

	private:
		void set_default_values();
		QSettings *settings;
};



#endif /* CSETTINGSMANAGER_H */

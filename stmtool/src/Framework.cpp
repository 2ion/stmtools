#include "Framework.h"

Framework::Framework()
{
    q_settings = NULL;
    q_app = NULL;
}

Framework::Framework(
    QApplication *q_app,
    QSettings *q_settings)
{
    q_settings = NULL;
    q_app = NULL;
    add_Qt(q_app,q_settings); 
}

int Framework::add_Qt(
    QApplication *q_app,
    QSettings *q_settings)
{
    if(q_app && q_settings)
        return 0;

    if(q_app == NULL || q_settings == NULL)
        return 1;

    this->q_app = q_app;
    this->q_settings = q_settings;

    return 0;
}

int Framework::run()
{
    if(!(q_app && q_settings))
        return -1;

    /* create and sort plugin instances */
    QVariant plugin_path = q_settings->value("plugin_path",
        QVariant(QDir::homePath() + "/.stmtool/plugins"));
    
    Q_FOREACH(const QString file, QDir(plugin_dir).entryList())
        if(QLibrary::isLibrary(file))
        {
            plugin_loader.setFileName(file);
            QObject *instance = plugin_loader.instance();
            if(instance == 0)
                continue;
            
            SourceInterface *si = qobject_cast<SourceInterface*>(instance);
            if(si)
            {
                interfaces_source.append(si);
                continue;
            }

            FilterInterface *fi = qobject_cast<FilterInterface*>(instance);
            if(fi)
            {
                interface_filter.append(fi);
                continue;
            }
        }
        

}

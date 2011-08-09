#ifndef FRAMEWORK_H
#define FRAMEWORK_H

class Framework
{
    public:
    Framework();
    Framework(
        QApplication *q_app,
        QSettings *q_settings);
    ~Framework();

    int add_Qt(
        QApplication *q_app,
        QSettings *q_settings);

    int run();

    private:
    QApplication *q_app;
    QSettings *q_settings;
    QList<SourceInterface*> interfaces_source;
    QList<FilterInterface*> interfaces_filter;
    QPluginLoader plugin_loader;
};


#endif /* FRAMEWORK_H */

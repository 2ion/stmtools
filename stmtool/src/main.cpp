int main(int argc, char **argv)
{
    QApplication q_app(argc, argv);
    q_app.setApplicationName(STMS_APPNAME);
    q_app.setApplicationVersion(STMS_VERSION);
    q_app.setOrganizationName(STMS_ORG);
    q_app.setOrganizationDomain(STMS_ORG_DOMAIN);
    
    QSettings q_settings;

    Framework f(&q_app, &q_settings);
    return f.run();
 }

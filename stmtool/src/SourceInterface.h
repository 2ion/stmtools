#ifndef SOURCE_INTERFACE_H
#define SOURCE_INTERFACE_H

class SourceInterface
{
    public:
    virtual const QWidget* user_interface() = 0;
    virtual QList<const QByteArray*> buffers() = 0;
    virtual QMap<QString,QVariant> settings() = 0;
    virtual qint32 open() = 0;
    virtual qint32 close() = 0;
    virtual qint32 kill() = 0;
};

#endif /* SOURCE_INTERFACE_H */

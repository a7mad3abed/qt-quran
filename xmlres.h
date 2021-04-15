#ifndef XMLRES_H
#define XMLRES_H

#include <QObject>

class XmlRes : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString textFromXml READ textFromXml NOTIFY textFromXmlChanged)
public:
    XmlRes();

    QString textFromXml()const{
        return m_textFromXml;
    }
signals:
    void textFromXmlChanged();
private:
    QString m_textFromXml;
};

#endif // XMLRES_H

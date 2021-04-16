#include "xmlres.h"
#include <QtXml/QDomComment>
#include <QFile>
#include <QIODevice>
#include <QDebug>

XmlRes::XmlRes()
{
    QDomDocument doc;
    QFile file(":/quran-uthmani.xml");
    if(!file.open(QIODevice::ReadOnly)){
       qDebug() << "Failed to open the file" ;
    }
    else{
        if(!doc.setContent(&file)){
            qDebug() << "failed to load xml";
        }

        file.close();
    }
    QDomElement root = doc.firstChildElement();
    QDomNodeList nodes = root.elementsByTagName("Verse");
    qDebug() << nodes.count();

    for (int i = 0; i < nodes.count(); i++)
    {
        QDomNode elm = nodes.at(i);
        if(elm.isElement())
        {
            QDomElement element = elm.toElement();
            m_textFromXml.push_back(element.text());
            m_textFromXml.push_back("\n");

        }
    }

}


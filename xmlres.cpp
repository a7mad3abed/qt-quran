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
    QDomNodeList nodes = root.elementsByTagName("sura");
    qDebug() << nodes.count();

    for (int i = 90; i < 91; i++)
    {
        QDomNode elm = nodes.at(i);
        if(elm.isElement())
        {
            QDomElement element = elm.toElement();
            QDomNodeList nodesAya = element.elementsByTagName("aya");
            for (int j = 0; j < nodesAya.count(); j++)
            {
                QDomNode elmAya = nodesAya.at(j);
                if (elmAya.isElement())
                {
                    QDomElement elmentAya = elmAya.toElement();
                    m_textFromXml.push_back(elmentAya.attribute("text"));
                    m_textFromXml.push_back("     ");
                }
            }

        }
    }

}


#include "xmlres.h"
#include <QtXml/QDomComment>
#include <QFile>
#include <QIODevice>
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>

XmlRes::XmlRes()
{
//    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
//    db.setHostName("localhost");
//    db.setDatabaseName("quran");
//    db.setUserName("ibrahiah");
//    db.setPassword("Mo14:Kh03");
//    bool ok = false;
//    if(!(ok = db.open())){
//        qDebug() << "cannot open db";
//        return;
//    }

//    QSqlQuery query;
//    query.exec("select * from quran_text where sura=12;");

//    while(query.next()){
//        QString text = query.value(3).toString();
//        m_textFromXml.push_back(text);
//        m_textFromXml.push_back("\n") ;
//    }



//    QDomDocument doc01;
//    QFile file01(":/quran-uthmani.xml");
//    if(!file01.open(QIODevice::ReadOnly)){
//       qDebug() << "Failed to open the file" ;
//    }
//    else {
//       if(!doc01.setContent(&file01)) {
//            qDebug() << "failed to load xml";
//       }
//       file01.close();
//    }
//    QDomElement root = doc01.firstChildElement();
//    QDomNodeList nodes = root.elementsByTagName("aya");
//    qDebug() << nodes.count();

//    for (int i = 0; i < nodes.count(); i++){
//        QDomNode elem = nodes.at(i);
//        if(elem.isElement())
//        {
//            QDomElement element = elem.toElement();
//            m_textFromXml.push_back(element.text());
//            m_textFromXml.push_back(" \uFCFE ");
//        }
//    }





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

    for (int i = 12; i < 13; i++)
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
                    buffer.push_back(elmentAya.attribute("text").toStdString().c_str());
                    buffer.push_back("\u06DD");
                    //m_textFromXml.push_back(elmentAya.attribute("text"));


                }
            }


        }
    }
//    buffer.push_back("\xd8\xa7\xd9\x92\x20");
//    m_textFromXml.push_back(buffer.toStdString().c_str());
//    //buffer.remove(0,2);
//    m_textFromXml.
    int i = 0;
    for(i = 0 ; i < buffer.size(); i++)
    {
        unsigned char c = buffer.at(i);
        unsigned char d = buffer.at(i+1);


        if(c == 0xD9| c == 0xD8)
        {
            if(c == 0xD9 && d == 0x9F)
            {
                qDebug() << "found";
                unsigned char c1 = 0xDB;
                unsigned char d1 = 0xA1;
                correct_buffer.push_back(c1) ;
                correct_buffer.push_back(d1) ;
                buffer[i] = 0xd9;
                buffer[i+1] = 0x92;
                i++;
            }
            else if(c == 0xd9 && d == 0x92){
                buffer[i] = 0xdb;
                buffer[i+1] = 0xa1;

            }
            else{
            correct_buffer.append(buffer.at(i));
            correct_buffer.append(buffer.at(++i));
            }
        }

        if(c == 0x20)
        {
            correct_buffer.append(buffer.at(i));
        }

        if(c == 0xDB)
        {
            // the problem was that the silent sign was false endcoded
            // the false code was DB 9F and the right is DB A0
            // that is of course based on the encoding of the hafs font of king fahad complex
            if(d==0x9f)
            {
                buffer[++i] = 0xa0;
            }

            // Ishmam correction
            if(d==0xab)
            {
                buffer[++i] = 0xac;
            }
            correct_buffer.append(buffer.at(i)) ;
            correct_buffer.append(buffer.at(++i));
        }

    }
    qDebug() << buffer;

    //m_textFromXml = QString().fromUtf8(correct_buffer, correct_buffer.size());
    m_textFromXml.push_back(buffer.toStdString().c_str()) ;
            //(correct_buffer.toStdString().c_str()) ;
}


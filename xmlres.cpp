#include "xmlres.h"
#include "tinyxml.h"

XmlRes::XmlRes()
{
    TiXmlDocument doc;
    doc.LoadFile("Chapter001.xml");
    m_textFromXml = doc.FirstChildElement()->FirstChildElement()->GetText();
    m_textFromXml.push_back("\n");
    m_textFromXml.push_back(doc.FirstChildElement()->FirstChildElement()->NextSiblingElement()->GetText());

}


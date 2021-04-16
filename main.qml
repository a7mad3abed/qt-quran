import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    width: 800
    height: 600
    visible: true
    title: qsTr("Hello World")
    Rectangle{
        id: centeredContent
        width: parent.width/2
        height: parent.height/2
        anchors.centerIn: parent
        FontLoader{
            id: uthmanic
            source: "/fonts/UthmanicHafs1.ttf"
            onStatusChanged: {
                uthmanic.status === "loaded" ? xmltext.text = xmlRes.textFromXml: ""
            }
        }

        Text {
            id: xmltext
            text: xmlRes.textFromXml
            font.family: uthmanic.name
            font.pointSize: 29
            anchors.centerIn:  parent

        }
    }
}

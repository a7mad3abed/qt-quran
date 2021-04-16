import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15

Window {
    width: 800
    height: 600
    visible: true
    title: qsTr("Hello World")

    Rectangle{
        id: centeredContent
        anchors.fill: parent
        FontLoader{
            id: uthmanic
            source: "/fonts/UthmanicHafs1.ttf"
            onStatusChanged: {
                uthmanic.status === "loaded" ? xmltext.text = xmlRes.textFromXml: ""
            }
        }

        Flickable{
            id: flickArea
            anchors.fill: parent
            contentWidth: xmltext.width
            contentHeight: xmltext.height
            flickableDirection: Flickable.HorizontalFlick
            clip: true


            Text{
                id: xmltext

                textFormat: Text.StyledText
                //readOnly: true
                wrapMode: Text.WrapAnywhere
                elide: Text.ElideRight
                text: xmlRes.textFromXml
                font.family: uthmanic.name
                font.pointSize: 29
            }
        }
    }
}

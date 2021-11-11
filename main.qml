import QtQuick 2.12
import QtQuick.Window 2.12

import MyApi.Test 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Text {
        anchors.top: parent.top
        text: myobject.myproperty
    }

    MyObject {
        id: myobject
        myproperty: 40
        onTimerSignal: myproperty = Math.random() * 1000
    }

    Text {
        anchors.bottom: parent.bottom
        text: MySingleton.myproperty
    }

    Connections {
        target: MySingleton
        function onTimerSignal() {
            MySingleton.myproperty = Math.random() * 1000
        }
    }

    Component.onCompleted: {
        myobject.myFunction()
        MySingleton.myFunction()
    }
}

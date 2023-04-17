import Qml.ImGui

Window {
    id: root
    title: "Widgets Gallery"

    Text {
        text: "This is some useful text."
    }

    Button {
        text: "Click Me"
        onClicked: {
            console.log("[WidgetsGallery.qml::15::onClicked]")
        }
    }

    Button {
        text: "Close Window"
        onClicked: {
            root.visible = false
        }
    }
}

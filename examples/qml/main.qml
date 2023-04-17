import Qml.ImGui
import QtQml 2.15

ApplicationWindow {
    id: root
    title: "QML ImGui Gallery"

    // MenuBar {
    //     Menu {
    //         title: "Demos"

    //         MenuItem {
    //             text: "Calculator"
    //             onTriggered: {
    //                 calculator.open()
    //             }
    //         }

    //         MenuItem {
    //             text: "Widgets Gallery"
    //             onTriggered: {
    //                 widgets.open()
    //             }
    //         }

    //         MenuItem {
    //             text: "Dialogs Gallery"
    //             onTriggered: {
    //                 dialogs.open()
    //             }
    //         }

    //         MenuItem {
    //             text: "Layouts Gallery"
    //             onTriggered: {
    //                 layouts.open()
    //             }
    //         }
    //     }

    //     Menu {
    //         title: "Help"
    //     }
    // }

    Window {
        title: "Demo Windows"

        Button {
            text: "Widgets Gallery"

            property WidgetsGallery window

            onClicked: {
                open()
            }

            function open() {
                if (!window) {
                    window = cmpWidgetsGallery.createObject(root)
                }

                window.visible = true
            }
        }
    }

    Component {
        id: cmpWidgetsGallery

        WidgetsGallery { }
    }
}

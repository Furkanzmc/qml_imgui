import Qml.ImGui
import QtQml 2.15

ApplicationWindow {
    id: root
    title: "QML ImGui Gallery"

    Window {
        title: "Demo Windows"
        flags: Window.MenuBar

        MenuBar {
            Menu {
                title: "Windows"

                Menu {
                    title: "Demo Windows"

                    MenuItem {
                        text: "Calculator"
                        onClicked: {
                        }
                    }

                    MenuItem {
                        text: "Widgets Gallery"
                        onClicked: {
                            widgets.open()
                        }
                    }

                    MenuItem {
                        text: "Dialogs Gallery"
                        onClicked: {
                        }
                    }

                    MenuItem {
                        text: "Layouts Gallery"
                        onClicked: {
                        }
                    }
                }

                MenuItem {
                    text: "Close All"
                    onClicked: {
                        widgets.window.destroy()
                        widgets.window = null
                    }
                }
            }

            Menu {
                title: "Help"
            }
        }

        Button {
            id: widgets
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

cmake_minimum_required(VERSION 3.16)
project(
  qml_imgui
  VERSION 0.1
  LANGUAGES CXX)

include(FetchContent)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_EXAMPLES "Build examples." OFF)

if(NOT DEFINED PLUGIN_INSTALL_DIR)
  set(PLUGIN_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/qml_imgui")
endif()

find_package(
  QT NAMES Qt6 Qt5
  COMPONENTS Core Quick
  REQUIRED)

find_package(
  Qt${QT_VERSION_MAJOR}
  COMPONENTS Core Quick
  REQUIRED)

find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
  message(STATUS "[qml_imgui] OpenGL found")
else()
  message(STATUS "[qml_imgui] OpenGL not found")
endif()

set(PLUGIN_DIR "${PLUGIN_INSTALL_DIR}/qml/Qml/ImGui")
set(IMGUI_DIR "libs/imgui")
message("[qml_imgui] Installing plugin to '${PLUGIN_INSTALL_DIR}'")

FetchContent_Declare(
  glfw
  GIT_REPOSITORY "https://github.com/glfw/glfw"
  GIT_TAG "3.3.8"
  GIT_SHALLOW ON)

# Now make the glfw target available to link against
FetchContent_MakeAvailable(glfw)

set(imgui_src
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp)

set(source_files
    src/plugin.cpp
    src/ZWidget.cpp
    src/ZWindow.cpp
    src/ZApplicationWindow.cpp
    src/ZText.cpp
    src/ZButton.cpp
    src/ZMenuBar.cpp
    src/ZMenu.cpp
    src/ZMenuItem.cpp)

qt_add_qml_module(
  qml_imgui
  OUTPUT_DIRECTORY
  qml/Qml/ImGui
  VERSION
  1.0
  URI
  "Qml.ImGui"
  SOURCES
  ${source_files}
  ${imgui_src}
  NO_GENERATE_PLUGIN_SOURCE
  CLASS_NAME
  QmlImGuiPlugin
  PLUGIN_TARGET
  qml_imgui)

target_compile_definitions(
  qml_imgui
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

include_directories(./src)
include_directories(./libs/imgui)
include_directories(./libs/imgui/backends/)
include_directories(${OPENGL_INCLUDE_DIRS})

target_link_libraries(qml_imgui PRIVATE Qt${QT_VERSION_MAJOR}::Core
                                        ${OPENGL_LIBRARIES} glfw)

install(
  TARGETS qml_imgui
  RUNTIME DESTINATION "${PLUGIN_DIR}"
  BUNDLE DESTINATION "${PLUGIN_DIR}"
  LIBRARY DESTINATION "${PLUGIN_DIR}")

if(BUILD_EXAMPLES)
  message("[qml_imgui] Building examples.")
  add_subdirectory(examples/)
endif()

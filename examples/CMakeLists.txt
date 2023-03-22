cmake_minimum_required(VERSION 3.14)

project(
  qml_imgui_examples
  VERSION 0.1
  LANGUAGES CXX)

include(FetchContent)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(
  QT NAMES Qt6 Qt5
  COMPONENTS Core Quick
  REQUIRED)

find_package(
  Qt${QT_VERSION_MAJOR}
  COMPONENTS Core Quick
  REQUIRED)

find_package(OpenGL REQUIRED)

set(PROJECT_SOURCES src/main.cpp qml.qrc)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  qt_add_executable(qml_imgui_examples MANUAL_FINALIZATION ${PROJECT_SOURCES})
else()
  if(ANDROID)
    add_library(qml_imgui_examples SHARED ${PROJECT_SOURCES})
  else()
    add_executable(qml_imgui_examples ${PROJECT_SOURCES})
  endif()
endif()

target_compile_definitions(
  qml_imgui_examples
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
include_directories(./src)
include_directories(../libs/imgui)
include_directories(${OPENGL_INCLUDE_DIRS})

target_link_libraries(
  qml_imgui_examples PRIVATE Qt${QT_VERSION_MAJOR}::Core
                             Qt${QT_VERSION_MAJOR}::Quick glfw)

set_target_properties(
  qml_imgui_examples
  PROPERTIES MACOSX_BUNDLE_GUI_IDENTIFIER zmc.space
             MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
             MACOSX_BUNDLE_SHORT_VERSION_STRING
             ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})

if(QT_VERSION_MAJOR EQUAL 6)
  qt_import_qml_plugins(qml_imgui_examples)
  qt_finalize_executable(qml_imgui_examples)
endif()

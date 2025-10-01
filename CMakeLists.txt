cmake_minimum_required(VERSION 3.16)

project(payroll-system VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools  Sql)
find_package(SQLite3 REQUIRED)

set(TS_FILES payroll-system_fa_IR.ts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        DatabaseHandler.cpp
        userdata.cpp
        allemployees.cpp
        allemployees.ui
        addemployeewindow.cpp


)
set(PROJECT_FORMS
        mainwindow.ui
        # Add other .ui files for other dialogs here later
)
set(PROJECT_HEADERS  # ← Add headers separately if needed for MOC
  DatabaseHandler.h
  mainwindow.h
  addemployeewindow.h
  allemployees.h
  userdata.h
)
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(payroll-system
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${PROJECT_FORMS}
        ${PROJECT_HEADERS}

        allemployees.h allemployees.cpp
        data/1-createtable.sql data/payroll.db
        styles/styles.qss

        allemployees.ui
        employeeinfobox.h employeeinfobox.cpp
        addemployeewindow.h addemployeewindow.cpp addemployeewindow.ui
        animatedrectwidget.h animatedrectwidget.cpp


    )

  add_custom_command(TARGET payroll-system POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory
      ${CMAKE_CURRENT_SOURCE_DIR}/data
      $<TARGET_FILE_DIR:payroll-system>/data
      COMMENT "Copying data directory to build folder"
  )

add_custom_command(TARGET payroll-system POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/styles
    $<TARGET_FILE_DIR:payroll-system>/styles
    COMMENT "Copying styles directory to build folder"
)

target_sources(payroll-system PRIVATE
    DatabaseHandler.h
    mainwindow.h
    addemployeewindow.h
    allemployees.h
    userdata.h
)
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/data
  ${CMAKE_CURRENT_SOURCE_DIR}/styles
)
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET payroll-system APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(payroll-system SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(payroll-system
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(payroll-system PRIVATE
  Qt${QT_VERSION_MAJOR}::Widgets
  Qt${QT_VERSION_MAJOR}::Sql
  SQLite::SQLite3
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.payroll-system)
endif()
set_target_properties(payroll-system PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS payroll-system
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(payroll-system)
endif()

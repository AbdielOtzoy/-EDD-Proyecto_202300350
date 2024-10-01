cmake_minimum_required(VERSION 3.16)

project(SocialStructure VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SocialStructure
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        register.h register.cpp register.ui
        userview.h userview.cpp userview.ui
        adminview.h adminview.cpp adminview.ui
        user.h user.cpp
        structures/avl.h structures/avl.cpp
        appstage.h appstage.cpp
        models/post.h models/post.cpp
        structures/doublylist.h structures/doublylist.cpp
        postform.h postform.cpp postform.ui
        structures/bst.h structures/bst.cpp
        models/request.h models/request.cpp
        structures/list.h structures/list.cpp
        structures/stack.h structures/stack.cpp
        structures/stack.h structures/stack.cpp
        structures/friendlist.h structures/friendlist.cpp
        commentform.h commentform.cpp commentform.ui
        models/comment.h models/comment.cpp
        structures/btree.h structures/btree.cpp
        structures/matrix/matrix/matrixnode.h structures/matrix/matrix/matrixnode.cpp
        structures/matrix/simpleList/listnode.h structures/matrix/simpleList/listnode.cpp
        structures/matrix/simpleList/simplelist.h structures/matrix/simpleList/simplelist.cpp
        structures/matrix/matrix/matrix.h structures/matrix/matrix/matrix.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SocialStructure APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(SocialStructure SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SocialStructure
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(SocialStructure PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.SocialStructure)
endif()
set_target_properties(SocialStructure PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS SocialStructure
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SocialStructure)
endif()

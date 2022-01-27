cmake_minimum_required(VERSION 3.16)

project(SceneGraphGL2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)
find_package(Qt6 COMPONENTS ShaderTools)

qt_add_executable(appSceneGraphGL2
    main.cpp
    ./Shaders/fragmentShader.frag
    ./Shaders/vertexShader.vert
)

qt_add_qml_module(appSceneGraphGL2
    URI SceneGraphGL2
    VERSION 1.0
    QML_FILES main.qml 
)

qt6_add_shaders(appSceneGraphGL2 "appSceneGraphGL2_shaders"
    PREFIX
        "/"
    FILES
    ./Shaders/fragmentShader.frag
    ./Shaders/vertexShader.vert
)

set_target_properties(appSceneGraphGL2 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(appSceneGraphGL2
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appSceneGraphGL2
    PRIVATE Qt6::Quick)

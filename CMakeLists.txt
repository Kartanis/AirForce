cmake_minimum_required(VERSION 3.2)
project(AirForce)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")

include_directories("headers/FileSystem/")
include_directories("headers/")
include_directories("headers/math")
include_directories("headers/models")
include_directories("headers/tga")
include_directories("include")

set(SOURCE_FILES
    headers/tga/tgawrite.c
    headers/tga/tgaread.c
    headers/tga/tga.c


    src/FileSystem/FileReader.cpp
    src/FileSystem/ObjModelReader.cpp
    src/GUI/features/BlinkedMark.cpp
    src/GUI/features/BlinkedMark.h
    src/GUI/features/Mark.cpp
    src/GUI/features/Mark.h
    src/json/jsoncpp.cpp
    src/math/CVector3.cpp
    src/math/Math.cpp
    src/model/Cube.cpp
    src/model/House.cpp
    src/model/Model.cpp
    src/model/Terrain.cpp

    src/ui/camera/Camera.cpp
    src/ui/camera/Camera.h
    src/ui/events/MouseEvent.cpp
    src/ui/events/MouseEvent.h
    src/ui/listeners/OnMouseActionListener.cpp
    src/ui/listeners/OnMouseActionListener.h
    src/ui/listeners/OnScreenSizeChangedListener.h
    src/ui/scene/Scene.cpp
    src/ui/scene/Scene.h
    src/ui/screens/ModelViewScreen.cpp
    src/ui/screens/ModelViewScreen.h
    src/ui/screens/Screen.cpp
    src/ui/screens/Screen.h
    src/ui/temp/Core.cpp
    src/ui/temp/Core.h
    src/ui/temp/Drawable.cpp
    src/ui/temp/Drawable.h
    src/ui/temp/Frame.cpp
    src/ui/temp/Frame.h
    src/ui/temp/View.cpp
    src/ui/temp/View.h
    src/ui/window/Window.cpp
    src/ui/window/Window.h
    src/GLSLUtils.cpp
    src/main.cpp
    )

#file(GLOB HEADER_FILES "headers/*.h")
#file(GLOB SOURCE_FILES "src/*.cpp" "src/*.h")

add_executable(AirForce ${SOURCE_FILES} include/definitions.h)
target_link_libraries (AirForce GL)
target_link_libraries (AirForce GLEW)
target_link_libraries (AirForce glut)
target_link_libraries (AirForce GLU)


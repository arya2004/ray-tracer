cmake_minimum_required(VERSION 3.26)
project(Tray_Racing_Computer_Graphics)

set(CMAKE_CXX_STANDARD 17)

add_executable(Tray_Racing_Computer_Graphics main.cpp
        CApp.h
        CApp.cpp
        RayTrace/Image.cpp
        RayTrace/Image.hpp
        RayTrace/Scene.cpp
        RayTrace/Scene.hpp
        RayTrace/Ray.cpp
        RayTrace/Ray.hpp
        RayTrace/Camera.cpp
        RayTrace/Camera.hpp
        RayTrace/ObjectBase.cpp
        RayTrace/ObjectBase.hpp
        RayTrace/ObjSphere.cpp
        RayTrace/ObjSphere.hpp
)

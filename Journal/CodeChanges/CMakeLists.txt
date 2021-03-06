project(GEL)
cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 20)

find_package(Threads)

option(Use_GLGraphics "Compile the OpenGL Viewer" ON)
if (Use_GLGraphics)
    find_package(OpenGL REQUIRED)

    set(GLFW_DIR ./GLFW)
    include_directories("C:/GLFW/include")
    link_directories("C:/GLFW/lib-mingw")

    if(NOT WIN32)
    find_package(glfw3 REQUIRED)
endif()
    if (APPLE)
        FIND_LIBRARY(COCOA_LIBRARY Cocoa)
        add_compile_definitions(GL_SILENCE_DEPRECATION)
        include_directories(./src/)
        SET(CMAKE_INSTALL_RPATH "@loader_path/")
        SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
    endif (APPLE)
endif (Use_GLGraphics)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if (LINUX)
  set(CMAKE_CXX_FLAGS, "-std=c++1z")
endif ()

if (WIN32)
    include_directories(./src/GEL)
    add_definitions(-DGLEW_STATIC)
endif ()

aux_source_directory(./src/GEL/CGLA CGLA_SRC_LIST)
aux_source_directory(./src/GEL/Geometry GEO_SRC_LIST)
aux_source_directory(./src/GEL/HMesh MSH_SRC_LIST)
aux_source_directory(./src/GEL/Util UTL_SRC_LIST)

if (Use_GLGraphics)
    include_directories(./src/GEL/GL/include)
    aux_source_directory(./src/GEL/GL GL_SRC_LIST)
    aux_source_directory(./src/GEL/GLGraphics GLG_SRC_LIST)
    add_library(GEL STATIC ${CGLA_SRC_LIST} ${GEO_SRC_LIST} ${MSH_SRC_LIST} ${UTL_SRC_LIST} ${GL_SRC_LIST} ${GLG_SRC_LIST})
if(LINUX)
    target_link_libraries(GEL Threads::Threads OpenGL ${COCOA_LIBRARY})
else()
    target_link_libraries(GEL Threads::Threads OpenGL::GLU OpenGL::GL ${COCOA_LIBRARY})
endif()
    # not right now ...
    # add_subdirectory(./src/demo)
else (Use_GLGraphics)
    add_library(GEL STATIC ${CGLA_SRC_LIST} ${GEO_SRC_LIST} ${MSH_SRC_LIST} ${UTL_SRC_LIST})
    target_link_libraries(GEL Threads::Threads)
endif (Use_GLGraphics)


include_directories(./src)
aux_source_directory(./src/PyGEL PYG_SRC_LIST)

if (Use_GLGraphics)
    add_library(PyGEL SHARED ${PYG_SRC_LIST})
    if (WIN32)
        target_link_libraries(PyGEL GEL glfw3.lib)
        
    else (WIN32)
        target_link_libraries(PyGEL GEL glfw)
        
    endif (WIN32)
else (Use_GLGraphics)
    list(REMOVE_ITEM PYG_SRC_LIST "./src/PyGEL/Viewer.cpp")
    add_library(PyGEL SHARED ${PYG_SRC_LIST})
    target_link_libraries(PyGEL GEL)
endif (Use_GLGraphics)

install(TARGETS PyGEL GEL
        LIBRARY DESTINATION PyGEL
        ARCHIVE DESTINATION PyGEL
        )


file(GLOB Dir1_Sources RELATIVE "./src/GEL/Geometry/" "*.h")
file(GLOB Dir2_Sources RELATIVE "./src/GEL/Geometry/" "*.cpp")
add_executable(Main src/main.cpp ${Dir1_Sources} ${Dir2_Sources})
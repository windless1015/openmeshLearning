CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
project(SetFacesColor)
set(SetFacesColor ${PROJECT_NAME})

SET(OpenMesh_DIR D:/Librarys/OpenMesh8.1/share/OpenMesh/cmake)


SET(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} OpenMesh_DIR)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)


#add USE_MATH_DEFINES macro definition
ADD_DEFINITIONS(-D_USE_MATH_DEFINES)

FIND_PACKAGE(OpenMesh REQUIRED)

#group source files, header files, resource files and ui files
SET(SRCs
	SetFacesColor.cpp
)

SET(HDRs
)


#integrate all the files to generate the executable program
ADD_EXECUTABLE( ${CMAKE_PROJECT_NAME}
  ${SRCs}
  ${HDRs}
)

INCLUDE_DIRECTORIES(
	${OpenMesh_INCLUDE_DIRS}
	${CMAKE_CURRENT_SOURCE_DIR}
)

TARGET_LINK_DIRECTORIES(${CMAKE_PROJECT_NAME} PUBLIC
	D:/Librarys/OpenMesh8.1/lib
)

#libraries needed for linkage when compile
target_link_libraries( ${CMAKE_PROJECT_NAME}
  debug OpenMeshCored OpenMeshToolsd
  optimized OpenMeshCore OpenMeshTools
)

message(STATUS {"${OpenMesh_INCLUDE_DIRS}"})
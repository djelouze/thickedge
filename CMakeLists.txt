cmake_minimum_required(VERSION 3.0)
cmake_policy(VERSION 3.0)

project( thickedge )

find_package( VTK 
  COMPONENTS
    vtkIOGeometry
    vtkFiltersExtraction
  )
include( ${VTK_USE_FILE} )

add_executable(thickedge main.cxx)
target_link_libraries(thickedge vtkIOGeometry vtkFiltersExtraction)
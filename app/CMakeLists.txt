find_package( OpenCV REQUIRED )
add_executable(laneDetector laneDetector.cpp main.cpp)
target_link_libraries( laneDetector ${OpenCV_LIBS} )
include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

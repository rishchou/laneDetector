find_package( OpenCV REQUIRED )
add_executable(laneDetector demo.cpp imageProcessor.cpp lanes.cpp)
target_link_libraries( laneDetector ${OpenCV_LIBS} )
include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

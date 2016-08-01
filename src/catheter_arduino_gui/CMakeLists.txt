cmake_minimum_required(VERSION 2.8)


project(catheter_arduino_gui)

find_package(Boost REQUIRED)
find_package(wxWidgets COMPONENTS core base REQUIRED )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
${BOOST_INDCLUDE_DIRS}
${WXWIDGETS_INCLUDE_DIRS}
inc
)

include( "${wxWidgets_USE_FILE}" )

# common folder libs
add_library(common_utils_lib src/com/common_utils.cpp)
add_library(pc_utils_lib src/com/pc_utils.cpp)

# gui folder libs

add_library(catheter_grid_lib src/gui/catheter_grid.cpp)
add_library(status_frame_lib src/gui/status_frame.cpp)
add_library(status_text_lib src/gui/status_text.cpp)

# ser folder libs

add_library(serial_sender_lib src/ser/serial_sender.cpp)
add_library(serial_thread_lib src/ser/serial_thread.cpp)
add_library(simple_serial_lib src/ser/simple_serial.cpp)




#final executable.

add_executable(catheter_gui src/gui/catheter_gui.cpp)


target_link_libraries(
catheter_gui
common_utils_lib
pc_utils_lib
catheter_grid_lib
status_frame_lib
status_text_lib
serial_sender_lib
serial_thread_lib
simple_serial_lib
${BOOST_LIBRARIES}
${wxWIDGETS_LIBRARIES}
)
cmake_minimum_required(VERSION 3.4.1)
set(OpenCV_DIR "src/sdk/native/jni")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

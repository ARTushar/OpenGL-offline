cmake_minimum_required(VERSION 3.14)
project(1605070)

set(OpenGlLinkers -lglut -lGLU -lGL)

add_executable(1605070 1605070_1.cpp Gun.cpp Gun.h DrawShape.cpp DrawShape.h Point.cpp Point.h constants.h 1605070_2.cpp Bubbles.cpp Bubbles.h Timer.h)
target_link_libraries(1605070 ${OpenGlLinkers})
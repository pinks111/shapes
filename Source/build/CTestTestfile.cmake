# CMake generated Testfile for 
# Source directory: C:/Users/Арина/OneDrive/Desktop/2sem/classwork/CW/shapes/Source
# Build directory: C:/Users/Арина/OneDrive/Desktop/2sem/classwork/CW/shapes/Source/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test([=[shapes_tests]=] "C:/Users/Арина/OneDrive/Desktop/2sem/classwork/CW/shapes/Source/build/Debug/shapes_tests.exe")
  set_tests_properties([=[shapes_tests]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Арина/OneDrive/Desktop/2sem/classwork/CW/shapes/Source/CMakeLists.txt;25;add_test;C:/Users/Арина/OneDrive/Desktop/2sem/classwork/CW/shapes/Source/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test([=[shapes_tests]=] "C:/Users/Арина/OneDrive/Desktop/2sem/classwork/CW/shapes/Source/build/Release/shapes_tests.exe")
  set_tests_properties([=[shapes_tests]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Арина/OneDrive/Desktop/2sem/classwork/CW/shapes/Source/CMakeLists.txt;25;add_test;C:/Users/Арина/OneDrive/Desktop/2sem/classwork/CW/shapes/Source/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test([=[shapes_tests]=] "C:/Users/Арина/OneDrive/Desktop/2sem/classwork/CW/shapes/Source/build/MinSizeRel/shapes_tests.exe")
  set_tests_properties([=[shapes_tests]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Арина/OneDrive/Desktop/2sem/classwork/CW/shapes/Source/CMakeLists.txt;25;add_test;C:/Users/Арина/OneDrive/Desktop/2sem/classwork/CW/shapes/Source/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test([=[shapes_tests]=] "C:/Users/Арина/OneDrive/Desktop/2sem/classwork/CW/shapes/Source/build/RelWithDebInfo/shapes_tests.exe")
  set_tests_properties([=[shapes_tests]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Арина/OneDrive/Desktop/2sem/classwork/CW/shapes/Source/CMakeLists.txt;25;add_test;C:/Users/Арина/OneDrive/Desktop/2sem/classwork/CW/shapes/Source/CMakeLists.txt;0;")
else()
  add_test([=[shapes_tests]=] NOT_AVAILABLE)
endif()
subdirs("_deps/googletest-build")

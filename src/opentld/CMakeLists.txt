
link_directories(${OpenCV_LIB_DIR})

include_directories(main
    ../libopentld/imacq
    ../libopentld/tld
    ${OpenCV_INCLUDE_DIRS})


#-------------------------------------------------------------------------------
# main
add_library(main
    main/Gui.cpp
    main/Main.cpp
    main/Gui.h
    main/Main.h)

target_link_libraries(main libopentld cvblobs ${OpenCV_LIBS})

#-------------------------------------------------------------------------------
# opentld
add_executable(opentld
    OpenTLD.cpp)

target_link_libraries(opentld main libopentld cvblobs ${OpenCV_LIBS})

install(TARGETS opentld DESTINATION bin)

#-------------------------------------------------------------------------------

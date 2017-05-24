set(SRCS
    main.cpp
)

set(HEADERS
    arm.h
    body.h
    falda.h
    feet.h

    forearm.h
    hand.h
    head.h
    leg.h
    leg2.h
    neck.h
    particula.h
    resorte.h
    vector.h
)


include(CreateDirectoryGroups)
create_directory_groups(${SRCS} ${HEADERS})

add_executable(telaSim ${SRCS} ${HEADERS})
set_target_properties(telaSim PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
target_link_libraries(telaSim ${OPENGL_gl_LIBRARY} glut32)
target_compile_options(telaSim PRIVATE ${TELA_SIM_CXX_FLAGS})

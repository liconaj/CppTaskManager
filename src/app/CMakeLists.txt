add_executable(taskmaster main.cpp taskmaster.h taskmaster.cpp)

target_link_libraries(taskmaster
    PRIVATE
        TaskMaster::Core
)

include(GNUInstallDirs)
install(TARGETS taskmaster
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

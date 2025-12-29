add_executable(taskmanager "main.cpp")

include(GNUInstallDirs)
install(TARGETS taskmanager
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

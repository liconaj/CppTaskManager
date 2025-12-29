add_executable(taskmaster "main.cpp")

include(GNUInstallDirs)
install(TARGETS taskmaster
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

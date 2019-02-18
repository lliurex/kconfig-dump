
find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#set(CMAKE_AUTOMOC ON)
find_package(KF5Config REQUIRED)
add_executable(kconfig-dump main.cpp)
target_link_libraries(kconfig-dump KF5::ConfigCore)

install(TARGETS kconfig-dump RUNTIME DESTINATION bin)
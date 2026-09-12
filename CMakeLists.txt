cmake_minimum_required(VERSION 3.22)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CMAKE_PROJECT_NAME stm32f411ceux_drivers)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

enable_language(C ASM)

file(GLOB USER_DRIVER_SOURCES CONFIGURE_DEPENDS
    Drivers/Src/*.c
)

add_executable(${CMAKE_PROJECT_NAME}
    Core/Src/main.c
    Core/Src/system_stm32f4xx.c
    Core/Src/syscalls.c
    Core/Src/sysmem.c
    startup_stm32f411xe.s
    ${USER_DRIVER_SOURCES}
    Drivers/Inc/stm32f411xx.h
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    Core/Inc
    Drivers/Inc
    Drivers/CMSIS/Device/ST/STM32F4xx/Include
    Drivers/CMSIS/Include
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    STM32F411xE
    HSE_VALUE=25000000
    HSE_STARTUP_TIMEOUT=100
    HSI_VALUE=16000000
    LSE_STARTUP_TIMEOUT=5000
    LSE_VALUE=32768
    LSI_VALUE=32000
    VDD_VALUE=3300
    $<$<CONFIG:Debug>:DEBUG>
)

target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${TOOLCHAIN_LINK_LIBRARIES})

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    ADDITIONAL_CLEAN_FILES ${CMAKE_PROJECT_NAME}.map
)

list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

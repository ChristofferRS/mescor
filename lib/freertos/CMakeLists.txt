set(libs_FreeRTOS_INCLUDE_DIRECTORIES_PUBLIC
    .
    ${PROJECT_SOURCE_DIR}/third_party/modified/FreeRTOS
    ${PROJECT_SOURCE_DIR}/third_party/modified/nxp/rt1176-sdk/rtos/freertos/freertos_kernel/include
    ${PROJECT_SOURCE_DIR}/third_party/freertos_kernel/include
    ${PROJECT_SOURCE_DIR}/third_party/freertos_kernel/portable/GCC/ARM_CM4F
)

add_library_m7(libs_FreeRTOS OBJECT
    ${libs_FreeRTOS_SOURCES}
)

target_include_directories(libs_FreeRTOS PUBLIC
    ${libs_FreeRTOS_INCLUDE_DIRECTORIES_PUBLIC}
    PRIVATE
    ${libs_FreeRTOS_INCLUDE_DIRECTORIES_PRIVATE}
)

add_library_m4(libs_FreeRTOS-m4 OBJECT
    ${libs_FreeRTOS_SOURCES}
)

target_include_directories(libs_FreeRTOS-m4 PUBLIC
    ${libs_FreeRTOS_INCLUDE_DIRECTORIES_PUBLIC}
    PRIVATE
    ${libs_FreeRTOS_INCLUDE_DIRECTORIES_PRIVATE}
)

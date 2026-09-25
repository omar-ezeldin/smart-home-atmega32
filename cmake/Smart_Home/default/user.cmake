# Project root
get_filename_component(
    PROJECT_ROOT
    "${CMAKE_CURRENT_LIST_DIR}/../../.."
    ABSOLUTE
)

# Allow includes relative to the project root
include_directories(
    "${PROJECT_ROOT}"
)

set_source_files_properties(
    "${PROJECT_ROOT}/HAL/LCD/LCD.c"
    PROPERTIES COMPILE_DEFINITIONS F_CPU=8000000UL
)
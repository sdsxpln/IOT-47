include_directories(../base)
include_directories(../gui)
include_directories(../song)
include_directories(../main)

aux_source_directory(. src)
add_library(gui STATIC ${src})

include_directories(../main)
include_directories(../base)
include_directories(../song)
include_directories(../gui)

aux_source_directory(. src)
add_library(song STATIC ${src})

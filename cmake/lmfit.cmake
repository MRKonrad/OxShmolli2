if(USE_LMFIT)
    add_subdirectory(thirdParty/lmfit)
    include_directories (${lmfit_SOURCE_DIR}/lib)
    set(TOMATO_LIBS_TO_LINK ${TOMATO_LIBS_TO_LINK} lmfit)
    set(LIB_INSTALL OFF)
    set(LIB_MAN OFF)
endif(USE_LMFIT)
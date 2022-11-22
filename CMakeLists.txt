cmake_minimum_required(VERSION 3.5)

include(cmake/platform.cmake)

set(USE_ASM ON CACHE BOOL "Use asm implementation for Fr and Fq")

project(witnesscalc LANGUAGES CXX ASM)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("USE_ASM=" ${USE_ASM})
message("CMAKE_CROSSCOMPILING=" ${CMAKE_CROSSCOMPILING})

message("GMP_PREFIX=" ${GMP_PREFIX})
message("GMP_INCLUDE_DIR=" ${GMP_INCLUDE_DIR})
message("GMP_LIB_DIR=" ${GMP_LIB_DIR})

if (NOT EXISTS ${GMP_INCLUDE_FILE_FULLPATH})
    message("WARNING: ${GMP_INCLUDE_FILE_FULLPATH} is not found and so system ${GMP_INCLUDE_FILE} is used.")
endif()

if (NOT EXISTS ${GMP_LIB_FILE_FULLPATH})
    message("WARNING: ${GMP_LIB_FILE_FULLPATH} is not found and so system ${GMP_LIB_FILE} is used.")
    set(GMP_LIB gmp)
endif()


include_directories(BEFORE ${GMP_INCLUDE_DIR})

add_subdirectory(src)


install(TARGETS
    tests
    test_platform
    auth
    witnesscalc_auth
    witnesscalc_authStatic
    authV2
    witnesscalc_authV2
    witnesscalc_authV2Static
    credentialAtomicQuerySig
    witnesscalc_credentialAtomicQuerySig
    witnesscalc_credentialAtomicQuerySigStatic
    credentialAtomicQueryMTP
    witnesscalc_credentialAtomicQueryMTP
    witnesscalc_credentialAtomicQueryMTPStatic
    fr
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    BUNDLE DESTINATION ${CMAKE_INSTALL_PREFIX}/app
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

install(FILES "${GMP_LIB_DIR}/${GMP_LIB_FILE}"
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

install(FILES src/auth.dat src/credentialAtomicQuerySig.dat src/credentialAtomicQueryMTP.dat
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

install(FILES
    src/witnesscalc.h
    src/witnesscalc_auth.h
    src/witnesscalc_authV2.h
    src/witnesscalc_credentialAtomicQuerySig.h
    src/witnesscalc_credentialAtomicQueryMTP.h
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include)

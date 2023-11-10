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
    #auth
    #witnesscalc_auth
    #witnesscalc_authStatic
    authV2
    witnesscalc_authV2
    witnesscalc_authV2Static
    credentialAtomicQueryMTPV2
    witnesscalc_credentialAtomicQueryMTPV2
    witnesscalc_credentialAtomicQueryMTPV2Static
    credentialAtomicQuerySigV2
    witnesscalc_credentialAtomicQuerySigV2
    witnesscalc_credentialAtomicQuerySigV2Static
    credentialAtomicQueryMTPV2OnChain
    witnesscalc_credentialAtomicQueryMTPV2OnChain
    witnesscalc_credentialAtomicQueryMTPV2OnChainStatic
    credentialAtomicQuerySigV2OnChain
    witnesscalc_credentialAtomicQuerySigV2OnChain
    witnesscalc_credentialAtomicQuerySigV2OnChainStatic
    fr
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    BUNDLE DESTINATION ${CMAKE_INSTALL_PREFIX}/app
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

install(FILES "${GMP_LIB_DIR}/${GMP_LIB_FILE}"
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

install(FILES
    # src/auth.dat
    src/authV2.dat
    src/credentialAtomicQuerySigV2.dat
    src/credentialAtomicQueryMTPV2.dat
    src/credentialAtomicQuerySigV2OnChain.dat
    src/credentialAtomicQueryMTPV2OnChain.dat
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

install(FILES
    src/witnesscalc.h
    #src/witnesscalc_auth.h
    src/witnesscalc_authV2.h
    src/witnesscalc_credentialAtomicQuerySigV2.h
    src/witnesscalc_credentialAtomicQueryMTPV2.h
    src/witnesscalc_credentialAtomicQuerySigV2OnChain.h
    src/witnesscalc_credentialAtomicQueryMTPV2OnChain.h
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include)

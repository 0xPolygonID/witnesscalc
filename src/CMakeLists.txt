include_directories(
    ../src
    ../build
    ../depends/json/single_include)

link_libraries(${GMP_LIB})


if(USE_ASM)
    add_definitions(-DUSE_ASM)

    if (CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin")
        set(NASM_FLAGS "-fmacho64 --prefix _")
    else()
        set(NASM_FLAGS -felf64)
    endif()

    add_custom_command(OUTPUT ${CMAKE_SOURCE_DIR}/build/fr_asm.o
        COMMAND nasm ${NASM_FLAGS} fr.asm -o fr_asm.o
        MAIN_DEPENDENCY ${CMAKE_SOURCE_DIR}/build/fr.asm
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
endif()

set(FR_SOURCES
    ../build/fr.hpp
    ../build/fr.cpp
    )

if(USE_ASM)
    set(FR_SOURCES ${FR_SOURCES} ../build/fr_asm.o)
endif()

add_library(fr STATIC ${FR_SOURCES})
set_target_properties(fr PROPERTIES POSITION_INDEPENDENT_CODE ON)

link_libraries(fr)


add_executable(tests tests.cpp)
add_executable(test_platform test_platform.cpp)


set(LIB_SOURCES
    calcwit.cpp
    witnesscalc.h
    witnesscalc.cpp
    )

# auth
set(AUTH_SOURCES ${LIB_SOURCES}
    auth.cpp
    witnesscalc_auth.h
    witnesscalc_auth.cpp
    )

add_library(witnesscalc_auth SHARED ${AUTH_SOURCES})
add_library(witnesscalc_authStatic STATIC ${AUTH_SOURCES})
set_target_properties(witnesscalc_authStatic PROPERTIES OUTPUT_NAME witnesscalc_auth)

add_executable(auth main.cpp)
target_link_libraries(auth witnesscalc_authStatic)


# credentialAtomicQuerySig
set(CREDENTIALATOMICQUERYSIG_SOURCES ${LIB_SOURCES}
    credentialAtomicQuerySig.cpp
    witnesscalc_credentialAtomicQuerySig.h
    witnesscalc_credentialAtomicQuerySig.cpp
    )

add_library(witnesscalc_credentialAtomicQuerySig SHARED ${CREDENTIALATOMICQUERYSIG_SOURCES})
add_library(witnesscalc_credentialAtomicQuerySigStatic STATIC ${CREDENTIALATOMICQUERYSIG_SOURCES})
set_target_properties(witnesscalc_credentialAtomicQuerySigStatic PROPERTIES OUTPUT_NAME witnesscalc_credentialAtomicQuerySig)

add_executable(credentialAtomicQuerySig main.cpp)
target_link_libraries(credentialAtomicQuerySig witnesscalc_credentialAtomicQuerySigStatic)

# credentialAtomicQueryMTP
set(CREDENTIALATOMICQUERYMTP_SOURCES ${LIB_SOURCES}
    credentialAtomicQueryMTP.cpp
    witnesscalc_credentialAtomicQueryMTP.h
    witnesscalc_credentialAtomicQueryMTP.cpp
    )

add_library(witnesscalc_credentialAtomicQueryMTP SHARED ${CREDENTIALATOMICQUERYMTP_SOURCES})
add_library(witnesscalc_credentialAtomicQueryMTPStatic STATIC ${CREDENTIALATOMICQUERYMTP_SOURCES})
set_target_properties(witnesscalc_credentialAtomicQueryMTPStatic PROPERTIES OUTPUT_NAME witnesscalc_credentialAtomicQueryMTP)

add_executable(credentialAtomicQueryMTP main.cpp)
target_link_libraries(credentialAtomicQueryMTP witnesscalc_credentialAtomicQueryMTPStatic)

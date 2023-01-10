include_directories(
    ../src
    ../build
    ../depends/json/single_include)

link_libraries(${GMP_LIB})

add_definitions(${GMP_DEFINIONS})

if(USE_ASM)
    if(ARCH MATCHES "arm64")
            add_definitions(-DUSE_ASM -DARCH_ARM64)
    elseif(ARCH MATCHES "x86_64")
            add_definitions(-DUSE_ASM -DARCH_X86_64)
    endif()
endif()

if(USE_ASM AND ARCH MATCHES "x86_64")

    if (CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin")
        set(NASM_FLAGS "-fmacho64 --prefix _")
    else()
        set(NASM_FLAGS -felf64)
    endif()

    add_custom_command(OUTPUT ${CMAKE_SOURCE_DIR}/build/fq_asm.o
        COMMAND nasm ${NASM_FLAGS} fq.asm -o fq_asm.o
        DEPENDS ${CMAKE_SOURCE_DIR}/build/fq.asm
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

    add_custom_command(OUTPUT ${CMAKE_SOURCE_DIR}/build/fr_asm.o
        COMMAND nasm ${NASM_FLAGS} fr.asm -o fr_asm.o
        DEPENDS ${CMAKE_SOURCE_DIR}/build/fr.asm
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
endif()

set(FR_SOURCES
    ../build/fr.hpp
    ../build/fr.cpp
    )

if(USE_ASM)
    if(ARCH MATCHES "arm64")
        set(FR_SOURCES ${FR_SOURCES} ../build/fr_raw_arm64.s ../build/fr_raw_generic.cpp ../build/fr_generic.cpp)
    elseif(ARCH MATCHES "x86_64")
        set(FR_SOURCES ${FR_SOURCES} ../build/fr_asm.o)
    endif()
else()
    set(FR_SOURCES ${FR_SOURCES} ../build/fr_generic.cpp ../build/fr_raw_generic.cpp)
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

target_compile_definitions(witnesscalc_auth PUBLIC CIRCUIT_NAME=auth)
target_compile_definitions(witnesscalc_authStatic PUBLIC CIRCUIT_NAME=auth)
target_compile_definitions(auth PUBLIC CIRCUIT_NAME=auth)

# authV2
set(AUTHV2_SOURCES ${LIB_SOURCES}
    authV2.cpp
    witnesscalc_authV2.h
    witnesscalc_authV2.cpp
    )

add_library(witnesscalc_authV2 SHARED ${AUTHV2_SOURCES})
add_library(witnesscalc_authV2Static STATIC ${AUTHV2_SOURCES})
set_target_properties(witnesscalc_authV2Static PROPERTIES OUTPUT_NAME witnesscalc_authV2)

add_executable(authV2 main.cpp)
target_link_libraries(authV2 witnesscalc_authV2Static)

target_compile_definitions(witnesscalc_authV2 PUBLIC CIRCUIT_NAME=authV2)
target_compile_definitions(witnesscalc_authV2Static PUBLIC CIRCUIT_NAME=authV2)
target_compile_definitions(authV2 PUBLIC CIRCUIT_NAME=authV2)

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

target_compile_definitions(witnesscalc_credentialAtomicQuerySig PUBLIC CIRCUIT_NAME=credentialAtomicQuerySig)
target_compile_definitions(witnesscalc_credentialAtomicQuerySigStatic PUBLIC CIRCUIT_NAME=credentialAtomicQuerySig)
target_compile_definitions(credentialAtomicQuerySig PUBLIC CIRCUIT_NAME=credentialAtomicQuerySig)

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

target_compile_definitions(witnesscalc_credentialAtomicQueryMTP PUBLIC CIRCUIT_NAME=credentialAtomicQueryMTP)
target_compile_definitions(witnesscalc_credentialAtomicQueryMTPStatic PUBLIC CIRCUIT_NAME=credentialAtomicQueryMTP)
target_compile_definitions(credentialAtomicQueryMTP PUBLIC CIRCUIT_NAME=credentialAtomicQueryMTP)

# credentialAtomicQueryMTPV2
set(CREDENTIALATOMICQUERYMTPV2_SOURCES ${LIB_SOURCES}
    credentialAtomicQueryMTPV2.cpp
    witnesscalc_credentialAtomicQueryMTPV2.h
    witnesscalc_credentialAtomicQueryMTPV2.cpp
    )

add_library(witnesscalc_credentialAtomicQueryMTPV2 SHARED ${CREDENTIALATOMICQUERYMTPV2_SOURCES})
add_library(witnesscalc_credentialAtomicQueryMTPV2Static STATIC ${CREDENTIALATOMICQUERYMTPV2_SOURCES})
set_target_properties(witnesscalc_credentialAtomicQueryMTPV2Static PROPERTIES OUTPUT_NAME witnesscalc_credentialAtomicQueryMTPV2)

add_executable(credentialAtomicQueryMTPV2 main.cpp)
target_link_libraries(credentialAtomicQueryMTPV2 witnesscalc_credentialAtomicQueryMTPV2Static)

target_compile_definitions(witnesscalc_credentialAtomicQueryMTPV2 PUBLIC CIRCUIT_NAME=credentialAtomicQueryMTPV2)
target_compile_definitions(witnesscalc_credentialAtomicQueryMTPV2Static PUBLIC CIRCUIT_NAME=credentialAtomicQueryMTPV2)
target_compile_definitions(credentialAtomicQueryMTPV2 PUBLIC CIRCUIT_NAME=credentialAtomicQueryMTPV2)

# credentialAtomicQuerySigV2
set(CREDENTIALATOMICQUERYSIGV2_SOURCES ${LIB_SOURCES}
    credentialAtomicQuerySigV2.cpp
    witnesscalc_credentialAtomicQuerySigV2.h
    witnesscalc_credentialAtomicQuerySigV2.cpp
    )

add_library(witnesscalc_credentialAtomicQuerySigV2 SHARED ${CREDENTIALATOMICQUERYSIGV2_SOURCES})
add_library(witnesscalc_credentialAtomicQuerySigV2Static STATIC ${CREDENTIALATOMICQUERYSIGV2_SOURCES})
set_target_properties(witnesscalc_credentialAtomicQuerySigV2Static PROPERTIES OUTPUT_NAME witnesscalc_credentialAtomicQuerySigV2)

add_executable(credentialAtomicQuerySigV2 main.cpp)
target_link_libraries(credentialAtomicQuerySigV2 witnesscalc_credentialAtomicQuerySigV2Static)

target_compile_definitions(witnesscalc_credentialAtomicQuerySigV2 PUBLIC CIRCUIT_NAME=credentialAtomicQuerySigV2)
target_compile_definitions(witnesscalc_credentialAtomicQuerySigV2Static PUBLIC CIRCUIT_NAME=credentialAtomicQuerySigV2)
target_compile_definitions(credentialAtomicQuerySigV2 PUBLIC CIRCUIT_NAME=credentialAtomicQuerySigV2)
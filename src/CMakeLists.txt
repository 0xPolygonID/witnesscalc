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
        set(NASM_FLAGS -fmacho64 --prefix _)
    else()
        set(NASM_FLAGS -felf64 -DPIC)
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

# # auth
# set(AUTH_SOURCES ${LIB_SOURCES}
#     auth.cpp
#     witnesscalc_auth.h
#     witnesscalc_auth.cpp
#     )
#
# add_library(witnesscalc_auth SHARED ${AUTH_SOURCES})
# add_library(witnesscalc_authStatic STATIC ${AUTH_SOURCES})
# set_target_properties(witnesscalc_authStatic PROPERTIES OUTPUT_NAME witnesscalc_auth)
#
# add_executable(auth main.cpp)
# target_link_libraries(auth witnesscalc_authStatic)
#
# target_compile_definitions(witnesscalc_auth PUBLIC CIRCUIT_NAME=auth)
# target_compile_definitions(witnesscalc_authStatic PUBLIC CIRCUIT_NAME=auth)
# target_compile_definitions(auth PUBLIC CIRCUIT_NAME=auth)

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

# credentialAtomicQueryMTPV2
set(CREDENTIALATOMICQUERYMTPV2OFFCHAIN_SOURCES ${LIB_SOURCES}
    credentialAtomicQueryMTPV2.cpp
    witnesscalc_credentialAtomicQueryMTPV2.h
    witnesscalc_credentialAtomicQueryMTPV2.cpp
    )

add_library(witnesscalc_credentialAtomicQueryMTPV2 SHARED ${CREDENTIALATOMICQUERYMTPV2OFFCHAIN_SOURCES})
add_library(witnesscalc_credentialAtomicQueryMTPV2Static STATIC ${CREDENTIALATOMICQUERYMTPV2OFFCHAIN_SOURCES})
set_target_properties(witnesscalc_credentialAtomicQueryMTPV2Static PROPERTIES OUTPUT_NAME witnesscalc_credentialAtomicQueryMTPV2)

add_executable(credentialAtomicQueryMTPV2 main.cpp)
target_link_libraries(credentialAtomicQueryMTPV2 witnesscalc_credentialAtomicQueryMTPV2Static)

target_compile_definitions(witnesscalc_credentialAtomicQueryMTPV2 PUBLIC CIRCUIT_NAME=credentialAtomicQueryMTPV2)
target_compile_definitions(witnesscalc_credentialAtomicQueryMTPV2Static PUBLIC CIRCUIT_NAME=credentialAtomicQueryMTPV2)
target_compile_definitions(credentialAtomicQueryMTPV2 PUBLIC CIRCUIT_NAME=credentialAtomicQueryMTPV2)

# credentialAtomicQuerySigV2
set(CREDENTIALATOMICQUERYSIGOFFCHAIN_SOURCES ${LIB_SOURCES}
    credentialAtomicQuerySigV2.cpp
    witnesscalc_credentialAtomicQuerySigV2.h
    witnesscalc_credentialAtomicQuerySigV2.cpp
    )

add_library(witnesscalc_credentialAtomicQuerySigV2 SHARED ${CREDENTIALATOMICQUERYSIGOFFCHAIN_SOURCES})
add_library(witnesscalc_credentialAtomicQuerySigV2Static STATIC ${CREDENTIALATOMICQUERYSIGOFFCHAIN_SOURCES})
set_target_properties(witnesscalc_credentialAtomicQuerySigV2Static PROPERTIES OUTPUT_NAME witnesscalc_credentialAtomicQuerySigV2)

add_executable(credentialAtomicQuerySigV2 main.cpp)
target_link_libraries(credentialAtomicQuerySigV2 witnesscalc_credentialAtomicQuerySigV2Static)

target_compile_definitions(witnesscalc_credentialAtomicQuerySigV2 PUBLIC CIRCUIT_NAME=credentialAtomicQuerySigV2)
target_compile_definitions(witnesscalc_credentialAtomicQuerySigV2Static PUBLIC CIRCUIT_NAME=credentialAtomicQuerySigV2)
target_compile_definitions(credentialAtomicQuerySigV2 PUBLIC CIRCUIT_NAME=credentialAtomicQuerySigV2)

# credentialAtomicQueryMTPV2OnChain
set(CREDENTIALATOMICQUERYMTPV2ONCHAIN_SOURCES ${LIB_SOURCES}
    credentialAtomicQueryMTPV2OnChain.cpp
    witnesscalc_credentialAtomicQueryMTPV2OnChain.h
    witnesscalc_credentialAtomicQueryMTPV2OnChain.cpp
    )

add_library(witnesscalc_credentialAtomicQueryMTPV2OnChain SHARED ${CREDENTIALATOMICQUERYMTPV2ONCHAIN_SOURCES})
add_library(witnesscalc_credentialAtomicQueryMTPV2OnChainStatic STATIC ${CREDENTIALATOMICQUERYMTPV2ONCHAIN_SOURCES})
set_target_properties(witnesscalc_credentialAtomicQueryMTPV2OnChainStatic PROPERTIES OUTPUT_NAME witnesscalc_credentialAtomicQueryMTPV2OnChain)

add_executable(credentialAtomicQueryMTPV2OnChain main.cpp)
target_link_libraries(credentialAtomicQueryMTPV2OnChain witnesscalc_credentialAtomicQueryMTPV2OnChainStatic)

target_compile_definitions(witnesscalc_credentialAtomicQueryMTPV2OnChain PUBLIC CIRCUIT_NAME=credentialAtomicQueryMTPV2OnChain)
target_compile_definitions(witnesscalc_credentialAtomicQueryMTPV2OnChainStatic PUBLIC CIRCUIT_NAME=credentialAtomicQueryMTPV2OnChain)
target_compile_definitions(credentialAtomicQueryMTPV2OnChain PUBLIC CIRCUIT_NAME=credentialAtomicQueryMTPV2OnChain)

# credentialAtomicQuerySigV2OnChain
set(CREDENTIALATOMICQUERYSIGONCHAIN_SOURCES ${LIB_SOURCES}
    credentialAtomicQuerySigV2OnChain.cpp
    witnesscalc_credentialAtomicQuerySigV2OnChain.h
    witnesscalc_credentialAtomicQuerySigV2OnChain.cpp
    )

add_library(witnesscalc_credentialAtomicQuerySigV2OnChain SHARED ${CREDENTIALATOMICQUERYSIGONCHAIN_SOURCES})
add_library(witnesscalc_credentialAtomicQuerySigV2OnChainStatic STATIC ${CREDENTIALATOMICQUERYSIGONCHAIN_SOURCES})
set_target_properties(witnesscalc_credentialAtomicQuerySigV2OnChainStatic PROPERTIES OUTPUT_NAME witnesscalc_credentialAtomicQuerySigV2OnChain)

add_executable(credentialAtomicQuerySigV2OnChain main.cpp)
target_link_libraries(credentialAtomicQuerySigV2OnChain witnesscalc_credentialAtomicQuerySigV2OnChainStatic)

target_compile_definitions(witnesscalc_credentialAtomicQuerySigV2OnChain PUBLIC CIRCUIT_NAME=credentialAtomicQuerySigV2OnChain)
target_compile_definitions(witnesscalc_credentialAtomicQuerySigV2OnChainStatic PUBLIC CIRCUIT_NAME=credentialAtomicQuerySigV2OnChain)
target_compile_definitions(credentialAtomicQuerySigV2OnChain PUBLIC CIRCUIT_NAME=credentialAtomicQuerySigV2OnChain)

# credentialAtomicQueryV3
set(CREDENTIALATOMICQUERYV3OFFCHAIN_SOURCES ${LIB_SOURCES}
    credentialAtomicQueryV3.cpp
    witnesscalc_credentialAtomicQueryV3.h
    witnesscalc_credentialAtomicQueryV3.cpp
    )

add_library(witnesscalc_credentialAtomicQueryV3 SHARED ${CREDENTIALATOMICQUERYV3OFFCHAIN_SOURCES})
add_library(witnesscalc_credentialAtomicQueryV3Static STATIC ${CREDENTIALATOMICQUERYV3OFFCHAIN_SOURCES})
set_target_properties(witnesscalc_credentialAtomicQueryV3Static PROPERTIES OUTPUT_NAME witnesscalc_credentialAtomicQueryV3)

add_executable(credentialAtomicQueryV3 main.cpp)
target_link_libraries(credentialAtomicQueryV3 witnesscalc_credentialAtomicQueryV3Static)

target_compile_definitions(witnesscalc_credentialAtomicQueryV3 PUBLIC CIRCUIT_NAME=credentialAtomicQueryV3)
target_compile_definitions(witnesscalc_credentialAtomicQueryV3Static PUBLIC CIRCUIT_NAME=credentialAtomicQueryV3)
target_compile_definitions(credentialAtomicQueryV3 PUBLIC CIRCUIT_NAME=credentialAtomicQueryV3)

# credentialAtomicQueryV3OnChain
set(CREDENTIALATOMICQUERYV3ONCHAIN_SOURCES ${LIB_SOURCES}
    credentialAtomicQueryV3OnChain.cpp
    witnesscalc_credentialAtomicQueryV3OnChain.h
    witnesscalc_credentialAtomicQueryV3OnChain.cpp
    )

add_library(witnesscalc_credentialAtomicQueryV3OnChain SHARED ${CREDENTIALATOMICQUERYV3ONCHAIN_SOURCES})
add_library(witnesscalc_credentialAtomicQueryV3OnChainStatic STATIC ${CREDENTIALATOMICQUERYV3ONCHAIN_SOURCES})
set_target_properties(witnesscalc_credentialAtomicQueryV3OnChainStatic PROPERTIES OUTPUT_NAME witnesscalc_credentialAtomicQueryV3OnChain)

add_executable(credentialAtomicQueryV3OnChain main.cpp)
target_link_libraries(credentialAtomicQueryV3OnChain witnesscalc_credentialAtomicQueryV3OnChainStatic)

target_compile_definitions(witnesscalc_credentialAtomicQueryV3OnChain PUBLIC CIRCUIT_NAME=credentialAtomicQueryV3OnChain)
target_compile_definitions(witnesscalc_credentialAtomicQueryV3OnChainStatic PUBLIC CIRCUIT_NAME=credentialAtomicQueryV3OnChain)
target_compile_definitions(credentialAtomicQueryV3OnChain PUBLIC CIRCUIT_NAME=credentialAtomicQueryV3OnChain)

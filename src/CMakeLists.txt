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


include_directories(
    ../src
    ../build
    ../depends/json/single_include)

link_libraries(${GMP_LIB})


set(UNIT_TEST_SOURCES
    ../build/fr.hpp
    ../build/fr.cpp
    tests.cpp
    )

if(USE_ASM)
    set(UNIT_TEST_SOURCES ${UNIT_TEST_SOURCES} ../build/fr_asm.o)
endif()

add_executable(tests ${UNIT_TEST_SOURCES})


set(LIB_SOURCES
    ../build/fr.hpp
    ../build/fr.cpp
    calcwit.cpp
    witnesscalc.h
    witnesscalc.cpp
    )

if(USE_ASM)
    set(LIB_SOURCES ${LIB_SOURCES} ../build/fr_asm.o)
endif()

# auth
add_library(witnesscalc_auth SHARED ${LIB_SOURCES})

add_library(witnesscalc_authStatic STATIC ${LIB_SOURCES})
set_target_properties(witnesscalc_authStatic PROPERTIES OUTPUT_NAME witnesscalc_auth)

add_executable(auth main.cpp auth.cpp)
target_link_libraries(auth witnesscalc_authStatic)

# credentialAtomicQuerySig
add_library(witnesscalc_credentialAtomicQuerySig SHARED ${LIB_SOURCES})

add_library(witnesscalc_credentialAtomicQuerySigStatic STATIC ${LIB_SOURCES})
set_target_properties(witnesscalc_credentialAtomicQuerySigStatic PROPERTIES OUTPUT_NAME witnesscalc_credentialAtomicQuerySig)

add_executable(credentialAtomicQuerySig main.cpp credentialAtomicQuerySig.cpp)
target_link_libraries(credentialAtomicQuerySig witnesscalc_credentialAtomicQuerySigStatic)

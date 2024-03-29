add_definitions(-DPLATFORM=LINUX -DLINUX)

find_package(PkgConfig REQUIRED)

pkg_check_modules(OPENSSL_LIBCRYPTO REQUIRED libcrypto)
pkg_check_modules(TTCN3 REQUIRED ttcn3-nomain)
pkg_check_modules(YAML_CPP REQUIRED yaml-cpp)
pkg_check_modules(ETSITS102941 REQUIRED EtsiTs102941)

add_executable( unit_tests
    itspki-tests.cpp
    itspki-cmd-args.cpp
    itspki-common.cpp
    )


set(TEST_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src/include ${OPENSSL_LIBCRYPTO_INCLUDE_DIRS} ${TTCN3_INCLUDE_DIRS} ${YAML_CPP_INCLUDE_DIRS} ${LIBETSITS102941_INCLUDE_DIRS})
message("In Tests: includes: ${TEST_INCLUDE_DIRS}")

include_directories(./ ${TEST_INCLUDE_DIRS})

target_include_directories(unit_tests PUBLIC ${TEST_INCLUDE_DIRS})
target_compile_options(unit_tests PUBLIC ${OPENSSL_LIBCRYPTO_CFLAGS_OTHER})

target_link_libraries(
    unit_tests
    gtest_main
    # libitspki_static
    libitspki_debug_static
    -lboost_program_options
    -lxml2 -lpthread -lrt -lncurses
    -lcrypto
    #    ${YAML_CPP_LDFLAGS}
    #    ${TTCN3_LDFLAGS}
    #    ${ETSITS102941_LDFLAGS}
)

target_compile_options( unit_tests PRIVATE ${TTCN3_CFLAGS} ${ETSITS102941_CFLAGS} ${YAML_CPP_CFLAGS} ${OPENSSL_LIBCRYPTO_CFLAGS} )
target_compile_definitions( unit_tests PUBLIC ITSPKI_CONFIG_FILE="${PROJECT_BINARY_DIR}/config.h" ITS_PKI_DEBUG)
target_link_libraries( unit_tests ${YAML_CPP_LDFLAGS} ${TTCN3_LDFLAGS} ${ETSITS102941_LDFLAGS} ${YAML_CPP_LDFLAGS})

add_test(
  NAME
    unit_itspki
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
  )

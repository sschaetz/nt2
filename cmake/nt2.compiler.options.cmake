################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

if(NOT NT2_COMPILER_OPTIONS_INCLUDED)
set(NT2_COMPILER_OPTIONS_INCLUDED 1)

include(nt2.info)

# Use lib prefix for static libraries like Boost does
if(WIN32)
  set(CMAKE_STATIC_LIBRARY_PREFIX lib)
endif()

# Remove /EHsc from CMAKE_CXX_FLAGS and re-add per configuration; useful to avoid 'overriding' warnings
if(CMAKE_CXX_FLAGS MATCHES "/EHsc")
  string(REPLACE " /EHsc" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  foreach(config Debug Release)
    string(TOUPPER ${config} config_U)
    set(CMAKE_CXX_FLAGS_${config_U} "/EHsc ${CMAKE_CXX_FLAGS_${config_U}}")
  endforeach()
endif()

set(NT2_FLAGS_TEST "${NT2_FLAGS_TEST} -DBOOST_ENABLE_ASSERT_HANDLER -DNT2_ASSERTS_AS_EXCEPTIONS -DNT2_WARNINGS_AS_ASSERTS")
set(NT2_FLAGS_BENCH "${CMAKE_CXX_FLAGS_RELEASE}")

# No debug symbols in tests because of excessive time and memory costs at compile time;
# use special debug targets instead
set(NT2_FLAGS_TESTDEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${NT2_FLAGS_TEST} -DBOOST_FORCEINLINE=inline")

if(MSVC)
  # Global MSVC settings: IEEE754 floating-point
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /fp:precise")

  set(NT2_FLAGS_TEST "${NT2_FLAGS_TEST} /MDd /Oxt /EHa")
  string(REPLACE "/EHsc" "/EHa" NT2_FLAGS_TESTDEBUG "${NT2_FLAGS_TESTDEBUG}")
  set(NT2_FLAGS_BENCH "/DNDEBUG /MD /D_SECURE_SCL=0 /GL /Oxt /wd4530")

elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # Strict aliasing disabled due to GCC bug #50800
  # -D_GLIBCXX_DEBUG=1 not used because of incompatibilities with libraries
  if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-strict-aliasing -DBOOST_SIMD_NO_STRICT_ALIASING")
  endif()
  set(NT2_FLAGS_TEST "${NT2_FLAGS_TEST} -O2")
  if(NT2_ARCH_X86) # valgrind doesn't support SSE4 or AVX
     set(NT2_FLAGS_TESTDEBUG "${NT2_FLAGS_TESTDEBUG} -mno-sse4.1 -mno-sse4.2 -mno-avx")
  endif()
  set(NT2_FLAGS_BENCH "-DNDEBUG -O3 -fomit-frame-pointer -fno-exceptions")

elseif(CMAKE_CXX_COMPILER_ID MATCHES "Intel")
  if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fp-model precise")
    set(NT2_FLAGS_TEST "${NT2_FLAGS_TEST} -O2")
    set(NT2_FLAGS_BENCH "${NT2_FLAGS_BENCH} -fno-exceptions")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /fp:precise")
    set(NT2_FLAGS_TEST "${NT2_FLAGS_TEST} /O2 /EHa")
    string(REPLACE "/EHsc" "" NT2_FLAGS_BENCH "${NT2_FLAGS_BENCH}")
    string(REPLACE "/EHsc" "/EHa" NT2_FLAGS_TESTDEBUG "${NT2_FLAGS_TESTDEBUG}")
  endif()
endif()

set(CMAKE_C_FLAGS_NT2TEST ${NT2_FLAGS_TEST})
set(CMAKE_C_FLAGS_NT2TESTDEBUG ${NT2_FLAGS_TESTDEBUG})
set(CMAKE_C_FLAGS_NT2BENCH ${NT2_FLAGS_BENCH})
set(CMAKE_C_FLAGS_NT2DEBUGEMPTY ${CMAKE_C_FLAGS})
set(CMAKE_CXX_FLAGS_NT2TEST ${NT2_FLAGS_TEST})
set(CMAKE_CXX_FLAGS_NT2TESTDEBUG ${NT2_FLAGS_TESTDEBUG})
set(CMAKE_CXX_FLAGS_NT2BENCH ${NT2_FLAGS_BENCH})
set(CMAKE_CXX_FLAGS_NT2DEBUGEMPTY ${CMAKE_CXX_FLAGS})
set(CMAKE_EXE_LINKER_FLAGS_NT2TEST ${CMAKE_EXE_LINKER_FLAGS_RELEASE})
set(CMAKE_EXE_LINKER_FLAGS_NT2TESTDEBUG ${CMAKE_EXE_LINKER_FLAGS_DEBUG})
set(CMAKE_EXE_LINKER_FLAGS_NT2BENCH ${CMAKE_EXE_LINKER_FLAGS_RELEASE})
set(CMAKE_EXE_LINKER_FLAGS_NT2DEBUGEMPTY ${CMAKE_EXE_LINKER_FLAGS})
set(CMAKE_SHARED_LINKER_FLAGS_NT2TEST ${CMAKE_SHARED_LINKER_FLAGS_RELEASE})
set(CMAKE_SHARED_LINKER_FLAGS_NT2TESTDEBUG ${CMAKE_SHARED_LINKER_FLAGS_DEBUG})
set(CMAKE_SHARED_LINKER_FLAGS_NT2BENCH ${CMAKE_SHARED_LINKER_FLAGS_RELEASE})
set(CMAKE_SHARED_LINKER_FLAGS_NT2DEBUGEMPTY ${CMAKE_SHARED_LINKER_FLAGS})
if(MSVC)
  set(CMAKE_EXE_LINKER_FLAGS_NT2BENCH "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG")
  set(CMAKE_SHARED_LINKER_FLAGS_NT2BENCH "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /LTCG")
endif()
set_property(GLOBAL APPEND PROPERTY DEBUG_CONFIGURATIONS NT2Test NT2TestDebug NT2DebugEmpty)

include(options/nt2.extra.warnings)

if(CMAKE_CXX_FLAGS MATCHES "[^ ]")
  message(STATUS "[nt2] Global flags: ${CMAKE_CXX_FLAGS}")
endif()

# Make sure no build type is selected
set(CMAKE_BUILD_TYPE "")

message(STATUS "[nt2] Debug flags: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "[nt2] Release flags: ${CMAKE_CXX_FLAGS_RELEASE}")

message(STATUS "[nt2] Test flags: ${CMAKE_CXX_FLAGS_NT2TEST}")
message(STATUS "[nt2] Test debug flags: ${CMAKE_CXX_FLAGS_NT2TESTDEBUG}")
message(STATUS "[nt2] Bench flags: ${CMAKE_CXX_FLAGS_NT2BENCH}")

endif()

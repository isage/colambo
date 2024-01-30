cmake_minimum_required(VERSION 3.2)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(colambo-helper)
include("${VITASDK}/share/vita.cmake" REQUIRED)

add_executable(${PROJECT_NAME}
  src/main.c
)

target_link_libraries(${PROJECT_NAME}
  SceDebugForDriver_stub
  SceSblAIMgrForDriver_stub
  SceIofilemgrForDriver_stub
  SceCtrlForDriver_stub
  SceKernelSuspendForDriver_stub
  SceSysclibForDriver_stub
  SceSysmemForDriver_stub
  SceThreadmgrForDriver_stub
  SceUsbdForDriver_stub
  SceUsbServForDriver_stub
  SceIdStorageForDriver_stub
  SceSysrootForKernel_stub
  SceSysconForDriver_stub
  ScePervasiveForDriver_stub
  SceSblSsMgrForDriver_stub
  SceHpremoteForDriver_stub
  taihenForKernel_stub
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES LINK_FLAGS "-nostdlib"
)

vita_create_self(${PROJECT_NAME}.skprx ${PROJECT_NAME}
  CONFIG colambo-helper.yml
  UNSAFE
)

vita_create_stubs(stubs colambo-helper ${CMAKE_CURRENT_SOURCE_DIR}/colambo-helper.yml KERNEL)

add_custom_target(colambo-helper_all
  ALL
  DEPENDS libcolambo-helper_stub.a
  DEPENDS libcolambo-helper_stub_weak.a
)

install(DIRECTORY ${CMAKE_BINARY_DIR}/stubs/
  DESTINATION lib
  FILES_MATCHING PATTERN "*.a"
)

install(FILES colambo-helper.h
  DESTINATION include
)

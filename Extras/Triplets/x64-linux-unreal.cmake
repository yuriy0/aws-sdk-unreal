set(VCPKG_TARGET_ARCHITECTURE x64)
set(VCPKG_CRT_LINKAGE dynamic)
set(VCPKG_LIBRARY_LINKAGE static)
set(VCPKG_CHAINLOAD_TOOLCHAIN_FILE ${CMAKE_CURRENT_LIST_DIR}/linux-clang-toolchain.cmake)

set(VCPKG_CMAKE_SYSTEM_NAME Linux)

set(VCPKG_CXX_FLAGS_RELEASE "-DUSE_AWS_MEMORY_MANAGEMENT -stdlib=libc++")
set(VCPKG_C_FLAGS_RELEASE "-DUSE_AWS_MEMORY_MANAGEMENT -stdlib=libc++")
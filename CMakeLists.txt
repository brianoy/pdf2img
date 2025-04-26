cmake_minimum_required(VERSION 3.10)
project(PDFProcessing)

# 設置 C++ 標準
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加 vcpkg 的包含目錄
include_directories("C:/vcpkg/installed/x64-windows/include")

# 添加 vcpkg 的庫目錄
link_directories("C:/vcpkg/installed/x64-windows/lib")

# 添加可執行文件
add_executable(${PROJECT_NAME} pdf2img.cpp)

# 查找並連接所需的庫
find_library(POPPLER_CPP_LIB poppler-cpp PATHS "C:/vcpkg/installed/x64-windows/lib" REQUIRED)
find_library(CAIRO_LIB cairo PATHS "C:/vcpkg/installed/x64-windows/lib" REQUIRED)

# 連接庫
target_link_libraries(${PROJECT_NAME} PRIVATE 
    ${POPPLER_CPP_LIB}
    ${CAIRO_LIB}
)

# 設置輸出目錄
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# 添加後構建步驟以複製特定的 DLL 文件（在 Windows 上需要）
if(WIN32)
    # 定義要複製的特定 DLL 文件列表
    set(REQUIRED_DLLS
        "poppler-cpp.dll"
        "poppler.dll"
        "iconv-2.dll"
        "jpeg62.dll"
        "zlib1.dll"
    )
    
    # 為每個 DLL 添加複製命令
    foreach(DLL ${REQUIRED_DLLS})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/vcpkg/installed/x64-windows/bin/${DLL}"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
        )
    endforeach()
endif()

# 輸出調試信息
message(STATUS "POPPLER_CPP_LIB: ${POPPLER_CPP_LIB}")
message(STATUS "CAIRO_LIB: ${CAIRO_LIB}")
message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
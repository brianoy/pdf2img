@echo off
setlocal

:: 判斷目前資料夾是不是 build，如果是就 cd ..
for %%i in ("%cd%") do set CURRENT_FOLDER=%%~nxi
if /i "%CURRENT_FOLDER%"=="build" (
    echo back to parent folder...
    cd ..
)

:: 如果有 build 資料夾就刪掉，強制刪除
if exist build (
    echo delete old build folder...
    rmdir /s /q build
)

:: 建立新的 build 資料夾
mkdir build
cd build

:: 跑 cmake 設定
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake

:: 編譯
cmake --build . --config Release

PAUSE

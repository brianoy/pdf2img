# pdf2img

compile poppler binary from: https://github.com/oschwartz10612/poppler-windows/releases/lastest 

## vcpkg安裝

到[vcpkg的github](https://github.com/microsoft/vcpkg)下載zip，點擊bootstrap-vcpkg.bat編譯，接著資料夾就會出現vcpkg.exe，把帶有vcpkg.exe的資料夾搬去C:\vcpkg

把以下三個路徑加到windows環境變數Path中

```bash
C:\vcpkg
C:\vcpkg\installed\x64-windows\share
C:\vcpkg\installed\x64-windows\include
```

## package安裝

vcpkg install poppler

vcpkg install cairo

vcpkg integrate install
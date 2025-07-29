REM build script for engine

@echo off
setlocal enabledelayedexpansion

REM Get a list of all .c files
set cFilenames=
for /R %%f in (*.c) do (
    set cFilenames=!cFilenames! %%f
)

REM Set up build variables
set assembly=engine
set compilerFlags=-g -shared -Wvarargs -Wall -Werror
set includeFlags=-Isrc -I%VULKAN_SDK%/Include
set linkerFlags=-luser32 -lvulkan-1 -L%VULKAN_SDK%/Lib
set defines=-D_DEBUG -DEXPORT -D_CRT_SECURE_NO_WARNINGS

echo Building %assembly%...

clang %cFilenames% %compilerFlags% -o ../bin/%assembly%.dll %defines% %includeFlags% %linkerFlags%

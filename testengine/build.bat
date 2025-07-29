REM Build the Test Engine

@echo off
setlocal enabledelayedexpansion

REM Get a list of all .c files
set cFilenames=
for /R %%f in (*.c) do (
    set cFilenames=!cFilenames! %%f
)

REM Set up variables (no spaces around `=`)
set assembly=testengine
set compilerFlags=-g
set includeFlags=-Isrc -I../engine/src/
set linkerFlags=-L../bin/ -lengine
set defines=-D_DEBUG -DIMPORT

echo Building %assembly%...
clang %cFilenames% %compilerFlags% -o ../bin/%assembly%.exe %defines% %includeFlags% %linkerFlags%
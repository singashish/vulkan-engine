@echo off
REM Build all

echo "Building all projects..."

pushd engine
call build.bat
popd
if %errorlevel% neq 0 (
    echo "Engine build failed!"
    exit /b %errorlevel%
)

pushd testengine
call build.bat
popd
if %errorlevel% neq 0 (
    echo "TestEngine build failed!"
    exit /b %errorlevel%
)

echo "All projects built successfully!"
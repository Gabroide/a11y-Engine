@echo off
REM build.bat - Script de compilacion del Game Engine

if not exist bin (
    mkdir bin
)

REM [EJ.4] 
cl /EHsc /nologo /I src ^
    src\memory_leak.cpp ^
    /Fe:bin\main.exe /Fo:bin\

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo [ERROR] La compilacion ha fallado. Revisa los mensajes anteriores.
    exit /b 1
)

echo.
echo [OK] Compilacion completada: bin\main.exe

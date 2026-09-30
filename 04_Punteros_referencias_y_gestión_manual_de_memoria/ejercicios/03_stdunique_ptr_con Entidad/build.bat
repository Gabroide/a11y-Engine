@echo off
REM build.bat - Script de compilacion del Game Engine

if not exist bin (
    mkdir bin
)

REM [CAP.4] Todos los ficheros fuente pasan de .c a .cpp a partir de este
REM [CAP.4] capitulo. cl.exe detecta automaticamente que debe compilarlos
REM [CAP.4] como C++ por su extension, sin necesidad de opciones extra.
cl /EHsc /nologo /I src ^
    src\main.cpp ^
    src\math\vector2.cpp ^
    src\math\vector3.cpp ^
    src\core\entidad.cpp ^
    src\core\buffer_raii.cpp ^
    /Fe:bin\main.exe /Fo:bin\

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo [ERROR] La compilacion ha fallado. Revisa los mensajes anteriores.
    exit /b 1
)

echo.
echo [OK] Compilacion completada: bin\main.exe

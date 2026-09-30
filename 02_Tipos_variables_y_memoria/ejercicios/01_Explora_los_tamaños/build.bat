@echo off
REM build.bat - Script de compilacion del Game Engine

if not exist bin (
    mkdir bin
)

REM [CAP.2] Ahora compilamos varios ficheros .c: main.c y todo el modulo math.
REM [CAP.2] /I src indica al compilador que busque cabeceras tambien en "src",
REM [CAP.2] para que "math/vector2.h" se encuentre desde cualquier fichero.
cl /EHsc /nologo /I src ^
    src\main.c ^
    src\math\vector2.c ^
    src\math\vector3.c ^
    /Fe:bin\main.exe /Fo:bin\

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo [ERROR] La compilacion ha fallado. Revisa los mensajes anteriores.
    exit /b 1
)

echo.
echo [OK] Compilacion completada: bin\main.exe
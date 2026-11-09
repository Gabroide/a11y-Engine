@echo off
REM build.bat - Script de compilacion del Game Engine

if not exist bin (
    mkdir bin
)

REM [CAP.3] Se anade src\core\entidad.c a la lista de ficheros a compilar.
cl /EHsc /nologo /I src ^
    src\main.c ^
    src\math\vector2.c ^
    src\math\vector3.c ^
    src\core\entidad.c ^
    /Fe:bin\main.exe /Fo:bin\

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo [ERROR] La compilacion ha fallado. Revisa los mensajes anteriores.
    exit /b 1
)

echo.
echo [OK] Compilacion completada: bin\main.exe

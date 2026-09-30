@echo off
REM build.bat - Script de compilacion del Game Engine

if not exist bin (
    mkdir bin
)

REM [CAP.5] Se anade src\core\registro.cpp a la lista de ficheros.
REM [CAP.5] buffer_raii.cpp del capitulo 4 ya no se incluye: era un
REM [CAP.5] ejemplo didactico aislado, no una pieza permanente del motor.
cl /EHsc /nologo /I src ^
    src\main.cpp ^
    src\math\vector2.cpp ^
    src\math\vector3.cpp ^
    src\core\entidad.cpp ^
    src\core\registro.cpp ^
    src\core\temporizador.cpp ^
    /Fe:bin\main.exe /Fo:bin\

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo [ERROR] La compilacion ha fallado. Revisa los mensajes anteriores.
    exit /b 1
)

echo.
echo [OK] Compilacion completada: bin\main.exe

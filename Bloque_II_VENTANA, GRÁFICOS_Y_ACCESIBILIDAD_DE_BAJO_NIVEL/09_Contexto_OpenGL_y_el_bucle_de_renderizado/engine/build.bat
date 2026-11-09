@echo off
REM build.bat - Script de compilacion del Game Engine

if not exist bin (
    mkdir bin
)

REM [CAP.9] Se anaden contexto_opengl.cpp y entrada_teclado.cpp.
REM [CAP.9] opengl32.lib se anade a la lista de bibliotecas a enlazar.
cl /EHsc /nologo /I src ^
    src\main.cpp ^
    src\math\vector2.cpp ^
    src\math\vector3.cpp ^
    src\core\entidad.cpp ^
    src\core\registro.cpp ^
    src\components\componente_transform.cpp ^
    src\components\componente_salud.cpp ^
    src\plataforma\ventana.cpp ^
    src\plataforma\contexto_opengl.cpp ^
    src\plataforma\entrada_teclado.cpp ^
    /Fe:bin\main.exe /Fo:bin\ ^
    /link /SUBSYSTEM:WINDOWS user32.lib gdi32.lib opengl32.lib

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo [ERROR] La compilacion ha fallado. Revisa los mensajes anteriores.
    exit /b 1
)

echo.
echo [OK] Compilacion completada: bin\main.exe

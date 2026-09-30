@echo off
REM build.bat - Script de compilacion del Game Engine

if not exist bin (
    mkdir bin
)

REM [CAP.6] Se anaden los tres nuevos ficheros de src\components.
cl /EHsc /nologo /I src ^
    src\main.cpp ^
    src\math\vector2.cpp ^
    src\math\vector3.cpp ^
    src\core\entidad.cpp ^
    src\core\registro.cpp ^
    src\components\componente_transform.cpp ^
    src\components\componente_salud.cpp ^
    src\components\componente_etiqueta.cpp ^
    /Fe:bin\main.exe /Fo:bin\

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo [ERROR] La compilacion ha fallado. Revisa los mensajes anteriores.
    exit /b 1
)

echo.
echo [OK] Compilacion completada: bin\main.exe

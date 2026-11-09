@echo off
REM [CAP.1] build.bat - Script de compilacion del Game Engine
REM [CAP.1] Uso: ejecutar "build.bat" desde la carpeta raiz del proyecto,
REM [CAP.1] dentro del "Symbolo del sistema para desarrolladores de VS".

REM [CAP.1] Si la carpeta bin no existe, la creamos.
if not exist bin (
    mkdir bin
)

REM [CAP.1] Compilamos y enlazamos main.c en un unico paso.
REM [CAP.1]   /EHsc  -> modelo de excepciones estandar de C++ (lo dejamos ya preparado)
REM [CAP.1]   /Fe:   -> ruta y nombre del ejecutable de salida
REM [CAP.1]   /Fo:   -> ruta de los ficheros objeto intermedios (.obj)
cl /EHsc /nologo src\main.c /Fe:bin\main.exe /Fo:bin\

REM [CAP.1] %ERRORLEVEL% contiene el codigo de salida del ultimo comando ejecutado.
REM [CAP.1] cl.exe devuelve 0 si la compilacion tuvo exito.
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo [ERROR] La compilacion ha fallado. Revisa los mensajes anteriores.
    echo La hora actual es: %TIME%
    exit /b 1
)

echo.
echo [OK] Compilacion completada: bin\main.exe
echo La hora actual es: %TIME%

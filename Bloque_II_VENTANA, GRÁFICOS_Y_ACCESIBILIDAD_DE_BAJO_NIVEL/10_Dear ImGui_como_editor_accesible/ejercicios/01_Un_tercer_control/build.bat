@echo off
REM build.bat - Script de compilacion del Game Engine

if not exist bin (
    mkdir bin
)

REM [CAP.10] Se anaden los ficheros de Dear ImGui (libs\imgui) y nuestra
REM [CAP.10] propia capa de integracion (src\editor\interfaz_editor.cpp).
cl /EHsc /nologo /I src /I libs\imgui /I libs\imgui\backends ^
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
    src\editor\interfaz_editor.cpp ^
    libs\imgui\imgui.cpp ^
    libs\imgui\imgui_draw.cpp ^
    libs\imgui\imgui_tables.cpp ^
    libs\imgui\imgui_widgets.cpp ^
    libs\imgui\backends\imgui_impl_win32.cpp ^
    libs\imgui\backends\imgui_impl_opengl3.cpp ^
    /Fe:bin\main.exe /Fo:bin\ ^
    /link /SUBSYSTEM:WINDOWS user32.lib gdi32.lib opengl32.lib

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo [ERROR] La compilacion ha fallado. Revisa los mensajes anteriores.
    exit /b 1
)

echo.
echo [OK] Compilacion completada: bin\main.exe
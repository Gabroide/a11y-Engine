// [CAP.11] interfaz_editor.cpp
#include "interfaz_editor.h"
#include "../../libs/imgui/imgui.h"
#include "../../libs/imgui/backends/imgui_impl_win32.h"
#include "../../libs/imgui/backends/imgui_impl_opengl3.h"
#include <cstring>

InterfazEditor::InterfazEditor(HWND hwnd) : hwndVentana(hwnd), ultimoControlAnunciado("") {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplOpenGL3_Init("#version 130");
}

InterfazEditor::~InterfazEditor() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void InterfazEditor::nuevoFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

void InterfazEditor::renderizar() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void InterfazEditor::anunciarSiCambioFoco(const char* nombreControl, BusAccesibilidad& bus, Registro& registro) {
    if (ImGui::IsItemFocused()) {
        if (strcmp(ultimoControlAnunciado, nombreControl) != 0) {
            bus.anunciar(nombreControl, registro);
            bus.notificarCambioFocoMSAA(hwndVentana);
            ultimoControlAnunciado = nombreControl;
        }
    }
}

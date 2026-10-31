// [CAP.10] interfaz_editor.cpp
#include "interfaz_editor.h"
#include "../../libs/imgui/imgui.h"
#include "../../libs/imgui/backends/imgui_impl_win32.h"
#include "../../libs/imgui/backends/imgui_impl_opengl3.h"
#include <cstdio>

const char* InterfazEditor::ultimoControlAnunciado = ""; // [CAP.10]

InterfazEditor::InterfazEditor(HWND hwnd) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();

    // [CAP.10] LA linea mas importante de este capitulo: activa la
    // [CAP.10] navegacion completa por teclado dentro de ImGui (Tab,
    // [CAP.10] flechas, Intro, Escape...), sin ella todos los controles
    // [CAP.10] serian alcanzables UNICAMENTE con el raton.
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark(); // [CAP.10] Tema oscuro: buen contraste por defecto

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplOpenGL3_Init("#version 130");

    printf("[InterfazEditor] Dear ImGui inicializado con navegacion por teclado activa.\n");
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

void InterfazEditor::anunciarSiCambioFoco(const char* nombreControl, Registro& registro) {
    // [CAP.10] ImGui::IsItemFocused() indica si el ULTIMO control dibujado
    // [CAP.10] tiene el foco de navegacion en este fotograma.
    if (ImGui::IsItemFocused()) {
        if (ultimoControlAnunciado == nullptr || strcmp(ultimoControlAnunciado, nombreControl) != 0) {
            // [CAP.10] AVISO: esto es un SUSTITUTO TEMPORAL de un anuncio
            // [CAP.10] real por voz. El capitulo 11 reemplazara este printf
            // [CAP.10] por una llamada autentica a la Windows Speech API.
            printf("[Accesibilidad - PROVISIONAL] Foco: %s\n", nombreControl);
            registro.escribir(std::string("[Accesibilidad] Foco movido a: ") + nombreControl);
            ultimoControlAnunciado = nombreControl;
        }
    }
}

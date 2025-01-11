#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui-master/imgui-master/imgui.h"
#include "imgui-master/imgui-master/backends/imgui_impl_opengl3.h"
#include "imgui-master/imgui-master/backends/imgui_impl_glfw.h"
#include "main.cpp" // Include your existing code

void setupImGui(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void cleanupImGui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Amprenta de Carbon", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // Setup ImGui
    setupImGui(window);

    // Variables for GUI interaction
    int option = 0;
    char regim[20] = "";
    double result = 0.0;

    while (!glfwWindowShouldClose(window)) {
        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Create GUI
        ImGui::Begin("Calculul amprentei de carbon");

        ImGui::Text("Selectati optiunea:");
        if (ImGui::RadioButton("Individual", &option, 1)) {}
        if (ImGui::RadioButton("Casa de locuit", &option, 2)) {}
        if (ImGui::RadioButton("Regim alimentar", &option, 3)) {}

        if (option == 1) {
            static int respiratii = 16;
            static double kmTransport = 10.0;
            static int tipTransport = 1;

            ImGui::InputInt("Respiratii pe minut", &respiratii);
            ImGui::InputDouble("Kilometri parcursi zilnic", &kmTransport);
            ImGui::RadioButton("Masina personala", &tipTransport, 1);
            ImGui::RadioButton("Transport public", &tipTransport, 2);

            if (ImGui::Button("Calculeaza")) {
                TipTransport transport = (tipTransport == 1) ? MASINA_PERSONALA : TRANSPORT_COMUN;
                Persoana persoana(respiratii, kmTransport, transport);
                result = persoana.calculTotalAC();
            }
        } else if (option == 2) {
            static double spatiuUtil = 50.0;
            static double curent = 100.0, gaze = 30.0, apaCalda = 500.0, apaRece = 700.0;
            static int tipLocuinta = 2;

            ImGui::InputDouble("Spatiu util (mp)", &spatiuUtil);
            ImGui::InputDouble("Curent electric (kWh)", &curent);
            ImGui::InputDouble("Gaze naturale (m3)", &gaze);
            ImGui::InputDouble("Apa calda (litri)", &apaCalda);
            ImGui::InputDouble("Apa rece (litri)", &apaRece);
            ImGui::RadioButton("Garsoniera", &tipLocuinta, 1);
            ImGui::RadioButton("Apartament", &tipLocuinta, 2);
            ImGui::RadioButton("Casa", &tipLocuinta, 3);

            if (ImGui::Button("Calculeaza")) {
                TipLocuinta locuinta = (tipLocuinta == 1) ? GARSONIERA : (tipLocuinta == 2) ? APARTAMENT : CASA;
                Casa casa(locuinta, spatiuUtil, curent, gaze, apaCalda, apaRece);
                result = casa.calculAC();
            }
        } else if (option == 3) {
            static int dieta = 1;

            ImGui::RadioButton("Vegan", &dieta, 1);
            ImGui::RadioButton("Vegetarian", &dieta, 2);
            ImGui::RadioButton("Omnivor", &dieta, 3);

            if (ImGui::Button("Calculeaza")) {
                TipRegim regim = (dieta == 1) ? VEGAN : (dieta == 2) ? VEGETARIAN : OMNIVOR;
                RegimAlimentar aliment(regim);
                result = aliment.calculAC();
            }
        }

        ImGui::Text("Rezultat: %.2f kg CO2/an", result);

        ImGui::End();

        // Render ImGui
        ImGui::Render();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    cleanupImGui();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

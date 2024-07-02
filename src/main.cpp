#include "shurukaro.cpp"

void work(void* args){
  int* sum = (int*)args;
  printf("args seen %d\n", *sum);  
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

int main(int argc, char** argv){
    JobQueue* queue = (JobQueue*)malloc(sizeof(JobQueue));
    jobQueueInit(queue);
    printf("Created Q\n");
    platformInit();
    int vals[300];
    for (int i = 0; i < 100; i++){
        vals[i] = i;
        enqueue(queue, work, &vals[i]);
    }
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    bool show_demo_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(WINDOW, RENDERER);
    ImGui_ImplSDLRenderer2_Init(RENDERER);
    bool done = false;
    while(!done){
        SDL_Event event;
        //Poll events and give them to ImGuiKeyboard
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(WINDOW))
                done = true;
        }
        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        //show demo window
        if (show_demo_window){
            ImGui::ShowDemoWindow(&show_demo_window);
        }
        //Render
        ImGui::Render();
        SDL_RenderSetScale(RENDERER, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
        SDL_SetRenderDrawColor(RENDERER, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
        SDL_RenderClear(RENDERER);
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), RENDERER);
        SDL_RenderPresent(RENDERER);

    }
    //If user clicks exit
    
    // Cleanup
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    Mix_FreeMusic(testMusic);
    printf("Shurring down\n");
    jobQueueDestroy(queue);
    platformDestroy();
    printf("Ending Program\n");
    return 0;
}

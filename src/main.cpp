#include "shurukaro.cpp"

void work(void* args){
  int* sum = (int*)args;
  printf("args seen %d\n", *sum);  
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

SDL_Color dark_beige = { 169, 149, 123, 255 };

void renderQuad(SDL_Renderer* renderer, glm::vec2 vertices[4], SDL_Color color, glm::vec4 camera){
    //We know the max number of any vertices is going to be 4
    SDL_Vertex vertex_buffer[4];
    unsigned int no_triangles = 2;//no_vertices - 2
    int indices[6] = {0,1,2,0,2,3};// no_triangles * 3
   
    for(int i = 0; i < 4; i++){
        vertex_buffer[i].position = { vertices[i][0], vertices[i][1]};
        vertex_buffer[i].color = color;
    }
        
    SDL_RenderGeometry(renderer, NULL, vertex_buffer, 4, indices, 6); 
}

int main(int argc, char** argv){
    JobQueue* queue = (JobQueue*)malloc(sizeof(JobQueue));
    Component shapes(sizeof(Quadrilateral),300,1); 
    Quadrilateral q1 = Quadrilateral::Rectangle(glm::vec2(0,0), glm::vec2(10,20));
    shapes.append(0,NULL,&q1, sizeof(q1));
    ((Quadrilateral*)shapes.query(0))->debugInfo();
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
    int frame_start = 0;
    while(!done){
        frame_start = SDL_GetTicks();
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
        renderQuad(RENDERER, q1.vertices, dark_beige, glm::vec4(0,0,0,0));    
        SDL_RenderPresent(RENDERER);
        //Cap framerate 
       /* 
        if(SDL_GetTicks() - frame_start < (1000/60)){
            std::this_thread::sleep_for(std::chrono::milliseconds((SDL_GetTicks()-frame_start));
        }
       */

    }
    //If user clicks exit
    
    // Cleanup
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    shapes.Destroy();
    Mix_FreeMusic(testMusic);
    printf("Shurring down\n");
    jobQueueDestroy(queue);
    platformDestroy();
    printf("Ending Program\n");
    return 0;
}

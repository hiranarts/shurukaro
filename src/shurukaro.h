#include <SDL2/SDL.h>
#include <SDL2_Mixer/SDL_mixer.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_sdlrenderer2.h"
#include "pthread.h"
#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>
#include <stdlib.h>
#include "jobsystem.h"
#include "platform.h"
#include "engine.h"
#include "component.h"

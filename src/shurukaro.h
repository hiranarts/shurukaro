/* SDL Header files */
#include <SDL2/SDL.h>
#include <SDL2_Mixer/SDL_mixer.h>
/*imgui header files */
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
/* C/C++ header files */
#include <algorithm>
#include "pthread.h"
#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>
#include <stdlib.h>
#include <iostream>
/* GLM header files */
#include "glm/glm.hpp"
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"
/* phmap header files */
#include "parallel_hashmap/phmap.h"
/* ShuruKaro header files */
#include "component.h"
#include "jobsystem.h"
#include "platform.h"
#include "engine.h"
#include "physics.h"

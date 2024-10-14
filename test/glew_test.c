#define CALLBACK __stdcall
#include <stdio.h>
#include <SDL3/SDL.h>
#include <glew.h>      // Include GLEW
#include <gl.h>        // Core OpenGL header

// Callback function for rendering
void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen
    // Swap buffers is done using SDL3 instead of GLUT
}

// Main program to initialize GLEW and create an OpenGL window
int main(int argc, char** argv) {
    // Initialize SDL3
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize: %s\n", SDL_GetError());
        return -1;
    }

    // Create an OpenGL window
    SDL_Window* window = SDL_CreateWindow("GLEW Test",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800, 600,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (!window) {
        fprintf(stderr, "SDL could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // Create OpenGL context
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        fprintf(stderr, "SDL could not create OpenGL context: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Initialize GLEW
    GLenum glew_status = glewInit();
    if (glew_status != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Print the OpenGL version to verify GLEW is working
    printf("GLEW initialized successfully!\n");
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("GLEW Version: %s\n", glewGetString(GLEW_VERSION));

    // Main loop
    int running = 1;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
        // Call your display function
        display();
        SDL_GL_SwapWindow(window);  // Swap the OpenGL buffers
    }

    // Cleanup
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

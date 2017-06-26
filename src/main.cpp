// Using SDL, SDL OpenGL and standard IO
#include <iostream>
#include <cmath>
#include <chrono>

#include <windows.h>

#define SDL_MAIN_HANDLED

#define SPEED 0.3

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/GLU.h>

#include "Camera.h"
#include "World.h"
#include "WaterMesh.h"

/***************************************************************************/
/* Constants and functions declarations                                    */
/***************************************************************************/
// Screen dimension constants
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;

// Max number of forms : static allocation
const int MAX_FORMS_NUMBER = 10;

// Animation actualization delay (in ms) => 100 updates per second
const Uint32 ANIM_DELAY = 10;


// Starts up SDL, creates window, and initializes OpenGL
bool init(SDL_Window** window, SDL_GLContext* context);

// Initializes matrices and clear color
bool initGL();

// Frees media and shuts down SDL
void close(SDL_Window** window);


/***************************************************************************/
/* Functions implementations                                               */
/***************************************************************************/
bool init(SDL_Window** window, SDL_GLContext* context)
{
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        // Use OpenGL 2.1
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

        // Create window
        *window = SDL_CreateWindow( "Simulation d'onde", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
        if( *window == NULL )
        {
            std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            // Create context
            *context = SDL_GL_CreateContext(*window);
            if( *context == NULL )
            {
                std::cout << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                // Use Vsync
                if(SDL_GL_SetSwapInterval(1) < 0)
                {
                    std::cout << "Warning: Unable to set VSync! SDL Error: " << SDL_GetError() << std::endl;
                }

                // Initialize OpenGL
                if( !initGL() )
                {
                    std::cout << "Unable to initialize OpenGL!"  << std::endl;
                    success = false;
                }
            }
        }
    }

    return success;
}


bool initGL()
{
    bool success = true;
    GLenum error = GL_NO_ERROR;

    // Initialize Projection Matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set the viewport : use all the window to display the rendered scene
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Fix aspect ratio and depth clipping planes
    gluPerspective(40.0, (GLdouble)SCREEN_WIDTH/SCREEN_HEIGHT, 1.0, 100.0);


    // Initialize Modelview Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Initialize clear color : black with no transparency
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

    // Activate Z-Buffer


    // Check for error
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        std::cout << "Error initializing OpenGL!  " << gluErrorString( error ) << std::endl;
        success = false;
    }

    glEnable(GL_DEPTH_TEST);

    return success;
}

void close(SDL_Window** window)
{
    //Destroy window
    SDL_DestroyWindow(*window);
    *window = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}


/***************************************************************************/
/* MAIN Function                                                           */
/***************************************************************************/
int main(int argc, char* args[])
{
    // The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    // OpenGL context
    SDL_GLContext gContext;


    // Start up SDL and create window
    if( !init(&gWindow, &gContext))
    {
        std::cout << "Failed to initialize!" << std::endl;
    }
    else
    {
        // Hide cursor
        SDL_ShowCursor(SDL_DISABLE);

        // Main loop flag
        bool quit = false;
        Uint32 current_time, previous_time, elapsed_time;

        // Event handler
        SDL_Event event;

        // Camera position
		Vector3 origin(10, 10, 10);
        Camera camera(origin);
        camera.rotateH(-45);
        camera.rotateV(35);

        double phi = camera.getPhi();
        double theta = camera.getTheta();

		World world;

        WaterMesh mesh(Vector3(0, 0, 0), 10, 100);

		double a = 0.5;
		double f = 1;
		double c = 1.1;
		std::vector<int> numbers = { };

		mesh.addWave(new Wave(a, f, c, Vector2(0, 0), 0, numbers));
		mesh.addWave(new Wave(a, f, c, Vector2(1, 1), 0, numbers));

		// First reflexion
		//mesh.addWave(new Wave(a, f, c, Vector2(10, 0), 0, numbers));
		//mesh.addWave(new Wave(a, f, c, Vector2(0, 10), 0, numbers));
		//mesh.addWave(new Wave(a, f, c, Vector2(-10, 0), 0, numbers));
		//mesh.addWave(new Wave(a, f, c, Vector2(0, -10), 0, numbers));

		//// Second reflexion
		//mesh.addWave(new Wave(a, f, c, Vector2(10, 10), 0, numbers));
		//mesh.addWave(new Wave(a, f, c, Vector2(-10, 10), 0, numbers));
		//mesh.addWave(new Wave(a, f, c, Vector2(10, -10), 0, numbers));
		//mesh.addWave(new Wave(a, f, c, Vector2(-10, -10), 0, numbers));

        world.add(&mesh);

        // Get first "current time"
        previous_time = SDL_GetTicks();

        // Center the cursor
        SDL_WarpMouseInWindow(gWindow, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
		int mouse_dx = 0, mouse_dy = 0;

		// FPS
		int fps = 0;
		double fpsElapsedTime = 0;
		double fpsPreviousTime = 0;

		double updateMilliseconds = 0;
		double renderMilliseconds = 0;

        Uint8 const *statEv = SDL_GetKeyboardState(NULL);
        while(!quit)
        {
            // Handle events on queue
            while(SDL_PollEvent(&event) != 0)
            {
                switch(event.type)
                {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEMOTION:
                    SDL_GetMouseState( &mouse_dx, &mouse_dy );
                    mouse_dx -= SCREEN_WIDTH / 2;
                    mouse_dy -= SCREEN_HEIGHT / 2;
                    SDL_WarpMouseInWindow(gWindow, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
                    camera.rotateH((double)mouse_dx / 3.0);
                    camera.rotateV((double)mouse_dy / 3.0);
                    break;
                default:
                    break;
                }
            }
			
			std::chrono::time_point<std::chrono::steady_clock> startUpdateTime = std::chrono::high_resolution_clock::now();

            // Update the scene
            current_time = SDL_GetTicks(); // get the elapsed time from SDL initialization (ms)
            elapsed_time = current_time - previous_time;
            if (elapsed_time > ANIM_DELAY)
            {
                previous_time = current_time;
                world.update(1e-3 * elapsed_time); // International system units : seconds
            }

			std::chrono::time_point<std::chrono::steady_clock> endUpdateTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> updateDuration = endUpdateTime - startUpdateTime;
			updateMilliseconds += updateDuration.count();

			double speed = SPEED;// *(double)elapsed_time * 1e-3;

			if (statEv[SDL_SCANCODE_ESCAPE])
			{
				quit = true;
			}
			if (statEv[SDL_SCANCODE_A])
			{
				camera.move(0, -speed, 0);
			}
			if (statEv[SDL_SCANCODE_D])
			{
				camera.move(0, speed, 0);
			}
			if (statEv[SDL_SCANCODE_W])
			{
				camera.move(-speed, 0, 0);
			}
			if (statEv[SDL_SCANCODE_S])
			{
				camera.move(speed, 0, 0);
			}
			if (statEv[SDL_SCANCODE_SPACE])
			{
				camera.move(0, 0, speed);
			}
			if (statEv[SDL_SCANCODE_LSHIFT])
			{
				camera.move(0, 0, -speed);
			}
			if (statEv[SDL_SCANCODE_RETURN])
			{
				std::cout << "EVENT" << std::endl;
			}
			if (statEv[SDL_SCANCODE_R])
			{
				camera.setPhi(phi);
				camera.setTheta(theta);
				camera.setPosition(origin);
			}

			std::chrono::time_point<std::chrono::steady_clock> startRenderTime = std::chrono::high_resolution_clock::now();

            // Render the scene
            world.render(camera);

			std::chrono::time_point<std::chrono::steady_clock> endRenderTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> renderDuration = endRenderTime - startRenderTime;
			renderMilliseconds += renderDuration.count();

            // Update window screen
            SDL_GL_SwapWindow(gWindow);

			// FPS
			fps++;
			fpsElapsedTime = current_time - fpsPreviousTime;
			if (fpsElapsedTime > 1000)
			{
				fpsPreviousTime = current_time;
				std::cout << "FPS: " << fps
					<< " (update: " << updateMilliseconds << " ms" 
					<< ", render: " << renderMilliseconds << " ms)"
					<< std::endl;
				fps = 0;
				updateMilliseconds = 0;
				renderMilliseconds = 0;
			}
        }
    }

    // Free resources and close SDL
    close(&gWindow);

    return 0;
}

#define M_PI		3.14159265358979323846
#define M_PI_2		1.57079632679489661923

// Using SDL, SDL OpenGL and standard IO
#include <iostream>
#include <cmath>
#include <chrono>

#include <windows.h>

#define SDL_MAIN_HANDLED

#define SPEED 1.2

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/GLU.h>

#include "ttf.h"

#include "Camera.h"
#include "World.h"
#include "WaterMesh.h"
#include "Slider.h"
#include "Button.h"

#ifdef _MinGW
    #define TIME_POINT std::chrono::_V2::system_clock::time_point
#else
    #define TIME_POINT std::chrono::time_point<std::chrono::steady_clock>
#endif

#include "Slider.h"

/***************************************************************************/
/* Constants and functions declarations                                    */
/***************************************************************************/
// Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_X = 64;
const int SCREEN_Y = 64;

const int HUD_WIDTH = 400;
const int HUD_HEIGHT = 600;
const int HUD_X = SCREEN_X + SCREEN_WIDTH;
const int HUD_Y = SCREEN_Y;

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
        if(TTF_Init() == -1)
        {
            std::cerr << "ERROR Init SDL_TTF : " << TTF_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
        IMG_Init(IMG_INIT_PNG);
        // Use OpenGL 2.1
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);

        // Create window
        *window = SDL_CreateWindow( "Simulation d'onde", SCREEN_X, SCREEN_Y, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
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

    IMG_Quit();

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
    SDL_Window* hud = NULL;

    // OpenGL context
    SDL_GLContext gContext;


    // Start up SDL and create window
    if( !init(&gWindow, &gContext))
    {
        std::cout << "Failed to initialize!" << std::endl;
    }
    else
    {
        hud = SDL_CreateWindow(
            "HUD",                  // window title
            HUD_X,           // initial x position
            HUD_Y,           // initial y position
            HUD_WIDTH,                               // width, in pixels
            HUD_HEIGHT,                               // height, in pixels
            SDL_WINDOW_SHOWN);

        SDL_Renderer* hudRenderer  = SDL_CreateRenderer( hud, -1, SDL_RENDERER_ACCELERATED );
        SDL_SetRenderDrawColor( hudRenderer , 0, 0, 0, 0 );

        TTF_Font *font = loadFont("rc/font.TTF", TEXT_HEIGHT);
        SDL_Color color = {255,255,255, 255};

        // Main loop flag
        bool quit = false;
        Uint32 current_time, previous_time, elapsed_time;

        // Event handler
        SDL_Event event;

        // Camera position
		Vector3 origin(5, 5, 5);
        Camera camera(origin);
        camera.rotateH(-45);
        camera.rotateV(35);

        double phi = camera.getPhi();
        double theta = camera.getTheta();

		double a = 0.5;
		double coefAttAmplitude = 0.6;
		double f = 1.3;
		double c = 0.72;

		World world;

        WaterMesh mesh(Vector3(0, 0, 0), 5, 100);
		//mesh.addWall(new Wall(Vector2(-2, 2.5), Vector2(0, -2.5), -0.3, 0.3));
		//mesh.addWall(new Wall(Vector2(2, 2.5), Vector2(0, -2.5), -0.3, 0.3));

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

		double updateMeanMs = 0;
		double renderMeanMs = 0;
		double splitsMean = 0;

		bool waveAdded = false;

		// Drag'n'drop
		bool drag = false;
		bool drag_hud = false;
		int x_beg = 0;
		int y_beg = 0;

		// Slider
		Slider amplitudeSlider("Amplitude", 0.1, 2.0, a, 50, 70);
		Slider frequencySlider("Fréquence", 0.1, 2.0, f, 50, 190);

		//LOGO
		SDL_Texture *logo = NULL;
		SDL_Surface *srf_logo = IMG_Load("rc/logo_onde2.png");
		logo = SDL_CreateTextureFromSurface(hudRenderer, srf_logo);
		SDL_Rect logo_pos = {0, 190 + CUR_HEIGHT, 400, 400};

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
                case SDL_MOUSEBUTTONDOWN: // On commence le drag'n'drop
                    if(SDL_GetMouseFocus() == gWindow)
                    {
                        SDL_GetMouseState( &mouse_dx, &mouse_dy );
                        // CHECK IF CLICK IS IN OPENGL PART OF WINDOW
                        drag = true;
                        x_beg = mouse_dx;
                        y_beg = mouse_dy;
                    }
                    else if(SDL_GetMouseFocus() == hud)
                    {
                        SDL_GetMouseState( &mouse_dx, &mouse_dy );
                        drag_hud = true;
                    }
                    break;
                case SDL_MOUSEBUTTONUP: // On relache le drag'n'drop
                    drag = false;
                    drag_hud = false;
                    break;
                case SDL_MOUSEMOTION:
                    if(drag && SDL_GetMouseFocus() == gWindow)
                    {
                        SDL_GetMouseState( &mouse_dx, &mouse_dy );
//                        SDL_WarpMouseInWindow(gWindow, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
                        camera.rotateH((double)(mouse_dx - x_beg) / SPEED/2);
                        camera.rotateV((double)(mouse_dy - y_beg) / SPEED/2);
                        x_beg = mouse_dx;
                        y_beg = mouse_dy;
                    }
                    else if(drag_hud && SDL_GetMouseFocus() == hud)
                    {
                        SDL_GetMouseState( &mouse_dx, &mouse_dy );
						amplitudeSlider.move(mouse_dx, mouse_dy);
                        frequencySlider.move(mouse_dx, mouse_dy);

						a = amplitudeSlider.getValue();
						f = frequencySlider.getValue();
                    }
                    break;
                default:
                    break;
                }
            }

			TIME_POINT startUpdateTime = std::chrono::high_resolution_clock::now();

            // Update the scene
            current_time = SDL_GetTicks(); // get the elapsed time from SDL initialization (ms)
            elapsed_time = current_time - previous_time;
            if (elapsed_time > ANIM_DELAY)
            {
                previous_time = current_time;
                world.update(1e-3 * elapsed_time); // International system units : seconds
            }

			TIME_POINT endUpdateTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> updateDuration = endUpdateTime - startUpdateTime;
			updateMeanMs += updateDuration.count();

			if (statEv[SDL_SCANCODE_ESCAPE])
			{
				quit = true;
			}
			if (statEv[SDL_SCANCODE_A])
			{
				camera.move(0, -1, 0);
			}
			if (statEv[SDL_SCANCODE_D])
			{
				camera.move(0, 1, 0);
			}
			if (statEv[SDL_SCANCODE_W])
			{
				camera.move(-1, 0, 0);
			}
			if (statEv[SDL_SCANCODE_S])
			{
				camera.move(1, 0, 0);
			}
			if (statEv[SDL_SCANCODE_SPACE])
			{
				camera.move(0, 0, 1);
			}
			if (statEv[SDL_SCANCODE_LSHIFT])
			{
				camera.move(0, 0, -1);
			}

			if (statEv[SDL_SCANCODE_RETURN])
			{
				if (!waveAdded)
				{
					waveAdded = true;
					mesh.addWave(new Wave(a, coefAttAmplitude, f, c, Vector2(0, 0)));
					mesh.addWave(new Wave(a, coefAttAmplitude, f, c, Vector2(0.5, 1)));
				}
			}
			if (!statEv[SDL_SCANCODE_RETURN])
			{
				waveAdded = false;
			}

			if (statEv[SDL_SCANCODE_R])
			{
				camera.setPhi(phi);
				camera.setTheta(theta);
				camera.setPosition(origin);
			}

			TIME_POINT startRenderTime = std::chrono::high_resolution_clock::now();

            // Render the scene
            world.render(camera);

			TIME_POINT endRenderTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> renderDuration = endRenderTime - startRenderTime;
			renderMeanMs += renderDuration.count();

            // Update window screen
            SDL_GL_SwapWindow(gWindow);

			splitsMean += mesh.getSplits();

			// FPS
			fps++;
			fpsElapsedTime = current_time - fpsPreviousTime;
			if (fpsElapsedTime > 1000)
			{
				fpsPreviousTime = current_time;
				std::cout << "FPS: " << fps << std::endl
					<< "\tupdate: " << updateMeanMs / (double)fps << " ms" << std::endl
					<< "\trender: " << renderMeanMs / (double)fps << " ms" << std::endl
					<< "\tsplits: " << splitsMean / (double) fps << std::endl
					<< "\twaves: " << mesh.countWaves() << std::endl;
				fps = 0;
				updateMeanMs = 0;
				renderMeanMs = 0;
				splitsMean = 0;
			}

			double time = updateDuration.count() + renderDuration.count();
			if (time > 33)
				mesh.setSplits((int)(mesh.getSplits() * 0.9));
			else if (time < 30 && mesh.getSplits() < 400)
				mesh.setSplits((int)(mesh.getSplits() * 1.1));

            // HUD WINDOW
            SDL_SetRenderDrawColor(hudRenderer, 0,0,0,255);
            SDL_RenderClear( hudRenderer );

//            SDL_Rect bar = {50,50,400-100,4};
//            SDL_Rect cursor = {400/2 - 20/2, 40 - 10, 20, 40};

            SDL_GetMouseState(&mouse_dx, &mouse_dy);
			amplitudeSlider.draw(hudRenderer, font, color);
            frequencySlider.draw(hudRenderer, font, color);
            SDL_RenderCopy(hudRenderer, logo, NULL, &logo_pos);
            SDL_RenderPresent( hudRenderer );
        }
        TTF_CloseFont(font);
        SDL_DestroyTexture(logo);
        SDL_FreeSurface(srf_logo);
    }

    // Free resources and close SDL
    close(&gWindow);
    SDL_DestroyWindow(hud);

    TTF_Quit();

    return 0;
}

// Using SDL, SDL OpenGL and standard IO
#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/GLU.h>

#include "Form.h"

/***************************************************************************/
/* Constants and functions declarations                                    */
/***************************************************************************/
// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Max number of forms : static allocation
const int MAX_FORMS_NUMBER = 10;

// Animation actualization delay (in ms) => 100 updates per second
const Uint32 ANIM_DELAY = 10;


// Starts up SDL, creates window, and initializes OpenGL
bool init(SDL_Window** window, SDL_GLContext* context);

// Initializes matrices and clear color
bool initGL();

// Updating forms for animation
void update(Form* formlist[MAX_FORMS_NUMBER], double delta_t);

// Renders scene to the screen
const void render(Form* formlist[MAX_FORMS_NUMBER], const Point &cam_pos);

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
        *window = SDL_CreateWindow( "TP intro OpenGL / SDL 2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
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

void update(Form* formlist[MAX_FORMS_NUMBER], double delta_t)
{
    // Update the list of forms
    unsigned short i = 0;
    while(formlist[i] != NULL)
    {
        formlist[i]->update(delta_t);
        i++;
    }
}

const void render(Form* formlist[MAX_FORMS_NUMBER], const Point &cam_pos)
{
    // Clear color buffer and Z-Buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Initialize Modelview Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set the camera position and parameters
    gluLookAt(cam_pos.x,cam_pos.y,cam_pos.z, 0.0,0.0,0.0, 0.0,0.0,1.0);

    // X, Y and Z axis
    glPushMatrix(); // Preserve the camera viewing point for further forms
    // Render the coordinates system
    glBegin(GL_LINES);
    {
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3i(0, 0, 0);
        glVertex3i(1, 0, 0);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3i(0, 0, 0);
        glVertex3i(0, 1, 0);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3i(0, 0, 0);
        glVertex3i(0, 0, 1);
    }
    glEnd();
    glPopMatrix(); // Restore the camera viewing point for next object

    // Render the list of forms
    unsigned short i = 0;
    while(formlist[i] != NULL)
    {
        formlist[i]->render();
        i++;
    }
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
        // Main loop flag
        bool quit = false;
        Uint32 current_time, previous_time, elapsed_time;

        int x = 0, y = 0;

        // Event handler
        SDL_Event event;

        // Camera position
        Point camera_position(5.0, 5.0, 5.0);

        // Get first "current time"
        previous_time = SDL_GetTicks();
        // While application is running

        // Center the cursor
        SDL_WarpMouseInWindow(gWindow, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

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
                    SDL_GetMouseState( &x, &y );
                    x -= SCREEN_WIDTH / 2;
                    y -= SCREEN_HEIGHT / 2;
                    y *= -1;
                    std::cout << "MOVE (" << x << "," << y << ")" << std::endl;
                    SDL_WarpMouseInWindow(gWindow, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
                    break;
                default:
                    break;
                }
            }

            if(statEv[SDL_SCANCODE_ESCAPE])
            {
                quit = true;
            }
            if(statEv[SDL_SCANCODE_LEFT])
            {
                std::cout << "LEFT" << std::endl;
            }
            if(statEv[SDL_SCANCODE_RIGHT])
            {
                std::cout << "RIGHT" << std::endl;
            }
            if(statEv[SDL_SCANCODE_UP])
            {
                std::cout << "UP" << std::endl;
            }
            if(statEv[SDL_SCANCODE_DOWN])
            {
                std::cout << "DOWN" << std::endl;
            }
            if(statEv[SDL_SCANCODE_SPACE])
            {
                std::cout << "SPACE" << std::endl;
            }
            if(statEv[SDL_SCANCODE_LSHIFT])
            {
                std::cout << "LSHIFT" << std::endl;
            }
            if(statEv[SDL_SCANCODE_RETURN])
            {
                std::cout << "EVENT" << std::endl;
            }

            // Update the scene
            current_time = SDL_GetTicks(); // get the elapsed time from SDL initialization (ms)
            elapsed_time = current_time - previous_time;
            if (elapsed_time > ANIM_DELAY)
            {
                previous_time = current_time;
                //update(forms_list, 1e-3 * elapsed_time); // International system units : seconds
            }

            // Render the scene
            //render(forms_list, camera_position);

            // Update window screen
            SDL_GL_SwapWindow(gWindow);
        }
    }

    // Free resources and close SDL
    close(&gWindow);

    return 0;
}

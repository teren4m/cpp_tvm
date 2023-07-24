#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <SDL3/SDL.h>

using namespace cv;
using namespace std::chrono;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The surface contained by the window
SDL_Surface *gScreenSurface = NULL;

// The image we will load and show on the screen
SDL_Surface *gHelloWorld = NULL;

int main(int argc, char **argv)
{
    VideoCapture camera(0);
    if (!camera.isOpened())
    {
        std::cerr << "ERROR: Could not open camera" << std::endl;
        return 1;
    }

    // Start up SDL and create window
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        // Load media
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            // Apply the image
            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

            // Update the surface
            SDL_UpdateWindowSurface(gWindow);

            // Hack to get window to stay up
            SDL_Event e;
            bool quit = false;
            while (quit == false)
            {
                while (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_EVENT_QUIT)
                        quit = true;
                }
            }
        }
    }

    // Free resources and close SDL
    close();

    return 0;

    // cv::namedWindow("Webcam", cv::WINDOW_AUTOSIZE);

    // // array to hold image
    // cv::Mat frame;

    // // display the frame until you press a keygit adds
    // while (1)
    // {
    //     milliseconds ms = duration_cast<milliseconds>(
    //     system_clock::now().time_since_epoch());
    //     // capture the next frame from the webcam
    //     camera >> frame;
    //     // show the image on the window
    //     cv::imshow(std::to_string(ms.count()), frame);
    //     // wait (10ms) for esc key to be pressed to stop
    //     if (cv::waitKey(10) == 27)
    //         break;
    // }
    return 0;
}

bool init()
{
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_VULKAN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}

bool loadMedia()
{
    // Loading success flag
    bool success = true;

    // Load splash image
    gHelloWorld = SDL_LoadBMP("hello_world.bmp");
    if (gHelloWorld == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError());
        success = false;
    }

    return success;
}

void close()
{
    // Deallocate surface
    SDL_DestroySurface(gHelloWorld);
    gHelloWorld = NULL;

    // Destroy window
     SDL_DestroyWindow( gWindow );
     gWindow = NULL;

    // Quit SDL subsystems
     SDL_Quit();
}
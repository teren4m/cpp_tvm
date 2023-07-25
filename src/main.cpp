#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <SDL3/SDL.h>
#include <SDL3/SDL_syswm.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

using namespace cv;
using namespace std::chrono;

SDL_Window *window = NULL;
SDL_SysWMinfo wm_info;
const int WIDTH = 640;
const int HEIGHT = 480;

int main(int argc, char **argv)
{
    VideoCapture camera(0);
    if (!camera.isOpened())
    {
        std::cerr << "ERROR: Could not open camera" << std::endl;
        return 1;
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n",
               SDL_GetError());
    }
    else
    {
        // Create a window
        window = SDL_CreateWindow("BGFX Tutorial",
                                  WIDTH, HEIGHT,
                                  SDL_WINDOW_VULKAN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n",
                   SDL_GetError());
        }
    }

    SDL_version version;

    SDL_VERSION(&version);
    Uint32 num_version = SDL_VERSIONNUM(version.major, version.minor, version.patch);

    SDL_Log("SDL version %u.%u.%u ...\n",
            version.major, version.minor, version.patch);
    SDL_Log("SDL num version %d ...\n", num_version);

    if (!SDL_GetWindowWMInfo(window, &wm_info, num_version))
    {
        return 1;
    }

    bool quit = false;
    SDL_Event currentEvent;
    while (!quit)
    {
        while (SDL_PollEvent(&currentEvent) != 0)
        {
            if (currentEvent.type == SDL_EVENT_QUIT)
            {
                quit = true;
            }
        }
    }

    // Free up window
    SDL_DestroyWindow(window);
    // Shutdown SDL
    SDL_Quit();

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
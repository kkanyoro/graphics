#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


// Function to simulate Protanopia (Red-Weakness color blindness)
void applyProtanopia(unsigned char* img, int width, int height, int channels) {
    size_t imgSize = (size_t)width * height * channels;
    unsigned char* p; // Pointer to iterate through the image data

    for (p = img; p != img + imgSize; p += channels) {
        // 1. Extract RGB (Cast to float for accurate matrix multiplication)
        float r = (float)p[0];
        float g = (float)p[1];
        float b = (float)p[2];

        // 2. Protanopia Simulation Matrix (Simulates Red-Weakness)
        // Red is largely replaced by a blend of Green and Blue
        float new_r = 0.567f * r + 0.433f * g + 0.0f * b;
        float new_g = 0.558f * r + 0.442f * g + 0.0f * b;
        float new_b = 0.0f * r + 0.242f * g + 0.758f * b;

        // 3. Clamp values to 255 (to prevent color overflow)
        if (new_r > 255) new_r = 255;
        if (new_g > 255) new_g = 255;
        if (new_b > 255) new_b = 255;

        // 4. Assign the new, simulated values back to the pixel
        p[0] = (unsigned char)new_r;
        p[1] = (unsigned char)new_g;
        p[2] = (unsigned char)new_b;
        // p[3] (Alpha channel) is left untouched
    }
}

int main() {
    int width, height, channels;
    const char* inputFilename = "container2.jpeg"; // INPUT FILE
    const char* outputFilename = "output_protanopia.jpg"; // OUTPUT FILE

    // Load image data from the file
    unsigned char* img = stbi_load(inputFilename, &width, &height, &channels, 0);

    if (!img) {
        printf("Error: Could not load image file '%s'.\n", inputFilename);
        return -1;
    }
    printf("Image Loaded: %dx%d pixels, %d channels.\n", width, height, channels);

    // Apply the Protanopia filter
    applyProtanopia(img, width, height, channels);

    // Write the modified image to a new file (quality 100)
    stbi_write_jpg(outputFilename, width, height, channels, img, 100);
    printf("Protanopia simulation saved to: %s\n", outputFilename);

    // Clean up memory
    stbi_image_free(img);

    // Open the file automatically
    system("start output_protanopia.jpg");

    return 0;
}
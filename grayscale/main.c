#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Function to convert a single pixel to Grayscale
void applyGrayscale(unsigned char* img, int width, int height, int channels) {
    size_t imgSize = (size_t)width * height * channels;
    unsigned char* p;

    // Iterate through every pixel
    for (p = img; p != img + imgSize; p += channels) {
        // Extract RGB
        float r = (float)p[0];
        float g = (float)p[1];
        float b = (float)p[2];

        // Calculate Luminosity
        unsigned char gray = (unsigned char)(0.299f * r + 0.587f * g + 0.114f * b);

        // Assign the gray value back to R, G, and B
        p[0] = gray;
        p[1] = gray;
        p[2] = gray;
    }
}

// Function to apply a Sepia Filter
void applySepia(unsigned char* img, int width, int height, int channels) {
    size_t imgSize = (size_t)width * height * channels;
    unsigned char* p;

    for (p = img; p != img + imgSize; p += channels) {
        float r = (float)p[0];
        float g = (float)p[1];
        float b = (float)p[2];

        // Standard Sepia Matrix
        float tr = 0.393f * r + 0.769f * g + 0.189f * b;
        float tg = 0.349f * r + 0.686f * g + 0.168f * b;
        float tb = 0.272f * r + 0.534f * g + 0.131f * b;

        // Clamp values to 255
        if (tr > 255) tr = 255;
        if (tg > 255) tg = 255;
        if (tb > 255) tb = 255;

        p[0] = (unsigned char)tr;
        p[1] = (unsigned char)tg;
        p[2] = (unsigned char)tb;
    }
}

int main() {
    int width, height, channels;
    int w2, h2, c2;
    const char* inputFilename = "container2.jpeg";

    // Load Original Image
    unsigned char* img1 = stbi_load(inputFilename, &width, &height, &channels, 0);
    // Reload a second copy for the filter
    unsigned char* img2 = stbi_load(inputFilename, &w2, &h2, &c2, 0);

    if (!img1 || !img2) {
        printf("Error loading image. Is the filename correct?\n");
        return -1;
    }
    printf("Image Loaded: %dx%d pixels\n", width, height);

    // Apply Grayscale to Image 1
    applyGrayscale(img1, width, height, channels);
    stbi_write_jpg("output_grayscale.jpg", width, height, channels, img1, 100);
    printf("Saved: output_grayscale.jpg\n");

    // Apply Sepia to Image 2
    applySepia(img2, width, height, channels);
    stbi_write_jpg("output_sepia.jpg", width, height, channels, img2, 100);
    printf("Saved: output_sepia.jpg\n");

    // Clean up memory
    stbi_image_free(img1);
    stbi_image_free(img2);

    // Open the files automatically
    system("start output_grayscale.jpg");
    system("start output_sepia.jpg");

    return 0;
}
#include <gtest/gtest.h>
#include "image.h"
#include "turnimage.h"
#include "kernel.h"

TEST(ImageTest, ConstructorTest) {
    Image img(100, 100);
    EXPECT_EQ(img.GetWidth(), 100);
    EXPECT_EQ(img.GetHeight(), 100);
}

TEST(ImageTest, SetAndGetColorTest) {
    Image img(100, 100);
    Color color(1.0f, 0.5f, 0.0f);
    img.SetColor(color, 50, 50);
    Color retrievedColor = img.GetColor(50, 50);
    EXPECT_FLOAT_EQ(retrievedColor.r, 1.0f);
    EXPECT_FLOAT_EQ(retrievedColor.g, 0.5f);
    EXPECT_FLOAT_EQ(retrievedColor.b, 0.0f);
}

TEST(ImageTest, GaussianBlurTest) {
    Image img(100, 100);
    for (int y = 0; y < 100; ++y) {
        for (int x = 0; x < 100; ++x) {
            img.SetColor(Color(1.0f, 1.0f, 1.0f), x, y);
        }
    }
    img.ApplyGaussianBlur(3, 2.0f);
    for (int y = 0; y < 100; ++y) {
        for (int x = 0; x < 100; ++x) {
            Color color = img.GetColor(x, y);
            EXPECT_GE(color.r, 0.0f);
            EXPECT_LE(color.r, 1.0f);
        }
    }
}

TEST(ImageTest, RightTurnTest) {
    Image original(0, 0);
    original.Read("input.bmp");
    
    int width = original.GetWidth();
    int height = original.GetHeight();
    
    Turn_Image::RightTurn("input.bmp");
    
    Image rotated(0, 0);
    rotated.Read("Right_rotated_image.bmp");
    
    EXPECT_EQ(rotated.GetWidth(), height);
    EXPECT_EQ(rotated.GetHeight(), width);
    
    float originalSum = 0.0f;
    float rotatedSum = 0.0f;
    
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Color c = original.GetColor(x, y);
            originalSum += c.r + c.g + c.b;
        }
    }
    
    for (int y = 0; y < width; ++y) {
        for (int x = 0; x < height; ++x) {
            Color c = rotated.GetColor(x, y);
            rotatedSum += c.r + c.g + c.b;
        }
    }
    
    float tolerance = originalSum * 0.001f;
    EXPECT_NEAR(originalSum, rotatedSum, tolerance);
}

TEST(ImageTest, LeftTurnTest) {
    Image original(0, 0);
    original.Read("input.bmp");
    
    int width = original.GetWidth();
    int height = original.GetHeight();
    
    Turn_Image::LeftTurn("input.bmp");
    
    Image rotated(0, 0);
    rotated.Read("Left_rotated_image.bmp");
    
    EXPECT_EQ(rotated.GetWidth(), height);
    EXPECT_EQ(rotated.GetHeight(), width);
    
    float originalSum = 0.0f;
    float rotatedSum = 0.0f;
    
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Color c = original.GetColor(x, y);
            originalSum += c.r + c.g + c.b;
        }
    }
    
    for (int y = 0; y < width; ++y) {
        for (int x = 0; x < height; ++x) {
            Color c = rotated.GetColor(x, y);
            rotatedSum += c.r + c.g + c.b;
        }
    }
    
    float tolerance = originalSum * 0.001f;
    EXPECT_NEAR(originalSum, rotatedSum, tolerance);
}

TEST(ImageTest, GaussianKernelTest) {
    std::vector<std::vector<float>> kernel = Gauss_Kernel::GenerateGaussianKernel(3, 2.0f);
    
    EXPECT_EQ(kernel.size(), 7); 
    EXPECT_EQ(kernel[0].size(), 7);
    
    float sum = 0.0f;
    for (const auto& row : kernel) {
        for (float val : row) {
            sum += val;
        }
    }
    EXPECT_NEAR(sum, 1.0f, 0.001f);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 
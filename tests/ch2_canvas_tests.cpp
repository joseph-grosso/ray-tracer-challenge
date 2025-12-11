#include <cstdio>
#include <fstream>
#include <string>

#include "canvas.hpp"
#include "gtest/gtest.h"
#include "tuple.hpp"

// Scenario: Colors are (red, green, blue) tuples
// p16
TEST(TestColors, ColorsAreTuples) {
  Color c(-0.5, 0.4, 1.7);
  EXPECT_TRUE(equalByEpsilon(c.red, -0.5f));
  EXPECT_TRUE(equalByEpsilon(c.green, 0.4f));
  EXPECT_TRUE(equalByEpsilon(c.blue, 1.7f));
}

// Scenario: Adding colors
// p17
TEST(TestColors, AddingColors) {
  Color c1(0.9, 0.6, 0.75), c2(0.7, 0.1, 0.25);
  Color expected(1.6, 0.7, 1.0);
  EXPECT_TRUE(expected == c1 + c2);
}

// Scenario: Subtracting colors
// p17
TEST(TestColors, SubtractingColors) {
  Color c3(0.9, 0.6, 0.75), c4(0.7, 0.1, 0.25);
  Color expected_2(0.2, 0.5, 0.5);
  EXPECT_TRUE(expected_2 == c3 - c4);
}

// Scenario: Multiplying a color by a scalar
// p17
TEST(TestColors, MultiplyingColorsByScalar) {
  Color c5(0.2, 0.3, 0.4);
  Color expected_3(0.4, 0.6, 0.8);
  EXPECT_TRUE(expected_3 == c5 * 2);
  EXPECT_TRUE(expected_3 == 2 * c5);
}

// Scenario: Multiplying two colors together
// p17
TEST(TestColors, MultiplyingColorsTogether) {
  Color c6(1, 0.2, 0.4), c7(0.9, 1, 0.1);
  EXPECT_TRUE(Color(0.9, 0.2, 0.04) == c6 * c7);
}

// Scenario: test getting heights and widths
// p19
TEST(TestCanvas, GetHeightsAndWidths) {
  Canvas canvas(10, 20);
  EXPECT_TRUE(canvas.get_width() == 10);
  EXPECT_TRUE(canvas.get_height() == 20);
}

// scenario: Writing pixels to canvas
// p19
TEST(TestCanvas, WritePixelsToCanvas) {
  Canvas canvas_1(5, 10);
  Color red(1, 0, 0), black(0, 0, 0);
  canvas_1.write_pixel(red, 3, 9);
  EXPECT_TRUE(canvas_1.pixel_at(3, 8) == black);
  EXPECT_TRUE(canvas_1.pixel_at(3, 9) == red);
}

// Scenario: Construct larger ppm file
// p21
TEST(TestCanvas, ConstructPPMFileString) {
  Canvas canvas_3(5, 3);
  canvas_3.write_pixel(Color(1.5, 0, 0), 0, 0);
  canvas_3.write_pixel(Color(0, 0.5, 0), 2, 1);
  canvas_3.write_pixel(Color(-0.5, 0, 1), 4, 2);
  std::string expected_5 =
      "P3\n5 3\n255\n255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 128 0 0 0 "
      "0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n";
  EXPECT_TRUE(expected_5 == canvas_3.canvas_to_ppm());
}

// Scenario: Splitting long lines in PPM files// p22
TEST(TestCanvas, SplittingLinesPPMFileString) {
  Canvas canvas_4(10, 2);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 2; j++) {
      canvas_4.write_pixel(Color(1, 0.8, 0.6), i, j);
    }
  }
  std::string expected_6 =
      "P3\n10 2\n255\n255 204 153 255 204 153 255 204 153 255 204 153 255 204 "
      "153 255 204\n153 255 204 153 255 204 153 255 204 153 255 204 153\n255 "
      "204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n153 "
      "255 204 153 255 204 153 255 204 153 255 204 153\n";
  EXPECT_TRUE(canvas_4.canvas_to_ppm() == expected_6);
}

// Scenario: PPM output always ends with newline
// p22
TEST(TestCanvas, EndPPMStringWithNewline) {
  Canvas canvas_5(5, 3);
  std::string ppm = canvas_5.canvas_to_ppm();
  EXPECT_TRUE(ppm.back() == '\n');
}

// PNG Export Tests
// Test that PNG file is created successfully
TEST(TestCanvasPNG, WritePNGFileCreated) {
  Canvas canvas(10, 10);
  // Fill canvas with a simple color
  Color red(1, 0, 0);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      canvas.write_pixel(red, i, j);
    }
  }

  // Write to PNG
  std::string filename = "test_canvas.png";
  canvas.write_to_png(filename);

  // Verify file was created
  std::ifstream file(filename);
  EXPECT_TRUE(file.good());
  file.close();

  // Clean up
  std::remove(filename.c_str());
}

// Test PNG with various colors
TEST(TestCanvasPNG, WritePNGMultipleColors) {
  Canvas canvas(3, 3);

  // Create a colorful pattern
  canvas.write_pixel(Color(1, 0, 0), 0, 0);  // Red
  canvas.write_pixel(Color(0, 1, 0), 1, 1);  // Green
  canvas.write_pixel(Color(0, 0, 1), 2, 2);  // Blue
  canvas.write_pixel(Color(1, 1, 0), 0, 2);  // Yellow
  canvas.write_pixel(Color(1, 0, 1), 2, 0);  // Magenta

  std::string filename = "test_colors.png";
  canvas.write_to_png(filename);

  std::ifstream file(filename);
  EXPECT_TRUE(file.good());
  file.close();

  std::remove(filename.c_str());
}

// Test PNG with clamped color values
TEST(TestCanvasPNG, WritePNGClampedColors) {
  Canvas canvas(2, 2);

  // Colors that need clamping
  canvas.write_pixel(Color(1.5, 0, 0), 0, 0);    // Should clamp to (1, 0, 0)
  canvas.write_pixel(Color(-0.5, 0, 0), 1, 0);   // Should clamp to (0, 0, 0)
  canvas.write_pixel(Color(0.5, 0.5, 0.5), 0, 1);
  canvas.write_pixel(Color(2, 2, 2), 1, 1);  // Should clamp to (1, 1, 1)

  std::string filename = "test_clamped.png";
  canvas.write_to_png(filename);

  std::ifstream file(filename);
  EXPECT_TRUE(file.good());
  file.close();

  std::remove(filename.c_str());
}

// Test PNG with default filename
TEST(TestCanvasPNG, WritePNGDefaultFilename) {
  Canvas canvas(5, 5);
  Color blue(0, 0, 1);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      canvas.write_pixel(blue, i, j);
    }
  }

  canvas.write_to_png();  // Uses default "canvas.png"

  std::ifstream file("canvas.png");
  EXPECT_TRUE(file.good());
  file.close();

  std::remove("canvas.png");
}

// Test PNG file has PNG magic number
TEST(TestCanvasPNG, WritePNGValidFormat) {
  Canvas canvas(4, 4);
  Color white(1, 1, 1);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      canvas.write_pixel(white, i, j);
    }
  }

  std::string filename = "test_format.png";
  canvas.write_to_png(filename);

  // Check PNG magic number (first 8 bytes)
  std::ifstream file(filename, std::ios::binary);
  unsigned char magic[8];
  file.read(reinterpret_cast<char*>(magic), 8);
  file.close();

  // PNG magic number is: 89 50 4E 47 0D 0A 1A 0A
  EXPECT_EQ(magic[0], 0x89);
  EXPECT_EQ(magic[1], 0x50);  // P
  EXPECT_EQ(magic[2], 0x4E);  // N
  EXPECT_EQ(magic[3], 0x47);  // G

  std::remove(filename.c_str());
}

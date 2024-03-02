#include <string>
#include "tuple.h"
#include "canvas.h"
#include "gtest/gtest.h"

// Scenario: Colors are (red, green, blue) tuples
// p16
TEST (TestColors, ColorsAreTuples) {
    Color c(-0.5, 0.4, 1.7);
    EXPECT_TRUE(equalByEpsilon(c.red, -0.5f));
    EXPECT_TRUE(equalByEpsilon(c.green, 0.4f));
    EXPECT_TRUE(equalByEpsilon(c.blue, 1.7f));
}

// Scenario: Adding colors
// p17
TEST (TestColors, AddingColors) {
    Color c1(0.9, 0.6, 0.75), c2(0.7, 0.1, 0.25);
    Color expected(1.6, 0.7, 1.0);
    EXPECT_TRUE(expected == c1 + c2);
}

// Scenario: Subtracting colors
// p17
TEST (TestColors, SubtractingColors) {
    Color c3(0.9, 0.6, 0.75), c4(0.7, 0.1, 0.25);
    Color expected_2(0.2, 0.5, 0.5);
    EXPECT_TRUE(expected_2 == c3 - c4);
}

// Scenario: Multiplying a color by a scalar
// p17
TEST (TestColors, MultiplyingColorsByScalar) {
    Color c5(0.2, 0.3, 0.4);
    Color expected_3(0.4, 0.6, 0.8);
    EXPECT_TRUE(expected_3 == c5 * 2);
    EXPECT_TRUE(expected_3 == 2 * c5);
}

// Scenario: Multiplying two colors together
// p17
TEST (TestColors, MultiplyingColorsTogether) {
    Color c6(1, 0.2, 0.4), c7(0.9, 1, 0.1);
    EXPECT_TRUE(Color(0.9, 0.2, 0.04) == c6 * c7);
}

// Scenario: test getting heights and widths
// p19
TEST (TestCanvas, GetHeightsAndWidths) {
    Canvas canvas(10, 20);
    EXPECT_TRUE(canvas.get_width() == 10);
    EXPECT_TRUE(canvas.get_height() == 20);
}

// scenario: Writing pixels to canvas
// p19
TEST (TestCanvas, WritePixelsToCanvas) {
    Canvas canvas_1(5, 10);
    Color red(1, 0, 0), black(0, 0, 0);
    canvas_1.write_pixel(red, 3, 9);
    EXPECT_TRUE(canvas_1.pixel_at(3, 8) == black);
    EXPECT_TRUE(canvas_1.pixel_at(3, 9) == red);
}

// Scenario: Construct larger ppm file
// p21
TEST (TestCanvas, ConstructPPMFileString) {
    Canvas canvas_3(5, 3);
    canvas_3.write_pixel(Color(1.5, 0, 0), 0, 0);
    canvas_3.write_pixel(Color(0, 0.5, 0), 2, 1);
    canvas_3.write_pixel(Color(-0.5, 0, 1), 4, 2);
    std::string expected_5 = "P3\n5 3\n255\n255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n";
    EXPECT_TRUE(expected_5 == canvas_3.canvas_to_ppm());
}

// Scenario: Splitting long lines in PPM files// p22
TEST (TestCanvas, SplittingLinesPPMFileString) {
    Canvas canvas_4(10, 2);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 2; j++) {
            canvas_4.write_pixel(Color(1, 0.8, 0.6), i, j);
        }
    }
    std::string expected_6 = "P3\n10 2\n255\n255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n153 255 204 153 255 204 153 255 204 153 255 204 153\n255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n153 255 204 153 255 204 153 255 204 153 255 204 153\n";
    EXPECT_TRUE(canvas_4.canvas_to_ppm() == expected_6);
}

// Scenario: PPM output always ends with newline
// p22
TEST (TestCanvas, EndPPMStringWithNewline) {
    Canvas canvas_5(5, 3);
    std::string ppm = canvas_5.canvas_to_ppm();
    EXPECT_TRUE(ppm.back() == '\n');
}

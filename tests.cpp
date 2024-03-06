
// Scenario: Multiply a product by its inverse
// p41
TEST (TestMatrices, MultiplyByInverse) {
    std::vector<float> a_data = {1, 0, 0, 1};
    std::vector<float> b_data = {1, 2, 3, 4};

    Matrix a(2, 2, a_data);
    Matrix b(2, 2, b_data);
    Matrix c = a * b;


    std::cout << b << 
    std::cout << (c * b.inverse()).get_matrix_data() << std::endl;
    std::cout << a.get_matrix_data() << std::endl;
    std::cout << b.inverse().get_matrix_data()  << std::endl;

    EXPECT_EQ(c * b.inverse(), a);
}

    if (get_column_count() == 1 && get_row_count() == 1) {
        return get_point(0, 0);
    };

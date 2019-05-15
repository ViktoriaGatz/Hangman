#include "../src/play.h"
#include "../thirdparty/ctest.h"

CTEST(check_win, neotgadan) {
    // Given
    unsigned int size = 4;
    int check[] = {27, 27, 27, 27};
    // When
    int real = Check_Win(size, check);
    // Then
    const int exp = 0;

    ASSERT_EQUAL(exp, real);
}
CTEST(check_win, otgadan_chast) {
    // Given
    unsigned int size = 4;
    int check[] = {27, 11, 8, 27};
    // When
    int real = Check_Win(size, check);
    // Then
    const int exp = 0;

    ASSERT_EQUAL(exp, real);
}
CTEST(check_win, otgadan) {
    // Given
    unsigned int size = 4;
    int check[] = {6, 11, 8, 7};
    // When
    int real = Check_Win(size, check);
    // Then
    const int exp = 1;

    ASSERT_EQUAL(exp, real);
}
CTEST(check_win, check_NULL) {
    // Given
    unsigned int size = 4;
    int check[] = {27, 11, 8, 27};
    // When
    int real = Check_Win(size, NULL);
    // Then
    const int exp = -1;

    ASSERT_EQUAL(exp, real);
}
/*----------------------------------------------------------------------------*/
CTEST(check_litriche, one_lit) {
    // Given
    unsigned int size = 4;
    int str[] = {8, 5, 2, 4};
    int check[] = {27, 27, 27, 27};
    unsigned int c = 5;
    // When
    int real = Check_Litriche(size, str, check, c);
    // Then
    const int exp = 1;

    ASSERT_EQUAL(exp, real);
}
CTEST(check_litriche, many_lit) {
    // Given
    unsigned int size = 4;
    int str[] = {8, 5, 2, 5};
    int check[] = {27, 27, 27, 27};
    unsigned int c = 5;
    // When
    int real = Check_Litriche(size, str, check, c);
    // Then
    const int exp = 2;

    ASSERT_EQUAL(exp, real);
}
CTEST(check_litriche, no_lit) {
    // Given
    unsigned int size = 4;
    int str[] = {8, 7, 2, 9};
    int check[] = {27, 27, 27, 27};
    unsigned int c = 5;
    // When
    int real = Check_Litriche(size, str, check, c);
    // Then
    const int exp = 0;

    ASSERT_EQUAL(exp, real);
}
/*-----------------------------*/
CTEST(check_litriche, array_one_lit) {
    // Given
    unsigned int size = 4;
    int str[] = {8, 5, 2, 4};
    int check[] = {27, 27, 27, 27};
    unsigned int c = 5;
    // When
    Check_Litriche(size, str, check, c);
    // Then
    const int exp[] = {27, 5, 27, 27};

    for (int i = 0; i < size; i++) {
        ASSERT_EQUAL(exp[i], check[i]);
    }
}
CTEST(check_litriche, array_many_lit) {
    // Given
    unsigned int size = 4;
    int str[] = {8, 5, 2, 5};
    int check[] = {27, 27, 27, 27};
    unsigned int c = 5;
    // When
    Check_Litriche(size, str, check, c);
    // Then
    const int exp[] = {27, 5, 27, 5};

    for (int i = 0; i < size; i++) {
        ASSERT_EQUAL(exp[i], check[i]);
    }
}
CTEST(check_litriche, array_no_lit) {
    // Given
    unsigned int size = 4;
    int str[] = {8, 7, 2, 9};
    int check[] = {27, 27, 27, 27};
    unsigned int c = 5;
    // When
    Check_Litriche(size, str, check, c);
    // Then
    const int exp[] = {27, 27, 27, 27};

    for (int i = 0; i < size; i++) {
        ASSERT_EQUAL(exp[i], check[i]);
    }
}
/*-----------------------------*/
CTEST(check_litriche, check_NULL_1) {
    // Given
    unsigned int size = 4;
    int str[] = {8, 7, 2, 9};
    int check[] = {27, 27, 27, 27};
    unsigned int c = 5;
    // When
    int real = Check_Litriche(size, NULL, check, c);
    // Then
    const int exp = -1;

    ASSERT_EQUAL(exp, real);
}
CTEST(check_litriche, check_NULL_2) {
    // Given
    unsigned int size = 4;
    int str[] = {8, 7, 2, 9};
    int check[] = {27, 27, 27, 27};
    unsigned int c = 5;
    // When
    int real = Check_Litriche(size, str, NULL, c);
    // Then
    const int exp = -1;

    ASSERT_EQUAL(exp, real);
}
CTEST(check_litriche, check_NULL_3) {
    // Given
    unsigned int size = 4;
    int str[] = {8, 7, 2, 9};
    int check[] = {27, 27, 27, 27};
    unsigned int c = 5;
    // When
    int real = Check_Litriche(size, NULL, NULL, c);
    // Then
    const int exp = -1;

    ASSERT_EQUAL(exp, real);
}
CTEST(check_litriche, check_NULL_4) {
    // Given
    unsigned int size = 4;
    int str[] = {8, 5, 2, 9};
    int check[] = {27, 27, 27, 27};
    unsigned int c = 5;
    // When
    Check_Litriche(size, NULL, NULL, c);
    // Then
    const int exp[] = {27, 27, 27, 27};

    for (int i = 0; i < size; i++) {
        ASSERT_EQUAL(exp[i], check[i]);
    }
}
/*----------------------------------------------------------------------------*/
CTEST(check_alphavit, array_lit_y) {
    // Given
    unsigned int size = 10;
    int str[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    unsigned int c = 5;
    // When
    Check_Alphavit(size, str, c);
    // Then
    const int exp[] = {1, 2, 3, 4, 0, 6, 7, 8, 9, 10};

    for (int i = 0; i < size; i++) {
        ASSERT_EQUAL(exp[i], str[i]);
    }
}
CTEST(check_alphavit, array_lit_n) {
    // Given
    unsigned int size = 10;
    int str[] = {1, 2, 3, 4, 0, 6, 7, 8, 9, 10};
    unsigned int c = 5;
    // When
    Check_Alphavit(size, str, c);
    // Then
    const int exp[] = {1, 2, 3, 4, 0, 6, 7, 8, 9, 10};

    for (int i = 0; i < size; i++) {
        ASSERT_EQUAL(exp[i], str[i]);
    }
}
CTEST(check_alphavit, return_array_lit_y) {
    // Given
    unsigned int size = 10;
    int str[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    unsigned int c = 5;
    // When
    int real = Check_Alphavit(size, str, c);
    // Then
    const int exp = 1;

    ASSERT_EQUAL(exp, real);
}
CTEST(check_alphavit, return_array_lit_n) {
    // Given
    unsigned int size = 10;
    int str[] = {1, 2, 3, 4, 0, 6, 7, 8, 9, 10};
    unsigned int c = 5;
    // When
    int real = Check_Alphavit(size, str, c);
    // Then
    const int exp = 0;

    ASSERT_EQUAL(exp, real);
}
CTEST(check_alphavit, return_if_NULL) {
    // Given
    unsigned int size = 10;
    int str[] = {1, 2, 3, 4, 0, 6, 7, 8, 9, 10};
    unsigned int c = 5;
    // When
    int real = Check_Alphavit(size, NULL, c);
    // Then
    const int exp = -1;

    ASSERT_EQUAL(exp, real);
}
/*----------------------------------------------------------------------------*/
CTEST(word_to_int, return_norm) {
    // Given
    unsigned int size = 7;
    char* string = "abcdefg";
    int str[256] = {0};
    int check[256] = {0};
    // When
    int real = Word_to_Int(&size, str, string, check);
    // Then
    const int exp = 0;

    ASSERT_EQUAL(exp, real);
}
CTEST(word_to_int, norm_str) {
    // Given
    unsigned int size = 7;
    char* string = "abcdefg";
    int str[256] = {0};
    int check[256] = {0};
    // When
    Word_to_Int(&size, str, string, check);
    // Then
    const int exp[] = {1, 2, 3, 4, 5, 6, 7};
    for (int i = 0; i < size; i++) {
        ASSERT_EQUAL(exp[i], str[i]);
    }
}
CTEST(word_to_int, norm_check) {
    // Given
    unsigned int size = 7;
    char* string = "abcdefg";
    int str[256] = {0};
    int check[256] = {0};
    // When
    Word_to_Int(&size, str, string, check);
    // Then
    const int exp[] = {1, 27, 27, 27, 27, 27, 7};
    for (int i = 0; i < size; i++) {
        ASSERT_EQUAL(exp[i], check[i]);
    }
}
/*-----------------------------*/
CTEST(word_to_int, return_if_NULL_1) {
    // Given
    unsigned int size = 7;
    char* string = "abcdefg";
    int str[256] = {0};
    int check[256] = {0};
    // When
    int real = Word_to_Int(NULL, str, string, check);
    // Then
    const int exp = -1;

    ASSERT_EQUAL(exp, real);
}
CTEST(word_to_int, return_if_NULL_2) {
    // Given
    unsigned int size = 7;
    char* string = "abcdefg";
    int str[256] = {0};
    int check[256] = {0};
    // When
    int real = Word_to_Int(&size, NULL, string, check);
    // Then
    const int exp = -1;

    ASSERT_EQUAL(exp, real);
}
CTEST(word_to_int, return_if_NULL_3) {
    // Given
    unsigned int size = 7;
    char* string = "abcdefg";
    int str[256] = {0};
    int check[256] = {0};
    // When
    int real = Word_to_Int(&size, str, NULL, check);
    // Then
    const int exp = -1;

    ASSERT_EQUAL(exp, real);
}
CTEST(word_to_int, return_if_NULL_4) {
    // Given
    unsigned int size = 7;
    char* string = "abcdefg";
    int str[256] = {0};
    int check[256] = {0};
    // When
    int real = Word_to_Int(&size, str, string, NULL);
    // Then
    const int exp = -1;

    ASSERT_EQUAL(exp, real);
}
// ASSERT_DATA_INT(exp, 7, word.str, word.size);

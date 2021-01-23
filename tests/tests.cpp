
#include "gtest/gtest.h"
#include "src/karkkainen_sanders.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

bool eq(int a1, int b1, int a2, int b2, int a3 = 0, int b3 = 0) {
    return a1 == b1 && a2 == b2 && a3 == b3;
}

bool is_sorted(int *a, int *index, int n) {
    int a1, a2, a3, b1, b2, b3;
    for (int i = 0; i < n-1; ++i) {
        a1 = a[index[i]], a2 = a[index[i] + 1], a3 = a[index[i] + 2];
        b1 = a[index[i + 1]], b2 = a[index[i + 1] + 1], b3 = a[index[i + 1] + 2];
        if (!lt(a1, b1, a2, b2, a3, b3) && !eq(a1, b1, a2, b2, a3, b3))
            return false;
    }
    return true;
}

class KarkkainenSandersTest : public testing::Test {
    protected:
        virtual void SetUp() {
            n = 11;
            n0 = (n + 2) / 3, n1 = n0, n2 = n / 3;
            n12 = n1 + n2;
            sigma = 4;

            int s[] = {2,1,4,4,1,4,4,1,3,3,1,0,0,0};
            S = new int[n + 3];
            memcpy(S, s, sizeof(int) * (n + 3));

            p12 = new int [n12];
            for (int i = 1, j = 0; j < n12; i += i % 3, j++)
                p12[j] = i;

            n_ = 5;
            n0_ = (n_ + 2) / 3, n1_ = n0_, n2_ = n_ / 3;
            n12_ = n1_ + n2_;
            sigma_ = 5;

            int s_[] = {5,5,5,5,5,0,0,0};
            S_ = new int[n_ + 3];
            memcpy(S_, s_, sizeof(int) * (n_ + 3));

            p12_ = new int [n12_];
            for (int i = 1, j = 0; j < n12_; i += i % 3, j++)
                p12_[j] = i;
        }
        int *S, *S_;
        int *p12, *p12_;
        int n, n1, n2, n0, n12;
        int n_, n1_, n2_, n0_, n12_;
        int sigma, sigma_;
};

TEST_F(KarkkainenSandersTest, TripleSorting) {
    p12 = sort_triples(S, p12, n12, sigma);
    ASSERT_EQ(true, is_sorted(S, p12, n12));

    p12_ = sort_triples(S_, p12_, n12_, sigma_);
    ASSERT_EQ(true, is_sorted(S_, p12_, n12_));
}

TEST_F(KarkkainenSandersTest, AssignNames) {
    int expected_names[] = {3, 3, 2, 1, 5, 5, 4};
    int names[n12];
    p12 = sort_triples(S, p12, n12, sigma);
    assign_names(S, names, p12, n12);
    for (int i = 0; i < n12; ++i)
        if (p12[i] % 3 == 1)
            EXPECT_EQ(expected_names[p12[i] / 3], names[i]);
        else EXPECT_EQ(expected_names[p12[i] / 3 + n1], names[i]);

    int expected_names_[] = {2,1,2};
    int names_[n12_];
    p12_ = sort_triples(S_, p12_, n12_, sigma_);
    assign_names(S_, names_, p12_, n12_);
    for (int i = 0; i < n12_; ++i)
        if (p12_[i] % 3 == 1)
            EXPECT_EQ(expected_names_[p12_[i] / 3], names_[i]);
        else EXPECT_EQ(expected_names_[p12_[i] / 3 + n1_], names_[i]);
}

TEST_F(KarkkainenSandersTest, SuffixArray) {
    int expected_sa[] = {10,7,4,1,0,9,8,6,3,5,2};
    int* sa = karkkainen_sanders_sa(S, n, sigma);
    for (int i = 0; i < n; ++i)
        EXPECT_EQ(expected_sa[i], sa[i]);

    int expected_sa_[] = {4,3,2,1,0};
    int* sa_ = karkkainen_sanders_sa(S_, n_, sigma_);
    for (int i = 0; i < n_; ++i)
        EXPECT_EQ(expected_sa_[i], sa_[i]);

    // mississipi test
    int expected2[] = {10, 7, 4, 1, 0, 9, 8, 6, 3, 5, 2};
    // Input must be padded with 3 zeros
    int input2[] = {13, 9, 19, 19, 9, 19, 19, 9, 16, 16, 9, 0, 0, 0};
    int* sa2 = karkkainen_sanders_sa(input2, 11, 20);
    for (int i = 0; i < 11; ++i)
        EXPECT_EQ(expected2[i], sa2[i]);

    // fvsqonheyowqeorycdavtnliyqakzcue test
    int expected3[] = {26, 18, 16, 29, 17, 31, 12, 7, 0, 6, 23, 27, 22, 5, 21, 4, 13, 9, 25, 11, 3, 14, 2, 20, 30, 1, 19, 10, 15, 8, 24, 28};
    // Input must be padded with 3 zeros
    int input3[] = {6, 22, 19, 17, 15, 14, 8, 5, 25, 15, 23, 17, 5, 15, 18, 25, 3, 4, 1, 22, 20, 14, 12, 9, 25, 17, 1, 11, 26, 3, 21, 5, 0, 0, 0};
    int* sa3 = karkkainen_sanders_sa(input3, 32, 35);
    for (int i = 0; i < 32; ++i)
        EXPECT_EQ(expected3[i], sa3[i]);


}

class KarkkainenSandersTest2 : public testing::Test {
    protected:
        virtual void SetUp() {
            n = 7;
            n0 = (n + 2) / 3, n1 = n0, n2 = n / 3;
            n12 = n1 + n2;
            sigma = 5;

            int s[] = {3,3,2,1,5,5,4,0,0,0};

            S = new int[n + 3];
            memcpy(S, s, sizeof(int) * (n + 3));

            p12 = new int [n12];
            for (int i = 1, j = 0; j < n12; i += i % 3, j++)
                p12[j] = i;
        }
        int *S;
        int *p12;
        int n, n1, n2, n0, n12;
        int sigma;
};

TEST_F(KarkkainenSandersTest2, TripleSorting) {
    p12 = sort_triples(S, p12, n12, sigma);
    ASSERT_EQ(true, is_sorted(S, p12, n12));
}


TEST_F(KarkkainenSandersTest2, AssignNames) {
    int expected_names[] = {3,5,1,2,4};
    int names[n12];
    p12 = sort_triples(S, p12, n12, sigma);
    assign_names(S, names, p12, n12);
    for (int i = 0; i < n12; ++i)
        if (p12[i] % 3 == 1)
            EXPECT_EQ(expected_names[p12[i] / 3], names[i]);
        else
            EXPECT_EQ(expected_names[p12[i] / 3 + n1], names[i]);
}


TEST_F(KarkkainenSandersTest2, SuffixArray) {
    int expected_sa[] = {3,2,1,0,6,5,4};
    int* sa = karkkainen_sanders_sa(S, n, sigma);
    for (int i = 0; i < n; ++i)
        EXPECT_EQ(expected_sa[i], sa[i]);
}









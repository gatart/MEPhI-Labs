#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../Lab2_c/big_dec.h"
#include "../Lab2_c/big_dec.cpp"

using namespace testing;

TEST(BigDecConstructor, DefaultConstructor){
    BigDec a;
    ASSERT_EQ(a, 0);
}

TEST(BigDecConstructor, LongConstructor){
    BigDec a(12345);
    BigDec b(-12345);
    BigDec c(-0);
    ASSERT_EQ(a, 12345);
    ASSERT_EQ(b, -12345);
    ASSERT_EQ(c, 0);
}

TEST(BigDecConstructor, StringConstructor){
    BigDec a("12345");
    BigDec b("-0000012345");
    BigDec c("+000324");
    ASSERT_EQ(a, 12345);
    ASSERT_EQ(b, -12345);
    ASSERT_EQ(c, 324);
    char* test = nullptr;
    ASSERT_THROW(BigDec d (test), invalid_argument);
    ASSERT_THROW(BigDec(""), invalid_argument);
    ASSERT_THROW(BigDec("jdfhksdj"), invalid_argument);
}

TEST(BigDecConstructor, CopyConstructor){
    BigDec a(12345);
    BigDec b(a);
    ASSERT_EQ(b, 12345);
}

TEST(BigDecConstructor, MoveConstructor){
    BigDec a(BigDec(15));
    ASSERT_EQ(a, 15);
}

TEST(BigDecMetods, Addition){ // all check also operator ~
    BigDec a (1234);
    BigDec b (11111);
    ASSERT_EQ(a + b, 12345); // check enlarging + correction
    a = 7654;
    b = 3111;
    ASSERT_EQ(a + b, 10765); // positive overflow
    a = -500;
    b = -500;
    ASSERT_EQ(a + b, -1000); // negative overflow 1 type
    a = -7123;
    b = -4321;
    ASSERT_EQ(a + b, -11444); // negative overflow 2 type
    a = 55123;
    b = -55012;
    ASSERT_EQ(a + b, 111); // correction
}

TEST(BigDecMetods, Subtraction){
    BigDec a(11111);
    BigDec b(1111);
    ASSERT_EQ(a - b, 10000);
}

TEST(BigDecMetods, ChangeSign){
    BigDec a(1);
    ASSERT_EQ(-a, -1);
    a = -1;
    ASSERT_EQ(-a, 1);
    a = 0l;
    ASSERT_EQ(-a, 0);
}

TEST(BigDecMetods, AssigmentOperator){

}
/*
TEST(BigDecMetods, MoveAssigmentOperator){

}

TEST(BigDecMetods, ReturnDigitOperator){

}

TEST(BigDecMetods, RightShift){

}

TEST(BigDecMetods, LeftShift){

}

TEST(BigDecMetods, ToString){

}

TEST(BigDecMetods, Comparisons){

}
*/

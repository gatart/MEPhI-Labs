#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../Lab1_2/catenary.h"
#include "../Lab1_2/menu.h"

using namespace testing;

TEST(CatenaryConstructor, DefaultConstructor){
    Catenary a;
    ASSERT_EQ(1, a.getParam());
}

TEST(CatenaryConstructor, InitConstructor){
    Catenary a1(4);
    ASSERT_EQ(4, a1.getParam());
    ASSERT_ANY_THROW(Catenary(-4));
}

struct CatenaryMetods : testing::Test{
    Catenary *catenary;

    CatenaryMetods(){
        catenary = new Catenary;
        catenary->setParam(4);
    }

    ~CatenaryMetods(){
        delete catenary;
    }
};

TEST_F(CatenaryMetods, setParam){
    catenary->setParam(19);
    ASSERT_EQ(19, catenary->getParam());
    ASSERT_ANY_THROW(catenary->setParam(-10););
}

TEST_F(CatenaryMetods, FindY){
    ASSERT_NEAR(7.5537, catenary->findY(5), 0.0001);
}

TEST_F(CatenaryMetods, FindLength){
    ASSERT_NEAR(11.2182, catenary->findLength(8, 3), 0.0001);
}

TEST_F(CatenaryMetods, FindR){
    ASSERT_NEAR(14.2646, catenary->findR(5), 0.0001);
}

TEST_F(CatenaryMetods, FindOr){
    ASSERT_NEAR(20.9133, catenary->findOr(5), 0.0001);
}

TEST_F(CatenaryMetods, FindS){
    ASSERT_NEAR(44.8727, catenary->findS(8, 3), 0.0001);
}

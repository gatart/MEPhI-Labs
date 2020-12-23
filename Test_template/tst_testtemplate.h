#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "template.h"

using namespace testing;
using std::string;

TEST(TemplateConstructors, Map){
    TemplateMap<string,int> test;
    ASSERT_EQ(test.size(), 0);
    ASSERT_EQ(test.begin(), test.end());
}

TEST(TemplatePrivate, Insert){
    TemplateMap<string,int> test;
    test.insert("test", 100);
    ASSERT_EQ(test.size(), 1);
    TemplateMap<string, int>::iterator tmp = test.begin();
    ASSERT_EQ(tmp->first, "test");
    ASSERT_EQ(tmp->second, 100);
    ASSERT_THROW(test.insert("test", 100), logic_error);
}

TEST(TemplatePrivate, Find){
    TemplateMap<string,int> test;
    ASSERT_EQ(test.find("test"), test.end());
    test.insert("test", 100);
    ASSERT_EQ(test.find("test"), test.begin());
}

TEST(TemplatePrivate, Clear){
    TemplateMap<string,int> test;
    test.insert("test1", 100);
    test.insert("test2", 100);
    test.insert("test3", 100);
    test.clear();
    ASSERT_EQ(test.size(), 0);
    ASSERT_EQ(test.find("test1"), test.end());
    ASSERT_EQ(test.find("test2"), test.end());
    ASSERT_EQ(test.find("test3"), test.end());
}

TEST(TemplatePublic, Begin){
    TemplateMap<string,int> test;
    ASSERT_EQ(test.begin(), test.end());
    test.insert("c",3);
    test.insert("a",1);
    test.insert("b",2);
    ASSERT_EQ(test.begin()->first, "a");
    ASSERT_EQ(test.begin()->second, 1);
}

TEST(TemplatePublic, Size){
    TemplateMap<string,int> test;
    ASSERT_EQ(test.size(), 0);
    test.insert("test1", 1);
    ASSERT_EQ(test.size(), 1);
    test.insert("test2", 1);
    test.insert("test3", 1);
    test.insert("test4", 1);
    ASSERT_EQ(test.size(), 4);
    test.clear();
    ASSERT_EQ(test.size(), 0);
}

TEST(TemplatePublic, Find){
    TemplateMap<string,int> test;
    ASSERT_EQ(test.find("test5"), test.end());
    test.insert("test1", 1);
    test.insert("test2", 2);
    test.insert("test3", 3);
    test.insert("test4", 4);
    ASSERT_EQ(test.find("test2")->first, "test2");
    ASSERT_EQ(test.find("test2")->second, 2);
    ASSERT_EQ(test.find("test5"), test.end());
}

TEST(TemplatePublic, Clear){
    TemplateMap<string,int> test;
    test.clear();
    ASSERT_EQ(test.size(), 0);
    test.insert("test1", 1);
    test.insert("test2", 2);
    test.insert("test3", 3);
    test.clear();
    ASSERT_EQ(test.size(), 0);
    ASSERT_EQ(test.find("test1"), test.end());
    ASSERT_EQ(test.find("test2"), test.end());
    ASSERT_EQ(test.find("test3"), test.end());
}

TEST(TemplatePublic, Erase){
    TemplateMap<string,int> test;
    ASSERT_EQ(test.erase("test"), 0);
    test.insert("test1", 1);
    test.insert("test2", 2);
    test.insert("test3", 3);
    test.insert("test4", 4);
    ASSERT_EQ(test.erase("test3"), 1);
    ASSERT_EQ(test.find("test3"), test.end());

}

TEST(TemplateIterator, CopyOperator){
    TemplateMap<string,int> test;
    test.insert("test1", 1);
    TemplateMap<string,int>::iterator tmp1 = test.begin();
    TemplateMap<string,int>::iterator tmp2 = tmp1;
    ASSERT_EQ(tmp1, tmp2);
}

TEST(TemplateIterator, Increment){
    TemplateMap<string,int> test;
    test.insert("test1", 1);
    test.insert("test2", 2);
    test.insert("test3", 3);
    test.insert("test4", 4);
    TemplateMap<string,int>::iterator tmp = test.begin();
    ++tmp;
    ASSERT_EQ(tmp->first, "test2");
    ASSERT_EQ(tmp->second, 2);
    ++tmp;
    ++tmp;
    ++tmp;
    ASSERT_EQ(tmp, test.end());
}

TEST(TemplateIterator, Equal){
    TemplateMap<string,int> test;
    TemplateMap<string,int>::iterator tmp = test.begin();
    ASSERT_EQ(tmp == test.end(), true);
    test.insert("test1", 1);
    tmp = test.begin();
    ASSERT_EQ(tmp == test.end(), false);
}

TEST(TemplateIterator, NotEqual){
    TemplateMap<string,int> test;
    TemplateMap<string,int>::iterator tmp = test.begin();
    ASSERT_EQ(tmp != test.end(), false);
    test.insert("test1", 1);
    tmp = test.begin();
    ASSERT_EQ(tmp != test.end(), true);
}

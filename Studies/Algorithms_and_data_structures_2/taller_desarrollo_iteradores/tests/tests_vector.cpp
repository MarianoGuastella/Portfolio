#include "vector.h"
#include "gtest-1.8.1/gtest.h"
#include <string>


TEST(vector, vacio) {
  vector<int> v_int;
  EXPECT_EQ(v_int.size(), 0);
  
  vector<std::string> v_string;
  EXPECT_EQ(v_string.size(), 0);
}


TEST(vector, un_elem) {
  vector<int> v_int;
  v_int.push_back(5);

  EXPECT_EQ(v_int.size(), 1);
  EXPECT_EQ(v_int[0], 5);
  
  vector<std::string> v_string;
  v_string.push_back("5");

  EXPECT_EQ(v_string.size(), 1);
  EXPECT_EQ(v_string[0], "5");
}

TEST(vector, varios_elems) {
  vector<int> v_int;
  v_int.push_back(5);
  v_int.push_back(10);
  v_int.push_back(15);

  EXPECT_EQ(v_int.size(), 3);
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(v_int[i], (i + 1) * 5);
  }
}

TEST(vector, varios_elems_const) {
  vector<int> v_int;
  const vector<int> & c_v = v_int;

  v_int.push_back(5);
  v_int.push_back(10);
  v_int.push_back(15);

  EXPECT_EQ(c_v.size(), 3);
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(c_v[i], (i + 1) * 5);
  }
}

TEST(vector, insertar_muchos) {
  vector<int> v;
  for (int i = 0; i < 105; i++) {
    v.push_back(i);
  }

  EXPECT_EQ(v.size(), 105);
  for (int i = 0; i < 105; i++) {
    EXPECT_EQ(v[i], i);
  }
}

// Iteradores

TEST(vector, insertar_it) {
  vector<int> v;
  auto it = v.push_back(5);
  EXPECT_EQ(*it, 5); 
  
  it = v.push_back(10);
  EXPECT_EQ(*it, 10); 
}

TEST(vector, insertar_it_muchos) {
  vector<int> v;
  for (int i = 0; i < 15; i++) {
    v.push_back(-1 * i);
  }

  auto it = v.push_back(5);
  EXPECT_EQ(*it, 5); 
  
  it = v.push_back(10);
  EXPECT_EQ(*it, 10); 
}

TEST(vector, recorrer_it) {
  vector<int> v;
  for (int i = 0; i < 15; i++) {
    v.push_back(i);
  }

  int c = 0;
  for (auto it = v.begin(); it != v.end(); ++it) {
    EXPECT_EQ(*it, c);
    c++;
  }
}

TEST(vector, recorrer_it_const) {
  vector<int> v;
  const vector<int>& vc = v;
  for (int i = 0; i < 15; i++) {
    v.push_back(i);
  }

  int c = 0;
  for (auto it = vc.begin(); it != vc.end(); ++it) {
    EXPECT_EQ(*it, c);
    c++;
  }
}

TEST(vector, for_range) {
  vector<int> v; 
  for (int i = 0; i < 15; i++) {
    v.push_back(i);
  }

  int c = 0;
  for (auto& x : v) {
    EXPECT_EQ(x, c);
    c++;
  }
}

TEST(vector, for_range_const) {
  vector<int> v; 
  const vector<int>& cv = v;
  for (int i = 0; i < 15; i++) {
    v.push_back(i);
  }

  int c = 0;
  for (auto& x : cv) {
    EXPECT_EQ(x, c);
    c++;
  }
}

#include "gtest-1.8.1/gtest.h"
#include "../src/aed2_Mapa.h"


TEST(mapa_test, test_mapa_vacio) {
    aed2_Mapa m;

    for (int x = -10; x <= 10; ++x) {
        for (int y = -10; y <= 10; ++y) {
            EXPECT_FALSE(m.hayRio({x, y}));
        }
    }
}

TEST(mapa_test, test_agregar_rio_vertical) {
    aed2_Mapa m;
    m.agregarRio(Vertical, 4);

    EXPECT_TRUE(m.hayRio({4, 0}));
    EXPECT_TRUE(m.hayRio({4, 1000}));
    EXPECT_TRUE(m.hayRio({4, -500}));
    EXPECT_FALSE(m.hayRio({0, 4}));
}

TEST(mapa_test, test_agregar_rio_horizontal) {
    aed2_Mapa m;
    m.agregarRio(Horizontal, -6);

    EXPECT_TRUE(m.hayRio({0, -6}));
    EXPECT_TRUE(m.hayRio({130, -6}));
    EXPECT_TRUE(m.hayRio({-48, -6}));
    EXPECT_FALSE(m.hayRio({-6, 1}));
}

TEST(mapa_test, test_agregar_varios_rios) {
    aed2_Mapa m;
    m.agregarRio(Vertical, 0);
    m.agregarRio(Vertical, 7);
    m.agregarRio(Vertical, -2);
    m.agregarRio(Horizontal, 1);
    m.agregarRio(Horizontal, -8);
    m.agregarRio(Horizontal, 5);

    EXPECT_TRUE(m.hayRio({0, 1}));
    EXPECT_TRUE(m.hayRio({-1, 5}));
    EXPECT_TRUE(m.hayRio({-2, -3}));
    EXPECT_TRUE(m.hayRio({7, -4}));
    EXPECT_TRUE(m.hayRio({3, -8}));
    EXPECT_FALSE(m.hayRio({1, 0}));
    EXPECT_FALSE(m.hayRio({-1, 0}));
    EXPECT_FALSE(m.hayRio({-1, 4}));
    EXPECT_FALSE(m.hayRio({5, 7}));
    EXPECT_FALSE(m.hayRio({-7, -5}));
}

TEST(mapa_test, test_unir_mapas) {
    aed2_Mapa m1;
    m1.agregarRio(Vertical, 0);
    m1.agregarRio(Vertical, 7);
    m1.agregarRio(Vertical, -2);
    m1.agregarRio(Horizontal, 1);
    m1.agregarRio(Horizontal, -8);
    m1.agregarRio(Horizontal, 5);

    aed2_Mapa m2;
    m2.agregarRio(Vertical, 6);
    m2.agregarRio(Vertical, 3);
    m2.agregarRio(Vertical, -4);
    m2.agregarRio(Horizontal, 1);
    m2.agregarRio(Horizontal, 9);
    m2.agregarRio(Horizontal, -5);

    m1.unirMapa(m2);

    EXPECT_TRUE(m1.hayRio({0, 1}));
    EXPECT_TRUE(m1.hayRio({-1, 5}));
    EXPECT_TRUE(m1.hayRio({-2, -3}));
    EXPECT_TRUE(m1.hayRio({7, -4}));
    EXPECT_TRUE(m1.hayRio({3, -8}));
    EXPECT_TRUE(m1.hayRio({-9, 9}));
    EXPECT_TRUE(m1.hayRio({-4, -7}));
    EXPECT_TRUE(m1.hayRio({3, 0}));
    EXPECT_TRUE(m1.hayRio({9, -5}));
    EXPECT_TRUE(m1.hayRio({6, 3}));
    EXPECT_FALSE(m1.hayRio({1, 0}));
    EXPECT_FALSE(m1.hayRio({-1, 0}));
    EXPECT_FALSE(m1.hayRio({-1, 4}));
    EXPECT_FALSE(m1.hayRio({-9, -9}));
    EXPECT_FALSE(m1.hayRio({9, -9}));
}

#include "gtest-1.8.1/gtest.h"
#include "../src/aed2_SimCity.h"


aed2_Mapa crearMapa(const set<int> &riosVerticales, const set<int> &riosHorizontales) {
    aed2_Mapa res;
    for (int r : riosVerticales) {
        res.agregarRio(Vertical, r);
    }
    for (int r : riosHorizontales) {
        res.agregarRio(Horizontal, r);
    }
    return res;
}

class SimCityTest : public testing::Test {
protected:
    Casilla pos0, pos1, pos2, pos3, pos4, pos5, pos6, pos7, pos8, pos9;
    set<Casilla> posicion1, posicion2, posiciones234, posiciones01234, posiciones56789;
    aed2_Mapa m1, m2, m3, m4, m12, m1234;

    void SetUp() {
        pos0 = {-2, -2};
        pos1 = {4, -2};
        pos2 = {3, 0};
        pos3 = {5, -3};
        pos4 = {4, -3};
        pos5 = {2, 0};
        pos6 = {2, -4};
        pos7 = {6, 0};
        pos8 = {6, -4};
        pos9 = {4, 7};
        posicion1 = {pos1};
        posicion2 = {pos2};
        posiciones234 = {pos2, pos3, pos4};
        posiciones01234 = {pos0, pos1, pos2, pos3, pos4};
        posiciones56789 = {pos5, pos6, pos7, pos8, pos9};
        m1 = crearMapa({0, 7, -3}, {1, 5, -6, -1});
        m2 = crearMapa({-8, 1, -3}, {1, 3, -5});
        m3 = crearMapa({9, -5, -8}, {-6, -9, 9});
        m4 = crearMapa({-3, 8, -5}, {6, -7, 8});
        m12 = crearMapa({0, 1, -3, 7, -8}, {-1, 1, 3, 5, -5, -6});
        m1234 = crearMapa({-8, 9, -5, 8, -3, 7, 0, 1}, {-9, -7, -6, -5, -1, 9, 8, 6, 5, 3, 1});
    }

};

void compararMapas(const aed2_Mapa &m1, const aed2_Mapa &m2) {
    for (int x = -10; x <= 10; ++x) {
        for (int y = -10; y <= 10; ++y) {
            EXPECT_EQ(m1.hayRio({x, y}), m2.hayRio({x, y}));
        }
    }
}

TEST_F(SimCityTest, empezar_partida) {
    aed2_SimCity sc(m1);

    compararMapas(sc.mapa(), m1);
    EXPECT_FALSE(sc.huboConstruccion());
    EXPECT_EQ(sc.popularidad(), 0);
    EXPECT_EQ(sc.antiguedad(), 0);
    EXPECT_TRUE(sc.casas().empty());
    EXPECT_TRUE(sc.comercios().empty());
}

TEST_F(SimCityTest, agregar_casa) {
    aed2_SimCity sc(m1);
    sc.agregarCasa(pos1);

    compararMapas(sc.mapa(), m1);
    EXPECT_TRUE(sc.huboConstruccion());
    EXPECT_EQ(sc.popularidad(), 0);
    EXPECT_EQ(sc.antiguedad(), 0);
    EXPECT_TRUE(sc.comercios().empty());
    EXPECT_EQ(sc.casas(), posicion1);
    EXPECT_EQ(sc.nivel(pos1), 0);
}

TEST_F(SimCityTest, agregar_comercio) {
    aed2_SimCity sc(m1);
    sc.agregarComercio(pos1);

    compararMapas(sc.mapa(), m1);
    EXPECT_TRUE(sc.huboConstruccion());
    EXPECT_EQ(sc.popularidad(), 0);
    EXPECT_EQ(sc.antiguedad(), 0);
    EXPECT_TRUE(sc.casas().empty());
    EXPECT_EQ(sc.comercios(), posicion1);
    EXPECT_EQ(sc.nivel(pos1), 0);
}

TEST_F(SimCityTest, avanzar_turno) {
    aed2_SimCity sc(m1);
    sc.agregarCasa(pos1);
    sc.avanzarTurno();

    compararMapas(sc.mapa(), m1);
    EXPECT_FALSE(sc.huboConstruccion());
    EXPECT_EQ(sc.popularidad(), 0);
    EXPECT_EQ(sc.antiguedad(), 1);
    EXPECT_TRUE(sc.comercios().empty());
    EXPECT_EQ(sc.casas(), posicion1);
    EXPECT_EQ(sc.nivel(pos1), 1);
}

TEST_F(SimCityTest, agregar_multiples_casas) {
    aed2_SimCity sc(m1);
    sc.agregarCasa(pos2);
    sc.avanzarTurno();
    sc.agregarCasa(pos3);
    sc.avanzarTurno();
    sc.agregarCasa(pos4);

    compararMapas(sc.mapa(), m1);
    EXPECT_TRUE(sc.huboConstruccion());
    EXPECT_EQ(sc.popularidad(), 0);
    EXPECT_EQ(sc.antiguedad(), 2);
    EXPECT_TRUE(sc.comercios().empty());
    EXPECT_EQ(sc.casas(), posiciones234);
    EXPECT_EQ(sc.nivel(pos2), 2);
    EXPECT_EQ(sc.nivel(pos3), 1);
    EXPECT_EQ(sc.nivel(pos4), 0);
}

TEST_F(SimCityTest, agregar_multiples_comercios) {
    aed2_SimCity sc(m1);
    sc.agregarComercio(pos4);
    sc.avanzarTurno();
    sc.agregarComercio(pos3);
    sc.avanzarTurno();
    sc.agregarComercio(pos2);
    sc.avanzarTurno();

    compararMapas(sc.mapa(), m1);
    EXPECT_FALSE(sc.huboConstruccion());
    EXPECT_EQ(sc.popularidad(), 0);
    EXPECT_EQ(sc.antiguedad(), 3);
    EXPECT_TRUE(sc.casas().empty());
    EXPECT_EQ(sc.comercios(), posiciones234);
    EXPECT_EQ(sc.nivel(pos2), 1);
    EXPECT_EQ(sc.nivel(pos3), 2);
    EXPECT_EQ(sc.nivel(pos4), 3);
}

TEST_F(SimCityTest, comercio_con_casa_mejor_cercana) {
    aed2_SimCity sc(m1);
    sc.agregarCasa(pos1);
    sc.avanzarTurno();
    sc.agregarComercio(pos2);

    compararMapas(sc.mapa(), m1);
    EXPECT_TRUE(sc.huboConstruccion());
    EXPECT_EQ(sc.popularidad(), 0);
    EXPECT_EQ(sc.antiguedad(), 1);
    EXPECT_EQ(sc.casas(), posicion1);
    EXPECT_EQ(sc.comercios(), posicion2);
    EXPECT_EQ(sc.nivel(pos1), 1);
    EXPECT_EQ(sc.nivel(pos2), 1);
}

TEST_F(SimCityTest, comercio_con_casa_peor_cercana) {
    aed2_SimCity sc(m1);
    sc.agregarComercio(pos2);
    sc.avanzarTurno();
    sc.agregarCasa(pos1);

    compararMapas(sc.mapa(), m1);
    EXPECT_TRUE(sc.huboConstruccion());
    EXPECT_EQ(sc.popularidad(), 0);
    EXPECT_EQ(sc.antiguedad(), 1);
    EXPECT_EQ(sc.casas(), posicion1);
    EXPECT_EQ(sc.comercios(), posicion2);
    EXPECT_EQ(sc.nivel(pos1), 0);
    EXPECT_EQ(sc.nivel(pos2), 1);
}

TEST_F(SimCityTest, comercio_con_varias_casas_cercanas) {
    aed2_SimCity sc(m1);
    sc.agregarCasa(pos3);
    sc.avanzarTurno();
    sc.agregarCasa(pos4);
    sc.avanzarTurno();
    sc.agregarCasa(pos2);
    sc.avanzarTurno();
    sc.agregarComercio(pos1);
    sc.avanzarTurno();

    compararMapas(sc.mapa(), m1);
    EXPECT_FALSE(sc.huboConstruccion());
    EXPECT_EQ(sc.popularidad(), 0);
    EXPECT_EQ(sc.antiguedad(), 4);
    EXPECT_EQ(sc.casas(), posiciones234);
    EXPECT_EQ(sc.comercios(), posicion1);
    EXPECT_EQ(sc.nivel(pos1), 4);
    EXPECT_EQ(sc.nivel(pos2), 2);
    EXPECT_EQ(sc.nivel(pos3), 4);
    EXPECT_EQ(sc.nivel(pos4), 3);
}

TEST_F(SimCityTest, comercio_con_casas_lejanas) {
    aed2_SimCity sc(m1);
    sc.agregarCasa(pos5);
    sc.avanzarTurno();
    sc.agregarCasa(pos6);
    sc.avanzarTurno();
    sc.agregarCasa(pos7);
    sc.avanzarTurno();
    sc.agregarCasa(pos8);
    sc.avanzarTurno();
    sc.agregarCasa(pos9);
    sc.agregarComercio(pos1);

    compararMapas(sc.mapa(), m1);
    EXPECT_TRUE(sc.huboConstruccion());
    EXPECT_EQ(sc.popularidad(), 0);
    EXPECT_EQ(sc.antiguedad(), 4);
    EXPECT_EQ(sc.casas(), posiciones56789);
    EXPECT_EQ(sc.comercios(), posicion1);
    EXPECT_EQ(sc.nivel(pos1), 0);
    EXPECT_EQ(sc.nivel(pos5), 4);
    EXPECT_EQ(sc.nivel(pos6), 3);
    EXPECT_EQ(sc.nivel(pos7), 2);
    EXPECT_EQ(sc.nivel(pos8), 1);
    EXPECT_EQ(sc.nivel(pos9), 0);
}

TEST_F(SimCityTest, varias_construcciones_en_mismo_turno) {
    aed2_SimCity sc(m1);
    sc.agregarCasa(pos0);
    sc.agregarComercio(pos9);
    sc.avanzarTurno();
    sc.agregarCasa(pos1);
    sc.agregarComercio(pos7);
    sc.agregarCasa(pos3);
    sc.avanzarTurno();
    sc.agregarComercio(pos6);
    sc.agregarCasa(pos2);
    sc.agregarComercio(pos8);
    sc.avanzarTurno();
    sc.agregarCasa(pos4);
    sc.agregarComercio(pos5);
    sc.avanzarTurno();

    compararMapas(sc.mapa(), m1);
    EXPECT_FALSE(sc.huboConstruccion());
    EXPECT_EQ(sc.popularidad(), 0);
    EXPECT_EQ(sc.antiguedad(), 4);
    EXPECT_EQ(sc.casas(), posiciones01234);
    EXPECT_EQ(sc.comercios(), posiciones56789);
    EXPECT_EQ(sc.nivel(pos0), 4);
    EXPECT_EQ(sc.nivel(pos1), 3);
    EXPECT_EQ(sc.nivel(pos2), 2);
    EXPECT_EQ(sc.nivel(pos3), 3);
    EXPECT_EQ(sc.nivel(pos4), 1);
    EXPECT_EQ(sc.nivel(pos5), 2);
    EXPECT_EQ(sc.nivel(pos6), 2);
    EXPECT_EQ(sc.nivel(pos7), 3);
    EXPECT_EQ(sc.nivel(pos8), 3);
    EXPECT_EQ(sc.nivel(pos9), 4);
}

TEST_F(SimCityTest, unir_partidas_vacias) {
    aed2_SimCity sc1(m1);
    aed2_SimCity sc2(m2);
    sc1.unir(sc2);

    compararMapas(sc1.mapa(), m12);
    EXPECT_FALSE(sc1.huboConstruccion());
    EXPECT_EQ(sc1.popularidad(), 1);
    EXPECT_EQ(sc1.antiguedad(), 0);
    EXPECT_TRUE(sc1.comercios().empty());
    EXPECT_TRUE(sc1.casas().empty());
}

TEST_F(SimCityTest, unir_partida_mas_nueva_con_casas) {
    aed2_SimCity sc1(m1);
    aed2_SimCity sc2(m2);
    sc1.agregarCasa(pos3);
    sc1.agregarCasa(pos4);
    sc1.avanzarTurno();
    sc2.agregarCasa(pos2);
    sc1.unir(sc2);

    compararMapas(sc1.mapa(), m12);
    EXPECT_TRUE(sc1.huboConstruccion());
    EXPECT_EQ(sc1.antiguedad(), 1);
    EXPECT_EQ(sc1.popularidad(), 1);
    EXPECT_TRUE(sc1.comercios().empty());
    EXPECT_EQ(sc1.casas(), posiciones234);
    EXPECT_EQ(sc1.nivel(pos2), 0);
    EXPECT_EQ(sc1.nivel(pos3), 1);
    EXPECT_EQ(sc1.nivel(pos4), 1);
}

TEST_F(SimCityTest, unir_partida_mas_vieja_con_casas) {
    aed2_SimCity sc1(m1);
    aed2_SimCity sc2(m2);
    sc1.agregarCasa(pos3);
    sc1.agregarCasa(pos4);
    sc2.agregarCasa(pos2);
    sc2.avanzarTurno();
    sc1.unir(sc2);

    compararMapas(sc1.mapa(), m12);
    EXPECT_TRUE(sc1.huboConstruccion());
    EXPECT_EQ(sc1.antiguedad(), 1);
    EXPECT_EQ(sc1.popularidad(), 1);
    EXPECT_TRUE(sc1.comercios().empty());
    EXPECT_EQ(sc1.casas(), posiciones234);
    EXPECT_EQ(sc1.nivel(pos2), 1);
    EXPECT_EQ(sc1.nivel(pos3), 0);
    EXPECT_EQ(sc1.nivel(pos4), 0);
}

TEST_F(SimCityTest, unir_partidas_con_comercios) {
    aed2_SimCity sc1(m1);
    aed2_SimCity sc2(m2);
    sc1.agregarComercio(pos3);
    sc1.agregarComercio(pos4);
    sc1.avanzarTurno();
    sc2.agregarComercio(pos2);
    sc1.unir(sc2);

    compararMapas(sc1.mapa(), m12);
    EXPECT_TRUE(sc1.huboConstruccion());
    EXPECT_EQ(sc1.antiguedad(), 1);
    EXPECT_EQ(sc1.popularidad(), 1);
    EXPECT_TRUE(sc1.casas().empty());
    EXPECT_EQ(sc1.comercios(), posiciones234);
    EXPECT_EQ(sc1.nivel(pos2), 0);
    EXPECT_EQ(sc1.nivel(pos3), 1);
    EXPECT_EQ(sc1.nivel(pos4), 1);
}

TEST_F(SimCityTest, unir_casas_solapadas_mismo_nivel) {
    aed2_SimCity sc1(m1);
    aed2_SimCity sc2(m2);
    sc1.agregarCasa(pos0);
    sc1.agregarCasa(pos1);
    sc1.avanzarTurno();
    sc1.agregarCasa(pos3);
    sc1.avanzarTurno();
    sc1.agregarCasa(pos2);
    sc1.avanzarTurno();
    sc2.agregarCasa(pos4);
    sc2.avanzarTurno();
    sc2.agregarCasa(pos2);
    sc2.avanzarTurno();
    sc1.unir(sc2);

    compararMapas(sc1.mapa(), m12);
    EXPECT_FALSE(sc1.huboConstruccion());
    EXPECT_EQ(sc1.antiguedad(), 3);
    EXPECT_EQ(sc1.popularidad(), 1);
    EXPECT_TRUE(sc1.comercios().empty());
    EXPECT_EQ(sc1.casas(), posiciones01234);
    EXPECT_EQ(sc1.nivel(pos0), 3);
    EXPECT_EQ(sc1.nivel(pos1), 3);
    EXPECT_EQ(sc1.nivel(pos2), 1);
    EXPECT_EQ(sc1.nivel(pos3), 2);
    EXPECT_EQ(sc1.nivel(pos4), 2);
}

TEST_F(SimCityTest, unir_casas_solapadas_mayor_nivel) {
    aed2_SimCity sc1(m1);
    aed2_SimCity sc2(m2);
    sc1.agregarCasa(pos0);
    sc1.agregarCasa(pos1);
    sc1.avanzarTurno();
    sc1.agregarCasa(pos3);
    sc1.avanzarTurno();
    sc1.agregarCasa(pos2);
    sc1.avanzarTurno();
    sc2.agregarCasa(pos4);
    sc2.avanzarTurno();
    sc2.agregarCasa(pos2);
    sc1.unir(sc2);

    compararMapas(sc1.mapa(), m12);
    EXPECT_TRUE(sc1.huboConstruccion());
    EXPECT_EQ(sc1.antiguedad(), 3);
    EXPECT_EQ(sc1.popularidad(), 1);
    EXPECT_TRUE(sc1.comercios().empty());
    EXPECT_EQ(sc1.casas(), posiciones01234);
    EXPECT_EQ(sc1.nivel(pos0), 3);
    EXPECT_EQ(sc1.nivel(pos1), 3);
    EXPECT_EQ(sc1.nivel(pos2), 1);
    EXPECT_EQ(sc1.nivel(pos3), 2);
    EXPECT_EQ(sc1.nivel(pos4), 1);
}

TEST_F(SimCityTest, unir_casas_solapadas_menor_nivel) {
    aed2_SimCity sc1(m1);
    aed2_SimCity sc2(m2);
    sc1.agregarCasa(pos0);
    sc1.agregarCasa(pos1);
    sc1.avanzarTurno();
    sc1.agregarCasa(pos3);
    sc1.avanzarTurno();
    sc1.agregarCasa(pos2);
    sc2.agregarCasa(pos4);
    sc2.avanzarTurno();
    sc2.agregarCasa(pos2);
    sc2.avanzarTurno();
    sc1.unir(sc2);

    compararMapas(sc1.mapa(), m12);
    EXPECT_TRUE(sc1.huboConstruccion());
    EXPECT_EQ(sc1.antiguedad(), 2);
    EXPECT_EQ(sc1.popularidad(), 1);
    EXPECT_TRUE(sc1.comercios().empty());
    EXPECT_EQ(sc1.casas(), posiciones01234);
    EXPECT_EQ(sc1.nivel(pos0), 2);
    EXPECT_EQ(sc1.nivel(pos1), 2);
    EXPECT_EQ(sc1.nivel(pos2), 1);
    EXPECT_EQ(sc1.nivel(pos3), 1);
    EXPECT_EQ(sc1.nivel(pos4), 2);
}

TEST_F(SimCityTest, unir_comercios_solapados_mismo_nivel) {
    aed2_SimCity sc1(m1);
    aed2_SimCity sc2(m2);
    sc1.agregarComercio(pos0);
    sc1.agregarComercio(pos1);
    sc1.avanzarTurno();
    sc1.agregarComercio(pos3);
    sc1.avanzarTurno();
    sc1.agregarComercio(pos2);
    sc1.avanzarTurno();
    sc2.agregarComercio(pos4);
    sc2.avanzarTurno();
    sc2.agregarComercio(pos2);
    sc2.avanzarTurno();
    sc1.unir(sc2);

    compararMapas(sc1.mapa(), m12);
    EXPECT_FALSE(sc1.huboConstruccion());
    EXPECT_EQ(sc1.antiguedad(), 3);
    EXPECT_EQ(sc1.popularidad(), 1);
    EXPECT_TRUE(sc1.casas().empty());
    EXPECT_EQ(sc1.comercios(), posiciones01234);
    EXPECT_EQ(sc1.nivel(pos0), 3);
    EXPECT_EQ(sc1.nivel(pos1), 3);
    EXPECT_EQ(sc1.nivel(pos2), 1);
    EXPECT_EQ(sc1.nivel(pos3), 2);
    EXPECT_EQ(sc1.nivel(pos4), 2);
}

TEST_F(SimCityTest, unir_comercios_solapados_mayor_nivel) {
    aed2_SimCity sc1(m1);
    aed2_SimCity sc2(m2);
    sc1.agregarComercio(pos0);
    sc1.agregarComercio(pos1);
    sc1.avanzarTurno();
    sc1.agregarComercio(pos3);
    sc1.avanzarTurno();
    sc1.agregarComercio(pos2);
    sc1.avanzarTurno();
    sc2.agregarComercio(pos4);
    sc2.avanzarTurno();
    sc2.agregarComercio(pos2);
    sc1.unir(sc2);

    compararMapas(sc1.mapa(), m12);
    EXPECT_TRUE(sc1.huboConstruccion());
    EXPECT_EQ(sc1.antiguedad(), 3);
    EXPECT_EQ(sc1.popularidad(), 1);
    EXPECT_TRUE(sc1.casas().empty());
    EXPECT_EQ(sc1.comercios(), posiciones01234);
    EXPECT_EQ(sc1.nivel(pos0), 3);
    EXPECT_EQ(sc1.nivel(pos1), 3);
    EXPECT_EQ(sc1.nivel(pos2), 1);
    EXPECT_EQ(sc1.nivel(pos3), 2);
    EXPECT_EQ(sc1.nivel(pos4), 1);
}

TEST_F(SimCityTest, unir_comercios_solapados_menor_nivel) {
    aed2_SimCity sc1(m1);
    aed2_SimCity sc2(m2);
    sc1.agregarComercio(pos0);
    sc1.agregarComercio(pos1);
    sc1.avanzarTurno();
    sc1.agregarComercio(pos3);
    sc1.avanzarTurno();
    sc1.agregarComercio(pos2);
    sc2.agregarComercio(pos4);
    sc2.avanzarTurno();
    sc2.agregarComercio(pos2);
    sc2.avanzarTurno();
    sc1.unir(sc2);

    compararMapas(sc1.mapa(), m12);
    EXPECT_TRUE(sc1.huboConstruccion());
    EXPECT_EQ(sc1.antiguedad(), 2);
    EXPECT_EQ(sc1.popularidad(), 1);
    EXPECT_TRUE(sc1.casas().empty());
    EXPECT_EQ(sc1.comercios(), posiciones01234);
    EXPECT_EQ(sc1.nivel(pos0), 2);
    EXPECT_EQ(sc1.nivel(pos1), 2);
    EXPECT_EQ(sc1.nivel(pos2), 1);
    EXPECT_EQ(sc1.nivel(pos3), 1);
    EXPECT_EQ(sc1.nivel(pos4), 2);
}

TEST_F(SimCityTest, unir_solapamiento_casa_mayor_a_comercio) {
    aed2_SimCity sc1(m1);
    aed2_SimCity sc2(m2);
    sc1.agregarComercio(pos1);
    sc1.avanzarTurno();
    sc1.agregarCasa(pos3);
    sc1.avanzarTurno();
    sc1.agregarCasa(pos2);
    sc1.avanzarTurno();
    sc2.agregarCasa(pos4);
    sc2.avanzarTurno();
    sc2.agregarComercio(pos2);
    sc1.unir(sc2);

    compararMapas(sc1.mapa(), m12);
    EXPECT_TRUE(sc1.huboConstruccion());
    EXPECT_EQ(sc1.antiguedad(), 3);
    EXPECT_EQ(sc1.popularidad(), 1);
    EXPECT_EQ(sc1.casas(), posiciones234);
    EXPECT_EQ(sc1.comercios(), posicion1);
    EXPECT_EQ(sc1.nivel(pos1), 3);
    EXPECT_EQ(sc1.nivel(pos2), 1);
    EXPECT_EQ(sc1.nivel(pos3), 2);
    EXPECT_EQ(sc1.nivel(pos4), 1);
}

TEST_F(SimCityTest, unir_solapamiento_casa_menor_a_comercio) {
    aed2_SimCity sc1(m1);
    aed2_SimCity sc2(m2);
    sc1.agregarComercio(pos1);
    sc1.avanzarTurno();
    sc1.agregarCasa(pos3);
    sc1.avanzarTurno();
    sc1.agregarCasa(pos2);
    sc2.agregarCasa(pos4);
    sc2.avanzarTurno();
    sc2.agregarComercio(pos2);
    sc2.avanzarTurno();
    sc1.unir(sc2);

    compararMapas(sc1.mapa(), m12);
    EXPECT_TRUE(sc1.huboConstruccion());
    EXPECT_EQ(sc1.antiguedad(), 2);
    EXPECT_EQ(sc1.popularidad(), 1);
    EXPECT_EQ(sc1.casas(), posiciones234);
    EXPECT_EQ(sc1.comercios(), posicion1);
    EXPECT_EQ(sc1.nivel(pos1), 2);
    EXPECT_EQ(sc1.nivel(pos2), 0);
    EXPECT_EQ(sc1.nivel(pos3), 1);
    EXPECT_EQ(sc1.nivel(pos4), 2);
}

TEST_F(SimCityTest, unir_solapamiento_comercio_mayor_a_casa) {
    aed2_SimCity sc1(m1);
    aed2_SimCity sc2(m2);
    sc1.agregarComercio(pos1);
    sc1.avanzarTurno();
    sc1.agregarCasa(pos3);
    sc1.avanzarTurno();
    sc1.agregarComercio(pos2);
    sc1.avanzarTurno();
    sc2.agregarCasa(pos4);
    sc2.avanzarTurno();
    sc2.agregarCasa(pos2);
    sc1.unir(sc2);

    compararMapas(sc1.mapa(), m12);
    EXPECT_TRUE(sc1.huboConstruccion());
    EXPECT_EQ(sc1.antiguedad(), 3);
    EXPECT_EQ(sc1.popularidad(), 1);
    EXPECT_EQ(sc1.casas(), posiciones234);
    EXPECT_EQ(sc1.comercios(), posicion1);
    EXPECT_EQ(sc1.nivel(pos1), 3);
    EXPECT_EQ(sc1.nivel(pos2), 0);
    EXPECT_EQ(sc1.nivel(pos3), 2);
    EXPECT_EQ(sc1.nivel(pos4), 1);
}

TEST_F(SimCityTest, unir_solapamiento_comercio_menor_a_casa) {
    aed2_SimCity sc1(m1);
    aed2_SimCity sc2(m2);
    sc1.agregarComercio(pos1);
    sc1.avanzarTurno();
    sc1.agregarCasa(pos3);
    sc1.avanzarTurno();
    sc1.agregarComercio(pos2);
    sc2.agregarCasa(pos4);
    sc2.avanzarTurno();
    sc2.agregarCasa(pos2);
    sc2.avanzarTurno();
    sc1.unir(sc2);

    compararMapas(sc1.mapa(), m12);
    EXPECT_TRUE(sc1.huboConstruccion());
    EXPECT_EQ(sc1.antiguedad(), 2);
    EXPECT_EQ(sc1.popularidad(), 1);
    EXPECT_EQ(sc1.casas(), posiciones234);
    EXPECT_EQ(sc1.comercios(), posicion1);
    EXPECT_EQ(sc1.nivel(pos1), 2);
    EXPECT_EQ(sc1.nivel(pos2), 1);
    EXPECT_EQ(sc1.nivel(pos3), 1);
    EXPECT_EQ(sc1.nivel(pos4), 2);
}

TEST_F(SimCityTest, unir_comercio_aumenta_nivel_por_casas_cercanas) {
    aed2_SimCity sc1(m1);
    aed2_SimCity sc2(m2);
    sc1.agregarComercio(pos2);
    sc1.agregarComercio(pos4);
    sc1.avanzarTurno();
    sc1.agregarComercio(pos3);
    sc2.agregarCasa(pos1);
    sc2.avanzarTurno();
    sc1.unir(sc2);

    compararMapas(sc1.mapa(), m12);
    EXPECT_TRUE(sc1.huboConstruccion());
    EXPECT_EQ(sc1.antiguedad(), 1);
    EXPECT_EQ(sc1.popularidad(), 1);
    EXPECT_EQ(sc1.casas(), posicion1);
    EXPECT_EQ(sc1.comercios(), posiciones234);
    EXPECT_EQ(sc1.nivel(pos1), 1);
    EXPECT_EQ(sc1.nivel(pos2), 1);
    EXPECT_EQ(sc1.nivel(pos3), 1);
    EXPECT_EQ(sc1.nivel(pos4), 1);
}

TEST_F(SimCityTest, unir_por_casas_cercanas_comercio_aumenta_nivel) {
    aed2_SimCity sc1(m1);
    aed2_SimCity sc2(m2);
    sc1.agregarComercio(pos2);
    sc1.agregarComercio(pos4);
    sc1.avanzarTurno();
    sc1.agregarCasa(pos1);
    sc1.avanzarTurno();
    sc2.agregarComercio(pos3);
    sc1.unir(sc2);

    compararMapas(sc1.mapa(), m12);
    EXPECT_TRUE(sc1.huboConstruccion());
    EXPECT_EQ(sc1.antiguedad(), 2);
    EXPECT_EQ(sc1.popularidad(), 1);
    EXPECT_EQ(sc1.casas(), posicion1);
    EXPECT_EQ(sc1.comercios(), posiciones234);
    EXPECT_EQ(sc1.nivel(pos1), 1);
    EXPECT_EQ(sc1.nivel(pos2), 2);
    EXPECT_EQ(sc1.nivel(pos3), 1);
    EXPECT_EQ(sc1.nivel(pos4), 2);
}

TEST_F(SimCityTest, unir_partidas_y_avanzar_turno) {
    aed2_SimCity sc1(m1);
    aed2_SimCity sc2(m2);
    sc1.agregarCasa(pos0);
    sc1.avanzarTurno();
    sc1.agregarComercio(pos3);
    sc1.avanzarTurno();
    sc1.agregarComercio(pos1);
    sc1.agregarCasa(pos2);
    sc1.avanzarTurno();
    sc1.agregarCasa(pos4);
    sc1.avanzarTurno();
    sc1.agregarComercio(pos6);
    sc1.agregarComercio(pos8);
    sc1.avanzarTurno();
    sc2.agregarComercio(pos9);
    sc2.avanzarTurno();
    sc2.agregarCasa(pos1);
    sc2.avanzarTurno();
    sc2.agregarComercio(pos4);
    sc2.avanzarTurno();
    sc2.agregarCasa(pos3);
    sc2.avanzarTurno();
    sc2.agregarComercio(pos2);
    sc2.avanzarTurno();
    sc2.agregarComercio(pos5);
    sc2.avanzarTurno();
    sc2.agregarComercio(pos7);
    sc1.unir(sc2);
    sc1.avanzarTurno();

    compararMapas(sc1.mapa(), m12);
    EXPECT_FALSE(sc1.huboConstruccion());
    EXPECT_EQ(sc1.antiguedad(), 7);
    EXPECT_EQ(sc1.popularidad(), 1);
    EXPECT_EQ(sc1.casas(), posiciones01234);
    EXPECT_EQ(sc1.comercios(), posiciones56789);
    EXPECT_EQ(sc1.nivel(pos0), 6);
    EXPECT_EQ(sc1.nivel(pos1), 6);
    EXPECT_EQ(sc1.nivel(pos2), 4);
    EXPECT_EQ(sc1.nivel(pos3), 4);
    EXPECT_EQ(sc1.nivel(pos4), 3);
    EXPECT_EQ(sc1.nivel(pos5), 4);
    EXPECT_EQ(sc1.nivel(pos6), 3);
    EXPECT_EQ(sc1.nivel(pos7), 4);
    EXPECT_EQ(sc1.nivel(pos8), 4);
    EXPECT_EQ(sc1.nivel(pos9), 7);
}

TEST_F(SimCityTest, unir_partidas_y_construir) {
    aed2_SimCity sc1(m1);
    aed2_SimCity sc2(m2);
    sc1.agregarComercio(pos0);
    sc1.agregarCasa(pos5);
    sc1.avanzarTurno();
    sc1.agregarCasa(pos6);
    sc1.avanzarTurno();
    sc1.agregarComercio(pos4);
    sc2.agregarCasa(pos8);
    sc2.agregarComercio(pos2);
    sc2.avanzarTurno();
    sc1.unir(sc2);
    sc1.agregarCasa(pos7);
    sc1.agregarComercio(pos1);
    sc1.avanzarTurno();
    sc1.agregarComercio(pos3);
    sc1.agregarCasa(pos9);
    sc1.avanzarTurno();

    compararMapas(sc1.mapa(), m12);
    EXPECT_FALSE(sc1.huboConstruccion());
    EXPECT_EQ(sc1.antiguedad(), 4);
    EXPECT_EQ(sc1.popularidad(), 1);
    EXPECT_EQ(sc1.comercios(), posiciones01234);
    EXPECT_EQ(sc1.casas(), posiciones56789);
    EXPECT_EQ(sc1.nivel(pos0), 4);
    EXPECT_EQ(sc1.nivel(pos1), 2);
    EXPECT_EQ(sc1.nivel(pos2), 4);
    EXPECT_EQ(sc1.nivel(pos3), 3);
    EXPECT_EQ(sc1.nivel(pos4), 3);
    EXPECT_EQ(sc1.nivel(pos5), 4);
    EXPECT_EQ(sc1.nivel(pos6), 3);
    EXPECT_EQ(sc1.nivel(pos7), 2);
    EXPECT_EQ(sc1.nivel(pos8), 3);
    EXPECT_EQ(sc1.nivel(pos9), 1);
}

TEST_F(SimCityTest, union_multiple_vacia) {
    aed2_SimCity sc1(m1);
    aed2_SimCity sc2(m2);
    aed2_SimCity sc3(m3);
    aed2_SimCity sc4(m4);
    sc1.unir(sc2);
    sc3.unir(sc4);
    sc1.unir(sc3);

    compararMapas(sc1.mapa(), m1234);
    EXPECT_FALSE(sc1.huboConstruccion());
    EXPECT_EQ(sc1.antiguedad(), 0);
    EXPECT_EQ(sc1.popularidad(), 3);
    EXPECT_TRUE(sc1.comercios().empty());
    EXPECT_TRUE(sc1.casas().empty());
}

TEST_F(SimCityTest, union_multiple) {
    aed2_SimCity sc1(m1);
    aed2_SimCity sc2(m2);
    aed2_SimCity sc3(m3);
    aed2_SimCity sc4(m4);
    sc1.agregarComercio(pos0);
    sc1.avanzarTurno();
    sc1.agregarCasa(pos8);
    sc1.agregarComercio(pos2);
    sc1.avanzarTurno();
    sc2.agregarCasa(pos6);
    sc2.avanzarTurno();
    sc2.agregarComercio(pos5);
    sc2.agregarComercio(pos8);
    sc4.agregarCasa(pos9);
    sc4.avanzarTurno();
    sc4.agregarCasa(pos5);
    sc4.avanzarTurno();
    sc4.agregarComercio(pos8);
    sc4.avanzarTurno();
    sc4.agregarComercio(pos4);
    sc4.avanzarTurno();
    sc1.unir(sc2);
    sc1.avanzarTurno();
    sc3.unir(sc4);
    sc3.agregarComercio(pos6);
    sc1.unir(sc3);
    sc1.agregarComercio(pos1);
    sc1.agregarCasa(pos7);
    sc1.avanzarTurno();
    sc1.agregarComercio(pos3);

    compararMapas(sc1.mapa(), m1234);
    EXPECT_TRUE(sc1.huboConstruccion());
    EXPECT_EQ(sc1.antiguedad(), 5);
    EXPECT_EQ(sc1.popularidad(), 3);
    EXPECT_EQ(sc1.comercios(), posiciones01234);
    EXPECT_EQ(sc1.casas(), posiciones56789);
    EXPECT_EQ(sc1.nivel(pos0), 4);
    EXPECT_EQ(sc1.nivel(pos1), 1);
    EXPECT_EQ(sc1.nivel(pos2), 4);
    EXPECT_EQ(sc1.nivel(pos3), 3);
    EXPECT_EQ(sc1.nivel(pos4), 3);
    EXPECT_EQ(sc1.nivel(pos5), 4);
    EXPECT_EQ(sc1.nivel(pos6), 3);
    EXPECT_EQ(sc1.nivel(pos7), 1);
    EXPECT_EQ(sc1.nivel(pos8), 3);
    EXPECT_EQ(sc1.nivel(pos9), 5);
}

#ifndef TESTS_H
#define TESTS_H

// Testes funcionais
void testCountingSortWithDifferentStructures();
void testCountingSortCorrectnessSmall();
void testCountingSortCorrectnessLarge();

// Testes de performance
void performanceTest(int size);
void performanceTestAllCases(int size);

// Teste principal
void runAllTests();
#endif
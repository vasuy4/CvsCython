﻿#include <iostream>
# define M_PI           3.14159265358979323846
#include <chrono>


float normal_distribution(float x, float nx = 0, float o = 1)
{
    return (1 / (o * sqrt(2 * M_PI))) * exp(-0.5 * pow(((x - nx) / o), 2));
}

float F(float b, int n = 10000) {
    int a = 0;
    float dx = (b - a) / n;
    float sum = 0;

    float xi;
    for (int i = 0; i < n; i++) {
        xi = a + i * dx;
        sum += normal_distribution(xi) * dx;
    }

    return sum;
}

void calculate(float ei, float es, float nx, float o, int n) {
    float t2 = (es - nx) / o;
    float t1 = (ei - nx) / o;
    float p_suitable_parts = (F(t2, n) - F(t1, n)) * 100;

    t2 = (ei - nx) / o;
    t1 = (nx - 3 * o - nx) / o;
    float p_incorrigible_marriage = (F(t2, n) - F(t1, n)) * 100;

    t2 = (nx + 3 * o - nx) / o;
    t1 = (es - nx) / o;
    float p_fixable_marriage = (F(t2, n) - F(t1, n)) * 100;
}

double test_normal_dist(int cycles)
{
    auto start = std::chrono::high_resolution_clock::now();


    for (int i = 0; i < cycles; i++) {
        calculate(0.006f, 0.055f, 0.026f, 0.012f, 10000);
    }


    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time: " << duration.count() << " seconds" << std::endl;
    return duration.count();
}



int main()
{
    int cycles = 1000;
    int countTests = 10;
    double sum = 0;

    for (int i = 0; i < countTests; i++) {
        sum += test_normal_dist(cycles);
    }
    std::cout << "Current time: " << sum / countTests << std::endl;
}

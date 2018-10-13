#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <cfloat>
#include <assert.h>


#define INFINIT_NUMBER_OF_ROOT 3
#define TEST_NUM 8
#define ONE_ROOT 1
#define TWO_ROOTS 2
#define NO_ROOTS 0
#define ERROR_IN_ROOTS -1


/*!
    Decide  linear equation, if quadratic equation
    was with ax^2 == 0
    @param[in] b - 1st coefficient
    @param[in] c - 2d coefficient

    @param[out] px1 - pointer on root

    @return Result of decide
*/
int SolveLinear(double b, double c, double* px1);
/*!
    @param[in] a - 1st coefficient
    @param[in] b - 2d coefficient
    @param[in] c - 3rd coefficient

    @param[out] x1 - pointer on 1st root
    @param[out] x2 - pointer on 2d root

    @return Result of decide
*/
int SolveSquare(double a, double b, double c,
                double* x1, double* x2);
int Tests();


int main()
{
    printf("# Square Eq Solver v.0.1a\n");
    printf("# Enter a b c: ");

    double a = NAN, b = NAN, c = NAN;
    int num_args = scanf("%lg %lg %lg", &a, &b, &c);
    if(num_args != 3)
    {
        printf("ERROR: not double arguments");
    }

    double x1 = NAN, x2 = NAN;
    int nRoots = SolveSquare(a, b, c, &x1, &x2);
    switch(nRoots)
    {
    case ONE_ROOT:
        printf("There is one root: %lg\n", x1);
        break;
    case TWO_ROOTS:
        printf("There are two roots: %lg, %lg\n", x1, x2);
        break;
    case NO_ROOTS:
        printf("Haven't got roots :(\n");
        break;
    case INFINIT_NUMBER_OF_ROOT:
        printf("Infinity number of roots");
        break;
    default:
        printf("ERROR: Strange nRoots = %d in SolveSquare(%lg, %lg, %lg)\n", nRoots, a, b, c);
        return 1;
        break;
    }
    int test = Tests();
    if (test)
    {
        printf("Results of tests is bad");
    }
    return 0;
}

int SolveSquare(double a, double b, double c, double* px1, double* px2)
{
    int nRoots = 0;
    double quad_discriminant = NAN;
    if(!std::isfinite(a) &&
        !std::isfinite(b) && !std::isfinite(c))
        std::cout << "Args in SolveSquare isn't finite!";
    /*assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));*/


    assert(px1 != NULL);
    assert(px2 != NULL);
    if(a == 0)
    {
        return SolveLinear(b, c, px1);
    }
    else
    {
        quad_discriminant = b*b - 4*a*c;
        if(quad_discriminant > 0)
        {
            int discr = sqrt(quad_discriminant);
            *px1 = (-b + discr)/(2*a);
            *px2 = (-b - discr)/(2*a);
            nRoots = TWO_ROOTS;
        }
        else if(quad_discriminant == 0)
        {
            *px1 = (-b)/(2*a);
            nRoots = ONE_ROOT;
        }
        else if(quad_discriminant < 0){nRoots = NO_ROOTS;}
        else{nRoots = ERROR_IN_ROOTS;}

        return nRoots;
    }
    return -1;
}

int SolveLinear(double b, double c, double* px1)
{
    assert(std::isfinite(b));
    assert(std::isfinite(c));
    assert(px1 != NULL);
    int nRoots = 4;
    if (b == 0)
    {
        if (c == 0){nRoots = INFINIT_NUMBER_OF_ROOT;}
        else{nRoots = NO_ROOTS;}
    }
    else
    {
        *px1 = -c/b;
        nRoots = ONE_ROOT;
    }
    return nRoots;
}

int Tests()
{
    double a_list[TEST_NUM] =   {0,   0,   0,   1,   1,   1,  4,     1};
    double b_list[TEST_NUM] =   {0,   0,   1,   2,   2,   2,  -3,    3};
    double c_list[TEST_NUM] =   {0,   5,   -3,  1,   2,   -3, -1,    2};
    double x1_list[TEST_NUM] =  {NAN, NAN, 3,   -1,  NAN, 1,  1,     -1};
    double x2_list[TEST_NUM] =  {NAN, NAN, NAN, NAN, NAN, -3, -0.25, -2};
    int result_list[TEST_NUM] = {3,   0,   1,   1,   0,   2,  2,     2};
    double x1 = NAN, x2 = NAN;
    int result = -1;

    for(int i = 0; i < TEST_NUM; i++)
    {
        x1 = NAN;
        x2 = NAN;
        result = SolveSquare(a_list[i], b_list[i], c_list[i], &x1, &x2);
        if ((x1_list[i] == x1 ||
             (x1 != x1 && x1_list[i] != x1_list[i])) &&
            (x2_list[i] == x2 ||
             (x2 != x2 && x2_list[i] != x2_list[i]))&&
            result_list[i] == result)
        {
            printf("Test %d - OK\n", i);
        }
        else
        {
            printf("Test %d - Error:\n a = %lg, b = %lg, c = %lg\n Roots: x1 = %lg, x2 = %lg\n Result = %d\n", i, a_list[i], b_list[i], c_list[i], x1, x2, result);
            return 1;
        }
    }
    return 0;
}

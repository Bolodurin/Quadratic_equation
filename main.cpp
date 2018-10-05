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

/*
	Эта строчка - зло. Не юзай ее. А при мне - тем более)
	Скорее всего скоро будет #pragma NO_C_PLUSPLUS
 */
using namespace std;


/* 
	Долюбиться до перевода - дело последнее, но все же solve. 
	И строчки не должны быть слишком длинными, что не помещается
	у меня в окошке - много)
	Вообще говоря, 80 символов, за них лучше стараться не 
	вылезать.
 */
/*!
    Decide  linear equation, if quadratic equation 
    was with ax^2 == 0


//	Не слепляй все в непрерывный текст. Ставь пустые строки,
//	они только читабельность улучшат. Но тоже с умом.

// Рядом с параметрами еще пиши [in], [out], [in, out], чтобы
// было понятно, что с ними происходит и зачем они.

    @param b - 1st coefficient
    @param c - 2d coefficient
    @param px1 - pointer on root

    @return Result of decide
*/

/*
	И здесь пустые строки тоже, не слепляй
 */

int SolveLinear(double b, double c, double* px1);
/*!
    @param a - 1st coefficient
    @param b - 2d coefficient
    @param c - 3rd coefficient

    @param x1 - pointer on 1st root
    @param x2 - pointer on 2d root

    @return Result of decide
*/

/*
	Много параметров - сноси строчку. Тем более, что тут 
	все сносится красиво - отдельно коэффициенты, отдельно
	корни, у них и типы различаются. Все как надо
 */
int SolveSquare(double a, double b, double c, 
				double* x1, double* x2);

/*
	Тут можно прям честно говорить < int UnitTest() >
 */
int Tests();



int main()
{
/*
	Версии и прочее можно просто оставлять в виде комментов к 
	коду. Это не ошибка, а просто напоминание и комментарий.
	Ну и всякие спецсимволы лучше смотрятся, когда пробел стоит.
	S с решеткой слепляются, не слишком удобно читать.
 */
    printf("# Square Eq Solver v.0.1a\n");
/*
	С ходу ведь не скажешь, что это за а, б и ц. Можно было 
	добавить что-то типа
	"Enter coefficients for square equation\n"
	"ax^2 + bx + c = 0\n"
 */
    printf("# Enter a b c: ");

    double a = NAN, b = NAN, c = NAN;
    scanf("%lg %lg %lg", &a, &b, &c);

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

/*
	"... и вот, через час работы мы получаем ответ и сообщение:
	тесты не пройдены, ответ считать недействительным."

	Что толку от тестов после запуска? Наоборот, прога начинает
	работу с самотестирования, еще до печати приглашения ко вводу.

	Ну и можно просто писать:
	<
	if (UnitTest())
	{
		fprintf(stderr, "Function doesn't work correctly\n");
		return EXIT_FAILURE;
	}
	>
 */
    int test = Tests();
    if (test)
    {
        printf("Results of tests is bad");
    }
    return 0;
}

int SolveSquare(double a, double b, double c, 
				double* px1, double* px2)
{
/*
	Не надо объявлять все переменные в начале функции. Так неясно,
	зачем они нужны, несмотря на их названия. Огромный плюс С - 
	возможность объявления переменных в любом месте кода, чем надо
	пользоваться. Понадобилась переменная - ввел, а до этого не
	стоит ее объявлять.
 */
    int nRoots = 0;
    double quad_discriminant = NAN;

/*
	Ассерты - хорошо, но они работают только в DEBUG сборке. В
	RELEASE они просто пропадают, а проверка на финитность 
	необходима в рантайме любой версии. Так что 
	std::isfinite надо проверять в ифах. А вот проверку на 
	ненулевость указателей в ассертах, да. Стоит отличать 
	ошибки, связанные с тупизмом конечного пользователя, и 
	ошибки, связанные с программистом. Пользователь никогда 
	не сможет сделать так, что указатели станут нулевыми тут - 
	это косяк программиста. Такие вещи проверять ассертами,
	но реальные проблемы рантайма - ифами.
 */
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    assert(px1 != NULL);
    assert(px2 != NULL);
/*
	И еще проверку на px1 != px2 - не хотелось бы перетереть 
	вторым корнем первый
 */

    if(a == 0)
    {
        return SolveLinear(b, c, px1);
    }
    else
    {
        quad_discriminant = b*b - 4*a*c;
/*
	Прога на корректном вводе упадет здесь. Ну, точнее, ответ
	выдаст не тот. Проверочка нужна, пока спойлерить не буду,
	предоставляю возможность подумкать :)
 */
        if(quad_discriminant > 0)
        {
            int discr = sqrt(quad_discriminant);
            *px1 = (-b + discr)/(2*a);
            *px2 = (-b - discr)/(2*a);
            nRoots = 2;
        }
        else if(quad_discriminant == 0)
        {
            *px1 = (-b)/(2*a);
            nRoots = 1;
        }
        else if(quad_discriminant < 0)
        {
            nRoots = 0;
        }
        else
        {
/*
	Функция решения квадратного уравнения не печатает на 
	стандартный вывод. Ты можешь делать свои логи, тогда
	допустим, но это другая история. В случае ошибки функция
	молча возвращает либо просто заявление об ошибке, либо,
	что приятнее, код ошибки. Тут можно задефайнить что-то
	типа ERR_LOL_WTF и его вернуть. 
 */
            printf("Sorry, ERROR with discriminant\n");
            nRoots = -1;
        }
        return nRoots;
    }
/*
	Выглядит стремно. Не говоря о том, что NULL в С++ - это
	не лучшая идея, ибо тут есть nullptr, кто в некотором 
	смысле лучше. И раз у тебя инты, то и верни инт нормальный,
	зачем такие извращения?
 */
    return int(NULL);
}

int SolveLinear(double b, double c, double* px1)
{
/*
	Та же ботва, что и в <SolveSquare()>
 */
    assert(std::isfinite(b));
    assert(std::isfinite(c));

    assert(px1 != NULL);
    
    int nRoots = 4;
    if (b == 0)
    {
/*
	Когда у тебя одно действие в теле ифа, цикла и тд, его есть
	смысл писать на той же строке. Исключение - понятное дело,
	когда линные строчки выходят, тогда да, сноси на следующую.
 */
        if (c == 0)	nRoots = INFINIT_NUMBER_OF_ROOT;
        else		nRoots = 0;
    }
    else
    {
        *px1 = -c/b;
        nRoots = 1;
    }
    return nRoots;
}

int Tests()
{
/*
	Когда много инициализаций последовательных, старайся 
	выравнивать их как-то. По <=> или еще как-то так
 */
    double   a_list[TEST_NUM] = {0,   0,   0,   1,   1,    1,  4,  1};
    double   b_list[TEST_NUM] = {0,   0,   1,   2,   2,    2, -3,  3};
    double   c_list[TEST_NUM] = {0,   5,  -3,   1,   2,   -3, -1,  2};
    double x 1_list[TEST_NUM] = {NAN, NAN, 3,  -1,   NAN,  1,  1, -1};
    double x 2_list[TEST_NUM] = {NAN, NAN, NAN, NAN, NAN, -3, -0.25, -2};
    int result_list[TEST_NUM] = {3,   0,   1,   1,   0,    2,  2,  2};
    
    double x1 = NAN, x2 = NAN;
    int result = -1;

    for(int i = 0; i < TEST_NUM; i++)
    {
        x1 = NAN;
        x2 = NAN;
/*
	Вот тут определенно слишком длинные строчки. Прямо перебор от
	слова "совсем". 
 */
        result = SolveSquare(a_list[i], b_list[i], c_list[i], 
        					 &x1, &x2);
        if ((x1_list[i] == x1 || 
        	(x1 != x1 && x1_list[i] != x1_list[i])) && 
        	(x2_list[i] == x2 || 
        	(x2 != x2 && x2_list[i] != x2_list[i])) && 
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

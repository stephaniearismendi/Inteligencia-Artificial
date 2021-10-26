#include <iostream>
#include "town.h"

#define RESET "\033[0m"
#define BLACK "\033[30m"              /* Black */
#define RED "\033[31m"                /* Red */
#define GREEN "\033[32m"              /* Green */
#define YELLOW "\033[33m"             /* Yellow */
#define BLUE "\033[34m"               /* Blue */
#define MAGENTA "\033[35m"            /* Magenta */
#define CYAN "\033[36m"               /* Cyan */
#define WHITE "\033[37m"              /* White */
#define BOLDBLACK "\033[1m\033[30m"   /* Bold Black */
#define BOLDRED "\033[1m\033[31m"     /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m"   /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m"    /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m"    /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m"   /* Bold White */

int main(void)
{
    town mapa;

    // Tipo de funcionamiento
    int decision = 0;
    while ((decision != 1) && (decision != 2))
    {
        system("clear");
        std::cout << YELLOW << "\n--------------------------------------------------------\n"
                  << RESET;
        std::cout << BOLDCYAN << "\n\t¿Desea introducir los obstaculos de manera manual o aleatoria?\n";
        std::cout << BOLDCYAN << "\n\t1. MANUAL\n";
        std::cout << BOLDCYAN << "\n\t2. ALEATORIA\n\n";
        std::cout << BOLDCYAN << "\n\tIMPORTANTE: los obstáculos, de ser establecidos manualmente, se deberán adjuntar en un fichero.\n";
        std::cout << GREEN << "\n\t Su elección >>\t" << BOLDGREEN << RESET;
        std::cin >> decision;
        std::cout << RESET;
        std::cout << YELLOW << "\n--------------------------------------------------------\n"
                  << RESET;
    }

    // Eleccion
    if (decision == 1)
    {
        // Ficheros
        bool ok = false;
        while (!ok)
        {
            std::string filename;
            std::cout << YELLOW << "\n\t Introduzca el nombre del fichero : " << RESET;
            std::cin >> filename;
            std::cout << RESET;
            ok = mapa.genMapFile(filename);
        }
        mapa.print();
    }
    else
    {
        // Generacion automatica
        // M x N
        int width = 0, height = 0;
        while (width <= 0 || height <= 0)
        {
            system("clear");
            std::cout << YELLOW << "\n--------------------------------------------------------\n"
                      << RESET;
            std::cout << BOLDCYAN << "\n\tIntroduzca la altura y la anchura del mapa.\n";
            std::cout << YELLOW << "\n--------------------------------------------------------\n"
                      << RESET;
            std::cout << GREEN << "\n\t Anchura >>\t" << BOLDGREEN << RESET;
            std::cin >> width;
            std::cout << GREEN << "\n\t Altura >>\t" << BOLDGREEN << RESET;
            std::cin >> height;
            std::cout << RESET;
        }
        mapa.setSize(width, height);

        // Porcentaje de obstaculos
        int percentage = 0;
        while (decision == 2 && (percentage <= 0 || percentage > 100))
        {
            std::cout << YELLOW << "\n\t Introduzca un porcentaje de obstáculos ( 0 - 100 % ) : " << RESET;
            std::cin >> percentage;
            std::cout << RESET;
            mapa.genObstacleRand(percentage);
        }

        // Posicion inicial
        int init_pos_x = 0, init_pos_y = 0;
        bool ok = false;
        while (init_pos_x <= 0 || init_pos_y <= 0 || ok == false)
        {
            system("clear");
            mapa.print();
            std::cout << YELLOW << "\n\n--------------------------------------------------------\n"
                      << RESET;
            std::cout << BOLDCYAN << "\n\tIntroduzca la posicion X e Y de inicio.\n";
            std::cout << YELLOW << "\n--------------------------------------------------------\n"
                      << RESET;
            std::cout << GREEN << "\n\t Pos X >>\t" << BOLDGREEN << RESET;
            std::cin >> init_pos_x;
            std::cout << GREEN << "\n\t Pos Y >>\t" << BOLDGREEN << RESET;
            std::cin >> init_pos_y;
            std::cout << RESET;
            ok = mapa.setInitialPos(init_pos_x, init_pos_y);
        }

        // Posicion final
        int end_pos_x = 0, end_pos_y = 0;
        ok = false;
        while (end_pos_x <= 0 || end_pos_y <= 0 || ok == false)
        {
            system("clear");
            mapa.print();
            std::cout << YELLOW << "\n\n--------------------------------------------------------\n"
                      << RESET;
            std::cout << BOLDCYAN << "\n\tIntroduzca la posicion X e Y de destino.\n";
            std::cout << YELLOW << "\n--------------------------------------------------------\n"
                      << RESET;
            std::cout << GREEN << "\n\t Pos X >>\t" << BOLDGREEN << RESET;
            std::cin >> end_pos_x;
            std::cout << GREEN << "\n\t Pos Y >>\t" << BOLDGREEN << RESET;
            std::cin >> end_pos_y;
            std::cout << RESET;
            ok = mapa.setEndPos(end_pos_x, end_pos_y);
        }
        system("clear");

        mapa.print();
    }
    mapa.solve();
    system("clear");
    mapa.printSol();
}
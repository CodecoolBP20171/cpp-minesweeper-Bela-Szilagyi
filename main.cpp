#include <iostream>
//#include <time.h>
#include <ctime>

namespace {
    class Minesweeper {
    public:
        Minesweeper(const size_t width, const size_t height)
                : width(width), height(height),
                  table(new char[width * height]) {
            fillTable();
        }

        /* In a real implementation there would also be a
         * - copy constructor
         * - assignment operator
         * - move constructor
         * - move assignment operator
         * We will learn about them later
         */

        virtual ~Minesweeper() {
            delete[] table;
        }

        void countNeighbours() {
            // step 2 goes here

            int tableNumbers[width*height];

            for (int i = 0; i < width*height; i++) {
                tableNumbers[i] = 0;
            }

            int neighbour;
            for (int i = 0; i < width*height; i++) {

                //N
                neighbour = i - width;
                if (i >= (int)width) {
                    if (table[neighbour] == '*') tableNumbers[i] += 1;
                }

                //NE
                neighbour = i - width + 1;
                if (i >= (int)width && (i+1) % (int)width != 0) {
                    if (table[neighbour] == '*') tableNumbers[i] += 1;
                }

                //E
                neighbour = i + 1;
                if (i < (int)width*(int)height && (i+1) % (int)width != 0) {
                    if (table[neighbour] == '*') tableNumbers[i] += 1;
                }

                //SE
                neighbour = i + width + 1;
                if (i < (int)width*(int)height-(int)width && (i+1) % (int)width != 0) {
                    if (table[neighbour] == '*') tableNumbers[i] += 1;
                }

                //S
                neighbour = i + width;
                if (i < (int)width*(int)height-(int)width) {
                    if (table[neighbour] == '*') tableNumbers[i] += 1;
                }

                //SW
                neighbour = i + width - 1;
                if (i < (int)width*(int)height-(int)width &&
                        i % (int)width != 0 &&
                        i != 0) {
                    if (table[neighbour] == '*') tableNumbers[i] += 1;
                }

                //W
                neighbour = i - 1;
                if (i > 0 && i % (int)width != 0) {
                    if (table[neighbour] == '*') tableNumbers[i] += 1;
                }

                //NW
                neighbour = i - width - 1;
                if (i > (int)width && i % (int)width != 0) {
                    if (table[neighbour] == '*') tableNumbers[i] += 1;
                }

            }

            for (int i = 0; i < width*height; i++) {
                table[i] = std::to_string(tableNumbers[i])[0];
            }
        }

        void printTable() const {
            // step 3 goes here

            std::cout<<std::endl;
            for (int h = 0; h < height; h++) {
                for (int w = 0; w < width; w++) {
                    std::cout<<h*width + w;
                }
                std::cout<<std::endl;
            }
            std::cout<<std::endl;

            std::cout<<std::endl;
            for (int h = 0; h < height; h++) {
                for (int w = 0; w < width; w++) {
                    std::cout<<table[h*width + w];
                }
                std::cout<<std::endl;
            }
            std::cout<<std::endl;
        }

    private:
        void fillTable() {
            // step 1 goes here
            int random;
            std::srand(std::time(NULL));
            for(int i = 0; i < width*height; i++) {
                random = std::rand()%2;
                if (random) {
                    table[i] = '*';
                } else {
                    table[i] = '.';
                }
            }
        }

        const size_t width, height;
        char *table;
    };
}

int main() {
    try {
        //Minesweeper ms(100, 50);
        Minesweeper ms(4, 3);
        ms.printTable();
        ms.countNeighbours();
        ms.printTable();
    } catch (const std::bad_alloc &e) {
        std::cerr << "Couldn't allocate enough memory for minesweeper table" << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}
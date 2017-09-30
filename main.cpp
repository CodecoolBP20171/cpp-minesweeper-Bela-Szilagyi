#include <iostream>
//#include <time.h>
#include <ctime>

namespace {
    class Minesweeper {
    public:
        Minesweeper(const size_t width, const size_t height)
                : width(width), height(height),
                  tableNeighbours(new int[width * height]),
                  tableReveal(new int[width * height]),
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

            for (int i = 0; i < width * height; i++) {
                tableNeighbours[i] = 0;
            }

            for (int i = 0; i < width * height; i++) {
                tableNeighbours[i] = countNeighbourOf(i);
            }

            /*
            for (int i = 0; i < width * height; i++) {
                table[i] = std::to_string(tableNeighbours[i])[0];
            }
             */
        }

        int countNeighbourOf(int i) {
            int neighbour;
            int result = 0;
            //N
            neighbour = i - width;
            if (i >= (int)width) {
                if (table[neighbour] == '+') ++result;
            }

            //NE
            neighbour = i - width + 1;
            if (i >= (int)width && (i+1) % (int)width != 0) {
                if (table[neighbour] == '+') ++result;
            }

            //E
            neighbour = i + 1;
            if (i < (int)width*(int)height && (i+1) % (int)width != 0) {
                if (table[neighbour] == '+') ++result;
            }

            //SE
            neighbour = i + width + 1;
            if (i < (int)width*(int)height-(int)width && (i+1) % (int)width != 0) {
                if (table[neighbour] == '+') ++result;
            }

            //S
            neighbour = i + width;
            if (i < (int)width*(int)height-(int)width) {
                if (table[neighbour] == '+') ++result;
            }

            //SW
            neighbour = i + width - 1;
            if (i < (int)width*(int)height-(int)width &&
                    i % (int)width != 0 &&
            i != 0) {
                if (table[neighbour] == '+') ++result;
            }

            //W
            neighbour = i - 1;
            if (i > 0 && i % (int)width != 0) {
                if (table[neighbour] == '+') ++result;
            }

            //NW
            neighbour = i - width - 1;
            if (i > (int)width && i % (int)width != 0) {
                if (table[neighbour] == '+') ++result;
            }

            return result;
        }

        void printTable() const {
            // step 3 goes here
            std::cout<<std::endl;
            for (int h = 0; h < height; h++) {
                for (int w = 0; w < width; w++) {
                    std::cout<<table[h*width + w];
                }
                std::cout<<std::endl;
            }
            std::cout<<std::endl;
        }

        void printNeighbours() const {
            // step 3 goes here
            std::cout<<std::endl;
            for (int h = 0; h < height; h++) {
                for (int w = 0; w < width; w++) {
                    std::cout<<tableNeighbours[h*width + w];
                }
                std::cout<<std::endl;
            }
            std::cout<<std::endl;
        }

        void fillRevealTable() {
            for(int i = 0; i < width*height; i++) {
                tableReveal[i] = -1;
            }
        }

        void reveal(int place) {

            /*
            for (int i = 0; i < width*height; i++) std::cout<<tableReveal[i];
            std::cout<<std::endl;
            */

            if (tableReveal[place] == -1) {
                int reveal = countNeighbourOf(place);
                tableReveal[place] = reveal;
                if (reveal == 0) revealNeighbourOf(place);
            }

            /*
            for (int i = 0; i < width*height; i++) std::cout<<tableReveal[i];
            std::cout<<std::endl;
             */
        }

        void revealNeighbourOf(int i) {
            int neighbour;
            int result = 0;
            //N
            neighbour = i - width;
            if (i >= (int)width) {
                reveal(neighbour);
            }

            //NE
            neighbour = i - width + 1;
            if (i >= (int)width && (i+1) % (int)width != 0) {
                reveal(neighbour);
            }

            //E
            neighbour = i + 1;
            if (i < (int)width*(int)height && (i+1) % (int)width != 0) {
                reveal(neighbour);
            }

            //SE
            neighbour = i + width + 1;
            if (i < (int)width*(int)height-(int)width && (i+1) % (int)width != 0) {
                reveal(neighbour);
            }

            //S
            neighbour = i + width;
            if (i < (int)width*(int)height-(int)width) {
                reveal(neighbour);
            }

            //SW
            neighbour = i + width - 1;
            if (i < (int)width*(int)height-(int)width &&
                i % (int)width != 0 &&
                i != 0) {
                reveal(neighbour);
            }

            //W
            neighbour = i - 1;
            if (i > 0 && i % (int)width != 0) {
                reveal(neighbour);
            }

            //NW
            neighbour = i - width - 1;
            if (i > (int)width && i % (int)width != 0) {
                reveal(neighbour);
            }
        }

        void printReveal() const {
            std::cout<<std::endl;
            std::cout<<"\033[1;34m";
            for (int i = 0; i < width*2+1; i++) std::cout<<"-";
            std::cout<<"\033[0m";
            std::cout<<std::endl;
            for (int h = 0; h < height; h++) {
                for (int w = 0; w < width; w++) {
                    std::cout<<"\033[1;34m|\033[0m";
                    if (tableReveal[h*width+w] != -1) {
                        std::cout<<tableReveal[h*width+w];
                    } else {
                        std::cout<<"X";
                    }
                }
                std::cout<<"\033[1;34m|\033[0m"<<std::endl;
            }
            std::cout<<"\033[1;34m";
            for (int i = 0; i < width*2+1; i++) std::cout<<"-";
            std::cout<<"\033[0m";
            std::cout<<std::endl;
        }

    private:
        void fillTable() {
            // step 1 goes here
            int random;
            std::srand(std::time(NULL));
            for(int i = 0; i < width*height; i++) {
                random = std::rand()%5+1;
                if (random > 4) {
                    table[i] = '+';
                } else {
                    table[i] = '-';
                }
            }
        }

        const size_t width, height;
        int *tableNeighbours;
        int *tableReveal;
        char *table;
    };
}

int main() {
    try {
        //Minesweeper ms(100, 50);
        Minesweeper ms(6, 5);
        ms.printTable();
        ms.countNeighbours();
        ms.printNeighbours();
        //for (int i = 0; i < 30; i++) ms.reveal(i);
        ms.fillRevealTable();
        ms.reveal(15);
        ms.printReveal();
    } catch (const std::bad_alloc &e) {
        std::cerr << "Couldn't allocate enough memory for minesweeper table" << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}
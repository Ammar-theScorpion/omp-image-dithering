#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include <sys/time.h>
#include <stdlib.h>
#include <ctime>
double GetWallTime() {
    struct timeval tp;
    int rtn = gettimeofday(&tp, NULL);
    return ((double) tp.tv_sec + (1.e-6)*tp.tv_usec);
}

class File {
public:
    File(const std::string& file_path) :
        file_path(file_path) {
        check_file(file_path);
    }
    File(const std::string& img_path, const std::string& mask_path, const std::string& save_path) :
        file_path(img_path), mask_path(mask_path), save_path(save_path) {
        check_file(img_path); check_file(mask_path);
        parse_file();
    }
    void parse_file() {
        std::ifstream fstream1(mask_path);
        int mask[9];
        char c;
        int i0 = 0;
        while (fstream1.get(c)) {
            if (c >= '0' && c <= '9')
                mask[i0++] = c - '0';
        }
        fstream1.close();
        std::string line;
        std::ifstream fstream(file_path);
        std::getline(fstream, line);


        int row = std::stoi(line.substr(0, line.find(' ')));
        std::string f = line.substr(line.find('\t'), line.length());
        int col = 0;
        for (char c : f) {
            if (c >= '0' && c <= '9') {
                col = 10 * col + (c - '0');
            }

        }
        int i = 0;
        int color = 0;
        short iterate = 3;
        std::stringstream ss;
        ostream.open(save_path);
        while (fstream.get(c)) {
            if (c >= '0' && c <= '9') {
                color = 10 * color + (c - '0');
                if (color > 255) {
                    std::cout << "Error: not a valid format\n";
                    exit(0);
                }
            }
            else {
                color /= 28;
                if (color > mask[i])
                    ss << "1 ";
                else
                    ss << "0 ";
                color = 0;
                i = (i + 1) % iterate;
                if (iterate - i > 4)
                    i = iterate - 3;
            }
            if (c == '\n') {
                iterate += 3;
                if (iterate == 12) {
                    iterate = 3;
                    i = 0;
                }
                else
                    i = iterate - 3;
                ss << std::endl;
            }
        }
        ostream << ss.str() << std::endl;
        ostream.close();
    }
    void check_file(const std::string& file_name) {
        fstream.open(file_name);
        if (!fstream.is_open()) {
            std::cout << file_name << " does not exist\n";
        }fstream.close();
    }
private:
    int* get_mask() {
   
    }
    std::string file_path;
    std::string mask_path;
    std::string save_path;
    std::ifstream fstream;
    std::ofstream ostream;
    std::ofstream ostreams;
};

int main(int argc, char** argv) {
    std::string mask_file;
    std::string img_file;
    std::string save_file;
    try {

          if (argc != 4)
               throw("unvaild command line: excpected 3 parameters");
           img_file = argv[1];
           mask_file = argv[2];
           save_file = argv[3];
        double start_time = GetWallTime();
        File file = File(img_file, mask_file, save_file);
        double finish = GetWallTime();
        std::cout << "Time: " << finish-start_time << std::endl;
    }
    catch (char const* string) {
        std::cout << string;
    }
}
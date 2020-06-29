#include <fstream>
#include <inja.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

/* enum mode represents the operational modes of the program
 * normalmode: template and data file paths are given
 * templatemode: template file path is given but data will come from stdin
 * datamode: data file path is given but template will come from stdin
 */ 
enum mode {normalmode, templatemode, datamode};

int main(int argc, char *argv[]){
    /* argv[1] = mode: ["n"|"t"|"d"] (normal/template/data)
     * argv[2] = outfile specified: "y" for yes, anything else for no
     * argv[3] = template: path to template file or undefined if mode is "d"
     * argv[4] = data: path to data file or undefined if mode is "t"
     * argv[5] = outfile: path to out file or undefined if argv[2] == "n"
     */

    if(argc != 6){
        std::cerr << "Invalid argument count...\n" << std::endl;
        return 1;
    }

    // Determine operation mode
    char mode_char = argv[1][0];
    enum mode operation_mode;
    if(mode_char == 'n'){
        operation_mode = normalmode;
    } else if(mode_char == 't'){
        operation_mode = templatemode;
    } else if(mode_char == 'd'){
        operation_mode = datamode;
    } else {
        std::cerr << "Invalid mode code...\n" << std::endl;
        return 1;
    }

    // Open necessary files and assign to templatein and datain
    std::istream *templatein, *datain;
    std::ifstream templateinfile, datainfile;
    if(operation_mode == normalmode){
        templateinfile.open(argv[3]);
        datainfile.open(argv[4]);
        if(templateinfile.fail()){
            std::cerr << "Problem reading file: " + std::string{argv[3]} << std::endl;
            return 1;
        }
        if(datainfile.fail()){
            std::cerr << "Problem reading file: " + std::string{argv[4]} << std::endl;
            return 1;
        }
        templatein = &templateinfile;
        datain = &datainfile;
    } else if (operation_mode == templatemode){
        templateinfile.open(argv[3]);
        if(templateinfile.fail()){
            std::cerr << "Problem reading file: " + std::string{argv[3]} << std::endl;
            return 1;
        }
        templatein = &templateinfile;
        datain = &std::cin;
    } else if (operation_mode == datamode){
        datainfile.open(argv[4]);
        if(datainfile.fail()){
            std::cerr << "Problem reading file: " + std::string{argv[4]} << std::endl;
            return 1;
        }
        datain = & datainfile;
        templatein = &std::cin;
    }


    // Open outfile if it is specified and assign to out
    bool outfile_is_specified = (argv[2][0] == 'y') && (argv[2][1] == '\0') ? true : false;
    std::ostream *out;
    std::ofstream outfile;
    if(outfile_is_specified){
        outfile.open(argv[5]);
        out = &outfile;
    } else{
        out = &std::cout;
    }

    nlohmann::json data;
    *datain >> data;
    
    std::stringstream strStream;
    strStream << (*templatein).rdbuf();
    std::string templatestr = strStream.str();

    inja::render_to(*out, templatestr, data);

    return 0;
}

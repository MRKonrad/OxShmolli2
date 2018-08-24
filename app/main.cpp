/*!
 * \file main.cpp
 * \author Konrad Werys
 * \date 2018/07/24
 */

#include <iostream>

#include "CmakeConfigForOxShmolli2.h"
#include "OxShmolli2.h"
#include "OxShmolli2Options.h"

/**
 * main
 * Try tests/testData/Hcmr_Phantom_1916_Shmolli_192i_e11_fileList.yaml
 * @return always 0
 */
int main(int argc, char* argv[]) {

    if (argc != 2){
        printf("\nUse: OxShmolliExe(<input_file.yaml>). Please see examples in testData\n");
        Ox::OxShmolli2Options<double>::printAvailable();

//        std::string inputFileName("tests/testData/Calculator_Shmolli_MOLLI_Volunteer_001_45_fileList.yaml");
//        Ox::OxShmolli2<double> OxShmolli2_object(inputFileName);
//        OxShmolli2_object._opts->printCurrent();
//        OxShmolli2_object.readAndSort();
//        OxShmolli2_object.calculate();
//        OxShmolli2_object.exportToDicom();
//        OxShmolli2_object.visualise();
    }

    else if (argc == 2){
        // process only if ITK is available
#ifdef USE_ITK
        std::string inputFileName(argv[1]);
        Ox::OxShmolli2<double> OxShmolli2_object(inputFileName);
        OxShmolli2_object._opts->printCurrent();
        OxShmolli2_object.readAndSort();
        OxShmolli2_object.calculate();
        OxShmolli2_object.exportToDicom();
        OxShmolli2_object.visualise();
#else
        throw std::runtime_error("You need ITK to run the executable");
#endif

    }

    printf("Thank you for using!\n");
    printf("Konrad Werys 2018\n");
    printf("konradwerys2@gmail.com\n\n");

    return 0;
}


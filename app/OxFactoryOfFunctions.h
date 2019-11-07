/*!
 * \file OxFactoryOfFunctions.h
 * \author Konrad Werys
 * \date 2018/08/18
 */

#ifndef Tomato_OXFACTORYOFFUNCTIONS_H
#define Tomato_OXFACTORYOFFUNCTIONS_H

#include "CmakeConfigForTomato.h"

#include "OxFunctionsT1ThreeParam.h"
#include "OxFunctionsT1TwoParam.h"
#include "OxFunctionsT1Shmolli.h"
#include "OxFunctionsT2ThreeParam.h"

namespace Ox {

    template<typename TYPE>
    struct TomatoOptions;


    static const char *functionsTypeNames[] = {
            "FunctionsThreeParam",
            "FunctionsTwoParam",
            "FunctionsShmolli",
            "FunctionsT2ThreeParam"
    };

    enum functionsType_t {
        FunctionsThreeParam = 0,
        FunctionsTwoParam = 1,
        FunctionsShmolli = 2,
        _FunctionsT2ThreeParam = 3,
        lastFunctorType = _FunctionsT2ThreeParam
    };

    static int functionsAvailability[] = {
            1, //FunctionsThreeParam
            1, //FunctionsTwoParam
            1, // FunctionsShmolli
            1  // FunctionsT2ThreeParam
    };

    template<typename TYPE>
    class FactoryOfFunctions {
    public:

        static FunctionsT1<TYPE>* newByFactory(TomatoOptions<TYPE> *opts){
            switch (opts->functions_type){
                case FunctionsThreeParam: {
                    return new FunctionsT1ThreeParam<TYPE>();
                }
                case FunctionsTwoParam: {
                    return new FunctionsT1TwoParam<TYPE>();
                }
                case FunctionsShmolli: {
                    return new FunctionsT1Shmolli<TYPE>();
                }
                case _FunctionsT2ThreeParam: {
                    return new FunctionsT2ThreeParam<TYPE>();
                }
                default:
                    throw std::runtime_error("functions_type not available");
            }
        }

        static void disp(int functions_type = -1){

            if (functions_type >= 0) {
                printf("%-28s%-22s", " functions_type: ", functionsTypeNames[functions_type]);
            }

            printf("options: [ ");

            for (int i = 0; i < lastFunctorType+1; i++){

                if(functionsAvailability[i]){
                    printf("%s ", functionsTypeNames[i]);
                }
            }

            printf("] \n");
        }
    };

} // namespace Ox

#endif //Tomato_OXFACTORYOFFUNCTIONS_H

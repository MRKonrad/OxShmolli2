/*!
 * \file OxFactoryOfFunctions.h
 * \author Konrad Werys
 * \date 2018/08/18
 */

#ifndef Tomato_OXFACTORYOFFUNCTIONS_H
#define Tomato_OXFACTORYOFFUNCTIONS_H

#include "CmakeConfigForTomato.h"

#include "OxFunctionsT1Basic.h"
#ifdef USE_PRIVATE_NR2
#include "OxFunctionsT1CalculatorShmolli.h"
#endif

namespace Ox {

    template<typename TYPE>
    struct TomatoOptions;

#ifdef USE_PRIVATE_NR2
    static const char *functionsTypeNames[] = {
            "FunctionsBasic",
            "FunctionsShmolli",
    };

    enum functionsType_t {
        FunctionsBasic = 0,
        FunctionsShmolli = 1,
        lastFunctorType = FunctionsShmolli
    };
#else
    static const char *functionsTypeNames[] = {
            "FunctionsBasic",
    };

    enum functionsType_t {
        FunctionsBasic = 0,
        lastFunctorType = FunctionsBasic
    };
#endif

    template<typename TYPE>
    class FactoryOfFunctions {
    public:

        static FunctionsT1<TYPE>* newByFactory(TomatoOptions<TYPE> *opts){
            switch (opts->functions_type){
                case FunctionsBasic: {
                    return new FunctionsT1Basic<TYPE>();
                }
#ifdef USE_PRIVATE_NR2
                case FunctionsShmolli: {
                    return new FunctionsT1CalculatorShmolli<TYPE>();
                }
#endif
                default:
                    return 0;
            }
        }
    };

} // namespace Ox

#endif //Tomato_OXFACTORYOFFUNCTIONS_H

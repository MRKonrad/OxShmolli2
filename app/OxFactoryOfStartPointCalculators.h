/*!
 * \file OxFactoryOfStartPointCalculators.h
 * \author Konrad Werys
 * \date 2018/08/18
 */

#ifndef OXSHMOLLI2_OXFACTORYOFStartPointCalculators_H
#define OXSHMOLLI2_OXFACTORYOFStartPointCalculators_H

#include "CmakeConfigForOxShmolli2.h"

#include "OxStartPointCalculatorDefault3Dims.h"
#ifdef USE_PRIVATE_NR2
#include "OxStartPointCalculatorShmolli.h"
#endif

namespace Ox {

    template<typename TYPE>
    struct OxShmolli2Options;

#ifdef USE_PRIVATE_NR2
    static const char *startPointCalculatorsTypeNames[] = {
            "Default",
            "StartPointSHMOLLI"
    };

    enum startPointCalculatorsType_t {
        Default = 0,
        StartPointSHMOLLI = 1,
        lastStartPointCalculatorType = StartPointSHMOLLI
    };
#else
    static const char *startPointCalculatorsTypeNames[] = {
            "Default",
    };

    enum startPointCalculatorsType_t {
        Default = 0,
        lastStartPointCalculatorType = Default
    };
#endif

    template<typename TYPE>
    class FactoryOfStartPointCalculators {
    public:

        static StartPointCalculator<TYPE>* newByFactory(OxShmolli2Options<TYPE> *opts){
            switch (opts->start_point_calc_method){
                case Default: {
                    return new StartPointCalculatorDefault3Dims<TYPE>();
                }
#ifdef USE_PRIVATE_NR2
                case StartPointSHMOLLI: {
                    return new StartPointCalculatorShmolli<TYPE>();
                }
#endif
                default:
                    return 0;
            }
        }
    };

} // namespace Ox

#endif //OXSHMOLLI2_OXFACTORYOFStartPointCalculators_H

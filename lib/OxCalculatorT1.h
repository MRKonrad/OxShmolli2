/*!
 * \file OxCalculator.h
 * \author Konrad Werys
 * \date 2018/07/29
 */

#ifndef OXSHMOLLI2_OXCALCULATORT1_H
#define OXSHMOLLI2_OXCALCULATORT1_H

#include "OxFitter.h"
#include "OxFunctionsT1.h"
#include "OxSignCalculator.h"
#include "OxStartPointCalculator.h"

namespace Ox {

    /**
     * \class CalculatorT1
     * \brief
     * \details
     * @tparam MeasureType
     */
    template< typename MeasureType >
    class CalculatorT1{

    public:
        virtual int PrepareToCalculate() = 0;
        virtual void Calculate() = 0;

    protected:
        Fitter<MeasureType>* _Fitter;
        FunctionsT1<MeasureType>* _Functions;

        SignCalculator<MeasureType>* _SignCalculator;
        StartPointCalculator<MeasureType>* _StartPointCalculator;

        const MeasureType* _InvTimes;
        const MeasureType* _SatTimes;
        const MeasureType* _RepTimes;
        const MeasureType* _RelAcqTimes;
        const MeasureType* _SigMag; // original one
        const MeasureType* _SigPha; // original one
        MeasureType* _Signal; // we will be working with this one
        MeasureType* _Signs;  // we will be working with this one

        // MeasureType* _InitialPoint;
        // MeasureType* _DefaultInitialPoint;
        MeasureType _TRRaverageHB;
        MeasureType _MeanCutOff;
        // signReconMethod_t m_SignReconMethod;
        // calcStartPointMethod_t m_CalcStartPointMethod;


        /**
         * \brief do not forget about the virtual destructor, see
         * https://stackoverflow.com/questions/461203/when-to-use-virtual-destructors
         */
        virtual ~CalculatorT1(){};

    };
} //namespace Ox

#endif //OXSHMOLLI2_OXCALCULATORT1_H

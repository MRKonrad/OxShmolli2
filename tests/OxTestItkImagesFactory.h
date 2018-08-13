/*!
 * \file itkOxTestItkImagesFactory.h
 * \author Konrad Werys
 * \date 2018/07/30
 */

#ifndef OXShmolli2_itkOxTestItkImagesFactory_H
#define OXShmolli2_itkOxTestItkImagesFactory_H

#include "CmakeConfigForOxShmolli2.h"
#ifdef USE_ITK

#include "itkImage.h"
#include "itkImageRegionIteratorWithIndex.h"

#include "OxTestImage.h"


namespace Ox {

    template< typename MeasureType >
    class TestItkImagesFactory {

    public:

        typedef itk::Image< MeasureType, 3 > TImageIn;
        typedef itk::Image< MeasureType, 2 > TImageOut;

        TestItkImagesFactory(int nRows, int nCols, std::vector <std::string> filesPaths);
        virtual ~TestItkImagesFactory();

        virtual int getNSamples() const;
        virtual MeasureType *getInvTimesPtr() ;
        virtual std::vector<MeasureType> getInvTimes() const;

        virtual typename itk::Image< MeasureType, 3 >::Pointer gererateImageMag();
        virtual typename itk::Image< MeasureType, 3 >::Pointer gererateImagePha();
        virtual typename itk::Image< MeasureType, 2 >::Pointer gererateImageResultsMolliA();
        virtual typename itk::Image< MeasureType, 2 >::Pointer gererateImageResultsMolliB();
        virtual typename itk::Image< MeasureType, 2 >::Pointer gererateImageResultsMolliT1star();
        virtual typename itk::Image< MeasureType, 2 >::Pointer gererateImageResultsShmolliA();
        virtual typename itk::Image< MeasureType, 2 >::Pointer gererateImageResultsShmolliB();
        virtual typename itk::Image< MeasureType, 2 >::Pointer gererateImageResultsShmolliT1star();

    protected:

        TestImage<MeasureType>* _testImage;

        typename itk::Image< MeasureType, 2 >::Pointer generateImage2d();
        typename itk::Image< MeasureType, 3 >::Pointer generateImage3d();

        void copyBufferToImage2d(typename itk::Image< MeasureType, 2 >::Pointer image, MeasureType* buffer);
        void copyBufferToImage3d(typename itk::Image< MeasureType, 3 >::Pointer image, MeasureType* buffer);

    };
} // namespace Ox


#include "OxTestItkImagesFactory.hxx"

#endif //USE_ITK

#endif //OXShmolli2_itkOxTestItkImagesFactory_H

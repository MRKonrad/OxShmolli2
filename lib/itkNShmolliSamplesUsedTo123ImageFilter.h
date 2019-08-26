//
//  NShmolliSamplesUsedTo123ImageFilter
//  TomatoLib
//
//  Created by Konrad Werys on 24/11/17.
//  Copyright © 2017 Konrad Werys. All rights reserved.
//

#ifndef TomatoLIB_ITKNShmolliSamplesUsedTo123ImageFilter_H
#define TomatoLIB_ITKNShmolliSamplesUsedTo123ImageFilter_H

#include "CmakeConfigForTomato.h"

#ifdef USE_ITK

#include "tomatolib_export.h"
#include "itkImageToImageFilter.h"
#include "itkImageRegionIterator.h"
#include "itkImageRegionConstIterator.h"

namespace itk {
    template<typename TImage>
    class NShmolliSamplesUsedTo123ImageFilter : public ImageToImageFilter<TImage, TImage> {

    public:
        /** Standard class typedefs. */
        typedef NShmolliSamplesUsedTo123ImageFilter Self;
        typedef ImageToImageFilter<TImage, TImage> Superclass;
        typedef SmartPointer<Self> Pointer;

        /** Method for creation through the object factory. */
        itkNewMacro(Self);

        /** Run-time type information (and related methods). */
        itkTypeMacro(OxColorbarImageFilter, ImageToImageFilter);

        typedef typename TImage::PixelType PixelTypeIn;
        typedef typename TImage::PixelType PixelTypeOut;

    protected:
        /** Constructor. */
        NShmolliSamplesUsedTo123ImageFilter() {};

        /** Destructor. */
        ~NShmolliSamplesUsedTo123ImageFilter() {};

        /** Does the real work. */
        virtual void GenerateData() ITK_OVERRIDE;

    private:
        ITK_DISALLOW_COPY_AND_ASSIGN(NShmolliSamplesUsedTo123ImageFilter); //purposely not implemented

    };
} //namespace ITK

#ifndef TOMATOLIB_COMPILED
#ifndef ITK_MANUAL_INSTANTIATION
#include "itkNShmolliSamplesUsedTo123ImageFilter.txx"
#endif //ITK_MANUAL_INSTANTIATION
#endif //TOMATOLIB_COMPILED

#endif // USE_ITK

#endif //TomatoLIB_ITKNShmolliSamplesUsedTo123ImageFilter_H

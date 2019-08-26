//
//  itkColorbar2DImageFilter
//  TomatoLib
//
//  Created by Konrad Werys on 13/7/17.
//  Copyright © 2017 Konrad Werys. All rights reserved.
//

#ifndef TomatoLIB_ITKColorbar2DImageFilter_H
#define TomatoLIB_ITKColorbar2DImageFilter_H

#include "CmakeConfigForTomato.h"

#ifdef USE_ITK

#include "tomatolib_export.h"
#include "itkImageToImageFilter.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkImageRegionConstIteratorWithIndex.h"

namespace itk {

    /**
     * \class Colorbar2DImageFilter
     * @tparam TImage
     */
    template<typename TImage>
    class Colorbar2DImageFilter : public ImageToImageFilter<TImage, TImage> {

    public:
        /** Standard class typedefs. */
        typedef Colorbar2DImageFilter Self;
        typedef ImageToImageFilter<TImage, TImage> Superclass;
        typedef SmartPointer<Self> Pointer;

        /** Method for creation through the object factory. */
        itkNewMacro(Self);

        /** Run-time type information (and related methods). */
        itkTypeMacro(OxColorbarImageFilter, ImageToImageFilter);

        typedef typename TImage::PixelType PixelTypeIn;
        typedef typename TImage::PixelType PixelTypeOut;

        itkSetMacro(ZerosInsteadOfColorbar, bool);
        itkGetMacro(ZerosInsteadOfColorbar, bool);

    protected:
        /** Constructor. */
        Colorbar2DImageFilter() {
            m_ZerosInsteadOfColorbar = false;
        };

        /** Destructor. */
        ~Colorbar2DImageFilter() {};

        /** Does the real work. */
        virtual void GenerateData() ITK_OVERRIDE;

    private:

        bool m_ZerosInsteadOfColorbar;

        ITK_DISALLOW_COPY_AND_ASSIGN(Colorbar2DImageFilter); //purposely not implemented

    };
} //namespace ITK

#ifndef TOMATOLIB_COMPILED
#ifndef ITK_MANUAL_INSTANTIATION
#include "itkColorbar2DImageFilter.txx"
#endif //ITK_MANUAL_INSTANTIATION
#endif //TOMATOLIB_COMPILED

#endif //USE_ITK

#endif //TomatoLIB_ITKColorbar2DImageFilter_H

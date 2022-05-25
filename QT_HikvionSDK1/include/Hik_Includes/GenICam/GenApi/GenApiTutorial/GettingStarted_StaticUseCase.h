
//-----------------------------------------------------------------------------
//  (c) 2004-2008 by Basler Vision Technologies
//  Section: Vision Components
//  Project: GenApi
//-----------------------------------------------------------------------------
/*!
\file
\brief XML file extracted from test code
*/
//-----------------------------------------------------------------------------
//  This file is generated automatically
//  Do not modify!
//-----------------------------------------------------------------------------


#ifndef GenApiTutorial_GettingStarted_StaticUseCase_PTR_H
#define GenApiTutorial_GettingStarted_StaticUseCase_PTR_H

#include <GenApi/NodeMapRef.h>
#include "GettingStarted_StaticUseCaseParams.h"

//! The namespace containing the device's control interface and related enumeration types
namespace GenApiTutorial_GettingStarted_StaticUseCase
{
    //**************************************************************************************************
    // Access class
    //**************************************************************************************************
    //! XML file extracted from test code
    class CGettingStarted_StaticUseCase
        : public GenApi::CNodeMapRefT<GenApiTutorial_GettingStarted_StaticUseCase::CGettingStarted_StaticUseCase_Params>
    {
    public:
        //! Constructor
        CGettingStarted_StaticUseCase(GenICam::gcstring DeviceName = "Device") : GenApi::CNodeMapRefT<GenApiTutorial_GettingStarted_StaticUseCase::CGettingStarted_StaticUseCase_Params>(DeviceName)
        {
        }
    };


} // namespace GenApiTutorial_GettingStarted_StaticUseCase

#endif // GenApiTutorial_GettingStarted_StaticUseCase_PTR_H

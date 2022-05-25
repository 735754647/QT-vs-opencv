
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


#ifndef SnipperTest_PostprocessingTest_TestStatic_PTR_H
#define SnipperTest_PostprocessingTest_TestStatic_PTR_H

#include <GenApi/NodeMapRef.h>
#include "PostprocessingTest_TestStaticParams.h"

//! The namespace containing the device's control interface and related enumeration types
namespace SnipperTest_PostprocessingTest_TestStatic
{
    //**************************************************************************************************
    // Access class
    //**************************************************************************************************
    //! XML file extracted from test code
    class CPostprocessingTest_TestStatic
        : public GenApi::CNodeMapRefT<SnipperTest_PostprocessingTest_TestStatic::CPostprocessingTest_TestStatic_Params>
    {
    public:
        //! Constructor
        CPostprocessingTest_TestStatic(GenICam::gcstring DeviceName = "Device") : GenApi::CNodeMapRefT<SnipperTest_PostprocessingTest_TestStatic::CPostprocessingTest_TestStatic_Params>(DeviceName)
        {
        }
    };


} // namespace SnipperTest_PostprocessingTest_TestStatic

#endif // SnipperTest_PostprocessingTest_TestStatic_PTR_H

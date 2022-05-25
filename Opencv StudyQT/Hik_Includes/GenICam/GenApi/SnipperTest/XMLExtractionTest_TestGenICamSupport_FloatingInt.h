
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


#ifndef SnipperTest_XMLExtractionTest_TestGenICamSupport_FloatingInt_PTR_H
#define SnipperTest_XMLExtractionTest_TestGenICamSupport_FloatingInt_PTR_H

#include <GenApi/NodeMapRef.h>
#include "XMLExtractionTest_TestGenICamSupport_FloatingIntParams.h"

//! The namespace containing the device's control interface and related enumeration types
namespace SnipperTest_XMLExtractionTest_TestGenICamSupport_FloatingInt
{
    //**************************************************************************************************
    // Access class
    //**************************************************************************************************
    //! XML file extracted from test code
    class CXMLExtractionTest_TestGenICamSupport_FloatingInt
        : public GenApi::CNodeMapRefT<SnipperTest_XMLExtractionTest_TestGenICamSupport_FloatingInt::CXMLExtractionTest_TestGenICamSupport_FloatingInt_Params>
    {
    public:
        //! Constructor
        CXMLExtractionTest_TestGenICamSupport_FloatingInt(GenICam::gcstring DeviceName = "Device") : GenApi::CNodeMapRefT<SnipperTest_XMLExtractionTest_TestGenICamSupport_FloatingInt::CXMLExtractionTest_TestGenICamSupport_FloatingInt_Params>(DeviceName)
        {
        }
    };


} // namespace SnipperTest_XMLExtractionTest_TestGenICamSupport_FloatingInt

#endif // SnipperTest_XMLExtractionTest_TestGenICamSupport_FloatingInt_PTR_H

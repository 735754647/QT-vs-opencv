

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



#ifndef SnipperTest_XMLExtractionTest_TestGenICamSupport_FloatingInt_PARAMS_H
#define SnipperTest_XMLExtractionTest_TestGenICamSupport_FloatingInt_PARAMS_H

#include <GenApi/IEnumerationT.h>
#include <GenApi/NodeMapRef.h>
#include <GenApi/DLLLoad.h>

//! The namespace containing the device's control interface and related enumeration types
namespace SnipperTest_XMLExtractionTest_TestGenICamSupport_FloatingInt
{

    //**************************************************************************************************
    // Enumerations
    //**************************************************************************************************
    

    //**************************************************************************************************
    // Parameter class
    //**************************************************************************************************
    

    //! XML file extracted from test code
    class CXMLExtractionTest_TestGenICamSupport_FloatingInt_Params
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
		// If you want to show the following methods in the help file
		// add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
        //! \cond HIDE_CLASS_METHODS
        
            //! Constructor
            CXMLExtractionTest_TestGenICamSupport_FloatingInt_Params(void);

            //! Destructor
            ~CXMLExtractionTest_TestGenICamSupport_FloatingInt_Params(void);

            //! Initializes the references
            void _Initialize(GenApi::INodeMap*);

            //! Return the vendor of the camera
            const char* _GetVendorName(void);

            //! Returns the camera model name
            const char* _GetModelName(void);
        
        //! \endcond

    //----------------------------------------------------------------------------------------------------------------
    // References to features
    //----------------------------------------------------------------------------------------------------------------
    public:
        

    private:
        //! \cond HIDE_CLASS_METHODS

            //! not implemented copy constructor
            CXMLExtractionTest_TestGenICamSupport_FloatingInt_Params(CXMLExtractionTest_TestGenICamSupport_FloatingInt_Params&);

            //! not implemented assignment operator
            CXMLExtractionTest_TestGenICamSupport_FloatingInt_Params& operator=(CXMLExtractionTest_TestGenICamSupport_FloatingInt_Params&);

        //! \endcond
    };


    //**************************************************************************************************
    // Parameter class implementation
    //**************************************************************************************************

    //! \cond HIDE_CLASS_METHODS

    inline CXMLExtractionTest_TestGenICamSupport_FloatingInt_Params::CXMLExtractionTest_TestGenICamSupport_FloatingInt_Params(void)
        
    {
    }

    inline CXMLExtractionTest_TestGenICamSupport_FloatingInt_Params::~CXMLExtractionTest_TestGenICamSupport_FloatingInt_Params(void)
    {
        
    }

    inline void CXMLExtractionTest_TestGenICamSupport_FloatingInt_Params::_Initialize(GenApi::INodeMap* _Ptr)
    {
        
    }

    inline const char* CXMLExtractionTest_TestGenICamSupport_FloatingInt_Params::_GetVendorName(void)
    {
        return "SnipperTest";
    }

    inline const char* CXMLExtractionTest_TestGenICamSupport_FloatingInt_Params::_GetModelName(void)
    {
        return "XMLExtractionTest_TestGenICamSupport_FloatingInt";
    }

    //! \endcond

} // namespace SnipperTest_XMLExtractionTest_TestGenICamSupport_FloatingInt

#endif // SnipperTest_XMLExtractionTest_TestGenICamSupport_FloatingInt_PARAMS_H

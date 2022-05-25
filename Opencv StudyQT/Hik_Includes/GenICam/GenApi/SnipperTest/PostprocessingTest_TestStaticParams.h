

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



#ifndef SnipperTest_PostprocessingTest_TestStatic_PARAMS_H
#define SnipperTest_PostprocessingTest_TestStatic_PARAMS_H

#include <GenApi/IEnumerationT.h>
#include <GenApi/NodeMapRef.h>
#include <GenApi/DLLLoad.h>

//! The namespace containing the device's control interface and related enumeration types
namespace SnipperTest_PostprocessingTest_TestStatic
{

    //**************************************************************************************************
    // Enumerations
    //**************************************************************************************************
    

    //**************************************************************************************************
    // Parameter class
    //**************************************************************************************************
    

    //! XML file extracted from test code
    class CPostprocessingTest_TestStatic_Params
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
		// If you want to show the following methods in the help file
		// add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
        //! \cond HIDE_CLASS_METHODS
        
            //! Constructor
            CPostprocessingTest_TestStatic_Params(void);

            //! Destructor
            ~CPostprocessingTest_TestStatic_Params(void);

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
        
	//! \name Root - 
    //@{
	/*!	
		\brief 

	
	
		\b Visibility = Beginner
        
	
    */
    GenApi::IInteger &MyInt;
    
    //@}



    private:
        //! \cond HIDE_CLASS_METHODS

            //! not implemented copy constructor
            CPostprocessingTest_TestStatic_Params(CPostprocessingTest_TestStatic_Params&);

            //! not implemented assignment operator
            CPostprocessingTest_TestStatic_Params& operator=(CPostprocessingTest_TestStatic_Params&);

        //! \endcond
    };


    //**************************************************************************************************
    // Parameter class implementation
    //**************************************************************************************************

    //! \cond HIDE_CLASS_METHODS

    inline CPostprocessingTest_TestStatic_Params::CPostprocessingTest_TestStatic_Params(void)
        : MyInt( *new GenApi::CIntegerRef() )
        
    {
    }

    inline CPostprocessingTest_TestStatic_Params::~CPostprocessingTest_TestStatic_Params(void)
    {
        delete static_cast < GenApi::CIntegerRef*> (&MyInt );
        
    }

    inline void CPostprocessingTest_TestStatic_Params::_Initialize(GenApi::INodeMap* _Ptr)
    {
        static_cast<GenApi::CIntegerRef*> (&MyInt )->SetReference(_Ptr->GetNode("MyInt"));
    
    }

    inline const char* CPostprocessingTest_TestStatic_Params::_GetVendorName(void)
    {
        return "SnipperTest";
    }

    inline const char* CPostprocessingTest_TestStatic_Params::_GetModelName(void)
    {
        return "PostprocessingTest_TestStatic";
    }

    //! \endcond

} // namespace SnipperTest_PostprocessingTest_TestStatic

#endif // SnipperTest_PostprocessingTest_TestStatic_PARAMS_H

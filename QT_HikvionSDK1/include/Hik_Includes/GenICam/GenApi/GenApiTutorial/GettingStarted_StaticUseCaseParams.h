

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



#ifndef GenApiTutorial_GettingStarted_StaticUseCase_PARAMS_H
#define GenApiTutorial_GettingStarted_StaticUseCase_PARAMS_H

#include <GenApi/IEnumerationT.h>
#include <GenApi/NodeMapRef.h>
#include <GenApi/DLLLoad.h>

//! The namespace containing the device's control interface and related enumeration types
namespace GenApiTutorial_GettingStarted_StaticUseCase
{

    //**************************************************************************************************
    // Enumerations
    //**************************************************************************************************
    
    //! Valid values for GainAuto
    enum GainAutoEnums
    {
        GainAuto_Off,  //!<
		GainAuto_Once,  //!<
		GainAuto_Continuous   //!<
		
    };


    //**************************************************************************************************
    // Parameter class
    //**************************************************************************************************
    

    //! XML file extracted from test code
    class CGettingStarted_StaticUseCase_Params
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
		// If you want to show the following methods in the help file
		// add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
        //! \cond HIDE_CLASS_METHODS
        
            //! Constructor
            CGettingStarted_StaticUseCase_Params(void);

            //! Destructor
            ~CGettingStarted_StaticUseCase_Params(void);

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
        
	//! \name AnalogControls - 
    //@{
	/*!	
		\brief 

	
	
		\b Visibility = Beginner
        
	
    */
    GenApi::IInteger &Gain;
    
    //@}


	//! \name AnalogControls - 
    //@{
	/*!	
		\brief 

	
	
		\b Visibility = Beginner
        
	
    */
    GenApi::IEnumerationT<GainAutoEnums > &GainAuto;
    
    //@}


	//! \name AnalogControls - 
    //@{
	/*!	
		\brief 

	
	
		\b Visibility = Beginner
        
	
    */
    GenApi::ICommand &GainOnePush;
    
    //@}


	//! \name AcquisitionControl - 
    //@{
	/*!	
		\brief 

	
	
		\b Visibility = Beginner
        
	
    */
    GenApi::IFloat &ExposureTime;
    
    //@}


	//! \name AcquisitionControl - 
    //@{
	/*!	
		\brief 

	
	
		\b Visibility = Beginner
        
	
    */
    GenApi::IInteger &ExposureTicks;
    
    //@}



    private:
        //! \cond HIDE_CLASS_METHODS

            //! not implemented copy constructor
            CGettingStarted_StaticUseCase_Params(CGettingStarted_StaticUseCase_Params&);

            //! not implemented assignment operator
            CGettingStarted_StaticUseCase_Params& operator=(CGettingStarted_StaticUseCase_Params&);

        //! \endcond
    };


    //**************************************************************************************************
    // Parameter class implementation
    //**************************************************************************************************

    //! \cond HIDE_CLASS_METHODS

    inline CGettingStarted_StaticUseCase_Params::CGettingStarted_StaticUseCase_Params(void)
        : Gain( *new GenApi::CIntegerRef() )
        , GainAuto( *new GenApi::CEnumerationTRef<GainAutoEnums>() )
        , GainOnePush( *new GenApi::CCommandRef() )
        , ExposureTime( *new GenApi::CFloatRef() )
        , ExposureTicks( *new GenApi::CIntegerRef() )
        
    {
    }

    inline CGettingStarted_StaticUseCase_Params::~CGettingStarted_StaticUseCase_Params(void)
    {
        delete static_cast < GenApi::CIntegerRef*> (&Gain );
        delete static_cast < GenApi::CEnumerationTRef<GainAutoEnums> *> (&GainAuto );
        delete static_cast < GenApi::CCommandRef*> (&GainOnePush );
        delete static_cast < GenApi::CFloatRef*> (&ExposureTime );
        delete static_cast < GenApi::CIntegerRef*> (&ExposureTicks );
        
    }

    inline void CGettingStarted_StaticUseCase_Params::_Initialize(GenApi::INodeMap* _Ptr)
    {
        static_cast<GenApi::CIntegerRef*> (&Gain )->SetReference(_Ptr->GetNode("Gain"));
    static_cast<GenApi::CEnumerationTRef<GainAutoEnums> *> (&GainAuto )->SetReference(_Ptr->GetNode("GainAuto"));
    static_cast<GenApi::CEnumerationTRef<GainAutoEnums> *> (&GainAuto )->SetNumEnums(3);
	static_cast<GenApi::CEnumerationTRef<GainAutoEnums> *> (&GainAuto )->SetEnumReference( GainAuto_Off, "Off" );		static_cast<GenApi::CEnumerationTRef<GainAutoEnums> *> (&GainAuto )->SetEnumReference( GainAuto_Once, "Once" );		static_cast<GenApi::CEnumerationTRef<GainAutoEnums> *> (&GainAuto )->SetEnumReference( GainAuto_Continuous, "Continuous" );		static_cast<GenApi::CCommandRef*> (&GainOnePush )->SetReference(_Ptr->GetNode("GainOnePush"));
    static_cast<GenApi::CFloatRef*> (&ExposureTime )->SetReference(_Ptr->GetNode("ExposureTime"));
    static_cast<GenApi::CIntegerRef*> (&ExposureTicks )->SetReference(_Ptr->GetNode("ExposureTicks"));
    
    }

    inline const char* CGettingStarted_StaticUseCase_Params::_GetVendorName(void)
    {
        return "GenApiTutorial";
    }

    inline const char* CGettingStarted_StaticUseCase_Params::_GetModelName(void)
    {
        return "GettingStarted_StaticUseCase";
    }

    //! \endcond

} // namespace GenApiTutorial_GettingStarted_StaticUseCase

#endif // GenApiTutorial_GettingStarted_StaticUseCase_PARAMS_H

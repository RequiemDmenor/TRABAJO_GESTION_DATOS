#include <public/ccobsmng_iface_v1.h>

// ***********************************************************************

// class EDROOM_CTX_Top_0

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CCObsMng::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(CCObsMng &act,
	 Pr_Time & EDROOMpVarVNextTimeOut ):

	EDROOMcomponent(act),
	Msg(EDROOMcomponent.Msg),
	MsgBack(EDROOMcomponent.MsgBack),
	ObsCtrl(EDROOMcomponent.ObsCtrl),
	ObservTimer(EDROOMcomponent.ObservTimer),
	AttCtrlTimer(EDROOMcomponent.AttCtrlTimer),
	CImageInterval(0,5),
	VNextTimeOut(EDROOMpVarVNextTimeOut)
{
}

CCObsMng::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(EDROOM_CTX_Top_0 &context):

	EDROOMcomponent(context.EDROOMcomponent),
	Msg(context.Msg),
	MsgBack(context.MsgBack),
	ObsCtrl(context.ObsCtrl),
	ObservTimer(context.ObservTimer),
	AttCtrlTimer(context.AttCtrlTimer),
	CImageInterval(0,5),
	VNextTimeOut(context.VNextTimeOut)
{

}

	// EDROOMSearchContextTrans********************************************

bool CCObsMng::EDROOM_CTX_Top_0::EDROOMSearchContextTrans(
			TEDROOMTransId &edroomCurrentTrans)
			{

	bool edroomValidMsg=false; 

	 switch(Msg->signal)
	{

		 case ( EDROOMSignalDestroy ): 

			 edroomValidMsg=true;
			 edroomCurrentTrans.distanceToContext = 0 ;
			 edroomCurrentTrans.localId = -1 ;
			 break;

	}

	return(edroomValidMsg);

}

	// User-defined Functions   ****************************

void	CCObsMng::EDROOM_CTX_Top_0::FDoActtitudeCtrl()

{

pus_service129_do_attitude_ctrl();

}



void	CCObsMng::EDROOM_CTX_Top_0::FEndObservation()

{

// Take absolute time reference
VNextTimeOut.GetTime;
 
pus_service129_end_observation();

}



void	CCObsMng::EDROOM_CTX_Top_0::FInit_Obs()

{
   //Define absolute time
  Pr_Time time;
	 
	//Timing Service useful methods
	 
	time.GetTime(); // Get current monotonic time
	time += Pr_Time(0,100000); // Add X sec + Y microsec
        VNextTimeout=time;
   //Program absolute timer 
   AttCtrlTimer.InformAt( time ); 
}



void	CCObsMng::EDROOM_CTX_Top_0::FObsCtrl_exec()

{
   //Handle Msg->data
  CDTCHandler & varSObsMng_TC = *(CDTCHandler *)Msg->data;
	
		// Data access
	
	varSObsMng_TC.ExecTC;

}



void	CCObsMng::EDROOM_CTX_Top_0::FProgAttitudeCtrl()

{
   //Define absolute time
  Pr_Time time;
	 
	//Timing Service useful methods
	 
	VNextTimeout += Pr_Time(0,100000); // Add X sec + Y microsec
        time = VNextTimeout
   //Program absolute timer 
   AttCtrlTimer.InformAt( time ); 
}



void	CCObsMng::EDROOM_CTX_Top_0::FProgTakeImage()

{
   //Define interval
  Pr_Time interval;
	
	//Timing Service useful methods
	 
         internal=CImageInterval;
   //Program relative timer 
   ObservTimer.InformIn( interval ); 
}



void	CCObsMng::EDROOM_CTX_Top_0::FTakeImage()

{

pus_service129_take_image();

}



void	CCObsMng::EDROOM_CTX_Top_0::FToObservation()

{

pus_service129_start_observation();

}



bool	CCObsMng::EDROOM_CTX_Top_0::GLastImage()

{

return pus_service129_is_last_image();

}



bool	CCObsMng::EDROOM_CTX_Top_0::GReadyToObservation()

{

return pus_service129_is_observation_ready();

}



	//********************************** Pools *************************************



// ***********************************************************************

// class EDROOM_SUB_Top_0

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CCObsMng::EDROOM_SUB_Top_0::EDROOM_SUB_Top_0 (CCObsMng&act):
		EDROOM_CTX_Top_0(act,
			VNextTimeOut)
{

}

	//***************************** EDROOMBehaviour ********************************

void CCObsMng::EDROOM_SUB_Top_0::EDROOMBehaviour()
{

	TEDROOMTransId edroomCurrentTrans;

	//Behaviour starts from Init State

	edroomCurrentTrans = EDROOMIArrival();

	do
	{

		//Take next transition

		switch(edroomCurrentTrans.localId)
		{

			//Next Transition is Init
			case (Init):
				//Execute Action 
				FInit_Obs();
				//Next State is Standby
				edroomNextState = Standby;
				break;
			//Next Transition is TC_Exec
			case (TC_Exec):
				//Msg->Data Handling 
				FObsCtrl_exec();
				//Next State is Standby
				edroomNextState = Standby;
				break;
			//To Choice Point Do_AttitudeCtrl
			case (Do_AttitudeCtrl):

				//Execute Action 
				FDoActtitudeCtrl();
				//Evaluate Branch To_Observation
				if( GReadyToObservation() )
				{
					//Execute Action 
					FToObservation();

					//Branch taken is Do_AttitudeCtrl_To_Observation
					edroomCurrentTrans.localId =
						Do_AttitudeCtrl_To_Observation;

					//Next State is Observation
					edroomNextState = Observation;
				 } 
				//Default Branch Default
				else
				{
					//Execute Action 
					FProgAttitudeCtrl();

					//Branch taken is Do_AttitudeCtrl_Default
					edroomCurrentTrans.localId =
						Do_AttitudeCtrl_Default;

					//Next State is Standby
					edroomNextState = Standby;
				 } 
				break;
			//To Choice Point Take_Image
			case (Take_Image):

				//Execute Action 
				FTakeImage();
				//Evaluate Branch To_Standby
				if( GLastImage() )
				{
					//Execute Actions 
					FEndObservation();
					FProgAttitudeCtrl();

					//Branch taken is Take_Image_To_Standby
					edroomCurrentTrans.localId =
						Take_Image_To_Standby;

					//Next State is Standby
					edroomNextState = Standby;
				 } 
				//Default Branch Default
				else
				{

					//Branch taken is Take_Image_Default
					edroomCurrentTrans.localId =
						Take_Image_Default;

					//Next State is Observation
					edroomNextState = Observation;
				 } 
				break;
		}

		//Entry into the Next State 
		switch(edroomNextState)
		{

				//Go to the state I
			case (I):
				//Arrival to state I
				edroomCurrentTrans=EDROOMIArrival();
				break;

				//Go to the state Standby
			case (Standby):
				//Arrival to state Standby
				edroomCurrentTrans=EDROOMStandbyArrival();
				break;

				//Go to the state Observation
			case (Observation):
				//Execute Entry Action 
				FProgTakeImage();
				//Arrival to state Observation
				edroomCurrentTrans=EDROOMObservationArrival();
				break;

		}

		edroomCurrentState=edroomNextState;

	}while(Msg->signal != EDROOMSignalDestroy);

}



	// Context Init**********************************************

void CCObsMng::EDROOM_SUB_Top_0::EDROOMInit()
{

edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId CCObsMng::EDROOM_SUB_Top_0::EDROOMIArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	//Next transition is  Init
	edroomCurrentTrans.localId = Init;
	edroomCurrentTrans.distanceToContext = 0;
	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  Standby

	// ***********************************************************************



TEDROOMTransId CCObsMng::EDROOM_SUB_Top_0::EDROOMStandbyArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	bool edroomValidMsg=false;

	do
	{

		EDROOMNewMessage ();

		switch(Msg->signal)
		{

			case (SObsMng_TC): 

				 if (*Msg->GetPInterface() == ObsCtrl)
				{

					//Next transition is  TC_Exec
					edroomCurrentTrans.localId= TC_Exec;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

				break;

			case (EDROOMSignalTimeout): 

				 if (*Msg->GetPInterface() == AttCtrlTimer)
				{

					//Next transition is  Do_AttitudeCtrl
					edroomCurrentTrans.localId = Do_AttitudeCtrl;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				break;

		};

		if (false == edroomValidMsg)
		{
			 edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

		}

	} while (false == edroomValidMsg);

	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  Observation

	// ***********************************************************************



TEDROOMTransId CCObsMng::EDROOM_SUB_Top_0::EDROOMObservationArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	bool edroomValidMsg=false;

	do
	{

		EDROOMNewMessage ();

		switch(Msg->signal)
		{

			case (EDROOMSignalTimeout): 

				 if (*Msg->GetPInterface() == ObservTimer)
				{

					//Next transition is  Take_Image
					edroomCurrentTrans.localId = Take_Image;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				break;

		};

		if (false == edroomValidMsg)
		{
			 edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

		}

	} while (false == edroomValidMsg);

	return(edroomCurrentTrans);

}




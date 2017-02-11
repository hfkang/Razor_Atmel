/**********************************************************************************************************************
File: battle.c                                                                
 
----------------------------------------------------------------------------------------------------------------------
To start a new task using this battle as a template:
 1. Copy both battle.c and battle.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "battle" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "BattleMode" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "BATTLE_MODE" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

Description:
This is a battle.c file template 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void Initialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void BattleModeRunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32BattleModeFlags;                       /* Global state flags */

u16 cycleCount = 0;

u8 msg1[] = "BUT0:   times.\0";
u8 msg2[] = {48,0};
u8 msg_wild1[] = "A wild ";
u8 msg_wild2[] = " appeared!";
u8 squaremon[] = "square";
u8 hexmon[] = "hexmon!";
u8 msg_send1[] = "Go ";


u8 buttoncount = 0;
PixelAddressType home = {0, 0};
PixelAddressType row1 = {0, 36};
PixelAddressType bottom = {57,0};
PixelAddressType bottom2 = {57, 71};
PixelAddressType bottom3 = {57, 20};
PixelAddressType bottomSpace = {57, 39};

/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "BattleMode_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type BattleMode_StateMachine;            /* The state machine function pointer */
//static u32 BattleMode_u32Timeout;                      /* Timeout counter used across states */


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: BattleModeInitialize

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void BattleModeInitialize(void)
{

    LcdClearScreen();  
    LcdLoadString(msg1, 0, &home); 
    LcdLoadString(msg2, 0, &row1);

    


  /* If good initialization, set state to Idle */
  if( 1 )
  {
    BattleMode_StateMachine = BattleModeSM_WildPolymon;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    BattleMode_StateMachine = BattleModeSM_FailedInit;
  }

} /* end BattleModeInitialize() */

  
/*----------------------------------------------------------------------------------------------------------------------
Function BattleModeRunActiveState()

Description:
Selects and runs one iteration of the current state in the state machine.
All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
  - State machine function pointer points at current state

Promises:
  - Calls the function to pointed by the state machine function pointer
*/
void BattleModeRunActiveState(void)
{
  BattleMode_StateMachine();

} /* end BattleModeRunActiveState */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

static void BattleModeSM_WildPolymon(void) {
    LcdClearScreen();
    LcdLoadString(msg_wild1, 0, &bottom);
    LcdLoadString(msg_wild2, 0, &bottom2);
    LcdLoadString(squaremon, 0 , &bottomSpace);
    cycleCount++;
    if(cycleCount > 2000){
      BattleMode_StateMachine = BattleModeSM_SendPolymon;
    }
}
  
static void BattleModeSM_SendPolymon(void) {
  LcdClearScreen();
  LcdLoadString(msg_send1, 0, &bottom);
  LcdLoadString(hexmon, 0, &bottom3);
  
      
}

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for a message to be queued */
static void BattleModeSM_Idle(void)
{
  LcdClearScreen();  
    LcdLoadString(msg1, 0, &home); 
    LcdLoadString(msg2, 0, &row1);
  if(WasButtonPressed(BUTTON0))
  {
    ButtonAcknowledge(BUTTON0);
    buttoncount = buttoncount + 1;   

    msg2[0] = buttoncount + 48;
    LcdClearScreen();  
    LcdLoadString(msg2, 0, &row1);
    LcdLoadString(msg1, 0, &home); 
    if (buttoncount==10)
      BattleMode_StateMachine = BattleModeSM_WildPolymon;
  }
  else{
  }

} /* end BattleModeSM_Idle() */
     
#if 0
/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void BattleModeSM_Error(void)          
{
  
} /* end BattleModeSM_Error() */
#endif


/*-------------------------------------------------------------------------------------------------------------------*/
/* State to sit in if init failed */
static void BattleModeSM_FailedInit(void)          
{
    
} /* end BattleModeSM_FailedInit() */

/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/

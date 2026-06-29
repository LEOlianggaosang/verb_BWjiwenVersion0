/* Includes files -------------------------------------------------------*/
#include "WatchdogDrv.h"
#include "Buzzer\Buzzer.h"
#include "WashDish\WashDish.h"
#include "LoadDrive\LoadDrive.h"
#include "ReadSwitch\ReadSwitch.h"
#include "Temperatures\Temperatures.h"
#include "TicketHandling\TicketHandling.h"
#include "Initialization\Initialization.h"

/* Function declare -----------------------------------------------------*/

/* Program Entry */

void  main( void )
{
  Initialization();

  Buzz_SetType(BUZZ_POWERON);
	
  /* System Working loop */  
  while (1)
  {
    RestartWatchdog();
    
    if (F_Base1ms)
    {
      F_Base1ms = 0;
			
      Read_Switch();
      Temperature_Read();
			Buzz_Control();
		  Load_Driver();
			WashDish_Control();
    }
  }
}

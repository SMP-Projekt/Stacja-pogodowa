/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    sleep.c
 *      Purpose: Wheather Station - project
 *			Author: DarthSkipper & ArdeoDeo
 *			Date: 09-12-2017
 *----------------------------------------------------------------------------
 *      ^^^^^WHEATHER STATION^^^^^
 *---------------------------------------------------------------------------*/
#include "sleep.h"
/*************************************************************************
Function: sleep()
Purpose:  Normal wait mode
Input:    none
Returns:  none          
**************************************************************************/
void sleep()
{
    SMC->PMPROT = SMC_PMPROT_AVLLS_MASK | SMC_PMPROT_ALLS_MASK | SMC_PMPROT_AVLP_MASK;
 
    //Normal sleep mode for ARM core:
    SCB->SCR = 0;
    __WFI();
}
/*************************************************************************
Function: deepsleep()
Purpose:  Very low-power stop mode
Input:    none
Returns:  none          
**************************************************************************/
void deepsleep()
{
    //Check if PLL/FLL is enabled:
    uint32_t PLL_FLL_en = (MCG->C1 & MCG_C1_CLKS_MASK) == MCG_C1_CLKS(0);
    
    SMC->PMPROT = SMC_PMPROT_AVLLS_MASK | SMC_PMPROT_ALLS_MASK | SMC_PMPROT_AVLP_MASK;
    SMC->PMCTRL = SMC_PMCTRL_STOPM(2);
 
    //Deep sleep for ARM core:
    SCB->SCR = 1<<SCB_SCR_SLEEPDEEP_Pos;
 
    __WFI();
 
    //Switch back to PLL as clock source if needed
    //The interrupt that woke up the device will run at reduced speed
    if (PLL_FLL_en) {
        #ifdef MCG_C5_PLLCLKEN0_MASK        //PLL available
        if ((MCG->C6 & (1<<MCG_C6_PLLS_SHIFT)) != 0) /* If PLL */
            while((MCG->S & MCG_S_LOCK0_MASK) == 0x00U); /* Wait until locked */
        #endif
        MCG->C1 &= ~MCG_C1_CLKS_MASK;
    }
 
}

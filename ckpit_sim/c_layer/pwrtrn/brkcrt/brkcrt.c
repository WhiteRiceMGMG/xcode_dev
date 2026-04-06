/* brkcrt.c                                             */
/********************************************************/
/* object    | brkcrt                                   */
/* edit his  | 2026/03/12 make new ver1.0               */
/*           |                                          */
/********************************************************/
/********************************************************/
/* Header Includes                                      */
/********************************************************/
#include "../../inc/common.h"          /* common header */
#include "../../inc/cmnclk.h"          /* u1g_absval()  */
#include "../../conf/cmnconf.h"        /* u1g_BRK_MAX   */
#include "../brkcrtif.h"               /* self header   */

/********************************************************/
/* External Public Variables, Constants, Macros         */
/********************************************************/
u1 u1g_brkcrtif_brkopn; /* correctioned brake percent   */
u1 u1g_brkcrtif_crtflg; /* correction bool on off       */

/********************************************************/
/* Internal Public Variables, Constants, Macros         */
/********************************************************/
static u1 u1t_brkcrt_o;            /* internal brk crt  */

/********************************************************/
/* External Public Function Definitions                 */
/********************************************************/

/********************************************************/
/* func    | vdg_brkcrtif_pwon( void )                  */
/* abst    | brake correction                           */
/* args    | none                                       */
/* rtn val | none                                       */
/********************************************************/
void
vdg_brkcrtif_pwon( void )
{
    u1g_brkcrtif_brkopn = (u1)0;
    u1g_brkcrtif_crtflg = (u1)0;
}


/********************************************************/
/* func    | vdg_brkcrtif_16msh( void )                 */
/* abst    | brake correction                           */
/* args    | none                                       */
/* rtn val | none                                       */
/********************************************************/
void
vdg_brkcrtif_16msh( void )
{
    u1 u1t_brkopn; 
    u1 u1t_brkcrt;
    u1 u1t_brkthld;
    u1 u1t_crtonoff;

    u1t_brkopn = u1g_swiftif_brkopn;
    u1t_brthld = ((u1g_BRK_MAX * 5 / 100) + 0.5);
    u1t_absbrk = u1g_abscal( u1t_brkopn, u1t_brkcrt_o );

    u1t_crtonoff = (u1)OFF;
    u1t_brkcrt = u1t_brkcrt_o;
    if ( u1t_absbrk > u1t_brkthld )
    {
        u1t_crtonoff = (u1)ON;
        u1t_brkcrt = u1t_brkopn;
    }

    u1s_brkcrt_o = u1t_brkopn;
    u1g_brkcrtif_brkopn = u1t_brkcrt;
    u1g_brkcrtif_crtflg = u1t_crtonoff;
}

/********************************************************/
/* Internal Public Function Definitions                 */
/********************************************************/

/********************************************************/
/* EOF                                                  */
/********************************************************/


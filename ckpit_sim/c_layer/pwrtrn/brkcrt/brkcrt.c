/* brkcrt.c                                             */
/********************************************************/
/* object    | brake correction                         */
/* edit his  | 2026/03/12 make new ver1.0               */
/*           |                                          */
/********************************************************/
/********************************************************/
/* Header Includes                                      */
/********************************************************/
#include "../../inc/common.h"         /* common header */
#include "../brkcrtif.h"              /* self header   */

/********************************************************/
/* External Public Variables, Constants, Macros         */
/********************************************************/
u1 u1g_brkcrtif_brkopn; /* correctioned brake percent   */
u1 u1g_brkcrtif_crtflg; /* correction bool on off       */

/********************************************************/
/* Internal Public Variables, Constants, Macros         */
/********************************************************/

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
    u1 u1t_brkcrt;
    u1 u1t_crtonoff;

    u1t_brkcrt = u1g_brkcrtif_brkpon;
    u1t_crtonoff = u1g_brkcrtif_crtflg;

    
}

/********************************************************/
/* Internal Public Function Definitions                 */
/********************************************************/

/********************************************************/
/* func    | u1 u1g_sample_function( void )             */
/* abst    | drive mode processing functions            */
/* args    | none                                       */
/* rtn val | none                                       */
/********************************************************/

/********************************************************/
/* EOF                                                  */
/********************************************************/


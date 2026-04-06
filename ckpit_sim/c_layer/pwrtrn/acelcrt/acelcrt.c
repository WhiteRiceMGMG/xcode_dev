/* acelcrt.c                                            */
/********************************************************/
/* object    | accel correction                         */
/* edit his  | 2026/03/11 make Ver1.0                   */
/*           |                                          */
/********************************************************/
/********************************************************/
/* Header Includes                                      */
/********************************************************/
#include "../../inc/common.h"       /* common library   */
#include "../..swift/swiftif.h"     /* u1g_swiftif_acel */
#include "../acelcrtif.h"           /* self header      */


/********************************************************/
/* External Public Variables, Constants, Macros         */
/********************************************************/
u1 u1g_acelcrtif_thlopn;    /* accel correctoin         */
u1 u1g_acelcrtif_crtflg;    /* correction bool on/off   */

/********************************************************/
/* Internal Public Variables, Constants, Macros         */
/********************************************************/
static u1 u1s_acelcrt_thlopn_o;
#define u1g_ACEL_THLD (u1)3;

/********************************************************/
/* External Public Function Definitions                 */
/********************************************************/

/********************************************************/
/* func    | vdg_acelcrtif_pwon()                       */
/* abst    | crt acel thl opn                           */
/* args    | none                                       */
/* rtn val | none                                       */
/********************************************************/
void
vdg_acelcrtif_pwon( void )
{
    u1 u1t_aceltmp;
    
    u1t_aceltmp = u1g_swiftif_acel;

    u1s_acelcrt_thlopn_o = u1t_aceltmp;
    u1g_acelcrtif_thlopn = u1t_aceltmp;
    u1g_acelcrtif_crtflg = (u1)ON;

}


/********************************************************/
/* func    | vdg_acelcrtif_50msm()                      */
/* abst    | crt acel thl opn                           */
/* args    | none                                       */
/* rtn val | none                                       */
/********************************************************/
void
vdg_acelcrtif_50msm( void )
{
    u1 u1t_swift_aceltmp;
    u1 u1t_aceltmp;
    u1 u1t_aceltmp_o;
    u1 u1t_crtflg;

    u1t_swift_aceltmp = u1g_swiftif_acel;
    u1t_aceltmp_o = u1s_acelcrt_thlopn_o;

    u1t_crtflg = (u1)OFF;
    u1t_aceltmp = u1t_aceltmp_o;
    if ( u1t_swift_aceltmp >= u1t_aceltmp_o)
    {
        if ( u1t_swift_aceltmp - u1t_aceltmp_o 
                                      >= u1g_ACEL_THLD )
        {
            u1t_crtflg = (u1)ON;
            u1t_aceltmp = u1t_swift_aceltmp;
        }
    }
    else
    {
        if ( u1t_aceltmp_o - u1t_swift_aceltmp
                                      >= u1g_ACEL_THLD )
        {
            u1t_crtflg = (u1)ON;
            u1t_aceltmp = u1t_swift_aceltmp;
        }
    }

    u1g_acelcrtif_thlopn = u1t_aceltmp;
    u1g_acelcrtif_crtflg = u1t_crtflg;
    u1s_acelcrt_thlopn_o = u1t_aceltmp;
}

/********************************************************/
/* Internal Public Function Definitions                 */
/********************************************************/

/********************************************************/
/* EOF                                                  */
/********************************************************/


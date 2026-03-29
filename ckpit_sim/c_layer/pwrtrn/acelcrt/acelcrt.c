/* acelcrt.c                                            */
/********************************************************/
/* object    | accel correction                         */
/* edit his  | 2026/03/11 make Ver1.0                   */
/*           |                                          */
/********************************************************/
/********************************************************/
/* Header Includes                                      */
/********************************************************/
#include "../../inc/common.h"         /* common library */
#include "../acelcrtif.h"             /* self header    */


/********************************************************/
/* External Public Variables, Constants, Macros         */
/********************************************************/
u1 u1g_acelcrtif_thlopn;    /* accel correctoin         */
u1 u1g_acelcrtif_crtflg;    /* correction bool on/off   */

/********************************************************/
/* Internal Public Variables, Constants, Macros         */
/********************************************************/
static u1 u1g_acelcrt_filterd_o;

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


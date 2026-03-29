/* velaclcalif.h                                        */
/********************************************************/
/* object    | calc vel and acl                         */
/* edit his  | 2026/03/22 make ver1.0                   */
/*           |                                          */
/********************************************************/
#ifndef VELACLCALIF_H
#define VELACLCALIF_H

/********************************************************/
/* Header Includes                                      */
/********************************************************/

/********************************************************/
/* External Public Variables, Constants, Macros         */
/********************************************************/
extern u1 u1g_velaclcalif_efcacl;
extern u1 u1g_velaclcalif_efcvel;

/********************************************************/
/* External Function Prototypes                         */
/********************************************************/
/********************************************************/

void vdg_velaclcalif_pwon( void );  /* ctltim  : pwon   */
                                    /* args    : none   */
                                    /* rtn val : none   */
                                    

void vdg_velaclcalif_50msm( void ); /* ctltim  : 50msm  */
                                    /* args    : none   */
                                    /* rtn val : none   */


#undef VELACLCALIF_H
/********************************************************/
/* EOF                                                  */
/********************************************************/

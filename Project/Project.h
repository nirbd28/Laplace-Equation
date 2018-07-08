/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL1                           1
#define  PANEL1_QUITBUTTON                2       /* control type: command, callback function: QuitCallback */
#define  PANEL1_SOL                       3       /* control type: numeric, callback function: (none) */
#define  PANEL1_Y                         4       /* control type: numeric, callback function: (none) */
#define  PANEL1_X                         5       /* control type: numeric, callback function: (none) */
#define  PANEL1_CALC                      6       /* control type: command, callback function: calc */
#define  PANEL1_CANVAS                    7       /* control type: canvas, callback function: canvas */
#define  PANEL1_PICTURE_2                 8       /* control type: picture, callback function: (none) */
#define  PANEL1_PICTURE_3                 9       /* control type: picture, callback function: (none) */
#define  PANEL1_DECORATION                10      /* control type: deco, callback function: (none) */
#define  PANEL1_TEXTMSG                   11      /* control type: textMsg, callback function: (none) */
#define  PANEL1_GO_GRAPH                  12      /* control type: command, callback function: go_graph */
#define  PANEL1_VX2                       13      /* control type: scale, callback function: (none) */
#define  PANEL1_VX1                       14      /* control type: scale, callback function: (none) */
#define  PANEL1_VY1                       15      /* control type: scale, callback function: (none) */
#define  PANEL1_VY2                       16      /* control type: scale, callback function: (none) */
#define  PANEL1_A                         17      /* control type: scale, callback function: a_fun */
#define  PANEL1_TIMER                     18      /* control type: timer, callback function: timer */
#define  PANEL1_B                         19      /* control type: scale, callback function: b_fun */
#define  PANEL1_PICTURE                   20      /* control type: picture, callback function: (none) */

#define  PANEL2                           2
#define  PANEL2_HIDE_PANEL2               2       /* control type: command, callback function: hide_panel2 */
#define  PANEL2_TAB                       3       /* control type: tab, callback function: (none) */

     /* tab page panel controls */
#define  TABPANEL_GRAPH_FIXED             2       /* control type: graph, callback function: graph_fixed */
#define  TABPANEL_CHOOSE_FIXED            3       /* control type: numeric, callback function: (none) */
#define  TABPANEL_SHOW_GRAPH_Y            4       /* control type: command, callback function: show_graph_y */
#define  TABPANEL_del_graph               5       /* control type: command, callback function: DEL_GRAPH */
#define  TABPANEL_RING                    6       /* control type: ring, callback function: (none) */
#define  TABPANEL_fixed_txt               7       /* control type: textMsg, callback function: (none) */
#define  TABPANEL_fixed_ring              8       /* control type: ring, callback function: FIXED_RING */
#define  TABPANEL_txt_fixed_val           9       /* control type: textMsg, callback function: (none) */
#define  TABPANEL_cursor2                 10      /* control type: binary, callback function: CURSOR2 */
#define  TABPANEL_cursor1                 11      /* control type: binary, callback function: CURSOR1 */
#define  TABPANEL_DECORATION              12      /* control type: deco, callback function: (none) */
#define  TABPANEL_cursor2_y               13      /* control type: numeric, callback function: (none) */
#define  TABPANEL_cursor2_x               14      /* control type: numeric, callback function: (none) */
#define  TABPANEL_cursor1_y               15      /* control type: numeric, callback function: (none) */
#define  TABPANEL_cursor1_x               16      /* control type: numeric, callback function: (none) */
#define  TABPANEL_DELTA_Y                 17      /* control type: numeric, callback function: (none) */
#define  TABPANEL_DELTA_X                 18      /* control type: numeric, callback function: (none) */
#define  TABPANEL_DECORATION_2            19      /* control type: deco, callback function: (none) */
#define  TABPANEL_DECORATION_3            20      /* control type: deco, callback function: (none) */

     /* tab page panel controls */
#define  TABPANEL_2_CWGRAPH3D             2       /* control type: activeX, callback function: (none) */
#define  TABPANEL_2_plot3d                3       /* control type: command, callback function: PLOT3D */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK a_fun(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK b_fun(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK calc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK canvas(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CURSOR1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CURSOR2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DEL_GRAPH(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK FIXED_RING(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK go_graph(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK graph_fixed(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK hide_panel2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PLOT3D(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK show_graph_y(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK timer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif

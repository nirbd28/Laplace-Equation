#include <analysis.h>
#include <cvirte.h>		
#include <userint.h>
#include "Project.h" 
#include "math.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "3DGraphCtrl.h" 

/************************************** Constants */ 

#define N 50 //default 50
#define pi 3.14159265358979323846 
#define arr_num 500

#define canvas_btm 400

#define num_3d 150 

 /************************************** Handles */

static int ph1;
static int ph2;

static int tab0; 
static int tab1; 

static int plot0;
static int plot1;  
static int plot2;  
static int plot3; 

static CAObjHandle graphHandle = 0;
static CAObjHandle plotHandle = 0;

/************************************** Parameters */ 

static double a,b;
static double vx1,vx2,vy1,vy2;

static double x,y;

static double fixed_val;

static int reps=1;
static int color_reps;
static int num_legend;

static int fixed_y_or_x;

static int c1_flag;  
static int c2_flag;  
 
/************************************** Arrays */

static double fixed_arrx[arr_num];
static double fixed_arry[arr_num]; 

/************************************** Declare Functions */

double v_bn(int n); 
double v_an(int n);
double w_bn(int n);
double w_an(int n);

double v(double x,double y); 
double w(double x,double y);

void get_parameters();

int set_graph_color(int x);

void set_delta_off(); 
void cursor_off();  

/************************************** Functions */ 

double v_bn(int n)//Bn of v
{
	return 2*vy1/(n*pi*sinh(n*pi*b/a))*(1-pow(-1,n));
}

double v_an(int n)//An of v
{
	return 2*vy2/(n*pi*sinh(n*pi*b/a))*(1-pow(-1,n));
}

double w_bn(int n)//Bn of w
{
	return 2*vx1/(n*pi*sinh(n*pi*a/b))*(1-pow(-1,n));
}

double w_an(int n)//An of w
{
	return 2*vx2/(n*pi*sinh(n*pi*a/b))*(1-pow(-1,n));
}

double v(double x,double y)//Calculate v
{
	int n;
	double temp=0;
	
	for(n=1;n<=N;n++)
	{
		temp+=sin(pi*n*x/a)*(v_an(n)*sinh(pi*n*y/a)+v_bn(n)*sinh(pi*n/a*(b-y)));
	}
	
	return temp;
}

double w(double x,double y)// Calculate w
{
	int n;
	double temp=0;
	
	for(n=1;n<=N;n++)
	{
		temp+=sin(pi*n*y/b)*(w_an(n)*sinh(pi*n*x/b)+w_bn(n)*sinh(pi*n/b*(a-x)));
	}
	
	return temp;
}

//The solution is u=v+w

void get_parameters()
{
	GetCtrlVal (ph1, PANEL1_VY1, &vy1);
	GetCtrlVal (ph1, PANEL1_VY2, &vy2); 
	GetCtrlVal (ph1, PANEL1_VX1, &vx1); 
	GetCtrlVal (ph1, PANEL1_VX2, &vx2);
	
	GetCtrlVal (ph1, PANEL1_A, &a);
	GetCtrlVal (ph1, PANEL1_B, &b);
}

int set_graph_color(int x)
{
	switch(x)
	{
		case 0:
			{
				x= VAL_RED;
				break;
			}
		case 1:
			{
				x= VAL_BLUE;
				break;
			}
		case 2:
			{
				x= VAL_GREEN;
				break;
			}
		case 3:
			{
				x= VAL_CYAN;
				break;
			}
		case 4:
			{
				x= VAL_MAGENTA;
				break;
			}
		case 5:
			{
				x= VAL_YELLOW;
				break;
			}
		case 6:
			{
				x= VAL_DK_RED;
				break;
			}
		case 7:
			{
				x= VAL_DK_BLUE;
				break;
			}
		case 8:
			{
				x= VAL_DK_GREEN;
				break;
			}
		case 9:
			{
				x= VAL_DK_CYAN;
				break;
			}
		case 10:
			{
				x= VAL_DK_MAGENTA;
				break;
			}
		case 11:
			{
				x= VAL_DK_YELLOW;
				break;
			}
		case 12:
			{
				x= VAL_LT_GRAY;
				break;
			}
			
	}
	
	return x;
	
}

void cursor_off()
{
	SetCtrlAttribute (tab0, TABPANEL_cursor1, ATTR_DIMMED, 1);
	SetCtrlAttribute (tab0, TABPANEL_cursor2, ATTR_DIMMED, 1);
				
	SetCursorAttribute (tab0, TABPANEL_GRAPH_FIXED, 1, ATTR_CURSOR_COLOR, VAL_TRANSPARENT);
	SetCursorAttribute (tab0, TABPANEL_GRAPH_FIXED, 2, ATTR_CURSOR_COLOR, VAL_TRANSPARENT);
				
	SetCursorAttribute (tab0, TABPANEL_GRAPH_FIXED, 1, ATTR_CURSOR_ENABLED, 0);
	SetCursorAttribute (tab0, TABPANEL_GRAPH_FIXED, 2, ATTR_CURSOR_ENABLED, 0);
				
	SetCtrlVal (tab0, TABPANEL_cursor1, 0);
	SetCtrlVal (tab0, TABPANEL_cursor2, 0);
				
	SetCtrlVal (tab0, TABPANEL_cursor1_x, 0.0);
	SetCtrlVal (tab0, TABPANEL_cursor1_y, 0.0); 
	SetCtrlVal (tab0, TABPANEL_cursor2_x, 0.0); 
	SetCtrlVal (tab0, TABPANEL_cursor2_y, 0.0); 
	 
	SetCtrlAttribute (tab0, TABPANEL_cursor1_x, ATTR_DIMMED, 1);
	SetCtrlAttribute (tab0, TABPANEL_cursor1_y, ATTR_DIMMED, 1);
	
	SetCtrlAttribute (tab0, TABPANEL_cursor2_x, ATTR_DIMMED, 1);
	SetCtrlAttribute (tab0, TABPANEL_cursor2_y, ATTR_DIMMED, 1);
	 
}

void set_delta_off()//cursors of delta
{
	SetCtrlAttribute (tab0, TABPANEL_DELTA_X, ATTR_DIMMED, 1);
	SetCtrlAttribute (tab0, TABPANEL_DELTA_Y, ATTR_DIMMED, 1);
					
	SetCtrlVal (tab0, TABPANEL_DELTA_X, 0.0);
	SetCtrlVal (tab0, TABPANEL_DELTA_Y, 0.0);
	
}


/************************************** Main */ 
	
int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((ph1 = LoadPanel (0, "Project.uir", PANEL1)) < 0)
		return -1;
	DisplayPanel (ph1);
	
	get_parameters();
	
	SetCtrlAttribute (ph1, PANEL1_CANVAS, ATTR_PEN_MODE, VAL_XOR_MODE); 	
	SetCtrlAttribute (ph1, PANEL1_CANVAS, ATTR_PEN_COLOR, VAL_DK_YELLOW);
	
	CanvasDrawRect (ph1, PANEL1_CANVAS, MakeRect(canvas_btm-b*10,0,b*10,a*10), VAL_DRAW_FRAME);
	
	RunUserInterface ();
	DiscardPanel (ph1);
	return 0;
}

/************************************** Panel1 */ 

int CVICALLBACK QuitCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK canvas (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	int xcord,ycord;
	
	double double_xcord,double_ycord;
	
	switch (event)
	{
		case EVENT_LEFT_CLICK:
			
				GetRelativeMouseState (ph1, PANEL1_CANVAS, &xcord, &ycord, NULL, NULL, NULL);
				
				ycord+=-canvas_btm;
				ycord*=-1;
				
				double_xcord=xcord;
				double_ycord=ycord;
				
				double_xcord/=10;
				double_ycord/=10;
				
				  
				SetCtrlVal (ph1, PANEL1_X,double_xcord );
				SetCtrlVal (ph1, PANEL1_Y,double_ycord );
				
				SetCtrlAttribute (ph1, PANEL1_X, ATTR_FRAME_COLOR, VAL_RED); 
				SetCtrlAttribute (ph1, PANEL1_Y, ATTR_FRAME_COLOR, VAL_RED); 
				
				SetCtrlAttribute (ph1, PANEL1_TIMER, ATTR_ENABLED, 1);
				
			break;
	}
	
	return 0;
}

int CVICALLBACK timer (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
			
			SetCtrlAttribute (ph1, PANEL1_X, ATTR_FRAME_COLOR, VAL_WHITE);
			SetCtrlAttribute (ph1, PANEL1_Y, ATTR_FRAME_COLOR, VAL_WHITE);
			
			SetCtrlAttribute (ph1, PANEL1_TIMER, ATTR_ENABLED, 0);  

			break;
	}
	return 0;
}


int CVICALLBACK calc (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	double u;
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			GetCtrlVal (ph1, PANEL1_VY1, &vy1);
			GetCtrlVal (ph1, PANEL1_VY2, &vy2); 
			GetCtrlVal (ph1, PANEL1_VX1, &vx1); 
			GetCtrlVal (ph1, PANEL1_VX2, &vx2); 
			
			GetCtrlVal (ph1, PANEL1_X, &x);
			GetCtrlVal (ph1, PANEL1_Y, &y);
			
			if(x>a||x<0)
			{
				MessagePopup ("Error", "Choose point within range");
				return 0;
			}
			
			if(y>b||y<0)
			{
				MessagePopup ("Error", "Choose point within range");
				return 0;
			}
			
			u=v(x,y)+w(x,y);
			
			SetCtrlVal (ph1, PANEL1_SOL,u );
			
			break;
	}
	return 0;
}


int CVICALLBACK a_fun (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			CanvasDrawRect (ph1, PANEL1_CANVAS, MakeRect(canvas_btm-b*10,0,b*10,a*10), VAL_DRAW_FRAME);
			
			GetCtrlVal (ph1, PANEL1_A, &a);
			
			CanvasDrawRect (ph1, PANEL1_CANVAS, MakeRect(canvas_btm-b*10,0,b*10,a*10), VAL_DRAW_FRAME);
			
			if(a<0)
				MessagePopup ("Error", "Size has to be positive");
				
			 break;
	}
	return 0;
}

int CVICALLBACK b_fun (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			CanvasDrawRect (ph1, PANEL1_CANVAS, MakeRect(canvas_btm-b*10,0,b*10,a*10), VAL_DRAW_FRAME); 
			
			GetCtrlVal (ph1, PANEL1_B, &b);
			
			CanvasDrawRect (ph1, PANEL1_CANVAS, MakeRect(canvas_btm-b*10,0,b*10,a*10), VAL_DRAW_FRAME);
			
			if(b<0)
				MessagePopup ("Error", "Size has to be positive");

			break;
	}
	return 0;
}

int CVICALLBACK go_graph (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			ph2 = LoadPanel (0, "Project.uir", PANEL2);
			DisplayPanel (ph2);
			
			GetPanelHandleFromTabPage (ph2, PANEL2_TAB, 0, &tab0); 
			GetPanelHandleFromTabPage (ph2, PANEL2_TAB, 1, &tab1);
			
			get_parameters();
			
			GetCtrlVal (tab0, TABPANEL_fixed_ring,&fixed_y_or_x);
			
			SetCursorAttribute (tab0, TABPANEL_GRAPH_FIXED, 1, ATTR_CURSOR_COLOR, VAL_TRANSPARENT);
			SetCursorAttribute (tab0, TABPANEL_GRAPH_FIXED, 2, ATTR_CURSOR_COLOR, VAL_TRANSPARENT);
			
			SetCursorAttribute (tab0, TABPANEL_GRAPH_FIXED, 1, ATTR_CURSOR_ENABLED, 0);
			SetCursorAttribute (tab0, TABPANEL_GRAPH_FIXED, 2, ATTR_CURSOR_ENABLED, 0);
			
	}
	return 0;
}

/************************************** Panel2 */ 


int CVICALLBACK hide_panel2 (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			num_legend=0;
			
			DiscardPanel (ph2);
			
			reps=1;
			color_reps=0;
			
			break;
	}
	return 0;
}

int CVICALLBACK FIXED_RING (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			GetCtrlVal (tab0, TABPANEL_fixed_ring,&fixed_y_or_x);//choose to present graph for fixed y or x
			
			switch (fixed_y_or_x)
			{
				case 0: //y
					{
						SetCtrlVal (tab0, TABPANEL_txt_fixed_val, "Choose y value");
						
						ClearListCtrl (tab0, TABPANEL_RING);
						DeleteGraphPlot (tab0, TABPANEL_GRAPH_FIXED, -1, VAL_IMMEDIATE_DRAW);
						SetCtrlAttribute (tab0, TABPANEL_del_graph, ATTR_DIMMED,1);
						
						cursor_off();
						set_delta_off();  
						
						SetCtrlAttribute (tab0, TABPANEL_GRAPH_FIXED, ATTR_XNAME,"x[cm]");
						
						num_legend=0;
						 
						break;
					}
				case 1: //x
					{
						SetCtrlVal (tab0, TABPANEL_txt_fixed_val, "Choose x value");
						
						ClearListCtrl (tab0, TABPANEL_RING);
						DeleteGraphPlot (tab0, TABPANEL_GRAPH_FIXED, -1, VAL_IMMEDIATE_DRAW);
						SetCtrlAttribute (tab0, TABPANEL_del_graph, ATTR_DIMMED,1);
						
						cursor_off();
						set_delta_off(); 
						
						SetCtrlAttribute (tab0, TABPANEL_GRAPH_FIXED, ATTR_XNAME,"y[cm]");
						
						num_legend=0;
						 
						break;
					}
			}

			break;
	}
	return 0;
}

int CVICALLBACK show_graph_y (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	int i;
	double x_val=0;
	double y_val=0; 

	char y_text[10]={"y="};
	char x_text[10]={"x="};
	char temp[10];
	char ring_label[10];
	
	int color;
	
	int num_of_elem;
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			
			if(num_legend==4)//graph limit is 4
			{
				MessagePopup ("Graphs limit", "For your convenient the maximum numbers of graphs is 4, you may delete some");
				return 0;
			}
			
			GetCtrlVal (tab0, TABPANEL_CHOOSE_FIXED, &fixed_val);
			
			switch (fixed_y_or_x)
			{
				case 0: //y
					{
						if(fixed_val>b||fixed_val<0)
						{
							MessagePopup ("Error", "Choose point within range");
							return 0;
						}
			
							sprintf(temp, "%.2lf", fixed_val);
							strcat(y_text,temp);
							
							GetNumListItems (tab0, TABPANEL_RING, &num_of_elem);
							for(i=0;i<num_of_elem;i++)//checks if graph exist already
							{
								GetLabelFromIndex (tab0, TABPANEL_RING, i,ring_label );
								if(!(strcmp(ring_label,y_text)))
								{
									MessagePopup ("Graph exists", "There is already a graph for this value");
									return 0;
								}
							 }
							 
							 for(i=0;i<arr_num;i++)//create the array to display
							{
				
							fixed_arrx[i]=x_val;
							fixed_arry[i]= v(x_val,fixed_val)+w(x_val,fixed_val);
				
							x_val+=a/100;
				
							if(x_val>=a)
								break;
							}

						
						break;
					}
				case 1: //x
					{
						if(fixed_val>a||fixed_val<0)
						{
							MessagePopup ("Error", "Choose point within range");
							return 0;
						}
			
							sprintf(temp, "%.2lf", fixed_val);
							strcat(x_text,temp);
							
							GetNumListItems (tab0, TABPANEL_RING, &num_of_elem);
							for(i=0;i<num_of_elem;i++)
							{
								GetLabelFromIndex (tab0, TABPANEL_RING, i,ring_label );
								if(!(strcmp(ring_label,x_text)))
								{
									MessagePopup ("Graph exists", "There is already a graph for this value");
									return 0;
								}
							 }
							
							
							for(i=0;i<arr_num;i++)
							{
				
								fixed_arrx[i]=y_val;
								fixed_arry[i]= v(fixed_val,y_val)+w(fixed_val,y_val);
				
								y_val+=b/100;
				
								if(y_val>=b)
									break;
							}
							
						   
						break;
					}
			}
			
			SetCtrlAttribute (tab0, TABPANEL_del_graph, ATTR_DIMMED,0); 
			SetCtrlAttribute (tab0, TABPANEL_cursor1, ATTR_DIMMED, 0);
			SetCtrlAttribute (tab0, TABPANEL_cursor2, ATTR_DIMMED, 0);
			
			switch (reps)
			{
				case 1:
					{
						
					color=set_graph_color(color_reps);
					plot0=PlotXY (tab0, TABPANEL_GRAPH_FIXED, fixed_arrx, fixed_arry, i, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE,VAL_SOLID, 1, color);
					
					switch (fixed_y_or_x)
					{
						case 0: //y
							{
								
								SetPlotAttribute (tab0, TABPANEL_GRAPH_FIXED, plot0, ATTR_PLOT_LG_TEXT,y_text );
								InsertListItem (tab0, TABPANEL_RING, 0, y_text, plot0);
								
								break;
							}
						case 1: //x
							{
								
								SetPlotAttribute (tab0, TABPANEL_GRAPH_FIXED, plot0, ATTR_PLOT_LG_TEXT,x_text );
								InsertListItem (tab0, TABPANEL_RING, 0, x_text, plot0);
								
								break;
							}
					}
					
					
					break;
					}
					
				case 2:
					{
						
					color=set_graph_color(color_reps);
					plot1=PlotXY (tab0, TABPANEL_GRAPH_FIXED, fixed_arrx, fixed_arry, i, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE,VAL_SOLID, 1, color);
					
					switch (fixed_y_or_x)
					{
						case 0: //y
							{
								
								SetPlotAttribute (tab0, TABPANEL_GRAPH_FIXED, plot1, ATTR_PLOT_LG_TEXT,y_text );
								InsertListItem (tab0, TABPANEL_RING, -1, y_text, plot1);
								
								break;
							}
						case 1: //x
							{
								
								SetPlotAttribute (tab0, TABPANEL_GRAPH_FIXED, plot1, ATTR_PLOT_LG_TEXT,x_text );
								InsertListItem (tab0, TABPANEL_RING, -1, x_text, plot1);
								
								break;
							}
					}
					
					break;
					}
				case 3:
					{
						
					color=set_graph_color(color_reps);
					plot2=PlotXY (tab0, TABPANEL_GRAPH_FIXED, fixed_arrx, fixed_arry, i, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE,VAL_SOLID, 1, color);
					
					switch (fixed_y_or_x)
					{
						case 0: //y
							{
								
								SetPlotAttribute (tab0, TABPANEL_GRAPH_FIXED, plot2, ATTR_PLOT_LG_TEXT,y_text );
								InsertListItem (tab0, TABPANEL_RING, -1, y_text, plot2);
								
								break;
							}
						case 1: //x
							{
								
								SetPlotAttribute (tab0, TABPANEL_GRAPH_FIXED, plot2, ATTR_PLOT_LG_TEXT,x_text );
								InsertListItem (tab0, TABPANEL_RING, -1, x_text, plot2);
								
								break;
							}
					}
					
					
					break;
					}
				case 4:
					{
						
					color=set_graph_color(color_reps);
					plot3=PlotXY (tab0, TABPANEL_GRAPH_FIXED, fixed_arrx, fixed_arry, i, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE,VAL_SOLID, 1, color);
					
					switch (fixed_y_or_x)
					{
						case 0: //y
							{
								
								SetPlotAttribute (tab0, TABPANEL_GRAPH_FIXED, plot3, ATTR_PLOT_LG_TEXT,y_text );
								InsertListItem (tab0, TABPANEL_RING, -1, y_text, plot3);
								
								break;
							}
						case 1: //x
							{
								
								SetPlotAttribute (tab0, TABPANEL_GRAPH_FIXED, plot3, ATTR_PLOT_LG_TEXT,x_text );
								InsertListItem (tab0, TABPANEL_RING, -1, x_text, plot3);
								
								break;
							}
					}
					
				
					break;
					}
			}
			
			GetNumLegendItems (tab0, TABPANEL_GRAPH_FIXED, &num_legend);
		
			color_reps++;
			if(color_reps==13)
				color_reps=0;
			
			
			 
			if(reps==4)
			{
				reps=1;
			}
			
			reps++;
			 
			break;
	}
	return 0;
}


int CVICALLBACK DEL_GRAPH (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	int delg;
	int index;
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			GetCtrlVal (tab0, TABPANEL_RING, &delg);
			
			GetCtrlIndex (tab0, TABPANEL_RING, &index );
			
			DeleteListItem (tab0, TABPANEL_RING, index, 1);
			DeleteGraphPlot (tab0, TABPANEL_GRAPH_FIXED, delg, VAL_IMMEDIATE_DRAW);
			
			GetNumLegendItems (tab0, TABPANEL_GRAPH_FIXED, &num_legend);
			
			if(num_legend==0)
			{
				SetCtrlAttribute (tab0, TABPANEL_del_graph, ATTR_DIMMED, 1);
			
				cursor_off();
				set_delta_off();  
			}
			
	
			break;
	}
	return 0;
}

 

int CVICALLBACK CURSOR1 (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			GetCtrlVal (tab0, TABPANEL_cursor1,&c1_flag);
			
			switch (c1_flag)//cursor on/off
			{
				case 0:
					
					SetCursorAttribute (tab0, TABPANEL_GRAPH_FIXED, 1, ATTR_CURSOR_ENABLED, 0);
					SetCursorAttribute (tab0, TABPANEL_GRAPH_FIXED, 1, ATTR_CURSOR_COLOR, VAL_TRANSPARENT);
					
					SetCtrlAttribute (tab0, TABPANEL_cursor1_x, ATTR_DIMMED, 1);
					SetCtrlAttribute (tab0, TABPANEL_cursor1_y, ATTR_DIMMED, 1);
					
					SetCtrlVal (tab0, TABPANEL_cursor1_x, 0.0);
					SetCtrlVal (tab0, TABPANEL_cursor1_y, 0.0);
					
					set_delta_off();
					
					break;
					
				case 1:
					
					SetCursorAttribute (tab0, TABPANEL_GRAPH_FIXED, 1, ATTR_CURSOR_ENABLED, 1);
					SetCursorAttribute (tab0, TABPANEL_GRAPH_FIXED, 1, ATTR_CURSOR_COLOR, VAL_BLUE);
					
					SetCtrlAttribute (tab0, TABPANEL_cursor1_x, ATTR_DIMMED, 0);
					SetCtrlAttribute (tab0, TABPANEL_cursor1_y, ATTR_DIMMED, 0);
					
					break;
			}
			
			
			break;
	}
	return 0;
}

int CVICALLBACK CURSOR2 (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			GetCtrlVal (tab0, TABPANEL_cursor2,&c2_flag); 
			
			switch (c2_flag)
			{
				case 0:
					
					SetCursorAttribute (tab0, TABPANEL_GRAPH_FIXED, 2, ATTR_CURSOR_ENABLED, 0);
					SetCursorAttribute (tab0, TABPANEL_GRAPH_FIXED, 2, ATTR_CURSOR_COLOR, VAL_TRANSPARENT);
					
					SetCtrlAttribute (tab0, TABPANEL_cursor2_x, ATTR_DIMMED, 1);
					SetCtrlAttribute (tab0, TABPANEL_cursor2_y, ATTR_DIMMED, 1);
					
					SetCtrlVal (tab0, TABPANEL_cursor2_x, 0.0);
					SetCtrlVal (tab0, TABPANEL_cursor2_y, 0.0);
					
					set_delta_off();
					
					break;
					
				case 1:
					
					SetCursorAttribute (tab0, TABPANEL_GRAPH_FIXED, 2, ATTR_CURSOR_ENABLED, 1);
					SetCursorAttribute (tab0, TABPANEL_GRAPH_FIXED, 2, ATTR_CURSOR_COLOR, VAL_RED);
					
					SetCtrlAttribute (tab0, TABPANEL_cursor2_x, ATTR_DIMMED, 0);
					SetCtrlAttribute (tab0, TABPANEL_cursor2_y, ATTR_DIMMED, 0);
					
					
					break;
			}
			
			
			break;
	}
	return 0;
}


int CVICALLBACK graph_fixed (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	double c1_x,c1_y,c2_x,c2_y;
	double delta_x,delta_y;
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			
			if(c1_flag==1)
			{
			
				GetGraphCursor (tab0, TABPANEL_GRAPH_FIXED, 1, &c1_x, &c1_y);
				SetCtrlVal (tab0, TABPANEL_cursor1_x, c1_x);
				SetCtrlVal (tab0, TABPANEL_cursor1_y, c1_y);
			}
			
			if(c2_flag==1)
			{
				GetGraphCursor (tab0, TABPANEL_GRAPH_FIXED, 2, &c2_x, &c2_y);
				SetCtrlVal (tab0, TABPANEL_cursor2_x, c2_x);
				SetCtrlVal (tab0, TABPANEL_cursor2_y, c2_y);
			}
			
			if((c1_flag==1)&&(c2_flag==1))
			{
				SetCtrlAttribute (tab0, TABPANEL_DELTA_X, ATTR_DIMMED, 0);
				SetCtrlAttribute (tab0, TABPANEL_DELTA_Y, ATTR_DIMMED, 0);
				
				delta_x=(c1_x-c2_x);
				if(delta_x<0)
					delta_x*=-1;
				  
				delta_y=(c1_y-c2_y);
				if(delta_y<0)
					delta_y*=-1;
				
				SetCtrlVal (tab0, TABPANEL_DELTA_X, delta_x);
				SetCtrlVal (tab0, TABPANEL_DELTA_Y, delta_y);
				
			}
		
			break;
	}
	return 0;
}


int CVICALLBACK PLOT3D (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	double		t[num_3d] = {0.0}, zData[num_3d][num_3d] = {0.0};
	VARIANT		zVt, tVt;
	int			i, j;
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			SetCtrlAttribute (tab1, TABPANEL_2_plot3d, ATTR_DIMMED, 1);
			
			GetObjHandleFromActiveXCtrl (tab1, TABPANEL_2_CWGRAPH3D, &graphHandle);
			GetObjHandleFromActiveXCtrl (tab1, TABPANEL_2_CWGRAPH3D, &plotHandle);
			   
			for (i = 0; i < num_3d; ++i)
			{
					t[i]=(i/100.0)*2*pi;
			}
			
			for (i = 0; i < num_3d; ++i)
				for(j = 0; j < num_3d; ++j)
					zData[j][i]=v(t[i],t[j])+w(t[i],t[j]);
					
				 
			CA_VariantSet1DArray(&tVt, CAVT_DOUBLE, num_3d, t);
			CA_VariantSet2DArray(&zVt, CAVT_DOUBLE, num_3d, num_3d, zData);
			
			CW3DGraphLib__DCWGraph3DPlot3DSurface(graphHandle, NULL, tVt, tVt, zVt, CA_DEFAULT_VAL);
			
			CW3DGraphLib__DCWGraph3DPlot3DSurface(plotHandle, NULL, tVt, tVt, zVt, CA_DEFAULT_VAL);
			
			break;
	}
	return 0;
}

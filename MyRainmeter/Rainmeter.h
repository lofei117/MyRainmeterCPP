
#include "RmControl.h"

// Matrix 
typedef struct Margin{
	int left;
	int right;
	int top;
	int bottom;
}Margin;

// CRainmeter

class CRainmeter
{	
	// Constructor and Destructor
public:
	CRainmeter();
	virtual ~CRainmeter();


	// public methods
public:
	// Organize the data as a whole section
	CString ToString() const;

	// private methods
private:

	// protected methods
protected:

	// public attributes
public:
	////General Options
	int m_Update;// Default: 1000
	CString m_DynamicWindowSize;// Default: 0
	CString m_DragMargins;//Default: 0,0,0,0
	int m_TransitionUpdate;// Default: 100
	CString m_ToolTipHidden;//Default: 0;
	//Action;
	CString m_OnRefreshAction;//Action to execute when the skin is loaded or refreshed.
	CString m_OnUpdateAction;//Action to execute on each Update of the skin.
	CString m_OnCloseAction;//Action to execute when the skin is unloaded or when Rainmeter is closed.
	CString m_OnFocusAction;//Action to execute when the skin recieves focus in Windows (set by clicking the mouse on the skin).
	CString m_OnUnfocusAction;//Action to execute when the skin loses focus in Windows.

	////Background options
	//General Image Options
	////ImageCrop
	CString m_ImageCrop;
	
	CString m_Greyscale;//default 0£»
	CString m_ImageTint;// default 255,255,255,255
	int m_ImageAlpha;//default 255
	CString m_ImageFlip;// Default: None
	float m_ImageRotate;//default 0.0
	//ColorMatrixN
	CString m_ColorMatrix1[5];//default 1; 0; 0; 0; 0
	CString m_ColorMatrix2[5];//default 0; 1; 0; 0; 0
	CString m_ColorMatrix3[5];//default 0; 0; 1; 0; 0
	CString m_ColorMatrix4[5];//default 0; 0; 0; 1; 0
	CString m_ColorMatrix5[5];//default 0; 0; 0; 0; 1
	//other
	CString m_Background;//Path of a background image file.
	CString m_BackgroundMode;// Default: 1  [0-4]
	CString m_BackgroundMargins;// Default: 0,0,0,0
	CString m_SolidColor;
	CString m_SolidColor2;// Default: 0,0,0,0
	float m_GradientAngle;
	CString m_BevelType;// Default: 0

	/////Context options
	vector<wstring> m_ContextTitle;
	vector<wstring> m_ContextAction;
	////Aero Blur options
	CString m_Blur;// Default: 0
	//vector<CBlurRegion> m_BlurRegion;

	// private attributes
private:

	// protected attributes
protected:

};



class CMetadata
{
	// Constructor and Destructor
public:
	CMetadata();
	virtual ~CMetadata();

	//public attribute
public:
	CString m_Name;
	CString m_Author;
	CString m_Information;
	CString m_Version;
	CString m_License;

	//public methods
public:
	CString ToString() const;

};

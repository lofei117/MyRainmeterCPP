#pragma once

#define MAX_LINE_LENGTH	4096

enum ToolTipType
{	
	Normal=0,
	Ballon=1
};
enum ToolTipIcon
{
	Info,
	Warning,
	Error,
	Question
};

enum MeterType
{
	Bar=1,
	Bitmap,
	Button,
	Histogram,
	Image,
	Line,
	Rotator,
	Roundline,
	String
};

enum MeansureType
{

};

enum ImageCropOrigin
{
	TopLeft=1,
	TopRight,
	BottomRight,
	BottomLeft,
	Center
};


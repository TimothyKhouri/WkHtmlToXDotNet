// WkHtmlToXDotNet.cpp

#include "stdafx.h"
#include "WkHtmlToXDotNet.h"
#include <stdbool.h>
#include <stdio.h>
#include "wkhtmltox\pdf.h"
#include "wkhtmltox\image.h"

using namespace System;
using namespace Runtime::InteropServices;

static WkHtmlToXDotNet::HtmlToXConverter::HtmlToXConverter()
{
	wkhtmltopdf_init(false);
}

static const char* DotNetStringToCharPointer(String^ value)
{
	auto pointerToValue = Marshal::StringToHGlobalAnsi(value);
	auto result = static_cast<char*>(pointerToValue.ToPointer());
	return result;
}

array<Byte>^ WkHtmlToXDotNet::HtmlToXConverter::ConvertToPdf(String^ html)
{
	wkhtmltopdf_global_settings * gs;
	wkhtmltopdf_object_settings * os;
	wkhtmltopdf_converter * c;
	unsigned char * data;

	gs = wkhtmltopdf_create_global_settings();
	os = wkhtmltopdf_create_object_settings();
	c = wkhtmltopdf_create_converter(gs);
	wkhtmltopdf_add_object(c, os, DotNetStringToCharPointer(html));

	if (wkhtmltopdf_convert(c) == false)
	{
		wkhtmltopdf_destroy_converter(c);
		return nullptr;
	}

	long length = wkhtmltopdf_get_output(c, (const unsigned char **)&data);
	auto resultBuffer = gcnew array<Byte>(length);
	auto sourcePointer = IntPtr(data);

	Marshal::Copy(sourcePointer, resultBuffer, 0, length);

	wkhtmltopdf_destroy_converter(c);
	return resultBuffer;
}

array<Byte>^ WkHtmlToXDotNet::HtmlToXConverter::ConvertToPng(String^ html)
{
	return ConvertToPng(html, 0, 0);
}

array<Byte>^ WkHtmlToXDotNet::HtmlToXConverter::ConvertToPng(String^ html, int width, int height)
{
	wkhtmltoimage_global_settings * gs;
	wkhtmltoimage_converter * c;
	unsigned char * data;

	gs = wkhtmltoimage_create_global_settings();
	wkhtmltoimage_set_global_setting(gs, "fmt", "png");
	c = wkhtmltoimage_create_converter(gs, DotNetStringToCharPointer(html));

	if (width != 0) {
		wkhtmltoimage_set_global_setting(gs, "screenWidth", DotNetStringToCharPointer(width.ToString()));
	}
	if (height != 0) {
		wkhtmltoimage_set_global_setting(gs, "screenHeight", DotNetStringToCharPointer(height.ToString()));
	}

	if (wkhtmltoimage_convert(c) == false)
	{
		wkhtmltoimage_destroy_converter(c);
		return nullptr;
	}

	long length = wkhtmltoimage_get_output(c, (const unsigned char **)&data);
	auto resultBuffer = gcnew array<Byte>(length);
	auto sourcePointer = IntPtr(data);

	Marshal::Copy(sourcePointer, resultBuffer, 0, length);

	wkhtmltoimage_destroy_converter(c);
	return resultBuffer;
}
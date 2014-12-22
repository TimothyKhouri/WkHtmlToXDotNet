// WkHtmlToXDotNet.h

#pragma once

#include <stdbool.h>
#include <stdio.h>
#include "wkhtmltox\pdf.h"
#include "wkhtmltox\image.h"

namespace WkHtmlToXDotNet {

	public ref class HtmlToXConverter
	{
	private:
		static HtmlToXConverter();

	public:
		static array<System::Byte>^ ConvertToPdf(System::String^ html);

		static array<System::Byte>^ ConvertToPng(System::String^ html);

		static array<System::Byte>^ ConvertToPng(System::String^ html, int width, int height);
	};
}

WkHtmlToXDotNet
===============

If you've seen the great "WkHtmlToPdf" tool (http://wkhtmltopdf.org/), but wanted to use it in your .NET (C# or VB) application, you've come to the right place. Simply include this .NET DLL in your .NET project, make sure the "wkhtmltox.dll" file is in your bin directory (because it's a dependancy), and voila! You will be able to use the following methods:

* HtmlToXConverter.ConvertToPdf
* HtmlToXConverter.ConvertToPng

This is what your code will look like:

    var pdfData = HtmlToXConverter.ConvertToPdf("<h1>SOO COOL!</h1>");

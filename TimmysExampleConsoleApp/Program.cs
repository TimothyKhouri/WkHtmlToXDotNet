using System;
using System.Diagnostics;
using System.IO;
using WkHtmlToXDotNet;

namespace TimmysExampleConsoleApp
{
	class Program
	{
		[STAThread] // <-- This is NOT required, but does prevent the lib from complaining a bit.
		static void Main(string[] args)
		{
			Console.WriteLine("Type some HTML to convert and press [ENTER].");

			string usersHtml = Console.ReadLine();

			string fullHtml = @"
<html>
	<head>
		<style type=""text/css"">
			h1 { border-bottom: solid 2px #369; }
		</style>
	</head>
	<body>
		<h1>This is my title</h1>

		<p>This is a paragraph, and below is a happy face!</p>

		<img src=""data:image/png;base64,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"" />

		<div>" + usersHtml + @"</div>
	</body>
</html>
";

			var pdfData = HtmlToXConverter.ConvertToPdf(fullHtml);

			if (pdfData == null)
			{
				Console.WriteLine("The conversion failed for some reason :'(");
			}
			else
			{
				Console.WriteLine("Youre PDF is {0} bytes in size!", fullHtml.Length);

				Console.WriteLine("Press [ENTER] to view the PDF");

				Console.ReadLine();

				string tempPdfFile = Path.GetTempFileName() + ".pdf";

				File.WriteAllBytes(tempPdfFile, pdfData);

				Process.Start(tempPdfFile);
			}
		}
	}
}

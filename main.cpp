#include "pbPlots.hpp"
#include "supportLib.hpp"
#include <../fparser.hh>
#include <vector>
#include <complex>
#include <iostream>

int main()
{
	double x1, y1, x2, y2, x3, y3;
	std::string function;

	std::cout << "f(z)=";
	std::cin >> function;
	std::cout << "z=";
	std::cin >> x1 >> y1;


	std::complex<double> z1(x1, y1);
	std::complex<double> z2(x2, y2);

	FunctionParser_cd fp;
	fp.Parse(function, "z");
	z2 = fp.Eval(&z1);
	x2 = z2.real();
	y2 = z2.imag();

	if (abs(x1) > abs(x2)) {
		x3 = abs(x1) + 10;
	}
	else {
		x3 = abs(x2) + 10;
	}
	if (abs(y1) > abs(y2)) {
		y3 = abs(y1) + 10;
	}
	else {
		y3 = abs(y2) + 10;
	}

	std::cout << "z1 = " << z1;
	std::cout << std::endl;
	std::cout << "z2 = " << z2;

	RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();
	
	double xsa[] = { x1 };
	std::vector<double> xs(xsa, xsa + sizeof(xsa) / sizeof(double));
	double ysa[] = { y1 };
	std::vector<double> ys(ysa, ysa + sizeof(ysa) / sizeof(double));

	double xsb[] = { x2 };
	std::vector<double> xs2(xsb, xsb + sizeof(xsb) / sizeof(double));
	double ysb[] = { y2 };
	std::vector<double> ys2(ysb, ysb + sizeof(ysb) / sizeof(double));
	
	double xsc[] = { x3, -1 * x3 };
	std::vector<double> xs3(xsc, xsc + sizeof(xsc) / sizeof(double));
	double ysc[] = { x3, -1 * x3 };
	std::vector<double> ys3(ysc, ysc + sizeof(ysc) / sizeof(double));
	
	ScatterPlotSeries* series = GetDefaultScatterPlotSeriesSettings();
	series->xs = &xs;
	series->ys = &ys;
	series->linearInterpolation = false;
	series->pointType = toVector(L"dots");
	series->color = CreateRGBColor(1, 0, 0);

	ScatterPlotSeries* series2 = GetDefaultScatterPlotSeriesSettings();
	series2->xs = &xs2;
	series2->ys = &ys2;
	series2->linearInterpolation = false;
	series2->pointType = toVector(L"dots");
	series2->color = CreateRGBColor(0, 1, 0);
	
	ScatterPlotSeries* series3 = GetDefaultScatterPlotSeriesSettings();
	series3->xs = &xs3;
	series3->ys = &ys3;
	series3->linearInterpolation = false;
	series3->pointType = toVector(L"dots");
	series3->color = CreateRGBColor(0, 0, 0);
	
	ScatterPlotSettings* settings = GetDefaultScatterPlotSettings();
	settings->width = 600;
	settings->height = 400;
	settings->autoBoundaries = true;
	settings->autoPadding = true;
	settings->title = toVector(L"");
	settings->xLabel = toVector(L"y");
	settings->yLabel = toVector(L"x");
	settings->scatterPlotSeries->push_back(series);
	settings->scatterPlotSeries->push_back(series2);
	settings->scatterPlotSeries->push_back(series3);
	
	DrawScatterPlotFromSettings(imageReference, settings);
	
	std::vector<double>* pngdata = ConvertToPNG(imageReference->image);
	WriteToFile(pngdata, "main.png");
	DeleteImage(imageReference->image);
	
	return 0;

}
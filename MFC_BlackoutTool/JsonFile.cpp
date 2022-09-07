#include "pch.h"
#include "JsonFile.h"

void JsonFile::jsonSave(vector<CDraw> vCDraw,CString filePath) {

	string str;
	Json::Value root;
	Json::Value shapes;
	Json::Value polygon;
	Json::Value points;
	Json::Value point;
	
	//도형의 개수
	root["count"] = vCDraw.size();
	

	for (auto cdraw : vCDraw)
	{
		polygon["count"] = cdraw.m_vPoint.size();
		for (auto pt : cdraw.m_vPoint) {

			point.clear();
			point.append(pt.X);
			point.append(pt.Y);
			points.append(point);
		}

		polygon["points"] = points;
		shapes.append(polygon);

		points.clear();
	}

	root["shapes"] = shapes;

	Json::StyledWriter writer;
	str = writer.write(root);

	std::ofstream stream;

	filePath = filePath + _T(".json");
	stream.open(filePath);
	stream << str;
	stream.close();
}
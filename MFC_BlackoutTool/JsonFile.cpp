#include "pch.h"
#include "JsonFile.h"

void JsonFile::jsonSave(vector<CDraw>const &vCDraw, DicomImg const &dcmImg) {

	string str;
	Json::Value root;
	Json::Value shapes;
	Json::Value polygon;
	Json::Value points;
	Json::Value point;

	//도형의 개수

	root["model name"] = std::string(CT2CA(dcmImg.m_modelName));
	root["manufacturer"] = std::string(CT2CA(dcmImg.m_manufacturer));
	root["rows"] = dcmImg.m_dcmImg.rows;
	root["columns"] = dcmImg.m_dcmImg.cols;
	root["count"] = vCDraw.size();

	for (auto cdraw : vCDraw)
	{
		polygon["count"] = cdraw.m_vPoint.size();
		for (auto pt : cdraw.m_vPoint) {

			point.clear();

			int x = (pt.X > 0) ? pt.X : 0;
			int y = (pt.Y > 0) ? pt.Y : 0;

			point.append(x);
			point.append(y);
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

	CString filePath = dcmImg.m_dcmPath + _T(".json");
	stream.open(filePath);
	stream << str;
	stream.close();
}

void JsonFile::jsonLoad(vector<CDraw> &vCDraw, CString filePath) {

	filePath = filePath + _T(".json");
	std::ifstream json_file(filePath, std::ios::in);

	if (!json_file.is_open()) return;

	Json::Value root;
	Json::Value shapes;
	Json::Value points;
	Json::Value point;

	json_file >> root;
	json_file.close();

	shapes = root["shapes"];

	//points = shapes["points"];

	for (int i = 0; i < root["count"].asInt(); i++) {
		if (shapes[i]["count"].asInt() == 4) {

			CDraw tmp;
			tmp.m_nType = 1;
			points.clear();
			points = shapes[i]["points"];

			for (int j = 0; j < 4; j++) {
				point.clear();
				point = points[j];
				tmp.m_vPoint.push_back(Gdiplus::Point(point[0].asInt(), point[1].asInt()));
			}
			vCDraw.push_back(tmp);
		}
	}
}

BOOL JsonFile::isSaved(vector<CDraw> const &vCDraw, CString filePath) {


	//filePath = filePath + _T(".json");
	//std::ifstream json_file(filePath, std::ios::in);

	//if (!json_file.is_open()) return FALSE;

	//Json::Value root;
	//Json::Value shapes;
	//Json::Value points;
	//Json::Value point;

	//json_file >> root;
	//json_file.close();

	//shapes = root["shapes"];

	////points = shapes["points"];

	//for (int i = 0; i < root["count"].asInt(); i++) {
	//	if (shapes[i]["count"].asInt() == 4) {

	//		//tmp.m_nType = 1;
	//		points.clear();
	//		points = shapes[i]["points"];

	//		for (int j = 0; j < 4; j++) {
	//			point.clear();
	//			point = points[j];
	//			if (!(vCDraw[i].m_vPoint[j].X == point[0].asInt() && vCDraw[i].m_vPoint[j].Y == point[1].asInt())) {
	//				return FALSE;
	//			}
	//		}
	//	}
	//}

	return TRUE;
}

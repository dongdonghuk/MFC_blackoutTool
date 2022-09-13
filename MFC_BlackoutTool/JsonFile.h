#pragma once
#include "CDraw.h"
#include "DicomImg.h"

class JsonFile
{
public:
	

public:
	void jsonSave(vector<CDraw>const &vCDraw, DicomImg const &dcmImg);
	void jsonLoad(vector<CDraw> &vCDraw, CString filePath);
	BOOL isSaved(vector<CDraw> const &vCDraw, CString filePath);

};


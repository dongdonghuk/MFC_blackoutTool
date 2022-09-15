#include "pch.h"
#include "DicomImg.h"

DicomImg::DicomImg()
{
	m_dcmImg = NULL;
}

DicomImg::~DicomImg()
{

}

void DicomImg::ImgAlignment(CRect& rect) {

	if (!(m_dcmImg.empty())) {

		float width = rect.Width(), height = rect.Height();
		float rectRate = width / height;
		float imgRate = (float)m_dcmImg.size().width / (float)m_dcmImg.size().height;

		int priority_range = ((imgRate > rectRate && imgRate < 1) || (imgRate < rectRate&& imgRate >= 1)) ? 1 : 0;
		if (imgRate < 1) priority_range = 1 - priority_range;

		if (priority_range) width = height * imgRate;
		else height = width / imgRate;

		int interval_x = (rect.right - (int)width) / 2, interval_y = (rect.bottom - (int)height) / 2;

		if (priority_range) {
			rect.left = interval_x; rect.right = (int)width; rect.top = 0; rect.bottom = (int)height;
		}
		else {
			rect.left = 0; rect.right = (int)width; rect.top = interval_y; rect.bottom = (int)height;
		}
	}
}


void DicomImg::dcmRead(CString filePath, CString fileName) {

	m_dcmName = fileName;
	m_dcmPath = filePath;

	//dicom load
	DJDecoderRegistration::registerCodecs();
	DcmFileFormat DcmFileFormat;
	OFCondition cond = DcmFileFormat.loadFile(std::string(CT2CA(m_dcmPath)).c_str());

	if (cond.good()) {
		//AfxMessageBox(_T("DCM파일 로드성공"));

		DcmDataset* dataset = DcmFileFormat.getDataset();
		E_TransferSyntax xfer = dataset->getOriginalXfer();

		m_ptrDicomImage = make_shared<DicomImage>(&DcmFileFormat, xfer, CIF_AcrNemaCompatibility, 0, 0);
		

		if (m_ptrDicomImage->getStatus() != EIS_Normal)
		{
			AfxMessageBox(_T("DicomImage 생성 실패"));
			return;
		}
	}

	else if (cond.bad()) {
		AfxMessageBox(_T("DCM파일 로드실패 : ") + CString(cond.text()));
		return;
	}
	m_nFrame = m_ptrDicomImage->getFrameCount();


	// dicom to mat

	DcmDataset* dataset = DcmFileFormat.getDataset();
	OFString strColorType;
	OFString strModelName;
	OFString strManufacturer;

	dataset->findAndGetOFString(DCM_PhotometricInterpretation, strColorType);
	dataset->findAndGetOFString(DCM_ManufacturerModelName, strModelName);
	dataset->findAndGetOFString(DCM_Manufacturer, strManufacturer);

	m_modelName = strModelName.c_str();
	m_manufacturer = strManufacturer.c_str();
	
	// grayscale
	if (strColorType == "MONOCHROME1" || strColorType == "MONOCHROME2") {
		Mat mat(int(m_ptrDicomImage->getHeight()), int(m_ptrDicomImage->getWidth()), CV_8U, (uchar*)m_ptrDicomImage->getOutputData(8, 0));
		cvtColor(mat, mat, COLOR_GRAY2BGRA);
		m_dcmImg = mat;
	}

	// true color
	else if(strColorType == "PALETTE COLOR" || strColorType == "RGB") {
		Mat mat(int(m_ptrDicomImage->getHeight()), int(m_ptrDicomImage->getWidth()), CV_8UC3, (uchar*)m_ptrDicomImage->getOutputData(8, 0));
		cvtColor(mat, mat, COLOR_RGB2BGRA);
		m_dcmImg = mat;
	}
	//YBR color type은 미처리

	DJDecoderRegistration::cleanup();

	// mat to bitmap

	m_bitImg = make_shared<Bitmap>((INT)m_dcmImg.size().width, (INT)m_dcmImg.size().height, m_dcmImg.step,
		PixelFormat32bppARGB, m_dcmImg.data);

	//imshow("test",m_dcmImg);
}


void DicomImg::DrawImage(Graphics& g, Graphics& memDC, CWnd* cwnd) {

	if (!(m_dcmImg.empty())) {

		m_pt = (0, 0);
		m_dAligmentRate = 1;

		CRect rect;
		cwnd->GetClientRect(rect);

		double width = rect.Width();
		double height = rect.Height();

		ImgAlignment(rect);

		memDC.TranslateTransform(rect.left, rect.top);


		m_pt.x = rect.left;
		m_pt.y = rect.top;


		if (rect.left == 0) {
			m_dAligmentRate = width / m_dcmImg.size().width;
		}
		else {
			m_dAligmentRate = height / m_dcmImg.size().height;
		}

		memDC.ScaleTransform(m_dAligmentRate, m_dAligmentRate);
		memDC.DrawImage(m_bitImg.get(), 0, 0);
	}
}

BOOL DicomImg::empty() {
	return m_dcmImg.empty();
}


void DicomImg::erase(vector<CDraw> &vCdraw) {

	for (auto cdraw : vCdraw) {
		cv::Rect rectRoi(cv::Point(cdraw.m_vPoint[0].X, cdraw.m_vPoint[0].Y), cv::Point(cdraw.m_vPoint[2].X, cdraw.m_vPoint[2].Y));
		Mat matRoi = m_dcmImg(rectRoi);
		matRoi.setTo(Scalar(0, 0, 0));
	}



	//DJDecoderRegistration::registerCodecs();
	//DcmFileFormat DcmFileFormat;
	//OFCondition cond = DcmFileFormat.loadFile(std::string(CT2CA(m_dcmPath)).c_str());
	//DcmDataset* dataset = DcmFileFormat.getDataset();
	//E_TransferSyntax xfer = dataset->getOriginalXfer();

	//if (cond.good()) {
	//	//AfxMessageBox(_T("DCM파일 로드성공"));
	//}

	//else if (cond.bad()) {
	//	AfxMessageBox(_T("DCM파일 로드실패 : ") + CString(cond.text()));
	//	return;
	//}
	////m_nFrame = m_ptrDicomImage->getFrameCount();

	//OFString strColorType;
	//dataset->findAndGetOFString(DCM_PhotometricInterpretation, strColorType);

	//Mat matTmp;

	//// grayscale
	//if (strColorType == "MONOCHROME1" || strColorType == "MONOCHROME2") {
	//	cvtColor(m_dcmImg, matTmp, COLOR_BGRA2GRAY);
	//}

	//// true color
	//else if (strColorType == "PALETTE COLOR" || strColorType == "RGB") {
	//	cvtColor(m_dcmImg, matTmp, COLOR_BGRA2RGB);
	//}
	////YBR color type은 미처리

	//imshow("test", matTmp);

	//dataset->putAndInsertUint8Array(DCM_PixelData, matTmp.data, matTmp.rows*matTmp.cols*matTmp.channels());

	//DJDecoderRegistration::cleanup();

}


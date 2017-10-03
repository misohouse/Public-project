
// rbs_viewerDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "rbs_viewer.h"
#include "rbs_viewerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Crbs_viewerDlg 대화 상자



Crbs_viewerDlg::Crbs_viewerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RBS_VIEWER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Crbs_viewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ed_folder_path, ed_folder_path_var);
	DDX_Control(pDX, hw_os_info, hw_os_info_var);
	DDX_Control(pDX, list_prog_info, list_prog_info_var);
	DDX_Control(pDX, list_process_info, list_process_info_var);
}

BEGIN_MESSAGE_MAP(Crbs_viewerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(bt_select_path, &Crbs_viewerDlg::OnBnClickedselectpath)
	ON_BN_CLICKED(bt_extrct, &Crbs_viewerDlg::OnBnClickedextrct)
	ON_NOTIFY(LVN_COLUMNCLICK, list_process_info, &Crbs_viewerDlg::OnLvnColumnclickprocessinfo)
	ON_BN_CLICKED(bt_csv, &Crbs_viewerDlg::OnBnClickedcsv)
	ON_NOTIFY(LVN_COLUMNCLICK, list_prog_info, &Crbs_viewerDlg::OnLvnColumnclickproginfo)
END_MESSAGE_MAP()


// Crbs_viewerDlg 메시지 처리기

BOOL Crbs_viewerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	list_process_info_var.InsertColumn(0, _T(""), LVCFMT_CENTER, 0);
	list_process_info_var.InsertColumn(1, _T("Process Name"), LVCFMT_CENTER, 300);
	list_process_info_var.InsertColumn(2, _T("Time (running)"), LVCFMT_CENTER, 150);

	list_prog_info_var.InsertColumn(0, _T(""), LVCFMT_CENTER, 0);
	list_prog_info_var.InsertColumn(1, _T("Program Name"), LVCFMT_CENTER, 300);
	list_prog_info_var.InsertColumn(2, _T("Install Date (heuristic)"), LVCFMT_CENTER, 150);
	list_prog_info_var.InsertColumn(3, _T("RootDirPath"), LVCFMT_CENTER, 300);
	list_prog_info_var.InsertColumn(4, _T("Program Version"), LVCFMT_CENTER, 150);
	list_prog_info_var.InsertColumn(5, _T("OSVersion At InstallTime"), LVCFMT_CENTER, 150);
	list_prog_info_var.InsertColumn(6, _T("Publisher"), LVCFMT_CENTER, 150);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void Crbs_viewerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void Crbs_viewerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

	ed_folder_path_var.LineScroll(ed_folder_path_var.GetLineCount());
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR Crbs_viewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int get_value(char* value) {
	int tmp_0 = (int)(Byte)value[0];
	int tmp_1 = (int)(Byte)value[1] << 8;
	int tmp_2 = (int)(Byte)value[2] << 16;
	int tmp_3 = (int)(Byte)value[3] << 24;

	return tmp_0 + tmp_1 + tmp_2 + tmp_3;
}

// Replace string 'from' -> 'to'
void ReplaceAll(std::string &str, const std::string& from, const std::string& to) {
	size_t start_pos = 0; // string Check from the beginning
	while ((start_pos = str.find(from, start_pos)) != std::string::npos)  // Until I can not find 'from'
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // For avoiding duplicate checking and from from.length() > to.length ()
	}
}

void Crbs_viewerDlg::OnBnClickedselectpath()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BROWSEINFO BrInfo;
	TCHAR szBuffer[512];                                      // Path storage buffer

	::ZeroMemory(&BrInfo, sizeof(BROWSEINFO));
	::ZeroMemory(szBuffer, 512);

	BrInfo.hwndOwner = GetSafeHwnd();

	BrInfo.lpszTitle = _T("Select folder which stores rbs files.");
	BrInfo.ulFlags = BIF_NEWDIALOGSTYLE | BIF_EDITBOX | BIF_RETURNONLYFSDIRS;

	LPITEMIDLIST pItemIdList = ::SHBrowseForFolder(&BrInfo);

	::SHGetPathFromIDList(pItemIdList, szBuffer);
	//The selected path is stored in szBuffer.

	SetDlgItemTextW(ed_folder_path, szBuffer);
}

void Crbs_viewerDlg::UpdateArrow(void) {
	CHeaderCtrl* pHeaderCtrl = list_prog_info_var.GetHeaderCtrl();
	HDITEM hdItem;
	TCHAR szBuffer[256];
	::ZeroMemory(&hdItem, sizeof(hdItem));
	::ZeroMemory(szBuffer, 256);

	hdItem.mask = -1;
	hdItem.pszText = szBuffer;
	hdItem.cchTextMax = 256;
	pHeaderCtrl->GetItem(0, &hdItem);

	hdItem.fmt &= ~(HDF_SORTDOWN | HDF_SORTUP);

	if (m_Ascending)
		hdItem.fmt |= HDF_SORTDOWN;
	else
		hdItem.fmt |= HDF_SORTUP;

	pHeaderCtrl->SetItem(0, &hdItem);
}

int CALLBACK Crbs_viewerDlg::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParam)
{
	BOOL Ascending = (BOOL)lParam;
	LPCTSTR s1 = (LPCTSTR)(DWORD)lParam1;
	LPCTSTR s2 = (LPCTSTR)(DWORD)lParam2;
	if (Ascending)
		return _tcscmp(s1, s2);
	else
		return -(_tcscmp(s1, s2));
	return 0;
}

void Crbs_viewerDlg::OnBnClickedextrct()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	list_prog_info_var.DeleteAllItems();
	list_process_info_var.DeleteAllItems();
	hw_os_info_var.DeleteAllItems();

	_wfinddata_t fd;
	long handle;
	CString folder_path;
	
	GetDlgItemTextW(ed_folder_path, folder_path);
	folder_path += L"\\*.rbs";

	handle = _wfindfirst(LPWSTR(LPCTSTR(folder_path)), &fd);

	short result = 1;
	short version_check;
	std::ifstream ifs;

	ifs.imbue(std::locale("kor"));

	if (handle == -1)
	{
		MessageBox(L"There were no rbs files.\n");
		SetDlgItemText(ed_folder_path, NULL);
	}

	else {
		list_prog_info_var.SetExtendedStyle(LVS_EX_DOUBLEBUFFER | LVS_EX_GRIDLINES);
		list_process_info_var.SetExtendedStyle(LVS_EX_DOUBLEBUFFER | LVS_EX_GRIDLINES);

		bool os_ver_check = false;
		bool mainboard_check = false;
		bool storage_check = false;
		bool memory_check = false;
		bool processor_check = false;

		int process_index = 0;
		int prog_index = 0;

		CString mem_val;
		CString phy_storage_val, sys_storage_val;
		CString hard_val_1, hard_val_2, hard_val_3, hard_val_4, hard_val_5;
		CString os_installdate_tmp, os_val_1, os_val_2, os_val_3;
		CString proc_val_1, proc_val_2, proc_val_3, proc_val_4, proc_val_5;

		while (1) {
			if (result < 0) {
				break;
			}

			CString name_tmp = fd.name;
			CString parsing_folder_path;
			name_tmp = name_tmp.Right(4);
			if (name_tmp != L".rbs") {
				result = _wfindnext(handle, &fd);
				continue;
			}

			GetDlgItemTextW(ed_folder_path, parsing_folder_path);
			parsing_folder_path += L"\\";
			parsing_folder_path += fd.name;

			// File open
			ifs.open(parsing_folder_path, std::ios_base::binary);

			// Calculate size of file
			ifs.seekg(0, std::ios::end);
			int file_size = ifs.tellg();

			// Return to the first index
			ifs.seekg(0, std::ios::beg);

			// Signature check
			char signature[8];
			ifs.read(signature, 8);

			// rbs file version check
			if (signature[7] == '3')
				version_check = 1;
			else if (signature[7] == '5')
				version_check = 2;
			else if (signature[7] == '7')
				version_check = 3;

			char time_value[8];
			ifs.read(time_value, 8);
			
			// Start offset of data block to be input next
			char next_block_offset_tmp[4];
			int next_block_offset;
			ifs.seekg(4, std::ios::cur);
			ifs.read(next_block_offset_tmp, 4);
			next_block_offset = get_value(next_block_offset_tmp);

			if (version_check == 1)
				next_block_offset += 42;
			else
				next_block_offset += 53;

			// Index of data block to be input next
			char next_index_offset_tmp[4];
			int next_index_offset;
			ifs.seekg(12, std::ios::cur);
			ifs.read(next_index_offset_tmp, 4);
			next_index_offset = get_value(next_index_offset_tmp);

			// Variables to check if data has been overwritten
			bool overwrite = false;
			char overwrite_check[4];

			// Depending on the rbs file version, the end of the moving header is different
			// Move to end of header
			if (version_check == 1)
				ifs.seekg(2, std::ios::cur); 
			else
				ifs.seekg(13, std::ios::cur);

			// The data block index value must be checked to ensure that the data has been overwritten.
			// Skip unknown data at the beginning of the data block
			if (version_check == 1)
				ifs.seekg(4, std::ios::cur);
			else
				ifs.seekg(12, std::ios::cur);

			// If the data is overwritten, set 'flag' to 'true' 
			ifs.read(overwrite_check, 4);
			if (overwrite_check[0] == '\0' && overwrite_check[1] == '\0' && overwrite_check[2] == '\0' && overwrite_check[3] == '\0')
				overwrite = false;
			else
				overwrite = true;

			// Return to original position (start of data block)
			if (version_check == 1)
				ifs.seekg(-8, std::ios::cur);
			else
				ifs.seekg(-16, std::ios::cur);

			// Data block index variable
			char data_index_tmp[4];
			int data_index;

			// Variable for the size of the data in the form 'Encoded'
			char base64_data_tmp[4];
			int base64_data_length;

			// Variable for the size of the data in the form 'Compressed'
			char data_length_tmp[4];
			int data_length;

			char base64_check[2];
			char base64_tmp[4];
			int base64_tmp_length;

			bool overwrite_paring = false;

			char last_index[4] = { 0, };

			// If the data is overwritten from the front
			if (overwrite) {
				while (1) {
					ifs.read(overwrite_check, 3);
					int aaaa = ifs.tellg();
					if (overwrite_check[0] == '\0' && overwrite_check[1] == '\0' && overwrite_check[2] == '\0') {
						ifs.seekg(-5, std::ios::cur);
						char index_check[2] = { 0, };
						ifs.read(index_check, 2);
						if (index_check[0] != '\0' && index_check[1] != '\0') {
							ifs.seekg(-2, std::ios::cur);
							ifs.read(last_index, 4);
							last_index[0] -= 1;
							break;
						}
						else {
							if (version_check == 3)
								ifs.seekg(-20, std::ios::cur);

							else
								ifs.seekg(-16, std::ios::cur);

							ifs.read(last_index, 4);
							break;
						}
					}
					else
						ifs.seekg(-2, std::ios::cur);
				}

				while (1) {
					char find_value[4] = { 0, };
					ifs.read(find_value, 4);
					// When you find the last index position
					if (!strcmp(find_value, last_index)) {
						if (version_check == 1)
							ifs.seekg(-8, std::ios::cur);
						else
							ifs.seekg(-16, std::ios::cur);
						break;
					}
					else
						ifs.seekg(-3, std::ios::cur);
				}
			}

			// If the data has not been overwritten
			else
				overwrite_paring = true;

			while (1) {
				// The position of the file pointer is equal to or greater than the start position of the next block to be written,
				// which means that the part to be parsed is finished.
				int end_check = ifs.tellg();
				if ((next_block_offset <= end_check || end_check == -1) && overwrite_paring == true)
					break;

				// Skip unknown data
				if (version_check == 1)
					ifs.seekg(4, std::ios::cur);
				else
					ifs.seekg(12, std::ios::cur);

				// Data block index parsing
				ifs.read(data_index_tmp, 4);
				data_index = get_value(data_index_tmp);

				if (version_check == 1 || version_check == 2) {
					// Parsing the size of the encoded Data
					ifs.read(base64_data_tmp, 4);
					base64_data_length = get_value(base64_data_tmp);

					// Parsing the size of compressed data
					ifs.read(data_length_tmp, 4);
					data_length = get_value(data_length_tmp);
				}
				else {
					// Parsing the size of the encoded Data
					ifs.read(base64_data_tmp, 4);
					base64_data_length = get_value(base64_data_tmp);

					// Skip unknown data
					ifs.seekg(4, std::ios::cur);

					// Parsing the size of compressed data
					ifs.read(data_length_tmp, 4);
					data_length = get_value(data_length_tmp);
				}

				// Skip unknown data
				if (version_check == 2)
					ifs.seekg(5, std::ios::cur);
				else
					ifs.seekg(6, std::ios::cur);

				Bytef* deflated_data_without_header = (Bytef*)malloc(sizeof(Bytef) * data_length);
				memset(deflated_data_without_header, 0, data_length);

				// Start of data area
				// If the data to be parsed has been overwritten and moved to the beginning,
				if ((base64_data_length + data_length + ifs.tellg()) > file_size) {
					// Skip encoded data
					ifs.seekg(base64_data_length, std::ios::cur);

					int alpha = file_size - ifs.tellg();
					ifs.read((char*)deflated_data_without_header, alpha);

					// Additional data size to read
					int beta = data_length - alpha;

					// Move the file offset to the beginning of the data block to read additional data
					if (version_check == 1)
						ifs.seekg(42, std::ios::beg);
					else
						ifs.seekg(53, std::ios::beg);

					// Read the rest of the data
					ifs.read((char*)(deflated_data_without_header + alpha), beta);

					overwrite_paring = true;
				}
				// If the data to be parsed is not overwritten
				else {
					// If the size of the encoded data is zero,
					// Skip encoded data and parse the compressed data
					if (base64_data_length == 0) {
						ifs.read((char*)deflated_data_without_header, data_length);
					}
					// If the size of the encoded data is not zero,
					// Since the compressed data will come after the encoded data, 
					// the compressed data is parsed after moving the file pointer by the encoded data.
					else {
						ifs.seekg(base64_data_length, std::ios::cur);
						ifs.read((char*)deflated_data_without_header, data_length);
					}
				}

				// Data to inflate from here
				Bytef* deflated_data = (Bytef*)malloc(sizeof(Bytef) * (data_length + 2));
				memset(deflated_data, 0, data_length + 2);
				deflated_data[0] = '\x78';
				deflated_data[1] = '\x9c';

				memcpy(deflated_data + 2, deflated_data_without_header, data_length);

				Bytef* inflated_data = (Bytef*)malloc(sizeof(Bytef) * (data_length * 100));
				memset(inflated_data, 0, data_length * 100);

				z_stream infstream;
				infstream.zalloc = Z_NULL;
				infstream.zfree = Z_NULL;
				infstream.opaque = Z_NULL;
				infstream.avail_in = (uInt)(data_length + 2); // size of input
				infstream.next_in = deflated_data; // input char array
				infstream.avail_out = (uInt)(data_length * 100); // size of output
				infstream.next_out = inflated_data; // output char array

				inflateInit(&infstream);
				inflate(&infstream, Z_NO_FLUSH);
				int inflated_size = infstream.total_out;
				inflateEnd(&infstream);

				Json::Value root = { 0, };
				Json::Reader reader;

				string tmp_out = { '[' };
				string tmp_out2 = { 0, };
				tmp_out2 = (char*)inflated_data;

				ReplaceAll(tmp_out2, std::string("}}\r\n{\"ver\""), std::string("}},\r\n{\"ver\""));
				ReplaceAll(tmp_out2, std::string(","), std::string(",\n"));
				tmp_out.append(tmp_out2);
				tmp_out.append("]");

				free(deflated_data);
				free(deflated_data_without_header);
				free(inflated_data);

				bool parsingSuccessful = reader.parse(tmp_out, root);
				if (!parsingSuccessful) {
					MessageBox(L"Failed to parse configuration");
					SetDlgItemText(ed_folder_path, NULL);
					break;
				}

				for (unsigned int i = 0; i < root.size(); i++) {
					if (root[i]["name"].asString().find("AppInteractivitySummary") != std::string::npos) {
						if (!strcmp(root[i]["data"]["AppId"].asString().c_str(), "<FailedLookup>"))
							continue;

						string tmp_appid= root[i]["data"]["AppId"].asString();
						if (*tmp_appid.c_str() == 0)
							continue;

						const char* tmp_appid2 = strrchr((char*)tmp_appid.c_str(), '!');
						char tmp_appid3[200] = { 0, };

						int j = 0;
						for (int i = 1; i < strlen(tmp_appid2); i++) {
							tmp_appid3[j] = tmp_appid2[i];
							j++;
						}

						CString data_tmp;
						data_tmp.Format(L"%s", CA2W(root[i]["time"].asString().c_str(), CP_UTF8));
						CString ymd = data_tmp.Left(10);
						CString time = data_tmp.Mid(11, 8);
						CString space = L" ";

						list_process_info_var.InsertItem(process_index, _T(""));
						list_process_info_var.SetItem(process_index, 1, LVIF_TEXT, CA2W(tmp_appid3, CP_UTF8), 0, 0, 0, NULL);
						list_process_info_var.SetItem(process_index, 2, LVIF_TEXT, ymd + space + time, 0, 0, 0, NULL);

						process_index++;
					}

					if (root[i]["name"].asString().find("InventoryApplicationAdd") != std::string::npos) {						
						CString data_tmp;
						data_tmp.Format(L"%s", CA2W(root[i]["data"]["InstallDate"].asString().c_str(),CP_UTF8));
						CString year = data_tmp.Mid(6, 4);
						CString month = data_tmp.Left(2);
						CString date = data_tmp.Mid(3, 2);
						CString time = data_tmp.Mid(11, 8);
						CString space = L" ";
						CString bar = L"-";

						list_prog_info_var.InsertItem(prog_index, _T(""));
						list_prog_info_var.SetItem(prog_index, 1, LVIF_TEXT, CA2W(root[i]["data"]["Name"].asString().c_str(), CP_UTF8), 0, 0, 0, NULL);
						list_prog_info_var.SetItem(prog_index, 2, LVIF_TEXT, year + bar + month + bar + date + space + time, 0, 0, 0, NULL);
						list_prog_info_var.SetItem(prog_index, 3, LVIF_TEXT, CA2W(root[i]["data"]["RootDirPath"].asString().c_str(), CP_UTF8), 0, 0, 0, NULL);
						list_prog_info_var.SetItem(prog_index, 4, LVIF_TEXT, CA2W(root[i]["data"]["Version"].asString().c_str(), CP_UTF8), 0, 0, 0, NULL);
						list_prog_info_var.SetItem(prog_index, 5, LVIF_TEXT, CA2W(root[i]["data"]["OSVersionAtInstallTime"].asString().c_str(), CP_UTF8), 0, 0, 0, NULL);
						list_prog_info_var.SetItem(prog_index, 6, LVIF_TEXT, CA2W(root[i]["data"]["Publisher"].asString().c_str(), CP_UTF8), 0, 0, 0, NULL);

						prog_index++;
					}

					if (root[i]["name"].asString().find("Census") != std::string::npos) {
						if (root[i]["name"].asString().find("OS") != std::string::npos){
							os_installdate_tmp.Format(L"%s", CA2W(root[i]["data"]["OSOOBEDateTime"].asString().c_str(), CP_UTF8));
							os_val_1 = CA2W(root[i]["os"].asString().c_str(), CP_UTF8);
							os_val_2 = CA2W(root[i]["osVer"].asString().c_str(), CP_UTF8);
							os_val_3 = CA2W(root[i]["data"]["OSEdition"].asString().c_str(), CP_UTF8);
						}

						if (root[i]["name"].asString().find("Hardware") != std::string::npos){
							hard_val_1 = CA2W(root[i]["data"]["DeviceName"].asString().c_str(),CP_UTF8);
							hard_val_2 = CA2W(root[i]["data"]["OEMManufacturerName"].asString().c_str(), CP_UTF8);
							hard_val_3 = CA2W(root[i]["data"]["OEMModelNumber"].asString().c_str(), CP_UTF8);
							hard_val_4 = CA2W(root[i]["data"]["OEMModelBaseBoard"].asString().c_str(), CP_UTF8);
							hard_val_5 = CA2W(root[i]["data"]["OEMModelBaseBoardVersion"].asString().c_str(), CP_UTF8);
						}

						if (root[i]["name"].asString().find("Storage") != std::string::npos){
							phy_storage_val.Format(L"%d", root[i]["data"]["PrimaryDiskTotalCapacity"].asInt());								
							sys_storage_val.Format(L"%d", root[i]["data"]["SystemVolumeTotalCapacity"].asInt());
						}

						if (root[i]["name"].asString().find("Memory") != std::string::npos)
							mem_val.Format(L"%d", root[i]["data"]["TotalPhysicalRAM"].asInt());

						if (root[i]["name"].asString().find("Processor") != std::string::npos){
							proc_val_1.Format(L"%d", root[i]["data"]["ProcessorCores"].asInt());
							proc_val_2.Format(L"%d", root[i]["data"]["ProcessorClockSpeed"].asInt());
							proc_val_3 = CA2W(root[i]["data"]["ProcessorManufacturer"].asString().c_str(), CP_UTF8);
							proc_val_4 = CA2W(root[i]["data"]["ProcessorModel"].asString().c_str(), CP_UTF8);
							proc_val_5 = CA2W(root[i]["data"]["ProcessorIdentifier"].asString().c_str(), CP_UTF8);
						}
					}
				}
			}
			result = _wfindnext(handle, &fd);

			ifs.close();
		}

		// Insert Treecontrol items
		// OS information
		HTREEITEM os_root;
		CString osd = L"OS Install Date : ";
		CString ymd = os_installdate_tmp.Left(10);
		CString time = os_installdate_tmp.Mid(11, 8);
		CString space = L" ";
		CString t1 = L"OS : ";
		CString t2 = L"OS Version : ";
		CString t3 = L"OSEdition : ";
		os_root = hw_os_info_var.InsertItem(L"OS", TVI_ROOT, TVI_LAST);
		hw_os_info_var.InsertItem(t1 + os_val_1, os_root, TVI_LAST);
		hw_os_info_var.InsertItem(t2 + os_val_2, os_root, TVI_LAST);
		hw_os_info_var.InsertItem(t3 + os_val_3, os_root, TVI_LAST);
		hw_os_info_var.InsertItem(osd + ymd + space + time, os_root, TVI_LAST);

		// Mainboard inforamtion
		HTREEITEM mainboard_root;
		mainboard_root = hw_os_info_var.InsertItem(L"Mainboard", TVI_ROOT, TVI_LAST);
		t1 = L"DeviceName : ";
		t2 = L"OEMManufacturerName : ";
		t3 = L"OEMModelNumber : ";
		CString t4 = L"OEMModelBaseBoard : ";
		CString t5 = L"OEMModelBaseBoardVersion : ";
		hw_os_info_var.InsertItem(t1 + hard_val_1, mainboard_root, TVI_LAST);
		hw_os_info_var.InsertItem(t2 + hard_val_2, mainboard_root, TVI_LAST);
		hw_os_info_var.InsertItem(t3 + hard_val_3, mainboard_root, TVI_LAST);
		hw_os_info_var.InsertItem(t4 + hard_val_4, mainboard_root, TVI_LAST);
		hw_os_info_var.InsertItem(t5 + hard_val_5, mainboard_root, TVI_LAST);

		// Storage information
		HTREEITEM storage_root;
		CString mb = L"MB";
		storage_root = hw_os_info_var.InsertItem(L"Storage", TVI_ROOT, TVI_LAST);
		t1 = L"PrimaryDiskTotalCapacity  : ";
		hw_os_info_var.InsertItem(t1 + phy_storage_val + mb, storage_root, TVI_LAST);
		t2 = L"SystemVolumeTotalCapacity  : ";
		hw_os_info_var.InsertItem(t2 + sys_storage_val + mb, storage_root, TVI_LAST);

		// Memory information
		HTREEITEM memory_root;
		memory_root = hw_os_info_var.InsertItem(L"Memory", TVI_ROOT, TVI_LAST);
		CString cp = L"Capacity : ";
		hw_os_info_var.InsertItem(cp + mem_val + mb, memory_root, TVI_LAST);

		// Processor information
		HTREEITEM processor_root;
		processor_root = hw_os_info_var.InsertItem(L"Processor", TVI_ROOT, TVI_LAST);
		CString core = L"ProcessorCores : ";
		hw_os_info_var.InsertItem(core + proc_val_1, processor_root, TVI_LAST);
		CString pcs = L"ProcessorClockSpeed : ";
		CString mhz = L"MHz";
		hw_os_info_var.InsertItem(pcs + proc_val_2 + mhz, processor_root, TVI_LAST);
		t1 = L"ProcessorManufacturer : ";
		hw_os_info_var.InsertItem(t1 + proc_val_3, processor_root, TVI_LAST);
		t2 = L"ProcessorModel : ";
		hw_os_info_var.InsertItem(t2 + proc_val_4, processor_root, TVI_LAST);
		t3 = L"ProcessorIdentifier : ";
		hw_os_info_var.InsertItem(t3 + proc_val_5, processor_root, TVI_LAST);
	}
}

void Crbs_viewerDlg::OnLvnColumnclickprocessinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int column = pNMLV->iSubItem;
	if (column == m_SortedColumn) {
		m_Ascending = !m_Ascending;
	}
	else {
		m_Ascending = TRUE;
	}
	m_SortedColumn = column;
	int cnt = list_process_info_var.GetItemCount();
	CString* str = new CString[cnt];

	for (int i = 0; i<cnt; i++) {
		str[i] = list_process_info_var.GetItemText(i, column);
		list_process_info_var.SetItemData(i, (DWORD)(LPCTSTR)str[i]);
	}
	list_process_info_var.SortItems(CompareFunc, (LPARAM)m_Ascending);

	delete[]str;

	*pResult = 0;
}


void Crbs_viewerDlg::OnNMCustomdrawproginfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	LPNMLVCUSTOMDRAW  lplvcd = (LPNMLVCUSTOMDRAW)pNMHDR;
	int iRow = lplvcd->nmcd.dwItemSpec;

	switch (lplvcd->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
		return;
	}

	// Modify item text and or background
	case CDDS_ITEMPREPAINT:
	{
		if (lplvcd->nmcd.uItemState && CDIS_SELECTED)
		{
			lplvcd->clrText = RGB(255, 255, 255);
			lplvcd->clrTextBk = RGB(0, 0, 150);
		}
		// If you want the sub items the same as the item,
		// set *pResult to CDRF_NEWFONT
		//*pResult = CDRF_NOTIFYSUBITEMDRAW;
		*pResult = CDRF_NEWFONT;
		return;
	}

	// Modify sub item text and/or background
	case CDDS_SUBITEM | CDDS_PREPAINT | CDDS_ITEM:
	{
		*pResult = CDRF_DODEFAULT;
		return;
	}
	}
}


void Crbs_viewerDlg::OnBnClickedcsv()
{
	if (list_process_info_var.GetItemCount() == 0 && list_prog_info_var.GetItemCount() == 0){
		AfxMessageBox(L"There are no results!");
	}

	else {
		// If a list of installed programs exists
		if (list_process_info_var.GetItemCount() != 0) {
			CString insert_data;
			CStdioFile prog_file;
			prog_file.Open(L"(rbs)Installed_Programs.csv", CStdioFile::modeCreate | CStdioFile::modeWrite | CStdioFile::typeText);			

			prog_file.WriteString(L"Program Name\t");
			prog_file.WriteString(L"Install Date\t");
			prog_file.WriteString(L"RootDirPath\t");
			prog_file.WriteString(L"Program Version\t");
			prog_file.WriteString(L"OSVersion At InstallTime\t");
			prog_file.WriteString(L"Publisher\n");

			setlocale(LC_ALL, "korean");

			for (int i = 0; i < list_prog_info_var.GetItemCount(); i++) {
				insert_data = list_prog_info_var.GetItemText(i, 1);
				prog_file.WriteString(insert_data + L",");

				insert_data = list_prog_info_var.GetItemText(i, 2);
				prog_file.WriteString(insert_data + L",");

				insert_data = list_prog_info_var.GetItemText(i, 3);
				prog_file.WriteString(insert_data + L",");

				insert_data = list_prog_info_var.GetItemText(i, 4);
				prog_file.WriteString(insert_data + L",");

				insert_data = list_prog_info_var.GetItemText(i, 5);
				prog_file.WriteString(insert_data + L",");

				insert_data = list_prog_info_var.GetItemText(i, 6);
				// If there is no ',' in the data
				if (insert_data.Find(L",") == NULL) 
					prog_file.WriteString(insert_data + L"\n");
				// If there is a ',' in the data
				else {
					insert_data.Replace(L",\n", L", ");
					prog_file.WriteString(L"\"" + insert_data + L"\"\n");
				}
			}
			prog_file.Close();
		}
		
		if (list_prog_info_var.GetItemCount() != 0) {
			CString insert_data;
			CStdioFile process_file;
			process_file.Open(L"(rbs)Executed_Process.csv", CStdioFile::modeCreate | CStdioFile::modeWrite | CStdioFile::typeText);

			process_file.WriteString(L"Process Name,");
			process_file.WriteString(L"Time (running)\n");

			setlocale(LC_ALL, "korean");

			for (int i = 0; i < list_process_info_var.GetItemCount(); i++) {
				insert_data = list_process_info_var.GetItemText(i, 1);
				process_file.WriteString(insert_data + L",");

				insert_data = list_process_info_var.GetItemText(i, 2);
				process_file.WriteString(insert_data + L"\n");
			}
			process_file.Close();
		}

		AfxMessageBox(L"Create CSV Files Done!");		
	}
}


void Crbs_viewerDlg::OnLvnColumnclickproginfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	int column = pNMLV->iSubItem;
	if (column == m_SortedColumn) {
		m_Ascending = !m_Ascending;
	}
	else {
		m_Ascending = TRUE;
	}
	m_SortedColumn = column;
	int cnt = list_prog_info_var.GetItemCount();
	CString* str = new CString[cnt];
	
	for (int i = 0; i<cnt; i++) {
		str[i] = list_prog_info_var.GetItemText(i, column);
		list_prog_info_var.SetItemData(i, (DWORD)(LPCTSTR)str[i]);
	}
	list_prog_info_var.SortItems(CompareFunc, (LPARAM)m_Ascending);
	
	delete[]str;
	
	*pResult = 0;
}

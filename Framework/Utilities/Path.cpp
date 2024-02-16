#include "Framework.h"
#include "Path.h"

// 파일 존재 여부
bool Path::ExistFile(string path)
{
	return ExistFile(String::ToWstring(path));
}

bool Path::ExistFile(wstring path)
{
	// 파일이나 폴더의 속성을 알아보는 함수 DWORD를 반환
	// 실패하면 INVALID_FILE_ATTRIBUTES를 반환
	DWORD fileValue = GetFileAttributes(path.c_str());

	// 파일이 존재하면 true 아니면 false를 반환
	return fileValue != INVALID_FILE_ATTRIBUTES;
}

// 폴더 존재 여부
bool Path::ExistDirectory(string path)
{
	return ExistDirectory(String::ToWstring(path));
}

bool Path::ExistDirectory(wstring path)
{
	DWORD attribute = GetFileAttributes(path.c_str());

	BOOL temp = (attribute != INVALID_FILE_ATTRIBUTES && attribute & FILE_ATTRIBUTE_DIRECTORY);

	return temp == TRUE;
}

// 병합
string Path::Combine(string path1, string path2)
{
	return path1 + path2;
}

wstring Path::Combine(wstring path1, wstring path2)
{
	return path1 + path2;
}

string Path::Combine(vector<string> paths)
{
	string temp = "";
	for (string path : paths)
		temp += path;

	return temp;
}

wstring Path::Combine(vector<wstring> paths)
{
	wstring temp = L"";
	for (wstring path : paths)
		temp += path;

	return temp;
}

// 입력된 경로에서 폴더 이름을 반환
string Path::GetDirectoryName(string path)
{
	String::Replace(&path, "\\", "/");
	size_t index = path.find_last_of('/');

	return path.substr(0, index + 1);
}

wstring Path::GetDirectoryName(wstring path)
{
	String::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('/');

	return path.substr(0, index + 1);
}

// 파일의 확장자를 반환
string Path::GetExtension(string path)
{
	String::Replace(&path, "\\", "/");
	size_t index = path.find_last_of('.');

	return path.substr(index + 1, path.length());
}

wstring Path::GetExtension(wstring path)
{
	String::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('.');

	return path.substr(index + 1, path.length());
}

// 파일 이름과 확장자를 반환
string Path::GetFileName(string path)
{
	String::Replace(&path, "\\", "/");
	size_t index = path.find_last_of('/');

	return path.substr(index + 1, path.length());
}

wstring Path::GetFileName(wstring path)
{
	String::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('/');

	return path.substr(index + 1, path.length());
}

// 파일 이름만 반환
string Path::GetFileNameWithoutExtension(string path)
{
	string fileName = GetFileName(path);

	size_t index = fileName.find_last_of('.');
	return fileName.substr(0, index);
}

wstring Path::GetFileNameWithoutExtension(wstring path)
{
	wstring fileName = GetFileName(path);

	size_t index = fileName.find_last_of('.');
	return fileName.substr(0, index);
}

const WCHAR* Path::ImageFilter = L"Image\0*.png;*.bmp;*.jpg";
const WCHAR* Path::ShaderFilter = L"HLSL file\0*.hlsl";
const WCHAR* Path::TextFilter = L"Text file\0*.txt";
const WCHAR* Path::TileFilter = L"Tile file\0*.png;*.bmp;*.jpg;*.json;*.data";
const WCHAR* Path::TMapFilter = L"TMap file\0*.tmap";

void Path::OpenFileDialog(wstring defaultFileName, const WCHAR* fileTypeFilter, const wstring defaultFolder, const function<void(wstring)> callback, HWND parentWindowHandle)
{
	WCHAR name[255];
	wcscpy_s(name, defaultFileName.c_str());

	wstring tempFolder = defaultFolder;

	OPENFILENAME ofn;
	Zero(ofn);

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = parentWindowHandle;				// 부모창 핸들
	ofn.lpstrFilter = fileTypeFilter;				// 파일 유형 필터
	ofn.lpstrFile = name;							// 파일 이름
	ofn.lpstrFileTitle = L"불러오기";				// 대화 상자 제목
	ofn.nMaxFile = 255;								// 파일 이름 최대 크기
	ofn.lpstrInitialDir = tempFolder.c_str();		// 기본 폴더 경로
	ofn.Flags = OFN_NOCHANGEDIR;					// 대화 상자 옵션

	if (GetOpenFileName(&ofn) == TRUE)					// 대화 상자 열고 사용자가 파일을 선택하면
	{
		if (callback != NULL)							// 콜백 함수가 지정되어 있으면
		{
			wstring loadName = name;					// 선택된 파일의 경로를 저장
			String::Replace(&loadName, L"\\", L"/");	// 경로에서 역슬래시를 슬래시로 변환

			callback(loadName);							// 콜백 함수 호출
		}
	}
}

void Path::SaveFileDialog(wstring defaultFileName, const WCHAR* fileTypeFilter, const wstring defaultFolder, const function<void(wstring)> callback, HWND parentWindowHandle)
{
	WCHAR name[255];
	wcscpy_s(name, defaultFileName.c_str());

	wstring tempFolder = defaultFolder;

	OPENFILENAME ofn;
	Zero(ofn);

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = parentWindowHandle;				// 부모창 핸들
	ofn.lpstrFilter = fileTypeFilter;				// 파일 유형 필터
	ofn.lpstrFile = name;							// 파일 이름
	ofn.lpstrFileTitle = L"저장하기";				// 대화 상자 제목
	ofn.nMaxFile = 255;								// 파일 이름 최대 크기
	ofn.lpstrInitialDir = tempFolder.c_str();		// 기본 폴더 경로
	ofn.Flags = OFN_NOCHANGEDIR;					// 대화 상자 옵션

	if (GetSaveFileName(&ofn) == TRUE)					// 대화 상자 열고 사용자가 파일을 선택하면
	{
		if (callback != NULL)							// 콜백 함수가 지정되어 있으면
		{
			wstring saveName = name;					// 선택된 파일의 경로를 저장
			String::Replace(&saveName, L"\\", L"/");	// 경로에서 역슬래시를 슬래시로 변환

			callback(saveName);							// 콜백 함수 호출
		}
	}
}

// 지정된 폴더에서 특정 유형의 파일들을 찾아 반환하는 함수
void Path::GetFiles(vector<string>* files, string path, string filter, bool bFindSubFolder)
{
	vector<wstring> wFiles;
	wstring wPath = String::ToWstring(path);
	wstring wFilter = String::ToWstring(path);

	GetFiles(&wFiles, wPath, wFilter, bFindSubFolder);

	for (wstring str : wFiles)
		files->push_back(String::ToString(str));
}

void Path::GetFiles(vector<wstring>* files, wstring path, wstring filter, bool bFindSubFolder)
{
	wstring file = path + filter;

	WIN32_FIND_DATA findData;
	HANDLE handle = FindFirstFile(file.c_str(), &findData);	// 첫 번째 파일 검색
	if (handle != INVALID_HANDLE_VALUE)	// 파일이 발견되면
	{
		do
		{
			// 발견된 파일이 디렉토리인 경우
			if (findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
			{
				// 하위 폴더 검색 옵션 활성화 & 발견된 디렉토리가 '.'으로 시작하지 않은 경우
				if (bFindSubFolder == true && findData.cFileName[0] != '.')
				{
					// 발견된 디렉토리의 전체 경로 설정
					wstring folder = path + wstring(findData.cFileName) + L"/";
					// 재귀적으로 하위 폴더에서 파일 검색
					GetFiles(files, folder, filter, bFindSubFolder);
				}
			}
			else // 발견된 파일이 디렉토리가 아닌 경우
			{
				// 발견된 파일의 전체 경로 생성
				wstring fileName = path + wstring(findData.cFileName);
				// 벡터에 발견된 파일의 전체 경로 추가
				files->push_back(fileName);
			}
		} while (FindNextFile(handle, &findData)); // 다음 파일 검색
		FindClose(handle); // 파일 검색 종료
	}
}

// 주어진 경로에 폴더가 존재하지 않는 경우 생성하는 함수
void Path::CreateFolder(string path)
{
	CreateFolder(String::ToWstring(path));
}

void Path::CreateFolder(wstring path)
{
	if(ExistDirectory(path) == false)
		CreateDirectory(path.c_str(), NULL);
}

// 주어진 경로의 모든 하위 폴더 생성
void Path::CreateFolders(string path)
{
	CreateFolder(String::ToWstring(path));
}

void Path::CreateFolders(wstring path)
{
	String::Replace(&path, L"\\", L"/");

	vector<wstring> folders;
	String::SplitString(&folders, path, L"/");

	wstring temp = L"";
	for (wstring folder : folders)
	{
		temp += folder + L"/";
		CreateFolder(temp);
	}
}

/*
	Depth
		- 3D 그래픽에서 픽셀의 깊이를 나타내는 값
		- 보통 깊이 버퍼라는 2D 이미지 버퍼에 저장
		- 깊이 버퍼는 각 픽셀에 대해 깊이 값을 설정, 이 값은 렌더링 중에 테스트 및 업데이트
		- 깊이 버퍼를 사용하면 3D 장면에서 물체들이 올바른 순서로 겹쳐지도록 할 수 있음

	Depth Test
		- 렌더링된 픽셀의 깊이 값을 검사하여 렌더링 여부를 결정하는데 사용
		- 깊이 테스트는 사용자가 정의한 깊이 함수를 사용하여 렌더링된 픽셀의 깊이 버퍼의 값을 비교
		- 성공하면 렌더링, 실패하면 걸러짐

	Stencil
		- 깊이 버퍼와 함께 사용되는 2D 이미지 버퍼
		- 각 픽셀에 대해 스텐실 값을 저장하며, 이 값은 렌더링 중에 테스트 및 업데이트
		- 다양한 렌더링 기술에서 사용
		ex) 그림자 볼륨, 클리핑 평면, 포털 렌더링 등

	Stencil Test
		- 렌더링된 픽셀의 스텐실 값을 검사하여 렌더링 여부를 결정하는데 사용
		- 사용자가 정의한 스텐실 함수를 사용하여 렌더링된 픽셀의 스텐실 값과 스텐실 버퍼의 값을 비교
		- 스텐실 테스트에 성공하면 픽셀이 렌더링, 실패하면 걸러짐

	Blending
		- 렌더링된 픽셀의 색상을 결정하는 방법 중 하나
		- 렌더링된 픽셀의 색상과 렌더 타겟의 현재 색상을 결합하는 과정

*/

/*
	Alpha To Converage
		- 멀티 샘플링인 안티에일리어싱(MSAA)을 사용할 때 알파값을 커버리지 마스트로 변환하여 투명도를 구현하는 기술
		- 투명한 객체의 가장자리를 더 부드럽게 처리할 수 있음

	Indpendent Blend
		- 여러 렌더 타겟에 대해 각각 다른 블렌드 상태를 설정할 수 있도록 하는 기능

*/
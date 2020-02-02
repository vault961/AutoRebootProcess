#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <locale.h>

int _tmain()
{
	// 이게 있어야 한글 출력이 된단다
	_wsetlocale(LC_ALL, _T("korean"));
	
	STARTUPINFO si = { 0, };			// 프로세스 시작정보
	PROCESS_INFORMATION pi = { 0, };	// 프로세스 인포메이션
	CONST TCHAR* filePath = _T("C:\\Program Files (x86)\\Melon Player4\\Melon.exe"); // 실행시킬 프로그램 주소
	
	while (TRUE)
	{
		
		// 프로세스 생성
		BOOL IsCreated = CreateProcess(
			filePath,	// 실행파일 이름, 경로명을 추가로 지정해줄 수 있음. 경로명이 없으면 현재 디렉토리에서 찾음
			NULL,		// 새로 생성하는 프로세스에 인자를 전달. 실행파일 이름을 넣을 경우 표준 검색경로로 찾음
			NULL,		// 프로세스 보안속성
			NULL,		// 쓰레드 보안속성
			FALSE,		// 자식프로세서에게 핸들을 상속할건지
			0,			// 프로세스의 특성 설정
			NULL,		// 환경 블록 문자열
			NULL,		// 생성하는 프로세스의 현재 디렉토리
			&si,		// 프로세스 생성 정보
			&pi			// 생성된 프로세스 정보 받기
		);

		// 핸들 닫아주기
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		// 프로세스 생성 성공했을때
		if (IsCreated == TRUE)
		{
			_tprintf(_T("프로세스가 생성되었습니다!\n\n"));
		}
		else 
		{
			// 프로세스 생성 실패시 에러 메시지 출력
			TCHAR* p_error_message = nullptr;
			FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR)&p_error_message, 0, NULL);
			_tprintf(_T("에러 메세지 : %s\n"), p_error_message);
			system("pause");
			break;
		}

		// 프로세스 종료까지 대기
		WaitForSingleObject(pi.hProcess, INFINITE);
		_tprintf(_T("프로세스가 종료되었습니다.\n\n"));
	}

	return 0;
}
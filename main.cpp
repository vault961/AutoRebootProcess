#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <locale.h>

int _tmain()
{
	// �̰� �־�� �ѱ� ����� �ȴܴ�
	_wsetlocale(LC_ALL, _T("korean"));
	
	STARTUPINFO si = { 0, };			// ���μ��� ��������
	PROCESS_INFORMATION pi = { 0, };	// ���μ��� �������̼�
	CONST TCHAR* filePath = _T("C:\\Program Files (x86)\\Melon Player4\\Melon.exe"); // �����ų ���α׷� �ּ�
	
	while (TRUE)
	{
		
		// ���μ��� ����
		BOOL IsCreated = CreateProcess(
			filePath,	// �������� �̸�, ��θ��� �߰��� �������� �� ����. ��θ��� ������ ���� ���丮���� ã��
			NULL,		// ���� �����ϴ� ���μ����� ���ڸ� ����. �������� �̸��� ���� ��� ǥ�� �˻���η� ã��
			NULL,		// ���μ��� ���ȼӼ�
			NULL,		// ������ ���ȼӼ�
			FALSE,		// �ڽ����μ������� �ڵ��� ����Ұ���
			0,			// ���μ����� Ư�� ����
			NULL,		// ȯ�� ��� ���ڿ�
			NULL,		// �����ϴ� ���μ����� ���� ���丮
			&si,		// ���μ��� ���� ����
			&pi			// ������ ���μ��� ���� �ޱ�
		);

		// �ڵ� �ݾ��ֱ�
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		// ���μ��� ���� ����������
		if (IsCreated == TRUE)
		{
			_tprintf(_T("���μ����� �����Ǿ����ϴ�!\n\n"));
		}
		else 
		{
			// ���μ��� ���� ���н� ���� �޽��� ���
			TCHAR* p_error_message = nullptr;
			FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR)&p_error_message, 0, NULL);
			_tprintf(_T("���� �޼��� : %s\n"), p_error_message);
			system("pause");
			break;
		}

		// ���μ��� ������� ���
		WaitForSingleObject(pi.hProcess, INFINITE);
		_tprintf(_T("���μ����� ����Ǿ����ϴ�.\n\n"));
	}

	return 0;
}
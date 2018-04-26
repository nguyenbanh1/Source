#include<conio.h>
#include<stdio.h>
#include <fcntl.h>
#include <io.h> 
#include<stdlib.h>
#include <fstream>
#include<string.h>
#include<Windows.h>
struct HOBBY {
	wchar_t Amthuc[200];
	wchar_t Amnhac[200];
};
struct SINHVIEN {
	wchar_t Ten[30];
	wchar_t Lop[10];
	wchar_t MSSV[10];
	wchar_t Khoa[30];
	wchar_t Khoas[10]; // khóa 
	wchar_t Ngaysinh[20];
	wchar_t Hinh[30];
	wchar_t Decrible[1000];
	wchar_t Email[100];
	HOBBY hobby;

};
// ----- hàm bổ trợ----------
void WCSCOPY(wchar_t*&str, wchar_t * source)
{
	int l = wcslen(source);
	str = (wchar_t*)malloc((l + 1) * sizeof(wchar_t));
	for (int i = 0; i < l; i++)
	{
		*(str + i) = *(source + i);
	}
	*(str + l) = L'\0';
}
int CountTokens(wchar_t*str, wchar_t *sep)
{
	wchar_t *str1;
	WCSCOPY(str1, str);
	int i = 0;
	wchar_t * next_tokens = NULL;
	wchar_t * words = NULL;
	words = wcstok_s(str1, sep, &next_tokens);
	while (words != NULL)
	{
		i++;
		words = wcstok_s(NULL, sep, &next_tokens);
	}
	return i;
}
void arrToken(wchar_t **&Tokens, wchar_t * str, wchar_t *sep, int &n, int lengthTokens)
{
	wchar_t * str1 = NULL;
	WCSCOPY(str1, str);
	n = CountTokens(str, sep);
	Tokens = (wchar_t**)malloc(n * sizeof(wchar_t*));
	for (int i = 0; i < n; i++)
	{
		*(Tokens + i) = (wchar_t*)malloc(lengthTokens * sizeof(wchar_t));
	}
	wchar_t * next_Tokens = NULL;
	*Tokens = wcstok_s(str1, sep, &next_Tokens);
	int i = 0;
	while (*(Tokens + i) != NULL)
	{
		i++;
		*(Tokens + i) = wcstok_s(NULL, sep, &next_Tokens);
	}
}
void WCSCAT(wchar_t * str, wchar_t *&source)
{
	int n1 = wcslen(source);
	int n2 = wcslen(str);
	if (n1 == 0)
	{
		WCSCOPY(source, str);
	}
	else
	{
		source = (wchar_t*)realloc(source, (n1 + n2 + 1) * sizeof(wchar_t));
		for (int i = 0; i <= n2; i++)
		{
			*(source + i + n1) = *(str + i);
		}
	}
}
void arrCatch_Change(wchar_t*&NewSource, wchar_t **Tokens, int n, wchar_t ch, wchar_t *Change)
{
	NewSource = L"";
	if (ch == L'\t')
	{
		for (int i = 0; i < n; i++)
		{
			if (i == 1)
			{
				WCSCAT(&ch, NewSource);
				WCSCAT(Change, NewSource);
				WCSCAT(&ch, NewSource);
				continue;
			}
			WCSCAT(&ch, NewSource);
			WCSCAT(*(Tokens + i), NewSource);
			WCSCAT(&ch, NewSource);
		}
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			if (i == 1)
			{
				//WCSCAT(L"<", NewSource);
				WCSCAT(Change, NewSource);
				//WCSCAT(L">", NewSource);
				continue;
			}
			WCSCAT(L"<", NewSource);
			WCSCAT(*(Tokens + i), NewSource);
			WCSCAT(L">", NewSource);
		}
	}
}
void fwgetline(FILE*&file, wchar_t*str, int length, wchar_t sep = L'\r')
{
	if (feof(file)) return;
	//fseek(file, 2, SEEK_SET);
	wchar_t ch;
	int len = 0;
	while (true)
	{
		ch = fgetwc(file);
		if (len >= length - 1 || ch == L'\r')
		{
			*(str + len) = L'\0';
			ch = fgetwc(file);
			break;
		}
		else if (ch == sep)
		{
			*(str + len) = L'\0';
			break;
		}
		else
		{
			*(str + len) = ch;
			len++;
		}
	}
}
//----------------------------------------------------------------------------------------
//Số lượng sinh viên có trong file.csv
int STUDENTS(FILE*file) // trả về số lượng sinh viên trong file.csv
{
	wchar_t *ten = (wchar_t*)malloc(1000 * sizeof(wchar_t));
	fwgetline(file, ten, 100);
	int i = 0;
	while (true)
	{
		if (feof(file)) break;
		fwgetline(file, ten, 1000);
		i++;
	}
	fseek(file, 0L, SEEK_SET);
	return i;
}
//Chép toàn bộ sinh viên trong file.csv vào mảng SV
void doc_file(FILE *&file, SINHVIEN *&sv, int &n, int students) // n là số lượng sinh viên cần nhập vào file
{
	wprintf_s(L"Số lương sinh viên trong file.csv : %d", students - 1);
	wprintf_s(L"\nNhập số lượng sinh viên cần khảo sát: ");
	do {
		wscanf_s(L"%d", &n);
		if (n >= students) wprintf_s(L"%s", L"Số lượng sinh viên đã lớn.Xin ktra lại!\nNhập số lượng sinh viên cần khảo sát:");
	} while (n >= students);
	wchar_t *a = (wchar_t*)malloc(100 * sizeof(wchar_t));  
	fwgetline(file, a, 100); // Dùng để đọc dòng đầu tiên
	sv = (SINHVIEN*)malloc(n * sizeof(SINHVIEN));
	for (int i = 0; i < n; i++) // Đọc dữ liệu n sinh viên (mỗi dòng là 1 sinh viên tương ứng)
	{
		fwgetline(file, (sv + i)->Ten, 30, L'\t');
		fwgetline(file, (sv + i)->Lop, 10, L'\t');
		fwgetline(file, (sv + i)->MSSV, 10, L'\t');
		fwgetline(file, (sv + i)->Khoa, 30, L'\t');
		fwgetline(file, (sv + i)->Khoas, 10, L'\t');
		fwgetline(file, (sv + i)->Email, 100, L'\t');
		fwgetline(file, (sv + i)->Ngaysinh, 20, L'\t');
		fwgetline(file, (sv + i)->Hinh, 30, L'\t');
		fwgetline(file, (sv + i)->Decrible, 200, L'\t');
		fseek(file, 2, SEEK_CUR);
		fwgetline(file, (sv + i)->hobby.Amnhac, 200, L'\"');
		fseek(file, 4, SEEK_CUR);
		fwgetline(file, (sv + i)->hobby.Amthuc, 200, L'\"');
		fseek(file, 4, SEEK_CUR);
	}

}
//In tất cả thông tin sinh viên ra màn hình consolve 
void Student(SINHVIEN *sv, int n)
{
	for (int i = 0; i < n; i++)
	{
		wprintf_s(L"\n----------------SINH VIÊN %d----------------------------", i + 1);
		wprintf_s(L"\nHọ và tên: %ls", (sv + i)->Ten);
		wprintf_s(L"\nLớp : %ls", (sv + i)->Lop);
		wprintf_s(L"\nMSSV : %ls", (sv + i)->MSSV);
		wprintf_s(L"\nKhoa : %ls", (sv + i)->Khoa);
		wprintf_s(L"\nKhóa : %ls", (sv + i)->Khoas);
		wprintf_s(L"\nKhóa : %ls", (sv + i)->Email);
		wprintf_s(L"\nNgày sinh : %ls", (sv + i)->Ngaysinh);
		wprintf_s(L"\nHình : %ls", (sv + i)->Hinh);
		wprintf_s(L"\nDecrible : %ls", (sv + i)->Decrible);
		wprintf_s(L"\nÂm nhạc : %ls", (sv + i)->hobby.Amnhac);
		wprintf_s(L"\nẨm thực : %ls", (sv + i)->hobby.Amthuc);
	}
}
// In menu danh sách
void MenuSelectPut_Ifile(int a[])
{
	wprintf_s(L"\n--------MENU---------");
	wprintf_s(L"\n1.Họ và tên.");
	wprintf_s(L"\n2.Mã số sinh viên.");
	wprintf_s(L"\n3.Lớp.");
	wprintf_s(L"\n4.Khoa.");
	wprintf_s(L"\n5.Khóa.");
	wprintf_s(L"\n6.Email.");
	wprintf_s(L"\n7.Ngày sinh.");
	wprintf_s(L"\n8.Hình.");
	wprintf_s(L"\n9.Mô tả.");
	wprintf_s(L"\n10.Âm Nhạc.");
	wprintf_s(L"\n11.Ẩm thực.");
	wprintf_s(L"\n12.Tất cả các trường hợp trên.");
	wprintf_s(L"\n13.Bấm phím '0' để phát sinh file.");
	wprintf_s(L"\n\nLựa chọn các thành phần cần phát sinh(bấm 1,3,4,.. ) : ");
	int b;
	do {
		wscanf_s(L"%d",&b);
		if (b == 0) break;
		if (1 <= b && b <= 11)
		{
			a[b] = 1;
		}
		else if (b == 12)
		{
			for (int i = 0; i < 13; i++)
				a[i] = 1;
			break;
		}
	} while (true);
}
//Chép dữ liệu từ HTML.txt sang file sinh viên cần tạo (chỉ một sinh viên)
void Make_OneFileStudents(SINHVIEN sv,int a[]) // đặt tên file là MSSV
{
	wchar_t *mssv = NULL;
	WCSCOPY(mssv, L"Websites/");
	WCSCAT(sv.MSSV, mssv);
	WCSCAT(L".html", mssv);
	FILE *html;
	FILE *STUDENT;
	int flag;
	_wfopen_s(&html, L"HTML.txt", L"rb");
	_wfopen_s(&STUDENT, mssv, L"wb");
	wchar_t * ch = (wchar_t*)malloc(200 * sizeof(wchar_t)); // dùng để chép 1 dòng không cần dùng để xử lý
	wchar_t * str = (wchar_t*)malloc(200 * sizeof(wchar_t));//Chép dòng để xử lý
	wchar_t ** arrTokens = NULL; // dùng để tạo mảng gồm nhiều tokens
	int n;// số lượng stokens trong arrTokens
	wchar_t *INPUT = NULL;//ghép tất cả các Tokens lại

	wchar_t ch1 = fgetwc(html);//dùng để di chuyển và lấy từng ký tự thứ 3 mỗi hàng trong file HTML.txt;
	while (!feof(html))
	{
		flag = 0;
		fseek(html, 4, SEEK_CUR); // di chuyển con trỏ file đến qua 4byte
		wchar_t ch1 = fgetwc(html);//nhận 1 ký tự tại con trỏ file pos = 4
		if (ch1 == L'1' || ch1 == L'2' || ch1 == L'3' || ch1 == L'4' || ch1 == L'5' || ch1 == L'6' || ch1 == L'7' || ch1 == L'8' || ch1 == L'9' || ch1 == L'A' || ch1 == L'B' || ch1 == L'C' || ch1 == L'F' || ch1 == L'E')
		{
			fseek(html, 2, SEEK_CUR);
			fwgetline(html, str, 200);
			wchar_t * source = L"";//dùng để sử lý chuỗi
			fputws(L"\r\n", STUDENT);
			if (ch1 == L'1')
			{

				arrToken(arrTokens, str, L"L'<',L'>'", n, 30);
				WCSCAT(L"HCMUS", source);
				WCSCAT(L" - ", source);
				if(a[1] == 1) WCSCAT(sv.Ten, source);
				arrCatch_Change(INPUT, arrTokens, n, L' ', source);
			}
			else if (ch1 == L'2' && (a[1] == 1 || a[2] == 1))
			{
				
				arrToken(arrTokens, str, L"L'<',L'>'", n, 30);
				if (a[1] == 1)
				{
					WCSCAT(sv.Ten, source);
					
				}
				if (a[2] == 1)
				{
					WCSCAT(L" - ", source);
					WCSCAT(sv.MSSV, source);
				}
				arrCatch_Change(INPUT, arrTokens, n, L' ', source);

			}
			else if (ch1 == L'3' && a[4] == 1)
			{
			
				WCSCAT(sv.Khoa, source);
				arrToken(arrTokens, str, L"L'<',L'>'", n, 30);
				arrCatch_Change(INPUT, arrTokens, n, L' ', source);
			}
			else if (ch1 == L'4' && a[6] == 1)
			{
			
				arrToken(arrTokens, str, L"L'<',L'>'", n, 30);
				WCSCAT(L"Email: ", source);
				WCSCAT(sv.Email, source);
				arrCatch_Change(INPUT, arrTokens, n, L' ', source);
			}
			else if (ch1 == L'5' && a[8] == 1)
			{
				
				arrToken(arrTokens, str, L"\t", n, 30);
				WCSCAT(sv.Hinh, source);
				arrCatch_Change(INPUT, arrTokens, n, L'\t', source);
			}
			else if (ch1 == L'6' && a[1] == 1)
			{
		
				arrToken(arrTokens, str, L"L'<',L'>'", n, 30);
				WCSCAT(L"Họ và tên: ", source);
				WCSCAT(sv.Ten, source);
				arrCatch_Change(INPUT, arrTokens, n, L' ', source);
			}
			else if (ch1 == L'7' && a[2] == 1)
			{
				
				arrToken(arrTokens, str, L"L'<',L'>'", n, 30);
				WCSCAT(L"MSSV: ", source);
				WCSCAT(sv.MSSV, source);
				arrCatch_Change(INPUT, arrTokens, n, L' ', source);
			}
			else if (ch1 == L'8' && a[4] == 1)
			{
				
				arrToken(arrTokens, str, L"L'<',L'>'", n, 30);
				WCSCAT(L"Sinh viên", source);
				WCSCAT(sv.Khoa, source);
				arrCatch_Change(INPUT, arrTokens, n, L' ', source);
			}
			else if (ch1 == L'9' && a[7] == 1)
			{
				
				arrToken(arrTokens, str, L"L'<',L'>'", n, 30);
				WCSCAT(L"Ngày sinh:  ", source);
				WCSCAT(sv.Ngaysinh, source);
				arrCatch_Change(INPUT, arrTokens, n, L' ', source);
			}
			else if ( ch1 == L'A' &&  a[6] == 1)
			{
				
				arrToken(arrTokens, str, L"L'<',L'>'", n, 30);
				WCSCAT(L"Email:  ", source);
				WCSCAT(sv.Email, source);
				arrCatch_Change(INPUT, arrTokens, n, L' ', source);
			}
			else if (ch1 == L'B' && a[10] == 1)
			{
				
				arrToken(arrTokens, str, L"L'<'L'>'", n, 100);
				WCSCAT(L"Âm nhạc: ", source);
				WCSCAT(sv.hobby.Amnhac, source);
				arrCatch_Change(INPUT, arrTokens, n, L' ', source);
			}
			else if (ch1 == L'C' && a[11] == 1)
			{
				
				arrToken(arrTokens, str, L"L'<'L'>'", n, 100);
				WCSCAT(L"Ẩm thực:  ", source);
				WCSCAT(sv.hobby.Amthuc, source);
				arrCatch_Change(INPUT, arrTokens, n, L' ', source);
			}
			else if (ch1 == L'E' && a[9] == 1)
			{
			
				arrToken(arrTokens, str, L"L'<'L'>'", n, 1000);
				WCSCAT(sv.Decrible, source);
				arrCatch_Change(INPUT, arrTokens, n, L' ', source);
			}
			else if (ch1 == L'F')
			{
			
				arrToken(arrTokens, str, L"L'<'L'>'", n, 30);
				WCSCAT(L"1660384", source);
				WCSCAT(L" - ", source);
				WCSCAT(L"Tăng Khánh Nguyên", source);
				arrCatch_Change(INPUT, arrTokens, n, L' ', source);
			}
			else
			{
				fputws(L"\r\n", STUDENT);
				fputws(str, STUDENT);
				flag = 1;
			}
			if(flag != 1) fputws(INPUT, STUDENT);

		}
		else
		{
			fseek(html, -6, SEEK_CUR);
			fwgetline(html, ch, 200);
			fputws(L"\r\n", STUDENT);
			fputws(ch, STUDENT);
		}
	}
	fclose(STUDENT);
	fclose(html);
}

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT); //needed for output
	_setmode(_fileno(stdin), _O_U16TEXT); //needed for input
	FILE*file; // trỏ tới file thongtin.csv
	SINHVIEN *sv;
	int n;//số lượng sinh viên cần 
	int a[13] = {0};//số lương các tùy chọn để phát sinh cho profile page
	//----------Chép dữ liệu file.csv
	_wfopen_s(&file, L"thongtin.csv", L"rb");
	if (feof(file)) wprintf_s(L"File không tồn tại: ");
	int i = STUDENTS(file);
	doc_file(file, sv, n, i);
	fclose(file);
	MenuSelectPut_Ifile(a);
	//------------ chép dữ liệu trong html và đồng thời chỉnh sữa thành một sinh viên tương ứng---------
	for (int i = 0; i < n; i++)
	{
		Make_OneFileStudents(*(sv + i),a);
	}
	wprintf_s(L"\nChương trình đã phát sinh %d profile page .", n);
	wprintf_s(L"\nMời thầy vào thư mục 1660384 -> Websites để xem thông tin sinh viên. CẢM ƠN THẦY!");
	
	_getch();
	return 0;
}
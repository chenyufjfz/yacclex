/*
 * SimplifyTool.cpp
 *
 *  Created on: Oct 24, 2012
 *      Author: yuchen
 */

#include "SimplifyTool.h"
#include "windows.h"

string espresso_path = "C:\\ChenYu\\work\\yacclex\\test\\espresso.exe";
class WinAPI {
public:
	static int WinExecEx(const char * command, const char * arg0, const char * file1, const char * arg1, const char * file2,
			const char * arg2, const char *redirect, int mShowWindow)
	{
		STARTUPINFO   si;
		PROCESS_INFORMATION   pi;
		string cmd;
		memset(&si, 0, sizeof(si));
		si.cb =sizeof(si);
		si.wShowWindow =mShowWindow;
		si.dwFlags =STARTF_USESHOWWINDOW;
		memset(&pi, 0, sizeof(pi));
		cmd.assign("\"");
		cmd.append(command);
		cmd.append("\"");
		if (arg0!=NULL) {
			cmd.append(" ");
			cmd.append(arg0);
		}
		if (file1!=NULL) {
			cmd.append(" \"");
			cmd.append(file1);
			cmd+='"';
		}
		if (arg1!=NULL) {
			cmd.append(" ");
			cmd.append(arg1);
		}
		if (file2!=NULL) {
			cmd.append(" \"");
			cmd.append(file2);
			cmd+='"';
		}
		if (arg2!=NULL) {
			cmd.append(" ");
			cmd.append(arg2);
		}

		if (redirect!=NULL) {
			SECURITY_ATTRIBUTES sa={sizeof(sa),NULL,TRUE};
			sa.bInheritHandle =TRUE;
			HANDLE hConsoleRedirect=CreateFile(redirect,
                GENERIC_WRITE,
                FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,
                &sa,
                CREATE_ALWAYS,
                FILE_ATTRIBUTE_NORMAL,
                NULL );
			if (hConsoleRedirect==INVALID_HANDLE_VALUE)
				return 2;
			si.hStdOutput =hConsoleRedirect;
			si.hStdError =hConsoleRedirect;
			si.dwFlags |=STARTF_USESTDHANDLES;
		}
		cout<<cmd<<"\n";
		if (!CreateProcess(NULL, (char*)cmd.c_str(), NULL, NULL, true, 0, NULL, NULL, &si, &pi)) {
			return GetLastError();
		}

		if (WaitForSingleObject( pi.hProcess, 180*1000 )==WAIT_TIMEOUT) {
			printf("optimize timeout");
			TerminateProcess(pi.hProcess, 1);
			return 1;
		}

		// Close process and thread handles.
		CloseHandle( pi.hProcess );
		CloseHandle( pi.hThread );

		if (redirect!=NULL)
			CloseHandle(si.hStdOutput);
		return 0;
	}

	static string get_exe_path()
	{
		char   ExeFile[300];
		ASSERT(0!=GetModuleFileName(NULL, ExeFile, sizeof(ExeFile)));
		string cmp_filename(ExeFile);
		int index =cmp_filename.find_last_of('\\');
		return cmp_filename.substr(0, index+1);
	}
};


SimplifyTool::SimplifyTool() {
	org_vec_file = NULL;
	opt_vec_file = NULL;
	simple_loop =0;
}

SimplifyTool::~SimplifyTool() {
	if (org_vec_file!=NULL)
		fclose(org_vec_file);
	if (opt_vec_file!=NULL)
		fclose(opt_vec_file);
}

void SimplifyTool::open(int var_in_num, int var_out_num)
{
	char filename[30];
	sprintf(filename, "org_logic_%d.txt", simple_loop);
	org_vec_file = fopen( (WinAPI::get_exe_path()+filename).c_str(), "w");
	if (org_vec_file==NULL) {
		printf("can't open original vector file for write");
		exit(1);
	}
	fprintf(org_vec_file, ".i %d\n", var_in_num);
	fprintf(org_vec_file, ".o %d\n", var_out_num);
	fprintf(org_vec_file, ".type f\n");
	in_num = var_in_num;
	out_num = var_out_num;
}

void SimplifyTool::write(const vector <int> & vec_in, const vector <int> & vec_out)
{
	unsigned i;
	for (i=0; i<vec_in.size(); i++)
		if (vec_in[i]<2)
			fprintf(org_vec_file, "%d", vec_in[i]);
		else
			fprintf(org_vec_file, "-");
	fprintf(org_vec_file, "   ");
	for (i=0; i<vec_out.size(); i++)
		if (vec_out[i]<2)
			fprintf(org_vec_file, "%d", vec_out[i]);
		else
			fprintf(org_vec_file, "-");
	fprintf(org_vec_file, "\n");
}

void SimplifyTool::insert_comment(string comment)
{
	fprintf(org_vec_file, "#");
	fprintf(org_vec_file, comment.c_str());
	fprintf(org_vec_file, "\n");
}

bool SimplifyTool::read(vector <int> & vec_in, vector <int> & vec_out)
{
	char line[200];
	bool done=false;
	unsigned i,j;
	int  line_num[200];
	ASSERT(opt_vec_file!=NULL);

	while (!done) {
		done =true;
		if (fgets(line, sizeof(line), opt_vec_file)==NULL) {
			done=false;
			break;
		}
		for (i=0,j=0; line[i]!=0; i++) {
			if (line[i]=='.' || line[i]=='#') {
				done=false;
				break;
			}
			switch (line[i]){
			case ' ':
			case '\n':
				break;
			case '0':
			case '1':
				line_num[j++] = line[i]-'0';
				break;
			case '-':
				line_num[j++] = 2;
				break;
			default:
				ASSERT(0);
				break;
			}
		}
	}

	if (done) {
		ASSERT(j==in_num+out_num);
		vec_in.resize(in_num);
		vec_out.resize(out_num);
		for (i=0; i<in_num; i++)
			vec_in[i] = line_num[i];
		for (i=0; i<out_num; i++)
			vec_out[i] = line_num[i+in_num];
	}
	return done;
}

void SimplifyTool::simply()
{
	fclose(org_vec_file);
	char org_file[30], opt_file[30];
	sprintf(org_file, "org_logic_%d.txt", simple_loop);
	sprintf(opt_file, "opt_logic_%d.txt", simple_loop++);
	WinAPI::WinExecEx(espresso_path.c_str(), "-Dsingle_output", (WinAPI::get_exe_path()+org_file).c_str(), NULL, NULL, NULL,
			(WinAPI::get_exe_path()+opt_file).c_str(), SW_MINIMIZE);
	opt_vec_file = fopen((WinAPI::get_exe_path()+opt_file).c_str(), "r");
	if (opt_vec_file==NULL) {
		printf("can't open optimize vector file for read");
		exit(1);
	}
}

void SimplifyTool::close()
{
	fclose(opt_vec_file);
}

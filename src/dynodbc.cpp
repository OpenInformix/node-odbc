#ifdef dynodbc

#include "dynodbc.h"

#ifdef _WIN32
  #include <windows.h>
#elif defined(__GNUC__) // GNU compiler
  #include <dlfcn.h>
#else
#error define your copiler
#endif

#include<string>
/*
#define RTLD_LAZY   1
#define RTLD_NOW    2
#define RTLD_GLOBAL 4
*/

void* LoadSharedLibrary(char *pcDllname, int iMode = 2)
{
  std::string sDllName = pcDllname;
#ifdef _WIN32
  sDllName += ".dll";
  return (void*)LoadLibraryA(pcDllname);
#elif defined(__GNUC__) // GNU compiler
  sDllName += ".so";
  return dlopen(sDllName.c_str(),iMode);
#endif
}

void* GetFunction(void *Lib, char *Fnname)
{
#if defined(_MSC_VER) // Microsoft compiler
  return (void*)GetProcAddress((HINSTANCE)Lib,Fnname);
#elif defined(__GNUC__) // GNU compiler
  return dlsym(Lib,Fnname);
#endif
}

bool FreeSharedLibrary(void *hDLL)
{
#if defined(_MSC_VER) // Microsoft compiler
  return (FreeLibrary((HINSTANCE)hDLL)!=0);
#elif defined(__GNUC__) // GNU compiler
  return dlclose(hDLL);
#endif
}

pfnSQLGetData           pSQLGetData;
pfnSQLGetFunctions      pSQLGetFunctions;
pfnSQLAllocConnect      pSQLAllocConnect;
pfnSQLAllocEnv          pSQLAllocEnv;
pfnSQLAllocStmt         pSQLAllocStmt;
pfnSQLBindCol           pSQLBindCol;
pfnSQLCancel            pSQLCancel;
pfnSQLColAttributes     pSQLColAttributes;
pfnSQLConnect           pSQLConnect;
pfnSQLDescribeCol       pSQLDescribeCol;
pfnSQLDisconnect        pSQLDisconnect;
pfnSQLError             pSQLError;
pfnSQLExecDirect        pSQLExecDirect;
pfnSQLExecute           pSQLExecute;
pfnSQLFetch             pSQLFetch;
pfnSQLGetDiagRec        pSQLGetDiagRec;
pfnSQLFreeHandle        pSQLFreeHandle;
pfnSQLFetchScroll       pSQLFetchScroll;
pfnSQLColAttribute      pSQLColAttribute;
pfnSQLSetConnectAttr    pSQLSetConnectAttr;
pfnSQLDriverConnect     pSQLDriverConnect;
pfnSQLAllocHandle       pSQLAllocHandle;
pfnSQLRowCount          pSQLRowCount;
pfnSQLNumResultCols     pSQLNumResultCols;
pfnSQLEndTran           pSQLEndTran;
pfnSQLTables            pSQLTables;
pfnSQLColumns           pSQLColumns;
pfnSQLBindParameter     pSQLBindParameter;
pfnSQLPrimaryKeys       pSQLPrimaryKeys;
pfnSQLSetEnvAttr        pSQLSetEnvAttr  ;
pfnSQLFreeConnect       pSQLFreeConnect;
pfnSQLFreeEnv           pSQLFreeEnv;
pfnSQLFreeStmt          pSQLFreeStmt;                      
pfnSQLGetCursorName     pSQLGetCursorName;
pfnSQLPrepare           pSQLPrepare;
pfnSQLSetCursorName     pSQLSetCursorName;
pfnSQLTransact          pSQLTransact;
pfnSQLSetConnectOption  pSQLSetConnectOption;
pfnSQLDrivers           pSQLDrivers;
pfnSQLDataSources       pSQLDataSources;
pfnSQLGetInfo           pSQLGetInfo;
pfnSQLMoreResults       pSQLMoreResults;

//#define LOAD_ENTRY( hMod, Name ) (p##Name = (pfn##Name) GetProcAddress( (hMod), #Name ))
#define LOAD_ENTRY( hMod, Name ) (p##Name = (pfn##Name) GetFunction( (hMod), #Name ))

static BOOL  s_fODBCLoaded = false;

BOOL DynLoadODBC( char* odbcModuleName )
{
#ifdef _WIN32
    HMODULE hMod;
#elif defined(__GNUC__) // GNU compiler
    void* hMod;
#endif

    if ( s_fODBCLoaded )
      return true;

 //   if ( (hMod = (HMODULE) LoadLibrary( odbcModuleName ))) {
#ifdef _WIN32
  if ( (hMod = (HMODULE) LoadSharedLibrary( odbcModuleName ))) {
#elif defined(__GNUC__) // GNU compiler
  if ( (hMod = (void *) LoadSharedLibrary( odbcModuleName ))) {
#endif

//#if (ODBCVER < 0x0300)
  if (LOAD_ENTRY( hMod, SQLGetData   )  )
  if (LOAD_ENTRY( hMod, SQLGetFunctions   )  )
  if (LOAD_ENTRY( hMod, SQLAllocConnect   )  )
  if (LOAD_ENTRY( hMod, SQLAllocEnv       )  )
  if (LOAD_ENTRY( hMod, SQLAllocStmt      )  )
  if (LOAD_ENTRY( hMod, SQLColAttributes  )  )
  if (LOAD_ENTRY( hMod, SQLError          )  )
  if (LOAD_ENTRY( hMod, SQLFreeConnect    )  )
  if (LOAD_ENTRY( hMod, SQLFreeEnv        )  )
  if (LOAD_ENTRY( hMod, SQLTransact       )  )
  if (LOAD_ENTRY( hMod, SQLSetConnectOption )  )
  if (LOAD_ENTRY( hMod, SQLDrivers        )  )
  if (LOAD_ENTRY( hMod, SQLDataSources    )  )
//#endif
  if (LOAD_ENTRY( hMod, SQLBindCol        )  )
  if (LOAD_ENTRY( hMod, SQLCancel         )  )
  if (LOAD_ENTRY( hMod, SQLConnect       )  )
  if (LOAD_ENTRY( hMod, SQLDescribeCol    )  )
  if (LOAD_ENTRY( hMod, SQLDisconnect     )  )
  if (LOAD_ENTRY( hMod, SQLExecDirect     )  )
  if (LOAD_ENTRY( hMod, SQLExecute        )  )
  if (LOAD_ENTRY( hMod, SQLFetch          )  )
  if (LOAD_ENTRY( hMod, SQLGetDiagRec     )  )
  if (LOAD_ENTRY( hMod, SQLFreeHandle     )  )
  if (LOAD_ENTRY( hMod, SQLFetchScroll    )  )
  if (LOAD_ENTRY( hMod, SQLColAttribute   )  )
  if (LOAD_ENTRY( hMod, SQLSetConnectAttr )  )
  if (LOAD_ENTRY( hMod, SQLDriverConnect   )  )
  if (LOAD_ENTRY( hMod, SQLAllocHandle   )  )
  if (LOAD_ENTRY( hMod, SQLRowCount     )  )
  if (LOAD_ENTRY( hMod, SQLNumResultCols   )  )
  if (LOAD_ENTRY( hMod, SQLEndTran     )  )
  if (LOAD_ENTRY( hMod, SQLTables)  )
  if (LOAD_ENTRY( hMod, SQLColumns)  )
  if (LOAD_ENTRY( hMod, SQLBindParameter)  )
  if (LOAD_ENTRY( hMod, SQLPrimaryKeys)  )
  if (LOAD_ENTRY( hMod, SQLSetEnvAttr)  )
  if (LOAD_ENTRY( hMod, SQLFreeStmt       )  )
  if (LOAD_ENTRY( hMod, SQLNumResultCols  )  )
  if (LOAD_ENTRY( hMod, SQLPrepare        )  )
  if (LOAD_ENTRY( hMod, SQLRowCount       )  )
  if (LOAD_ENTRY( hMod, SQLGetInfo        )  )
  if (LOAD_ENTRY( hMod, SQLBindParameter  )  )
  if (LOAD_ENTRY( hMod, SQLMoreResults    )
          ) {

          s_fODBCLoaded = true;
      }
  }

  return (s_fODBCLoaded);
}
#endif
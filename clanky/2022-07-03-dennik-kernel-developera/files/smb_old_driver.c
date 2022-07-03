typedef unsigned char   undefined;

typedef unsigned long long    GUID;
typedef unsigned int    ImageBaseOffset32;
typedef unsigned char    bool;
typedef unsigned char    byte;
typedef unsigned int    dword;
typedef long long    longlong;
typedef unsigned long long    qword;
typedef unsigned int    uint;
typedef unsigned long long    ulonglong;
typedef unsigned char    undefined1;
typedef unsigned short    undefined2;
typedef unsigned int    undefined4;
typedef unsigned long long    undefined8;
typedef unsigned short    word;
typedef unsigned short    wchar16;
typedef union IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryUnion IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryUnion, *PIMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryUnion;

typedef struct IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryStruct IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryStruct, *PIMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryStruct;

struct IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryStruct {
    dword OffsetToDirectory;
    dword DataIsDirectory;
};

union IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryUnion {
    dword OffsetToData;
    struct IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryStruct IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryStruct;
};

typedef struct _IMAGE_RUNTIME_FUNCTION_ENTRY _IMAGE_RUNTIME_FUNCTION_ENTRY, *P_IMAGE_RUNTIME_FUNCTION_ENTRY;

struct _IMAGE_RUNTIME_FUNCTION_ENTRY {
    ImageBaseOffset32 BeginAddress;
    ImageBaseOffset32 EndAddress;
    ImageBaseOffset32 UnwindInfoAddressOrData;
};

typedef struct Var Var, *PVar;

struct Var {
    word wLength;
    word wValueLength;
    word wType;
};

typedef struct IMAGE_RESOURCE_DIRECTORY_ENTRY_NameStruct IMAGE_RESOURCE_DIRECTORY_ENTRY_NameStruct, *PIMAGE_RESOURCE_DIRECTORY_ENTRY_NameStruct;

struct IMAGE_RESOURCE_DIRECTORY_ENTRY_NameStruct {
    dword NameOffset;
    dword NameIsString;
};

typedef struct IMAGE_DEBUG_DIRECTORY IMAGE_DEBUG_DIRECTORY, *PIMAGE_DEBUG_DIRECTORY;

struct IMAGE_DEBUG_DIRECTORY {
    dword Characteristics;
    dword TimeDateStamp;
    word MajorVersion;
    word MinorVersion;
    dword Type;
    dword SizeOfData;
    dword AddressOfRawData;
    dword PointerToRawData;
};

typedef struct IMAGE_FILE_HEADER IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;

struct IMAGE_FILE_HEADER {
    word Machine; // 34404
    word NumberOfSections;
    dword TimeDateStamp;
    dword PointerToSymbolTable;
    dword NumberOfSymbols;
    word SizeOfOptionalHeader;
    word Characteristics;
};

typedef struct IMAGE_LOAD_CONFIG_DIRECTORY64 IMAGE_LOAD_CONFIG_DIRECTORY64, *PIMAGE_LOAD_CONFIG_DIRECTORY64;

typedef enum IMAGE_GUARD_FLAGS {
    IMAGE_GUARD_CF_INSTRUMENTED=256,
    IMAGE_GUARD_CFW_INSTRUMENTED=512,
    IMAGE_GUARD_CF_FUNCTION_TABLE_PRESENT=1024,
    IMAGE_GUARD_SECURITY_COOKIE_UNUSED=2048,
    IMAGE_GUARD_PROTECT_DELAYLOAD_IAT=4096,
    IMAGE_GUARD_DELAYLOAD_IAT_IN_ITS_OWN_SECTION=8192,
    IMAGE_GUARD_CF_EXPORT_SUPPRESSION_INFO_PRESENT=16384,
    IMAGE_GUARD_CF_ENABLE_EXPORT_SUPPRESSION=32768,
    IMAGE_GUARD_CF_LONGJUMP_TABLE_PRESENT=65536,
    IMAGE_GUARD_RF_INSTRUMENTED=131072,
    IMAGE_GUARD_RF_ENABLE=262144,
    IMAGE_GUARD_RF_STRICT=524288,
    IMAGE_GUARD_CF_FUNCTION_TABLE_SIZE_MASK_1=268435456,
    IMAGE_GUARD_CF_FUNCTION_TABLE_SIZE_MASK_2=536870912,
    IMAGE_GUARD_CF_FUNCTION_TABLE_SIZE_MASK_4=1073741824,
    IMAGE_GUARD_CF_FUNCTION_TABLE_SIZE_MASK_8=2147483648
} IMAGE_GUARD_FLAGS;

struct IMAGE_LOAD_CONFIG_DIRECTORY64 {
    dword Size;
    dword TimeDateStamp;
    word MajorVersion;
    word MinorVersion;
    dword GlobalFlagsClear;
    dword GlobalFlagsSet;
    dword CriticalSectionDefaultTimeout;
    qword DeCommitFreeBlockThreshold;
    qword DeCommitTotalFreeThreshold;
    pointer64 LockPrefixTable;
    qword MaximumAllocationSize;
    qword VirtualMemoryThreshold;
    qword ProcessAffinityMask;
    dword ProcessHeapFlags;
    word CsdVersion;
    word DependentLoadFlags;
    pointer64 EditList;
    pointer64 SecurityCookie;
    pointer64 SEHandlerTable;
    qword SEHandlerCount;
    pointer64 GuardCFCCheckFunctionPointer;
    pointer64 GuardCFDispatchFunctionPointer;
    pointer64 GuardCFFunctionTable;
    qword GuardCFFunctionCount;
    enum IMAGE_GUARD_FLAGS GuardFlags;
};

typedef struct StringFileInfo StringFileInfo, *PStringFileInfo;

struct StringFileInfo {
    word wLength;
    word wValueLength;
    word wType;
};

typedef union IMAGE_RESOURCE_DIRECTORY_ENTRY IMAGE_RESOURCE_DIRECTORY_ENTRY, *PIMAGE_RESOURCE_DIRECTORY_ENTRY;

typedef union IMAGE_RESOURCE_DIRECTORY_ENTRY_NameUnion IMAGE_RESOURCE_DIRECTORY_ENTRY_NameUnion, *PIMAGE_RESOURCE_DIRECTORY_ENTRY_NameUnion;

union IMAGE_RESOURCE_DIRECTORY_ENTRY_NameUnion {
    struct IMAGE_RESOURCE_DIRECTORY_ENTRY_NameStruct IMAGE_RESOURCE_DIRECTORY_ENTRY_NameStruct;
    dword Name;
    word Id;
};

union IMAGE_RESOURCE_DIRECTORY_ENTRY {
    union IMAGE_RESOURCE_DIRECTORY_ENTRY_NameUnion NameUnion;
    union IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryUnion DirectoryUnion;
};

typedef struct IMAGE_OPTIONAL_HEADER64 IMAGE_OPTIONAL_HEADER64, *PIMAGE_OPTIONAL_HEADER64;

typedef struct IMAGE_DATA_DIRECTORY IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;

struct IMAGE_DATA_DIRECTORY {
    ImageBaseOffset32 VirtualAddress;
    dword Size;
};

struct IMAGE_OPTIONAL_HEADER64 {
    word Magic;
    byte MajorLinkerVersion;
    byte MinorLinkerVersion;
    dword SizeOfCode;
    dword SizeOfInitializedData;
    dword SizeOfUninitializedData;
    ImageBaseOffset32 AddressOfEntryPoint;
    ImageBaseOffset32 BaseOfCode;
    pointer64 ImageBase;
    dword SectionAlignment;
    dword FileAlignment;
    word MajorOperatingSystemVersion;
    word MinorOperatingSystemVersion;
    word MajorImageVersion;
    word MinorImageVersion;
    word MajorSubsystemVersion;
    word MinorSubsystemVersion;
    dword Win32VersionValue;
    dword SizeOfImage;
    dword SizeOfHeaders;
    dword CheckSum;
    word Subsystem;
    word DllCharacteristics;
    qword SizeOfStackReserve;
    qword SizeOfStackCommit;
    qword SizeOfHeapReserve;
    qword SizeOfHeapCommit;
    dword LoaderFlags;
    dword NumberOfRvaAndSizes;
    struct IMAGE_DATA_DIRECTORY DataDirectory[16];
};

typedef struct StringTable StringTable, *PStringTable;

struct StringTable {
    word wLength;
    word wValueLength;
    word wType;
};

typedef struct IMAGE_SECTION_HEADER IMAGE_SECTION_HEADER, *PIMAGE_SECTION_HEADER;

typedef union Misc Misc, *PMisc;

typedef enum SectionFlags {
    IMAGE_SCN_TYPE_NO_PAD=8,
    IMAGE_SCN_RESERVED_0001=16,
    IMAGE_SCN_CNT_CODE=32,
    IMAGE_SCN_CNT_INITIALIZED_DATA=64,
    IMAGE_SCN_CNT_UNINITIALIZED_DATA=128,
    IMAGE_SCN_LNK_OTHER=256,
    IMAGE_SCN_LNK_INFO=512,
    IMAGE_SCN_RESERVED_0040=1024,
    IMAGE_SCN_LNK_REMOVE=2048,
    IMAGE_SCN_LNK_COMDAT=4096,
    IMAGE_SCN_GPREL=32768,
    IMAGE_SCN_MEM_16BIT=131072,
    IMAGE_SCN_MEM_PURGEABLE=131072,
    IMAGE_SCN_MEM_LOCKED=262144,
    IMAGE_SCN_MEM_PRELOAD=524288,
    IMAGE_SCN_ALIGN_1BYTES=1048576,
    IMAGE_SCN_ALIGN_2BYTES=2097152,
    IMAGE_SCN_ALIGN_4BYTES=3145728,
    IMAGE_SCN_ALIGN_8BYTES=4194304,
    IMAGE_SCN_ALIGN_16BYTES=5242880,
    IMAGE_SCN_ALIGN_32BYTES=6291456,
    IMAGE_SCN_ALIGN_64BYTES=7340032,
    IMAGE_SCN_ALIGN_128BYTES=8388608,
    IMAGE_SCN_ALIGN_256BYTES=9437184,
    IMAGE_SCN_ALIGN_512BYTES=10485760,
    IMAGE_SCN_ALIGN_1024BYTES=11534336,
    IMAGE_SCN_ALIGN_2048BYTES=12582912,
    IMAGE_SCN_ALIGN_4096BYTES=13631488,
    IMAGE_SCN_ALIGN_8192BYTES=14680064,
    IMAGE_SCN_LNK_NRELOC_OVFL=16777216,
    IMAGE_SCN_MEM_DISCARDABLE=33554432,
    IMAGE_SCN_MEM_NOT_CACHED=67108864,
    IMAGE_SCN_MEM_NOT_PAGED=134217728,
    IMAGE_SCN_MEM_SHARED=268435456,
    IMAGE_SCN_MEM_EXECUTE=536870912,
    IMAGE_SCN_MEM_READ=1073741824,
    IMAGE_SCN_MEM_WRITE=2147483648
} SectionFlags;

union Misc {
    dword PhysicalAddress;
    dword VirtualSize;
};

struct IMAGE_SECTION_HEADER {
    char Name[8];
    union Misc Misc;
    ImageBaseOffset32 VirtualAddress;
    dword SizeOfRawData;
    dword PointerToRawData;
    dword PointerToRelocations;
    dword PointerToLinenumbers;
    word NumberOfRelocations;
    word NumberOfLinenumbers;
    enum SectionFlags Characteristics;
};

typedef struct IMAGE_NT_HEADERS64 IMAGE_NT_HEADERS64, *PIMAGE_NT_HEADERS64;

struct IMAGE_NT_HEADERS64 {
    char Signature[4];
    struct IMAGE_FILE_HEADER FileHeader;
    struct IMAGE_OPTIONAL_HEADER64 OptionalHeader;
};

typedef struct VS_VERSION_INFO VS_VERSION_INFO, *PVS_VERSION_INFO;

struct VS_VERSION_INFO {
    word StructLength;
    word ValueLength;
    word StructType;
    wchar16 Info[16];
    byte Padding[2];
    dword Signature;
    word StructVersion[2];
    word FileVersion[4];
    word ProductVersion[4];
    dword FileFlagsMask[2];
    dword FileFlags;
    dword FileOS;
    dword FileType;
    dword FileSubtype;
    dword FileTimestamp;
};

typedef struct IMAGE_RESOURCE_DATA_ENTRY IMAGE_RESOURCE_DATA_ENTRY, *PIMAGE_RESOURCE_DATA_ENTRY;

struct IMAGE_RESOURCE_DATA_ENTRY {
    dword OffsetToData;
    dword Size;
    dword CodePage;
    dword Reserved;
};

typedef struct VarFileInfo VarFileInfo, *PVarFileInfo;

struct VarFileInfo {
    word wLength;
    word wValueLength;
    word wType;
};

typedef struct IMAGE_RESOURCE_DIRECTORY IMAGE_RESOURCE_DIRECTORY, *PIMAGE_RESOURCE_DIRECTORY;

struct IMAGE_RESOURCE_DIRECTORY {
    dword Characteristics;
    dword TimeDateStamp;
    word MajorVersion;
    word MinorVersion;
    word NumberOfNamedEntries;
    word NumberOfIdEntries;
};

typedef struct StringInfo StringInfo, *PStringInfo;

struct StringInfo {
    word wLength;
    word wValueLength;
    word wType;
};

typedef struct IMAGE_DOS_HEADER IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER;

struct IMAGE_DOS_HEADER {
    char e_magic[2]; // Magic number
    word e_cblp; // Bytes of last page
    word e_cp; // Pages in file
    word e_crlc; // Relocations
    word e_cparhdr; // Size of header in paragraphs
    word e_minalloc; // Minimum extra paragraphs needed
    word e_maxalloc; // Maximum extra paragraphs needed
    word e_ss; // Initial (relative) SS value
    word e_sp; // Initial SP value
    word e_csum; // Checksum
    word e_ip; // Initial IP value
    word e_cs; // Initial (relative) CS value
    word e_lfarlc; // File address of relocation table
    word e_ovno; // Overlay number
    word e_res[4][4]; // Reserved words
    word e_oemid; // OEM identifier (for e_oeminfo)
    word e_oeminfo; // OEM information; e_oemid specific
    word e_res2[10][10]; // Reserved words
    dword e_lfanew; // File address of new exe header
    byte e_program[64]; // Actual DOS program
};

typedef struct _WDF_BIND_INFO _WDF_BIND_INFO, *P_WDF_BIND_INFO;

struct _WDF_BIND_INFO { // PlaceHolder Structure
};

typedef ulonglong size_t;

typedef struct DotNetPdbInfo DotNetPdbInfo, *PDotNetPdbInfo;

struct DotNetPdbInfo {
    char signature[4];
    GUID guid;
    dword age;
    char pdbname[21];
};




void FUN_140001000(ulonglong param_1,longlong param_2,uint *param_3)

{
  longlong lVar1;
  ulonglong uVar2;
  
  uVar2 = param_1;
  if ((*(byte *)param_3 & 4) != 0) {
    uVar2 = (longlong)(int)param_3[1] + param_1 & (longlong)(int)-param_3[2];
  }
  lVar1 = (ulonglong)*(uint *)(*(longlong *)(param_2 + 0x10) + 8) + *(longlong *)(param_2 + 8);
  if ((*(byte *)(lVar1 + 3) & 0xf) != 0) {
    param_1 = param_1 + (longlong)(int)(*(byte *)(lVar1 + 3) & 0xfffffff0);
  }
  FUN_1400049b0(param_1 ^ *(ulonglong *)((longlong)(int)(*param_3 & 0xfffffff8) + uVar2));
  return;
}



undefined8 * FUN_1400010a0(undefined8 *param_1,undefined8 *param_2,ulonglong param_3)

{
  undefined8 uVar1;
  int iVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  ulonglong uVar5;
  ulonglong uVar6;
  
  uVar5 = (longlong)param_2 - (longlong)param_1;
  if (param_2 < param_1) {
    puVar4 = (undefined8 *)((longlong)param_1 + param_3);
    puVar3 = puVar4;
    if (param_3 < 8) goto LAB_1400012b4;
    if (((ulonglong)puVar4 & 7) != 0) {
      if (((ulonglong)puVar4 & 1) != 0) {
        puVar4 = (undefined8 *)((longlong)puVar4 + -1);
        param_3 = param_3 - 1;
        *(undefined *)puVar4 = *(undefined *)(uVar5 + (longlong)puVar4);
      }
      if (((ulonglong)puVar4 & 2) != 0) {
        puVar4 = (undefined8 *)((longlong)puVar4 + -2);
        param_3 = param_3 - 2;
        *(undefined2 *)puVar4 = *(undefined2 *)(uVar5 + (longlong)puVar4);
      }
      if (((ulonglong)puVar4 & 4) != 0) {
        puVar4 = (undefined8 *)((longlong)puVar4 + -4);
        param_3 = param_3 - 4;
        *(undefined4 *)puVar4 = *(undefined4 *)(uVar5 + (longlong)puVar4);
      }
    }
    while (uVar6 = param_3 >> 5, puVar3 = puVar4, uVar6 != 0) {
      if ((uVar6 < 0x2000) || (0xfffffffffffff000 < uVar5)) goto LAB_1400012f0;
      do {
        iVar2 = 0x20;
        do {
          puVar3 = puVar4;
          iVar2 = iVar2 + -1;
          puVar4 = puVar3 + -0x10;
        } while (iVar2 != 0);
        iVar2 = 0x40;
        puVar3 = puVar3 + 0x1f0;
        do {
          uVar1 = *(undefined8 *)((uVar5 - 0x10) + (longlong)puVar3);
          puVar3[-1] = *(undefined8 *)((uVar5 - 8) + (longlong)puVar3);
          puVar3[-2] = uVar1;
          uVar1 = *(undefined8 *)((uVar5 - 0x20) + (longlong)puVar3);
          puVar3[-3] = *(undefined8 *)((uVar5 - 0x18) + (longlong)puVar3);
          puVar3[-4] = uVar1;
          uVar1 = *(undefined8 *)((uVar5 - 0x30) + (longlong)puVar3);
          puVar4 = puVar3 + -8;
          puVar3[-5] = *(undefined8 *)((uVar5 - 0x28) + (longlong)puVar3);
          puVar3[-6] = uVar1;
          uVar1 = *(undefined8 *)(uVar5 + (longlong)puVar4);
          iVar2 = iVar2 + -1;
          puVar3[-7] = *(undefined8 *)(uVar5 + 8 + (longlong)puVar4);
          *puVar4 = uVar1;
          puVar3 = puVar4;
        } while (iVar2 != 0);
        param_3 = param_3 - 0x1000;
      } while (0xfff < param_3);
      LOCK();
    }
    goto LAB_140001297;
  }
  puVar4 = param_1;
  if (param_3 < 8) goto LAB_140001114;
  puVar3 = param_1;
  if (((ulonglong)param_1 & 7) != 0) {
    if (((ulonglong)param_1 & 1) != 0) {
      param_3 = param_3 - 1;
      *(undefined *)param_1 = *(undefined *)(uVar5 + (longlong)param_1);
      puVar3 = (undefined8 *)((longlong)param_1 + 1);
    }
    if (((ulonglong)puVar3 & 2) != 0) {
      param_3 = param_3 - 2;
      *(undefined2 *)puVar3 = *(undefined2 *)(uVar5 + (longlong)puVar3);
      puVar3 = (undefined8 *)((longlong)puVar3 + 2);
    }
    if (((ulonglong)puVar3 & 4) != 0) {
      param_3 = param_3 - 4;
      *(undefined4 *)puVar3 = *(undefined4 *)(uVar5 + (longlong)puVar3);
      puVar3 = (undefined8 *)((longlong)puVar3 + 4);
    }
  }
  while (uVar6 = param_3 >> 5, puVar4 = puVar3, uVar6 != 0) {
    if ((uVar6 < 0x2000) || (uVar5 < 0x1000)) goto LAB_140001150;
    do {
      iVar2 = 0x20;
      do {
        puVar4 = puVar3;
        iVar2 = iVar2 + -1;
        puVar3 = puVar4 + 0x10;
      } while (iVar2 != 0);
      iVar2 = 0x40;
      puVar4 = puVar4 + -0x1f0;
      do {
        uVar1 = *(undefined8 *)(uVar5 + 8 + (longlong)puVar4);
        *puVar4 = *(undefined8 *)(uVar5 + (longlong)puVar4);
        puVar4[1] = uVar1;
        uVar1 = *(undefined8 *)(uVar5 + 0x18 + (longlong)puVar4);
        puVar4[2] = *(undefined8 *)(uVar5 + 0x10 + (longlong)puVar4);
        puVar4[3] = uVar1;
        uVar1 = *(undefined8 *)(uVar5 + 0x28 + (longlong)puVar4);
        puVar3 = puVar4 + 8;
        puVar4[4] = *(undefined8 *)(uVar5 + 0x20 + (longlong)puVar4);
        puVar4[5] = uVar1;
        uVar1 = *(undefined8 *)((uVar5 - 8) + (longlong)puVar3);
        iVar2 = iVar2 + -1;
        puVar4[6] = *(undefined8 *)((uVar5 - 0x10) + (longlong)puVar3);
        puVar4[7] = uVar1;
        puVar4 = puVar3;
      } while (iVar2 != 0);
      param_3 = param_3 - 0x1000;
    } while (0xfff < param_3);
    LOCK();
  }
  goto LAB_1400010f7;
LAB_1400012f0:
  do {
    uVar1 = *(undefined8 *)((uVar5 - 0x10) + (longlong)puVar4);
    puVar3 = puVar4 + -4;
    puVar4[-1] = *(undefined8 *)((uVar5 - 8) + (longlong)puVar4);
    puVar4[-2] = uVar1;
    uVar1 = *(undefined8 *)(uVar5 + (longlong)puVar3);
    uVar6 = uVar6 - 1;
    puVar4[-3] = *(undefined8 *)(uVar5 + 8 + (longlong)puVar3);
    *puVar3 = uVar1;
    puVar4 = puVar3;
  } while (uVar6 != 0);
  param_3 = param_3 & 0x1f;
LAB_140001297:
  uVar6 = param_3 >> 3;
  if (uVar6 != 0) {
    do {
      puVar3 = puVar3 + -1;
      uVar6 = uVar6 - 1;
      *puVar3 = *(undefined8 *)(uVar5 + (longlong)puVar3);
    } while (uVar6 != 0);
    param_3 = param_3 & 7;
  }
LAB_1400012b4:
  if (param_3 == 0) {
    return param_1;
  }
  do {
    puVar3 = (undefined8 *)((longlong)puVar3 + -1);
    param_3 = param_3 - 1;
    *(undefined *)puVar3 = *(undefined *)(uVar5 + (longlong)puVar3);
  } while (param_3 != 0);
  return param_1;
LAB_140001150:
  do {
    uVar1 = *(undefined8 *)(uVar5 + 8 + (longlong)puVar3);
    puVar4 = puVar3 + 4;
    *puVar3 = *(undefined8 *)(uVar5 + (longlong)puVar3);
    puVar3[1] = uVar1;
    uVar1 = *(undefined8 *)((uVar5 - 8) + (longlong)puVar4);
    uVar6 = uVar6 - 1;
    puVar3[2] = *(undefined8 *)((uVar5 - 0x10) + (longlong)puVar4);
    puVar3[3] = uVar1;
    puVar3 = puVar4;
  } while (uVar6 != 0);
  param_3 = param_3 & 0x1f;
LAB_1400010f7:
  uVar6 = param_3 >> 3;
  if (uVar6 != 0) {
    do {
      *puVar4 = *(undefined8 *)(uVar5 + (longlong)puVar4);
      puVar4 = puVar4 + 1;
      uVar6 = uVar6 - 1;
    } while (uVar6 != 0);
    param_3 = param_3 & 7;
  }
LAB_140001114:
  if (param_3 == 0) {
    return param_1;
  }
  do {
    *(undefined *)puVar4 = *(undefined *)(uVar5 + (longlong)puVar4);
    puVar4 = (undefined8 *)((longlong)puVar4 + 1);
    param_3 = param_3 - 1;
  } while (param_3 != 0);
  return param_1;
}



void FUN_1400013f0(ulonglong *param_1,ulonglong param_2,ulonglong param_3)

{
  uint uVar1;
  ulonglong *puVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  
  uVar3 = param_3;
  if (7 < param_3) {
    param_2 = (param_2 & 0xff) * 0x101010101010101;
    if (0x3f < param_3) {
      uVar1 = -(int)param_1 & 7;
      if (uVar1 != 0) {
        uVar3 = param_3 - uVar1;
        *param_1 = param_2;
      }
      param_1 = (ulonglong *)((ulonglong)uVar1 + (longlong)param_1);
      param_3 = uVar3 & 0x3f;
      uVar3 = uVar3 >> 6;
      if (uVar3 != 0) {
        puVar2 = param_1;
        if (uVar3 < 0x1c00) {
          do {
            *puVar2 = param_2;
            puVar2[1] = param_2;
            puVar2[2] = param_2;
            param_1 = puVar2 + 8;
            puVar2[3] = param_2;
            puVar2[4] = param_2;
            uVar3 = uVar3 - 1;
            puVar2[5] = param_2;
            puVar2[6] = param_2;
            puVar2[7] = param_2;
            puVar2 = param_1;
          } while (uVar3 != 0);
        }
        else {
          do {
            *puVar2 = param_2;
            puVar2[1] = param_2;
            puVar2[2] = param_2;
            param_1 = puVar2 + 8;
            puVar2[3] = param_2;
            puVar2[4] = param_2;
            uVar3 = uVar3 - 1;
            puVar2[5] = param_2;
            puVar2[6] = param_2;
            puVar2[7] = param_2;
            puVar2 = param_1;
          } while (uVar3 != 0);
          LOCK();
        }
      }
    }
    uVar3 = param_3 & 7;
    for (uVar4 = param_3 >> 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *param_1 = param_2;
      param_1 = param_1 + 1;
    }
  }
  for (; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(char *)param_1 = (char)param_2;
    param_1 = (ulonglong *)((longlong)param_1 + 1);
  }
  return;
}



// FUN_140001550
uint asf_master_dis(longlong param_1)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = FUN_140003c94((int *)(param_1 + 0x20));
  if (iVar2 == 0x10002) {
    out(0xcd6,0x28);
    bVar1 = in(0xcd7);
    out(0xcd6,0x28);
    bVar1 = bVar1 & 0xfb | 1;
    uVar3 = bVar1 | 0x10000;
    out(0xcd7,bVar1);
  }
  else {
    uVar3 = FUN_140003c94((int *)(param_1 + 0x20));
    if (uVar3 == 0x20002) {
      out(0xcd6,2);
      bVar1 = in(0xcd7);
      out(0xcd6,2);
      uVar3 = bVar1 & 0xfe | 0x20000;
      out(0xcd7,bVar1 & 0xfe);
    }
  }
  return uVar3;
}



undefined8
FUN_140001610(longlong param_1,uint param_2,undefined8 param_3,uint param_4,undefined4 param_5,
             int param_6,undefined4 param_7)

{
  undefined8 uVar1;
  
  if (((param_2 < 0x18) && (param_4 < 0x18)) || (param_6 == 0)) {
    uVar1 = 0xc000009a;
  }
  else {
    uVar1 = FUN_140003ddc((undefined4 *)(param_1 + 0x58),param_2,param_3,param_4,param_5,param_6,
                          param_7);
    if (-1 < (int)uVar1) {
      FUN_140003f54(param_1 + 0x58);
      uVar1 = 0;
    }
  }
  return uVar1;
}



int FUN_140001668(longlong param_1,undefined4 *param_2,undefined8 *param_3,undefined4 *param_4,
                 undefined4 *param_5,undefined4 *param_6)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_140003e00((undefined4 *)(param_1 + 0x58),param_2,param_3,param_4,param_5,param_6,
                        (undefined4 *)&stack0x00000038);
  iVar2 = 0;
  if (iVar1 < 0) {
    iVar2 = iVar1;
  }
  return iVar2;
}



longlong FUN_14000180c(longlong param_1)

{
  char cVar1;
  uint uVar2;
  undefined7 extraout_var;
  ulonglong uVar4;
  longlong lVar5;
  int iVar3;
  
  cVar1 = FUN_14000411c(param_1 + 0x58);
  iVar3 = (int)CONCAT71(extraout_var,cVar1);
  uVar2 = iVar3 - 1;
  if (uVar2 == 0) {
LAB_140001853:
    lVar5 = (ulonglong)(uVar2 >> 8) << 8;
  }
  else {
    uVar4 = (ulonglong)(iVar3 - 2U);
    if (iVar3 - 2U != 0) {
      uVar2 = iVar3 - 3;
      if (uVar2 != 0) goto LAB_140001853;
      if ((*(char *)(param_1 + 1) != '\0') && (*(int *)(param_1 + 0x80) == 3)) {
        *(undefined *)(param_1 + 2) = 1;
      }
      uVar4 = (*DAT_1400067c0)(DAT_1400070e0,*(undefined8 *)(param_1 + 0x10));
    }
    lVar5 = CONCAT71((int7)(uVar4 >> 8),1);
  }
  return lVar5;
}



undefined FUN_14000185c(longlong param_1,undefined8 param_2,int param_3,byte *param_4,
                       ulonglong param_5,undefined8 *param_6,ulonglong param_7)

{
  char cVar1;
  char cVar2;
  undefined uVar3;
  char cVar4;
  ulonglong uVar5;
  undefined8 uVar6;
  longlong lVar7;
  byte bVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  int iVar11;
  int iVar12;
  byte bVar13;
  byte bVar14;
  
  if ((((param_5 == 0) || (param_4 == (byte *)0x0)) || (param_7 == 0)) ||
     (param_6 == (undefined8 *)0x0)) {
LAB_14000198f:
    uVar9 = 0xc000000d;
  }
  else {
    if ((param_3 == 0x53592004) || (param_3 == 0x53592007)) {
      if ((param_5 == 0x25) && (param_7 == 0x25)) {
        if (*(int *)(param_1 + 0x80) != 1) {
          uVar9 = 0xc00000a3;
          goto LAB_1400019b7;
        }
        if (param_4[2] < 0x80) {
          bVar14 = param_4[1];
          uVar9 = 1;
          iVar11 = 2;
          if ((bVar14 & 0x80) != 0) {
            uVar9 = 2;
          }
          bVar8 = bVar14 & 0x7f;
          if (bVar8 < 7) {
            if (bVar8 == 6) {
              if (param_4[4] == 2) {
                uVar3 = 0;
                bVar14 = 2;
                iVar12 = 1;
LAB_140001b03:
                iVar11 = 4;
                goto LAB_140001ad4;
              }
            }
            else if ((bVar14 & 0x7f) == 0) {
              if (param_4[4] == 0) {
                uVar3 = 0;
                bVar14 = 0;
                iVar11 = 1;
                goto LAB_140001ad0;
              }
            }
            else {
              if (bVar8 == 1) goto LAB_140001b28;
              if (bVar8 == 2) {
                if (param_4[4] == 1) {
                  uVar3 = 0;
                  bVar14 = 0;
                  goto LAB_140001ad0;
                }
              }
              else if (bVar8 == 3) {
                if (param_4[4] == 0) {
                  uVar3 = 1;
                  bVar14 = 0;
                  iVar12 = 2;
                  iVar11 = 2;
                  goto LAB_140001ad4;
                }
              }
              else if (bVar8 == 4) {
                if (param_4[4] == 1) {
                  uVar3 = 0;
                  bVar14 = 1;
                  iVar11 = 3;
                  goto LAB_140001ad0;
                }
              }
              else {
                if (bVar8 != 5) goto LAB_140001b28;
                if (param_4[4] == 0) {
                  uVar3 = 1;
                  bVar14 = 0;
                  iVar12 = 2;
                  iVar11 = 3;
                  goto LAB_140001ad4;
                }
              }
            }
          }
          else {
            if (bVar8 != 7) {
              if (bVar8 == 8) {
                bVar14 = param_4[4];
                if (0x1f < (byte)(bVar14 - 1)) {
LAB_140001b28:
                  *(undefined *)param_6 = 0x19;
                  uVar9 = 0xc0000010;
                  goto LAB_1400019b7;
                }
                uVar3 = 0;
                iVar11 = 6;
              }
              else {
                if (bVar8 == 9) {
                  if (param_4[4] == 0) {
                    uVar3 = 0x20;
                    bVar14 = 0;
                    iVar12 = 2;
                    iVar11 = 6;
                    goto LAB_140001ad4;
                  }
                  goto LAB_140001ab5;
                }
                if (bVar8 == 10) {
                  if (param_4[4] != 2) goto LAB_140001ab5;
                  uVar3 = 2;
                  bVar14 = 2;
                  iVar11 = 5;
                }
                else {
                  if ((bVar8 != 0xb) || (bVar14 = param_4[4], 0x1f < (byte)(bVar14 - 1)))
                  goto LAB_140001b28;
                  uVar3 = 0x20;
                  iVar11 = 7;
                }
              }
LAB_140001ad0:
              iVar12 = 1;
LAB_140001ad4:
              cVar4 = FUN_140002208(param_1,(longlong)param_4,(undefined *)param_6,iVar11,iVar12,
                                    uVar9,bVar14,uVar3);
              if (cVar4 != '\0') {
                return 1;
              }
              return 0;
            }
            if (param_4[4] == 0) {
              uVar3 = 2;
              bVar14 = 0;
              iVar12 = 2;
              goto LAB_140001b03;
            }
          }
LAB_140001ab5:
          *(undefined *)param_6 = 0x19;
        }
        else {
          *(undefined *)param_6 = 0x10;
        }
        uVar9 = 0xc0000010;
LAB_1400019b7:
        FUN_140002438(param_1,uVar9,0);
        return 1;
      }
      goto LAB_14000198f;
    }
    if (param_3 == 0x5359200b) {
      if ((0x11 < param_5) && (7 < param_7)) {
        if ((*param_4 < 0x80) &&
           (((param_4[1] < 0x80 && (*param_4 <= param_4[1])) && (*(longlong *)(param_4 + 2) != 0))))
        {
          uVar6 = FUN_14000363c(param_1,(longlong)&LAB_1400015d0,
                                (undefined8 *)&stack0xffffffffffffffd8,0x20);
          uVar9 = 0;
          uVar10 = 8;
          *param_6 = uVar6;
        }
        else {
          uVar10 = 0;
          uVar9 = 0xc000000d;
        }
        uVar3 = FUN_140002438(param_1,uVar9,uVar10);
        return uVar3;
      }
      goto LAB_14000198f;
    }
    if (param_3 == 0x5359200f) {
      if (param_5 == 8) {
        lVar7 = (*DAT_1400069a0)(DAT_1400070e0,*(undefined8 *)(param_1 + 0x28),PTR_DAT_140006078);
        *(byte **)(lVar7 + 8) = param_4;
        (*DAT_140006f30)(DAT_1400070e0,*(undefined8 *)(param_1 + 0x28));
        return 1;
      }
      goto LAB_14000198f;
    }
    if (param_3 == 0x53592013) {
      if (0x16 < param_7) {
        *(undefined4 *)param_6 = 0x12010;
        *(undefined *)((longlong)param_6 + 4) = 0;
        uVar9 = 0;
        uVar10 = 0x17;
        goto LAB_140001997;
      }
    }
    else {
      if (param_3 != 0x535924a4) {
        if ((param_3 == 0x53593004) || (param_3 == 0x53593007)) {
          if (param_5 == 0x24) {
            if (param_7 < 0x24) goto LAB_14000198f;
            *(undefined4 *)(param_1 + 0x84) = 1;
          }
          else {
            if ((param_5 < 0x45) || (param_7 < 0x45)) goto LAB_14000198f;
            *(undefined4 *)(param_1 + 0x84) = 2;
          }
          if (*(int *)(param_1 + 0x84) == 1) {
            uVar5 = (ulonglong)param_4[3] + 4;
          }
          else {
            uVar5 = (ulonglong)param_4[4] + 5;
          }
          if ((param_5 & 0xffffffff) < uVar5) {
            uVar9 = 0xc000000d;
          }
          else if (*(int *)(param_1 + 0x80) == 1) {
            if (param_4[2] < 0x80) {
              if (param_4[1] == 0x10) {
                iVar11 = 1;
                bVar14 = 0;
                if (*(int *)(param_1 + 0x84) == 1) {
                  bVar13 = param_4[3];
                  bVar8 = param_4[4];
                }
                else {
                  bVar13 = param_4[4];
                  bVar8 = param_4[3];
                }
LAB_140001da9:
                cVar4 = FUN_1400020f4(param_1,(longlong)param_4,(undefined *)param_6,iVar11,bVar8,
                                      bVar13,bVar14);
                if (cVar4 != '\0') {
                  return 1;
                }
                return 0;
              }
              if (param_4[1] == 0x11) {
                iVar11 = 2;
                bVar8 = param_4[3];
                if (*(int *)(param_1 + 0x84) == 1) {
                  bVar13 = 0;
                  iVar11 = 2;
                  bVar14 = bVar8;
                  bVar8 = 0;
                }
                else {
                  bVar14 = 0x40;
                  bVar13 = 0;
                }
                goto LAB_140001da9;
              }
              *(undefined *)param_6 = 0x19;
            }
            else {
              *(undefined *)param_6 = 0x10;
            }
            uVar9 = 0xc0000010;
          }
          else {
            uVar9 = 0xc00000a3;
          }
          FUN_140002438(param_1,uVar9,0);
          return 1;
        }
        goto LAB_14000198f;
      }
      if (4 < param_7) {
        (*DAT_140006d30)(DAT_1400070e0,*(undefined8 *)(param_1 + 0x40));
        cVar4 = *(char *)(param_1 + 1);
        cVar1 = *(char *)(param_1 + 2);
        cVar2 = *(char *)(param_1 + 3);
        (*DAT_140006d38)(DAT_1400070e0);
        *(uint *)param_6 =
             -(uint)(cVar2 != '\0') & 4 | -(uint)(cVar1 != '\0') & 2 | (uint)(cVar4 != '\0');
        if (*(int *)(param_1 + 0x68) == 0) {
          uVar3 = **(undefined **)(param_1 + 0x60);
        }
        else {
          uVar3 = in((short)*(undefined4 *)(param_1 + 0x6c));
        }
        *(undefined *)((longlong)param_6 + 4) = uVar3;
        uVar3 = FUN_140002438(param_1,0,5);
        return uVar3;
      }
    }
    uVar9 = 0xc0000023;
  }
  uVar10 = 0;
LAB_140001997:
  uVar3 = FUN_140002438(param_1,uVar9,uVar10);
  return uVar3;
}



void FUN_140001f60(longlong param_1)

{
  FUN_140002438(param_1,0xc0000010,0);
  return;
}



bool FUN_140001f70(longlong param_1,int param_2,int param_3,undefined4 param_4,undefined param_5,
                  undefined param_6,undefined param_7,undefined8 param_8,undefined param_9,
                  undefined8 param_10,undefined8 param_11,undefined *param_12,undefined4 param_13)

{
  byte bVar1;
  char cVar2;
  undefined *local_18;
  longlong local_10;
  
  out((short)*(undefined4 *)(param_1 + 0x6c) + 0x14,1);
  bVar1 = in((short)*(undefined4 *)(param_1 + 0x6c) + 0x14);
  if ((bVar1 & 1) == 0) {
    *param_12 = 0x1a;
    FUN_140002438(param_1,0xc00000a3,0);
    return true;
  }
  if (param_2 != 1) {
    if (((param_2 != 2) && (param_2 != 3)) && (param_2 != 4)) {
      if (param_2 == 5) goto LAB_140002014;
      if (param_2 != 6) {
        if (param_2 == 7) goto LAB_140002014;
        if (param_2 != 8) goto LAB_1400020b2;
      }
    }
    if ((param_3 != 1) && (param_3 != 2)) goto LAB_1400020b2;
  }
LAB_140002014:
  *(int *)(param_1 + 0x88) = param_2;
  *(int *)(param_1 + 0x8c) = param_3;
  *(undefined4 *)(param_1 + 0x90) = param_4;
  *(undefined *)(param_1 + 0x94) = param_5;
  *(undefined *)(param_1 + 0x95) = param_6;
  *(undefined4 *)(param_1 + 0x80) = 2;
  *(undefined *)(param_1 + 0x96) = param_7;
  *(undefined *)(param_1 + 0x97) = 0;
  *(undefined8 *)(param_1 + 0x98) = param_8;
  *(undefined *)(param_1 + 0xa0) = param_9;
  *(undefined *)(param_1 + 0xa1) = 0;
  *(undefined8 *)(param_1 + 0xa8) = param_10;
  *(undefined8 *)(param_1 + 0xb0) = param_11;
  *(undefined **)(param_1 + 0xb8) = param_12;
  *(undefined4 *)(param_1 + 0xc0) = param_13;
LAB_1400020b2:
  FUN_140003bd0(param_1);
  local_18 = &LAB_1400027a4;
  local_10 = param_1;
  cVar2 = (*DAT_1400067c8)(DAT_1400070e0,*(undefined8 *)(param_1 + 0x10),&LAB_140003c74,&local_18);
  return cVar2 != '\0';
}



undefined FUN_1400020f4(longlong param_1,longlong param_2,undefined *param_3,int param_4,
                       undefined param_5,undefined param_6,byte param_7)

{
  undefined uVar1;
  undefined uVar2;
  bool bVar3;
  int iVar4;
  undefined *puVar5;
  longlong lVar6;
  undefined *puVar7;
  
  *param_3 = 0x13;
  param_3[1] = *(undefined *)(param_2 + 1);
  param_3[2] = *(undefined *)(param_2 + 2);
  uVar1 = *(undefined *)(param_2 + 2);
  if (*(int *)(param_1 + 0x84) == 1) {
    uVar2 = *(undefined *)(param_2 + 3);
    puVar7 = param_3 + 3;
    lVar6 = param_2 + 4;
    puVar5 = param_3 + 4;
  }
  else {
    uVar2 = *(undefined *)(param_2 + 4);
    puVar7 = param_3 + 4;
    lVar6 = param_2 + 5;
    puVar5 = param_3 + 5;
  }
  *puVar7 = uVar2;
  if (param_4 == 1) {
    iVar4 = 0x45;
    if (*(int *)(param_1 + 0x84) == 1) {
      iVar4 = 0x24;
    }
  }
  else {
    if (param_4 != 2) {
      FUN_140002438(param_1,0xc0000010,0);
      return 1;
    }
    if (*(int *)(param_1 + 0x84) == 1) {
      iVar4 = param_7 + 4;
    }
    else {
      iVar4 = param_7 + 5;
    }
  }
  bVar3 = FUN_140001f70(param_1,8,param_4,1,uVar1,param_5,param_6,lVar6,param_7,puVar7,puVar5,
                        param_3,iVar4);
  return bVar3;
}



void FUN_140002208(longlong param_1,longlong param_2,undefined *param_3,int param_4,int param_5,
                  undefined4 param_6,undefined param_7,undefined param_8)

{
  *param_3 = 7;
  param_3[1] = *(undefined *)(param_2 + 1);
  param_3[2] = *(undefined *)(param_2 + 2);
  param_3[3] = *(undefined *)(param_2 + 3);
  FUN_140001f70(param_1,param_4,param_5,param_6,*(undefined *)(param_2 + 2),
                *(undefined *)(param_2 + 3),param_7,param_2 + 5,param_8,param_3 + 4,param_3 + 5,
                param_3,0x25);
  return;
}



void FUN_1400022ac(longlong param_1)

{
  undefined *local_18;
  longlong local_10;
  
  local_18 = &LAB_140002790;
  local_10 = param_1;
  (*DAT_1400067c8)(DAT_1400070e0,*(undefined8 *)(param_1 + 0x10),&LAB_140003c74,&local_18);
  return;
}



void FUN_1400022e4(longlong param_1)

{
  uint uVar1;
  undefined8 uVar2;
  longlong lVar3;
  uint uVar4;
  undefined *local_18;
  longlong local_10;
  
  local_18 = &LAB_14000277c;
  local_10 = param_1;
  (*DAT_1400067c8)(DAT_1400070e0,*(undefined8 *)(param_1 + 0x10),&LAB_140003c74,&local_18);
  uVar1 = (*DAT_1400063c0)(DAT_1400070e0,*(undefined8 *)(param_1 + 0x18));
  uVar4 = 0;
  if (uVar1 != 0) {
    do {
      uVar2 = (*DAT_1400063e0)(DAT_1400070e0,*(undefined8 *)(param_1 + 0x18),uVar4);
      (*DAT_1400066d8)(DAT_1400070e0,uVar2,1);
      lVar3 = (*DAT_1400069a0)(DAT_1400070e0,uVar2);
      uVar4 = uVar4 + 1;
      *(undefined4 *)(lVar3 + 0x10) = 1;
    } while (uVar4 < uVar1);
  }
  return;
}



void FUN_140002438(longlong param_1,undefined4 param_2,undefined4 param_3)

{
  longlong lVar1;
  
  (*DAT_140006d30)(DAT_1400070e0,*(undefined8 *)(param_1 + 0x40));
  (*DAT_140006d50)(DAT_1400070e0,*(undefined8 *)(param_1 + 0x30),0);
  lVar1 = *(longlong *)(param_1 + 0x20);
  if (lVar1 == 0) {
    (*DAT_140006d38)(DAT_1400070e0,*(undefined8 *)(param_1 + 0x40));
  }
  else {
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(undefined *)(param_1 + 2) = 0;
    *(undefined *)(param_1 + 1) = 0;
    (*DAT_140006d38)(DAT_1400070e0,*(undefined8 *)(param_1 + 0x40));
    (*DAT_140006b98)(DAT_1400070e0,lVar1,param_2,param_3);
  }
  return;
}



undefined8 FUN_1400024e0(longlong param_1)

{
  undefined8 uVar1;
  
  uVar1 = FUN_140003e48((undefined4 *)(param_1 + 0x58));
  if (-1 < (int)uVar1) {
    *(undefined4 *)(param_1 + 0x120) = 1;
    *(undefined4 *)(param_1 + 0x124) = 1;
    *(undefined4 *)(param_1 + 0x84) = 0;
    *(undefined4 *)(param_1 + 0x88) = 0;
    *(undefined4 *)(param_1 + 0x8c) = 0;
    *(undefined4 *)(param_1 + 0x90) = 0;
    *(undefined *)(param_1 + 0x94) = 0xff;
    *(undefined *)(param_1 + 0x95) = 0;
    *(undefined *)(param_1 + 0x96) = 0;
    *(undefined *)(param_1 + 0x97) = 0;
    *(undefined8 *)(param_1 + 0x98) = 0;
    *(undefined *)(param_1 + 0xa0) = 0;
    *(undefined *)(param_1 + 0xa1) = 0;
    *(undefined8 *)(param_1 + 0xa8) = 0;
    *(undefined8 *)(param_1 + 0xb0) = 0;
    *(undefined4 *)(param_1 + 0x80) = 1;
    *(undefined8 *)(param_1 + 0xb8) = 0;
    *(undefined4 *)(param_1 + 200) = 1;
    uVar1 = 0;
  }
  return uVar1;
}




// FUN_140002574
ulonglong kill_slave(longlong param_1)

{
  byte bVar1;
  undefined8 in_RAX;
  ulonglong uVar2;
  
  *(undefined4 *)(param_1 + 0x70) = 1;
    uVar2 = CONCAT71((int7)((ulonglong)in_RAX >> 8),0x10);
  out((short)*(undefined4 *)(param_1 + 0x14) + 9,0x10);
  bVar1 = in((short)*(undefined4 *)(param_1 + 0x14) + 0x15);
  uVar2 = uVar2 & 0xffffffffffffff00;
  uVar2 = uVar2 & 0xffffffffffffff00 | (ulonglong)bVar1 | 0x10;
  out((short)*(undefined4 *)(param_1 + 0x14) + 0x15,(char)uVar2);
  return uVar2;
}


// FUN_1400025dc
longlong enable_slave(longlong param_1)

{
  longlong lVar1;
  byte bVar2;
  ulonglong in_RAX;
  ulonglong uVar3;
  
  bVar2 = in((short)*(undefined4 *)(param_1 + 0x14) + 0x15);
  uVar3 = in_RAX & 0xffffffffffffff00;
  uVar3 = uVar3 & 0xffffffffffffff00;
  out((short)*(undefined4 *)(param_1 + 0x14) + 0x15,bVar2 & 0xef);
  out((short)*(undefined4 *)(param_1 + 0x14) + 9,0x11);
  return CONCAT71((int7)(uVar3 >> 8),0x11);
}



bool FUN_140002644(longlong param_1)

{
  bool bVar1;
  
  bVar1 = false;
  do {
    (*DAT_140006d30)(DAT_1400070e0,*(undefined8 *)(param_1 + 0x40));
    if ((*(char *)(param_1 + 1) == '\0') || (*(char *)(param_1 + 2) != '\0')) {
      *(undefined *)(param_1 + 3) = 1;
      bVar1 = true;
    }
    (*DAT_140006d38)(DAT_1400070e0,*(undefined8 *)(param_1 + 0x40));
  } while (!bVar1);
  return *(char *)(param_1 + 1) == '\0';
}



undefined8 FUN_1400027b0(undefined8 param_1,undefined8 param_2)

{
  undefined8 uVar1;
  undefined *puVar2;
  undefined8 local_res18 [2];
  ulonglong local_68;
  undefined *local_60;
  ulonglong local_48 [3];
  undefined4 local_30;
  undefined4 local_2c;
  undefined *local_18;
  
  FUN_1400013f0(local_48,0,0x38);
  local_30 = 1;
  local_2c = 1;
  local_48[0]._0_4_ = 0x38;
  local_18 = PTR_DAT_1400060d8;
  FUN_1400013f0(&local_68,0,0x20);
  local_60 = &LAB_140002b74;
  local_68._0_4_ = 0x20;
  uVar1 = (*DAT_1400066f0)(DAT_1400070e0,param_1,param_2,local_48,&local_68,local_res18);
  if (-1 < (int)uVar1) {
    puVar2 = (undefined *)(*DAT_1400069a0)(DAT_1400070e0,local_res18[0],PTR_DAT_1400060d8);
    FUN_14000397c(puVar2,local_res18[0]);
    uVar1 = 0;
  }
  return uVar1;
}



undefined8 FUN_140002884(undefined8 param_1)

{
  longlong lVar1;
  
  lVar1 = (*DAT_1400069a0)(DAT_1400070e0,param_1,PTR_DAT_140006100);
  *(undefined4 *)(lVar1 + 0x120) = 2;
  return 0;
}



undefined8 FUN_1400028f4(undefined8 param_1,int param_2)

{
  longlong lVar1;
  undefined4 uVar2;
  
  lVar1 = (*DAT_1400069a0)(DAT_1400070e0,param_1);
  if (param_2 == 1) {
    uVar2 = 2;
  }
  else if (param_2 == 2) {
    uVar2 = 3;
  }
  else if (param_2 == 3) {
    uVar2 = 4;
  }
  else if (param_2 == 4) {
    uVar2 = 5;
  }
  else if ((param_2 == 5) || (param_2 != 6)) {
    uVar2 = 6;
  }
  else {
    uVar2 = 7;
  }
  *(undefined4 *)(lVar1 + 0x120) = uVar2;
  return 0;
}



void FUN_1400031d4(byte param_1,undefined8 param_2,ulonglong param_3,ulonglong param_4,
                  ulonglong param_5,int param_6)

{
  bool bVar1;
  int iVar2;
  undefined8 uVar3;
  longlong lVar4;
  ulonglong uVar5;
  undefined8 *local_res20;
  undefined8 *local_28 [2];
  
  uVar3 = (*DAT_140006838)(DAT_1400070e0);
  lVar4 = (*DAT_1400069a0)(DAT_1400070e0,uVar3);
  bVar1 = false;
  do {
    (*DAT_140006d30)(DAT_1400070e0,*(undefined8 *)(lVar4 + 0x40));
    if (*(char *)(lVar4 + 1) == '\0') {
      *(undefined *)(lVar4 + 1) = 1;
      *(ulonglong *)(lVar4 + 0x20) = param_3;
      bVar1 = true;
    }
    uVar5 = *(ulonglong *)(lVar4 + 0x40);
    (*DAT_140006d38)(DAT_1400070e0);
  } while (!bVar1);
  local_28[0] = (undefined8 *)0x0;
  if (param_5 != 0) {
    uVar5 = param_3;
    iVar2 = (*DAT_140006bb8)(DAT_1400070e0,param_3,param_5,local_28,0);
    if (iVar2 < 0) {
      param_5 = 0;
    }
  }
  local_res20 = (undefined8 *)0x0;
  if (param_4 == 0) {
    if (param_1 != 0) {
      local_res20 = local_28[0];
      param_4 = param_5;
    }
  }
  else {
    iVar2 = (*DAT_140006bc0)(DAT_1400070e0,param_3,param_4,&local_res20,0);
    uVar5 = param_3;
    if (iVar2 < 0) {
      param_4 = 0;
    }
  }
  FUN_14000185c(lVar4,uVar5 & 0xffffffffffffff00 | (ulonglong)param_1,param_6,(byte *)local_28[0],
                param_5,local_res20,param_4);
  return;
}



void FUN_140003470(undefined8 param_1)

{
  bool bVar1;
  int iVar2;
  undefined8 uVar3;
  longlong lVar4;
  
  uVar3 = (*DAT_140006838)(DAT_1400070e0,param_1);
  lVar4 = (*DAT_1400069a0)(DAT_1400070e0,uVar3);
  bVar1 = FUN_140002644(lVar4);
  if (bVar1 == false) {
    iVar2 = FUN_140003c94((int *)(lVar4 + 0x78));
    if ((iVar2 == 0x10002) || (iVar2 = FUN_140003c94((int *)(lVar4 + 0x78)), iVar2 == 0x20002)) {
      asf_master_dis(lVar4 + 0x58);
    }
    in((short)*(undefined4 *)(lVar4 + 0x6c) + 0x14);
    out((short)*(undefined4 *)(lVar4 + 0x6c) + 0x14,2);
    FUN_140002438(lVar4,0,*(undefined4 *)(lVar4 + 0xc0));
    *(undefined4 *)(lVar4 + 0x84) = 0;
    *(undefined4 *)(lVar4 + 0x88) = 0;
    *(undefined4 *)(lVar4 + 0x8c) = 0;
    *(undefined4 *)(lVar4 + 0x90) = 0;
    *(undefined *)(lVar4 + 0x94) = 0xff;
    *(undefined *)(lVar4 + 0x95) = 0;
    *(undefined *)(lVar4 + 0x96) = 0;
    *(undefined *)(lVar4 + 0x97) = 0;
    *(undefined8 *)(lVar4 + 0x98) = 0;
    *(undefined *)(lVar4 + 0xa0) = 0;
    *(undefined *)(lVar4 + 0xa1) = 0;
    *(undefined8 *)(lVar4 + 0xa8) = 0;
    *(undefined8 *)(lVar4 + 0xb0) = 0;
    *(undefined4 *)(lVar4 + 0x80) = 1;
    *(undefined8 *)(lVar4 + 0xb8) = 0;
  }
  return;
}



void FUN_1400035ec(undefined8 param_1)

{
  longlong lVar1;
  longlong *plVar2;
  undefined8 *puVar3;
  longlong lVar4;
  
  puVar3 = (undefined8 *)(*DAT_1400069a0)(DAT_1400070e0,param_1,PTR_DAT_140006078);
  plVar2 = (longlong *)puVar3[1];
  lVar4 = (*DAT_1400069a0)(DAT_1400070e0,*puVar3);
  lVar1 = *plVar2;
  if (lVar1 != 0) {
    FUN_140003990(lVar4,lVar1);
  }
  *plVar2 = 0;
  FUN_140002438(lVar4,0,0);
  return;
}



undefined8 thunk_FUN_1400027b0(undefined8 param_1,undefined8 param_2)

{
  undefined8 uVar1;
  undefined *puVar2;
  undefined8 auStackX24 [2];
  ulonglong uStack104;
  undefined *puStack96;
  ulonglong auStack72 [3];
  undefined4 uStack48;
  undefined4 uStack44;
  undefined *puStack24;
  
  FUN_1400013f0(auStack72,0,0x38);
  uStack48 = 1;
  uStack44 = 1;
  auStack72[0]._0_4_ = 0x38;
  puStack24 = PTR_DAT_1400060d8;
  FUN_1400013f0(&uStack104,0,0x20);
  puStack96 = &LAB_140002b74;
  uStack104._0_4_ = 0x20;
  uVar1 = (*DAT_1400066f0)(DAT_1400070e0,param_1,param_2,auStack72,&uStack104,auStackX24);
  if (-1 < (int)uVar1) {
    puVar2 = (undefined *)(*DAT_1400069a0)(DAT_1400070e0,auStackX24[0],PTR_DAT_1400060d8);
    FUN_14000397c(puVar2,auStackX24[0]);
    uVar1 = 0;
  }
  return uVar1;
}



undefined8 FUN_14000363c(longlong param_1,longlong param_2,undefined8 *param_3,uint param_4)

{
  int iVar1;
  undefined8 *puVar2;
  undefined8 local_res10;
  undefined8 *local_88;
  undefined8 local_80;
  undefined8 local_78;
  code *local_70;
  undefined8 local_68;
  undefined4 local_60;
  undefined4 local_48;
  undefined4 local_44;
  undefined8 local_40;
  ulonglong local_38;
  undefined *local_30;
  
  if (((param_2 != 0) && (param_3 != (undefined8 *)0x0)) && (param_4 != 0)) {
    local_78 = 0x18;
    local_68 = 0;
    local_70 = FUN_140003bf4;
    FUN_1400013f0((ulonglong *)&local_60,0,0x38);
    local_30 = PTR_DAT_140006128;
    local_40 = *(undefined8 *)(param_1 + 0x18);
    local_60 = 0x38;
    local_48 = 1;
    local_44 = 4;
    iVar1 = (*DAT_1400066c8)(DAT_1400070e0,&local_78,&local_60,&local_res10);
    if (-1 < iVar1) {
      local_88 = (undefined8 *)0x0;
      FUN_1400013f0((ulonglong *)&local_60,0,0x38);
      local_60 = 0x38;
      local_30 = PTR_DAT_140006150;
      local_48 = 1;
      local_44 = 1;
      if (8 < param_4) {
        local_38 = (ulonglong)param_4;
      }
      iVar1 = (*DAT_1400069a8)(DAT_1400070e0,local_res10,&local_60,&local_88);
      if (-1 < iVar1) {
        FUN_1400013f0((ulonglong *)&local_60,0,0x38);
        local_40 = local_res10;
        local_60 = 0x38;
        local_48 = 1;
        local_44 = 1;
        iVar1 = (*DAT_140006d28)(DAT_1400070e0,&local_60,&local_80);
        if (-1 < iVar1) {
          FUN_1400010a0(local_88,param_3,(ulonglong)param_4);
          puVar2 = (undefined8 *)(*DAT_1400069a0)(DAT_1400070e0,local_res10,PTR_DAT_140006128);
          *puVar2 = local_res10;
          *(undefined4 *)(puVar2 + 2) = 1;
          puVar2[3] = param_2;
          puVar2[1] = local_80;
          puVar2[4] = local_88;
          (*DAT_140006d30)(DAT_1400070e0,*(undefined8 *)(param_1 + 0x38));
          iVar1 = (*DAT_1400063c8)(DAT_1400070e0,*(undefined8 *)(param_1 + 0x18),local_res10);
          (*DAT_140006d38)(DAT_1400070e0,*(undefined8 *)(param_1 + 0x38));
          if (iVar1 < 0) {
            return 0;
          }
          return puVar2[4];
        }
      }
      (*DAT_1400069d0)(DAT_1400070e0,local_res10);
    }
  }
  return 0;
}



void FUN_140003928(undefined *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                  undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                  undefined8 param_9,undefined8 param_10)

{
  *param_1 = 2;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  *(undefined8 *)(param_1 + 0x48) = param_2;
  *(undefined8 *)(param_1 + 8) = param_3;
  *(undefined8 *)(param_1 + 0x18) = param_5;
  *(undefined8 *)(param_1 + 0x10) = param_4;
  *(undefined8 *)(param_1 + 0x28) = param_6;
  *(undefined8 *)(param_1 + 0x30) = param_7;
  *(undefined8 *)(param_1 + 0x38) = param_8;
  *(undefined8 *)(param_1 + 0x40) = param_9;
  *(undefined8 *)(param_1 + 0x50) = param_10;
  return;
}



void FUN_14000397c(undefined *param_1,undefined8 param_2)

{
  *param_1 = 1;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  *(undefined8 *)(param_1 + 0x48) = param_2;
  return;
}



void FUN_140003990(longlong param_1,longlong param_2)

{
  uint uVar1;
  longlong lVar2;
  longlong lVar3;
  uint uVar4;
  
  (*DAT_140006d30)(DAT_1400070e0,*(undefined8 *)(param_1 + 0x38));
  lVar2 = 0;
  uVar1 = (*DAT_1400063c0)(DAT_1400070e0,*(undefined8 *)(param_1 + 0x18));
  uVar4 = 0;
  if (uVar1 != 0) {
    do {
      lVar2 = (*DAT_1400063e0)(DAT_1400070e0,*(undefined8 *)(param_1 + 0x18),uVar4);
      lVar3 = (*DAT_1400069a0)(DAT_1400070e0,lVar2);
      if (*(longlong *)(lVar3 + 0x20) == param_2) break;
      uVar4 = uVar4 + 1;
    } while (uVar4 < uVar1);
  }
  if ((uVar4 == uVar1) || (lVar2 == 0)) {
    (*DAT_140006d38)(DAT_1400070e0,*(undefined8 *)(param_1 + 0x38));
  }
  else {
    (*DAT_1400063d0)(DAT_1400070e0,*(undefined8 *)(param_1 + 0x18),lVar2);
    (*DAT_140006d38)(DAT_1400070e0,*(undefined8 *)(param_1 + 0x38));
    (*DAT_1400066d8)(DAT_1400070e0,lVar2,1);
    lVar3 = (*DAT_1400069a0)(DAT_1400070e0,lVar2,PTR_DAT_140006128);
    *(undefined8 *)(lVar3 + 0x18) = 0;
    *(undefined8 *)(lVar3 + 0x20) = 0;
    *(undefined4 *)(lVar3 + 0x10) = 4;
    (*DAT_1400069d0)(DAT_1400070e0,lVar2);
  }
  return;
}



void FUN_140003abc(longlong param_1,undefined *param_2,undefined8 param_3)

{
  undefined8 uVar1;
  char cVar2;
  uint uVar3;
  undefined8 *puVar4;
  uint uVar5;
  
  (*DAT_140006d30)(DAT_1400070e0,*(undefined8 *)(param_1 + 0x38));
  uVar3 = (*DAT_1400063c0)(DAT_1400070e0,*(undefined8 *)(param_1 + 0x18));
  uVar5 = 0;
  if (uVar3 != 0) {
    do {
      uVar1 = (*DAT_1400063e0)(DAT_1400070e0,*(undefined8 *)(param_1 + 0x18),uVar5);
      puVar4 = (undefined8 *)(*DAT_1400069a0)(DAT_1400070e0,uVar1);
      (*DAT_140006d30)(DAT_1400070e0,puVar4[1]);
      if (*(int *)(puVar4 + 2) == 1) {
        cVar2 = (*(code *)param_2)(puVar4[4],param_3);
        if (cVar2 == '\0') goto LAB_140003b88;
        *(undefined4 *)(puVar4 + 2) = 2;
        (*DAT_140006d38)(DAT_1400070e0,puVar4[1]);
        (*DAT_1400066d0)(DAT_1400070e0,*puVar4);
      }
      else {
LAB_140003b88:
        (*DAT_140006d38)(DAT_1400070e0,puVar4[1]);
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 < uVar3);
  }
                    // WARNING: Could not recover jumptable at 0x000140003bc6. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_140006d38)(DAT_1400070e0,*(undefined8 *)(param_1 + 0x38));
  return;
}



undefined FUN_140003bd0(longlong param_1)

{
  (*DAT_140006d48)(DAT_1400070e0,*(undefined8 *)(param_1 + 0x30),0xfffffffffe363c80);
  return 1;
}



void FUN_140003bf4(undefined8 param_1)

{
  longlong lVar1;
  
  lVar1 = (*DAT_1400069a0)(DAT_1400070e0,param_1,PTR_DAT_140006128);
  (*DAT_140006d30)(DAT_1400070e0,*(undefined8 *)(lVar1 + 8));
  *(undefined4 *)(lVar1 + 0x10) = 3;
  (*DAT_140006d38)(DAT_1400070e0,*(undefined8 *)(lVar1 + 8));
  (**(code **)(lVar1 + 0x18))(*(undefined8 *)(lVar1 + 0x20));
  (*DAT_140006d30)(DAT_1400070e0,*(undefined8 *)(lVar1 + 8));
  *(undefined4 *)(lVar1 + 0x10) = 1;
                    // WARNING: Could not recover jumptable at 0x000140003c6c. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_140006d38)(DAT_1400070e0,*(undefined8 *)(lVar1 + 8));
  return;
}



// WARNING: Removing unreachable block (ram,0x000140003d5a)
// WARNING: Removing unreachable block (ram,0x000140003cd0)

void FUN_140003c94(int *param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  byte bVar7;
  size_t _MaxCount;
  size_t _MaxCount_00;
  undefined auStack88 [32];
  undefined8 local_38;
  int iStack48;
  int iStack44;
  ulonglong local_18;
  
  local_18 = DAT_140006180 ^ (ulonglong)auStack88;
  if (*param_1 == 0) {
    puVar1 = (undefined4 *)cpuid_basic_info(0);
    local_38._0_4_ = *puVar1;
    uVar3 = puVar1[1];
    uVar4 = puVar1[2];
    uVar5 = puVar1[3];
    local_38._4_4_ = 0;
    iStack48 = 0;
    iStack44 = 0;
    FUN_1400013f0(&local_38,0,0x20);
    _MaxCount = 0xffffffffffffffff;
    _MaxCount_00 = 0xffffffffffffffff;
    do {
      _MaxCount_00 = _MaxCount_00 + 1;
    } while (PTR_s_AuthenticAMD_140006160[_MaxCount_00] != '\0');
    local_38._0_4_ = uVar3;
    local_38._4_4_ = uVar4;
    iStack48 = uVar5;
    iVar6 = strncmp((char *)&local_38,PTR_s_AuthenticAMD_140006160,_MaxCount_00);
    if (iVar6 == 0) {
      *param_1 = 2;
    }
    else {
      do {
        _MaxCount = _MaxCount + 1;
      } while (PTR_s_GenuineIntel_140006168[_MaxCount] != '\0');
      iVar6 = strncmp((char *)&local_38,PTR_s_GenuineIntel_140006168,_MaxCount);
      *param_1 = (-(uint)(iVar6 != 0) & 0xfffffffe) + 1;
    }
    piVar2 = (int *)cpuid_Version_info(1);
    iVar6 = *piVar2;
    local_38._4_4_ = piVar2[1];
    iStack44 = piVar2[2];
    iStack48 = piVar2[3];
    bVar7 = (char)((uint)iVar6 >> 0x10) << 4 | (byte)(iVar6 >> 4) & 0xf;
    if ((*param_1 == 2) &&
       ((byte)(((byte)((uint)iVar6 >> 8) & 0xf) + (char)(iVar6 >> 0x14)) == '\x16')) {
      if (bVar7 < 0x10) {
        *param_1 = 0x10002;
      }
      else {
        iVar6 = *param_1;
        if ((byte)(bVar7 - 0x30) < 0x10) {
          iVar6 = 0x20002;
        }
        *param_1 = iVar6;
      }
    }
  }
  FUN_1400049b0(local_18 ^ (ulonglong)auStack88);
  return;
}



undefined8
FUN_140003ddc(undefined4 *param_1,undefined4 param_2,undefined8 param_3,undefined4 param_4,
             undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  *param_1 = param_2;
  *(undefined8 *)(param_1 + 2) = param_3;
  param_1[5] = param_5;
  param_1[4] = param_4;
  param_1[6] = param_6;
  param_1[7] = param_7;
  return 0;
}



void FUN_140003e00(undefined4 *param_1,undefined4 *param_2,undefined8 *param_3,undefined4 *param_4,
                  undefined4 *param_5,undefined4 *param_6,undefined4 *param_7)

{
  *param_2 = *param_1;
  *param_3 = *(undefined8 *)(param_1 + 2);
  *param_4 = param_1[4];
  *param_5 = param_1[5];
  *param_6 = param_1[6];
  *param_7 = param_1[7];
  *param_1 = 0;
  *(undefined8 *)(param_1 + 2) = 0;
  *(undefined8 *)(param_1 + 4) = 0;
  *(undefined8 *)(param_1 + 6) = 0;
  return;
}



void FUN_140003e48(undefined4 *param_1)

{
  *param_1 = 0;
  *(undefined8 *)(param_1 + 2) = 0;
  *(undefined8 *)(param_1 + 4) = 0;
  *(undefined8 *)(param_1 + 6) = 0;
  return;
}



ulonglong FUN_140003e5c(longlong param_1)

{
  byte bVar1;
  ulonglong uVar2;
  
  uVar2 = FUN_140003c94((int *)(param_1 + 0x20));
  if ((int)uVar2 == 0x10002) {
    out(0xcd6,0x28);
    bVar1 = in(0xcd7);
    out(0xcd6,0x28);
    uVar2 = uVar2 & 0xffffffffffffff00 | (ulonglong)(bVar1 | 1);
    out(0xcd7,bVar1 | 1);
  }
  else {
    uVar2 = FUN_140003c94((int *)(param_1 + 0x20));
    if ((int)uVar2 == 0x20002) {
      out(0xcd6,0);
      bVar1 = in(0xcd7);
      out(0xcd6,0);
      uVar2 = (ulonglong)(bVar1 | 0x10);
      out(0xcd7,bVar1 | 0x10);
    }
  }
  return uVar2;
}



// FUN_140003ed8
uint asf_master_en(longlong param_1)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = FUN_140003c94((int *)(param_1 + 0x20));
  if (iVar2 == 0x10002) {
    out(0xcd6,0x28);
    bVar1 = in(0xcd7);
    out(0xcd6,0x28);
    uVar3 = (bVar1 | 5) | 0x10000;
    out(0xcd7,bVar1 | 5);
  }
  else {
    uVar3 = FUN_140003c94((int *)(param_1 + 0x20));
    if (uVar3 == 0x20002) {
      out(0xcd6,2);
      bVar1 = in(0xcd7);
      out(0xcd6,2);
      uVar3 = (bVar1 | 1) | 0x20000;
      out(0xcd7,bVar1 | 1);
    }
  }
  return uVar3;
}



ulonglong FUN_140003f54(longlong param_1)

{
  byte bVar1;
  undefined2 *puVar2;
  ulonglong uVar3;
  longlong lVar4;
  
  puVar2 = (undefined2 *)(param_1 + 0xc2);
  *(undefined4 *)(param_1 + 0x78) = 0;
  *(undefined4 *)(param_1 + 0x7c) = 0;
  *(undefined4 *)(param_1 + 0x80) = 0;
  *(undefined4 *)(param_1 + 0x84) = 0;
  *(undefined4 *)(param_1 + 0x88) = 0;
  *(undefined4 *)(param_1 + 0x8c) = 0;
  *(undefined4 *)(param_1 + 0x90) = 0;
  *(undefined4 *)(param_1 + 0x94) = 0;
  *(undefined4 *)(param_1 + 0x98) = 0;
  *(undefined4 *)(param_1 + 0x9c) = 0;
  *(undefined4 *)(param_1 + 0xa0) = 0;
  *(undefined4 *)(param_1 + 0xa4) = 0;
  *(undefined4 *)(param_1 + 0xa8) = 0;
  *(undefined4 *)(param_1 + 0xac) = 0;
  *(undefined8 *)(param_1 + 0xb0) = 0;
  *(undefined8 *)(param_1 + 0xb8) = 0;
  lVar4 = 2;
  do {
    *(undefined *)(puVar2 + -1) = 0xff;
    *puVar2 = 0;
    puVar2 = puVar2 + 2;
    lVar4 = lVar4 + -1;
  } while (lVar4 != 0);
  uVar3 = FUN_140003e5c(param_1);
  bVar1 = in((short)*(undefined4 *)(param_1 + 0x14) + 0x15);
  uVar3 = uVar3 & 0xffffffffffffff00;
  uVar3 = CONCAT71((int7)(uVar3 >> 8),0x10);
  out((short)*(undefined4 *)(param_1 + 0x14) + 9,0x10);
  uVar3 = uVar3 & 0xffffffffffffff00 | (ulonglong)bVar1 | 0x12;
  out((short)*(undefined4 *)(param_1 + 0x14) + 0x15,(char)uVar3);
  bVar1 = in((short)*(undefined4 *)(param_1 + 0x14) + 0x13);
  uVar3 = uVar3 & 0xffffffffffffff00;
  uVar3 = uVar3 & 0xffffffffffffff00;
  out((short)*(undefined4 *)(param_1 + 0x14) + 0x13,bVar1 & 0xc);
  bVar1 = in((short)*(undefined4 *)(param_1 + 0x14) + 0x15);
  uVar3 = uVar3 & 0xffffffffffffff00;
  uVar3 = uVar3 & 0xffffffffffffff00 | (ulonglong)bVar1 & 0xffffffffffffffef | 2;
  out((short)*(undefined4 *)(param_1 + 0x14) + 0x15,(char)uVar3);
  return uVar3;
}



// Interrupt handler?
ulonglong FUN_1400040c4(longlong param_1,char param_2)

{
  ulonglong uVar1;
  
  if (param_2 == '\0') {
    uVar1 = FUN_1400044c4(param_1);
    if ((char)uVar1 == '\0') goto LAB_14000410c;
  }
  else {
    uVar1 = FUN_1400044c4(param_1);
    if ((char)uVar1 == '\0') {
      *(int *)(param_1 + 0xa4) = *(int *)(param_1 + 0xa4) + 1;
LAB_14000410c:
      *(undefined4 *)(param_1 + 0x70) = 2;
      return CONCAT71((int7)(uVar1 >> 8),1);
    }
    *(int *)(param_1 + 0xa8) = *(int *)(param_1 + 0xa8) + 1;
    uVar1 = (ulonglong)*(uint *)(param_1 + 0xac);
    *(uint *)(param_1 + 0xac) = (int)*(undefined8 *)(param_1 + 0xb8) + 1 + *(uint *)(param_1 + 0xac)
    ;
  }
  return uVar1 & 0xffffffffffffff00;
}



char FUN_14000411c(longlong param_1)

{
  char cVar1;
  bool bVar2;
  char cVar3;
  byte bVar4;
  undefined uVar5;
  undefined uVar6;
  int iVar7;
  ulonglong uVar8;
  byte bus_collision;
  char cVar10;
  byte bVar11;
  longlong lVar12;
  
  lVar12 = 0;
  *(int *)(param_1 + 0x78) = *(int *)(param_1 + 0x78) + 1;
  cVar3 = '\0';
  bVar2 = false;
  bVar4 = in((short)*(undefined4 *)(param_1 + 0x14));
  cVar10 = '\x03';
  if ((bVar4 & 0x1e) == 0) goto LAB_14000439d;
  *(int *)(param_1 + 0x88) = *(int *)(param_1 + 0x88) + 1;
  cVar3 = '\x01';
  bVar11 = 0;
  bus_collision = bVar4 >> 3 & 1;
  // no bus collisin, no pec error, no dev error
  if (((bus_collision == 0) && ((bVar4 & 0x10) == 0)) && ((bVar4 & 4) == 0)) {
    bVar2 = false;
    if ((bVar4 & 2) != 0) {
      bVar2 = false;
      if (*(int *)(param_1 + 0x28) == 2) {
        out((short)*(undefined4 *)(param_1 + 0x14) + 0x13,0x80);
        cVar1 = *(char *)(param_1 + 0x48);
        if (cVar1 == '\x01') {
          uVar5 = in((short)*(undefined4 *)(param_1 + 0x14) + 5);
          **(undefined **)(param_1 + 0x50) = 1;
          **(undefined **)(param_1 + 0x58) = uVar5;
LAB_1400042f5:
          *(int *)(param_1 + 0x84) = *(int *)(param_1 + 0x84) + 1;
          **(undefined **)(param_1 + 0x60) = 0;
        }
        else {
          if (cVar1 == '\x02') {
            uVar5 = in((short)*(undefined4 *)(param_1 + 0x14) + 5);
            uVar6 = in((short)*(undefined4 *)(param_1 + 0x14) + 6);
            **(undefined **)(param_1 + 0x50) = 2;
            **(undefined **)(param_1 + 0x58) = uVar5;
            *(undefined *)(*(longlong *)(param_1 + 0x58) + 1) = uVar6;
            goto LAB_1400042f5;
          }
          if (cVar1 != ' ') {
            **(undefined **)(param_1 + 0x50) = 0;
            goto LAB_1400042f5;
          }
          bVar4 = in((short)*(undefined4 *)(param_1 + 0x14) + 5);
          if ((byte)(bVar4 - 1) < 0x20) {
            **(byte **)(param_1 + 0x50) = bVar4;
            in((short)*(undefined4 *)(param_1 + 0x14) + 2);
            if (bVar4 != 0) {
              uVar8 = (ulonglong)bVar4;
              do {
                uVar5 = in((short)*(undefined4 *)(param_1 + 0x14) + 7);
                *(undefined *)(*(longlong *)(param_1 + 0x58) + lVar12) = uVar5;
                lVar12 = lVar12 + 1;
                uVar8 = uVar8 - 1;
              } while (uVar8 != 0);
            }
            goto LAB_1400042f5;
          }
          *(int *)(param_1 + 0x80) = *(int *)(param_1 + 0x80) + 1;
          **(undefined **)(param_1 + 0x60) = 0x13;
        }
        *(undefined4 *)(param_1 + 0x28) = 3;
        bVar2 = true;
      }
      bVar11 = 2;
    }
  }
  else {
    bVar2 = false;
    if (*(int *)(param_1 + 0x28) == 2) {
      *(int *)(param_1 + 0x80) = *(int *)(param_1 + 0x80) + 1;
      if (bus_collision == 0) {
        **(undefined **)(param_1 + 0x60) = 0x11;
      }
      else {
        **(undefined **)(param_1 + 0x60) = 0x1a;
      }
      *(undefined4 *)(param_1 + 0x28) = 3;
      bVar2 = true;
    }
    if (bus_collision != 0) {
      bVar11 = 8;
    }
    if ((bVar4 & 0x10) != 0) {
      bVar11 = bVar11 | 0x10;
    }
    if ((bVar4 & 4) != 0) {
      bVar11 = bVar11 | 4;
    }
    if ((bVar4 & 2) != 0) {
      bVar11 = bVar11 | 2;
    }
  }
  out((short)*(undefined4 *)(param_1 + 0x14),bVar11);
  iVar7 = FUN_140003c94((int *)(param_1 + 0x20));
  if ((iVar7 == 0x10002) || (iVar7 = FUN_140003c94((int *)(param_1 + 0x20)), iVar7 == 0x20002)) {
    asf_master_dis(param_1);
  }
LAB_14000439d:
  if (*(int *)(param_1 + 0x70) - 2U < 3) {
    bVar4 = in((short)*(undefined4 *)(param_1 + 0x14) + 10);
    if ((char)bVar4 < '\0') {
      iVar7 = FUN_140003c94((int *)(param_1 + 0x20));
      if ((iVar7 == 0x10002) || (iVar7 = FUN_140003c94((int *)(param_1 + 0x20)), iVar7 == 0x20002))
      {
        kill_slave(param_1);
        enable_slave(param_1);
      }
    }
    else if ((bVar4 & 0x40) != 0) {
      *(int *)(param_1 + 0x8c) = *(int *)(param_1 + 0x8c) + 1;
      cVar3 = '\x01';
      out((short)*(undefined4 *)(param_1 + 0x14) + 10,0x40);
      bVar4 = in((short)*(undefined4 *)(param_1 + 0x14) + 0x15);
      if ((bVar4 & 0x10) == 0) {
        if (*(int *)(param_1 + 0x70) - 3U < 2) {
          *(int *)(param_1 + 0x94) = *(int *)(param_1 + 0x94) + 1;
        }
        else {
          uVar8 = FUN_1400044c4(param_1);
          if ((char)uVar8 != '\0') {
            *(int *)(param_1 + 0x9c) = *(int *)(param_1 + 0x9c) + 1;
            *(undefined4 *)(param_1 + 0x70) = 3;
            return '\x03';
          }
          *(int *)(param_1 + 0x98) = *(int *)(param_1 + 0x98) + 1;
        }
      }
      else {
        *(int *)(param_1 + 0x90) = *(int *)(param_1 + 0x90) + 1;
      }
    }
  }
  if (!bVar2) {
    cVar10 = cVar3 + '\x01';
  }
  return cVar10;
}


/*

0 00x0       ret0
1 00x1       ret0
4 01x0    00 ret0
5 01x1       ret0
8 10x0       ret0
9 10x1    10 ret1
c 11x0 10 01 ret1
d 11x1 00 11 ret1

*/


ulonglong FUN_1400044c4(longlong param_1)

{
  byte bVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  longlong lVar4;
  longlong lVar6;
  
  bVar1 = in((short)*(undefined4 *)(param_1 + 0x14) + 0x13);
  bVar1 = bVar1 & 0xd;
  uVar2 = 0;
  if (bVar1 < 2) {
LAB_1400045d8:
    return uVar2 & 0xffffffffffffff00;
  }
  if (bVar1 == 4) {
    *(undefined8 *)(param_1 + 0xb0) = 0;
    lVar6 = 0;
  }
  else {
    if (bVar1 == 9) {
      *(undefined8 *)(param_1 + 0xb0) = 0;
      lVar6 = 0;
      lVar4 = 1;
      goto LAB_14000458b;
    }
    if (bVar1 != 0xc) {
      if (bVar1 != 0xd) {
        out((ulonglong)*(uint *)(param_1 + 0x14) + 0x13,bVar1 & 0xc);
        return 0;
      }
      *(undefined8 *)(param_1 + 0xb0) = 0;
      read_notify_address(param_1,0,0);
      lVar6 = 1;
      lVar4 = 1;
      goto LAB_14000458b;
    }
    *(undefined8 *)(param_1 + 0xb0) = 0;
    read_notify_address(param_1,1,0);
    lVar6 = 1;
  }
  lVar4 = 0;
LAB_14000458b:
  uVar2 = read_notify_address(param_1,lVar4,lVar6);
  uVar2 = uVar2 & 0xffffffffffffff00;
  out((short)*(undefined4 *)(param_1 + 0x14) + 0x13,bVar1 & 0xc);
  return uVar2 & 0xffffffffffffff00 | 1;
}



// FUN_1400045ec
void read_notify_address(longlong param_1,longlong param_2,longlong param_3)

{
  byte bVar1;
  undefined uVar2;
  undefined uVar3;
  
  *(int *)(param_1 + 0xa0) = *(int *)(param_1 + 0xa0) + 1;
  out((short)*(undefined4 *)(param_1 + 0x14) + 0x13,(&DAT_1400051d0)[param_2]);
  in((short)*(undefined4 *)(param_1 + 0x14) + 2);
  in((short)*(undefined4 *)(param_1 + 0x14) + 7);
  bVar1 = in((short)*(undefined4 *)(param_1 + 0x14) + 7);
  uVar2 = in((short)*(undefined4 *)(param_1 + 0x14) + 7);
  uVar3 = in((short)*(undefined4 *)(param_1 + 0x14) + 7);
  *(byte *)(param_1 + 0xc0 + param_3 * 4) = bVar1 >> 1;
  *(ushort *)(param_1 + 0xc2 + param_3 * 4) = CONCAT11(uVar3,uVar2);
  *(longlong *)(param_1 + 0xb8) = param_3;
  return;
}



// FUN_1400046d4
undefined8 transfer(longlong param_1)

{
  int *piVar1;
  undefined uVar2;
  char cVar3;
  int iVar4;
  uint uVar5;
  ulonglong uVar6;
  undefined4 extraout_var;
  undefined *puVar7;
  undefined4 extraout_var_00;
  undefined uVar8;
  byte bVar9;
  
  iVar4 = *(int *)(param_1 + 0x30);
  if (iVar4 != 2) {
    if (iVar4 == 3) {
      uVar8 = 0x48;
      goto LAB_14000473f;
    }
    if (iVar4 == 4) {
      uVar8 = 0x4c;
      goto LAB_14000473f;
    }
    if (iVar4 == 5) {
      uVar8 = 0x50;
      goto LAB_14000473f;
    }
    if (iVar4 == 6) {
      uVar8 = 0x54;
      goto LAB_14000473f;
    }
    if (iVar4 == 7) {
      uVar8 = 0x58;
      goto LAB_14000473f;
    }
LAB_140004710:
    puVar7 = *(undefined **)(param_1 + 0x60);
    *puVar7 = 7;
    *(undefined4 *)(param_1 + 0x28) = 3;
    goto LAB_140004976;
  }
  uVar8 = 0x44;
LAB_14000473f:
  bVar9 = *(char *)(param_1 + 0x3c) * '\x02';
  if (*(int *)(param_1 + 0x34) != 1) {
    if (*(int *)(param_1 + 0x34) != 2) goto LAB_140004710;
    bVar9 = bVar9 | 1;
  }
  *(int *)(param_1 + 0x7c) = *(int *)(param_1 + 0x7c) + 1;
  piVar1 = (int *)(param_1 + 0x20);
  iVar4 = FUN_140003c94(piVar1);
  if ((iVar4 == 0x10002) || (iVar4 = FUN_140003c94(piVar1), iVar4 == 0x20002)) {
    asf_master_en(param_1);
  }
  out((short)*(undefined4 *)(param_1 + 0x14) + 0x13,0x80);
  out((short)*(undefined4 *)(param_1 + 0x14) + 4,bVar9);
  out((short)*(undefined4 *)(param_1 + 0x14) + 3,*(undefined *)(param_1 + 0x3d));
  iVar4 = *(int *)(param_1 + 0x30);
  if (1 < iVar4) {
    if (iVar4 < 6) {
      cVar3 = *(char *)(param_1 + 0x3e);
      if (cVar3 == '\0') goto LAB_140004900;
      if (cVar3 != '\x01') {
        if (cVar3 != '\x02') goto LAB_140004946;
        uVar2 = *(undefined *)(*(longlong *)(param_1 + 0x40) + 1);
        out((short)*(undefined4 *)(param_1 + 0x14) + 6,uVar2);
      }
      out((short)*(undefined4 *)(param_1 + 0x14) + 5,**(undefined **)(param_1 + 0x40));
LAB_140004900:
      iVar4 = FUN_140003c94(piVar1);
      if ((iVar4 == 0x10002) || (uVar6 = FUN_140003c94(piVar1), (int)uVar6 == 0x20002)) {
        uVar5 = asf_master_en(param_1);
        uVar6 = CONCAT44(extraout_var,uVar5);
      }
      uVar6 = uVar6 & 0xffffffffffffff00;
      out((short)*(undefined4 *)(param_1 + 0x14) + 2,uVar8);
      return uVar6 & 0xffffffffffffff00;
    }
    if (iVar4 < 8) {
      in((short)*(undefined4 *)(param_1 + 0x14) + 2);
      if (*(char *)(param_1 + 0x3e) != '\0') {
        out((short)*(undefined4 *)(param_1 + 0x14) + 5,*(undefined *)(param_1 + 0x3e));
        bVar9 = 0;
        if (*(char *)(param_1 + 0x3e) != '\0') {
          do {
            uVar2 = *(undefined *)(*(longlong *)(param_1 + 0x40) + (ulonglong)bVar9);
            out((short)*(undefined4 *)(param_1 + 0x14) + 7,uVar2);
            bVar9 = bVar9 + 1;
          } while (bVar9 < *(byte *)(param_1 + 0x3e));
        }
      }
      goto LAB_140004900;
    }
  }
LAB_140004946:
  **(undefined **)(param_1 + 0x60) = 7;
  *(undefined4 *)(param_1 + 0x28) = 3;
  iVar4 = FUN_140003c94(piVar1);
  if ((iVar4 == 0x10002) || (puVar7 = (undefined *)FUN_140003c94(piVar1), (int)puVar7 == 0x20002)) {
    uVar5 = asf_master_dis(param_1);
    puVar7 = (undefined *)CONCAT44(extraout_var_00,uVar5);
  }
LAB_140004976:
  return CONCAT71((int7)((ulonglong)puVar7 >> 8),1);
}



void FUN_1400049b0(longlong param_1)

{
  code *pcVar1;
  
  if ((param_1 == DAT_140006180) && ((short)((ulonglong)param_1 >> 0x30) == 0)) {
    return;
  }
  KeBugCheckEx(0xf7,param_1,DAT_140006180,DAT_140006188,0);
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}



int strncmp(char *_Str1,char *_Str2,size_t _MaxCount)

{
  int iVar1;
  
                    // WARNING: Could not recover jumptable at 0x0001400049f8. Too many branches
                    // WARNING: Treating indirect jump as call
  iVar1 = strncmp(_Str1,_Str2,_MaxCount);
  return iVar1;
}



void FUN_140004a00(void)

{
  FxStubUnbindClasses((_WDF_BIND_INFO *)&DAT_140006190);
                    // WARNING: Could not recover jumptable at 0x000140004d2e. Too many branches
                    // WARNING: Treating indirect jump as call
  WdfVersionUnbind(&DAT_140007308,&DAT_140006190,DAT_1400070e0);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

ulonglong entry(longlong param_1,undefined8 param_2)

{
  uint uVar1;
  ulonglong uVar2;
  undefined8 uVar3;
  undefined8 unaff_RDI;
  
  FUN_14000a000();
  if (param_1 == 0) {
    uVar2 = thunk_FUN_1400027b0(0,param_2);
  }
  else {
    _DAT_140007310 = &DAT_140007100;
    _DAT_140007308 = 0x2080000;
    _DAT_1400070e8 = param_1;
    RtlCopyUnicodeString(&DAT_140007308);
    uVar2 = WdfVersionBind(param_1,&DAT_140007308,&DAT_140006190,&DAT_1400070e0,unaff_RDI);
    if (-1 < (int)uVar2) {
      uVar1 = FxStubBindClasses((_WDF_BIND_INFO *)&DAT_140006190);
      if ((-1 < (int)uVar1) && (uVar1 = FxStubInitTypes(), -1 < (int)uVar1)) {
        uVar3 = thunk_FUN_1400027b0(param_1,param_2);
        uVar1 = (uint)uVar3;
        if (-1 < (int)uVar1) {
          if (*(char *)(DAT_1400070e0 + 0x30) == '\0') {
            if ((*(uint *)(DAT_1400070e0 + 8) & 2) != 0) {
              _DAT_1400070f0 = DAT_140006998;
              DAT_140006998 = &LAB_140004b7c;
            }
          }
          else {
            if (*(longlong *)(param_1 + 0x68) != 0) {
              DAT_1400070d8 = *(longlong *)(param_1 + 0x68);
            }
            *(code **)(param_1 + 0x68) = FUN_140004b84;
          }
          return 0;
        }
      }
      FUN_140004a00();
      uVar2 = (ulonglong)uVar1;
    }
  }
  return uVar2;
}



void FUN_140004b84(void)

{
  if ((DAT_1400070d8 != (code *)0x0) && (DAT_1400070d8 != FUN_140004b84)) {
    (*DAT_1400070d8)();
  }
  FUN_140004a00();
  return;
}



// WARNING: Removing unreachable block (ram,0x000140004bdc)
// WARNING: Removing unreachable block (ram,0x000140004be3)
// WARNING: Removing unreachable block (ram,0x000140004c11)
// WARNING: Removing unreachable block (ram,0x000140004be9)
// WARNING: Removing unreachable block (ram,0x000140004bf1)
// WARNING: Removing unreachable block (ram,0x000140004bf7)
// WARNING: Removing unreachable block (ram,0x000140004bc9)
// WARNING: Unknown calling convention yet parameter storage is locked
// Library Function - Single Match
//  long __cdecl FxStubInitTypes(void)
// 
// Library: Visual Studio 2019 Release

long FxStubInitTypes(void)

{
  return 0;
}



// WARNING: Removing unreachable block (ram,0x000140004c3f)
// Library Function - Single Match
//  long __cdecl FxStubBindClasses(struct _WDF_BIND_INFO * __ptr64)
// 
// Library: Visual Studio 2019 Release

long FxStubBindClasses(_WDF_BIND_INFO *param_1)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  piVar2 = &DAT_1400061d0;
  while( true ) {
    if ((int *)0x1400061cf < piVar2) {
      return iVar1;
    }
    if (*piVar2 != 0x50) break;
    PTR_DAT_1400061d8 = (undefined *)piVar2;
    if (*(code **)(piVar2 + 0xe) == (code *)0x0) {
      iVar1 = WdfVersionBindClass(param_1,DAT_1400070e0,piVar2);
    }
    else {
      iVar1 = (**(code **)(piVar2 + 0xe))(WdfVersionBindClass,param_1,DAT_1400070e0,piVar2);
    }
    if (iVar1 < 0) {
      return iVar1;
    }
    piVar2 = piVar2 + 0x14;
  }
  return -0x3ffffffc;
}



// Library Function - Single Match
//  void __cdecl FxStubUnbindClasses(struct _WDF_BIND_INFO * __ptr64)
// 
// Library: Visual Studio 2019 Release

void FxStubUnbindClasses(_WDF_BIND_INFO *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = &DAT_1400061d0;
  if ((PTR_DAT_1400061d8 != &DAT_1400061c0) && ((undefined *)0x1400061cf < PTR_DAT_1400061d8)) {
    do {
      if (*(code **)(puVar1 + 0x10) == (code *)0x0) {
        WdfVersionUnbindClass(param_1,DAT_1400070e0,puVar1);
      }
      else {
        (**(code **)(puVar1 + 0x10))(WdfVersionUnbindClass,param_1,DAT_1400070e0,puVar1);
      }
      puVar1 = puVar1 + 0x14;
    } while (puVar1 <= PTR_DAT_1400061d8);
  }
  return;
}



void WdfVersionBind(void)

{
                    // WARNING: Could not recover jumptable at 0x000140004d28. Too many branches
                    // WARNING: Treating indirect jump as call
  WdfVersionBind();
  return;
}



void WdfVersionBindClass(void)

{
                    // WARNING: Could not recover jumptable at 0x000140004d34. Too many branches
                    // WARNING: Treating indirect jump as call
  WdfVersionBindClass();
  return;
}



void WdfVersionUnbindClass(void)

{
                    // WARNING: Could not recover jumptable at 0x000140004d3a. Too many branches
                    // WARNING: Treating indirect jump as call
  WdfVersionUnbindClass();
  return;
}



void _guard_check_icall(void)

{
  return;
}



void FUN_14000a000(void)

{
  ulonglong uVar1;
  
  if ((DAT_140006180 == 0) || (DAT_140006180 == 0x2b992ddfa232)) {
    uVar1 = rdtsc();
    DAT_140006180 =
         ((DAT_140006180 & 0xffffffff00000000 | uVar1 & 0xffffffff | uVar1 & 0xffffffff00000000) ^
         0x140006180) & 0xffffffffffff;
    if (DAT_140006180 == 0) {
      DAT_140006180 = 0x2b992ddfa232;
    }
  }
  DAT_140006188 = ~DAT_140006180;
  return;
}



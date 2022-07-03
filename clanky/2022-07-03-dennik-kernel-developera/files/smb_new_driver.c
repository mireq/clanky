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
typedef struct _IMAGE_RUNTIME_FUNCTION_ENTRY _IMAGE_RUNTIME_FUNCTION_ENTRY, *P_IMAGE_RUNTIME_FUNCTION_ENTRY;

struct _IMAGE_RUNTIME_FUNCTION_ENTRY {
    ImageBaseOffset32 BeginAddress;
    ImageBaseOffset32 EndAddress;
    ImageBaseOffset32 UnwindInfoAddressOrData;
};

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

typedef unsigned short    wchar16;
typedef struct GuardCfgTableEntry GuardCfgTableEntry, *PGuardCfgTableEntry;

struct GuardCfgTableEntry {
    ImageBaseOffset32 Offset;
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

typedef struct DotNetPdbInfo DotNetPdbInfo, *PDotNetPdbInfo;

struct DotNetPdbInfo {
    char signature[4];
    GUID guid;
    dword age;
    char pdbname[24];
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

typedef struct IMAGE_LOAD_CONFIG_CODE_INTEGRITY IMAGE_LOAD_CONFIG_CODE_INTEGRITY, *PIMAGE_LOAD_CONFIG_CODE_INTEGRITY;

struct IMAGE_LOAD_CONFIG_CODE_INTEGRITY {
    word Flags;
    word Catalog;
    dword CatalogOffset;
    dword Reserved;
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
    struct IMAGE_LOAD_CONFIG_CODE_INTEGRITY CodeIntegrity;
    pointer64 GuardAddressTakenIatEntryTable;
    qword GuardAddressTakenIatEntryCount;
    pointer64 GuardLongJumpTargetTable;
    qword GuardLongJumpTargetCount;
    pointer64 DynamicValueRelocTable;
    pointer64 CHPEMetadataPointer;
    pointer64 GuardRFFailureRoutine;
    pointer64 GuardRFFailureRoutineFunctionPointer;
    dword DynamicValueRelocTableOffset;
    word DynamicValueRelocTableSection;
    word Reserved1;
    pointer64 GuardRFVerifyStackPointerFunctionPointer;
    dword HotPatchTableOffset;
    dword Reserved2;
    qword Reserved3;
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

typedef struct astruct astruct, *Pastruct;

struct astruct {
    undefined field0_0x0;
    undefined field1_0x1;
    undefined field2_0x2;
    undefined field3_0x3;
    undefined field4_0x4;
    undefined field5_0x5;
    undefined field6_0x6;
    undefined field7_0x7;
    undefined field8_0x8;
    undefined field9_0x9;
    undefined field10_0xa;
    undefined field11_0xb;
    undefined field12_0xc;
    undefined field13_0xd;
    undefined field14_0xe;
    undefined field15_0xf;
    undefined field16_0x10;
    undefined field17_0x11;
    undefined field18_0x12;
    undefined field19_0x13;
    undefined field20_0x14;
    undefined field21_0x15;
    undefined field22_0x16;
    undefined field23_0x17;
    undefined field24_0x18;
    undefined field25_0x19;
    undefined field26_0x1a;
    undefined field27_0x1b;
    undefined field28_0x1c;
    undefined field29_0x1d;
    undefined field30_0x1e;
    undefined field31_0x1f;
    undefined field32_0x20;
    undefined field33_0x21;
    undefined field34_0x22;
    undefined field35_0x23;
    undefined field36_0x24;
    undefined field37_0x25;
    undefined field38_0x26;
    undefined field39_0x27;
    undefined field40_0x28;
    undefined field41_0x29;
    undefined field42_0x2a;
    undefined field43_0x2b;
    undefined field44_0x2c;
    undefined field45_0x2d;
    undefined field46_0x2e;
    undefined field47_0x2f;
    undefined field48_0x30;
    undefined field49_0x31;
    undefined field50_0x32;
    undefined field51_0x33;
    undefined field52_0x34;
    undefined field53_0x35;
    undefined field54_0x36;
    undefined field55_0x37;
    undefined field56_0x38;
    undefined field57_0x39;
    undefined field58_0x3a;
    undefined field59_0x3b;
    undefined field60_0x3c;
    undefined field61_0x3d;
    undefined field62_0x3e;
    undefined field63_0x3f;
    undefined field64_0x40;
    undefined field65_0x41;
    undefined field66_0x42;
    undefined field67_0x43;
    undefined field68_0x44;
    undefined field69_0x45;
    undefined field70_0x46;
    undefined field71_0x47;
    undefined field72_0x48;
    undefined field73_0x49;
    undefined field74_0x4a;
    undefined field75_0x4b;
    undefined field76_0x4c;
    undefined field77_0x4d;
    undefined field78_0x4e;
    undefined field79_0x4f;
    undefined field80_0x50;
    undefined field81_0x51;
    undefined field82_0x52;
    undefined field83_0x53;
    undefined field84_0x54;
    undefined field85_0x55;
    undefined field86_0x56;
    undefined field87_0x57;
    undefined field88_0x58;
    undefined field89_0x59;
    undefined field90_0x5a;
    undefined field91_0x5b;
    undefined field92_0x5c;
    undefined field93_0x5d;
    undefined field94_0x5e;
    undefined field95_0x5f;
    undefined field96_0x60;
    undefined field97_0x61;
    undefined field98_0x62;
    undefined field99_0x63;
    undefined field100_0x64;
    undefined field101_0x65;
    undefined field102_0x66;
    undefined field103_0x67;
    ulonglong mmio_addr;
    int use_io;
    undefined4 base_addr;
    undefined field107_0x78;
    undefined field108_0x79;
    undefined field109_0x7a;
    undefined field110_0x7b;
    undefined field111_0x7c;
    undefined field112_0x7d;
    undefined field113_0x7e;
    undefined field114_0x7f;
    int field115_0x80;
    undefined field116_0x84;
    undefined field117_0x85;
    undefined field118_0x86;
    undefined field119_0x87;
    undefined field120_0x88;
    undefined field121_0x89;
    undefined field122_0x8a;
    undefined field123_0x8b;
    undefined field124_0x8c;
    undefined field125_0x8d;
    undefined field126_0x8e;
    undefined field127_0x8f;
    undefined4 field128_0x90;
    undefined field129_0x94;
    undefined field130_0x95;
    undefined field131_0x96;
    undefined field132_0x97;
    int field133_0x98;
    int field134_0x9c;
    undefined field135_0xa0;
    undefined field136_0xa1;
    undefined field137_0xa2;
    undefined field138_0xa3;
    char field139_0xa4;
    undefined field140_0xa5;
    byte field141_0xa6;
    undefined field142_0xa7;
    undefined * field143_0xa8;
    undefined field144_0xb0;
    undefined field145_0xb1;
    undefined field146_0xb2;
    undefined field147_0xb3;
    undefined field148_0xb4;
    undefined field149_0xb5;
    undefined field150_0xb6;
    undefined field151_0xb7;
    undefined field152_0xb8;
    undefined field153_0xb9;
    undefined field154_0xba;
    undefined field155_0xbb;
    undefined field156_0xbc;
    undefined field157_0xbd;
    undefined field158_0xbe;
    undefined field159_0xbf;
    undefined field160_0xc0;
    undefined field161_0xc1;
    undefined field162_0xc2;
    undefined field163_0xc3;
    undefined field164_0xc4;
    undefined field165_0xc5;
    undefined field166_0xc6;
    undefined field167_0xc7;
    undefined * field168_0xc8;
    undefined field169_0xd0;
    undefined field170_0xd1;
    undefined field171_0xd2;
    undefined field172_0xd3;
    undefined field173_0xd4;
    undefined field174_0xd5;
    undefined field175_0xd6;
    undefined field176_0xd7;
    undefined field177_0xd8;
    undefined field178_0xd9;
    undefined field179_0xda;
    undefined field180_0xdb;
    undefined field181_0xdc;
    undefined field182_0xdd;
    undefined field183_0xde;
    undefined field184_0xdf;
    undefined field185_0xe0;
    undefined field186_0xe1;
    undefined field187_0xe2;
    undefined field188_0xe3;
    int field189_0xe4;
};

typedef struct astruct_10 astruct_10, *Pastruct_10;

struct astruct_10 {
    undefined field0_0x0;
    undefined field1_0x1;
    undefined field2_0x2;
    undefined field3_0x3;
    undefined field4_0x4;
    undefined field5_0x5;
    undefined field6_0x6;
    undefined field7_0x7;
    ulonglong mmio_addr;
    int use_mmio;
    undefined4 base_addr;
    undefined field11_0x18;
    undefined field12_0x19;
    undefined field13_0x1a;
    undefined field14_0x1b;
    undefined field15_0x1c;
    undefined field16_0x1d;
    undefined field17_0x1e;
    undefined field18_0x1f;
    undefined field19_0x20;
    undefined field20_0x21;
    undefined field21_0x22;
    undefined field22_0x23;
    undefined field23_0x24;
    undefined field24_0x25;
    undefined field25_0x26;
    undefined field26_0x27;
    undefined field27_0x28;
    undefined field28_0x29;
    undefined field29_0x2a;
    undefined field30_0x2b;
    undefined field31_0x2c;
    undefined field32_0x2d;
    undefined field33_0x2e;
    undefined field34_0x2f;
    undefined field35_0x30;
    undefined field36_0x31;
    undefined field37_0x32;
    undefined field38_0x33;
    undefined field39_0x34;
    undefined field40_0x35;
    undefined field41_0x36;
    undefined field42_0x37;
    undefined field43_0x38;
    undefined field44_0x39;
    undefined field45_0x3a;
    undefined field46_0x3b;
    undefined field47_0x3c;
    undefined field48_0x3d;
    undefined field49_0x3e;
    undefined field50_0x3f;
    undefined field51_0x40;
    undefined field52_0x41;
    undefined field53_0x42;
    undefined field54_0x43;
    undefined field55_0x44;
    undefined field56_0x45;
    undefined field57_0x46;
    undefined field58_0x47;
    undefined field59_0x48;
    undefined field60_0x49;
    undefined field61_0x4a;
    undefined field62_0x4b;
    undefined field63_0x4c;
    undefined field64_0x4d;
    undefined field65_0x4e;
    undefined field66_0x4f;
    undefined field67_0x50;
    undefined field68_0x51;
    undefined field69_0x52;
    undefined field70_0x53;
    undefined field71_0x54;
    undefined field72_0x55;
    undefined field73_0x56;
    undefined field74_0x57;
    undefined field75_0x58;
    undefined field76_0x59;
    undefined field77_0x5a;
    undefined field78_0x5b;
    undefined field79_0x5c;
    undefined field80_0x5d;
    undefined field81_0x5e;
    undefined field82_0x5f;
    undefined field83_0x60;
    undefined field84_0x61;
    undefined field85_0x62;
    undefined field86_0x63;
    undefined field87_0x64;
    undefined field88_0x65;
    undefined field89_0x66;
    undefined field90_0x67;
    undefined field91_0x68;
    undefined field92_0x69;
    undefined field93_0x6a;
    undefined field94_0x6b;
    undefined field95_0x6c;
    undefined field96_0x6d;
    undefined field97_0x6e;
    undefined field98_0x6f;
    undefined field99_0x70;
    undefined field100_0x71;
    undefined field101_0x72;
    undefined field102_0x73;
    undefined field103_0x74;
    undefined field104_0x75;
    undefined field105_0x76;
    undefined field106_0x77;
    undefined field107_0x78;
    undefined field108_0x79;
    undefined field109_0x7a;
    undefined field110_0x7b;
    undefined field111_0x7c;
    undefined field112_0x7d;
    undefined field113_0x7e;
    undefined field114_0x7f;
    undefined field115_0x80;
    undefined field116_0x81;
    undefined field117_0x82;
    undefined field118_0x83;
    undefined field119_0x84;
    undefined field120_0x85;
    undefined field121_0x86;
    undefined field122_0x87;
    undefined field123_0x88;
    undefined field124_0x89;
    undefined field125_0x8a;
    undefined field126_0x8b;
    undefined field127_0x8c;
    undefined field128_0x8d;
    undefined field129_0x8e;
    undefined field130_0x8f;
    undefined field131_0x90;
    undefined field132_0x91;
    undefined field133_0x92;
    undefined field134_0x93;
    undefined field135_0x94;
    undefined field136_0x95;
    undefined field137_0x96;
    undefined field138_0x97;
    undefined field139_0x98;
    undefined field140_0x99;
    undefined field141_0x9a;
    undefined field142_0x9b;
    undefined field143_0x9c;
    undefined field144_0x9d;
    undefined field145_0x9e;
    undefined field146_0x9f;
    undefined field147_0xa0;
    undefined field148_0xa1;
    undefined field149_0xa2;
    undefined field150_0xa3;
    undefined field151_0xa4;
    undefined field152_0xa5;
    undefined field153_0xa6;
    undefined field154_0xa7;
    int field155_0xa8;
    undefined field156_0xac;
    undefined field157_0xad;
    undefined field158_0xae;
    undefined field159_0xaf;
    undefined field160_0xb0;
    undefined field161_0xb1;
    undefined field162_0xb2;
    undefined field163_0xb3;
    undefined field164_0xb4;
    undefined field165_0xb5;
    undefined field166_0xb6;
    undefined field167_0xb7;
    undefined8 field168_0xb8;
    longlong field169_0xc0;
    undefined field170_0xc8;
    undefined field171_0xc9;
};

typedef struct astruct_3 astruct_3, *Pastruct_3;

struct astruct_3 {
    undefined field0_0x0;
    undefined field1_0x1;
    undefined field2_0x2;
    undefined field3_0x3;
    undefined field4_0x4;
    undefined field5_0x5;
    undefined field6_0x6;
    undefined field7_0x7;
    undefined field8_0x8;
    undefined field9_0x9;
    undefined field10_0xa;
    undefined field11_0xb;
    undefined field12_0xc;
    undefined field13_0xd;
    undefined field14_0xe;
    undefined field15_0xf;
    undefined field16_0x10;
    undefined field17_0x11;
    undefined field18_0x12;
    undefined field19_0x13;
    undefined field20_0x14;
    undefined field21_0x15;
    undefined field22_0x16;
    undefined field23_0x17;
    undefined field24_0x18;
    undefined field25_0x19;
    undefined field26_0x1a;
    undefined field27_0x1b;
    undefined field28_0x1c;
    undefined field29_0x1d;
    undefined field30_0x1e;
    undefined field31_0x1f;
    longlong field32_0x20;
    undefined field33_0x28;
    undefined field34_0x29;
    undefined field35_0x2a;
    undefined field36_0x2b;
    undefined field37_0x2c;
    undefined field38_0x2d;
    undefined field39_0x2e;
    undefined field40_0x2f;
    undefined field41_0x30;
    undefined field42_0x31;
    undefined field43_0x32;
    undefined field44_0x33;
    undefined field45_0x34;
    undefined field46_0x35;
    undefined field47_0x36;
    undefined field48_0x37;
    undefined field49_0x38;
    undefined field50_0x39;
    undefined field51_0x3a;
    undefined field52_0x3b;
    undefined field53_0x3c;
    undefined field54_0x3d;
    undefined field55_0x3e;
    undefined field56_0x3f;
    undefined field57_0x40;
    undefined field58_0x41;
    undefined field59_0x42;
    undefined field60_0x43;
    undefined field61_0x44;
    undefined field62_0x45;
    undefined field63_0x46;
    undefined field64_0x47;
    undefined field65_0x48;
    undefined field66_0x49;
    undefined field67_0x4a;
    undefined field68_0x4b;
    undefined field69_0x4c;
    undefined field70_0x4d;
    undefined field71_0x4e;
    undefined field72_0x4f;
    undefined field73_0x50;
    undefined field74_0x51;
    undefined field75_0x52;
    undefined field76_0x53;
    undefined field77_0x54;
    undefined field78_0x55;
    undefined field79_0x56;
    undefined field80_0x57;
    undefined field81_0x58;
    undefined field82_0x59;
    undefined field83_0x5a;
    undefined field84_0x5b;
    undefined field85_0x5c;
    undefined field86_0x5d;
    undefined field87_0x5e;
    undefined field88_0x5f;
    undefined field89_0x60;
    undefined field90_0x61;
    undefined field91_0x62;
    undefined field92_0x63;
    undefined field93_0x64;
    undefined field94_0x65;
    undefined field95_0x66;
    undefined field96_0x67;
    longlong mmio_addr;
    int use_mmio;
    undefined4 base_addr;
    undefined field100_0x78;
    undefined field101_0x79;
    undefined field102_0x7a;
    undefined field103_0x7b;
    undefined field104_0x7c;
    undefined field105_0x7d;
    undefined field106_0x7e;
    undefined field107_0x7f;
    undefined field108_0x80;
    undefined field109_0x81;
    undefined field110_0x82;
    undefined field111_0x83;
    undefined field112_0x84;
    undefined field113_0x85;
    undefined field114_0x86;
    undefined field115_0x87;
    undefined field116_0x88;
    undefined field117_0x89;
    undefined field118_0x8a;
    undefined field119_0x8b;
    undefined field120_0x8c;
    undefined field121_0x8d;
    undefined field122_0x8e;
    undefined field123_0x8f;
    undefined4 field124_0x90;
    undefined field125_0x94;
    undefined field126_0x95;
    undefined field127_0x96;
    undefined field128_0x97;
    int field129_0x98;
    int field130_0x9c;
    undefined4 field131_0xa0;
    undefined field132_0xa4;
    undefined field133_0xa5;
    undefined field134_0xa6;
    undefined field135_0xa7;
    undefined8 field136_0xa8;
    undefined field137_0xb0;
    undefined field138_0xb1;
    undefined field139_0xb2;
    undefined field140_0xb3;
    undefined field141_0xb4;
    undefined field142_0xb5;
    undefined field143_0xb6;
    undefined field144_0xb7;
    undefined8 field145_0xb8;
    undefined8 field146_0xc0;
    undefined * field147_0xc8;
    undefined4 field148_0xd0;
};

typedef struct astruct_5 astruct_5, *Pastruct_5;

struct astruct_5 {
    undefined field0_0x0;
    undefined field1_0x1;
    undefined field2_0x2;
    undefined field3_0x3;
    undefined field4_0x4;
    undefined field5_0x5;
    undefined field6_0x6;
    undefined field7_0x7;
    ulonglong mmio_addr;
    int use_mmio;
    undefined4 base_addr;
    undefined field11_0x18;
    undefined field12_0x19;
    undefined field13_0x1a;
    undefined field14_0x1b;
    undefined field15_0x1c;
    undefined field16_0x1d;
    undefined field17_0x1e;
    undefined field18_0x1f;
    undefined field19_0x20;
    undefined field20_0x21;
    undefined field21_0x22;
    undefined field22_0x23;
    undefined field23_0x24;
    undefined field24_0x25;
    undefined field25_0x26;
    undefined field26_0x27;
    undefined field27_0x28;
    undefined field28_0x29;
    undefined field29_0x2a;
    undefined field30_0x2b;
    undefined field31_0x2c;
    undefined field32_0x2d;
    undefined field33_0x2e;
    undefined field34_0x2f;
    undefined field35_0x30;
    undefined field36_0x31;
    undefined field37_0x32;
    undefined field38_0x33;
    undefined field39_0x34;
    undefined field40_0x35;
    undefined field41_0x36;
    undefined field42_0x37;
    undefined field43_0x38;
    undefined field44_0x39;
    undefined field45_0x3a;
    undefined field46_0x3b;
    undefined field47_0x3c;
    undefined field48_0x3d;
    undefined field49_0x3e;
    undefined field50_0x3f;
    undefined field51_0x40;
    undefined field52_0x41;
    undefined field53_0x42;
    undefined field54_0x43;
    undefined field55_0x44;
    undefined field56_0x45;
    undefined field57_0x46;
    undefined field58_0x47;
    undefined field59_0x48;
    undefined field60_0x49;
    undefined field61_0x4a;
    undefined field62_0x4b;
    undefined field63_0x4c;
    undefined field64_0x4d;
    undefined field65_0x4e;
    undefined field66_0x4f;
    undefined field67_0x50;
    undefined field68_0x51;
    undefined field69_0x52;
    undefined field70_0x53;
    undefined field71_0x54;
    undefined field72_0x55;
    undefined field73_0x56;
    undefined field74_0x57;
    undefined field75_0x58;
    undefined field76_0x59;
    undefined field77_0x5a;
    undefined field78_0x5b;
    undefined field79_0x5c;
    undefined field80_0x5d;
    undefined field81_0x5e;
    undefined field82_0x5f;
    undefined field83_0x60;
    undefined field84_0x61;
    undefined field85_0x62;
    undefined field86_0x63;
    undefined field87_0x64;
    undefined field88_0x65;
    undefined field89_0x66;
    undefined field90_0x67;
    undefined field91_0x68;
    undefined field92_0x69;
    undefined field93_0x6a;
    undefined field94_0x6b;
    undefined field95_0x6c;
    undefined field96_0x6d;
    undefined field97_0x6e;
    undefined field98_0x6f;
    undefined field99_0x70;
    undefined field100_0x71;
    undefined field101_0x72;
    undefined field102_0x73;
    undefined field103_0x74;
    undefined field104_0x75;
    undefined field105_0x76;
    undefined field106_0x77;
    undefined4 field107_0x78;
};

typedef struct astruct_1 astruct_1, *Pastruct_1;

struct astruct_1 {
    undefined field0_0x0;
    undefined field1_0x1;
    undefined field2_0x2;
    undefined field3_0x3;
    undefined field4_0x4;
    undefined field5_0x5;
    undefined field6_0x6;
    undefined field7_0x7;
    undefined field8_0x8;
    undefined field9_0x9;
    undefined field10_0xa;
    undefined field11_0xb;
    undefined field12_0xc;
    undefined field13_0xd;
    undefined field14_0xe;
    undefined field15_0xf;
    undefined field16_0x10;
    undefined field17_0x11;
    undefined field18_0x12;
    undefined field19_0x13;
    undefined field20_0x14;
    undefined field21_0x15;
    undefined field22_0x16;
    undefined field23_0x17;
    undefined field24_0x18;
    undefined field25_0x19;
    undefined field26_0x1a;
    undefined field27_0x1b;
    undefined field28_0x1c;
    undefined field29_0x1d;
    undefined field30_0x1e;
    undefined field31_0x1f;
    longlong field32_0x20;
    undefined field33_0x28;
    undefined field34_0x29;
    undefined field35_0x2a;
    undefined field36_0x2b;
    undefined field37_0x2c;
    undefined field38_0x2d;
    undefined field39_0x2e;
    undefined field40_0x2f;
    undefined field41_0x30;
    undefined field42_0x31;
    undefined field43_0x32;
    undefined field44_0x33;
    undefined field45_0x34;
    undefined field46_0x35;
    undefined field47_0x36;
    undefined field48_0x37;
    undefined8 field49_0x38;
    undefined field50_0x40;
    undefined field51_0x41;
    undefined field52_0x42;
    undefined field53_0x43;
    undefined field54_0x44;
    undefined field55_0x45;
    undefined field56_0x46;
    undefined field57_0x47;
    undefined field58_0x48;
    undefined field59_0x49;
    undefined field60_0x4a;
    undefined field61_0x4b;
    undefined field62_0x4c;
    undefined field63_0x4d;
    undefined field64_0x4e;
    undefined field65_0x4f;
    undefined field66_0x50;
    undefined field67_0x51;
    undefined field68_0x52;
    undefined field69_0x53;
    undefined field70_0x54;
    undefined field71_0x55;
    undefined field72_0x56;
    undefined field73_0x57;
    undefined field74_0x58;
    undefined field75_0x59;
    undefined field76_0x5a;
    undefined field77_0x5b;
    undefined field78_0x5c;
    undefined field79_0x5d;
    undefined field80_0x5e;
    undefined field81_0x5f;
    undefined field82_0x60;
    undefined field83_0x61;
    undefined field84_0x62;
    undefined field85_0x63;
    undefined field86_0x64;
    undefined field87_0x65;
    undefined field88_0x66;
    undefined field89_0x67;
    longlong mmio_addr;
    int field91_0x70;
    undefined4 base_addr;
    undefined field93_0x78;
    undefined field94_0x79;
    undefined field95_0x7a;
    undefined field96_0x7b;
    undefined field97_0x7c;
    undefined field98_0x7d;
    undefined field99_0x7e;
    undefined field100_0x7f;
    undefined field101_0x80;
    undefined field102_0x81;
    undefined field103_0x82;
    undefined field104_0x83;
    undefined field105_0x84;
    undefined field106_0x85;
    undefined field107_0x86;
    undefined field108_0x87;
    undefined field109_0x88;
    undefined field110_0x89;
    undefined field111_0x8a;
    undefined field112_0x8b;
    undefined field113_0x8c;
    undefined field114_0x8d;
    undefined field115_0x8e;
    undefined field116_0x8f;
    undefined field117_0x90;
    undefined field118_0x91;
    undefined field119_0x92;
    undefined field120_0x93;
    undefined field121_0x94;
    undefined field122_0x95;
    undefined field123_0x96;
    undefined field124_0x97;
    undefined field125_0x98;
    undefined field126_0x99;
    undefined field127_0x9a;
    undefined field128_0x9b;
    undefined field129_0x9c;
    undefined field130_0x9d;
    undefined field131_0x9e;
    undefined field132_0x9f;
    undefined field133_0xa0;
    undefined field134_0xa1;
    undefined field135_0xa2;
    undefined field136_0xa3;
    undefined field137_0xa4;
    undefined field138_0xa5;
    undefined field139_0xa6;
    undefined field140_0xa7;
    undefined field141_0xa8;
    undefined field142_0xa9;
    undefined field143_0xaa;
    undefined field144_0xab;
    undefined field145_0xac;
    undefined field146_0xad;
    undefined field147_0xae;
    undefined field148_0xaf;
    undefined field149_0xb0;
    undefined field150_0xb1;
    undefined field151_0xb2;
    undefined field152_0xb3;
    undefined field153_0xb4;
    undefined field154_0xb5;
    undefined field155_0xb6;
    undefined field156_0xb7;
    undefined field157_0xb8;
    undefined field158_0xb9;
    undefined field159_0xba;
    undefined field160_0xbb;
    undefined field161_0xbc;
    undefined field162_0xbd;
    undefined field163_0xbe;
    undefined field164_0xbf;
    undefined field165_0xc0;
    undefined field166_0xc1;
    undefined field167_0xc2;
    undefined field168_0xc3;
    undefined field169_0xc4;
    undefined field170_0xc5;
    undefined field171_0xc6;
    undefined field172_0xc7;
    undefined field173_0xc8;
    undefined field174_0xc9;
    undefined field175_0xca;
    undefined field176_0xcb;
    undefined field177_0xcc;
    undefined field178_0xcd;
    undefined field179_0xce;
    undefined field180_0xcf;
    undefined field181_0xd0;
    undefined field182_0xd1;
    undefined field183_0xd2;
    undefined field184_0xd3;
    undefined field185_0xd4;
    undefined field186_0xd5;
    undefined field187_0xd6;
    undefined field188_0xd7;
    undefined field189_0xd8;
    undefined field190_0xd9;
    undefined field191_0xda;
    undefined field192_0xdb;
    undefined field193_0xdc;
    undefined field194_0xdd;
    undefined field195_0xde;
    undefined field196_0xdf;
    undefined field197_0xe0;
    undefined field198_0xe1;
    undefined field199_0xe2;
    undefined field200_0xe3;
    undefined field201_0xe4;
    undefined field202_0xe5;
    undefined field203_0xe6;
    undefined field204_0xe7;
    undefined field205_0xe8;
    undefined field206_0xe9;
    undefined field207_0xea;
    undefined field208_0xeb;
    undefined field209_0xec;
    undefined field210_0xed;
    undefined field211_0xee;
    undefined field212_0xef;
    undefined field213_0xf0;
    undefined field214_0xf1;
    undefined field215_0xf2;
    undefined field216_0xf3;
    undefined field217_0xf4;
    undefined field218_0xf5;
    undefined field219_0xf6;
    undefined field220_0xf7;
    undefined field221_0xf8;
    undefined field222_0xf9;
    undefined field223_0xfa;
    undefined field224_0xfb;
    undefined field225_0xfc;
    undefined field226_0xfd;
    undefined field227_0xfe;
    undefined field228_0xff;
    undefined field229_0x100;
    undefined field230_0x101;
    undefined field231_0x102;
    undefined field232_0x103;
    undefined field233_0x104;
    undefined field234_0x105;
    undefined field235_0x106;
    undefined field236_0x107;
    undefined field237_0x108;
    undefined field238_0x109;
    undefined field239_0x10a;
    undefined field240_0x10b;
    undefined field241_0x10c;
    undefined field242_0x10d;
    undefined field243_0x10e;
    undefined field244_0x10f;
    undefined field245_0x110;
    undefined field246_0x111;
    undefined field247_0x112;
    undefined field248_0x113;
    undefined field249_0x114;
    undefined field250_0x115;
    undefined field251_0x116;
    undefined field252_0x117;
    ulonglong field253_0x118;
    ulonglong field254_0x120;
};

typedef struct astruct_7 astruct_7, *Pastruct_7;

struct astruct_7 {
    undefined field0_0x0;
    undefined field1_0x1;
    undefined field2_0x2;
    undefined field3_0x3;
    undefined field4_0x4;
    undefined field5_0x5;
    undefined field6_0x6;
    undefined field7_0x7;
    ulonglong mmio_addr;
    int use_mmio;
    undefined4 base_addr;
    undefined field11_0x18;
    undefined field12_0x19;
    undefined field13_0x1a;
    undefined field14_0x1b;
    undefined field15_0x1c;
    undefined field16_0x1d;
    undefined field17_0x1e;
    undefined field18_0x1f;
    int field19_0x20;
};

typedef struct astruct_9 astruct_9, *Pastruct_9;

struct astruct_9 {
    undefined field0_0x0;
    undefined field1_0x1;
    undefined field2_0x2;
    undefined field3_0x3;
    undefined field4_0x4;
    undefined field5_0x5;
    undefined field6_0x6;
    undefined field7_0x7;
    byte * mmio_addr;
    int use_mmio;
    undefined4 base_addr;
    undefined field11_0x18;
    undefined field12_0x19;
    undefined field13_0x1a;
    undefined field14_0x1b;
    undefined field15_0x1c;
    undefined field16_0x1d;
    undefined field17_0x1e;
    undefined field18_0x1f;
    int field19_0x20;
    undefined field20_0x24;
    undefined field21_0x25;
    undefined field22_0x26;
    undefined field23_0x27;
    undefined field24_0x28;
    undefined field25_0x29;
    undefined field26_0x2a;
    undefined field27_0x2b;
    undefined field28_0x2c;
    undefined field29_0x2d;
    undefined field30_0x2e;
    undefined field31_0x2f;
    int field32_0x30;
    undefined field33_0x34;
    undefined field34_0x35;
    undefined field35_0x36;
    undefined field36_0x37;
    undefined field37_0x38;
    undefined field38_0x39;
    undefined field39_0x3a;
    undefined field40_0x3b;
    undefined field41_0x3c;
    undefined field42_0x3d;
    undefined field43_0x3e;
    undefined field44_0x3f;
    undefined field45_0x40;
    undefined field46_0x41;
    undefined field47_0x42;
    undefined field48_0x43;
    undefined field49_0x44;
    undefined field50_0x45;
    undefined field51_0x46;
    undefined field52_0x47;
    undefined field53_0x48;
    undefined field54_0x49;
    undefined field55_0x4a;
    undefined field56_0x4b;
    undefined field57_0x4c;
    undefined field58_0x4d;
    undefined field59_0x4e;
    undefined field60_0x4f;
    char field61_0x50;
    undefined field62_0x51;
    undefined field63_0x52;
    undefined field64_0x53;
    undefined field65_0x54;
    undefined field66_0x55;
    undefined field67_0x56;
    undefined field68_0x57;
    byte * field69_0x58;
    undefined * field70_0x60;
    undefined * field71_0x68;
    undefined field72_0x70;
    undefined field73_0x71;
    undefined field74_0x72;
    undefined field75_0x73;
    undefined field76_0x74;
    undefined field77_0x75;
    undefined field78_0x76;
    undefined field79_0x77;
    int field80_0x78;
    undefined field81_0x7c;
    undefined field82_0x7d;
    undefined field83_0x7e;
    undefined field84_0x7f;
    int field85_0x80;
    undefined field86_0x84;
    undefined field87_0x85;
    undefined field88_0x86;
    undefined field89_0x87;
    int field90_0x88;
    int field91_0x8c;
    int field92_0x90;
    int field93_0x94;
    int field94_0x98;
    int field95_0x9c;
    int field96_0xa0;
    int field97_0xa4;
    undefined field98_0xa8;
    undefined field99_0xa9;
    undefined field100_0xaa;
    undefined field101_0xab;
    undefined field102_0xac;
    undefined field103_0xad;
    undefined field104_0xae;
    undefined field105_0xaf;
    undefined field106_0xb0;
    undefined field107_0xb1;
    undefined field108_0xb2;
    undefined field109_0xb3;
    undefined field110_0xb4;
    undefined field111_0xb5;
    undefined field112_0xb6;
    undefined field113_0xb7;
    undefined8 field114_0xb8;
    undefined field115_0xc0;
    undefined field116_0xc1;
    undefined field117_0xc2;
    undefined field118_0xc3;
    undefined field119_0xc4;
    undefined field120_0xc5;
    undefined field121_0xc6;
    undefined field122_0xc7;
    undefined field123_0xc8;
    undefined field124_0xc9;
    undefined field125_0xca;
    undefined field126_0xcb;
    undefined field127_0xcc;
    undefined field128_0xcd;
    undefined field129_0xce;
    undefined field130_0xcf;
    char field131_0xd0;
    undefined field132_0xd1;
    undefined field133_0xd2;
    undefined field134_0xd3;
    undefined field135_0xd4;
    undefined field136_0xd5;
    undefined field137_0xd6;
    undefined field138_0xd7;
    ulonglong field139_0xd8;
};

typedef struct astruct_2 astruct_2, *Pastruct_2;

struct astruct_2 {
    undefined field0_0x0;
    char field1_0x1;
    char field2_0x2;
    undefined field3_0x3;
    undefined field4_0x4;
    undefined field5_0x5;
    undefined field6_0x6;
    undefined field7_0x7;
    undefined field8_0x8;
    undefined field9_0x9;
    undefined field10_0xa;
    undefined field11_0xb;
    undefined field12_0xc;
    undefined field13_0xd;
    undefined field14_0xe;
    undefined field15_0xf;
    undefined field16_0x10;
    undefined field17_0x11;
    undefined field18_0x12;
    undefined field19_0x13;
    undefined field20_0x14;
    undefined field21_0x15;
    undefined field22_0x16;
    undefined field23_0x17;
    undefined field24_0x18;
    undefined field25_0x19;
    undefined field26_0x1a;
    undefined field27_0x1b;
    undefined field28_0x1c;
    undefined field29_0x1d;
    undefined field30_0x1e;
    undefined field31_0x1f;
    longlong field32_0x20;
    undefined field33_0x28;
    undefined field34_0x29;
    undefined field35_0x2a;
    undefined field36_0x2b;
    undefined field37_0x2c;
    undefined field38_0x2d;
    undefined field39_0x2e;
    undefined field40_0x2f;
    undefined field41_0x30;
    undefined field42_0x31;
    undefined field43_0x32;
    undefined field44_0x33;
    undefined field45_0x34;
    undefined field46_0x35;
    undefined field47_0x36;
    undefined field48_0x37;
    undefined field49_0x38;
    undefined field50_0x39;
    undefined field51_0x3a;
    undefined field52_0x3b;
    undefined field53_0x3c;
    undefined field54_0x3d;
    undefined field55_0x3e;
    undefined field56_0x3f;
    undefined field57_0x40;
    undefined field58_0x41;
    undefined field59_0x42;
    undefined field60_0x43;
    undefined field61_0x44;
    undefined field62_0x45;
    undefined field63_0x46;
    undefined field64_0x47;
    undefined field65_0x48;
    undefined field66_0x49;
    undefined field67_0x4a;
    undefined field68_0x4b;
    undefined field69_0x4c;
    undefined field70_0x4d;
    undefined field71_0x4e;
    undefined field72_0x4f;
    undefined field73_0x50;
    undefined field74_0x51;
    undefined field75_0x52;
    undefined field76_0x53;
    undefined field77_0x54;
    undefined field78_0x55;
    undefined field79_0x56;
    undefined field80_0x57;
    undefined field81_0x58;
    undefined field82_0x59;
    undefined field83_0x5a;
    undefined field84_0x5b;
    undefined field85_0x5c;
    undefined field86_0x5d;
    undefined field87_0x5e;
    undefined field88_0x5f;
    undefined field89_0x60;
    undefined field90_0x61;
    undefined field91_0x62;
    undefined field92_0x63;
    undefined field93_0x64;
    undefined field94_0x65;
    undefined field95_0x66;
    undefined field96_0x67;
    longlong mmio_addr;
    int use_mmio;
    undefined4 base_addr;
    undefined field100_0x78;
    undefined field101_0x79;
    undefined field102_0x7a;
    undefined field103_0x7b;
    undefined field104_0x7c;
    undefined field105_0x7d;
    undefined field106_0x7e;
    undefined field107_0x7f;
    int field108_0x80;
    undefined field109_0x84;
    undefined field110_0x85;
    undefined field111_0x86;
    undefined field112_0x87;
    undefined field113_0x88;
    undefined field114_0x89;
    undefined field115_0x8a;
    undefined field116_0x8b;
    undefined field117_0x8c;
    undefined field118_0x8d;
    undefined field119_0x8e;
    undefined field120_0x8f;
    undefined4 field121_0x90;
    undefined4 field122_0x94;
    undefined4 field123_0x98;
    undefined4 field124_0x9c;
    undefined4 field125_0xa0;
    undefined field126_0xa4;
    undefined field127_0xa5;
    undefined field128_0xa6;
    undefined field129_0xa7;
    undefined8 field130_0xa8;
    undefined field131_0xb0;
    undefined field132_0xb1;
    undefined field133_0xb2;
    undefined field134_0xb3;
    undefined field135_0xb4;
    undefined field136_0xb5;
    undefined field137_0xb6;
    undefined field138_0xb7;
    undefined8 field139_0xb8;
    undefined8 field140_0xc0;
    undefined8 field141_0xc8;
};

typedef struct astruct_4 astruct_4, *Pastruct_4;

struct astruct_4 {
    undefined field0_0x0;
    undefined field1_0x1;
    undefined field2_0x2;
    undefined field3_0x3;
    undefined field4_0x4;
    undefined field5_0x5;
    undefined field6_0x6;
    undefined field7_0x7;
    undefined field8_0x8;
    undefined field9_0x9;
    undefined field10_0xa;
    undefined field11_0xb;
    undefined field12_0xc;
    undefined field13_0xd;
    undefined field14_0xe;
    undefined field15_0xf;
    undefined field16_0x10;
    undefined field17_0x11;
    undefined field18_0x12;
    undefined field19_0x13;
    undefined field20_0x14;
    undefined field21_0x15;
    undefined field22_0x16;
    undefined field23_0x17;
    undefined field24_0x18;
    undefined field25_0x19;
    undefined field26_0x1a;
    undefined field27_0x1b;
    undefined field28_0x1c;
    undefined field29_0x1d;
    undefined field30_0x1e;
    undefined field31_0x1f;
    longlong field32_0x20;
    undefined field33_0x28;
    undefined field34_0x29;
    undefined field35_0x2a;
    undefined field36_0x2b;
    undefined field37_0x2c;
    undefined field38_0x2d;
    undefined field39_0x2e;
    undefined field40_0x2f;
    undefined field41_0x30;
    undefined field42_0x31;
    undefined field43_0x32;
    undefined field44_0x33;
    undefined field45_0x34;
    undefined field46_0x35;
    undefined field47_0x36;
    undefined field48_0x37;
    undefined field49_0x38;
    undefined field50_0x39;
    undefined field51_0x3a;
    undefined field52_0x3b;
    undefined field53_0x3c;
    undefined field54_0x3d;
    undefined field55_0x3e;
    undefined field56_0x3f;
    undefined field57_0x40;
    undefined field58_0x41;
    undefined field59_0x42;
    undefined field60_0x43;
    undefined field61_0x44;
    undefined field62_0x45;
    undefined field63_0x46;
    undefined field64_0x47;
    undefined field65_0x48;
    undefined field66_0x49;
    undefined field67_0x4a;
    undefined field68_0x4b;
    undefined field69_0x4c;
    undefined field70_0x4d;
    undefined field71_0x4e;
    undefined field72_0x4f;
    undefined field73_0x50;
    undefined field74_0x51;
    undefined field75_0x52;
    undefined field76_0x53;
    undefined field77_0x54;
    undefined field78_0x55;
    undefined field79_0x56;
    undefined field80_0x57;
    undefined field81_0x58;
    undefined field82_0x59;
    undefined field83_0x5a;
    undefined field84_0x5b;
    undefined field85_0x5c;
    undefined field86_0x5d;
    undefined field87_0x5e;
    undefined field88_0x5f;
    undefined field89_0x60;
    undefined field90_0x61;
    undefined field91_0x62;
    undefined field92_0x63;
    undefined field93_0x64;
    undefined field94_0x65;
    undefined field95_0x66;
    undefined field96_0x67;
    longlong mmio_addr;
    int use_mmio;
    undefined4 base_addr;
    undefined field100_0x78;
    undefined field101_0x79;
    undefined field102_0x7a;
    undefined field103_0x7b;
    undefined field104_0x7c;
    undefined field105_0x7d;
    undefined field106_0x7e;
    undefined field107_0x7f;
    int field108_0x80;
    undefined field109_0x84;
    undefined field110_0x85;
    undefined field111_0x86;
    undefined field112_0x87;
    undefined field113_0x88;
    undefined field114_0x89;
    undefined field115_0x8a;
    undefined field116_0x8b;
    undefined field117_0x8c;
    undefined field118_0x8d;
    undefined field119_0x8e;
    undefined field120_0x8f;
    undefined4 field121_0x90;
    undefined4 field122_0x94;
    undefined4 field123_0x98;
    undefined4 field124_0x9c;
    undefined4 field125_0xa0;
    undefined field126_0xa4;
    undefined field127_0xa5;
    undefined field128_0xa6;
    undefined field129_0xa7;
    undefined8 field130_0xa8;
    undefined field131_0xb0;
    undefined field132_0xb1;
    undefined field133_0xb2;
    undefined field134_0xb3;
    undefined field135_0xb4;
    undefined field136_0xb5;
    undefined field137_0xb6;
    undefined field138_0xb7;
    undefined8 field139_0xb8;
    undefined8 field140_0xc0;
    undefined8 field141_0xc8;
};

typedef struct astruct_6 astruct_6, *Pastruct_6;

struct astruct_6 {
    undefined field0_0x0;
    undefined field1_0x1;
    undefined field2_0x2;
    undefined field3_0x3;
    undefined field4_0x4;
    undefined field5_0x5;
    undefined field6_0x6;
    undefined field7_0x7;
    undefined field8_0x8;
    undefined field9_0x9;
    undefined field10_0xa;
    undefined field11_0xb;
    undefined field12_0xc;
    undefined field13_0xd;
    undefined field14_0xe;
    undefined field15_0xf;
    undefined field16_0x10;
    undefined field17_0x11;
    undefined field18_0x12;
    undefined field19_0x13;
    undefined field20_0x14;
    undefined field21_0x15;
    undefined field22_0x16;
    undefined field23_0x17;
    undefined field24_0x18;
    undefined field25_0x19;
    undefined field26_0x1a;
    undefined field27_0x1b;
    undefined field28_0x1c;
    undefined field29_0x1d;
    undefined field30_0x1e;
    undefined field31_0x1f;
    undefined field32_0x20;
    undefined field33_0x21;
    undefined field34_0x22;
    undefined field35_0x23;
    undefined field36_0x24;
    undefined field37_0x25;
    undefined field38_0x26;
    undefined field39_0x27;
    undefined field40_0x28;
    undefined field41_0x29;
    undefined field42_0x2a;
    undefined field43_0x2b;
    undefined field44_0x2c;
    undefined field45_0x2d;
    undefined field46_0x2e;
    undefined field47_0x2f;
    undefined field48_0x30;
    undefined field49_0x31;
    undefined field50_0x32;
    undefined field51_0x33;
    undefined field52_0x34;
    undefined field53_0x35;
    undefined field54_0x36;
    undefined field55_0x37;
    undefined field56_0x38;
    undefined field57_0x39;
    undefined field58_0x3a;
    undefined field59_0x3b;
    undefined field60_0x3c;
    undefined field61_0x3d;
    undefined field62_0x3e;
    undefined field63_0x3f;
    undefined field64_0x40;
    undefined field65_0x41;
    undefined field66_0x42;
    undefined field67_0x43;
    undefined field68_0x44;
    undefined field69_0x45;
    undefined field70_0x46;
    undefined field71_0x47;
    undefined field72_0x48;
    undefined field73_0x49;
    undefined field74_0x4a;
    undefined field75_0x4b;
    undefined field76_0x4c;
    undefined field77_0x4d;
    undefined field78_0x4e;
    undefined field79_0x4f;
    undefined field80_0x50;
    undefined field81_0x51;
    undefined field82_0x52;
    undefined field83_0x53;
    undefined field84_0x54;
    undefined field85_0x55;
    undefined field86_0x56;
    undefined field87_0x57;
    undefined field88_0x58;
    undefined field89_0x59;
    undefined field90_0x5a;
    undefined field91_0x5b;
    undefined field92_0x5c;
    undefined field93_0x5d;
    undefined field94_0x5e;
    undefined field95_0x5f;
    undefined field96_0x60;
    undefined field97_0x61;
    undefined field98_0x62;
    undefined field99_0x63;
    undefined field100_0x64;
    undefined field101_0x65;
    undefined field102_0x66;
    undefined field103_0x67;
    longlong mmio_addr;
    int use_mmio;
    undefined4 base_addr;
    undefined field107_0x78;
    undefined field108_0x79;
    undefined field109_0x7a;
    undefined field110_0x7b;
    undefined field111_0x7c;
    undefined field112_0x7d;
    undefined field113_0x7e;
    undefined field114_0x7f;
    undefined field115_0x80;
    undefined field116_0x81;
    undefined field117_0x82;
    undefined field118_0x83;
    undefined field119_0x84;
    undefined field120_0x85;
    undefined field121_0x86;
    undefined field122_0x87;
    undefined field123_0x88;
    undefined field124_0x89;
    undefined field125_0x8a;
    undefined field126_0x8b;
    undefined field127_0x8c;
    undefined field128_0x8d;
    undefined field129_0x8e;
    undefined field130_0x8f;
    undefined field131_0x90;
    undefined field132_0x91;
    undefined field133_0x92;
    undefined field134_0x93;
    undefined field135_0x94;
    undefined field136_0x95;
    undefined field137_0x96;
    undefined field138_0x97;
    undefined field139_0x98;
    undefined field140_0x99;
    undefined field141_0x9a;
    undefined field142_0x9b;
    undefined field143_0x9c;
    undefined field144_0x9d;
    undefined field145_0x9e;
    undefined field146_0x9f;
    undefined field147_0xa0;
    undefined field148_0xa1;
    undefined field149_0xa2;
    undefined field150_0xa3;
    undefined field151_0xa4;
    undefined field152_0xa5;
    undefined field153_0xa6;
    undefined field154_0xa7;
    undefined field155_0xa8;
    undefined field156_0xa9;
    undefined field157_0xaa;
    undefined field158_0xab;
    undefined field159_0xac;
    undefined field160_0xad;
    undefined field161_0xae;
    undefined field162_0xaf;
    undefined field163_0xb0;
    undefined field164_0xb1;
    undefined field165_0xb2;
    undefined field166_0xb3;
    undefined field167_0xb4;
    undefined field168_0xb5;
    undefined field169_0xb6;
    undefined field170_0xb7;
    undefined field171_0xb8;
    undefined field172_0xb9;
    undefined field173_0xba;
    undefined field174_0xbb;
    undefined field175_0xbc;
    undefined field176_0xbd;
    undefined field177_0xbe;
    undefined field178_0xbf;
    undefined field179_0xc0;
    undefined field180_0xc1;
    undefined field181_0xc2;
    undefined field182_0xc3;
    undefined field183_0xc4;
    undefined field184_0xc5;
    undefined field185_0xc6;
    undefined field186_0xc7;
    undefined field187_0xc8;
    undefined field188_0xc9;
    undefined field189_0xca;
    undefined field190_0xcb;
    undefined field191_0xcc;
    undefined field192_0xcd;
    undefined field193_0xce;
    undefined field194_0xcf;
    undefined field195_0xd0;
    undefined field196_0xd1;
    undefined field197_0xd2;
    undefined field198_0xd3;
    undefined field199_0xd4;
    undefined field200_0xd5;
    undefined field201_0xd6;
    undefined field202_0xd7;
    undefined4 field203_0xd8;
};

typedef struct astruct_8 astruct_8, *Pastruct_8;

struct astruct_8 {
    undefined field0_0x0;
    undefined field1_0x1;
    undefined field2_0x2;
    undefined field3_0x3;
    undefined field4_0x4;
    undefined field5_0x5;
    undefined field6_0x6;
    undefined field7_0x7;
    ulonglong mmio_addr;
    int use_mmio;
    undefined4 base_addr;
    undefined field11_0x18;
    undefined field12_0x19;
    undefined field13_0x1a;
    undefined field14_0x1b;
    undefined field15_0x1c;
    undefined field16_0x1d;
    undefined field17_0x1e;
    undefined field18_0x1f;
    int field19_0x20;
    undefined field20_0x24;
    undefined field21_0x25;
    undefined field22_0x26;
    undefined field23_0x27;
    undefined field24_0x28;
    undefined field25_0x29;
    undefined field26_0x2a;
    undefined field27_0x2b;
    undefined field28_0x2c;
    undefined field29_0x2d;
    undefined field30_0x2e;
    undefined field31_0x2f;
    undefined field32_0x30;
    undefined field33_0x31;
    undefined field34_0x32;
    undefined field35_0x33;
    undefined field36_0x34;
    undefined field37_0x35;
    undefined field38_0x36;
    undefined field39_0x37;
    undefined field40_0x38;
    undefined field41_0x39;
    undefined field42_0x3a;
    undefined field43_0x3b;
    undefined field44_0x3c;
    undefined field45_0x3d;
    undefined field46_0x3e;
    undefined field47_0x3f;
    undefined field48_0x40;
    undefined field49_0x41;
    undefined field50_0x42;
    undefined field51_0x43;
    undefined field52_0x44;
    undefined field53_0x45;
    undefined field54_0x46;
    undefined field55_0x47;
    undefined field56_0x48;
    undefined field57_0x49;
    undefined field58_0x4a;
    undefined field59_0x4b;
    undefined field60_0x4c;
    undefined field61_0x4d;
    undefined field62_0x4e;
    undefined field63_0x4f;
    undefined field64_0x50;
    undefined field65_0x51;
    undefined field66_0x52;
    undefined field67_0x53;
    undefined field68_0x54;
    undefined field69_0x55;
    undefined field70_0x56;
    undefined field71_0x57;
    undefined field72_0x58;
    undefined field73_0x59;
    undefined field74_0x5a;
    undefined field75_0x5b;
    undefined field76_0x5c;
    undefined field77_0x5d;
    undefined field78_0x5e;
    undefined field79_0x5f;
    undefined field80_0x60;
    undefined field81_0x61;
    undefined field82_0x62;
    undefined field83_0x63;
    undefined field84_0x64;
    undefined field85_0x65;
    undefined field86_0x66;
    undefined field87_0x67;
    undefined field88_0x68;
    undefined field89_0x69;
    undefined field90_0x6a;
    undefined field91_0x6b;
    undefined field92_0x6c;
    undefined field93_0x6d;
    undefined field94_0x6e;
    undefined field95_0x6f;
    undefined field96_0x70;
    undefined field97_0x71;
    undefined field98_0x72;
    undefined field99_0x73;
    undefined field100_0x74;
    undefined field101_0x75;
    undefined field102_0x76;
    undefined field103_0x77;
    undefined field104_0x78;
    undefined field105_0x79;
    undefined field106_0x7a;
    undefined field107_0x7b;
    undefined field108_0x7c;
    undefined field109_0x7d;
    undefined field110_0x7e;
    undefined field111_0x7f;
    undefined4 field112_0x80;
    undefined4 field113_0x84;
    undefined4 field114_0x88;
    undefined4 field115_0x8c;
    undefined4 field116_0x90;
    undefined4 field117_0x94;
    undefined4 field118_0x98;
    undefined4 field119_0x9c;
    undefined4 field120_0xa0;
    undefined4 field121_0xa4;
    undefined4 field122_0xa8;
    undefined4 field123_0xac;
    undefined4 field124_0xb0;
    undefined4 field125_0xb4;
    undefined8 field126_0xb8;
    undefined8 field127_0xc0;
    undefined field128_0xc8;
    undefined field129_0xc9;
    undefined2 field130_0xca;
    undefined field131_0xcc;
    undefined field132_0xcd;
    undefined field133_0xce;
    undefined field134_0xcf;
    byte field135_0xd0;
    undefined field136_0xd1;
    undefined field137_0xd2;
    undefined field138_0xd3;
    undefined field139_0xd4;
    undefined field140_0xd5;
    undefined field141_0xd6;
    undefined field142_0xd7;
    byte * field143_0xd8;
    undefined8 field144_0xe0;
};

typedef struct astruct_11 astruct_11, *Pastruct_11;

struct astruct_11 {
    undefined field0_0x0;
    undefined field1_0x1;
    undefined field2_0x2;
    undefined field3_0x3;
    undefined field4_0x4;
    undefined field5_0x5;
    undefined field6_0x6;
    undefined field7_0x7;
    longlong mmio_addr;
    int use_mmio;
    undefined4 base_addr;
    undefined field11_0x18;
    undefined field12_0x19;
    undefined field13_0x1a;
    undefined field14_0x1b;
    undefined field15_0x1c;
    undefined field16_0x1d;
    undefined field17_0x1e;
    undefined field18_0x1f;
    undefined field19_0x20;
    undefined field20_0x21;
    undefined field21_0x22;
    undefined field22_0x23;
    undefined field23_0x24;
    undefined field24_0x25;
    undefined field25_0x26;
    undefined field26_0x27;
    undefined field27_0x28;
    undefined field28_0x29;
    undefined field29_0x2a;
    undefined field30_0x2b;
    undefined field31_0x2c;
    undefined field32_0x2d;
    undefined field33_0x2e;
    undefined field34_0x2f;
    undefined field35_0x30;
    undefined field36_0x31;
    undefined field37_0x32;
    undefined field38_0x33;
    undefined field39_0x34;
    undefined field40_0x35;
    undefined field41_0x36;
    undefined field42_0x37;
    undefined field43_0x38;
    undefined field44_0x39;
    undefined field45_0x3a;
    undefined field46_0x3b;
    undefined field47_0x3c;
    undefined field48_0x3d;
    undefined field49_0x3e;
    undefined field50_0x3f;
    undefined field51_0x40;
    undefined field52_0x41;
    undefined field53_0x42;
    undefined field54_0x43;
    undefined field55_0x44;
    undefined field56_0x45;
    undefined field57_0x46;
    undefined field58_0x47;
    undefined field59_0x48;
    undefined field60_0x49;
    undefined field61_0x4a;
    undefined field62_0x4b;
    undefined field63_0x4c;
    undefined field64_0x4d;
    undefined field65_0x4e;
    undefined field66_0x4f;
    undefined field67_0x50;
    undefined field68_0x51;
    undefined field69_0x52;
    undefined field70_0x53;
    undefined field71_0x54;
    undefined field72_0x55;
    undefined field73_0x56;
    undefined field74_0x57;
    undefined field75_0x58;
    undefined field76_0x59;
    undefined field77_0x5a;
    undefined field78_0x5b;
    undefined field79_0x5c;
    undefined field80_0x5d;
    undefined field81_0x5e;
    undefined field82_0x5f;
    undefined field83_0x60;
    undefined field84_0x61;
    undefined field85_0x62;
    undefined field86_0x63;
    undefined field87_0x64;
    undefined field88_0x65;
    undefined field89_0x66;
    undefined field90_0x67;
    undefined field91_0x68;
    undefined field92_0x69;
    undefined field93_0x6a;
    undefined field94_0x6b;
    undefined field95_0x6c;
    undefined field96_0x6d;
    undefined field97_0x6e;
    undefined field98_0x6f;
    undefined field99_0x70;
    undefined field100_0x71;
    undefined field101_0x72;
    undefined field102_0x73;
    undefined field103_0x74;
    undefined field104_0x75;
    undefined field105_0x76;
    undefined field106_0x77;
    undefined field107_0x78;
    undefined field108_0x79;
    undefined field109_0x7a;
    undefined field110_0x7b;
    undefined field111_0x7c;
    undefined field112_0x7d;
    undefined field113_0x7e;
    undefined field114_0x7f;
    undefined field115_0x80;
    undefined field116_0x81;
    undefined field117_0x82;
    undefined field118_0x83;
    undefined field119_0x84;
    undefined field120_0x85;
    undefined field121_0x86;
    undefined field122_0x87;
    undefined field123_0x88;
    undefined field124_0x89;
    undefined field125_0x8a;
    undefined field126_0x8b;
    undefined field127_0x8c;
    undefined field128_0x8d;
    undefined field129_0x8e;
    undefined field130_0x8f;
    undefined field131_0x90;
    undefined field132_0x91;
    undefined field133_0x92;
    undefined field134_0x93;
    undefined field135_0x94;
    undefined field136_0x95;
    undefined field137_0x96;
    undefined field138_0x97;
    undefined field139_0x98;
    undefined field140_0x99;
    undefined field141_0x9a;
    undefined field142_0x9b;
    undefined field143_0x9c;
    undefined field144_0x9d;
    undefined field145_0x9e;
    undefined field146_0x9f;
    undefined field147_0xa0;
    undefined field148_0xa1;
    undefined field149_0xa2;
    undefined field150_0xa3;
    undefined field151_0xa4;
    undefined field152_0xa5;
    undefined field153_0xa6;
    undefined field154_0xa7;
    int field155_0xa8;
    undefined field156_0xac;
    undefined field157_0xad;
    undefined field158_0xae;
    undefined field159_0xaf;
    undefined field160_0xb0;
    undefined field161_0xb1;
    undefined field162_0xb2;
    undefined field163_0xb3;
    undefined field164_0xb4;
    undefined field165_0xb5;
    undefined field166_0xb6;
    undefined field167_0xb7;
    undefined field168_0xb8;
    undefined field169_0xb9;
    undefined field170_0xba;
    undefined field171_0xbb;
    undefined field172_0xbc;
    undefined field173_0xbd;
    undefined field174_0xbe;
    undefined field175_0xbf;
    longlong field176_0xc0;
    undefined field177_0xc8;
    undefined field178_0xc9;
};

typedef ulonglong size_t;




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined8 win_irq_check(void)

{
  DAT_140008098 = KeGetCurrentIrql();
  KeInitializeSpinLock(&DAT_140008090);
  _DAT_140008074 = 0;
  _DAT_140008070 = 0;
  if (0x1f < DAT_140008380) {
    _DAT_140008070 = 0;
    _DAT_140008074 = 0;
    return 0xffffffff;
  }
  *(code **)(&DAT_140008280 + (longlong)DAT_140008380 * 8) = win_1400067c0;
  DAT_140008380 = DAT_140008380 + 1;
  return 0;
}



undefined8 * win_140001040(undefined8 *param_1,ulonglong param_2)

{
  ulonglong uVar1;
  
  *param_1 = &PTR_win_1400071a0;
  if ((param_2 & 1) != 0) {
    uVar1 = win_1400013f0((longlong)&DAT_140008070,(ulonglong)param_1);
    if ((char)uVar1 == '\0') {
      ExFreePoolWithTag(param_1,0);
    }
  }
  return param_1;
}



void win_1400010f8(ulonglong param_1)

{
  win_140001104(param_1,DAT_140008240);
  return;
}



void win_140001104(ulonglong param_1,int param_2)

{
  int iVar1;
  char cVar2;
  undefined (*pauVar3) [16];
  longlong lVar4;
  ulonglong uVar5;
  
  uVar5 = 1;
  if (param_1 != 0) {
    uVar5 = param_1;
  }
  iVar1 = param_2;
  if (param_2 == 3) {
    uVar5 = param_1 + 7 & 0xfffffff8;
    iVar1 = DAT_140008240;
  }
  while (((param_2 != 3 ||
          (pauVar3 = win_14000126c((int *)&DAT_140008070,uVar5), pauVar3 == (undefined (*) [16])0x0)
          ) && (lVar4 = ExAllocatePoolWithTag(iVar1,uVar5,0x546e7953), lVar4 == 0))) {
    cVar2 = KeGetCurrentIrql();
    if (cVar2 == '\0') {
      win_delay(1);
    }
  }
  return;
}



void win_140001194(ulonglong param_1)

{
  ulonglong uVar1;
  
  if ((param_1 != 0) &&
     (uVar1 = win_1400013f0((longlong)&DAT_140008070,param_1), (char)uVar1 == '\0')) {
    ExFreePoolWithTag(param_1,0);
  }
  return;
}



void win_1400011c8(longlong param_1)

{
  undefined (*pauVar1) [16];
  longlong lVar2;
  undefined (*pauVar3) [16];
  
  pauVar3 = (undefined (*) [16])win_140001104(0x10000,DAT_140008240);
  static_init_2(pauVar3,0xcd,0x10000);
  *(undefined8 *)pauVar3[1] = 0xffe0;
  *(undefined4 *)(pauVar3[1] + 8) = 0x504a41;
  lVar2 = *(longlong *)(param_1 + 8);
  *(undefined8 *)*pauVar3 = 0;
  if (lVar2 == 0) {
    *(undefined8 *)(*pauVar3 + 8) = 0;
  }
  else {
    *(longlong *)(*pauVar3 + 8) = lVar2;
    **(undefined (***) [16])(param_1 + 8) = pauVar3;
  }
  *(undefined (**) [16])(param_1 + 8) = pauVar3;
  pauVar1 = pauVar3[2];
  *(undefined8 *)pauVar3[3] = 0xffc0;
  *(undefined4 *)(pauVar3[3] + 8) = 0x504a41;
  lVar2 = *(longlong *)(param_1 + 0x10);
  *(undefined8 *)*pauVar1 = 0;
  if (lVar2 == 0) {
    *(undefined8 *)(pauVar3[2] + 8) = 0;
  }
  else {
    *(longlong *)(pauVar3[2] + 8) = lVar2;
    **(undefined (***) [16])(param_1 + 0x10) = pauVar1;
  }
  *(undefined (**) [16])(param_1 + 0x10) = pauVar1;
  return;
}



undefined (*) [16] win_14000126c(int *param_1,ulonglong param_2)

{
  longlong **pplVar1;
  longlong *plVar2;
  undefined uVar3;
  undefined (*pauVar4) [16];
  longlong lVar5;
  longlong *plVar6;
  longlong lVar7;
  ulonglong uVar8;
  
  if (param_2 < 0xffc1) {
    uVar3 = KeAcquireSpinLockRaiseToDpc(param_1 + 8);
    pplVar1 = (longlong **)(param_1 + 4);
    *(undefined *)(param_1 + 10) = uVar3;
    lVar5 = win_140001364(pplVar1,param_2);
    if (lVar5 == 0) {
      win_1400011c8((longlong)param_1);
      lVar5 = win_140001364(pplVar1,param_2);
    }
    if (param_2 + 0x100 <= *(ulonglong *)(lVar5 + 0x10) &&
        *(ulonglong *)(lVar5 + 0x10) != param_2 + 0x100) {
      lVar7 = *(longlong *)(lVar5 + 0x10) - param_2;
      plVar6 = (longlong *)((*(longlong *)(lVar5 + 0x10) - lVar7) + 0x20 + lVar5);
      plVar6[2] = lVar7 + -0x20;
      *(undefined4 *)(plVar6 + 3) = 0x504a41;
      plVar2 = *pplVar1;
      *plVar6 = 0;
      if (plVar2 == (longlong *)0x0) {
        plVar6[1] = 0;
      }
      else {
        plVar6[1] = (longlong)plVar2;
        **pplVar1 = (longlong)plVar6;
      }
      *pplVar1 = plVar6;
      *(longlong *)(lVar5 + 0x10) = *(longlong *)(lVar5 + 0x10) - lVar7;
    }
    *param_1 = *param_1 + 1;
    pauVar4 = (undefined (*) [16])(lVar5 + 0x20);
    uVar8 = 0;
    static_init_2(pauVar4,0,*(ulonglong *)(lVar5 + 0x10));
    KeReleaseSpinLock(param_1 + 8,uVar8 & 0xffffffffffffff00 | (ulonglong)*(byte *)(param_1 + 10));
  }
  else {
    pauVar4 = (undefined (*) [16])0x0;
  }
  return pauVar4;
}



void win_140001364(longlong **param_1,ulonglong param_2)

{
  longlong *plVar1;
  ulonglong uVar2;
  longlong *plVar3;
  longlong *plVar4;
  longlong *plVar5;
  
  plVar1 = *param_1;
  plVar4 = (longlong *)0x0;
  plVar5 = plVar1;
  if (plVar1 != (longlong *)0x0) {
    do {
      uVar2 = plVar5[2];
      if ((param_2 <= uVar2) &&
         ((plVar4 == (longlong *)0x0 || (uVar2 <= (ulonglong)plVar4[2] && plVar4[2] != uVar2)))) {
        plVar4 = plVar5;
      }
      plVar3 = (longlong *)plVar5[1];
      if (plVar3 == plVar1) {
        if (*plVar5 != 0) {
          plVar5[1] = 0;
        }
        break;
      }
      plVar5 = plVar3;
    } while (plVar3 != (longlong *)0x0);
    if (plVar4 != (longlong *)0x0) {
      if (*param_1 == plVar4) {
        plVar1 = (longlong *)(*param_1)[1];
        *param_1 = plVar1;
        if (plVar1 != (longlong *)0x0) {
          *plVar1 = 0;
        }
      }
      else if (*plVar4 != 0) {
        *(longlong *)(*plVar4 + 8) = plVar4[1];
        if ((longlong *)plVar4[1] != (longlong *)0x0) {
          *(longlong *)plVar4[1] = *plVar4;
        }
      }
      *plVar4 = 0;
      plVar4[1] = 0;
    }
  }
  return;
}



ulonglong win_1400013f0(longlong param_1,ulonglong param_2)

{
  undefined8 *puVar1;
  longlong lVar2;
  undefined uVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  
  uVar5 = 0;
  uVar3 = KeAcquireSpinLockRaiseToDpc(param_1 + 0x20);
  *(undefined *)(param_1 + 0x28) = uVar3;
  uVar4 = *(ulonglong *)(param_1 + 8);
  do {
    if (uVar4 == 0) {
LAB_14000146c:
      uVar4 = KeReleaseSpinLock(param_1 + 0x20,*(undefined *)(param_1 + 0x28));
      return uVar4 & 0xffffffffffffff00 | uVar5;
    }
    if ((uVar4 <= param_2) && (param_2 < uVar4 + 0x20 + *(longlong *)(uVar4 + 0x10))) {
      puVar1 = (undefined8 *)(param_2 - 0x20);
      *(undefined4 *)(param_2 - 8) = 0x504a41;
      lVar2 = *(longlong *)(param_1 + 0x10);
      *puVar1 = 0;
      if (lVar2 == 0) {
        *(undefined8 *)(param_2 - 0x18) = 0;
      }
      else {
        *(longlong *)(param_2 - 0x18) = lVar2;
        **(undefined8 **)(param_1 + 0x10) = puVar1;
      }
      *(undefined8 **)(param_1 + 0x10) = puVar1;
      uVar5 = 1;
      *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 1;
      goto LAB_14000146c;
    }
    uVar4 = *(ulonglong *)(uVar4 + 8);
  } while( true );
}



void win_delay(int param_1)

{
  longlong local_res10 [3];
  
  local_res10[0] = (longlong)(param_1 * -10000);
  KeDelayExecutionThread(0,0,local_res10);
  return;
}



// WARNING: Removing unreachable block (ram,0x0001400015a9)
// WARNING: Removing unreachable block (ram,0x00014000152e)

void get_cpuid(int *param_1)

{
  longlong lVar1;
  int *piVar2;
  int iVar3;
  byte bVar4;
  char cVar5;
  int iVar6;
  size_t sVar7;
  undefined auStack88 [32];
  undefined4 local_38;
  undefined4 uStack52;
  undefined4 uStack48;
  undefined4 uStack44;
  undefined4 uStack40;
  undefined4 uStack36;
  undefined4 uStack32;
  undefined4 local_1c;
  ulonglong local_18;
  
  local_18 = DAT_1400081b0 ^ (ulonglong)auStack88;
  if (*param_1 == 0) {
    local_1c = 0;
    lVar1 = cpuid_basic_info(0);
    local_38 = *(undefined4 *)(lVar1 + 4);
    uStack52 = *(undefined4 *)(lVar1 + 8);
    uStack48 = *(undefined4 *)(lVar1 + 0xc);
    iVar6 = -1;
    sVar7 = 0xffffffffffffffff;
    uStack44 = 0;
    uStack40 = 0;
    uStack36 = 0;
    uStack32 = 0;
    do {
      sVar7 = sVar7 + 1;
    } while (PTR_s_AuthenticAMD_1400080a8[sVar7] != '\0');
    iVar3 = strncmp((char *)&local_38,PTR_s_AuthenticAMD_1400080a8,sVar7);
    if (iVar3 == 0) {
      *param_1 = 2;
      iVar6 = 2;
    }
    else {
      sVar7 = 0xffffffffffffffff;
      do {
        sVar7 = sVar7 + 1;
      } while (PTR_s_GenuineIntel_1400080b0[sVar7] != '\0');
      iVar3 = strncmp((char *)&local_38,PTR_s_GenuineIntel_1400080b0,sVar7);
      if (iVar3 == 0) {
        *param_1 = 1;
        iVar6 = 1;
      }
      else {
        *param_1 = -1;
      }
    }
    piVar2 = (int *)cpuid_Version_info(1);
    iVar3 = *piVar2;
    cVar5 = ((byte)((uint)iVar3 >> 8) & 0xf) + (char)(iVar3 >> 0x14);
    bVar4 = (char)((uint)iVar3 >> 0x10) << 4 | (byte)(iVar3 >> 4) & 0xf;
    if (iVar6 == 1) {
      if (cVar5 == '\x06') {
        if ((bVar4 + 0xb2 & 0xef) == 0) {
          *param_1 = 0x10001;
        }
        if ((bVar4 + 0x72 & 0xef) == 0) {
          *param_1 = 0x20001;
        }
      }
    }
    else if (iVar6 == 2) {
      if (cVar5 == '\x15') {
        if ((byte)(bVar4 + 0xa0) < 0x10) {
          *param_1 = 0x30002;
        }
        else if ((byte)(bVar4 + 0x90) < 0x10) {
          *param_1 = 0x40002;
        }
      }
      else if (cVar5 == '\x16') {
        if (bVar4 < 0x10) {
          *param_1 = 0x10002;
        }
        else if ((byte)(bVar4 - 0x30) < 0x10) {
          *param_1 = 0x20002;
        }
      }
      else if (cVar5 == '\x17') {
        *param_1 = 0x50002;
      }
      else if ((cVar5 == '\x19') && ((byte)(bVar4 + 0xb0) < 0x10)) {
        *param_1 = 0x60002;
      }
    }
  }
  FUN_140005a70(local_18 ^ (ulonglong)auStack88);
  return;
}



ulonglong asf_master_en(longlong param_1)

{
  byte bVar1;
  uint uVar2;
  ulonglong uVar3;
  
  uVar3 = get_cpuid((int *)(param_1 + 0x20));
  if ((int)uVar3 == 0x10002) {
    out(0xcd6,0x28);
    bVar1 = in(0xcd7);
    out(0xcd6,0x28);
    bVar1 = bVar1 & 0xfb | 1;
    uVar3 = uVar3 & 0xffffffffffffff00 | (ulonglong)bVar1;
    out(0xcd7,bVar1);
  }
  else {
    uVar2 = (int)uVar3 - 0x20002;
    uVar3 = (ulonglong)uVar2;
    if ((uVar2 < 0x40001) && (uVar3 = (ulonglong)(ushort)uVar2, (uVar2 & 0xffff) == 0)) {
      if (*(char *)(param_1 + 0xd0) == (char)uVar2) {
        out(0xcd6,2);
        bVar1 = in(0xcd7);
        out(0xcd6,2);
        uVar3 = (ulonglong)(CONCAT11((char)(uVar2 >> 8),bVar1) & 0xfffe);
        out(0xcd7,bVar1 & 0xfe);
      }
      else {
        uVar3 = *(ulonglong *)(param_1 + 0xd8);
        *(byte *)(uVar3 + 2) = *(byte *)(*(longlong *)(param_1 + 0xd8) + 2) & 0xfe;
      }
    }
  }
  return uVar3;
}



void FUN_140001730(longlong param_1)

{
                    // WARNING: Could not recover jumptable at 0x000140006130. Too many branches
                    // WARNING: Treating indirect jump as call
  (**(code **)(param_1 + 10))
            (*(undefined8 *)(param_1 + 0x12),*(undefined *)(param_1 + 0x1a),
             *(undefined2 *)(param_1 + 0x1c));
  return;
}



ulonglong FUN_140001750(longlong param_1,byte *param_2)

{
  byte bVar1;
  undefined2 uVar2;
  ulonglong in_RAX;
  
  bVar1 = *param_2;
  if ((*(byte *)(param_1 + 8) < bVar1 || *(byte *)(param_1 + 8) == bVar1) &&
     (bVar1 <= *(byte *)(param_1 + 9))) {
    *(byte *)(param_1 + 0x1a) = bVar1;
    uVar2 = *(undefined2 *)(param_2 + 2);
    *(undefined2 *)(param_1 + 0x1c) = uVar2;
    return CONCAT71((uint7)(byte)((ushort)uVar2 >> 8),1);
  }
  return in_RAX & 0xffffffffffffff00;
}



undefined8
FUN_14000177c(longlong param_1,uint param_2,undefined8 param_3,uint param_4,undefined4 param_5,
             int param_6,undefined4 param_7,undefined8 param_8)

{
  undefined8 uVar1;
  
  if (((param_2 < 0x18) && (param_4 < 0x18)) || (param_6 == 0)) {
    uVar1 = 0xc000009a;
  }
  else {
    uVar1 = FUN_140004b94((undefined4 *)(astruct_8 *)(param_1 + 0x60),param_2,param_3,param_4,
                          param_5,param_6,param_7,param_8);
    if (-1 < (int)uVar1) {
      cleanup_data_bank_and_restart_slave((astruct_8 *)(param_1 + 0x60));
      uVar1 = 0;
    }
  }
  return uVar1;
}



undefined8
FUN_1400017ec(longlong param_1,undefined4 *param_2,undefined8 *param_3,undefined4 *param_4,
             undefined4 *param_5,undefined4 *param_6)

{
  undefined8 uVar1;
  
  uVar1 = FUN_140004bc0((undefined4 *)(param_1 + 0x60),param_2,param_3,param_4,param_5,param_6,
                        (undefined4 *)&stack0x00000038);
  if (-1 < (int)uVar1) {
    uVar1 = 0;
  }
  return uVar1;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

ulonglong FUN_1400019c0(longlong param_1)

{
  char cVar1;
  uint uVar2;
  undefined7 extraout_var;
  ulonglong uVar4;
  int iVar3;
  
  cVar1 = smbus_trans((astruct_9 *)(param_1 + 0x60));
  iVar3 = (int)CONCAT71(extraout_var,cVar1);
  uVar2 = iVar3 - 1;
  uVar4 = (ulonglong)uVar2;
  if (uVar2 == 0) {
LAB_140001a1a:
    uVar4 = uVar4 & 0xffffffffffffff00;
  }
  else {
    uVar2 = iVar3 - 2;
    uVar4 = (ulonglong)uVar2;
    if (uVar2 != 0) {
      if (uVar2 != 1) goto LAB_140001a1a;
      if ((*(char *)(param_1 + 1) != '\0') && (*(int *)(param_1 + 0x90) == 3)) {
        *(undefined *)(param_1 + 2) = 1;
      }
      uVar4 = (**(code **)(DAT_140008608 + 0x470))();
    }
    uVar4 = CONCAT71((int7)(uVar4 >> 8),1);
  }
  return uVar4;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

undefined FUN_140001a24(longlong param_1,undefined8 param_2,int param_3,byte *param_4,
                       ulonglong param_5,undefined8 *param_6,ulonglong param_7)

{
  undefined uVar1;
  byte bVar2;
  char cVar3;
  undefined7 extraout_var;
  ulonglong uVar4;
  undefined8 uVar5;
  longlong lVar6;
  byte bVar7;
  int iVar8;
  int iVar9;
  byte bVar10;
  
  if ((((param_5 == 0) || (param_4 == (byte *)0x0)) || (param_7 == 0)) ||
     (param_6 == (undefined8 *)0x0)) {
LAB_140001b5f:
    uVar1 = FUN_140002608(param_1);
    return uVar1;
  }
  if ((param_3 != 0x53592004) && (param_3 != 0x53592007)) {
    if (param_3 == 0x5359200b) {
      if ((0x11 < param_5) && (7 < param_7)) {
        if ((*param_4 < 0x80) &&
           (((param_4[1] < 0x80 && (*param_4 <= param_4[1])) && (*(longlong *)(param_4 + 2) != 0))))
        {
          uVar5 = FUN_1400042e8(param_1,(longlong)FUN_140001730,
                                (undefined8 *)&stack0xffffffffffffffd8,0x20);
          *param_6 = uVar5;
        }
        uVar1 = FUN_140002608(param_1);
        return uVar1;
      }
    }
    else if (param_3 == 0x5359200f) {
      if (param_5 == 8) {
        lVar6 = (**(code **)(DAT_140008608 + 0x650))();
        *(byte **)(lVar6 + 8) = param_4;
        (**(code **)(DAT_140008608 + 0xbe0))();
        return 1;
      }
    }
    else if (param_3 == 0x53592013) {
      if (0x16 < param_7) {
        *(undefined4 *)param_6 = 0x12010;
        *(undefined *)((longlong)param_6 + 4) = 0;
      }
    }
    else if (param_3 == 0x535924a4) {
      if (4 < param_7) {
        bVar2 = FUN_140002838(param_1);
        *(int *)param_6 = (int)CONCAT71(extraout_var,bVar2);
        uVar1 = 0;
        if (*(int *)(param_1 + 0x70) == 0) {
          if (*(undefined **)(param_1 + 0x68) != (undefined *)0x0) {
            uVar1 = **(undefined **)(param_1 + 0x68);
          }
        }
        else {
          uVar1 = in((short)*(undefined4 *)(param_1 + 0x74));
        }
        *(undefined *)((longlong)param_6 + 4) = uVar1;
        uVar1 = FUN_140002608(param_1);
        return uVar1;
      }
    }
    else if ((param_3 == 0x53593004) || (param_3 == 0x53593007)) {
      if (param_5 == 0x24) {
        if (param_7 < 0x24) goto LAB_140001b5f;
        *(undefined4 *)(param_1 + 0x94) = 1;
      }
      else {
        if ((param_5 < 0x45) || (param_7 < 0x45)) goto LAB_140001b5f;
        *(undefined4 *)(param_1 + 0x94) = 2;
      }
      if (*(int *)(param_1 + 0x94) == 1) {
        uVar4 = (ulonglong)param_4[3] + 4;
      }
      else {
        uVar4 = (ulonglong)param_4[4] + 5;
      }
      if ((uVar4 <= (param_5 & 0xffffffff)) && (*(int *)(param_1 + 0x90) == 1)) {
        if (param_4[2] < 0x80) {
          if (param_4[1] == 0x10) {
            iVar8 = 1;
            bVar2 = 0;
            if (*(int *)(param_1 + 0x94) == 1) {
              bVar10 = param_4[3];
              bVar7 = param_4[4];
            }
            else {
              bVar10 = param_4[4];
              bVar7 = param_4[3];
            }
          }
          else {
            if (param_4[1] != 0x11) {
              *(undefined *)param_6 = 0x19;
              goto LAB_140001e7c;
            }
            iVar8 = 2;
            bVar7 = param_4[3];
            if (*(int *)(param_1 + 0x94) == 1) {
              bVar10 = 0;
              bVar2 = bVar7;
              bVar7 = 0;
            }
            else {
              bVar2 = 0x40;
              bVar10 = 0;
            }
          }
          cVar3 = FUN_1400022a8(param_1,(longlong)param_4,(undefined *)param_6,iVar8,bVar7,bVar10,
                                bVar2);
          if (cVar3 != '\0') {
            return 1;
          }
          return 0;
        }
        *(undefined *)param_6 = 0x10;
      }
LAB_140001e7c:
      FUN_140002608(param_1);
      return 1;
    }
    goto LAB_140001b5f;
  }
  if ((param_5 != 0x25) || (param_7 != 0x25)) goto LAB_140001b5f;
  if (*(int *)(param_1 + 0x90) != 1) goto LAB_140001b83;
  if (0x7f < param_4[2]) {
    *(undefined *)param_6 = 0x10;
    goto LAB_140001b83;
  }
  bVar2 = param_4[1];
  bVar7 = bVar2 & 0x7f;
  iVar8 = 1;
  if (bVar7 < 7) {
    if (bVar7 == 6) {
      if (param_4[4] == 2) {
        uVar1 = 0;
        bVar7 = 2;
        iVar8 = 4;
        iVar9 = 1;
        goto LAB_140001dae;
      }
    }
    else if ((bVar2 & 0x7f) == 0) {
      if (param_4[4] == 0) {
        uVar1 = 0;
        bVar7 = 0;
        iVar9 = 1;
        goto LAB_140001dae;
      }
    }
    else if (bVar7 != 1) {
      if (bVar7 == 2) {
        if (param_4[4] == 1) {
          uVar1 = 0;
          bVar7 = 0;
          iVar8 = 2;
          iVar9 = 1;
          goto LAB_140001dae;
        }
      }
      else if (bVar7 == 3) {
        if (param_4[4] == 0) {
          uVar1 = 1;
          iVar8 = 2;
LAB_140001da6:
          bVar7 = 0;
          iVar9 = 2;
LAB_140001dae:
          cVar3 = FUN_1400023bc(param_1,(longlong)param_4,(undefined *)param_6,iVar8,iVar9,
                                (bVar2 >> 7) + 1,bVar7,uVar1);
          if (cVar3 != '\0') {
            return 1;
          }
          return 0;
        }
      }
      else if (bVar7 == 4) {
        if (param_4[4] == 1) {
          uVar1 = 0;
          bVar7 = 1;
          iVar8 = 3;
          iVar9 = 1;
          goto LAB_140001dae;
        }
      }
      else if ((bVar7 == 5) && (param_4[4] == 0)) {
        uVar1 = 1;
        iVar8 = 3;
        goto LAB_140001da6;
      }
    }
  }
  else if (bVar7 == 7) {
    if (param_4[4] == 0) {
      uVar1 = 2;
      iVar8 = 4;
      goto LAB_140001da6;
    }
  }
  else if (bVar7 == 8) {
    bVar7 = param_4[4];
    if ((byte)(bVar7 - 1) < 0x20) {
      uVar1 = 0;
      iVar8 = 6;
      iVar9 = 1;
      goto LAB_140001dae;
    }
  }
  else if (bVar7 == 9) {
    if (param_4[4] == 0) {
      uVar1 = 0x20;
      iVar8 = 6;
      goto LAB_140001da6;
    }
  }
  else if (bVar7 == 10) {
    if (param_4[4] == 2) {
      uVar1 = 2;
      bVar7 = 2;
      iVar8 = 5;
      iVar9 = 1;
      goto LAB_140001dae;
    }
  }
  else if ((bVar7 == 0xb) && (bVar7 = param_4[4], (byte)(bVar7 - 1) < 0x20)) {
    uVar1 = 0x20;
    iVar8 = 7;
    iVar9 = 1;
    goto LAB_140001dae;
  }
  *(undefined *)param_6 = 0x19;
LAB_140001b83:
  FUN_140002608(param_1);
  return 1;
}



void FUN_140001fdc(longlong param_1)

{
  FUN_140002608(param_1);
  return;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

bool acquire_host_semaphore
               (astruct_3 *param_1,int param_2,int param_3,undefined4 param_4,undefined param_5,
               undefined param_6,undefined param_7,undefined8 param_8,undefined param_9,
               undefined8 param_10,undefined8 param_11,undefined *param_12,undefined4 param_13)

{
  byte bVar1;
  char cVar2;
  
  if (param_1->use_mmio == 0) {
    if (param_1->mmio_addr != 0) {
      *(undefined *)(param_1->mmio_addr + 0x14) = 1;
      LOCK();
    }
  }
  else {
    out((short)param_1->base_addr + 0x14,1);
  }
  if (param_1->use_mmio == 0) {
    if (param_1->mmio_addr == 0) goto LAB_140002283;
    bVar1 = *(byte *)(param_1->mmio_addr + 0x14);
  }
  else {
    bVar1 = in((short)param_1->base_addr + 0x14);
  }
  if ((bVar1 & 1) == 0) {
LAB_140002283:
    *param_12 = 0x1a;
    FUN_140002608((longlong)param_1);
    return true;
  }
  if (param_2 != 1) {
    if (((param_2 != 2) && (param_2 != 3)) && (param_2 != 4)) {
      if (param_2 == 5) goto LAB_140002194;
      if (param_2 != 6) {
        if (param_2 == 7) goto LAB_140002194;
        if (param_2 != 8) goto LAB_140002238;
      }
    }
    if ((param_3 != 1) && (param_3 != 2)) goto LAB_140002238;
  }
LAB_140002194:
  param_1->field129_0x98 = param_2;
  param_1->field130_0x9c = param_3;
  param_1->field131_0xa0 = param_4;
  param_1->field_0xa4 = param_5;
  param_1->field_0xa5 = param_6;
  param_1->field_0xa6 = param_7;
  param_1->field_0xa7 = 0;
  param_1->field136_0xa8 = param_8;
  param_1->field_0xb0 = param_9;
  param_1->field_0xb1 = 0;
  param_1->field145_0xb8 = param_10;
  param_1->field146_0xc0 = param_11;
  param_1->field147_0xc8 = param_12;
  param_1->field148_0xd0 = param_13;
  param_1->field124_0x90 = 2;
LAB_140002238:
  FUN_140004a6c();
  cVar2 = (**(code **)(DAT_140008608 + 0x478))();
  return cVar2 != '\0';
}



undefined FUN_1400022a8(longlong param_1,longlong param_2,undefined *param_3,int param_4,
                       undefined param_5,undefined param_6,byte param_7)

{
  undefined *puVar1;
  undefined uVar2;
  bool bVar3;
  int iVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  
  *param_3 = 0x13;
  puVar5 = (undefined *)(param_2 + 4);
  puVar1 = param_3 + 4;
  param_3[1] = *(undefined *)(param_2 + 1);
  param_3[2] = *(undefined *)(param_2 + 2);
  uVar2 = *(undefined *)(param_2 + 2);
  if (*(int *)(param_1 + 0x94) == 1) {
    param_3[3] = *(undefined *)(param_2 + 3);
    puVar6 = param_3 + 3;
    puVar7 = puVar1;
  }
  else {
    *puVar1 = *puVar5;
    puVar5 = (undefined *)(param_2 + 5);
    puVar7 = param_3 + 5;
    puVar6 = puVar1;
  }
  if (param_4 == 1) {
    iVar4 = 0x45;
    if (*(int *)(param_1 + 0x94) == 1) {
      iVar4 = 0x24;
    }
  }
  else {
    if (param_4 != 2) {
      FUN_140002608(param_1);
      return 1;
    }
    if (*(int *)(param_1 + 0x94) == 1) {
      iVar4 = param_7 + 4;
    }
    else {
      iVar4 = param_7 + 5;
    }
  }
  bVar3 = acquire_host_semaphore
                    ((astruct_3 *)param_1,8,param_4,1,uVar2,param_5,param_6,puVar5,param_7,puVar6,
                     puVar7,param_3,iVar4);
  return bVar3;
}



void FUN_1400023bc(longlong param_1,longlong param_2,undefined *param_3,int param_4,int param_5,
                  undefined4 param_6,undefined param_7,undefined param_8)

{
  *param_3 = 7;
  param_3[1] = *(undefined *)(param_2 + 1);
  param_3[2] = *(undefined *)(param_2 + 2);
  param_3[3] = *(undefined *)(param_2 + 3);
  acquire_host_semaphore
            ((astruct_3 *)param_1,param_4,param_5,param_6,*(undefined *)(param_2 + 2),
             *(undefined *)(param_2 + 3),param_7,param_2 + 5,param_8,param_3 + 4,param_3 + 5,param_3
             ,0x25);
  return;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

void FUN_140002460(void)

{
  (**(code **)(DAT_140008608 + 0x478))();
  return;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

void FUN_1400024a8(void)

{
  uint uVar1;
  longlong lVar2;
  uint uVar3;
  
  (**(code **)(DAT_140008608 + 0x478))();
  uVar1 = (**(code **)(DAT_140008608 + 0x70))();
  uVar3 = 0;
  if (uVar1 != 0) {
    do {
      (**(code **)(DAT_140008608 + 0x90))();
      (**(code **)(DAT_140008608 + 0x388))();
      lVar2 = (**(code **)(DAT_140008608 + 0x650))();
      uVar3 = uVar3 + 1;
      *(undefined4 *)(lVar2 + 0x10) = 1;
    } while (uVar3 < uVar1);
  }
  return;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

void FUN_140002608(longlong param_1)

{
  (**(code **)(DAT_140008608 + 0x9e0))();
  (**(code **)(DAT_140008608 + 0xa00))();
  if (*(longlong *)(param_1 + 0x20) == 0) {
    (**(code **)(DAT_140008608 + 0x9e8))();
  }
  else {
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(undefined *)(param_1 + 2) = 0;
    *(undefined *)(param_1 + 1) = 0;
    (**(code **)(DAT_140008608 + 0x9e8))();
    (**(code **)(DAT_140008608 + 0x848))();
  }
  return;
}



undefined8 FUN_1400026f0(longlong param_1)

{
  undefined8 uVar1;
  
  uVar1 = FUN_140004c30((undefined4 *)(param_1 + 0x60));
  if (-1 < (int)uVar1) {
    *(undefined4 *)(param_1 + 0x148) = 1;
    *(undefined4 *)(param_1 + 0x14c) = 1;
    *(undefined4 *)(param_1 + 0x94) = 0;
    *(undefined4 *)(param_1 + 0x98) = 0;
    *(undefined4 *)(param_1 + 0x9c) = 0;
    *(undefined4 *)(param_1 + 0xa0) = 0;
    *(undefined *)(param_1 + 0xa4) = 0xff;
    *(undefined *)(param_1 + 0xa5) = 0;
    *(undefined *)(param_1 + 0xa6) = 0;
    *(undefined *)(param_1 + 0xa7) = 0;
    *(undefined8 *)(param_1 + 0xa8) = 0;
    *(undefined *)(param_1 + 0xb0) = 0;
    *(undefined *)(param_1 + 0xb1) = 0;
    *(undefined8 *)(param_1 + 0xb8) = 0;
    *(undefined8 *)(param_1 + 0xc0) = 0;
    *(undefined8 *)(param_1 + 200) = 0;
    *(undefined4 *)(param_1 + 0x90) = 1;
    *(undefined4 *)(param_1 + 0xd8) = 1;
    uVar1 = 0;
  }
  return uVar1;
}



longlong restart_slave_and_listen_broadcast(astruct_5 *param_1)

{
  byte bVar1;
  ulonglong in_RAX;
  ulonglong uVar2;
  
  if (param_1->use_mmio == 0) {
    uVar2 = param_1->mmio_addr;
    if (uVar2 == 0) {
      bVar1 = 0;
    }
    else {
      bVar1 = *(byte *)(uVar2 + 0x15);
    }
  }
  else {
    bVar1 = in((short)param_1->base_addr + 0x15);
    uVar2 = in_RAX & 0xffffffffffffff00;
  }
  uVar2 = uVar2 & 0xffffffffffffff00;
  if (param_1->use_mmio == 0) {
    if (param_1->mmio_addr != 0) {
      *(byte *)(param_1->mmio_addr + 0x15) = bVar1 | 0x10;
      LOCK();
    }
  }
  else {
    out((short)param_1->base_addr + 0x15,bVar1 | 0x10);
  }
  if (param_1->use_mmio == 0) {
    uVar2 = param_1->mmio_addr;
    if (uVar2 != 0) {
      *(byte *)(uVar2 + 0x15) = bVar1 & 0xef;
      LOCK();
    }
  }
  else {
    out((short)param_1->base_addr + 0x15,bVar1 & 0xef);
  }
  if (param_1->use_mmio == 0) {
    uVar2 = param_1->mmio_addr;
    if (uVar2 != 0) {
      *(undefined *)(uVar2 + 9) = 0x11;
      LOCK();
    }
  }
  else {
    uVar2 = CONCAT71((int7)(uVar2 >> 8),0x11);
    out((short)param_1->base_addr + 9,0x11);
  }
  param_1->field107_0x78 = 2;
  return uVar2;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

byte FUN_140002838(longlong param_1)

{
  char cVar1;
  char cVar2;
  char cVar3;
  
  (**(code **)(DAT_140008608 + 0x9e0))();
  cVar1 = *(char *)(param_1 + 1);
  cVar2 = *(char *)(param_1 + 2);
  cVar3 = *(char *)(param_1 + 3);
  (**(code **)(DAT_140008608 + 0x9e8))();
  return -(cVar3 != '\0') & 4U | -(cVar2 != '\0') & 2U | cVar1 != '\0';
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

ulonglong FUN_1400028b4(longlong param_1)

{
  bool bVar1;
  ulonglong uVar2;
  
  bVar1 = false;
  do {
    (**(code **)(DAT_140008608 + 0x9e0))();
    if ((*(char *)(param_1 + 1) == '\0') || (*(char *)(param_1 + 2) != '\0')) {
      *(undefined *)(param_1 + 3) = 1;
      bVar1 = true;
    }
    uVar2 = (**(code **)(DAT_140008608 + 0x9e8))();
  } while (!bVar1);
  return uVar2 & 0xffffffffffffff00 | (ulonglong)(*(char *)(param_1 + 1) == '\0');
}



ulonglong FUN_140002930(ulonglong *param_1)

{
  int iVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  bool bVar4;
  
  iVar1 = *(int *)(*param_1 + 0x90);
  uVar3 = 0;
  *(bool *)(param_1 + 1) = iVar1 == 3;
  if (iVar1 == 3) {
    uVar2 = *param_1;
    *(undefined4 *)(uVar2 + 0x94) = 0;
    *(undefined4 *)(uVar2 + 0x98) = 0;
    *(undefined4 *)(uVar2 + 0x9c) = 0;
    *(undefined4 *)(uVar2 + 0xa0) = 0;
    *(undefined *)(uVar2 + 0xa4) = 0xff;
    *(undefined *)(uVar2 + 0xa5) = 0;
    *(undefined *)(uVar2 + 0xa6) = 0;
    *(undefined *)(uVar2 + 0xa7) = 0;
    *(undefined8 *)(uVar2 + 0xa8) = 0;
    *(undefined *)(uVar2 + 0xb0) = 0;
    *(undefined *)(uVar2 + 0xb1) = 0;
    *(undefined8 *)(uVar2 + 0xb8) = 0;
    *(undefined8 *)(uVar2 + 0xc0) = 0;
    *(undefined8 *)(uVar2 + 200) = 0;
    *(undefined4 *)(uVar2 + 0x90) = 1;
  }
  bVar4 = *(int *)(*param_1 + 0xd8) == 3;
  uVar2 = *param_1 & 0xffffffffffffff00;
  *(bool *)((longlong)param_1 + 9) = bVar4;
  if (bVar4) {
    uVar2 = *param_1;
    *(undefined4 *)(uVar2 + 0xd8) = 4;
  }
  if ((*(char *)(param_1 + 1) != '\0') || (*(char *)((longlong)param_1 + 9) != '\0')) {
    uVar3 = 1;
  }
  return uVar2 & 0xffffffffffffff00 | uVar3;
}



ulonglong FUN_1400029d0(longlong param_1)

{
  ulonglong uVar1;
  
  if (*(int *)(param_1 + 0x14c) == 2) {
    uVar1 = process_host_notify((astruct_10 *)(param_1 + 0x60));
    if ((char)uVar1 == '\0') {
      *(int *)(param_1 + 0x10c) = *(int *)(param_1 + 0x10c) + 1;
LAB_1400050d4:
      *(undefined4 *)(param_1 + 0xd8) = 2;
      return CONCAT71((int7)(uVar1 >> 8),1);
    }
    *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + 1;
    uVar1 = (ulonglong)*(uint *)(param_1 + 0x114);
    *(uint *)(param_1 + 0x114) =
         (int)*(undefined8 *)(param_1 + 0x120) + 1 + *(uint *)(param_1 + 0x114);
  }
  else {
    uVar1 = process_host_notify((astruct_10 *)(param_1 + 0x60));
    if ((char)uVar1 == '\0') goto LAB_1400050d4;
  }
  return uVar1 & 0xffffffffffffff00;
}



undefined stop_listen_broadcast(astruct_6 *param_1)

{
  param_1->field203_0xd8 = 1;
  if (param_1->use_mmio == 0) {
    if (param_1->mmio_addr != 0) {
      *(undefined *)(param_1->mmio_addr + 9) = 0x10;
      LOCK();
    }
  }
  else {
    out((short)param_1->base_addr + 9,0x10);
  }
  return 1;
}



undefined8 FUN_140002a30(longlong param_1)

{
  longlong lVar1;
  
  lVar1 = restart_slave_and_listen_broadcast((astruct_5 *)(param_1 + 0x60));
  return CONCAT71((int7)((ulonglong)lVar1 >> 8),1);
}



ulonglong smbus_trans_start(astruct *dev)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  undefined *puVar4;
  ulonglong uVar5;
  undefined *puVar6;
  undefined uVar7;
  byte bVar8;
  
  puVar6 = &dev->field_0x60;
  iVar2 = dev->field133_0x98;
  if (iVar2 == 2) {
    uVar7 = 0x44;
LAB_1400057ab:
    bVar8 = dev->field139_0xa4 * '\x02';
    if (dev->field134_0x9c != 1) {
      if (dev->field134_0x9c != 2) goto LAB_140005777;
      bVar8 = bVar8 | 1;
    }
    piVar1 = &dev->field115_0x80;
    dev->field189_0xe4 = dev->field189_0xe4 + 1;
    iVar2 = get_cpuid(piVar1);
    if ((iVar2 - 0x10002U < 0x50001) && ((iVar2 - 0x10002U & 0xffff) == 0)) {
      asf_sm_master_en((longlong)puVar6);
    }
    if (dev->use_io == 0) {
      if (dev->mmio_addr != 0) {
        *(undefined *)(dev->mmio_addr + 0x13) = 0x80;
        LOCK();
      }
    }
    else {
      out((short)dev->base_addr + 0x13,0x80);
    }
    if (dev->use_io == 0) {
      if (dev->mmio_addr != 0) {
        *(byte *)(dev->mmio_addr + 4) = bVar8;
        LOCK();
      }
    }
    else {
      out((short)dev->base_addr + 4,bVar8);
    }
    if (dev->use_io == 0) {
      if (dev->mmio_addr != 0) {
        *(undefined *)(dev->mmio_addr + 3) = dev->field_0xa5;
        LOCK();
      }
    }
    else {
      out((short)dev->base_addr + 3,dev->field_0xa5);
    }
    iVar2 = dev->field133_0x98;
    if ((((iVar2 == 2) || (iVar2 == 3)) || (iVar2 == 4)) || (iVar2 == 5)) {
      bVar8 = dev->field141_0xa6;
      if (bVar8 != 0) {
        if (bVar8 != 1) {
          if (bVar8 != 2) goto LAB_140005962;
          if (dev->use_io == 0) {
            if (dev->mmio_addr != 0) {
              *(undefined *)(dev->mmio_addr + 6) = dev->field143_0xa8[1];
              LOCK();
            }
          }
          else {
            out((short)dev->base_addr + 6,dev->field143_0xa8[1]);
          }
        }
        if (dev->use_io == 0) {
          if (dev->mmio_addr != 0) {
            *(undefined *)(dev->mmio_addr + 5) = *dev->field143_0xa8;
            LOCK();
          }
        }
        else {
          out((short)dev->base_addr + 5,*dev->field143_0xa8);
        }
      }
    }
    else {
      if ((iVar2 != 6) && (iVar2 != 7)) {
LAB_140005962:
        *dev->field168_0xc8 = 7;
        dev->field128_0x90 = 3;
        iVar2 = get_cpuid(piVar1);
        uVar3 = iVar2 - 0x10002;
        puVar4 = (undefined *)(ulonglong)uVar3;
        if ((uVar3 < 0x50001) &&
           (puVar4 = (undefined *)(ulonglong)(ushort)uVar3, (uVar3 & 0xffff) == 0)) {
          puVar4 = (undefined *)asf_master_en((longlong)puVar6);
        }
        goto LAB_140005788;
      }
      if (dev->use_io != 0) {
        in((short)dev->base_addr + 2);
      }
      if (dev->field141_0xa6 != 0) {
        if (dev->use_io == 0) {
          if (dev->mmio_addr != 0) {
            *(byte *)(dev->mmio_addr + 5) = dev->field141_0xa6;
            LOCK();
          }
        }
        else {
          out((short)dev->base_addr + 5,dev->field141_0xa6);
        }
        bVar8 = 0;
        if (dev->field141_0xa6 != 0) {
          do {
            if (dev->use_io == 0) {
              if (dev->mmio_addr != 0) {
                *(undefined *)(dev->mmio_addr + 7) = dev->field143_0xa8[bVar8];
                LOCK();
              }
            }
            else {
              out((short)dev->base_addr + 7,dev->field143_0xa8[bVar8]);
            }
            bVar8 = bVar8 + 1;
          } while (bVar8 < dev->field141_0xa6);
        }
      }
    }
    iVar2 = get_cpuid(piVar1);
    uVar3 = iVar2 - 0x10002;
    uVar5 = (ulonglong)uVar3;
    if ((uVar3 < 0x50001) && (uVar5 = (ulonglong)(ushort)uVar3, (uVar3 & 0xffff) == 0)) {
      uVar5 = asf_sm_master_en((longlong)puVar6);
    }
    if (dev->use_io == 0) {
      uVar5 = dev->mmio_addr;
      if (uVar5 != 0) {
        *(undefined *)(uVar5 + 2) = uVar7;
        LOCK();
      }
    }
    else {
      uVar5 = uVar5 & 0xffffffffffffff00;
      out((short)dev->base_addr + 2,uVar7);
    }
    uVar5 = uVar5 & 0xffffffffffffff00;
  }
  else {
    if (iVar2 == 3) {
      uVar7 = 0x48;
      goto LAB_1400057ab;
    }
    if (iVar2 == 4) {
      uVar7 = 0x4c;
      goto LAB_1400057ab;
    }
    if (iVar2 == 5) {
      uVar7 = 0x50;
      goto LAB_1400057ab;
    }
    if (iVar2 == 6) {
      uVar7 = 0x54;
      goto LAB_1400057ab;
    }
    if (iVar2 == 7) {
      uVar7 = 0x58;
      goto LAB_1400057ab;
    }
LAB_140005777:
    puVar4 = dev->field168_0xc8;
    *puVar4 = 7;
    dev->field128_0x90 = 3;
LAB_140005788:
    uVar5 = CONCAT71((int7)((ulonglong)puVar4 >> 8),1);
  }
  return uVar5;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

void FUN_140002a5c(undefined8 param_1,undefined8 param_2)

{
  int iVar1;
  undefined auStack248 [32];
  int *local_d8;
  undefined *local_d0;
  undefined *local_c8;
  int local_b8;
  undefined local_b4 [4];
  undefined local_b0 [8];
  undefined local_a8 [8];
  undefined local_a0 [8];
  undefined4 local_98;
  undefined8 *local_90;
  undefined4 local_88;
  undefined4 *local_80;
  undefined8 local_78 [2];
  undefined4 local_68;
  undefined4 uStack100;
  undefined4 uStack96;
  undefined4 uStack92;
  undefined4 local_58;
  undefined4 uStack84;
  undefined4 uStack80;
  undefined4 uStack76;
  undefined4 local_48;
  undefined4 uStack68;
  undefined4 uStack64;
  undefined4 uStack60;
  undefined4 local_38;
  undefined4 uStack52;
  undefined4 uStack48;
  undefined4 uStack44;
  undefined2 local_28;
  ulonglong local_18;
  
  local_18 = DAT_1400081b0 ^ (ulonglong)auStack248;
  local_d0 = local_a8;
  local_b8 = 0;
  local_78[0] = 0x4600440057;
  local_90 = local_78;
  local_68 = 0x640057;
  uStack100 = 0x440066;
  uStack96 = 0x720069;
  uStack92 = 0x630065;
  local_28 = 0;
  local_80 = &local_68;
  local_58 = 0x650074;
  uStack84 = 0x500064;
  uStack80 = 0x77006f;
  uStack76 = 0x720065;
  local_d8 = (int *)0x0;
  local_98 = 0x80006;
  local_48 = 0x720054;
  uStack68 = 0x6e0061;
  uStack64 = 0x690073;
  uStack60 = 0x690074;
  local_38 = 0x6e006f;
  uStack52 = 0x6e0045;
  uStack48 = 0x620061;
  uStack44 = 0x65006c;
  local_88 = 0x420040;
  iVar1 = (**(code **)(DAT_140008608 + 0x180))();
  if (-1 < iVar1) {
    local_d0 = local_a0;
    local_d8 = (int *)0x0;
    iVar1 = (**(code **)(DAT_140008608 + 0x728))();
    if (-1 < iVar1) {
      local_c8 = local_b4;
      local_d0 = local_b0;
      local_d8 = &local_b8;
      (**(code **)(DAT_140008608 + 0x758))();
    }
  }
  *(bool *)param_2 = local_b8 != 0;
  FUN_140005a70(local_18 ^ (ulonglong)auStack248);
  return;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

void FUN_140002bd4(longlong param_1,undefined8 param_2)

{
  bool bVar1;
  
  bVar1 = false;
  do {
    (**(code **)(DAT_140008608 + 0x9e0))();
    if (*(char *)(param_1 + 1) == '\0') {
      *(undefined *)(param_1 + 1) = 1;
      bVar1 = true;
      *(undefined8 *)(param_1 + 0x20) = param_2;
    }
    (**(code **)(DAT_140008608 + 0x9e8))();
  } while (!bVar1);
  return;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

void FUN_140002c60(void)

{
  undefined *puVar1;
  
  if ((undefined **)PTR_LOOP_1400080a0 != &PTR_LOOP_1400080a0) {
    puVar1 = PTR_LOOP_1400080a0;
    if (DAT_140008270 == 4) {
      for (; puVar1 != (undefined *)0x0; puVar1 = *(undefined **)(puVar1 + 0x10)) {
        if (*(longlong *)(puVar1 + 0x38) != 0) {
          (*DAT_140008258)();
          *(undefined8 *)(puVar1 + 0x38) = 0;
        }
      }
    }
    else if (DAT_140008270 == 2) {
      IoWMIRegistrationControl(PTR_LOOP_1400080a0,0x80000002);
    }
    PTR_LOOP_1400080a0 = (undefined *)&PTR_LOOP_1400080a0;
  }
  return;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

undefined8 FUN_140002c68(void)

{
  undefined8 uVar1;
  undefined *puVar2;
  undefined8 local_res18;
  
  FUN_140004250(L"SmbDrv\\Parameters\\Debug",L"Mask",&DAT_140008000);
  uVar1 = (**(code **)(DAT_140008608 + 0x3a0))();
  if (-1 < (int)uVar1) {
    puVar2 = (undefined *)(**(code **)(DAT_140008608 + 0x650))();
    FUN_140004720(puVar2,local_res18);
    RtlDeleteRegistryValue(1,L"SmbDrv\\Parameters",L"SmbStopRemove");
    uVar1 = 0;
  }
  return uVar1;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

undefined8 FUN_140002da0(void)

{
  longlong lVar1;
  
  lVar1 = (**(code **)(DAT_140008608 + 0x650))();
  *(undefined4 *)(lVar1 + 0x148) = 2;
  return 0;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

undefined8 FUN_140002e30(undefined8 param_1,int param_2)

{
  longlong lVar1;
  undefined4 uVar2;
  
  lVar1 = (**(code **)(DAT_140008608 + 0x650))();
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
  *(undefined4 *)(lVar1 + 0x148) = uVar2;
  return 0;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

undefined8 FUN_140002ec0(void)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  char *pcVar5;
  ulonglong uVar6;
  longlong lVar7;
  undefined8 uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  undefined8 local_res20;
  
  local_res20 = 0;
  uVar11 = 0;
  uVar14 = 0;
  uVar10 = 0;
  uVar13 = 0;
  iVar12 = 0;
  uVar3 = (**(code **)(DAT_140008608 + 0x980))();
  uVar9 = 0;
  if (uVar3 != 0) {
    do {
      pcVar5 = (char *)(**(code **)(DAT_140008608 + 0x988))();
      cVar1 = *pcVar5;
      if (cVar1 == '\x01') {
        if (((*(int *)(pcVar5 + 8) == 0) && (*(uint *)(pcVar5 + 0xc) != 0)) && (uVar10 == 0)) {
          uVar14 = *(undefined4 *)(pcVar5 + 4);
          uVar10 = *(uint *)(pcVar5 + 0xc);
        }
      }
      else if (cVar1 == '\x02') {
        if (iVar12 == 0) {
          uVar13 = *(undefined4 *)(pcVar5 + 4);
          iVar12 = 1;
        }
      }
      else if (((cVar1 == '\x03') && (uVar2 = *(uint *)(pcVar5 + 0xc), uVar2 != 0)) && (uVar11 == 0)
              ) {
        local_res20 = MmMapIoSpace(*(undefined8 *)(pcVar5 + 4),uVar2,0);
        uVar11 = uVar2;
      }
      uVar9 = uVar9 + 1;
    } while (uVar9 < uVar3);
  }
  uVar6 = win_1400010f8(0x40);
  if ((uVar6 != 0) && (iVar4 = (**(code **)(DAT_140008608 + 0x418))(), iVar4 < 0)) {
    win_140001194(uVar6);
    uVar6 = 0;
  }
  lVar7 = (**(code **)(DAT_140008608 + 0x650))();
  uVar8 = FUN_14000177c(lVar7,uVar11,local_res20,uVar10,uVar14,iVar12,uVar13,uVar6);
  if (-1 < (int)uVar8) {
    uVar8 = 0;
  }
  return uVar8;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

undefined4 FUN_140003090(void)

{
  longlong lVar1;
  undefined4 uVar2;
  int local_res10 [6];
  
  uVar2 = 0;
  lVar1 = (**(code **)(DAT_140008608 + 0x650))();
  if (lVar1 != 0) {
    local_res10[0] = 0;
    FUN_140004250(L"SmbDrv\\Parameters",L"SmbStopRemove",local_res10);
    uVar2 = 0;
    if (local_res10[0] != 0) {
      uVar2 = 0xc0000001;
    }
  }
  return uVar2;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

undefined8 FUN_140003100(void)

{
  longlong lVar1;
  undefined8 uVar2;
  int local_res18 [2];
  undefined4 local_res20 [2];
  undefined4 local_18;
  undefined4 local_14;
  longlong local_10;
  
  lVar1 = (**(code **)(DAT_140008608 + 0x650))();
  local_10 = 0;
  local_res18[0] = 0;
  local_18 = 0;
  local_14 = 0;
  local_res20[0] = 0;
  uVar2 = FUN_1400017ec(lVar1,local_res18,&local_10,&local_14,&local_18,local_res20);
  if (-1 < (int)uVar2) {
    if (local_10 != 0) {
      if (local_res18[0] == 0) {
        return 0xc0000001;
      }
      MmUnmapIoSpace(local_10,local_res18[0]);
    }
    uVar2 = 0;
  }
  return uVar2;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

undefined8 FUN_1400031a0(void)

{
  (**(code **)(DAT_140008608 + 0x650))();
  FUN_140002460();
  if (DAT_1400083d0 != '\0') {
    (**(code **)(DAT_140008608 + 0xdb0))();
  }
  return 0;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

undefined8 FUN_140003220(void)

{
  (**(code **)(DAT_140008608 + 0x650))();
  FUN_140002460();
  return 0;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

undefined8 FUN_140003260(void)

{
  (**(code **)(DAT_140008608 + 0x650))();
  FUN_1400024a8();
  if (DAT_1400083d0 != '\0') {
    (**(code **)(DAT_140008608 + 0xdb0))();
  }
  return 0;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall
// WARNING: Could not reconcile some variable overlaps

void FUN_1400032e0(undefined8 param_1,undefined8 param_2)

{
  int iVar1;
  ulonglong *puVar2;
  undefined *puVar3;
  undefined8 uVar4;
  undefined auStackY1176 [32];
  char local_448 [8];
  ulonglong local_440;
  undefined8 local_438;
  undefined8 local_430;
  undefined8 local_428;
  undefined8 local_420;
  undefined8 local_418;
  undefined8 local_410;
  undefined8 local_408;
  undefined8 local_400;
  undefined4 local_3f8;
  undefined4 *local_3f0;
  undefined4 local_3e8;
  undefined4 *local_3e0;
  undefined local_3d8 [16];
  undefined8 local_3c8;
  undefined local_3c0 [16];
  undefined local_3b0 [16];
  undefined8 local_3a0;
  undefined local_398 [16];
  undefined local_388 [16];
  undefined local_378 [16];
  undefined *local_368;
  undefined local_360 [16];
  undefined local_350 [16];
  undefined local_340 [16];
  undefined8 local_330;
  undefined local_328 [16];
  undefined local_318 [16];
  undefined local_308 [16];
  undefined8 local_2f8;
  undefined local_2f0 [16];
  undefined local_2e0 [16];
  undefined local_2d0 [16];
  undefined8 local_2c0;
  undefined local_2b8 [16];
  undefined local_2a8 [16];
  undefined local_298 [16];
  undefined8 local_288;
  undefined4 local_280;
  undefined local_27c [16];
  undefined4 local_26c;
  undefined4 local_268;
  undefined4 local_264;
  ulonglong local_260;
  undefined8 local_258;
  undefined *local_250;
  undefined4 local_248;
  undefined local_244 [16];
  undefined4 local_234;
  undefined4 local_230;
  undefined4 local_22c;
  ulonglong local_228;
  undefined8 local_220;
  undefined *local_218;
  undefined4 local_208;
  undefined4 local_204;
  undefined4 local_200;
  undefined local_1fb;
  code *local_1f0;
  code *local_1e8;
  code *local_1e0;
  code *local_1d8;
  code *local_1d0;
  undefined4 local_1a8;
  undefined4 local_198;
  undefined local_193;
  code *local_190;
  code *local_188;
  code *local_180;
  code *local_178;
  undefined4 local_14c;
  undefined4 local_138;
  code *local_130;
  code *local_120;
  code *local_110;
  code *local_108;
  code *local_f0;
  code *local_e8;
  code *local_e0;
  code *local_d0;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_80;
  undefined4 uStack124;
  undefined4 uStack120;
  undefined4 uStack116;
  undefined4 local_70;
  undefined4 uStack108;
  undefined4 uStack104;
  undefined4 uStack100;
  undefined4 local_60;
  undefined4 local_58;
  undefined4 uStack84;
  undefined4 uStack80;
  undefined4 uStack76;
  undefined4 local_48;
  undefined4 uStack68;
  undefined4 uStack64;
  undefined4 uStack60;
  undefined8 local_38;
  ulonglong local_30;
  
  local_30 = DAT_1400081b0 ^ (ulonglong)auStackY1176;
  local_60 = 0x72;
  local_3f0 = &local_80;
  local_80 = 0x44005c;
  uStack124 = 0x760065;
  uStack120 = 0x630069;
  uStack116 = 0x5c0065;
  local_3f8 = 0x240022;
  local_70 = 0x6d0053;
  uStack108 = 0x440062;
  uStack104 = 0x690072;
  uStack100 = 0x650076;
  local_438 = param_2;
  iVar1 = (**(code **)(DAT_140008608 + 0x218))();
  if (-1 < iVar1) {
    (**(code **)(DAT_140008608 + 0x1e8))();
    static_init_2((undefined (*) [16])&local_138,0,0x90);
    local_110 = FUN_140002ec0;
    local_108 = FUN_140003100;
    local_d0 = FUN_140003090;
    local_130 = FUN_140002da0;
    local_120 = FUN_140002e30;
    local_f0 = FUN_1400031a0;
    local_e8 = FUN_140003260;
    local_e0 = FUN_140003220;
    local_138 = 0x90;
    (**(code **)(DAT_140008608 + 0x1b8))();
    local_368 = PTR_DAT_140008148;
    local_398 = CONCAT124(SUB1612(ZEXT816(0) >> 0x20,0),0x38);
    local_378 = ZEXT816(0);
    local_388 = CONCAT412(1,ZEXT412(1) << 0x40);
    iVar1 = (**(code **)(DAT_140008608 + 600))();
    if (-1 < iVar1) {
      static_init_2((undefined (*) [16])&local_1a8,0,0x68);
      local_190 = FUN_140003c20;
      local_1a8 = 0x68;
      local_188 = asf_clr_host_semaphore;
      local_14c = 2;
      local_180 = FUN_140003bc0;
      local_193 = 1;
      local_178 = FUN_140003b00;
      local_198 = 1;
      iVar1 = (**(code **)(DAT_140008608 + 0x468))();
      if (-1 < iVar1) {
        static_init_2((undefined (*) [16])&local_208,0,0x60);
        local_1f0 = FUN_140003e40;
        local_208 = 0x60;
        local_1fb = 1;
        local_1e8 = FUN_140003f90;
        local_204 = 1;
        local_1e0 = FUN_140003de0;
        local_200 = 1;
        local_1d8 = FUN_140003e10;
        local_1d0 = cleanup_transaction;
        local_330 = 0;
        local_360 = CONCAT124(SUB1612(ZEXT816(0) >> 0x20,0),0x38);
        local_340 = ZEXT816(local_440);
        local_350 = CONCAT412(1,ZEXT412(1) << 0x40);
        iVar1 = (**(code **)(DAT_140008608 + 0x4c0))();
        if (-1 < iVar1) {
          local_2f8 = 0;
          local_308 = ZEXT816(local_440);
          local_328 = CONCAT124(SUB1612(ZEXT816(0) >> 0x20,0),0x38);
          local_318 = CONCAT412(1,ZEXT412(1) << 0x40);
          iVar1 = (**(code **)(DAT_140008608 + 0x68))();
          if (-1 < iVar1) {
            local_2c0 = 0;
            local_2d0 = ZEXT816(local_440);
            local_2f0 = CONCAT124(SUB1612(ZEXT816(0) >> 0x20,0),0x38);
            local_2e0 = CONCAT412(1,ZEXT412(1) << 0x40);
            iVar1 = (**(code **)(DAT_140008608 + 0x9d8))();
            if (-1 < iVar1) {
              local_288 = 0;
              local_298 = ZEXT816(local_440);
              local_2b8 = CONCAT124(SUB1612(ZEXT816(0) >> 0x20,0),0x38);
              local_2a8 = CONCAT412(1,ZEXT412(1) << 0x40);
              iVar1 = (**(code **)(DAT_140008608 + 0x9d8))();
              if (-1 < iVar1) {
                local_26c = 0;
                local_258 = 0;
                local_250 = PTR_DAT_1400080d0;
                local_260 = local_440;
                local_3d8 = ZEXT816(0x1400040e0) << 0x40;
                local_27c = ZEXT816(0);
                local_280 = 0x38;
                local_268 = 1;
                local_264 = 1;
                local_3d8 = CONCAT124(local_3d8._4_12_,0x18);
                local_3c8 = 1;
                iVar1 = (**(code **)(DAT_140008608 + 0xbd8))();
                if (-1 < iVar1) {
                  puVar2 = (ulonglong *)(**(code **)(DAT_140008608 + 0x650))();
                  local_234 = 0;
                  local_220 = 0;
                  *puVar2 = local_440;
                  local_218 = PTR_DAT_1400080f8;
                  local_228 = local_440;
                  local_3b0._0_12_ = ZEXT812(0);
                  local_3a0 = 0;
                  local_3c0 = ZEXT816(0x140004080) << 0x40;
                  local_248 = 0x38;
                  local_244 = ZEXT816(0);
                  local_230 = 1;
                  local_22c = 1;
                  local_3c0 = CONCAT124(local_3c0._4_12_,0x28);
                  local_3b0 = CONCAT115(ZEXT711(SUB127(local_3b0._0_12_ >> 0x28,0)),0x100000000);
                  iVar1 = (**(code **)(DAT_140008608 + 0x9f0))();
                  if (-1 < iVar1) {
                    puVar2 = (ulonglong *)(**(code **)(DAT_140008608 + 0x650))();
                    *puVar2 = local_440;
                    puVar3 = (undefined *)(**(code **)(DAT_140008608 + 0x650))();
                    FUN_1400046b0(puVar3,param_1,local_440,local_400,local_408,local_428,local_430,
                                  local_410,local_418,local_420);
                    uVar4 = FUN_1400026f0((longlong)puVar3);
                    if ((-1 < (int)uVar4) &&
                       (iVar1 = (**(code **)(DAT_140008608 + 0x268))(), -1 < iVar1)) {
                      local_3e0 = &local_58;
                      local_58 = 0x47005c;
                      uStack84 = 0x6f006c;
                      uStack80 = 0x610062;
                      uStack76 = 0x3f006c;
                      local_3e8 = 0x280026;
                      local_38 = 0x7200650076;
                      local_48 = 0x5c003f;
                      uStack68 = 0x6d0053;
                      uStack64 = 0x440062;
                      uStack60 = 0x690072;
                      iVar1 = (**(code **)(DAT_140008608 + 0x280))();
                      if (-1 < iVar1) {
                        local_448[0] = '\0';
                        FUN_140002a5c(local_440,local_448);
                        DAT_1400083d0 = local_448[0];
                        if (local_448[0] != '\0') {
                          local_88 = 0;
                          local_a8 = 0x24;
                          local_98 = 2;
                          local_a4 = 1;
                          local_a0 = 4;
                          local_8c = 2;
                          local_9c = 5000;
                          local_90 = 1;
                          local_94 = 1;
                          iVar1 = (**(code **)(DAT_140008608 + 0x170))();
                          DAT_1400083d0 = -1 < iVar1;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  FUN_140005a70(local_30 ^ (ulonglong)auStackY1176);
  return;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

undefined8 FUN_140003b00(void)

{
  longlong lVar1;
  
  (**(code **)(DAT_140008608 + 0x4b8))();
  lVar1 = (**(code **)(DAT_140008608 + 0x650))();
  if (*(int *)(lVar1 + 0x14c) != 3) {
    *(undefined4 *)(lVar1 + 0x14c) = 3;
  }
  return 0;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall
// WARNING: Could not reconcile some variable overlaps

void asf_clr_host_semaphore(void)

{
  char cVar1;
  astruct_1 *dev;
  astruct_1 *local_38;
  undefined8 local_30;
  code *local_28;
  astruct_1 **local_20;
  code *local_18;
  astruct_1 *local_10;
  
  local_30 = 0x140003b82;
  (**(code **)(DAT_140008608 + 0x4b8))();
  local_30 = 0x140003ba7;
  dev = (astruct_1 *)(**(code **)(DAT_140008608 + 0x650))();
  local_30 = local_30 & 0xffffffffffff0000;
  local_28 = FUN_140002930;
  local_20 = &local_38;
  local_38 = dev;
  cVar1 = (**(code **)(DAT_140008608 + 0x478))();
  if (cVar1 != '\0') {
    if ((char)local_30 != '\0') {
      if (dev->field91_0x70 != 0) {
        in((short)dev->base_addr + 0x14);
      }
      if (dev->field91_0x70 == 0) {
        if (dev->mmio_addr != 0) {
          *(undefined *)(dev->mmio_addr + 0x14) = 2;
          LOCK();
        }
      }
      else {
        out((short)dev->base_addr + 0x14,2);
      }
      FUN_140002608((longlong)dev);
    }
    if (local_30._1_1_ != '\0') {
      do {
        while (dev->field253_0x118 <= dev->field254_0x120) {
          dev->field253_0x118 = dev->field253_0x118 + 1;
          FUN_1400048e4((longlong)dev,FUN_140001750);
        }
        local_18 = FUN_1400029d0;
        local_10 = dev;
        cVar1 = (**(code **)(DAT_140008608 + 0x478))();
      } while (cVar1 == '\0');
    }
  }
  return;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

undefined8 FUN_140003bc0(void)

{
  longlong lVar1;
  
  (**(code **)(DAT_140008608 + 0x4b8))();
  lVar1 = (**(code **)(DAT_140008608 + 0x650))();
  if (*(int *)(lVar1 + 0x14c) != 2) {
    *(undefined4 *)(lVar1 + 0x14c) = 2;
  }
  return 0;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

ulonglong FUN_140003c20(void)

{
  longlong lVar1;
  ulonglong uVar2;
  
  (**(code **)(DAT_140008608 + 0x4b8))();
  lVar1 = (**(code **)(DAT_140008608 + 0x650))();
  uVar2 = FUN_1400019c0(lVar1);
  return uVar2 & 0xffffffffffffff00 | (ulonglong)((char)uVar2 != '\0');
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

void FUN_140003c7c(byte param_1,undefined8 param_2,ulonglong param_3,ulonglong param_4,
                  ulonglong param_5,int param_6)

{
  int iVar1;
  longlong lVar2;
  ulonglong uVar3;
  
  (**(code **)(DAT_140008608 + 0x4e8))();
  lVar2 = (**(code **)(DAT_140008608 + 0x650))();
  uVar3 = param_3;
  FUN_140002bd4(lVar2,param_3);
  if (param_5 != 0) {
    uVar3 = param_3;
    iVar1 = (**(code **)(DAT_140008608 + 0x868))();
    if (iVar1 < 0) {
      param_5 = 0;
    }
  }
  if (param_4 == 0) {
    if (param_1 != 0) {
      param_4 = param_5;
    }
  }
  else {
    iVar1 = (**(code **)(DAT_140008608 + 0x870))();
    uVar3 = param_3;
    if (iVar1 < 0) {
      param_4 = 0;
    }
  }
  FUN_140001a24(lVar2,uVar3 & 0xffffffffffffff00 | (ulonglong)param_1,param_6,(byte *)0x0,param_5,
                (undefined8 *)0x0,param_4);
  return;
}



void FUN_140003de0(undefined8 param_1,ulonglong param_2,ulonglong param_3,ulonglong param_4,
                  int param_5)

{
  FUN_140003c7c(0,param_1,param_2,param_3,param_4,param_5);
  return;
}



void FUN_140003e10(undefined8 param_1,ulonglong param_2,ulonglong param_3,ulonglong param_4,
                  int param_5)

{
  FUN_140003c7c(1,param_1,param_2,param_3,param_4,param_5);
  return;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall
// WARNING: Could not reconcile some variable overlaps

void FUN_140003e40(undefined8 param_1,undefined8 param_2)

{
  longlong lVar1;
  undefined auStack88 [32];
  undefined local_38 [4];
  int iStack52;
  undefined local_28 [16];
  undefined8 local_18;
  ulonglong local_10;
  
  local_10 = DAT_1400081b0 ^ (ulonglong)auStack88;
  (**(code **)(DAT_140008608 + 0x4e8))();
  lVar1 = (**(code **)(DAT_140008608 + 0x650))();
  FUN_140002bd4(lVar1,param_2);
  local_18 = 0;
  _local_38 = CONCAT142(SUB1614(ZEXT816(0) >> 0x10,0),0x28);
  local_28 = ZEXT816(0);
  (**(code **)(DAT_140008608 + 0x850))();
  if (iStack52 == 3) {
    FUN_140001fdc(lVar1);
  }
  else {
    FUN_140002608(lVar1);
  }
  FUN_140005a70(local_10 ^ (ulonglong)auStack88);
  return;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

void cleanup_transaction(void)

{
  int iVar1;
  ulonglong uVar2;
  astruct_2 *lVar3;
  
  (**(code **)(DAT_140008608 + 0x4e8))();
  lVar3 = (astruct_2 *)(**(code **)(DAT_140008608 + 0x650))();
  uVar2 = FUN_1400028b4((longlong)lVar3);
  if ((char)uVar2 == '\0') {
    iVar1 = get_cpuid(&lVar3->field108_0x80);
    if ((iVar1 - 0x10002U < 0x50001) && ((iVar1 - 0x10002U & 0xffff) == 0)) {
      asf_master_en((longlong)&lVar3->field_0x60);
    }
    if (lVar3->use_mmio != 0) {
      in((short)lVar3->base_addr + 0x14);
    }
    if (lVar3->use_mmio == 0) {
      if (lVar3->mmio_addr != 0) {
        *(undefined *)(lVar3->mmio_addr + 0x14) = 2;
        LOCK();
      }
    }
    else {
      out((short)lVar3->base_addr + 0x14,2);
    }
    FUN_140002608((longlong)lVar3);
    lVar3->field122_0x94 = 0;
    lVar3->field123_0x98 = 0;
    lVar3->field124_0x9c = 0;
    lVar3->field125_0xa0 = 0;
    lVar3->field_0xa4 = 0xff;
    lVar3->field_0xa5 = 0;
    lVar3->field_0xa6 = 0;
    lVar3->field_0xa7 = 0;
    lVar3->field130_0xa8 = 0;
    lVar3->field_0xb0 = 0;
    lVar3->field_0xb1 = 0;
    lVar3->field139_0xb8 = 0;
    lVar3->field140_0xc0 = 0;
    lVar3->field141_0xc8 = 0;
    lVar3->field121_0x90 = 1;
  }
  return;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall
// WARNING: Could not reconcile some variable overlaps

void FUN_140003f90(undefined8 param_1,undefined8 param_2)

{
  longlong lVar1;
  undefined auStack88 [32];
  undefined local_38 [4];
  int iStack52;
  undefined local_28 [16];
  undefined8 local_18;
  ulonglong local_10;
  
  local_10 = DAT_1400081b0 ^ (ulonglong)auStack88;
  (**(code **)(DAT_140008608 + 0x4e8))();
  lVar1 = (**(code **)(DAT_140008608 + 0x650))();
  FUN_140002bd4(lVar1,param_2);
  local_18 = 0;
  _local_38 = CONCAT142(SUB1614(ZEXT816(0) >> 0x10,0),0x28);
  local_28 = ZEXT816(0);
  (**(code **)(DAT_140008608 + 0x850))();
  if (iStack52 == 4) {
    FUN_140001fdc(lVar1);
  }
  else {
    FUN_140002608(lVar1);
  }
  FUN_140005a70(local_10 ^ (ulonglong)auStack88);
  return;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

void asf_clear_host_semaphore_2(void)

{
  int iVar1;
  astruct_4 *lVar2;
  
  (**(code **)(DAT_140008608 + 0x650))();
  lVar2 = (astruct_4 *)(**(code **)(DAT_140008608 + 0x650))();
  if (lVar2->field32_0x20 != 0) {
    iVar1 = get_cpuid(&lVar2->field108_0x80);
    if ((iVar1 - 0x10002U < 0x50001) && ((iVar1 - 0x10002U & 0xffff) == 0)) {
      asf_master_en((longlong)&lVar2->field_0x60);
    }
    if (lVar2->use_mmio != 0) {
      in((short)lVar2->base_addr + 0x14);
    }
    if (lVar2->use_mmio == 0) {
      if (lVar2->mmio_addr != 0) {
        *(undefined *)(lVar2->mmio_addr + 0x14) = 2;
        LOCK();
      }
    }
    else {
      out((short)lVar2->base_addr + 0x14,2);
    }
    lVar2->field122_0x94 = 0;
    lVar2->field123_0x98 = 0;
    lVar2->field124_0x9c = 0;
    lVar2->field125_0xa0 = 0;
    lVar2->field_0xa4 = 0xff;
    lVar2->field_0xa5 = 0;
    lVar2->field_0xa6 = 0;
    lVar2->field_0xa7 = 0;
    lVar2->field130_0xa8 = 0;
    lVar2->field_0xb0 = 0;
    lVar2->field_0xb1 = 0;
    lVar2->field139_0xb8 = 0;
    lVar2->field140_0xc0 = 0;
    lVar2->field141_0xc8 = 0;
    lVar2->field121_0x90 = 1;
    FUN_140002608((longlong)lVar2);
  }
  return;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

void FUN_1400040e0(void)

{
  longlong *plVar1;
  longlong lVar2;
  longlong lVar3;
  
  lVar2 = (**(code **)(DAT_140008608 + 0x650))();
  plVar1 = *(longlong **)(lVar2 + 8);
  lVar3 = (**(code **)(DAT_140008608 + 0x650))();
  lVar2 = *plVar1;
  if (lVar2 != 0) {
    FUN_140004734(lVar3,lVar2);
  }
  *plVar1 = 0;
  FUN_140002608(lVar3);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_140004144(void)

{
  int iVar1;
  undefined auStack344 [32];
  undefined4 local_138;
  uint local_134;
  uint local_130;
  ulonglong local_18;
  
  local_18 = DAT_1400081b0 ^ (ulonglong)auStack344;
  _DAT_1400083b8 = 1;
  _DAT_140008390 = 0;
  DAT_140008398 = &DAT_1400071a8;
  DAT_1400083a0 = 0;
  _DAT_1400083b0 = 0;
  win_14000b0fc();
  _DAT_1400083b0 = 0;
  win_14000b074();
  local_138 = 0x114;
  iVar1 = RtlGetVersion(&local_138);
  if ((-1 < iVar1) && ((6 < local_134 || ((local_134 == 6 && (1 < local_130)))))) {
    DAT_140008240 = 0x200;
    _DAT_140008244 = 0x40000000;
  }
  FUN_140002c68();
  FUN_140005a70(local_18 ^ (ulonglong)auStack344);
  return;
}



void FUN_140004220(undefined8 param_1,byte param_2,undefined8 *param_3,longlong param_4)

{
  undefined8 uVar1;
  
  if (param_2 < 2) {
    uVar1 = 0;
    if (param_2 == 0) {
      *(undefined *)(param_4 + 0x29) = 0;
      *(undefined4 *)(param_4 + 0x2c) = 0;
    }
    else {
      *(undefined4 *)(param_4 + 0x2c) = *(undefined4 *)((longlong)param_3 + 4);
      *(undefined *)(param_4 + 0x29) = *(undefined *)((longlong)param_3 + 2);
      uVar1 = *param_3;
    }
    *(undefined8 *)(param_4 + 0x18) = uVar1;
  }
  return;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

void FUN_140004250(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  code *pcVar1;
  undefined local_88 [16];
  undefined local_78 [8];
  undefined4 local_70;
  undefined8 local_68;
  undefined8 local_60;
  
  static_init_2((undefined (*) [16])local_78,0,0x70);
  local_70 = 0x24;
  local_68 = param_2;
  local_60 = param_3;
  RtlInitUnicodeString(local_88,L"RtlQueryRegistryValuesEx");
  pcVar1 = (code *)MmGetSystemRoutineAddress(local_88);
  if (pcVar1 == (code *)0x0) {
    pcVar1 = RtlQueryRegistryValues_exref;
  }
  (*pcVar1)();
  return;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

undefined8 FUN_1400042e8(undefined8 param_1,longlong param_2,undefined8 *param_3,uint param_4)

{
  int iVar1;
  undefined8 *puVar2;
  undefined8 local_res10;
  undefined8 local_80;
  
  if ((((param_2 != 0) && (param_3 != (undefined8 *)0x0)) && (param_4 != 0)) &&
     (iVar1 = (**(code **)(DAT_140008608 + 0x378))(), -1 < iVar1)) {
    iVar1 = (**(code **)(DAT_140008608 + 0x658))();
    if ((iVar1 < 0) || (iVar1 = (**(code **)(DAT_140008608 + 0x9d8))(), iVar1 < 0)) {
      (**(code **)(DAT_140008608 + 0x680))();
    }
    else {
      static_init((undefined8 *)0x0,param_3,(ulonglong)param_4);
      puVar2 = (undefined8 *)(**(code **)(DAT_140008608 + 0x650))();
      *puVar2 = local_res10;
      puVar2[1] = local_80;
      *(undefined4 *)(puVar2 + 2) = 1;
      puVar2[3] = param_2;
      puVar2[4] = 0;
      (**(code **)(DAT_140008608 + 0x9e0))();
      iVar1 = (**(code **)(DAT_140008608 + 0x78))();
      (**(code **)(DAT_140008608 + 0x9e8))();
      if (-1 < iVar1) {
        return puVar2[4];
      }
    }
  }
  return 0;
}



void FUN_1400046b0(undefined *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                  undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                  undefined8 param_9,undefined8 param_10)

{
  *param_1 = 2;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  *(undefined8 *)(param_1 + 0x18) = param_5;
  *(undefined8 *)(param_1 + 0x28) = param_6;
  *(undefined8 *)(param_1 + 0x30) = param_7;
  *(undefined8 *)(param_1 + 0x38) = param_8;
  *(undefined8 *)(param_1 + 0x40) = param_9;
  *(undefined8 *)(param_1 + 8) = param_3;
  *(undefined8 *)(param_1 + 0x48) = param_2;
  *(undefined8 *)(param_1 + 0x50) = param_10;
  *(undefined8 *)(param_1 + 0x10) = param_4;
  *(undefined4 *)(param_1 + 0x58) = 3000;
  FUN_140004250(L"SmbDrv\\Parameters",L"SmbRequestTimeout",param_1 + 0x58);
  return;
}



void FUN_140004720(undefined *param_1,undefined8 param_2)

{
  *param_1 = 1;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  *(undefined8 *)(param_1 + 0x48) = param_2;
  return;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

void FUN_140004734(longlong param_1,longlong param_2)

{
  uint uVar1;
  longlong lVar2;
  longlong lVar3;
  code *UNRECOVERED_JUMPTABLE;
  uint uVar4;
  
  (**(code **)(DAT_140008608 + 0x9e0))();
  lVar2 = 0;
  uVar1 = (**(code **)(DAT_140008608 + 0x70))();
  uVar4 = 0;
  if (uVar1 != 0) {
    do {
      lVar2 = (**(code **)(DAT_140008608 + 0x90))();
      lVar3 = (**(code **)(DAT_140008608 + 0x650))();
      if (*(longlong *)(lVar3 + 0x20) == param_2) goto LAB_1400047f6;
      uVar4 = uVar4 + 1;
    } while (uVar4 < uVar1);
  }
  if (uVar4 != uVar1) {
LAB_1400047f6:
    if (lVar2 != 0) {
      (**(code **)(DAT_140008608 + 0x80))();
      (**(code **)(DAT_140008608 + 0x9e8))();
      (**(code **)(DAT_140008608 + 0x388))();
      lVar3 = (**(code **)(DAT_140008608 + 0x650))();
      *(undefined8 *)(lVar3 + 0x18) = 0;
      *(undefined8 *)(lVar3 + 0x20) = 0;
      *(undefined4 *)(lVar3 + 0x10) = 4;
      UNRECOVERED_JUMPTABLE = *(code **)(DAT_140008608 + 0x680);
      goto LAB_1400048bc;
    }
  }
  lVar2 = *(longlong *)(param_1 + 0x38);
  UNRECOVERED_JUMPTABLE = *(code **)(DAT_140008608 + 0x9e8);
LAB_1400048bc:
                    // WARNING: Could not recover jumptable at 0x000140006130. Too many branches
                    // WARNING: Treating indirect jump as call
  (*UNRECOVERED_JUMPTABLE)(DAT_140008610,lVar2);
  return;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

void FUN_1400048e4(longlong param_1,undefined *param_2)

{
  char cVar1;
  uint uVar2;
  longlong lVar3;
  code *pcVar4;
  uint uVar5;
  
  (**(code **)(DAT_140008608 + 0x9e0))();
  uVar2 = (**(code **)(DAT_140008608 + 0x70))();
  uVar5 = 0;
  if (uVar2 != 0) {
    do {
      (**(code **)(DAT_140008608 + 0x90))();
      lVar3 = (**(code **)(DAT_140008608 + 0x650))();
      (**(code **)(DAT_140008608 + 0x9e0))();
      if ((*(int *)(lVar3 + 0x10) == 1) && (cVar1 = (*(code *)param_2)(), cVar1 != '\0')) {
        *(undefined4 *)(lVar3 + 0x10) = 2;
        (**(code **)(DAT_140008608 + 0x9e8))();
        pcVar4 = *(code **)(DAT_140008608 + 0x380);
      }
      else {
        pcVar4 = *(code **)(DAT_140008608 + 0x9e8);
      }
      (*pcVar4)();
      uVar5 = uVar5 + 1;
    } while (uVar5 < uVar2);
  }
                    // WARNING: Could not recover jumptable at 0x000140006130. Too many branches
                    // WARNING: Treating indirect jump as call
  (**(code **)(DAT_140008608 + 0x9e8))(DAT_140008610,*(undefined8 *)(param_1 + 0x38));
  return;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

undefined8 FUN_140004a6c(void)

{
  undefined8 uVar1;
  
  uVar1 = (**(code **)(DAT_140008608 + 0x9f8))();
  return CONCAT71((int7)((ulonglong)uVar1 >> 8),1);
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

void FUN_140004aa0(void)

{
  longlong lVar1;
  
  lVar1 = (**(code **)(DAT_140008608 + 0x650))();
  (**(code **)(DAT_140008608 + 0x9e0))();
  *(undefined4 *)(lVar1 + 0x10) = 3;
  (**(code **)(DAT_140008608 + 0x9e8))();
  (**(code **)(lVar1 + 0x18))();
  (**(code **)(DAT_140008608 + 0x9e0))();
  *(undefined4 *)(lVar1 + 0x10) = 1;
                    // WARNING: Could not recover jumptable at 0x000140006130. Too many branches
                    // WARNING: Treating indirect jump as call
  (**(code **)(DAT_140008608 + 0x9e8))(DAT_140008610,*(undefined8 *)(lVar1 + 8));
  return;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

ulonglong FUN_140004b70(undefined8 param_1,undefined **param_2)

{
  ulonglong in_RAX;
  ulonglong uVar1;
  
  if (param_2 == (undefined **)0x0) {
    uVar1 = in_RAX & 0xffffffffffffff00;
  }
  else {
    uVar1 = (*(code *)*param_2)();
    uVar1 = uVar1 & 0xffffffffffffff00 | (ulonglong)((char)uVar1 != '\0');
  }
  return uVar1;
}



undefined8
FUN_140004b94(undefined4 *param_1,undefined4 param_2,undefined8 param_3,undefined4 param_4,
             undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined8 param_8)

{
  param_1[5] = param_5;
  param_1[6] = param_6;
  param_1[7] = param_7;
  *(undefined8 *)(param_1 + 10) = param_8;
  *param_1 = param_2;
  *(undefined8 *)(param_1 + 2) = param_3;
  param_1[4] = param_4;
  return 0;
}



undefined8
FUN_140004bc0(undefined4 *param_1,undefined4 *param_2,undefined8 *param_3,undefined4 *param_4,
             undefined4 *param_5,undefined4 *param_6,undefined4 *param_7)

{
  *param_2 = *param_1;
  *param_3 = *(undefined8 *)(param_1 + 2);
  *param_4 = param_1[4];
  *param_5 = param_1[5];
  *param_6 = param_1[6];
  *param_7 = param_1[7];
  if (*(ulonglong *)(param_1 + 10) != 0) {
    win_140001194(*(ulonglong *)(param_1 + 10));
  }
  *param_1 = 0;
  *(undefined8 *)(param_1 + 2) = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  *(undefined8 *)(param_1 + 10) = 0;
  return 0;
}



void FUN_140004c30(undefined4 *param_1)

{
  *param_1 = 0;
  *(undefined8 *)(param_1 + 2) = 0;
  *(undefined8 *)(param_1 + 4) = 0;
  *(undefined8 *)(param_1 + 6) = 0;
  *(undefined8 *)(param_1 + 10) = 0;
  return;
}



byte * smbus_asf_io_en(longlong param_1)

{
  byte bVar1;
  uint uVar2;
  ulonglong uVar3;
  byte *pbVar4;
  
  uVar3 = get_cpuid((int *)(param_1 + 0x20));
  if ((int)uVar3 == 0x10002) {
    out(0xcd6,0x28);
    bVar1 = in(0xcd7);
    out(0xcd6,0x28);
    pbVar4 = (byte *)(uVar3 & 0xffffffffffffff00 | (ulonglong)(bVar1 | 1));
    out(0xcd7,bVar1 | 1);
  }
  else {
    uVar2 = (int)uVar3 - 0x20002;
    pbVar4 = (byte *)(ulonglong)uVar2;
    if ((uVar2 < 0x40001) && (pbVar4 = (byte *)(ulonglong)(ushort)uVar2, (uVar2 & 0xffff) == 0)) {
      if (*(char *)(param_1 + 0xd0) == (char)uVar2) {
        out(0xcd6,0);
        bVar1 = in(0xcd7);
        out(0xcd6,0);
        pbVar4 = (byte *)(ulonglong)(bVar1 | 0x10);
        out(0xcd7,bVar1 | 0x10);
      }
      else {
        pbVar4 = *(byte **)(param_1 + 0xd8);
        *pbVar4 = **(byte **)(param_1 + 0xd8) | 0x10;
      }
    }
  }
  return pbVar4;
}



ulonglong asf_sm_master_en(longlong param_1)

{
  byte bVar1;
  uint uVar2;
  ulonglong uVar3;
  
  uVar3 = get_cpuid((int *)(param_1 + 0x20));
  if ((int)uVar3 == 0x10002) {
    out(0xcd6,0x28);
    bVar1 = in(0xcd7);
    out(0xcd6,0x28);
    uVar3 = uVar3 & 0xffffffffffffff00 | (ulonglong)(bVar1 | 5);
    out(0xcd7,bVar1 | 5);
  }
  else {
    uVar2 = (int)uVar3 - 0x20002;
    uVar3 = (ulonglong)uVar2;
    if ((uVar2 < 0x40001) && (uVar3 = (ulonglong)(ushort)uVar2, (uVar2 & 0xffff) == 0)) {
      if (*(char *)(param_1 + 0xd0) == (char)uVar2) {
        out(0xcd6,2);
        bVar1 = in(0xcd7);
        out(0xcd6,2);
        uVar3 = (ulonglong)(ushort)(CONCAT11((char)(uVar2 >> 8),bVar1) | 1);
        out(0xcd7,bVar1 | 1);
      }
      else {
        uVar3 = *(ulonglong *)(param_1 + 0xd8);
        *(byte *)(uVar3 + 2) = *(byte *)(*(longlong *)(param_1 + 0xd8) + 2) | 5;
      }
    }
  }
  return uVar3;
}



ulonglong restart_slave_and_enable_listen(astruct_7 *param_1)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  ulonglong uVar4;
  
  iVar2 = get_cpuid(&param_1->field19_0x20);
  uVar3 = iVar2 - 0x10002;
  uVar4 = (ulonglong)uVar3;
  if ((uVar3 < 0x50001) && (uVar4 = (ulonglong)(ushort)uVar3, (uVar3 & 0xffff) == 0)) {
    if (param_1->use_mmio == 0) {
      uVar4 = param_1->mmio_addr;
      if (uVar4 == 0) {
        bVar1 = 0;
      }
      else {
        bVar1 = *(byte *)(uVar4 + 0x15);
      }
    }
    else {
      bVar1 = in((short)param_1->base_addr + 0x15);
      uVar4 = (ulonglong)CONCAT11((char)(uVar3 >> 8),bVar1);
    }
    uVar4 = uVar4 & 0xffffffffffffff00;
    if (param_1->use_mmio == 0) {
      if (param_1->mmio_addr != 0) {
        *(byte *)(param_1->mmio_addr + 0x15) = bVar1 | 0x10;
        LOCK();
      }
    }
    else {
      out((short)param_1->base_addr + 0x15,bVar1 | 0x10);
    }
    if (param_1->use_mmio == 0) {
      uVar4 = param_1->mmio_addr;
      if (uVar4 != 0) {
        *(byte *)(uVar4 + 0x15) = bVar1 & 0xef;
        LOCK();
      }
    }
    else {
      out((short)param_1->base_addr + 0x15,bVar1 & 0xef);
    }
    if (param_1->use_mmio == 0) {
      uVar4 = param_1->mmio_addr;
      if (uVar4 != 0) {
        *(undefined *)(uVar4 + 9) = 0x11;
        LOCK();
      }
    }
    else {
      uVar4 = CONCAT71((int7)(uVar4 >> 8),0x11);
      out((short)param_1->base_addr + 9,0x11);
    }
    uVar4 = CONCAT71((int7)(uVar4 >> 8),1);
  }
  else {
    uVar4 = uVar4 & 0xffffffffffffff00;
  }
  return uVar4;
}



void mmio_en(longlong param_1)

{
  byte bVar1;
  int iVar2;
  undefined8 uVar3;
  
  *(undefined8 *)(param_1 + 0xd8) = 0;
  *(undefined *)(param_1 + 0xd0) = 0;
  iVar2 = get_cpuid((int *)(param_1 + 0x20));
  if ((iVar2 - 0x20002U < 0x40001) && ((iVar2 - 0x20002U & 0xffff) == 0)) {
    out(0xcd6,4);
    bVar1 = in(0xcd7);
    bVar1 = bVar1 >> 1 & 1;
    *(byte *)(param_1 + 0xd0) = bVar1;
    if (bVar1 != 0) {
      uVar3 = MmMapIoSpace(0xfed80300,8);
      *(undefined8 *)(param_1 + 0xd8) = uVar3;
      uVar3 = MmMapIoSpace(0xfed80900,0x17);
      *(undefined8 *)(param_1 + 0xe0) = uVar3;
      *(undefined8 *)(param_1 + 8) = uVar3;
    }
  }
  return;
}



ulonglong cleanup_data_bank_and_restart_slave(astruct_8 *param_1)

{
  byte bVar1;
  byte bVar2;
  undefined2 *puVar3;
  byte *pbVar4;
  longlong lVar6;
  ulonglong uVar5;
  
  puVar3 = &param_1->field130_0xca;
  param_1->field112_0x80 = 0;
  param_1->field113_0x84 = 0;
  param_1->field114_0x88 = 0;
  param_1->field115_0x8c = 0;
  param_1->field116_0x90 = 0;
  param_1->field117_0x94 = 0;
  param_1->field118_0x98 = 0;
  param_1->field119_0x9c = 0;
  param_1->field120_0xa0 = 0;
  param_1->field121_0xa4 = 0;
  param_1->field122_0xa8 = 0;
  param_1->field123_0xac = 0;
  param_1->field124_0xb0 = 0;
  param_1->field125_0xb4 = 0;
  param_1->field126_0xb8 = 0;
  param_1->field127_0xc0 = 0;
  lVar6 = 2;
  do {
    *(undefined *)(puVar3 + -1) = 0xff;
    *puVar3 = 0;
    puVar3 = puVar3 + 2;
    lVar6 = lVar6 + -1;
  } while (lVar6 != 0);
  mmio_en((longlong)param_1);
  pbVar4 = smbus_asf_io_en((longlong)param_1);
  bVar2 = 0;
  if (param_1->use_mmio == 0) {
    uVar5 = param_1->mmio_addr;
    if (uVar5 == 0) {
      uVar5 = 0;
    }
    else {
      uVar5 = uVar5 & 0xffffffffffffff00 | (ulonglong)*(byte *)(uVar5 + 0x13);
    }
  }
  else {
    bVar1 = in((short)param_1->base_addr + 0x13);
    uVar5 = (ulonglong)pbVar4 & 0xffffffffffffff00 | (ulonglong)bVar1;
  }
  bVar1 = (byte)uVar5 & 0xc;
  if (param_1->use_mmio == 0) {
    if (param_1->mmio_addr != 0) {
      *(byte *)(param_1->mmio_addr + 0x13) = bVar1;
      LOCK();
    }
  }
  else {
    out((short)param_1->base_addr + 0x13,bVar1);
  }
  if (param_1->use_mmio == 0) {
    uVar5 = param_1->mmio_addr;
    if (uVar5 != 0) {
      bVar2 = *(byte *)(uVar5 + 0x15);
    }
  }
  else {
    bVar2 = in((short)param_1->base_addr + 0x15);
    uVar5 = uVar5 & 0xffffffffffffff00;
  }
  if (param_1->use_mmio == 0) {
    uVar5 = param_1->mmio_addr;
    if (uVar5 != 0) {
      *(undefined *)(uVar5 + 9) = 0x10;
      LOCK();
    }
  }
  else {
    uVar5 = CONCAT71((int7)(uVar5 >> 8),0x10);
    out((short)param_1->base_addr + 9,0x10);
  }
  if (param_1->use_mmio == 0) {
    if (param_1->mmio_addr != 0) {
      *(byte *)(param_1->mmio_addr + 0x15) = bVar2 | 0x12;
      LOCK();
    }
  }
  else {
    out((short)param_1->base_addr + 0x15,bVar2 | 0x12);
  }
  if (param_1->use_mmio == 0) {
    uVar5 = param_1->mmio_addr;
    if (uVar5 != 0) {
      *(byte *)(uVar5 + 0x15) = bVar2 & 0xef | 2;
      LOCK();
    }
  }
  else {
    uVar5 = uVar5 & 0xffffffffffffff00 | (ulonglong)bVar2 & 0xffffffffffffffef | 2;
    out((short)param_1->base_addr + 0x15,(char)uVar5);
  }
  return uVar5;
}



char smbus_trans(astruct_9 *param_1)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  char cVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  int iVar8;
  ulonglong uVar9;
  char cVar10;
  longlong lVar11;
  
  lVar11 = 0;
  bVar7 = 0;
  cVar4 = '\0';
  param_1->field85_0x80 = param_1->field85_0x80 + 1;
  bVar3 = false;
  bVar2 = false;
  cVar10 = '\x03';
  if (param_1->use_mmio == 0) {
    if (param_1->mmio_addr != (byte *)0x0) {
      bVar5 = *param_1->mmio_addr;
      goto LAB_14000513d;
    }
  }
  else {
    bVar5 = in((short)param_1->base_addr);
LAB_14000513d:
    if ((bVar5 & 0x1e) != 0) {
      cVar4 = '\x01';
      param_1->field92_0x90 = param_1->field92_0x90 + 1;
      if ((bVar5 & 0x1c) == 0) {
        bVar6 = 0;
        bVar2 = false;
        if (((bVar5 & 2) != 0) && (bVar6 = 2, bVar2 = bVar3, param_1->field32_0x30 == 2)) {
          if (param_1->use_mmio == 0) {
            if (param_1->mmio_addr != (byte *)0x0) {
              param_1->mmio_addr[0x13] = 0x80;
              LOCK();
            }
          }
          else {
            out((short)param_1->base_addr + 0x13,0x80);
          }
          cVar1 = param_1->field61_0x50;
          if (cVar1 == '\x01') {
            if (param_1->use_mmio == 0) {
              if (param_1->mmio_addr != (byte *)0x0) {
                bVar7 = param_1->mmio_addr[5];
              }
            }
            else {
              bVar7 = in((short)param_1->base_addr + 5);
            }
            *param_1->field69_0x58 = 1;
            *param_1->field70_0x60 = bVar7;
LAB_1400052fd:
            param_1->field91_0x8c = param_1->field91_0x8c + 1;
            *param_1->field71_0x68 = 0;
          }
          else {
            if (cVar1 == '\x02') {
              if (param_1->use_mmio == 0) {
                bVar5 = bVar7;
                if (param_1->mmio_addr != (byte *)0x0) {
                  bVar5 = param_1->mmio_addr[5];
                }
              }
              else {
                bVar5 = in((short)param_1->base_addr + 5);
              }
              if (param_1->use_mmio == 0) {
                if (param_1->mmio_addr != (byte *)0x0) {
                  bVar7 = param_1->mmio_addr[6];
                }
              }
              else {
                bVar7 = in((short)param_1->base_addr + 6);
              }
              *param_1->field69_0x58 = 2;
              *param_1->field70_0x60 = bVar5;
              param_1->field70_0x60[1] = bVar7;
              goto LAB_1400052fd;
            }
            if (cVar1 != ' ') {
              *param_1->field69_0x58 = 0;
              goto LAB_1400052fd;
            }
            if (param_1->use_mmio == 0) {
              if (param_1->mmio_addr != (byte *)0x0) {
                bVar5 = param_1->mmio_addr[5];
                goto LAB_1400051e3;
              }
            }
            else {
              bVar5 = in((short)param_1->base_addr + 5);
LAB_1400051e3:
              if ((byte)(bVar5 - 1) < 0x20) {
                *param_1->field69_0x58 = bVar5;
                if (param_1->use_mmio != 0) {
                  in((short)param_1->base_addr + 2);
                }
                if (bVar5 != 0) {
                  uVar9 = (ulonglong)bVar5;
                  do {
                    if (param_1->use_mmio == 0) {
                      bVar5 = bVar7;
                      if (param_1->mmio_addr != (byte *)0x0) {
                        bVar5 = param_1->mmio_addr[7];
                      }
                    }
                    else {
                      bVar5 = in((short)param_1->base_addr + 7);
                    }
                    param_1->field70_0x60[lVar11] = bVar5;
                    lVar11 = lVar11 + 1;
                    uVar9 = uVar9 - 1;
                  } while (uVar9 != 0);
                }
                goto LAB_1400052fd;
              }
            }
            param_1->field90_0x88 = param_1->field90_0x88 + 1;
            *param_1->field71_0x68 = 0x13;
          }
          param_1->field32_0x30 = 3;
          bVar2 = true;
        }
      }
      else {
        if (param_1->field32_0x30 == 2) {
          if ((bVar5 & 8) == 0) {
            param_1->field90_0x88 = param_1->field90_0x88 + 1;
            *param_1->field71_0x68 = 0x11;
          }
          else {
            param_1->field90_0x88 = param_1->field90_0x88 + 1;
            *param_1->field71_0x68 = 0x1a;
          }
          param_1->field32_0x30 = 3;
          bVar3 = true;
        }
        bVar7 = bVar5 & 8 | 0x10;
        if ((bVar5 & 0x10) == 0) {
          bVar7 = bVar5 & 8;
        }
        bVar6 = bVar7 | 4;
        if ((bVar5 & 4) == 0) {
          bVar6 = bVar7;
        }
        bVar2 = bVar3;
        if ((bVar5 & 2) != 0) {
          bVar6 = bVar6 | 2;
        }
      }
      if (param_1->use_mmio == 0) {
        if (param_1->mmio_addr != (byte *)0x0) {
          *param_1->mmio_addr = bVar6;
          LOCK();
        }
      }
      else {
        out((short)param_1->base_addr,bVar6);
      }
      iVar8 = get_cpuid(&param_1->field19_0x20);
      if ((iVar8 - 0x10002U < 0x50001) && ((iVar8 - 0x10002U & 0xffff) == 0)) {
        asf_master_en((longlong)param_1);
      }
    }
  }
  if (((param_1->field80_0x78 != 2) && (param_1->field80_0x78 != 3)) && (param_1->field80_0x78 != 4)
     ) goto LAB_1400054d4;
  if (param_1->use_mmio == 0) {
    if (param_1->mmio_addr == (byte *)0x0) goto LAB_1400054d4;
    bVar7 = param_1->mmio_addr[10];
  }
  else {
    bVar7 = in((short)param_1->base_addr + 10);
  }
  if ((char)bVar7 < '\0') {
    restart_slave_and_enable_listen((astruct_7 *)param_1);
    goto LAB_1400054d4;
  }
  if ((bVar7 & 0x40) == 0) goto LAB_1400054d4;
  cVar4 = '\x01';
  param_1->field93_0x94 = param_1->field93_0x94 + 1;
  if (param_1->use_mmio == 0) {
    if (param_1->mmio_addr != (byte *)0x0) {
      param_1->mmio_addr[10] = 0x40;
      LOCK();
    }
  }
  else {
    out((short)param_1->base_addr + 10,0x40);
  }
  if (param_1->use_mmio == 0) {
    if (param_1->mmio_addr != (byte *)0x0) {
      bVar7 = param_1->mmio_addr[0x15];
      goto LAB_140005474;
    }
  }
  else {
    bVar7 = in((short)param_1->base_addr + 0x15);
LAB_140005474:
    if ((bVar7 & 0x10) != 0) {
      param_1->field94_0x98 = param_1->field94_0x98 + 1;
      goto LAB_1400054d4;
    }
  }
  if ((param_1->field80_0x78 == 3) || (param_1->field80_0x78 == 4)) {
    param_1->field95_0x9c = param_1->field95_0x9c + 1;
  }
  else {
    uVar9 = process_host_notify((astruct_10 *)param_1);
    if ((char)uVar9 != '\0') {
      param_1->field97_0xa4 = param_1->field97_0xa4 + 1;
      param_1->field80_0x78 = 3;
      return '\x03';
    }
    param_1->field96_0xa0 = param_1->field96_0xa0 + 1;
  }
LAB_1400054d4:
  if (!bVar2) {
    cVar10 = cVar4 + '\x01';
  }
  return cVar10;
}



ulonglong process_host_notify(astruct_10 *param_1)

{
  byte bVar1;
  ulonglong in_RAX;
  ulonglong uVar2;
  uint uVar3;
  longlong input_addr_sel;
  longlong output_addr_sel;
  
  if (param_1->use_mmio == 0) {
    uVar2 = param_1->mmio_addr;
    if (uVar2 != 0) {
      uVar2 = uVar2 & 0xffffffffffffff00 | (ulonglong)*(byte *)(uVar2 + 0x13);
    }
  }
  else {
    bVar1 = in((short)param_1->base_addr + 0x13);
    uVar2 = in_RAX & 0xffffffffffffff00 | (ulonglong)bVar1;
  }
  bVar1 = (byte)uVar2 & 0xc;
  uVar3 = (uint)uVar2 & 0xd;
  if (((uVar2 & 0xd) == 0) || (uVar3 == 1)) {
LAB_14000556f:
    return uVar2 & 0xffffffffffffff00;
  }
  if (uVar3 == 4) {
    input_addr_sel = 0;
  }
  else {
    if (uVar3 != 9) {
      if (uVar3 == 0xc) {
        param_1->field168_0xb8 = 0;
        get_host_notify_address((astruct_11 *)param_1,1,0);
        input_addr_sel = 0;
      }
      else {
        if (uVar3 != 0xd) {
          if (param_1->use_mmio == 0) {
            uVar2 = param_1->mmio_addr;
            if (uVar2 != 0) {
              *(byte *)(uVar2 + 0x13) = bVar1;
              LOCK();
            }
          }
          else {
            uVar2 = uVar2 & 0xffffffffffffff00;
            out((short)param_1->base_addr + 0x13,bVar1);
          }
          goto LAB_14000556f;
        }
        param_1->field168_0xb8 = 0;
        get_host_notify_address((astruct_11 *)param_1,0,0);
        input_addr_sel = 1;
      }
      output_addr_sel = 1;
      goto LAB_1400055e3;
    }
    input_addr_sel = 1;
  }
  output_addr_sel = 0;
  param_1->field168_0xb8 = 0;
LAB_1400055e3:
  uVar2 = get_host_notify_address((astruct_11 *)param_1,input_addr_sel,output_addr_sel);
  if (param_1->use_mmio == 0) {
    if (param_1->mmio_addr != 0) {
      *(byte *)(param_1->mmio_addr + 0x13) = bVar1;
      LOCK();
    }
  }
  else {
    uVar2 = uVar2 & 0xffffffffffffff00;
    out((short)param_1->base_addr + 0x13,bVar1);
  }
  return uVar2 & 0xffffffffffffff00 | 1;
}



void get_host_notify_address(astruct_11 *dev,longlong input_addr_sel,longlong output_addr_sel)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  ushort uVar4;
  
  dev->field155_0xa8 = dev->field155_0xa8 + 1;
  uVar4 = 0;
  if (dev->use_mmio == 0) {
    if (dev->mmio_addr != 0) {
      *(undefined *)(dev->mmio_addr + 0x13) = (&DAT_140007394)[input_addr_sel];
      LOCK();
    }
  }
  else {
    out((short)dev->base_addr + 0x13,(&DAT_140007394)[input_addr_sel]);
  }
  if (dev->use_mmio != 0) {
    in((short)dev->base_addr + 2);
  }
  if (dev->use_mmio != 0) {
    in((short)dev->base_addr + 7);
  }
  if (dev->use_mmio == 0) {
    if (dev->mmio_addr == 0) {
      bVar1 = 0;
    }
    else {
      bVar1 = *(byte *)(dev->mmio_addr + 7);
    }
  }
  else {
    bVar1 = in((short)dev->base_addr + 7);
  }
  if (dev->use_mmio == 0) {
    if (dev->mmio_addr == 0) {
      bVar2 = 0;
    }
    else {
      bVar2 = *(byte *)(dev->mmio_addr + 7);
    }
  }
  else {
    bVar2 = in((short)dev->base_addr + 7);
  }
  if (dev->use_mmio == 0) {
    if (dev->mmio_addr != 0) {
      uVar4 = (ushort)*(byte *)(dev->mmio_addr + 7);
    }
  }
  else {
    bVar3 = in((short)dev->base_addr + 7);
    uVar4 = (ushort)bVar3;
  }
  (&dev->field_0xc8)[output_addr_sel * 4] = bVar1 >> 1;
  *(ushort *)(&dev[1].field_0x0 + output_addr_sel * 4) = uVar4 << 8 | (ushort)bVar2;
  dev->field176_0xc0 = output_addr_sel;
  return;
}



void FUN_140005a70(longlong param_1)

{
  if ((param_1 == DAT_1400081b0) && ((short)((ulonglong)param_1 >> 0x30) == 0)) {
    return;
  }
  FUN_140005a90();
  return;
}



void FUN_140005a90(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x29);
  (*pcVar1)(2);
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}



void _guard_check_icall(void)

{
  return;
}



undefined8 FUN_140005ab0(undefined8 param_1,ulonglong param_2,undefined8 param_3,longlong param_4)

{
  FUN_140005ad0(param_2,param_4,*(uint **)(param_4 + 0x38));
  return 1;
}



void FUN_140005ad0(ulonglong param_1,longlong param_2,uint *param_3)

{
  byte bVar1;
  ulonglong uVar2;
  
  uVar2 = param_1;
  if ((*param_3 & 4) != 0) {
    uVar2 = (longlong)(int)param_3[1] + param_1 & (longlong)(int)-param_3[2];
  }
  bVar1 = *(byte *)((ulonglong)*(uint *)(*(longlong *)(param_2 + 0x10) + 8) + 3 +
                   *(longlong *)(param_2 + 8));
  if ((bVar1 & 0xf) != 0) {
    param_1 = param_1 + (bVar1 & 0xfffffff0);
  }
  FUN_140005a70(param_1 ^ *(ulonglong *)((longlong)(int)(*param_3 & 0xfffffff8) + uVar2));
  return;
}



int strncmp(char *_Str1,char *_Str2,size_t _MaxCount)

{
  int iVar1;
  
                    // WARNING: Could not recover jumptable at 0x000140005b30. Too many branches
                    // WARNING: Treating indirect jump as call
  iVar1 = strncmp(_Str1,_Str2,_MaxCount);
  return iVar1;
}



// WARNING: Removing unreachable block (ram,0x000140005b7d)
// WARNING: Removing unreachable block (ram,0x000140005b59)
// WARNING: Removing unreachable block (ram,0x000140005b4a)

undefined8 get_cpuid_2(void)

{
  int *piVar1;
  longlong lVar2;
  uint uVar3;
  byte bVar4;
  byte in_XCR0;
  
  piVar1 = (int *)cpuid_basic_info(0);
  bVar4 = 0;
  lVar2 = cpuid_Version_info(1);
  uVar3 = *(uint *)(lVar2 + 0xc);
  if (6 < *piVar1) {
    bVar4 = 0;
    lVar2 = cpuid_Extended_Feature_Enumeration_info(7);
    if ((*(uint *)(lVar2 + 4) >> 9 & 1) != 0) {
      bVar4 = 2;
    }
  }
  if (((((uVar3 >> 0x14 & 1) != 0) && ((uVar3 >> 0x1b & 1) != 0)) && ((uVar3 >> 0x1c & 1) != 0)) &&
     ((in_XCR0 & 6) == 6)) {
    bVar4 = bVar4 | 4;
  }
  DAT_1400081c0 = bVar4 | 1;
  return 0;
}



// WARNING: Unknown calling convention yet parameter storage is locked
// Library Function - Single Match
//  void __cdecl FxStubDriverUnloadCommon(void)
// 
// Library: Visual Studio 2019 Release

void FxStubDriverUnloadCommon(void)

{
  FUN_14000601c(&DAT_1400081c8);
  WdfVersionUnbind(&DAT_1400085f8,&DAT_1400081c8,DAT_140008610);
  return;
}



void entry(longlong param_1)

{
  supervisor();
  FUN_140005c3c(param_1);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

ulonglong FUN_140005c3c(longlong param_1)

{
  uint uVar1;
  ulonglong uVar2;
  undefined8 uVar3;
  
  if (param_1 == 0) {
    uVar2 = FUN_140004144();
  }
  else {
    _DAT_1400085f8 = 0x2080000;
    _DAT_140008600 = &DAT_1400083e0;
    _DAT_140008618 = param_1;
    RtlCopyUnicodeString(&DAT_1400085f8);
    uVar2 = WdfVersionBind(param_1,&DAT_1400085f8,&DAT_1400081c8,&DAT_140008610);
    if (-1 < (int)uVar2) {
      _DAT_1400085e8 = *(code **)(DAT_140008608 + 0x648);
      uVar1 = FUN_140005e98(&DAT_1400081c8);
      if (-1 < (int)uVar1) {
        uVar3 = FUN_140005dd0();
        uVar1 = (uint)uVar3;
        if (-1 < (int)uVar1) {
          uVar1 = FUN_140004144();
          if (-1 < (int)uVar1) {
            if (*(char *)(DAT_140008610 + 0x30) == '\0') {
              if ((*(uint *)(DAT_140008610 + 8) & 2) != 0) {
                _DAT_1400085e8 = FUN_140005d90;
              }
            }
            else {
              if (*(longlong *)(param_1 + 0x68) != 0) {
                DAT_140008620 = *(longlong *)(param_1 + 0x68);
              }
              *(code **)(param_1 + 0x68) = FxStubDriverUnload;
            }
            return 0;
          }
          DbgPrintEx(0x4d,0,"DriverEntry failed 0x%x for driver %wZ\n",uVar1,&DAT_1400085f8);
        }
      }
      FxStubDriverUnloadCommon();
      uVar2 = (ulonglong)uVar1;
    }
  }
  return uVar2;
}



void FUN_140005d90(void)

{
  FxStubDriverUnloadCommon();
  return;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall
// Library Function - Single Match
//  FxStubDriverUnload
// 
// Library: Visual Studio 2019 Release

void FxStubDriverUnload(void)

{
  if ((DAT_140008620 != (code *)0x0) && (DAT_140008620 != FxStubDriverUnload)) {
    (*DAT_140008620)();
  }
  FxStubDriverUnloadCommon();
  return;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall
// WARNING: Removing unreachable block (ram,0x000140005ded)

undefined8 FUN_140005dd0(void)

{
  longlong *plVar1;
  longlong lVar2;
  longlong *plVar3;
  
  plVar1 = (longlong *)&DAT_140008230;
LAB_140005e33:
  plVar3 = plVar1;
  if (plVar3 + 1 < (longlong *)((longlong)&DAT_140008230 + 1)) goto LAB_140005e26;
  goto LAB_140005e38;
LAB_140005e26:
  plVar1 = plVar3 + 1;
  if (*plVar3 != 0) {
LAB_140005e38:
    if ((longlong *)0x14000822f < plVar3) {
      return 0;
    }
    if (((&DAT_140008230 < plVar3 + 5) || (*(uint *)plVar3 != 0x28)) || (plVar3 == (longlong *)0x0))
    {
      DbgPrintEx(0x4d,0,"FxGetNextObjectContextTypeInfo failed\n");
      return 0xc000007b;
    }
    if ((code *)plVar3[4] != (code *)0x0) {
      lVar2 = (*(code *)plVar3[4])();
      plVar3[3] = lVar2;
    }
    plVar1 = (longlong *)((ulonglong)*(uint *)plVar3 + (longlong)plVar3);
  }
  goto LAB_140005e33;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall
// WARNING: Removing unreachable block (ram,0x000140005ec4)

uint FUN_140005e98(undefined8 param_1)

{
  longlong *plVar1;
  uint uVar2;
  longlong *plVar3;
  ulonglong in_stack_ffffffffffffffe0;
  
  uVar2 = 0;
  plVar1 = (longlong *)&DAT_140008210;
LAB_140005f0b:
  plVar3 = plVar1;
  if (plVar3 + 1 < (longlong *)((longlong)&DAT_140008210 + 1)) goto LAB_140005efe;
  goto LAB_140005f10;
LAB_140005efe:
  plVar1 = plVar3 + 1;
  if (*plVar3 != 0) {
LAB_140005f10:
    if ((longlong *)0x14000820f < plVar3) {
      return uVar2;
    }
    if (((&DAT_140008210 < plVar3 + 10) || (*(uint *)plVar3 != 0x50)) || (plVar3 == (longlong *)0x0)
       ) {
      DbgPrintEx(0x4d,0,"FxGetNextClassBindInfo failed\n");
      return 0xc000007b;
    }
    PTR_DAT_140008218 = (undefined *)plVar3;
    if ((code *)plVar3[7] == (code *)0x0) {
      uVar2 = WdfVersionBindClass(param_1,DAT_140008610,plVar3);
      if ((int)uVar2 < 0) {
        DbgPrintEx(0x4d,0,
                   "FxStubBindClasses: VersionBindClass WDF_CLASS_BIND_INFO 0x%p, class %S, returned status 0x%x\n"
                   ,plVar3,plVar3[1],
                   in_stack_ffffffffffffffe0 & 0xffffffff00000000 | (ulonglong)uVar2);
        return uVar2;
      }
    }
    else {
      uVar2 = (*(code *)plVar3[7])();
      if ((int)uVar2 < 0) {
        DbgPrintEx(0x4d,0,
                   "FxStubBindClasses: ClientBindClass %p, WDF_CLASS_BIND_INFO 0x%p, class %S, returned status 0x%x\n"
                   ,plVar3[7],plVar3,plVar3[1],uVar2);
        return uVar2;
      }
    }
    plVar1 = (longlong *)((ulonglong)*(uint *)plVar3 + (longlong)plVar3);
  }
  goto LAB_140005f0b;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

void FUN_14000601c(undefined8 param_1)

{
  longlong *plVar1;
  longlong *plVar2;
  longlong *plVar3;
  
  if (PTR_DAT_140008218 == &DAT_140008200) {
    return;
  }
  plVar3 = (longlong *)(PTR_DAT_140008218 + 0x50);
  plVar2 = (longlong *)&DAT_140008210;
LAB_140006063:
  plVar1 = plVar2;
  if (plVar1 + 1 <= plVar3) goto LAB_140006056;
  goto LAB_140006068;
LAB_140006056:
  plVar2 = plVar1 + 1;
  if (*plVar1 != 0) {
LAB_140006068:
    plVar2 = plVar3;
    if (((plVar1 < plVar3) && ((plVar3 < plVar1 + 10 || (plVar2 = plVar1, *(uint *)plVar1 != 0x50)))
        ) || (plVar2 == (longlong *)0x0)) {
      DbgPrintEx(0x4d,0,"FxGetNextClassBindInfo failed\n");
      return;
    }
    if (plVar3 <= plVar2) {
      return;
    }
    if ((code *)plVar2[8] == (code *)0x0) {
      WdfVersionUnbindClass(param_1,DAT_140008610,plVar2);
    }
    else {
      (*(code *)plVar2[8])();
    }
    plVar2 = (longlong *)((longlong)plVar2 + (ulonglong)*(uint *)plVar2);
  }
  goto LAB_140006063;
}



void WdfVersionBind(void)

{
                    // WARNING: Could not recover jumptable at 0x0001400060f1. Too many branches
                    // WARNING: Treating indirect jump as call
  WdfVersionBind();
  return;
}



void WdfVersionUnbind(void)

{
                    // WARNING: Could not recover jumptable at 0x0001400060f7. Too many branches
                    // WARNING: Treating indirect jump as call
  WdfVersionUnbind();
  return;
}



void WdfVersionBindClass(void)

{
                    // WARNING: Could not recover jumptable at 0x000140006100. Too many branches
                    // WARNING: Treating indirect jump as call
  WdfVersionBindClass();
  return;
}



void WdfVersionUnbindClass(void)

{
                    // WARNING: Could not recover jumptable at 0x000140006110. Too many branches
                    // WARNING: Treating indirect jump as call
  WdfVersionUnbindClass();
  return;
}



// WARNING: This is an inlined function

void _guard_dispatch_icall(void)

{
  code *UNRECOVERED_JUMPTABLE;
  
                    // WARNING: Could not recover jumptable at 0x000140006130. Too many branches
                    // WARNING: Treating indirect jump as call
  (*UNRECOVERED_JUMPTABLE)();
  return;
}



void static_init(undefined8 *param_1,undefined8 *param_2,ulonglong param_3)

{
  undefined4 *puVar1;
  undefined *puVar2;
  undefined8 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  undefined *puVar16;
  undefined8 *puVar17;
  undefined8 *puVar18;
  undefined (*pauVar19) [16];
  undefined (*pauVar20) [16];
  longlong lVar21;
  ulonglong uVar22;
  ulonglong uVar23;
  undefined4 *puVar24;
  undefined4 uVar25;
  undefined4 uVar26;
  undefined4 uVar27;
  undefined4 uVar28;
  undefined4 uVar29;
  undefined4 uVar30;
  undefined4 uVar31;
  undefined4 uVar32;
  
  if (param_3 < 8) {
    if (param_3 != 0) {
      puVar17 = param_1;
      if (param_2 < param_1) {
        puVar16 = (undefined *)((longlong)param_1 + param_3);
        do {
          puVar2 = puVar16 + ((longlong)param_2 - (longlong)param_1) + -1;
          puVar16 = puVar16 + -1;
          param_3 = param_3 - 1;
          *puVar16 = *puVar2;
        } while (param_3 != 0);
        return;
      }
      do {
        param_3 = param_3 - 1;
        *(undefined *)puVar17 =
             *(undefined *)((longlong)puVar17 + ((longlong)param_2 - (longlong)param_1));
        puVar17 = (undefined8 *)((longlong)puVar17 + 1);
      } while (param_3 != 0);
    }
    return;
  }
  if (param_3 < 0x11) {
    uVar3 = *(undefined8 *)((longlong)param_2 + (param_3 - 8));
    *param_1 = *param_2;
    *(undefined8 *)((longlong)param_1 + (param_3 - 8)) = uVar3;
    return;
  }
  if (param_3 < 0x21) {
    uVar25 = *(undefined4 *)((longlong)param_2 + 4);
    uVar27 = *(undefined4 *)(param_2 + 1);
    uVar29 = *(undefined4 *)((longlong)param_2 + 0xc);
    puVar1 = (undefined4 *)((longlong)param_2 + (param_3 - 0x10));
    uVar26 = *puVar1;
    uVar28 = puVar1[1];
    uVar30 = puVar1[2];
    uVar32 = puVar1[3];
    *(undefined4 *)param_1 = *(undefined4 *)param_2;
    *(undefined4 *)((longlong)param_1 + 4) = uVar25;
    *(undefined4 *)(param_1 + 1) = uVar27;
    *(undefined4 *)((longlong)param_1 + 0xc) = uVar29;
    puVar1 = (undefined4 *)((longlong)param_1 + (param_3 - 0x10));
    *puVar1 = uVar26;
    puVar1[1] = uVar28;
    puVar1[2] = uVar30;
    puVar1[3] = uVar32;
    return;
  }
  lVar21 = (longlong)param_2 - (longlong)param_1;
  if ((param_2 < param_1) && (param_1 < (undefined8 *)((longlong)param_2 + param_3))) {
    puVar1 = (undefined4 *)((longlong)param_1 + lVar21 + (param_3 - 0x10));
    uVar25 = puVar1[1];
    uVar27 = puVar1[2];
    uVar29 = puVar1[3];
    pauVar19 = (undefined (*) [16])((longlong)param_1 + (param_3 - 0x10));
    uVar22 = param_3 - 0x10;
    pauVar20 = pauVar19;
    uVar26 = *puVar1;
    uVar28 = uVar25;
    uVar30 = uVar27;
    uVar32 = uVar29;
    if (((ulonglong)pauVar19 & 0xf) != 0) {
      pauVar20 = (undefined (*) [16])((ulonglong)pauVar19 & 0xfffffffffffffff0);
      puVar24 = (undefined4 *)((longlong)pauVar20 + lVar21);
      uVar26 = *puVar24;
      uVar28 = puVar24[1];
      uVar30 = puVar24[2];
      uVar32 = puVar24[3];
      *(undefined4 *)*pauVar19 = *puVar1;
      *(undefined4 *)((longlong)param_1 + (param_3 - 0xc)) = uVar25;
      *(undefined4 *)((longlong)param_1 + (param_3 - 8)) = uVar27;
      *(undefined4 *)((longlong)param_1 + (param_3 - 4)) = uVar29;
      uVar22 = (longlong)pauVar20 - (longlong)param_1;
    }
    uVar23 = uVar22 >> 6;
    if (uVar23 != 0) {
      uVar22 = uVar22 & 0x3f;
      pauVar19 = pauVar20;
      uVar25 = uVar26;
      uVar27 = uVar28;
      uVar29 = uVar30;
      uVar31 = uVar32;
      do {
        puVar1 = (undefined4 *)((longlong)pauVar19 + lVar21 + -0x10);
        uVar4 = *puVar1;
        uVar5 = puVar1[1];
        uVar6 = puVar1[2];
        uVar7 = puVar1[3];
        puVar1 = (undefined4 *)((longlong)pauVar19 + lVar21 + -0x20);
        uVar8 = *puVar1;
        uVar9 = puVar1[1];
        uVar10 = puVar1[2];
        uVar11 = puVar1[3];
        puVar1 = (undefined4 *)((longlong)pauVar19 + lVar21 + -0x30);
        uVar12 = *puVar1;
        uVar13 = puVar1[1];
        uVar14 = puVar1[2];
        uVar15 = puVar1[3];
        puVar1 = (undefined4 *)((longlong)pauVar19 + lVar21 + -0x40);
        uVar26 = *puVar1;
        uVar28 = puVar1[1];
        uVar30 = puVar1[2];
        uVar32 = puVar1[3];
        *pauVar19 = CONCAT412(uVar31,CONCAT48(uVar29,CONCAT44(uVar27,uVar25)));
        pauVar20 = pauVar19[-4];
        uVar23 = uVar23 - 1;
        *(undefined4 *)pauVar19[-1] = uVar4;
        *(undefined4 *)(pauVar19[-1] + 4) = uVar5;
        *(undefined4 *)(pauVar19[-1] + 8) = uVar6;
        *(undefined4 *)(pauVar19[-1] + 0xc) = uVar7;
        *(undefined4 *)pauVar19[-2] = uVar8;
        *(undefined4 *)(pauVar19[-2] + 4) = uVar9;
        *(undefined4 *)(pauVar19[-2] + 8) = uVar10;
        *(undefined4 *)(pauVar19[-2] + 0xc) = uVar11;
        *(undefined4 *)pauVar19[-3] = uVar12;
        *(undefined4 *)(pauVar19[-3] + 4) = uVar13;
        *(undefined4 *)(pauVar19[-3] + 8) = uVar14;
        *(undefined4 *)(pauVar19[-3] + 0xc) = uVar15;
        pauVar19 = pauVar20;
        uVar25 = uVar26;
        uVar27 = uVar28;
        uVar29 = uVar30;
        uVar31 = uVar32;
      } while (uVar23 != 0);
    }
    for (uVar23 = uVar22 >> 4; uVar23 != 0; uVar23 = uVar23 - 1) {
      *pauVar20 = CONCAT412(uVar32,CONCAT48(uVar30,CONCAT44(uVar28,uVar26)));
      puVar1 = (undefined4 *)((longlong)pauVar20 + lVar21 + -0x10);
      uVar26 = *puVar1;
      uVar28 = puVar1[1];
      uVar30 = puVar1[2];
      uVar32 = puVar1[3];
      pauVar20 = pauVar20[-1];
    }
    if ((uVar22 & 0xf) != 0) {
      puVar24 = (undefined4 *)((longlong)pauVar20 - (uVar22 & 0xf));
      puVar1 = (undefined4 *)((longlong)puVar24 + lVar21);
      uVar25 = puVar1[1];
      uVar27 = puVar1[2];
      uVar29 = puVar1[3];
      *puVar24 = *puVar1;
      puVar24[1] = uVar25;
      puVar24[2] = uVar27;
      puVar24[3] = uVar29;
    }
    *pauVar20 = CONCAT412(uVar32,CONCAT48(uVar30,CONCAT44(uVar28,uVar26)));
    return;
  }
  puVar1 = (undefined4 *)((longlong)param_1 + lVar21);
  uVar25 = puVar1[1];
  uVar27 = puVar1[2];
  uVar29 = puVar1[3];
  puVar17 = param_1 + 2;
  uVar26 = *puVar1;
  uVar28 = uVar25;
  uVar30 = uVar27;
  uVar32 = uVar29;
  if (((ulonglong)puVar17 & 0xf) != 0) {
    puVar24 = (undefined4 *)(((ulonglong)puVar17 & 0xfffffffffffffff0) + lVar21);
    uVar26 = *puVar24;
    uVar28 = puVar24[1];
    uVar30 = puVar24[2];
    uVar32 = puVar24[3];
    *(undefined4 *)param_1 = *puVar1;
    *(undefined4 *)((longlong)param_1 + 4) = uVar25;
    *(undefined4 *)(param_1 + 1) = uVar27;
    *(undefined4 *)((longlong)param_1 + 0xc) = uVar29;
    puVar17 = (undefined8 *)(((ulonglong)puVar17 & 0xfffffffffffffff0) + 0x10);
  }
  uVar22 = (longlong)param_1 + (param_3 - (longlong)puVar17);
  uVar23 = uVar22 >> 6;
  if (uVar23 != 0) {
    if (uVar23 < 0x1001) {
      uVar22 = uVar22 & 0x3f;
      puVar18 = puVar17;
      uVar25 = uVar26;
      uVar27 = uVar28;
      uVar29 = uVar30;
      uVar31 = uVar32;
      do {
        puVar1 = (undefined4 *)((longlong)puVar18 + lVar21);
        uVar4 = *puVar1;
        uVar5 = puVar1[1];
        uVar6 = puVar1[2];
        uVar7 = puVar1[3];
        puVar1 = (undefined4 *)((longlong)puVar18 + lVar21 + 0x10);
        uVar8 = *puVar1;
        uVar9 = puVar1[1];
        uVar10 = puVar1[2];
        uVar11 = puVar1[3];
        puVar1 = (undefined4 *)((longlong)puVar18 + lVar21 + 0x20);
        uVar12 = *puVar1;
        uVar13 = puVar1[1];
        uVar14 = puVar1[2];
        uVar15 = puVar1[3];
        puVar1 = (undefined4 *)((longlong)puVar18 + lVar21 + 0x30);
        uVar26 = *puVar1;
        uVar28 = puVar1[1];
        uVar30 = puVar1[2];
        uVar32 = puVar1[3];
        *(undefined (*) [16])(puVar18 + -2) =
             CONCAT412(uVar31,CONCAT48(uVar29,CONCAT44(uVar27,uVar25)));
        puVar17 = puVar18 + 8;
        uVar23 = uVar23 - 1;
        *(undefined4 *)puVar18 = uVar4;
        *(undefined4 *)((longlong)puVar18 + 4) = uVar5;
        *(undefined4 *)(puVar18 + 1) = uVar6;
        *(undefined4 *)((longlong)puVar18 + 0xc) = uVar7;
        *(undefined4 *)(puVar18 + 2) = uVar8;
        *(undefined4 *)((longlong)puVar18 + 0x14) = uVar9;
        *(undefined4 *)(puVar18 + 3) = uVar10;
        *(undefined4 *)((longlong)puVar18 + 0x1c) = uVar11;
        *(undefined4 *)(puVar18 + 4) = uVar12;
        *(undefined4 *)((longlong)puVar18 + 0x24) = uVar13;
        *(undefined4 *)(puVar18 + 5) = uVar14;
        *(undefined4 *)((longlong)puVar18 + 0x2c) = uVar15;
        puVar18 = puVar17;
        uVar25 = uVar26;
        uVar27 = uVar28;
        uVar29 = uVar30;
        uVar31 = uVar32;
      } while (uVar23 != 0);
    }
    else {
      uVar23 = uVar22 >> 6;
      uVar22 = uVar22 & 0x3f;
      puVar18 = puVar17;
      uVar25 = uVar26;
      uVar27 = uVar28;
      uVar29 = uVar30;
      uVar31 = uVar32;
      do {
        puVar1 = (undefined4 *)((longlong)puVar18 + lVar21);
        uVar4 = *puVar1;
        uVar5 = puVar1[1];
        uVar6 = puVar1[2];
        uVar7 = puVar1[3];
        puVar1 = (undefined4 *)((longlong)puVar18 + lVar21 + 0x10);
        uVar8 = *puVar1;
        uVar9 = puVar1[1];
        uVar10 = puVar1[2];
        uVar11 = puVar1[3];
        puVar1 = (undefined4 *)((longlong)puVar18 + lVar21 + 0x20);
        uVar12 = *puVar1;
        uVar13 = puVar1[1];
        uVar14 = puVar1[2];
        uVar15 = puVar1[3];
        puVar1 = (undefined4 *)((longlong)puVar18 + lVar21 + 0x30);
        uVar26 = *puVar1;
        uVar28 = puVar1[1];
        uVar30 = puVar1[2];
        uVar32 = puVar1[3];
        *(undefined (*) [16])(puVar18 + -2) =
             CONCAT412(uVar31,CONCAT48(uVar29,CONCAT44(uVar27,uVar25)));
        puVar17 = puVar18 + 8;
        uVar23 = uVar23 - 1;
        *(undefined4 *)puVar18 = uVar4;
        *(undefined4 *)((longlong)puVar18 + 4) = uVar5;
        *(undefined4 *)(puVar18 + 1) = uVar6;
        *(undefined4 *)((longlong)puVar18 + 0xc) = uVar7;
        *(undefined4 *)(puVar18 + 2) = uVar8;
        *(undefined4 *)((longlong)puVar18 + 0x14) = uVar9;
        *(undefined4 *)(puVar18 + 3) = uVar10;
        *(undefined4 *)((longlong)puVar18 + 0x1c) = uVar11;
        *(undefined4 *)(puVar18 + 4) = uVar12;
        *(undefined4 *)((longlong)puVar18 + 0x24) = uVar13;
        *(undefined4 *)(puVar18 + 5) = uVar14;
        *(undefined4 *)((longlong)puVar18 + 0x2c) = uVar15;
        puVar18 = puVar17;
        uVar25 = uVar26;
        uVar27 = uVar28;
        uVar29 = uVar30;
        uVar31 = uVar32;
      } while (uVar23 != 0);
    }
  }
  for (uVar23 = uVar22 >> 4; uVar23 != 0; uVar23 = uVar23 - 1) {
    *(undefined (*) [16])(puVar17 + -2) = CONCAT412(uVar32,CONCAT48(uVar30,CONCAT44(uVar28,uVar26)))
    ;
    puVar1 = (undefined4 *)((longlong)puVar17 + lVar21);
    uVar26 = *puVar1;
    uVar28 = puVar1[1];
    uVar30 = puVar1[2];
    uVar32 = puVar1[3];
    puVar17 = puVar17 + 2;
  }
  if ((uVar22 & 0xf) != 0) {
    puVar24 = (undefined4 *)((longlong)puVar17 + ((uVar22 & 0xf) - 0x10));
    puVar1 = (undefined4 *)((longlong)puVar24 + lVar21);
    uVar25 = puVar1[1];
    uVar27 = puVar1[2];
    uVar29 = puVar1[3];
    *puVar24 = *puVar1;
    puVar24[1] = uVar25;
    puVar24[2] = uVar27;
    puVar24[3] = uVar29;
  }
  *(undefined (*) [16])(puVar17 + -2) = CONCAT412(uVar32,CONCAT48(uVar30,CONCAT44(uVar28,uVar26)));
  return;
}



undefined (*) [16] static_init_2(undefined (*param_1) [16],byte param_2,ulonglong param_3)

{
  undefined (*pauVar1) [16];
  undefined (*pauVar2) [16];
  undefined (*pauVar3) [16];
  undefined4 uVar4;
  longlong lVar5;
  undefined *puVar6;
  ulonglong uVar7;
  undefined (*pauVar8) [16];
  undefined auVar9 [16];
  undefined extraout_XMM0 [16];
  
  pauVar1 = param_1;
  lVar5 = (ulonglong)param_2 * 0x101010101010101;
  auVar9 = CONCAT88(lVar5,lVar5);
  if (param_3 < 0x40) {
    if (param_3 < 0x10) {
      if (3 < param_3) {
        uVar4 = (undefined4)lVar5;
        *(undefined4 *)*param_1 = uVar4;
        uVar7 = (param_3 & 8) >> 1;
        *(undefined4 *)(param_1[-1] + param_3 + 0xc) = uVar4;
        *(undefined4 *)(*param_1 + uVar7) = uVar4;
        *(undefined4 *)((longlong)(param_1[-1] + param_3 + 0xc) - uVar7) = uVar4;
        return pauVar1;
      }
      if (param_3 != 0) {
        (*param_1)[0] = (char)lVar5;
        if (param_3 != 1) {
          *(short *)(param_1[-1] + param_3 + 0xe) = (short)lVar5;
        }
      }
      return pauVar1;
    }
  }
  else {
    if (((DAT_1400081c0 & 2) != 0) && (799 < param_3)) {
      if ((DAT_1400081c0 & 1) == 0) {
        param_1 = (undefined (*) [16])static_init_3();
        auVar9 = extraout_XMM0;
      }
      *pauVar1 = auVar9;
      pauVar1[1] = auVar9;
      pauVar1[2] = auVar9;
      pauVar1[3] = auVar9;
      puVar6 = (undefined *)((ulonglong)pauVar1[4] & 0xffffffffffffffc0);
      for (lVar5 = (longlong)pauVar1 +
                   (param_3 - (longlong)(undefined *)((ulonglong)pauVar1[4] & 0xffffffffffffffc0));
          lVar5 != 0; lVar5 = lVar5 + -1) {
        *puVar6 = SUB161(auVar9,0);
        puVar6 = puVar6 + 1;
      }
      return param_1;
    }
    *param_1 = auVar9;
    pauVar2 = (undefined (*) [16])((ulonglong)param_1[1] & 0xfffffffffffffff0);
    param_3 = (longlong)param_1 + (param_3 - (longlong)pauVar2);
    param_1 = pauVar2;
    if (0x3f < param_3) {
      pauVar8 = (undefined (*) [16])((longlong)pauVar2 + (param_3 - 0x30) & 0xfffffffffffffff0);
      uVar7 = param_3 >> 6;
      pauVar3 = pauVar2;
      do {
        *pauVar3 = auVar9;
        pauVar3[1] = auVar9;
        uVar7 = uVar7 - 1;
        pauVar3[2] = auVar9;
        pauVar3[3] = auVar9;
        pauVar3 = pauVar3[4];
      } while (uVar7 != 0);
      *pauVar8 = auVar9;
      pauVar8[1] = auVar9;
      pauVar8[2] = auVar9;
      *(undefined (*) [16])((longlong)pauVar2 + (param_3 - 0x10)) = auVar9;
      return pauVar1;
    }
  }
  *param_1 = auVar9;
  uVar7 = (param_3 & 0x20) >> 1;
  *(undefined (*) [16])(param_1[-1] + param_3) = auVar9;
  *(undefined (*) [16])(*param_1 + uVar7) = auVar9;
  *(undefined (*) [16])((longlong)(undefined (*) [16])(param_1[-1] + param_3) - uVar7) = auVar9;
  return pauVar1;
}



undefined8 static_init_3(void)

{
  undefined8 in_RAX;
  
  get_cpuid_2();
  return in_RAX;
}



void win_1400067c0(undefined8 param_1,ulonglong param_2)

{
  longlong lVar1;
  longlong lVar2;
  
  DAT_140008098 = KeAcquireSpinLockRaiseToDpc(&DAT_140008090);
  lVar2 = DAT_140008078;
  while (lVar2 != 0) {
    lVar1 = *(longlong *)(lVar2 + 8);
    param_2 = 0;
    ExFreePoolWithTag(lVar2,0);
    lVar2 = lVar1;
  }
  DAT_140008078 = 0;
  DAT_140008080 = 0;
  KeReleaseSpinLock(&DAT_140008090,param_2 & 0xffffffffffffff00 | (ulonglong)DAT_140008098);
  DAT_140008078 = 0;
  DAT_140008080 = 0;
  PTR_PTR_win_140008088 = (undefined *)&PTR_win_1400071a0;
  return;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall
// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void win_14000b074(void)

{
  undefined *puVar1;
  
  puVar1 = &DAT_140008390;
  if (PTR_LOOP_1400080a0 != &DAT_140008390) {
    PTR_LOOP_1400080a0 = &DAT_140008390;
    if (DAT_140008270 == 4) {
      do {
        *(undefined8 *)(puVar1 + 0x38) = 0;
        (*DAT_140008260)();
        puVar1 = *(undefined **)(puVar1 + 0x10);
      } while (puVar1 != (undefined *)0x0);
      return;
    }
    if (DAT_140008270 == 2) {
      _DAT_140008390 = win_14000b200;
      IoWMIRegistrationControl(&DAT_140008390,0x80010001);
    }
  }
  return;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall
// WARNING: Removing unreachable block (ram,0x00014000b19d)
// WARNING: Removing unreachable block (ram,0x00014000b1c4)
// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void win_14000b0fc(void)

{
  undefined local_18 [16];
  
  RtlInitUnicodeString(local_18,L"PsGetVersion");
  DAT_140008268 = MmGetSystemRoutineAddress(local_18);
  RtlInitUnicodeString(local_18,L"WmiTraceMessage");
  _DAT_140008250 = MmGetSystemRoutineAddress(local_18);
  RtlInitUnicodeString(local_18,L"WmiQueryTraceInformation");
  DAT_140008248 = MmGetSystemRoutineAddress(local_18);
  DAT_140008270 = 2;
  if (DAT_140008268 != 0) {
    (*(code *)DAT_140008268)();
  }
  return;
}



// WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall

undefined4
win_14000b200(byte param_1,undefined8 param_2,uint param_3,undefined (*param_4) [16],
             longlong param_5,uint *param_6)

{
  int *piVar1;
  undefined8 uVar2;
  ushort *puVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  undefined4 uVar9;
  longlong lVar10;
  ulonglong uVar11;
  uint uVar12;
  undefined4 *puVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  undefined local_res8;
  undefined uStack54;
  undefined4 uStack52;
  
  uVar11 = 0;
  uVar12 = 0;
  *param_6 = 0;
  if (param_1 < 6) {
    if ((param_1 == 5) ||
       ((((param_1 != 0 && (param_1 != 1)) && (param_1 != 2)) && ((param_1 != 3 && (param_1 == 4))))
       )) {
      if (param_5 != 0) {
        if (param_3 < 0x30) {
          return 0xc000000d;
        }
        do {
          piVar1 = *(int **)(param_5 + 8);
          if (((*piVar1 == *(int *)(param_4[1] + 8)) && (piVar1[1] == *(int *)(param_4[1] + 0xc)))
             && ((piVar1[2] == *(int *)param_4[2] && (piVar1[3] == *(int *)(param_4[2] + 4)))))
          break;
          param_5 = *(longlong *)(param_5 + 0x10);
        } while (param_5 != 0);
        if (param_5 != 0) {
          if (param_1 == 5) {
            *(undefined4 *)(param_5 + 0x2c) = 0;
            *(undefined8 *)(param_5 + 0x18) = 0;
            *(undefined *)(param_5 + 0x29) = 0;
            return 0;
          }
          uVar2 = *(undefined8 *)(*param_4 + 8);
          *(undefined8 *)(param_5 + 0x18) = uVar2;
          if (DAT_140008270 != 2) {
            uStack52 = (undefined4)((ulonglong)uVar2 >> 0x20);
            *(undefined4 *)(param_5 + 0x2c) = uStack52;
            uStack54 = (undefined)((ulonglong)uVar2 >> 0x10);
            *(undefined *)(param_5 + 0x29) = uStack54;
            return 0;
          }
          iVar8 = (*DAT_140008248)();
          if (iVar8 == 0) {
            *(undefined *)(param_5 + 0x29) = local_res8;
          }
          uVar9 = (*DAT_140008248)();
          return uVar9;
        }
      }
      return 0xc0000295;
    }
  }
  else {
    if (param_1 == 6) {
      return 0;
    }
    if (param_1 == 7) {
      return 0;
    }
    if (param_1 == 8) {
      puVar3 = *(ushort **)(param_5 + 0x20);
      lVar10 = param_5;
      do {
        lVar10 = *(longlong *)(lVar10 + 0x10);
        uVar14 = (int)uVar11 + 1;
        uVar11 = (ulonglong)uVar14;
      } while (lVar10 != 0);
      if (0x3f < uVar14) {
        return 0xc000000d;
      }
      uVar15 = uVar14 * 0x20 + 0x18;
      uVar16 = uVar15;
      if (puVar3 != (ushort *)0x0) {
        uVar16 = *puVar3 + 2 + uVar15;
        uVar12 = uVar15;
      }
      if (param_3 < uVar16) {
        if (3 < param_3) {
          *(uint *)*param_4 = uVar16;
          *param_6 = 4;
          return 0xc0000023;
        }
        return 0xc0000023;
      }
      static_init_2(param_4,0,(ulonglong)param_3);
      *(uint *)*param_4 = uVar16;
      *(uint *)(*param_4 + 8) = uVar12;
      *(uint *)param_4[1] = uVar14;
      if (puVar3 != (ushort *)0x0) {
        *(ushort *)(*param_4 + uVar12) = *puVar3;
        static_init((undefined8 *)((longlong)(*param_4 + uVar12) + 2),*(undefined8 **)(puVar3 + 4),
                    (ulonglong)*puVar3);
      }
      if (uVar14 != 0) {
        puVar13 = (undefined4 *)(param_4[2] + 8);
        do {
          puVar4 = *(undefined4 **)(param_5 + 8);
          uVar9 = *puVar4;
          uVar5 = puVar4[1];
          uVar6 = puVar4[2];
          uVar7 = puVar4[3];
          *puVar13 = 0x81000;
          puVar13[-4] = uVar9;
          puVar13[-3] = uVar5;
          puVar13[-2] = uVar6;
          puVar13[-1] = uVar7;
          *(undefined *)(param_5 + 0x29) = 0;
          *(undefined4 *)(param_5 + 0x2c) = 0;
          param_5 = *(longlong *)(param_5 + 0x10);
          uVar11 = uVar11 - 1;
          puVar13 = puVar13 + 8;
        } while (uVar11 != 0);
      }
      *param_6 = uVar16;
      return 0;
    }
  }
  return 0xc0000010;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void supervisor(void)

{
  code *pcVar1;
  
  if ((DAT_1400081b0 != 0) && (DAT_1400081b0 != 0x2b992ddfa232)) {
    _DAT_1400081b8 = ~DAT_1400081b0;
    return;
  }
  pcVar1 = (code *)swi(0x29);
  (*pcVar1)(6);
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}



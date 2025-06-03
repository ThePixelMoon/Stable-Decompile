#include "LLawnLib.h"
#include "../../PakLib/PakInterface.h"

using namespace Sexy;

std::string FileTimeToString(const FILETIME& ft) {
    SYSTEMTIME st;
    FileTimeToSystemTime(&ft, &st);
    char buffer[64];
    sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d", 
            st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
    return std::string(buffer);
}

void open_pak(sol::state_view lua) {
    lua.new_usertype<PakRecord>("PakRecord",
        "mCollection", &PakRecord::mCollection,
        "mFileName", &PakRecord::mFileName,
        "mFileTime", sol::property([](const PakRecord& p) { return FileTimeToString(p.mFileTime); }),
        "mStartPos", &PakRecord::mStartPos,
        "mSize", &PakRecord::mSize
    );

    lua.new_usertype<PakCollection>("PakCollection",
        "mFileHandle", &PakCollection::mFileHandle,
        "mMappingHandle", &PakCollection::mMappingHandle,
        "mDataPtr", &PakCollection::mDataPtr
    );

    lua.new_usertype<PFILE>("PFILE",
        "mRecord", &PFILE::mRecord,
        "mPos", &PFILE::mPos,
        "mFP", &PFILE::mFP
    );

    lua.new_usertype<PFindData>("PFindData",
        "mWHandle", &PFindData::mWHandle,
        "mLastFind", &PFindData::mLastFind,
        "mFindCriteria", &PFindData::mFindCriteria
    );

    lua.new_usertype<PakInterface>("PakInterface",
        "AddPakFile", &PakInterface::AddPakFile,

        "FOpen", [](PakInterface& self, const std::string& filename, const std::string& access) {
            return self.FOpen(filename.c_str(), access.c_str());
        },

        "FClose", &PakInterface::FClose,
        "FSeek", &PakInterface::FSeek,
        "FTell", &PakInterface::FTell,

        "FRead", [](PakInterface& self, void* buffer, int elemSize, int count, PFILE* file) {
            return self.FRead(buffer, elemSize, count, file);
        },

        "FReadString", [](PakInterface& self, PFILE* file, int bytesToRead) -> std::string {
            if (!file || bytesToRead <= 0) return std::string();
            std::string buffer(bytesToRead, '\0');
            size_t readCount = self.FRead((void*)buffer.data(), 1, bytesToRead, file);
            buffer.resize(readCount);
            return buffer;
        },

        "FGetC", &PakInterface::FGetC,
        "UnGetC", &PakInterface::UnGetC,

        "FGetS", &PakInterface::FGetS,

        "FEof", &PakInterface::FEof,

        "FindFirstFile", &PakInterface::FindFirstFile,
        "FindNextFile", &PakInterface::FindNextFile,
        "FindClose", &PakInterface::FindClose
    );

    lua["PakInterface"] = gPakInterface;
}
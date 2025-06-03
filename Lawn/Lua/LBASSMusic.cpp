#include "LLawnLib.h"
#include "../../SexyAppFramework/BassMusicInterface.h"
#include "../../Lawn/System/Music.h"
#include "../../LawnApp.h"

using namespace Sexy;

void open_bassmusic(sol::state_view lua) {
    sol::table sexy;
    if (lua["Sexy"].valid() && lua["Sexy"].get_type() == sol::type::table) {
        sexy = lua["Sexy"];
    } else {
        sexy = lua.create_table();
        lua["Sexy"] = sexy;
    }

    sexy.new_usertype<BassMusicInterface>("BassMusicInterface",
        "LoadMusic",         &BassMusicInterface::LoadMusic,
        "PlayMusic",         &BassMusicInterface::PlayMusic,
        "StopMusic",         &BassMusicInterface::StopMusic,
        "PauseMusic",        &BassMusicInterface::PauseMusic,
        "ResumeMusic",       &BassMusicInterface::ResumeMusic,
        "StopAllMusic",      &BassMusicInterface::StopAllMusic,
        "UnloadMusic",       &BassMusicInterface::UnloadMusic,
        "UnloadAllMusic",    &BassMusicInterface::UnloadAllMusic,
        "PauseAllMusic",     &BassMusicInterface::PauseAllMusic,
        "ResumeAllMusic",    &BassMusicInterface::ResumeAllMusic,
        "FadeIn",            &BassMusicInterface::FadeIn,
        "FadeOut",           &BassMusicInterface::FadeOut,
        "FadeOutAll",        &BassMusicInterface::FadeOutAll,
        "SetSongVolume",     &BassMusicInterface::SetSongVolume,
        "SetSongMaxVolume",  &BassMusicInterface::SetSongMaxVolume,
        "SetVolume",         &BassMusicInterface::SetVolume,
        "SetMusicAmplify",   &BassMusicInterface::SetMusicAmplify,
        "IsPlaying",         &BassMusicInterface::IsPlaying,
        "Update",            &BassMusicInterface::Update,

        "GetMusicOrder",     &BassMusicInterface::GetMusicOrder,
        "GetChannelPosition",&BassMusicInterface::GetChannelPosition
    );

    lua["GetBassMusic"] = []() -> BassMusicInterface *{
        return static_cast<BassMusicInterface *>(gLawnApp->mMusicInterface);
    };
}
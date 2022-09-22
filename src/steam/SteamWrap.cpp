#include "SteamWrap.h"

using namespace godot;

void SteamWrap::_register_methods()
{
    register_property<SteamWrap, String>("app_id", &SteamWrap::app_id, "");

    register_method("set_app_id", &SteamWrap::set_app_id);
    register_method("get_app_id", &SteamWrap::get_app_id);
}

void SteamWrap::_init()
{
    app_id = "";
}

void SteamWrap::set_app_id(String p_app_id)
{
    app_id = p_app_id;
}

godot::String SteamWrap::get_app_id()
{
    return app_id;
}

SteamWrap::SteamWrap()
{}

SteamWrap::~SteamWrap()
{}
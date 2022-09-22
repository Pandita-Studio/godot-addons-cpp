#include "DiscordWrap.h"

using namespace std;
using namespace godot;

void DiscordWrap::_register_methods()
{
    register_property<DiscordWrap, int16_t>("end_time", &DiscordWrap::set_end_time, &DiscordWrap::get_end_time, 0);
    register_property<DiscordWrap, int16_t>("activity_time", &DiscordWrap::set_activity_time, &DiscordWrap::get_activity_time, 0);
    register_property<DiscordWrap, int64_t>("client_id", &DiscordWrap::set_client_id, &DiscordWrap::get_client_id, 0.0);
    register_property<DiscordWrap, String>("activity_large_image", &DiscordWrap::set_activity_large_image, &DiscordWrap::get_activity_large_image, "");
    register_property<DiscordWrap, String>("activity_small_image", &DiscordWrap::set_activity_small_image, &DiscordWrap::get_activity_small_image, "");
    register_property<DiscordWrap, String>("activity_state", &DiscordWrap::set_activity_state, &DiscordWrap::get_activity_state, "");
    register_property<DiscordWrap, String>("activity_details", &DiscordWrap::set_activity_details, &DiscordWrap::get_activity_details, "");

    register_method("_process", &DiscordWrap::_process);
    register_method("init", &DiscordWrap::init);
    register_method("update_activity", &DiscordWrap::update_activity);
    register_method("clear_end_time", &DiscordWrap::clear_end_time);
    register_method("clear_activity_time", &DiscordWrap::clear_activity_time);
    register_method("clear_activity_small_image", &DiscordWrap::clear_activity_small_image);
    register_method("clear_activity_large_image", &DiscordWrap::clear_activity_large_image);
}

void DiscordWrap::_init()
{
    start_time = time(0);
    core_creation_ok = false;
    client_id = 1020053067326029926;
    activity_large_image = "";
    activity_small_image = "";
    activity_state = "";
    activity_details = "";
}

void DiscordWrap::_process(float delta)
{
    if (core_creation_ok)
        core->RunCallbacks();
}

void DiscordWrap::log(String msg)
{
    Godot::print("[DiscordWrap] " + msg);
}

void DiscordWrap::init()
{
    discord::ClientId client_id_obj = client_id;

    auto result = discord::Core::Create(client_id_obj, DiscordCreateFlags_NoRequireDiscord, &core);

    if (result != discord::Result::Ok) {
        DiscordWrap::log("Error: Core init failed. Discord is not running maybe?");
        return;
    }
    
    core_creation_ok = true;

    core->SetLogHook(discord::LogLevel::Info, [](discord::LogLevel level, const char *msg) {
        switch (level) {
            case discord::LogLevel::Warn:
                DiscordWrap::log(strcat("Warning: ", msg));
                break;

            case discord::LogLevel::Info:
                DiscordWrap::log(strcat("Info: ", msg));
                break;

            case discord::LogLevel::Error:
                DiscordWrap::log(strcat("Error: ", msg));
                break;
        }
    });
}

void DiscordWrap::clear_end_time()
{
    end_time = -1;
}

void DiscordWrap::clear_activity_time()
{
    activity_time = -1;
}

void DiscordWrap::clear_activity_small_image()
{
    activity_small_image = "";
}

void DiscordWrap::clear_activity_large_image()
{
    activity_large_image = "";
}

void DiscordWrap::update_activity()
{
    if (!core_creation_ok)
    {
        DiscordWrap::log("Error: cannot update activity, core is not initialized.");
        return;
    }

    discord::Activity activity{};

    activity.SetType(discord::ActivityType::Playing);

    if (end_time > 0)
        activity.GetTimestamps().SetEnd(end_time);
    
    else if (activity_time > 0)
        activity.GetTimestamps().SetStart(activity_time);
    
    else
        activity.GetTimestamps().SetStart(start_time);

    if (strcmp(activity_state, "") != 0)
        activity.SetState(activity_state);
    
    if (strcmp(activity_details, "") != 0)
        activity.SetDetails(activity_details);

    if (strcmp(activity_large_image, "") != 0)
        activity.GetAssets().SetLargeImage(activity_large_image);
    
    if (strcmp(activity_small_image, "") != 0)
        activity.GetAssets().SetSmallImage(activity_small_image);

    core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {
        if (result != discord::Result::Ok)
            DiscordWrap::log("Failed to update activity.");
    });
}

void DiscordWrap::set_end_time(int16_t p_end_time)
{
    if (p_end_time < 0)
    {
        end_time = 0;
        return;
    }

    end_time = time(0) + p_end_time;
}

int16_t DiscordWrap::get_end_time()
{
    return end_time;
}

void DiscordWrap::set_activity_time(int16_t p_activity_time)
{
    if (p_activity_time < 0)
    {
        activity_time = 0;
        return;
    }

    activity_time = time(0) + p_activity_time;
}

int16_t DiscordWrap::get_activity_time()
{
    return activity_time;
}

void DiscordWrap::set_client_id(int64_t p_client_id)
{
    client_id = p_client_id;
}

int64_t DiscordWrap::get_client_id()
{
    return client_id;
}

void DiscordWrap::set_activity_large_image(String p_large_image)
{
    activity_large_image = p_large_image.alloc_c_string();
}

String DiscordWrap::get_activity_large_image()
{
    return String(activity_large_image);
}

void DiscordWrap::set_activity_small_image(String p_small_image)
{
    activity_small_image = p_small_image.alloc_c_string();
}

String DiscordWrap::get_activity_small_image()
{
    return String(activity_small_image);
}

void DiscordWrap::set_activity_state(String p_activity_state)
{
    activity_state = p_activity_state.alloc_c_string();
}

String DiscordWrap::get_activity_state()
{
    return String(activity_state);
}

void DiscordWrap::set_activity_details(String p_activity_details)
{
    activity_details = p_activity_details.alloc_c_string();
}

String DiscordWrap::get_activity_details()
{
    return String(activity_details);
}

DiscordWrap::DiscordWrap()
{}

DiscordWrap::~DiscordWrap()
{
    delete core;
}
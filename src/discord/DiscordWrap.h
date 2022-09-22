#pragma once

#include <ctime>

#include <Godot.hpp>
#include <Node.hpp>

#include "discord.h"

namespace godot
{
    class DiscordWrap : public Node
    {
        GODOT_CLASS(DiscordWrap, Node)

    protected:
        discord::Core *core{};
        int64_t client_id;

        char *activity_large_image;
        char *activity_small_image;
        char *activity_state;
        char *activity_details;
        
        std::time_t end_time;
        std::time_t start_time;
        std::time_t activity_time;

        bool core_creation_ok;

    public:
        static void log(String msg);
        static void _register_methods();

        void _init();
        void _process(float delta);

        void init();
        void clear_end_time();
        void clear_activity_time();
        void clear_activity_small_image();
        void clear_activity_large_image();

        void update_activity();

        void set_end_time(int16_t p_end_time);
        int16_t get_end_time();

        void set_activity_time(int16_t p_activity_time);
        int16_t get_activity_time();

        void set_client_id(int64_t p_client_id);
        int64_t get_client_id();

        void set_activity_large_image(String p_large_image);
        String get_activity_large_image();

        void set_activity_small_image(String p_small_image);
        String get_activity_small_image();

        void set_activity_state(String p_activity_state);
        String get_activity_state();

        void set_activity_details(String p_activity_details);
        String get_activity_details();

        DiscordWrap();
        ~DiscordWrap();
    };    
} // namespace godot

#pragma once

#include <Godot.hpp>
#include <Node.hpp>

namespace godot
{
    class SteamWrap : public Node
    {
        GODOT_CLASS(SteamWrap, Node)

    protected:
        godot::String app_id;

    public:
        static void _register_methods();

        void _init();

        void set_app_id(godot::String p_app_id);
        godot::String get_app_id();

        SteamWrap();
        ~SteamWrap();
    };    
} // namespace godot

#pragma once

#include "modules/meta/event_handler.hpp"
#include "modules/meta/static_module.hpp"
#include "x11/events.hpp"
#include "x11/ewmh.hpp"
#include "x11/icccm.hpp"
#include "x11/window.hpp"

POLYBAR_NS

class connection;

namespace modules {
  class active_window {
   public:
    explicit active_window(xcb_connection_t* conn, xcb_window_t win);
    ~active_window();

    bool match(const xcb_window_t win) const;
    string title(xcb_ewmh_connection_t* ewmh) const;

   private:
    xcb_connection_t* m_connection{nullptr};
    xcb_window_t m_window{XCB_NONE};
  };

  /**
   * Module used to display information about the
   * currently active X window.
   */
  class xwindow_module : public static_module<xwindow_module>, public event_handler<evt::property_notify> {
   public:
    explicit xwindow_module(const bar_settings&, string);

    void update(bool force = false);
    bool build(builder* builder, const string& tag) const;

   protected:
    void handle(const evt::property_notify& evt);

   private:
    static constexpr const char* TAG_LABEL{"<label>"};

    connection& m_connection;
    ewmh_connection_t m_ewmh;
    unique_ptr<active_window> m_active;
    label_t m_label;
  };
}

POLYBAR_NS_END

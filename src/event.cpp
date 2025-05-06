#include "event.h"
#include "clock_time.h"
#include "utils.h"

#include <iomanip>
#include <iostream>
#include <vector>
#include <memory>
#include <optional>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

Event::Event(Time time, std::optional<int> id) : time_(time), id_(id) {};

istringstream &operator>>(istringstream& f, Event& event) {
    f >> event.time_;

    int id;
    f >> id;
    if (f.fail()) return f;

    event.id_ = id;
    return f;
}

ostream &operator<<(ostream& f, const Event& event) {
    f << event.time_ << " " << event.id_.value() << " ";
    return f;
}

Time Event::get_time() { return time_; }
int Event::get_id() { return id_.value(); }

// OUTGOING EVENT
OutgoingEvent::OutgoingEvent() : Event(Time(), nullopt), table_number_(nullopt) { }

istringstream &operator>>(istringstream& f, OutgoingEvent& event) {
    f >> static_cast<Event &>(event);
    if (f.fail()) return f;

    f >> event.client_name_;
    if (f.fail()) return f;

    if (event.id_ == 2) {
        int table_number;
        f >> table_number;
        if (f.fail()) return f;

        event.table_number_ = table_number;
    }

    return f;
}

ostream &operator<<(std::ostream& f, OutgoingEvent& event) {
    f << static_cast<Event &>(event) << event.client_name_;
    if (event.id_ == 2) {
        f << " " << event.table_number_.value();
    }
    f << '\n';
    return f;
}

int OutgoingEvent::get_table_number() { return table_number_.value(); }
string OutgoingEvent::get_client_name() { return client_name_; }

// INCOMING EVENT
IncomingEvent::IncomingEvent(Time time, int id, optional<string> client_name, optional<string> fault, optional<int> table_number) : 
    Event(time, id), client_name_(client_name), fault_(fault), table_number_(table_number) { };

ostream &operator<<(std::ostream& f, IncomingEvent& event) {
    f << static_cast<Event &>(event);
    if (event.client_name_ && event.table_number_) {
        f << event.client_name_.value() << " " << event.table_number_.value() << '\n';
    }
    else if (event.client_name_) {
        f << event.client_name_.value() << '\n';
    }
    else if (event.fault_) {
        f << event.fault_.value() << '\n';
    }

    return f;
}

int IncomingEvent::get_table_number() { return table_number_.value(); }
string IncomingEvent::get_client_name() { return client_name_.value(); }
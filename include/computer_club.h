#ifndef COMPUTER_CLUB_H
#define COMPUTER_CLUB_H

#include <iostream>
#include <vector>
#include <memory>
#include <optional>
#include <queue>
#include <deque>
#include <set>

class Time {
public:
    Time() = default;
    Time(int, int);
    ~Time() = default;

    friend std::ifstream &operator>>(std::ifstream&, Time&);
    friend std::ostream &operator<<(std::ostream&, const Time&);

    Time operator+(const Time &);
    Time operator-(const Time &);

    friend bool operator<(Time&, Time&);

    int get_hours();
    int get_minutes();

private:
    int hours_;
    int minutes_;
};


class Event {
public:
    Event(Time, std::optional<int>);
    ~Event() = default;

    friend std::ifstream &operator>>(std::ifstream&, Event&);
    friend std::ostream &operator<<(std::ostream&, const Event&);

    Time get_time();
    int get_id();

protected:
    Time time_;
    std::optional<int> id_;
};

class OutgoingEvent : public Event {
public:
    OutgoingEvent();
    ~OutgoingEvent() = default;

    friend std::ifstream &operator>>(std::ifstream&, OutgoingEvent&);
    friend std::ostream &operator<<(std::ostream&, OutgoingEvent&);

    int get_table_number();
    std::string get_client_name();

private:
    std::string client_name_;
    std::optional<int> table_number_;
};

class IncomingEvent : public Event {
public:
    IncomingEvent(Time, int, std::optional<std::string> = std::nullopt,
                  std::optional<std::string> = std::nullopt, std::optional<int> = std::nullopt);
    ~IncomingEvent() = default;

    friend std::ostream &operator<<(std::ostream&, IncomingEvent&);

    int get_table_number();
    std::string get_client_name();

private:
    std::optional<std::string> client_name_;
    std::optional<std::string> fault_;
    std::optional<int> table_number_;
};


class Client {
public:
    Client(std::string, Time, std::optional<int> = std::nullopt);

    std::optional<int> get_table_number();
    std::string get_client_name() const;
    Time& get_start_time();

    void set_table_number(int);
    void set_start_time(Time);

    friend bool operator<(const Client &a, const Client &b);

private:
    std::string client_name_;
    Time start_time_;
    std::optional<int> table_number_;
};


class Table {
public:
    Table(int);
    ~Table() = default;

    void add_revenue(int);
    void add_time(Time);

    bool is_free();
    void set_free();
    void set_busy();

    void cout_money_time(Time, int);

    int get_number();

    friend std::ostream &operator<<(std::ostream&, const Table&);

    friend bool operator<(const Table& a, const Table& b);

private:
    int number_;
    bool free_;
    int revenue_;
    Time use_time_;
};


class ComputerClub {
public:
    ComputerClub() = default;
    ~ComputerClub() = default;

    friend std::ifstream &operator>>(std::ifstream&, ComputerClub&);
    friend std::ostream &operator<<(std::ostream&, const ComputerClub&);

    std::optional<int> delete_client(Client &, Time);

    std::optional<std::reference_wrapper<Client>> is_here(std::string);

    std::optional<int> remove_table_free(Client &client, Time time);

    bool has_free_tables();

    bool is_closed(Time);

    void check_event(OutgoingEvent&);

    void simulate(std::ifstream &);

    int get_table_count();

private:
    int table_count_;
    Time work_start_;
    Time work_end_;
    int hour_cost_;
    std::deque<OutgoingEvent> events_;
    std::set<Client> clients_;
    std::vector<Table> tables_;
};

#endif
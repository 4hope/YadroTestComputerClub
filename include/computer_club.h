#ifndef COMPUTER_CLUB_H
#define COMPUTER_CLUB_H

#include "clock_time.h"
#include "event.h"

#include <iostream>
#include <vector>
#include <memory>
#include <optional>
#include <queue>
#include <deque>
#include <set>
#include <sstream>

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

    bool simulate(std::ifstream &);

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
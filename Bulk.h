#ifndef BULK_H
#define BULK_H

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

struct Block {
    Block(const size_t _count) : commands_count(_count){}

    void exec()
    {
        while (true)
        {
            string s;
            cin >> s;
            if (cin.eof())
            {
                if (!opened_count)
                {
                    print();
                }
                break;
            }
            update(s);
        }
    }

    void update(const string& _s)
    {
        if (_s == "{") {
            ++opened_count;
            if (opened_count == 1 && !m_commands.empty())
            {
                print();
            }
        }

        else if (_s == "}")
        {
            if (opened_count)
            {
                --opened_count;
                if (!opened_count)
                {
                    print();
                }
            }
        }

        else {
            if (m_commands.empty())
            {
                milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
                m_command_time = ms.count();
            }

            m_commands.push_back(_s);

            if (!opened_count && (m_commands.size() == commands_count))
            {
                print();
            }
        }
    }

    void print()
    {
        cout << "bulk: ";
        size_t size = m_commands.size();
        for (size_t ix = 0; ix < size; ++ix)
        {
            cout << m_commands[ix] << (ix < size - 1 ? ", " : "");
        }
        cout << endl;

        save_to_file();

        m_commands.clear();
    }

    void save_to_file()
    {
        string file_name = "bulk" + to_string(m_command_time) + ".log";

        ofstream file;
        file.open(file_name);

        if (file.is_open())
        {
            for (size_t ix = 0; ix < m_commands.size(); ++ix)
            {
                file << m_commands[ix] << endl;
            }

            file.close();
        }
    }

private:
    const size_t commands_count;

    long long m_command_time = 0;
    char opened_count = 0;
    vector<string> m_commands;
};

#endif // BULK_H

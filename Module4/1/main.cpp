#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class hash_table {
public:
    hash_table();
    bool insert(string data);
    bool erase(string data);
    bool check(string data);

private:
    void rehash();
    vector<string> buffer;
    vector<int> deleted; //0 - ничего не было, 1 - элемент был удален
    int hash(string data);
    int hash2(string data);
    int size;
    int elements;
    const int mod = 127;
    const int mod2 = 51;
};

hash_table::hash_table() {
    elements = 0;
    buffer.resize(8);
    deleted.resize(8);
    size = 8;
}

int hash_table::hash(string data) {
    int result = 0;
    for (int i = 0; i < data.size(); ++i) {
        result = (result * mod % size + data[i]) % size;
    }
    return result % size;
}

int hash_table::hash2(string data) {
    int result = 0;
    for (int i = 0; i < data.size(); ++i) {
        result = (result * mod2 + data[i]) % size;
    }
    return (2 * result + 1) % size;
}

bool hash_table::insert(string data) {
    if (check(data))
        return false;
    if (size * 3 <= (++elements) * 4) {
        rehash();
    }
    int f_hash = hash(data);
    int s_hash = hash2(data);
    for (int i = 0; i < size; ++i) {
        if (deleted[f_hash] == 0 || deleted[f_hash] == 1) {
            buffer[f_hash] = data;
            deleted[f_hash] = -1;
            return true;
        }
        f_hash = (f_hash + s_hash) % size;
    }
    return false;
}

bool hash_table::erase(string data) {
    int f_hash = hash(data);
    int s_hash = hash2(data);
    if (!check(data))
        return false;
    for (int i = 0; i < size; ++i) {
        if (deleted[f_hash] != 0) {
            if (buffer[f_hash] == data && deleted[f_hash] == -1) {
                deleted[f_hash] = 1;
                --elements;
                return true;
            }
            else if (buffer[f_hash] == data && deleted[f_hash] == 1) {
                return false;
            }
        }
        f_hash = (f_hash + s_hash) % size;
    }
    return false;
}

bool hash_table::check(string data) {
    int f_hash = hash(data);
    int s_hash = hash2(data);
    for (int i = 0; i < size; ++i) {
        if (deleted[f_hash] != 0) {
            if (buffer[f_hash] == data && deleted[f_hash] == -1)
                return true;
            else if (deleted[f_hash] == 1 && buffer[f_hash] == data)
                return false;
        }
        else
            return false;
        f_hash = (f_hash + s_hash) % size;
    }
    return false;
}

void hash_table::rehash() {
    size *= 2;
    vector<string> new_buffer(size);
    vector<int> new_deleted(size);
    for (int i = 0; i < buffer.size(); ++i) {
        if (deleted[i] == -1) {
            int f_hash = hash(buffer[i]);
            int s_hash = hash2(buffer[i]);
            for (int j = 0; j < size; ++j) {
                if (new_deleted[f_hash] == 0 || new_deleted[f_hash] == 1) {
                    new_buffer[f_hash] = buffer[i];
                    new_deleted[f_hash] = -1;
                    break;
                }
                f_hash = (f_hash + s_hash) % size;
            }
        }
    }
    buffer = new_buffer;
    deleted = new_deleted;
}

int main() {
    hash_table table;
    char command;
    while (std::cin >> command) {
        string input, in_string;
        std::cin >> in_string;
        if (command == '+') {
            if (table.insert(in_string)) {
                std::cout << "OK" << std::endl;
            }
            else {
                std::cout << "FAIL" << std::endl;
            }
        }
        else if (command == '-') {
            if (table.erase(in_string)) {
                std::cout << "OK" << std::endl;
            }
            else {
                std::cout << "FAIL" << std::endl;
            }
        }
        else if (command == '?') {
            if (table.check(in_string)) {
                std::cout << "OK" << std::endl;
            }
            else {
                std::cout << "FAIL" << std::endl;
            }
        }
    }
    return 0;
}
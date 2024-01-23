#include <vector>
#include <iomanip>
#include <iostream>
#include "Directory.h"
using namespace std;
namespace sdds {
Directory::Directory(const std::string dirName) {
    m_name = dirName;
}

void Directory::update_parent_path(const std::string &file_path) {
    m_parent_path = file_path;
    for(auto &item : m_contents) {
        if(m_parent_path != "/") {
            item->update_parent_path(file_path);
        }
    }
}

sdds::NodeType Directory::type() const {
    return NodeType::DIR;
}

std::string Directory::path() const {
    return m_parent_path + m_name;
}

std::string Directory::name() const {
    return m_name;
}

int Directory::count() const {
    return int(m_contents.size());
}

size_t Directory::size() const {
    size_t size = 0u;
    for(auto &item : m_contents) {
        size += item->size();
    }
    return size;
}

Directory& Directory::operator+=(sdds::Resource* resource) {
    for(auto &item : m_contents) {
        if(item->name() == resource->name()) {
            throw "ERROR";
        }
    }
    m_contents.push_back(resource);
    m_contents.back()->update_parent_path(path());
    return *this;
}

Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flag) {
    Resource* result = nullptr;
    for(auto &item : m_contents) {
        if(item->type() == NodeType::DIR && flag.size() != 0) {
            Directory* dir = dynamic_cast<Directory*>(item);
            result = dir->find(name, flag);
            if(result != nullptr) {
                break;
            }
        }
        else if(item->name() == name) {
            result = item;
        }
    }
    return result;
}

Directory::~Directory() {
    for(auto &item : m_contents) {
        delete item;
    }
}

void Directory::remove(const std::string &name, const std::vector<OpFlags>& flag) {
    Resource* result = find(name);
    if(result != nullptr) {
        if(result->type() == NodeType::DIR) {
            if(flag.size() != 0) {
                for(auto i = m_contents.begin(); i != m_contents.end(); i++) {
                    if(*i == result) {
                        m_contents.erase(i);
                        delete result;
                    }
                }
            }
            else {
                throw std::invalid_argument(name + " is a directory. Pass the recursive flag to delete directories.");
            }
        }
    }
    else {
        throw name + "NAME does not exist in " + m_name;
    }
}

void Directory::display(std::ostream & os, const std::vector<FormatFlags> & flag) const {
    os << "Total size: " << size() << " bytes" << endl;
    for(auto &item : m_contents){
        if(item->type() == NodeType::DIR){
            os << "D";
        }else{
            os << "F";
        }
        os << " | " << left << setw(15) << item->name() << " |";
        
        if(!flag.empty() && flag[0] == FormatFlags::LONG){
            if(item->type() == NodeType::DIR) {
                os << " " << right << setw(2) << item->count() << " | ";
            }
            else {
                os << " " << right << setw(2) << "  " << " | ";
            }
            os << right << setw(4) << item->size() << " bytes" << " | " << endl;
        }else{
            os << endl;
        }
    }
}


}


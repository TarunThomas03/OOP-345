#include <vector>
#include "Directory.h"
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

}


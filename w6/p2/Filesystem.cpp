#include <fstream>
#include <vector>
#include <string>
#include "Filesystem.h"
#include "File.h"
using namespace std;
namespace sdds {
Filesystem::Filesystem(const std::string filename, const std::string root) {
    fstream file;
    file.open(filename);
    if(file.is_open()) {
        m_root = new Directory(root);
        std::string line;
        while (std::getline(file, line)) {
            line.erase(0, line.find_first_not_of(" "));
            line.erase(line.find_last_not_of(" ") + 1);
            if(!line.empty()){
                if (line.find('|') != std::string::npos) {
                    size_t pipe = line.find('|');
                    std::string file_path = line.substr(0, pipe);
                    std::string content = line.substr(pipe + 1);
                    file_path = file_path.substr(file_path.find_first_not_of(" "), file_path.find_last_not_of(" ") + 1);
                    content = content.substr(content.find_first_not_of(" "), content.find_last_not_of(" ") + 1);
                    std::vector<std::string> components;
                    size_t start = 0;
                    size_t end;
                    while ((end = file_path.find('/', start)) != std::string::npos) {
                        components.push_back(file_path.substr(start, end - start + 1));
                        start = end + 1;
                    }
                    std::string name = file_path.substr(start);
                    Directory* dir = nullptr;
                    m_current = m_root;
                    for (const std::string& component : components) {
                        if (m_root->find(component) == nullptr) {
                            dir = new Directory(component);
                            *m_current += dir;
                        }
                        else {
                            dir = dynamic_cast<Directory*>(m_root->find(component));
                        }
                        m_current = dir;
                    }
                    File* newFile = new File(name, content);
                    *m_current += newFile;
                } else {
                    std::vector<std::string> components;
                    size_t start = 0;
                    size_t end;
                    while ((end = line.find('/', start)) != std::string::npos) {
                        components.push_back(line.substr(start, end - start + 1));
                        start = end + 1;
                    }
                    Directory* dir = nullptr;
                    m_current = m_root;
                    for (const std::string& component : components) {
                        if (m_root->find(component) == nullptr) {
                            dir = new Directory(component);
                            *m_current += dir;
                        }
                        else {
                            dir = dynamic_cast<Directory*>(m_root->find(component));
                        }
                        m_current = dir;
                    }
                }
            }
            m_current = m_root;
        }
        file.close();
    }
    else {
        throw std::runtime_error("file cannot be opened");
       
    }
    
}

Filesystem::Filesystem(sdds::Filesystem &&source) {
    *this = std::move(source);
}

sdds::Filesystem& Filesystem::operator=(sdds::Filesystem &&source) {
    if(this != &source) {
        delete m_root;
        m_root = source.m_root;
        m_current = source.m_current;
        source.m_root = nullptr;
        source.m_current = nullptr;
    }
    return *this;
}

sdds::Filesystem& Filesystem::operator+=(sdds::Resource* resource) {
    *m_current += resource;
    return *this;
}

sdds::Directory* Filesystem::change_directory(const std::string &dir) {
    if(dir == "") {
        m_current = m_root;
    }
    else {
        if(m_current->find(dir) != nullptr) {
            m_current = dynamic_cast<Directory*>(m_current->find(dir));
        }
        else {
            throw std::invalid_argument("Cannot change directory! DIR_NAME not found!");
        }
    }
    return m_current;
}

sdds::Directory *Filesystem::get_current_directory() const {
    return m_current;
}

Filesystem::~Filesystem() {
    delete m_root;
    m_root = nullptr;
}
}



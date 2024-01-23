#include <fstream>
#include "File.h"
#include "Flags.h"
using namespace std;
namespace sdds {
File::File(const std::string filename, const std::string contents) {
    m_name = filename;
    m_contents = contents;
}

void File::update_parent_path(const std::string &file_path) {
    m_parent_path = file_path;
}

sdds::NodeType File::type() const {
    return NodeType::FILE;
}

std::string File::path() const {
    return m_parent_path + m_name;
}

std::string File::name() const {
    return m_name;
}

int File::count() const {
    return -1;
}

size_t File::size() const {
    return m_contents.length();
}

}

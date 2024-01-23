#ifndef SDDS_FILESYSTEM_H
#define SDDS_FILESYSTEM_H
#include "Directory.h"
namespace sdds {
class Filesystem {
    Directory* m_root;
    Directory* m_current;
public:
    Filesystem(const std::string filename, const std::string root = "");
    Filesystem(const Filesystem& source) = delete;
    Filesystem& operator=(const Filesystem& source) = delete;
    Filesystem(Filesystem&& source);
    Filesystem& operator=(Filesystem&& source);
    Filesystem& operator+=(Resource*);
    Directory* change_directory(const std::string& = "");
    Directory* get_current_directory() const;
    ~Filesystem();
};
}

#endif /* Filesystem_h */

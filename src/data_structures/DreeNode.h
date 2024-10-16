#ifndef DREENODE_H
#define DREENODE_H

#include <string>
#include <vector>

class DreeNode {
   private:
    std::string getFileNameFromPath(const std::string &path); 
   public:
    std::string name;
    std::string path;
    std::vector<DreeNode *> children;
    DreeNode *parent;
    DreeNode *left;
    DreeNode *right;

    DreeNode(const std::string &str); 
};

#endif 

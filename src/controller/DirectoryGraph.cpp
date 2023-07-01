#include "DirectoryGraph.h"
#include <iostream>

using namespace std;

bool DirectoryGraph::isDirectory(const string &pathStr)
{
    filesystem::path path(pathStr);
    return filesystem::is_directory(path);
}

DirectoryNode *DirectoryGraph::BuildGraph(const string &directoryName, long long depth)
{
    DirectoryNode *graph = new DirectoryNode(directoryName);
    TraverseDirectoriesDFS(graph, depth, 0);
    return graph;
}

void DirectoryGraph::TraverseDirectoriesDFS(DirectoryNode *node, long long depth, long long currentDepth)
{
    if (currentDepth > depth)
        return;

    for (const auto &entry : filesystem::directory_iterator(node->path))
    {
        // if (entry.is_directory())
        if (true)
        {
            string childDirectory = entry.path().string();
            DirectoryNode *child = new DirectoryNode(childDirectory);
            node->children.push_back(child);
        }
    }
    for (auto ch : node->children)
    {
        if (isDirectory(ch->path))
        {
            TraverseDirectoriesDFS(ch, depth, currentDepth + 1);
        }
    }
}

void DirectoryGraph::PrintGraph(DirectoryNode *node, long long depth, long long currentDepth, bool isLastChild, long long mask)
{
    if (currentDepth == depth)
        return;

    for (long long i = 0; i < currentDepth; i++)
    {
        if (((mask >> i) & 1ll) == 0ll)
            cout << "│    ";
        else
            cout << "     ";
    }
    isLastChild ? cout << "└── " : cout << "├── ";

    cout << node->name << "\n";
    for (size_t i = 0; i < node->children.size(); i++)
    {
        DirectoryNode *child = node->children[i];
        if (i == node->children.size() - 1)
        {
            mask = mask | (1ll << (currentDepth + 1));
        }
        PrintGraph(child, depth, currentDepth + 1, i == node->children.size() - 1, mask);
    }
}

void DirectoryGraph::PrintGraph(DirectoryNode *node, long long depth)
{
    this->PrintGraph(node, depth, 0, true, 1);
}
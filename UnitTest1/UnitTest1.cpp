#include "pch.h"
#include "CppUnitTest.h"
#include "..\Lab_09\Graph.cpp"
#include <fstream>
#include <cstdio>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestReadGraphFromFile_Success)
        {
            const char* filename = "test_graph.txt";
            {
                std::ofstream outFile(filename);
                outFile << "4 4\n1 2\n1 3\n2 4\n3 4\n";
                outFile.close();
            }

            std::vector<std::vector<unsigned int>> graph;
            bool result = readGraphFromFile(filename, graph);

            Assert::IsTrue(result);

            Assert::AreEqual(static_cast<int>(4), static_cast<int>(graph.size()));

            Assert::AreEqual(static_cast<int>(2), static_cast<int>(graph[0].size())); // 1 -> 2,3
            Assert::AreEqual(static_cast<int>(2), static_cast<int>(graph[1].size())); // 2 -> 1,4
            Assert::AreEqual(static_cast<int>(2), static_cast<int>(graph[2].size())); // 3 -> 1,4
            Assert::AreEqual(static_cast<int>(2), static_cast<int>(graph[3].size())); // 4 -> 2,3

            Assert::IsTrue((graph[0][0] == 1 && graph[0][1] == 2) || (graph[0][0] == 2 && graph[0][1] == 1));
            Assert::IsTrue((graph[1][0] == 0 && graph[1][1] == 3) || (graph[1][0] == 3 && graph[1][1] == 0));

            std::remove(filename);
        }

        TEST_METHOD(TestReadGraphFromFile_FileNotFound)
        {
            std::vector<std::vector<unsigned int>> graph;
            bool result = readGraphFromFile("nonexistent_file.txt", graph);
            Assert::IsFalse(result);
            Assert::AreEqual(static_cast<size_t>(0), graph.size());
        }
    };
}

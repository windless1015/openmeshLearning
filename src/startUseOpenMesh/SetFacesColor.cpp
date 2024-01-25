// SetFacesColor.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
//#include <vector>
//#include <string>
//#include <direct.h>
//#include <vector>
//#include <fstream>
//#include<Windows.h>
#include <io.h>
// -------------------- OpenMesh
#include <OpenMesh\/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
using namespace std;


typedef OpenMesh::PolyMesh_ArrayKernelT<>  Triangle_Mesh;

void SetOneFaceColr(Triangle_Mesh& mesh, int faceIdx, Triangle_Mesh::Color& color);


////获取特定格式的文件名  
void GetAllFormatFiles()
{
    //目标文件夹路径
    //std::string inPath = "*.txt";//遍历文件夹下的所有.txt文件

    string inPath = "*.txt";

    //用于查找的句柄
    long handle;
    struct _finddata_t fileinfo;

    //第一次查找
    handle = _findfirst(inPath.c_str(), &fileinfo);
    if (handle == -1)
    {
        return;
    }
    do
    {
        //找到的文件的文件名
        printf("%s\n", fileinfo.name);
    } while (!_findnext(handle, &fileinfo));

    _findclose(handle);
}


int main()
{

    Triangle_Mesh::Color clr;
    clr[0] = 254;
    clr[1] = 0;
    clr[2] = 0;
    //读入mesh
    Triangle_Mesh mesh;
    OpenMesh::IO::read_mesh(mesh, "D:/debug/611992776887767041/612003338334076928.stl");
    /*SetOneFaceColr(mesh, 23835, clr);
    return 1;*/

    //写一个文件
    mesh.request_face_colors(); //需要颜色属性
    std::vector<int> faceIdVec;
    std::string fileName = "D:/1.3Test/seedLocatedFaces.txt";
    std::ifstream f(fileName);
    string line;
    while (getline(f, line))
    {
        int idx = std::atoi(line.c_str());
        OpenMesh::FaceHandle fh(idx);
        mesh.set_color(fh, clr);
    }
    //bool hasColor = mesh.has_face_colors();
    OpenMesh::IO::write_mesh(mesh, "D:/1.3Test/seedLocatedFaces.ply", OpenMesh::IO::Options::FaceColor);
    mesh.release_face_colors(); //这里取消面片属性,不然下次再写,上次的就会保留
    f.close();


    //从外界读入需要设置的面片的索引
    //for (int i = 5; i < 6; i++)
    //{
    //    mesh.request_face_colors(); //需要颜色属性
    //    std::vector<int> faceIdVec;
    //    std::string fileName = "D:/faceIdxs" + std::to_string(i) + ".txt";
    //    std::ifstream f(fileName);
    //    string line;
    //    while (getline(f, line))
    //    {
    //        int idx = std::atoi(line.c_str());
    //        OpenMesh::FaceHandle fh(idx);
    //        mesh.set_color(fh, clr);
    //    }
    //    //bool hasColor = mesh.has_face_colors();
    //    OpenMesh::IO::write_mesh(mesh, "D:/faceIdxs" + std::to_string(i) + ".ply", OpenMesh::IO::Options::FaceColor);
    //    mesh.release_face_colors(); //这里取消面片属性,不然下次再写,上次的就会保留
    //    f.close();
    //    int a = 1;
    //}
}

void SetOneFaceColr(Triangle_Mesh& mesh, int faceIdx, Triangle_Mesh::Color& color)
{
    mesh.request_face_colors(); //需要颜色属性
    OpenMesh::FaceHandle fh(faceIdx);
    mesh.set_color(fh, color);
    OpenMesh::IO::write_mesh(mesh, "D:/Mesh_" + std::to_string(faceIdx) + ".ply", OpenMesh::IO::Options::FaceColor);
}

void ReadAllTxtFiles(std::string dir)
{
    
}


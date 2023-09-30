//#include "ModelImporter.h"
//
//void ModelImporter::Import()
//{
//    FbxManager* sdkManager = FbxManager::Create();
//
//    FbxIOSettings* ios = FbxIOSettings::Create(sdkManager, IOSROOT);
//    sdkManager->SetIOSettings(ios);
//
//    FbxImporter* importer = FbxImporter::Create(sdkManager, "");
//
//    const char* filename = "spider.fbx";
//
//
//    bool importStatus = importer->Initialize(filename, -1, sdkManager->GetIOSettings());
////}
//
//  FindFileInfo.cpp
//  TestThreeApp
//
//  Created by dzp on 14-7-6.
//
//

#include "FindFileInfo.h"

@interface TestOC : NSObject

+ (NSArray*)getResourceAllFileName:(NSString*)path;

@end


FindFileInfo* FindFileInfo::getInstance()
{
    FindFileInfo *file = new FindFileInfo();
    if(file){
        return file;
    }else{
        return NULL;
    }
}

vector<const char*> FindFileInfo::getFileList(const char *path)
{
    /*储存符合条件的文件名*/
    vector<const char*> files;
    
    /*设置指定路径*/
    vector<string> p;
    p.push_back(path);
    FileUtils::getInstance()->setSearchPaths(p);
    
    /*获取指定路径的所有文件名*/
    NSArray* fileNameList_OC = [TestOC getResourceAllFileName:[NSString stringWithFormat:@"%s",path] ];
    vector<const char*> fileNameList_C;
    int fileNameCount = (int)[fileNameList_OC count];
    for (int i = 0 ; i < fileNameCount; ++i) {
        fileNameList_C.push_back([ [fileNameList_OC objectAtIndex:i] UTF8String ]) ;
    }
    
    /*判断是否是.jpg或.png格式的图片*/
    for (int i = 0; i<(int)fileNameList_C.size(); ++i) {
        if(isJpgOrPng(fileNameList_C.at(i))){
            files.push_back(fileNameList_C.at(i));
        }
    }
    
    return files;
}


@implementation TestOC

+ (NSArray*)getResourceAllFileName:(NSString*)path
{
    NSArray *files = NULL;
    NSFileManager* fm=[NSFileManager defaultManager];
    files = [fm subpathsAtPath:  path ];
    return files;
    
}

@end

bool FindFileInfo::isJpgOrPng(const char *fileName)
{
    string filter[] = {".jpg",".png"};
    string strName = static_cast<string>(fileName);
    

    string::size_type lastPos = strName.find_last_of(".");
    if(string::npos != lastPos){
        for (int i = 0 ; i < filter->size();  ++i) {
            if(filter[i] == strName.substr(lastPos,strName.length()-lastPos)){
                return true;
            }
        }
        
    }
    return false;
}



//- (NSArray*) getResourceAllFileName(NSString)

//NSFileManager* fm=[NSFileManager defaultManager];
//if(![fm fileExistsAtPath:[self dataFilePath]]){
//    
//    //下面是对该文件进行制定路径的保存
//    [fm createDirectoryAtPath:[self dataFilePath] withIntermediateDirectories:YES attributes:nil error:nil];
//    
//    //取得一个目录下得所有文件名
//    NSArray *files = [fm subpathsAtPath: [self dataFilePath] ];
//    
//    //读取某个文件
//    NSData *data = [fm contentsAtPath:[self dataFilePath]];
//    
//    //或者
//    NSData *data = [NSData dataWithContentOfPath:[self dataFilePath]];
//}

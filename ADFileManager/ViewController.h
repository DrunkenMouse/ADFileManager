//
//  ViewController.h
//  ADFileManager
//
//  Created by 王奥东 on 16/10/11.
//  Copyright © 2016年 王奥东. All rights reserved.

//仿写HYFileManager:https://github.com/castial/HYFileManager
//附带详解

#pragma mark - 沙盒目录相关
/**
 主目录，tmp目录路径可直接获取
 libraryDir通过NSSearchPathForDirectoriesInDomains
 Library / Preferences的目录通过libraryDir拼接
 Library / Caches的目录通过NSSearch搜索CachesDirectory
 
 NSSearchPathForDirectoriesInDomains
 第一个参数是哪个目录
 第二个参数是搜索谁的
 第三个参数 ' ~ ' 路径是否展开
 ' ~ ' 路径是详细路径前半段直接隐藏用' ~ '显示
 
 */

#pragma mark - 遍历文件夹
/**
 通过FileManager的subpathsOfDirectoryAtPath:error:深遍历路径
 通过FileManager的contentsOfDirectoryAtPath:error:浅遍历路径
 */

#pragma mark - 获取文件属性
/**
 先通过FileManager的attributesOfItemAtPath:error:获取路径下文件属性集合，而后通过key取出某个属性
 */

#pragma mark - 创建文件(夹)
/**
 创建文件夹:通过fileManager的createDirectoryAtPath:withIntermediateDirectories:attributes:error:
 
 createDirectoryAtPath:withIntermediateDirectories:attributes:error:
 第一个参数代表文件夹路径
 第二个参数代表是否允许创建中间目录
 第三个参数代表设置，如访问权限、所属用户/用户组。nil代表选择系统默认设置。
 第四个参数代表错误信息
 
 创建文件:通过fileManager的createFileAtPath:contents:attributes:
 如果文件夹路径不存在，则先创建文件夹。通过自定义方法directoryAtPath判断
 如果创建失败返回NO，没有错误信息
 如果文件存在但不想复写则返回YES
 先创建文件，而后判断是否写入内容
 content代表写入的内容，如果有则写入
 
 获取文件修改时间、创建时间则先获取文件的所有属性
 通过KeyNSFileModificationDate(修改) NSFileCreationDate(创建)
 获取到所需的修改时间、创建时间
 
 
 */

#pragma mark - 删除文件(夹)
/**
 删除文件/文件夹 通过fileManager的removeItemAtPath:error:直接删除这个路径文件/文件夹
 
 清空Caches文件夹:
 先浅遍历cache文件夹，获取其下所有文件与目录
 而后拼接在cache路径后，通过自定义方法removeItemAtPath:移除
 让一个BOOL值为YES的isSuccess &= 移除后的结果值
 则有一个移除错误就会为NO
 
 清空tmp文件夹同上
 */

#pragma mark - 复制文件(夹)
/**
 复制文件/文件夹 先要保证源文件路径存在，不然通过NSException抛出异常
 而后获取路径上的文件夹，如果文件夹路径不存在则创建文件夹路径，创建失败直接返回NO
 而后判断是否允许重写，如果允许重写且文件存在则先删掉要重写的文件
 
 调用fileManager的copyItemAtPath:toPath:error:复制文件
 */

#pragma mark - 移动文件(夹)
/**
 同复制文件夹，只是移动时若文件存在且不允许重写则把源文件移除而后返回YES
 如果文件存在且允许重写则移除要重写的文件而后移动源文件
 
 调用fileManager的moveItemAtPath:toPath:error:移动源文件
 */

#pragma mark - 根据URL获取文件名
/**
 根据文件路径获取文件名称，是否需要后缀
 直接通过字符串的lastPathComponent方法获取文件名称
 若不需要后缀则通过stringByDeletingPathExtension删除掉后缀
 
 获取文件所在的文件夹路径
 直接通过字符串的stringByDeletingLastPathComponent删除最后一个目录
 也就是最后一个' / '之后的内容包括' / '
 
 根据文件路径获取文件扩展类型
 直接通过字符串的pathExtension获取扩展名
 会从最后面截取' . '之后的内容
 
 */

#pragma mark - 判断文件(夹)是否存在
/**
 判断文件路径是否存在直接通过fileManager的fileExistsAtPath:方法判断
 
 判断路径是否为空(判断条件是文件大小为0, 或者是文件夹下没有子文件)
 目标路径是一个文件并且文件大小是0
 或 目标路径是一个文件夹并且文件夹下没有子文件
 
 判断目录是否是文件夹,通过文件属性NSFileType得值是否为NSFileTypeDirectory
 
 判断目录是否是文件,通过文件属性NSFileType得值是否为NSFileTypeRegular
 
 可执行、可读、可写通过fileManager的isExecutableFileAtPath、
 isReadableFileAtPath、isWritableFileAtPath判断
 
 */

#pragma mark - 获取文件(夹)大小
/**
 获取文件/目录大小 通过属性的key值NSFileSize获取
 只是获取文件大小时，若目标路径不是文件则返回nil
 
 获取文件夹大小时先判断路径是否为文件夹，不是则返回nil
 而后获取文件夹的目录大小，再深遍历文件夹累加目录和文件、子文件夹大小
 */


#pragma mark - 写入文件内容
/**
 写入文件内容时，如果文件不存在就异常警告并返回NO
 如果文件路径不存在则返回NO
 如果文件存在，路径存在就根据文件所属类型转换并写入
 (不转换就是NSObject类型无法调用write方法)
 atomically是否允许持续写入
 其中JSON格式转变为字典类型
 UIImage格式通过UIImagePNGRepresentation转变为NSData类型
 NSCoding类型通过[NSKeyedArchiver archiveRootObject:content toFile:path]
 如果类型都不对则异常提示并返回NO
 
 */


#pragma mark - private methods
//转换错误信息,如果错误信息为空则返回YES。不过没有用到
//转换大小格式,显示如:2KB 或4.26MB 或1002.25GB

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController


@end


//
//  DWAlbumGridViewController.h
//  DWCheckBox
//
//  Created by Wicky on 2019/8/4.
//

/**
 DWAlbumGridController
 
 提供相册网格视图
 
 version 0.0.0.1
 提供基础功能，包括旋屏处理，列表展示等
 通过预加载、缩略图加载等手段提升滑动体验
 
 version 0.0.0.2
 注册功能完成
 
 version 0.0.0.3
 代理修改
 
 version 0.0.0.4
 添加清除接口
 
 version 0.0.0.5
 添加selection时携带previewImage
 
 version 0.0.0.6
 cell支持tintColor
 
 version 0.0.0.7
 修复navigationBar相关处理
 
 version 0.0.0.8
 增加是否自动恢复navigationBar标志位
 
 version 0.0.0.9
 添加默认值同时屏蔽 -init 方法
 
 version 0.0.0.10
 修复快速滑动停止时松手后加载真实图片没有缓存的问题
 */

#import <UIKit/UIKit.h>
#import "DWAlbumSelectionManager.h"
#import "DWAlbumGridCellModel.h"
#import "DWAlbumGridCell.h"

///DWAlbumGridController支持的工具栏协议
@protocol DWAlbumGridToolBarProtocol <NSObject>

///工具栏高度
@property (nonatomic ,assign) CGFloat toolBarHeight;

///工具栏选择管理者
@property (nonatomic ,strong) DWAlbumSelectionManager * selectionManager;

///为工具栏配置选择管理者
-(void)configWithSelectionManager:(DWAlbumSelectionManager *)selectionManager;

///刷新工具栏展示
-(void)refreshSelection;

@end

typedef void(^DWGridViewControllerFetchCompletion)(DWAlbumGridCellModel * model);
@class DWAlbumGridController;
@protocol DWAlbumGridDataSource <NSObject>

@required
///获取指定asset对应尺寸媒体资源的代理
-(void)gridController:(DWAlbumGridController *)gridController fetchMediaForAsset:(PHAsset *)asset targetSize:(CGSize)targetSize thumnail:(BOOL)thumnail completion:(DWGridViewControllerFetchCompletion)completion;

@optional
///返回指定资源对应展示cell的代理，可选实现。若不实现，将默认使用DWAlbumGridCell。
-(DWAlbumGridCell *)gridViewController:(DWAlbumGridController *)gridController cellForAsset:(PHAsset *)asset mediaOption:(DWAlbumMediaOption)mediaOption atIndex:(NSInteger)index;

///网格视图对应cell被点击回调
-(void)gridViewController:(DWAlbumGridController *)gridController didSelectAsset:(PHAsset *)asset mediaOption:(DWAlbumMediaOption)mediaOption atIndex:(NSInteger)index;

///网格视图可以开始预加载资源回调
-(void)gridController:(DWAlbumGridController *)gridController startCachingMediaForIndexes:(NSIndexSet *)indexes targetSize:(CGSize)targetSize;

///网格视图取消置顶index的预加载行为回调
-(void)gridController:(DWAlbumGridController *)gridController stopCachingMediaForIndexes:(NSIndexSet *)indexes targetSize:(CGSize)targetSize;

@end

///资源模型
@interface DWAlbumGridModel : NSObject

///资源Asset集合
@property (nonatomic ,strong) NSArray <PHAsset *>* results;

///相册名称
@property (nonatomic ,copy) NSString * name;

@end

///网格视图控制器
@interface DWAlbumGridController : UIViewController

///代理
@property (nonatomic ,weak) id<DWAlbumGridDataSource> dataSource;

///网格视图
@property (nonatomic ,strong ,readonly) UICollectionView * gridView;

///列宽
@property (nonatomic ,assign) CGFloat itemWidth;

///资源模型
@property (nonatomic ,strong ,readonly) DWAlbumGridModel * gridModel;

///顶部工具栏
@property (nonatomic ,strong) UIView <DWAlbumGridToolBarProtocol>* topToolBar;

///底部工具栏
@property (nonatomic ,strong) UIView <DWAlbumGridToolBarProtocol>* bottomToolBar;

///选择管理者
@property (nonatomic ,strong) DWAlbumSelectionManager * selectionManager;

///是否自动恢复系统导航栏
@property (nonatomic ,assign) BOOL autoRecoveryNavigationBar;

-(instancetype)init API_UNAVAILABLE(ios);

///初始化方法
-(instancetype)initWithItemWidth:(CGFloat)width;

///注册网格视图使用的cell，必须为DWAlbumGridCell或者其子类
-(void)registerClass:(Class)cellClass forCellWithReuseIdentifier:(NSString *)identifier;

///生成一个预览cell
-(__kindof DWAlbumGridCell *)dequeueReusableCellWithReuseIdentifier:(NSString *)identifier forIndex:(NSInteger)index;

///配置资源模型
-(void)configWithGridModel:(DWAlbumGridModel *)gridModel;

///通知网格控制器，改变当前预览位置
-(void)notifyPreviewIndexChangeTo:(NSInteger)index;

@end

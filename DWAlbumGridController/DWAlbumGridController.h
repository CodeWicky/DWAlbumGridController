//
//  DWAlbumGridViewController.h
//  DWCheckBox
//
//  Created by Wicky on 2019/8/4.
//

#import <UIKit/UIKit.h>
#import "DWAlbumSelectionManager.h"
#import "DWAlbumGridCellModel.h"

@protocol DWAlbumGridToolBarProtocol <NSObject>

@property (nonatomic ,assign) CGFloat toolBarHeight;

@property (nonatomic ,strong) DWAlbumSelectionManager * selectionManager;

-(void)configWithSelectionManager:(DWAlbumSelectionManager *)selectionManager;

-(void)refreshSelection;

@end

typedef void(^DWGridViewControllerFetchCompletion)(DWAlbumGridCellModel * model);
@class DWAlbumGridController;
@protocol DWAlbumGridDataSource <NSObject>

@required
-(void)gridViewController:(DWAlbumGridController *)gridViewController fetchMediaForAsset:(PHAsset *)asset targetSize:(CGSize)targetSize thumnail:(BOOL)thumnail completion:(DWGridViewControllerFetchCompletion)completion;

@optional
-(void)gridViewController:(DWAlbumGridController *)gridViewController startCachingMediaForIndexes:(NSIndexSet *)indexes targetSize:(CGSize)targetSize;

-(void)gridViewController:(DWAlbumGridController *)gridViewController stopCachingMediaForIndexes:(NSIndexSet *)indexes targetSize:(CGSize)targetSize;

@end

@interface DWAlbumGridModel : NSObject

@property (nonatomic ,strong) NSArray <PHAsset *>* results;

@property (nonatomic ,copy) NSString * name;

@end

@interface DWAlbumGridController : UIViewController

@property (nonatomic ,weak) id<DWAlbumGridDataSource> dataSource;

@property (nonatomic ,strong ,readonly) UICollectionView * gridView;

@property (nonatomic ,assign) CGFloat itemWidth;

@property (nonatomic ,assign) NSInteger maxSelectCount;

@property (nonatomic ,strong ,readonly) DWAlbumGridModel * gridModel;

@property (nonatomic ,strong) UIView <DWAlbumGridToolBarProtocol>* topToolBar;

@property (nonatomic ,strong) UIView <DWAlbumGridToolBarProtocol>* bottomToolBar;

@property (nonatomic ,strong) DWAlbumSelectionManager * selectionManager;

@property (nonatomic ,copy) void(^gridClickAction)(NSIndexPath * indexPath);

-(instancetype)initWithItemWidth:(CGFloat)width;

-(void)registGridCell:(Class)cellClazz;

-(void)configWithGridModel:(DWAlbumGridModel *)gridModel;

-(void)notifyPreviewIndexChangeTo:(NSInteger)index;

@end

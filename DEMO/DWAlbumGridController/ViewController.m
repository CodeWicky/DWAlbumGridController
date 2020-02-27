//
//  ViewController.m
//  DWAlbumGridController
//
//  Created by Wicky on 2020/2/23.
//  Copyright © 2020 Wicky. All rights reserved.
//

#import "ViewController.h"
#import "DWAlbumManager.h"
#import <DWAlbumGridController/DWAlbumGridControllerHeader.h>
@interface ViewController ()<DWAlbumGridDataSource>

@property (nonatomic ,strong) DWAlbumManager * albumManager;

@property (nonatomic ,strong) DWAlbumGridController * gridVC;

@property (nonatomic ,strong) DWAlbumModel * currentGridAlbum;

@property (nonatomic ,strong) PHFetchResult * currentGridAlbumResult;

@property (nonatomic ,strong) DWAlbumSelectionManager * mgr;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor redColor];
}

-(void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [self.albumManager fetchCameraRollWithOption:nil completion:^(DWAlbumManager * _Nullable mgr, DWAlbumModel * _Nullable obj) {
        [self configAlbum:obj];
        [self presentViewController:self.gridVC animated:YES completion:nil];
    }];
}

#pragma mark --- tool method ---
-(void)configAlbum:(DWAlbumModel *)album {
    if (![self.currentGridAlbum isEqual:album]) {
        self.currentGridAlbumResult = album.fetchResult;
        self.currentGridAlbum = album;
        DWAlbumGridModel * gridModel = [self gridModelFromAlbumModel:album];
        [self.gridVC configWithGridModel:gridModel];
    }
}

-(DWAlbumGridModel *)gridModelFromAlbumModel:(DWAlbumModel *)album {
    DWAlbumGridModel * gridModel = [DWAlbumGridModel new];
    NSMutableArray * tmp = [NSMutableArray arrayWithCapacity:album.count];
    [album.fetchResult enumerateObjectsUsingBlock:^(id  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
        [tmp addObject:obj];
    }];
    gridModel.results = [tmp copy];
    gridModel.name = album.name;
    return gridModel;
}

-(DWAlbumGridCellModel *)gridCellModelFromImageAssetModel:(DWImageAssetModel *)assetModel {
    DWAlbumGridCellModel * gridModel = [DWAlbumGridCellModel new];
    gridModel.asset = assetModel.asset;
    gridModel.media = assetModel.media;
    gridModel.mediaType = assetModel.mediaType;
    gridModel.targetSize = assetModel.targetSize;
    return gridModel;
}

#pragma mark --- grid dataSource ---
-(void)gridController:(DWAlbumGridController *)gridController fetchMediaForAsset:(PHAsset *)asset targetSize:(CGSize)targetSize thumnail:(BOOL)thumnail completion:(DWGridViewControllerFetchCompletion)completion {
    if (thumnail) {
        [self.albumManager fetchImageWithAsset:asset targetSize:targetSize networkAccessAllowed:self.currentGridAlbum.networkAccessAllowed progress:nil completion:^(DWAlbumManager * _Nullable mgr, DWImageAssetModel * _Nullable obj) {
            if (completion) {
                completion([self gridCellModelFromImageAssetModel:obj]);
            }
        }];
    } else {
        NSInteger index = [self.currentGridAlbumResult indexOfObject:asset];
        [self.albumManager fetchImageWithAlbum:self.currentGridAlbum index:index targetSize:targetSize shouldCache:YES progress:nil completion:^(DWAlbumManager * _Nullable mgr, DWImageAssetModel * _Nullable obj) {
            if (completion) {
                completion([self gridCellModelFromImageAssetModel:obj]);
            }
        }];
    }
}

-(void)gridController:(DWAlbumGridController *)gridController startCachingMediaForIndexes:(NSIndexSet *)indexes targetSize:(CGSize)targetSize {
    [self.albumManager startCachingImagesForAlbum:self.currentGridAlbum indexes:indexes targetSize:targetSize];
}

-(void)gridController:(DWAlbumGridController *)gridController stopCachingMediaForIndexes:(NSIndexSet *)indexes targetSize:(CGSize)targetSize {
    [self.albumManager stopCachingImagesForAlbum:self.currentGridAlbum indexes:indexes targetSize:targetSize];
}

#pragma mark --- setter/getter ---
-(DWAlbumGridController *)gridVC {
    if (!_gridVC) {
        CGFloat shortSide = MIN([UIScreen mainScreen].bounds.size.width, [UIScreen mainScreen].bounds.size.height);
        CGFloat width = (shortSide - (3 - 1) * 0.5) / 3;
        _gridVC = [[DWAlbumGridController alloc] initWithItemWidth:width];
        _gridVC.selectionManager = self.mgr;
        _gridVC.dataSource = self;
        _gridVC.modalPresentationStyle = UIModalPresentationFullScreen;
    }
    return _gridVC;
}

-(DWAlbumManager *)albumManager {
    if (!_albumManager) {
        _albumManager = [[DWAlbumManager alloc] init];
    }
    return _albumManager;
}

-(DWAlbumSelectionManager *)mgr {
    if (!_mgr) {
        _mgr = [[DWAlbumSelectionManager alloc] initWithMaxSelectCount:9 selectableOption:(DWAlbumMediaOptionImageMask) multiTypeSelectionEnable:YES];
        _mgr.selectionValidation = ^BOOL(DWAlbumSelectionManager * _Nonnull mgr, PHAsset * _Nonnull asset, DWAlbumMediaOption mediaOption, NSError *__autoreleasing  _Nullable * _Nullable error) {
            if (mgr.selections.count == 5) {
//                *error = [NSError errorWithDomain:@"aaa" code:0 userInfo:nil];
                return NO;
            }
            return YES;
        };
        
        _mgr.validationFailCallback = ^(NSError * _Nonnull error) {
            NSLog(@"%@",error);
        };
    }
    return _mgr;
}

@end

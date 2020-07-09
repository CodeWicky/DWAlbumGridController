Pod::Spec.new do |s|
s.name = 'DWAlbumGridController'
s.version = '0.0.0.10'
s.license = { :type => 'MIT', :file => 'LICENSE' }
s.summary = '一个相册网格视图。Album Grid controller.'
s.homepage = 'https://github.com/CodeWicky/DWAlbumGridController'
s.authors = { 'codeWicky' => 'codewicky@163.com' }
s.source = { :git => 'https://github.com/CodeWicky/DWAlbumGridController.git', :tag => s.version.to_s }
s.requires_arc = true
s.ios.deployment_target = '9.0'
s.source_files = 'DWAlbumGridController/**/*.{h,m}'
s.frameworks = 'UIKit'
s.dependency 'DWKit/DWComponent/DWLabel', '~> 0.0.0.10'
s.dependency 'DWKit/DWComponent/DWFixAdjustCollectionView', '~> 0.0.0.12'

end

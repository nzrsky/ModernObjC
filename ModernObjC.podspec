#
# Be sure to run `pod lib lint ModernObjC.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'ModernObjC'
  s.version          = '0.1.2'
  s.summary          = 'Header-only ObjC modernization pack'

  s.description      = <<-DESC
  It adds lets, vars and typed copy/foreach functions for ObjC collections
  DESC

  s.homepage         = 'https://github.com/nzrsky/ModernObjC'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'Alexey Nazarov' => 'alexx.nazaroff@gmail.com' }
  s.source           = { :git => 'https://github.com/nzrsky/ModernObjC.git', :tag => s.version.to_s }
  s.social_media_url = 'https://twitter.com/nzrsky'

  s.osx.deployment_target = "10.10"
  s.ios.deployment_target = '10.0'
  s.tvos.deployment_target = '10.0'
  s.watchos.deployment_target = '5.0'

  pch_TARGETS = <<-EOS
#ifndef TARGET_OS_IOS
  #define TARGET_OS_IOS TARGET_OS_IPHONE
#endif
#ifndef TARGET_OS_WATCH
  #define TARGET_OS_WATCH 0
#endif
#ifndef TARGET_OS_TV
  #define TARGET_OS_TV 0
#endif
EOS

  s.source_files = 'ModernObjC/Classes/**/*.{m,h}'
  s.frameworks = 'Foundation'
  s.requires_arc = true

  s.xcconfig = {
    'WARNING_CFLAGS' => '-Wno-auto-var-id'
  }
end

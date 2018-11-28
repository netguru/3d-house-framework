Pod::Spec.new do |s|
  s.name             = 'VRHouseFramework'
  s.version          = '0.1'
  s.summary          = 'An open-source OpenCV wrapper written in Objective-C'
  s.homepage         = 'https://github.com/netguru/3d-house-framework'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'Piotr Sochalewski' => 'piotr.sochalewski@netguru.co' }
  s.source           = { :git => 'https://github.com/netguru/3d-house-framework.git', :tag => s.version.to_s }

  s.ios.deployment_target = '9.0'

  s.static_framework = true
  s.source_files = 'VRHouseFramework/Source Files/**/*'
  s.prefix_header_file = 'VRHouseFramework/Supporting Files/Prefix.pch'
  s.dependency 'OpenCV2', '~> 4.0.0'
end
